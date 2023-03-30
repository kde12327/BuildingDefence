// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "UObject/NoExportTypes.h"
#include "BDSectorIncomeListItemData.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDSectorIncomeListItemData : public UObject
{
	GENERATED_BODY()
	
public:
	FString SectorName;
	int32 Income;
};
