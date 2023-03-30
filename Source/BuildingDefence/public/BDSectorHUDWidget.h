// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "BDSectorHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDSectorHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;



public:
	void SetSectorName(FString Name);
	void UpdateWidget(int32 CommercialIncome, int32 Range, int32 IndustrialIncome, int32 Tourist);


protected:

	UPROPERTY()
		class UTextBlock* SectorNameText;

	UPROPERTY()
		class UTextBlock* CommercialIncomeText;

	UPROPERTY()
		class UTextBlock* RangeText;

	UPROPERTY()
		class UTextBlock* IndustrialIncomeText;

	UPROPERTY()
		class UTextBlock* TouristText;

private:
	FText SectorName;


};


