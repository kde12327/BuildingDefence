// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/Actor.h"
#include "BDBuilding.generated.h"


UCLASS()
class BUILDINGDEFENCE_API ABDBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABDBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTypes(TArray<BuildingType> NewType);

	TArray<int32> GetTypes();


private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Mesh;

protected:
	

	UPROPERTY()
		TArray<int32> Types;
};
