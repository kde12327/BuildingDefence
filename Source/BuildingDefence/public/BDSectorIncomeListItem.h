// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "BDSectorIncomeListItem.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDSectorIncomeListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

protected:
	UPROPERTY()
		class UTextBlock* SectorNameText;
	
	UPROPERTY()
		class UTextBlock* SectorIncomeText;
};
