// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "WaveManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWaveEndDelegate);


UCLASS()
class BUILDINGDEFENCE_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void WaveStart();

	void WaveEnd();

	void SetWaveNum(int32 Num);

private:
	void OnPersonSpawn();
	
	UFUNCTION()
		void OnWaveEndTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


public:	
	UPROPERTY()
		class UBDCounterWidget* CounterWidget;

	FOnWaveEndDelegate OnWaveEnd;


	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
		UBoxComponent* WaveEndTrigger;

	UPROPERTY(EditAnywhere, Category = WavePoint, Meta = (AllowPrivateAccess = true))
		TArray<ATargetPoint*> WavePoints;

private:
	int32 WaveCount;
	int32 WaveLeftCount;

	float TimeCount = 0.0f;
	bool TempFlag = false;

	FTimerHandle SpawnPersonTimer = {};
};
