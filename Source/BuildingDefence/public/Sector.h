// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/Actor.h"
#include "BDBuilding.h"

#include "Sector.generated.h"

UCLASS()
class BUILDINGDEFENCE_API ASector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASector();

	void BuildBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Click)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* SectorDetailWidget;



public:
	void OnSectorClicked();

	void OnSectorFocusOut();

private:

	TArray<ABDBuilding*> Buildings;
};
