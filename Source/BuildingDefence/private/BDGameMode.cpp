// Fill out your copyright notice in the Description page of Project Settings.


#include "BDGameMode.h"
#include "BDPlayerPawn.h"
#include "BDPlayerController.h"

ABDGameMode::ABDGameMode()
{
	DefaultPawnClass = ABDPlayerPawn::StaticClass();
	PlayerControllerClass = ABDPlayerController::StaticClass();
}