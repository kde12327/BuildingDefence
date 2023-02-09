// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/Character.h"
#include "BDPerson.generated.h"

UCLASS()
class BUILDINGDEFENCE_API ABDPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABDPerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
