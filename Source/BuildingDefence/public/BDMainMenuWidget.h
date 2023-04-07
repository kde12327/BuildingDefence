// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "BDMainMenuWidget.generated.h"

/**
 * 
 */


DECLARE_MULTICAST_DELEGATE(FOnGameStartClickedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExitClickedDelegate);

UCLASS()
class BUILDINGDEFENCE_API UBDMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnGameStartClicked();

	UFUNCTION()
		void OnExitClicked();

protected:

	UPROPERTY()
		class UButton* GameStartButton;

	UPROPERTY()
		class UButton* ExitButton;

public:

	FOnGameStartClickedDelegate OnGameStart;

	FOnExitClickedDelegate OnExit;

};
