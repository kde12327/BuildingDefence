// Fill out your copyright notice in the Description page of Project Settings.


#include "BDMainMenuWidget.h"
#include "Components/Button.h"

void UBDMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameStartButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnGameStart")));
	if (nullptr != GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UBDMainMenuWidget::OnGameStartClicked);
	}


	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnExit")));
	if (nullptr != ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UBDMainMenuWidget::OnExitClicked);
	}
}

void UBDMainMenuWidget::OnGameStartClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GamePlay"));
}


void UBDMainMenuWidget::OnExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
}