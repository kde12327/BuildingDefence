// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/PlayerController.h"
#include "BDMainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABDMainMenuPlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDMainMenuWidget> MainMenuWidgetClass;

private:

	UPROPERTY()
		class UBDMainMenuWidget* MainMenuWidget;
};
