// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "Sector.h"

#include "BDLeftWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDLeftWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void ShowSectorDetail();
	void HideSectorDetail();

	UPROPERTY()
		class UTextBlock* SectorName;

	UPROPERTY()
		TArray<class UTextBlock*> TypeTextArray;

	UPROPERTY()
		TArray<class UButton*> TypeButtonArray;
	
	UPROPERTY()
		TArray<class UBorder*> BuildingDetailBorderArray;

	void UpdateSectorDetail(ASector& ClickedSector);


private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* ShowWidget;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HideWidget;

	bool IsRulletVisible;

	const int32 ROW = 7;
	const int32 COL = 4;

};
