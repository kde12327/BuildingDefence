// Fill out your copyright notice in the Description page of Project Settings.


#include "BDMainMenuPlayerController.h"
#include "BDMainMenuWidget.h"

ABDMainMenuPlayerController::ABDMainMenuPlayerController()
{
	static ConstructorHelpers::FClassFinder<UBDMainMenuWidget> UI_MAINMENU_C(TEXT("/Game/BuildingDefence/UI/UI_BDMainMenuWidget.UI_BDMainMenuWidget_C"));
	if (UI_MAINMENU_C.Succeeded())
	{
		MainMenuWidgetClass = UI_MAINMENU_C.Class;
	}
}

void ABDMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	MainMenuWidget = CreateWidget<UBDMainMenuWidget>(this, MainMenuWidgetClass);
	MainMenuWidget->AddToViewport(1);
}