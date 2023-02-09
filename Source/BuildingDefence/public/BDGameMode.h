// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/GameModeBase.h"
#include "BDGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABDGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
