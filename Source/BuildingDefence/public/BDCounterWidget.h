// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "BDCounterWidget.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnStartClickedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnPauseClickedDelegate);


UCLASS()
class BUILDINGDEFENCE_API UBDCounterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;


	UFUNCTION()
		void OnStartClicked();

	UFUNCTION()
		void OnPauseClicked();

public:

	void OnWaveEnd();

private:
	void OnReadyCountDown();

protected:

	UPROPERTY()
		class UButton* StartButton;

	UPROPERTY()
		class UTextBlock* CountText;

	UPROPERTY()
		class UButton* PauseButton;

public:

	FOnStartClickedDelegate OnStart;

	FOnPauseClickedDelegate OnPause;

	void UpdateWaveLeftText(int32 WaveLeft);


	

private:

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* ShowStartButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HideStartButton;

	bool WaveStarted;

	FWidgetAnimationDynamicEvent ShowStartButtonDelegate;
	FWidgetAnimationDynamicEvent HideStartButtonDelegate;

	UFUNCTION()
		void ShowStartButtonStarted();

	UFUNCTION()
		void HideStartButtonEnded();

	FTimerHandle ReadyWaveTimer = {};

	int32 CountLeft;

	void UpdateCountText();


};
