// Fill out your copyright notice in the Description page of Project Settings.


#include "BDGameMode.h"
#include "BDPlayerPawn.h"
#include "BDPlayerController.h"
#include "BDPlayerState.h"

ABDGameMode::ABDGameMode()
{
	DefaultPawnClass = ABDPlayerPawn::StaticClass();
	PlayerControllerClass = ABDPlayerController::StaticClass();
	PlayerStateClass = ABDPlayerState::StaticClass();

}

void ABDGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABDGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

}