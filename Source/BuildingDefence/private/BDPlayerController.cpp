// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerController.h"
#include "BDBottomWidget.h"
#include "BDLeftWidget.h"
#include "BDRightWidget.h"
#include "BDCounterWidget.h"
#include "Sector.h"
#include "BDPlayerState.h"
#include "WaveManager.h"



ABDPlayerController::ABDPlayerController()
{
	static ConstructorHelpers::FClassFinder<UBDBottomWidget> UI_BOTTOM_C(TEXT("/Game/BuildingDefence/UI/UI_BDBottomWidget.UI_BDBottomWidget_C"));
	if (UI_BOTTOM_C.Succeeded())
	{
		BottomWidgetClass = UI_BOTTOM_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UBDLeftWidget> UI_LEFT_C(TEXT("/Game/BuildingDefence/UI/UI_BDLeftWidget.UI_BDLeftWidget_C"));
	if (UI_LEFT_C.Succeeded())
	{
		LeftWidgetClass = UI_LEFT_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UBDCounterWidget> UI_COUNTER_C(TEXT("/Game/BuildingDefence/UI/UI_BDCounterWidget.UI_BDCounterWidget_C"));
	if (UI_COUNTER_C.Succeeded())
	{
		CounterWidgetClass = UI_COUNTER_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UBDRightWidget> UI_RIGHT_C(TEXT("/Game/BuildingDefence/UI/UI_BDRightWidget.UI_BDRightWidget_C"));
	if (UI_RIGHT_C.Succeeded())
	{
		RightWidgetClass = UI_RIGHT_C.Class;
	}

	WaveLevel = 1;
	GameState = InGameState::READY;
	UpdateWaveStarted();

	SecondCounter = 0.0f;
}

void ABDPlayerController::Tick(float DeltaTime)
{
	int32 CurrentMoney = static_cast<ABDPlayerState*>(PlayerState)->GetCurrentMoney();

	// Update Money Text on Bottom Widget
	BottomWidget->SetMoneyText(CurrentMoney);

	// Check has enough money for reroll & build
	if (nullptr != ClickedSector)
	{
		BottomWidget->UpdateWidgetByMoney(*ClickedSector, CurrentMoney);

	}
	

	SecondCounter += DeltaTime;
	if (SecondCounter >= 1.0f)
	{
		SecondCounter -= 1.0f;

		RightWidget->UpdateIncomeWidget(Sectors);
	}

}


void ABDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	



	BottomWidget = CreateWidget<UBDBottomWidget>(this, BottomWidgetClass);
	BottomWidget->AddToViewport(1);
	BottomWidget->OnBuild.AddLambda([this]()->void {
		// On Build
		BDCHECK(nullptr != ClickedSector);
		if (!ClickedSector->GetCanBuild() && static_cast<ABDPlayerState*>(PlayerState)->UseMoney(ClickedSector->GetNeedBuildMoney()))
		{
			ClickedSector->Reroll();
			BottomWidget->UpdateRullet(*ClickedSector);
			BottomWidget->ShowRullet();

		}
	});

	BottomWidget->OnReroll.AddLambda([this]()->void {
		// On Reroll
		BDCHECK(nullptr != ClickedSector);

		if (static_cast<ABDPlayerState*>(PlayerState)->UseMoney(ClickedSector->GetNeedRerollMoney()))
		{
			ClickedSector->Reroll();
			BottomWidget->UpdateRullet(*ClickedSector);
			LeftWidget->UpdateSectorDetail(*ClickedSector);

		}
	});
	
	BottomWidget->OnConfirm.AddLambda([this]()->void {
		// On Reroll
		BDCHECK(nullptr != ClickedSector);
		if (ClickedSector->GetCanBuild())
		{
			ClickedSector->BuildBuilding();
			BottomWidget->HideRullet();
			LeftWidget->UpdateSectorDetail(*ClickedSector);

		}
	});

	LeftWidget = CreateWidget<UBDLeftWidget>(this, LeftWidgetClass);
	LeftWidget->AddToViewport(1);


	CounterWidget = CreateWidget<UBDCounterWidget>(this, CounterWidgetClass);
	CounterWidget->AddToViewport(1);
	CounterWidget->OnStart.AddLambda([this]()->void {
		// On Wave Start
		BDLOG_S(Warning);
		UpdateWaveStarted();
		BDLOG(Warning, TEXT("%d"), WaveNum);

		WaveManager->SetWaveNum(WaveNum);
		WaveManager->WaveStart();
		SetGameState(InGameState::WAVE);
		if (ClickedSector) {
			ClickedSector->OnSectorFocusOut();
			ClickedSector = nullptr;
			BottomWidget->HideRullet();
			LeftWidget->HideSectorDetail();
		}

		for (auto Sector : Sectors)
		{
			Sector->InitWaveIncome();
		}
	});

	

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveManager::StaticClass(), FoundActors);

	BDCHECK(FoundActors.Num() == 1);
	WaveManager = static_cast<AWaveManager*>(FoundActors[0]);
	WaveManager->CounterWidget = CounterWidget;
	
	WaveManager->OnWaveEnd.AddLambda([this]()->void {
		// On Wave End
		BDLOG_S(Warning);
		CounterWidget->OnWaveEnd();

		WaveLevel++;
		BottomWidget->SetWaveText(WaveLevel);
		SetGameState(InGameState::READY);

	});

	FoundActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASector::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		Sectors.Add(static_cast<ASector*>(FoundActors[i]));
	}

	BDCHECK(RightWidgetClass != nullptr);
	RightWidget = CreateWidget<UBDRightWidget>(this, RightWidgetClass);
	RightWidget->AddToViewport(1);
	RightWidget->UpdateIncomeWidget(Sectors);
	
	
}

void ABDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("InputClick"), EInputEvent::IE_Pressed, this, &ABDPlayerController::OnMouseClicked);
	InputComponent->BindAction(TEXT("Tap"), EInputEvent::IE_Pressed, this, &ABDPlayerController::OnTapPressed);
	InputComponent->BindAction(TEXT("Tap"), EInputEvent::IE_Released, this, &ABDPlayerController::OnTapReleased);
}

void ABDPlayerController::SetGameState(InGameState NewGameState)
{
	switch (NewGameState) {

	case InGameState::READY:
		GameState = NewGameState;
		for (auto Sector : Sectors)
		{
			Sector->IsEnable = false;
		}
		break;
	case InGameState::WAVE:
		GameState = NewGameState;
		for (auto Sector : Sectors)
		{
			Sector->IsEnable = true;
		}
		break;
	default:
		break;
	}
}

void ABDPlayerController::OnMouseClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, Hit);

	BDCHECK(nullptr != Hit.GetActor());
	BDLOG(Warning, TEXT("%s"), *Hit.GetActor()->GetName());

	if (GameState == InGameState::READY)
	{
		if (nullptr != Cast<ASector>(Hit.GetActor()))
		{
			//BDCHECK(nullptr != ClickedSector);
			if (nullptr != ClickedSector && ClickedSector != static_cast<ASector*>(Hit.GetActor()))
			{
				ClickedSector->OnSectorFocusOut();
			}
			ClickedSector = static_cast<ASector*>(Hit.GetActor());
			ClickedSector->OnSectorClicked();
			BottomWidget->UpdateRullet(*ClickedSector);
			LeftWidget->UpdateSectorDetail(*ClickedSector);

			if (ClickedSector->GetCanBuild())
			{
				BottomWidget->ShowRullet();
				LeftWidget->ShowSectorDetail();
			}
			else
			{
				BottomWidget->ShowBuild();
				LeftWidget->ShowSectorDetail();
			}


		}
		else
		{
			if (ClickedSector) {
				ClickedSector->OnSectorFocusOut();
				ClickedSector = nullptr;
				BottomWidget->HideRullet();
				LeftWidget->HideSectorDetail();


			}


		}

	}
}

void ABDPlayerController::OnTapPressed()
{
	RightWidget->ShowIncomeWidget();
}

void ABDPlayerController::OnTapReleased()
{
	RightWidget->HideIncomeWidget();
}

void ABDPlayerController::UpdateWaveStarted()
{
	WaveNum = 5 + WaveLevel;

	for (int i = 0; i < Sectors.Num(); i++)
	{
		WaveNum += Sectors[i]->GetAdditionalPerson();
	}
}

