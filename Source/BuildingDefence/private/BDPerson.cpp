// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPerson.h"
#include "BDPersonAIController.h"


// Sets default values
ABDPerson::ABDPerson()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("BDPerson"));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_CAR(TEXT("/Game/SimPoly_Town/Models/Car/SK_Car_01.SK_Car_01"));
	if (SM_CAR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_CAR.Object);
	}

	AIControllerClass = ABDPersonAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	TargetWaveIndex = 0;

}


// Called when the game starts or when spawned
void ABDPerson::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABDPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABDPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called to bind functionality to input
void ABDPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



