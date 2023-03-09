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

	
public:
	void SetMoneyText(int32 Money);

protected:
	UPROPERTY()
		class UButton* RerollButton;

	UPROPERTY()
		class UButton* BuildButton;

	UPROPERTY()
		TArray<class UTextBlock*> RulletTextArray;
	
	UPROPERTY()
		class UTextBlock* RerollCostText;
	
	UPROPERTY()
		class UTextBlock* BuildCostText;
	
	UPROPERTY()
		class UTextBlock* MoneyText;


public:
	FOnBuildClickedDelegate OnBuild;

	FOnRerollClickedDelegate OnReroll;

	void UpdateRullet(ASector& ClickedSector);

	void UpdateWidgetByMoney(ASector& ClickedSector, int32 money);
	

};
