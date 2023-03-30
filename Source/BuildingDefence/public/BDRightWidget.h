// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BDSectorIncomeListItemData.h"
#include "BDRightWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDRightWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
		class UListView* SectorIncomeListView;

public:
	void ShowIncomeWidget();
	void HideIncomeWidget();

	void UpdateIncomeWidget(TArray<class ASector*>& Sectors);

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* ShowWidget;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HideWidget;

	bool IsWidgetVisible = false;

};
