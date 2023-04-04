// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "BDPauseWidget.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnToMainClickedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnResumeClickedDelegate);

UCLASS()
class BUILDINGDEFENCE_API UBDPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnToMainClicked();

	UFUNCTION()
		void OnResumeClicked();

protected:

	UPROPERTY()
		class UButton* ToMainButton;


	UPROPERTY()
		class UButton* ResumeButton;

public:

	FOnToMainClickedDelegate OnToMain;

	FOnResumeClickedDelegate OnResume;

};
