// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerController.h"
#include "BDBottomWidget.h"
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

	static ConstructorHelpers::FClassFinder<UBDCounterWidget> UI_COUNTER_C(TEXT("/Game/BuildingDefence/UI/UI_BDCounterWidget.UI_BDCounterWidget_C"));
	if (UI_COUNTER_C.Succeeded())
	{
		CounterWidgetClass = UI_COUNTER_C.Class;
	}

	WaveLevel = 1;

	UpdateWaveStarted();
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
}


void ABDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	



	BottomWidget = CreateWidget<UBDBottomWidget>(this, BottomWidgetClass);
	BottomWidget->AddToViewport(1);
	BottomWidget->SetVisibility(ESlateVisibility::Hidden);
	BottomWidget->OnBuild.AddLambda([this]()->void {
		// On Build
		BDCHECK(nullptr != ClickedSector);
		if (static_cast<ABDPlayerState*>(PlayerState)->UseMoney(ClickedSector->GetNeedBuildMoney()))
		{
			ClickedSector->BuildBuilding();
		}
	});

	BottomWidget->OnReroll.AddLambda([this]()->void {
		// On Reroll
		BDCHECK(nullptr != ClickedSector);

		if (static_cast<ABDPlayerState*>(PlayerState)->UseMoney(ClickedSector->GetNeedRerollMoney()))
		{
			ClickedSector->Reroll();
			BottomWidget->UpdateRullet(*ClickedSector);
		}
	});

	CounterWidget = CreateWidget<UBDCounterWidget>(this, CounterWidgetClass);
	CounterWidget->AddToViewport(1);
	CounterWidget->OnStart.AddLambda([this]()->void {
		// On Wave Start
		BDLOG_S(Warning);
		UpdateWaveStarted();
		BDLOG(Warning, TEXT("%d"), WaveNum);

		WaveManager->SetWaveNum(WaveNum);
		WaveManager->WaveStart();
	});

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveManager::StaticClass(), FoundActors);

	BDCHECK(FoundActors.Num() == 1);
	WaveManager = static_cast<AWaveManager*>(FoundActors[0]);
	WaveManager->CounterWidget = CounterWidget;
	
	FoundActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASector::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		Sectors.Add(static_cast<ASector*>(FoundActors[i]));
	}

	
	
}

void ABDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("InputClick"), EInputEvent::IE_Pressed, this, &ABDPlayerController::OnMouseClicked);
}

void ABDPlayerController::OnMouseClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, Hit);

	BDCHECK(nullptr != Hit.GetActor());
	BDLOG(Warning, TEXT("%s"), *Hit.GetActor()->GetName());



	if (nullptr != Cast<ASector>(Hit.GetActor()))
	{
		//BDCHECK(nullptr != ClickedSector);
		if (nullptr != ClickedSector && ClickedSector != Cast<ASector>(Hit.GetActor()))
		{
			ClickedSector->OnSectorFocusOut();
		}
		ClickedSector = Cast<ASector>(Hit.GetActor());
		ClickedSector->OnSectorClicked();
		BottomWidget->SetVisibility(ESlateVisibility::Visible);

		BottomWidget->UpdateRullet(*ClickedSector);

		
	}
	else
	{
		if (ClickedSector) {
			ClickedSector->OnSectorFocusOut();
			ClickedSector = nullptr;
			BottomWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		

	}


}

void ABDPlayerController::UpdateWaveStarted()
{
	WaveNum = 5 + WaveLevel;

	for (int i = 0; i < Sectors.Num(); i++)
	{
		WaveNum += Sectors[i]->GetAdditionalPerson();
	}
}