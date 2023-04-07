// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingDefenceGameModeBase.h"
#include "BDMainMenuPlayerController.h"

ABuildingDefenceGameModeBase::ABuildingDefenceGameModeBase()
{
	PlayerControllerClass = ABDMainMenuPlayerController::StaticClass();

}