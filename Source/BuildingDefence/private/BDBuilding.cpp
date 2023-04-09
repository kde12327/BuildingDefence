// Fill out your copyright notice in the Description page of Project Settings.


#include "BDBuilding.h"

// Sets default values
ABDBuilding::ABDBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	FString AssetPath = TEXT("/Game/BuildingDefence/Models/SM_House_Red.SM_House_Red");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_HOUSE(*AssetPath);
	if (SM_HOUSE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_HOUSE.Object);
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
		Mesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		Mesh->SetRelativeScale3D(FVector(0.033f, 0.033f, 0.033f));
	}
	else
	{
		BDLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	AssetPath = TEXT("/Game/BuildingDefence/Models/SM_House_Red.SM_House_Red");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> REDBUILDINGMESH(*AssetPath);
	
	if (REDBUILDINGMESH.Succeeded())
	{
		BuildingMeshs.Add(REDBUILDINGMESH.Object);
	}

	AssetPath = TEXT("/Game/BuildingDefence/Models/SM_House_Yellow.SM_House_Yellow");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> YELLOWBUILDINGMESH(*AssetPath);

	if (YELLOWBUILDINGMESH.Succeeded())
	{
		BuildingMeshs.Add(YELLOWBUILDINGMESH.Object);
	}

	AssetPath = TEXT("/Game/BuildingDefence/Models/SM_House_Green.SM_House_Green");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GREENBUILDINGMESH(*AssetPath);

	if (GREENBUILDINGMESH.Succeeded())
	{
		BuildingMeshs.Add(GREENBUILDINGMESH.Object);
	}

	AssetPath = TEXT("/Game/BuildingDefence/Models/SM_House_Blue.SM_House_Blue");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BLUEBUILDINGMESH(*AssetPath);

	if (BLUEBUILDINGMESH.Succeeded())
	{
		BuildingMeshs.Add(BLUEBUILDINGMESH.Object);
	}


	Types.Init(0, 4);
}

// Called when the game starts or when spawned
void ABDBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABDBuilding::SetTypes(TArray<BuildingType> NewType)
{
	Types.Init(0, 4);

	for (int TypeIdx = 0; TypeIdx < NewType.Num(); TypeIdx++)
	{
		Types[static_cast<int32>(NewType[TypeIdx])] ++;

		if (Types[static_cast<int32>(NewType[TypeIdx])] > Grade)
		{
			MainType = static_cast<int32>(NewType[TypeIdx]);
			Grade = Types[static_cast<int32>(NewType[TypeIdx])];
		}
		else if(Types[static_cast<int32>(NewType[TypeIdx])] == Grade)
		{
			MainType = (FMath::RandRange(0, 1) == 0)? MainType : static_cast<int32>(NewType[TypeIdx]);
		}
	}

	Mesh->SetStaticMesh(BuildingMeshs[MainType]);

}


TArray<int32> ABDBuilding::GetTypes()
{
	return Types;
}

