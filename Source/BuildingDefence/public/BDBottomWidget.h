// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "Sector.h"

#include "BDBottomWidget.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnRerollClickedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBuildClickedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnConfirmClickedDelegate);


UCLASS()
class BUILDINGDEFENCE_API UBDBottomWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnRerollClicked();

	UFUNCTION()
		void OnBuildClicked();
	
	UFUNCTION()
		void OnConfirmClicked();

	
public:
	void SetMoneyText(int32 Money);

	void SetWaveText(int32 Wave);

protected:
	UPROPERTY()
		class UButton* RerollButton;

	UPROPERTY()
		class UButton* BuildButton;

	UPROPERTY()
		class UButton* ConfirmButton;

	UPROPERTY()
		TArray<class UTextBlock*> RulletTextArray;
	
	UPROPERTY()
		TArray<class UButton*> RulletButtonArray;
	
	UPROPERTY()
		class UTextBlock* RerollCostText;
	
	UPROPERTY()
		class UTextBlock* BuildCostText;
	
	
	UPROPERTY()
		class UTextBlock* MoneyText;
	
	UPROPERTY()
		class UTextBlock* WaveText;
	
	UPROPERTY()
		class UTextBlock* TaxText;


public:
	FOnBuildClickedDelegate OnBuild;

	FOnRerollClickedDelegate OnReroll;

	FOnRerollClickedDelegate OnConfirm;

	void UpdateRullet(ASector& ClickedSector);

	void UpdateWidgetByMoney(ASector& ClickedSector, int32 money);

	void ShowBuild();

	void ShowRullet();
	void HideRullet();
	
private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* ShowWidget;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HideWidget;

	bool IsRulletVisible;
};
