// Fill out your copyright notice in the Description page of Project Settings.


#include "Sector.h"
#include "Components/WidgetComponent.h"


// Sets default values
ASector::ASector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SectorDetailWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SECTORDETAILWIDGET"));


	RootComponent = Trigger;
	SectorDetailWidget->SetupAttachment(RootComponent);


	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	Trigger->SetCollisionProfileName(TEXT("ClickableObject"));

	SectorDetailWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SectorDetailWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/BuildingDefence/UI/UI_BDSectorHUDWidget.UI_BDSectorHUDWidget_C"));
	BDCHECK(UI_HUD.Succeeded());
	if (UI_HUD.Succeeded())
	{
		SectorDetailWidget->SetWidgetClass(UI_HUD.Class);
		SectorDetailWidget->SetDrawSize(FVector2D(200.0f, 150.0f));
	}


}

void ASector::BuildBuilding()
{
	BDLOG_S(Warning);
	auto Building = GetWorld()->SpawnActor<ABDBuilding>(GetActorLocation(), FRotator::ZeroRotator);

	Buildings.Add(Building);
}

// Called when the game starts or when spawned
void ASector::BeginPlay()
{
	Super::BeginPlay();

	SectorDetailWidget->SetRelativeLocation(FVector(0.0f, 100.0f, 100.0f));
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

}


void ASector::OnSectorClicked()
{
	SectorDetailWidget->SetHiddenInGame(false);
}

void ASector::OnSectorFocusOut()
{
	SectorDetailWidget->SetHiddenInGame(true);
}