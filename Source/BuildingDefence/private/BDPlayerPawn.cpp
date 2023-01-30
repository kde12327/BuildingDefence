// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerPawn.h"

// Sets default values
ABDPlayerPawn::ABDPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ABDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABDPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

