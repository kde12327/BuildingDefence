// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "AIController.h"
#include "BDPersonAIController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDPersonAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABDPersonAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;


private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;

};
