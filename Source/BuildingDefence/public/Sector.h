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
		UBoxComponent* ClickableTrigger;

	UPROPERTY(VisibleAnywhere, Category = Range)
		USphereComponent* RangeTrigger;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* SectorDetailWidget;

	



public:
	void OnSectorClicked();

	void OnSectorFocusOut();

	void Reroll();

	void UpdateState();

	int32 GetAdditionalPerson();

	int32 GetLevel();

	int32 GetNeedRerollMoney();

	int32 GetNeedBuildMoney();

	bool GetCanBuild();

	TArray<ABDBuilding*> GetBuildings();

	void InitWaveIncome();

	int32 GetWaveIncome();

	void AddWaveIncome(float money);

	FString GetSectorName();

public:
	TArray<BuildingType> RulletTypeArray;

	bool IsEnable;

	

private:

	TArray<ABDBuilding*> Buildings;

	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = Sector, Meta = (AllowPrivateAccess = true))
		FString SectorName;

	TArray<int32> BuildingGrades;

	float TakingMoneyPerSecond;
	float TakingMoneyRadius;
	float ProducedMoneyPerSecond;
	int32 AdditionalPersonNum;
	
	int32 OwnerPlayerIndex = 0;

	bool CanBuild = false;

	int32 Level;

	float WaveIncome;

	float BoxWidth = 80.0f;
	float BoxHeight = 80.0f;

};
