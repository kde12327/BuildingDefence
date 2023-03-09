// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BuildingDefence.h"
#include "GameFramework/PlayerController.h"
#include "Sector.h"
#include "BDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGDEFENCE_API ABDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABDPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void OnMouseClicked();

	void UpdateWaveStarted();


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDBottomWidget> BottomWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDCounterWidget> CounterWidgetClass;



private:
	UPROPERTY(EditAnywhere, Category = Sector, Meta = (AllowPrivateAccess = true))
		TArray<class ASector*> Sectors;

	ASector* ClickedSector;

	UPROPERTY()
		class UBDBottomWidget* BottomWidget;

	UPROPERTY()
		class UBDCounterWidget* CounterWidget;

	class AWaveManager* WaveManager;

	int32 WaveNum;

	int32 WaveLevel;
};
