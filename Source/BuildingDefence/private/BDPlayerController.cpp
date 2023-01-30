// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerController.h"
#include "Sector.h"

void ABDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;


}

void ABDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("InputClick"), EInputEvent::IE_Pressed, this, &ABDPlayerController::OnMouseClicked);
}

void ABDPlayerController::OnMouseClicked()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery_MAX, true, Hit);

	BDCHECK(nullptr != Hit.GetActor());
	BDLOG(Warning, TEXT("%s"), *Hit.GetActor()->GetName());
	BDCHECK(nullptr != Cast<ASector>(Hit.GetActor()));


}