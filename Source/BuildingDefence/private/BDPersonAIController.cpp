// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPersonAIController.h"
#include "BDPerson.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ABDPersonAIController::ABDPersonAIController()
{

}

void ABDPersonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ABDPersonAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ABDPerson* PossessedPawn = static_cast<ABDPerson*>(GetPawn());

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());


	if (PossessedPawn->WavePoints.Num() > 0 && (PossessedPawn->GetActorLocation() * FVector(1.0f, 1.0f, 0.0f) - PossessedPawn->WavePoints[PossessedPawn->TargetWaveIndex]->GetActorLocation() * FVector(1.0f, 1.0f, 0.0f)).Size() < 10.0f)
	{
		if (PossessedPawn->TargetWaveIndex < PossessedPawn->WavePoints.Num() - 1)
		{
			PossessedPawn->TargetWaveIndex++;
		}
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossessedPawn->WavePoints[PossessedPawn->TargetWaveIndex]->GetActorLocation());
	}
	
}



