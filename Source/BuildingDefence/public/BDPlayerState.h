// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/PlayerState.h"
#include "BDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ABDPlayerState();

	float GetCurrentMoney() const;

	bool UseMoney(float Cost);
	void AddMoney(float IncomeMoney);

protected:
	UPROPERTY(Transient)
		float CurrentMoney;

};
