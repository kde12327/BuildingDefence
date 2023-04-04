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

	void OnTapPressed();

	void OnTapReleased();

	void UpdateWaveStarted();


public:
	enum class InGameState
	{
		READY,
		WAVE,
		GAMEOVER,
	};
	void SetGameState(InGameState NewGameState);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDBottomWidget> BottomWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDLeftWidget> LeftWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDCounterWidget> CounterWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDRightWidget> RightWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDGameOverWidget> GameOverWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UBDPauseWidget> PauseWidgetClass;

private:
	UPROPERTY(EditAnywhere, Category = Sector, Meta = (AllowPrivateAccess = true))
		TArray<class ASector*> Sectors;

	ASector* ClickedSector;

	UPROPERTY()
		class UBDBottomWidget* BottomWidget;
	
	UPROPERTY()
		class UBDLeftWidget* LeftWidget;

	UPROPERTY()
		class UBDCounterWidget* CounterWidget;
	
	UPROPERTY()
		class UBDRightWidget* RightWidget;

	UPROPERTY()
		class UBDGameOverWidget* GameOverWidget;

	UPROPERTY()
		class UBDPauseWidget* PauseWidget;

	class AWaveManager* WaveManager;

	int32 WaveNum;

	int32 WaveLevel;

	InGameState GameState;

	float SecondCounter;
};
