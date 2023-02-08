// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerController.h"
#include "BDBottomWidget.h"


ABDPlayerController::ABDPlayerController()
{
	static ConstructorHelpers::FClassFinder<UBDBottomWidget> UI_BOTTOM_C(TEXT("/Game/BuildingDefence/UI/UI_BDBottomWidget.UI_BDBottomWidget_C"));
	if (UI_BOTTOM_C.Succeeded())
	{
		BottomWidgetClass = UI_BOTTOM_C.Class;
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
		BDCHECK(nullptr != ClickedSector);

		ClickedSector->BuildBuilding();
	});
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



		
	}
	else
	{
		ClickedSector->OnSectorFocusOut();
		ClickedSector = nullptr;
		BottomWidget->SetVisibility(ESlateVisibility::Hidden);



	}


}