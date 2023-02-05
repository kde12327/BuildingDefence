// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/PlayerController.h"
#include "Sector.h"
#include "BDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABDPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void OnMouseClicked();

private:
	ASector* ClickedSector;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDBottomWidget> BottomWidgetClass;

private:
	UPROPERTY()
		class UBDBottomWidget* BottomWidget;
};
