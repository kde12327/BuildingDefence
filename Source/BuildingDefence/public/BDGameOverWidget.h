// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BDGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API UBDGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	void SetLastWave(int32 Wave);

	void SetTotalIncome(int32 Income);


protected:
	
	UPROPERTY()
		class UTextBlock* LastWaveText;

	UPROPERTY()
		class UTextBlock* TotalIncomeText;

	UPROPERTY()
		class UButton* ToMainButton;
};
