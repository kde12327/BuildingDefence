// Fill out your copyright notice in the Description page of Project Settings.


#include "Sector.h"
#include "Components/WidgetComponent.h"
#include "BDPerson.h"
#include "BDPlayerState.h"
#include "Kismet/GamePlayStatics.h"


// Sets default values
ASector::ASector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClickableTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CLICKABLETrigger"));
	RangeTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RANGETrigger"));
	SectorDetailWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SECTORDETAILWIDGET"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = BaseMesh;
	ClickableTrigger->SetupAttachment(RootComponent);
	SectorDetailWidget->SetupAttachment(RootComponent);
	RangeTrigger->SetupAttachment(RootComponent);


	ClickableTrigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	ClickableTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	ClickableTrigger->SetCollisionProfileName(TEXT("ClickableObject"));
	RangeTrigger->SetRelativeScale3D(FVector(4.0f, 4.0f, 4.0f));



	FString SMPalletAssetPath = TEXT("/Game/SimPoly_Town/Models/Props/SM_Pallet.SM_Pallet");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PALLET(*SMPalletAssetPath);
	if (SM_PALLET.Succeeded())
	{
		BaseMesh->SetStaticMesh(SM_PALLET.Object);
		BaseMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		//Mesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		//Mesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	}
	else
	{
		BDLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *SMPalletAssetPath);
	}


	SectorDetailWidget->SetRelativeLocation(FVector(0.0f, 150.0f, 100.0f));
	SectorDetailWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/BuildingDefence/UI/UI_BDSectorHUDWidget.UI_BDSectorHUDWidget_C"));
	BDCHECK(UI_HUD.Succeeded());
	if (UI_HUD.Succeeded())
	{
		SectorDetailWidget->SetWidgetClass(UI_HUD.Class);
		SectorDetailWidget->SetDrawSize(FVector2D(200.0f, 150.0f));
	}


	TakingMoneyPerSecond = 0.0f;
	TakingMoneyRadius = 0.0f;
	ProducedMoneyPerSecond = 0.0f;
	AdditionalPersonNum = 0;


	BuildingGrades.Init(0, 4);

	RulletTypeArray.Init(BuildingType::RESIDENCE, 5);
	Reroll();

}

void ASector::BuildBuilding()
{
	BDLOG_S(Warning);
	if (CanBuild)
	{
		int32 Count[5] = { 0, };
		TArray<int32> MaxTypes;
		int32 MaxType;
		int32 MaxValue = 0;
		

		for (int i = 0; i < RulletTypeArray.Num(); i++)
		{
			Count[static_cast<int32>(RulletTypeArray[i])]++;
		}

		for (int i = 0; i < RulletTypeArray.Num(); i++)
		{
			if (MaxValue < Count[i])
			{
				MaxValue = Count[i];
				MaxTypes.SetNum(0);
				MaxTypes.Add(i);
			}
			else if (MaxValue == Count[i])
			{
				MaxTypes.Add(i);
			}
		}

		if (MaxTypes.Num() == 1)
		{
			MaxType = MaxTypes[0];
		}
		else
		{
			MaxType = MaxTypes[FMath::RandRange(0, MaxTypes.Num() - 1)];
		}
		
		
		auto Building = GetWorld()->SpawnActor<ABDBuilding>(GetActorLocation() + FVector(0.0f, 0.0f, 45.0f), FRotator::ZeroRotator);
		Building->SetType(static_cast<BuildingType>(MaxType));
		Building->SetGrade(MaxValue);

		Buildings.Add(Building);
		UpdateState();

		CanBuild = false;

		BDLOG(Warning, TEXT("%f %f %f %d"), TakingMoneyPerSecond, TakingMoneyRadius, ProducedMoneyPerSecond, AdditionalPersonNum)
	}
}

// Called when the game starts or when spawned
void ASector::BeginPlay()
{
	Super::BeginPlay();

	//SectorDetailWidget->SetRelativeLocation(FVector(0.0f, 100.0f, 100.0f));
	SectorDetailWidget->SetHiddenInGame(true);

	
}

void ASector::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ASector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	UWorld* World = GetWorld();
	FVector Center = GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(TakingMoneyRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		float TakingMoney = 0.0f;
		for (auto const& OverlapResult : OverlapResults)
		{
			ABDPerson* BDPerson = Cast<ABDPerson>(OverlapResult.GetActor());
			if (BDPerson)
			{
				DrawDebugSphere(World, Center, TakingMoneyRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugLine(World, GetActorLocation(), BDPerson->GetActorLocation(), FColor::Blue, false, 0.2f);

				TakingMoney += TakingMoneyPerSecond * DeltaTime;

			}
		}

		if (TakingMoney > 0.0f)
		{
			ABDPlayerState* BDPlayerState = Cast<ABDPlayerState>(UGameplayStatics::GetPlayerPawn(World, 0)->GetPlayerState());
			BDPlayerState->AddMoney(TakingMoney);
		}
		
	}

	float ProducedMoney = 0.0f;
	ProducedMoney += ProducedMoneyPerSecond * DeltaTime;
	if (ProducedMoney > 0.0f)
	{
		ABDPlayerState* BDPlayerState = Cast<ABDPlayerState>(UGameplayStatics::GetPlayerPawn(World, 0)->GetPlayerState());
		BDPlayerState->AddMoney(ProducedMoney);
	}

	DrawDebugSphere(World, Center, TakingMoneyRadius, 16, FColor::Red, false, 0.2f);


}


void ASector::OnSectorClicked()
{
	SectorDetailWidget->SetHiddenInGame(false);
}

void ASector::OnSectorFocusOut()
{
	SectorDetailWidget->SetHiddenInGame(true);
}

void ASector::Reroll()
{
	for (int i = 0; i < RulletTypeArray.Num(); i++)
	{
		RulletTypeArray[i] = static_cast<BuildingType>(FMath::RandRange(static_cast<int32>(BuildingType::RESIDENCE), static_cast<int32>(BuildingType::TOURISM)));
	}

	CanBuild = true;
}

void ASector::UpdateState()
{
	// Initiate BuildingGrades
	for (int i = 0; i < BuildingGrades.Num(); i++)
	{
		BuildingGrades[i] = 0;
	}

	// Count Buildings Grade
	for (int i = 0; i < Buildings.Num(); i++)
	{
		BuildingGrades[static_cast<int32>(Buildings[i]->GetType())] = Buildings[i]->GetGrade();
	}

	TakingMoneyPerSecond = BuildingGrades[static_cast<int32>(BuildingType::COMMERCE)] * 10.0f;
	TakingMoneyRadius = (BuildingGrades[static_cast<int32>(BuildingType::TOURISM)] * 0.1f + 1.0f) * 150.0f;
	ProducedMoneyPerSecond = BuildingGrades[static_cast<int32>(BuildingType::INDUSTRY)] * 2.0f;
	AdditionalPersonNum = BuildingGrades[static_cast<int32>(BuildingType::RESIDENCE)];

}