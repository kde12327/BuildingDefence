// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLeftWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"


void UBDLeftWidget::NativeConstruct()
{

	Super::NativeConstruct();

	
	SectorName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSectorName")));

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			TypeTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(FString(TEXT("TextBuildingType")) + FString::FromInt(i) + TEXT("_") + FString::FromInt(j)))));
			TypeButtonArray.Add(Cast<UButton>(GetWidgetFromName(FName(FString(TEXT("BtnBuildingType")) + FString::FromInt(i) + TEXT("_") + FString::FromInt(j)))));
			TypeButtonArray[i * COL + j]->SetBackgroundColor(BuildingTypeColor[j]);
		}
		BuildingDetailBorderArray.Add(Cast<UBorder>(GetWidgetFromName(FName(FString(TEXT("BorderBuilding")) + FString::FromInt(i)))));
	}
	

	IsRulletVisible = false;
}

void UBDLeftWidget::ShowSectorDetail()
{
	if (!IsRulletVisible)
	{
		PlayAnimation(ShowWidget);
		IsRulletVisible = true;
	}
}


void UBDLeftWidget::HideSectorDetail()
{
	if (IsRulletVisible)
	{
		PlayAnimation(HideWidget);
		IsRulletVisible = false;
	}
}

void UBDLeftWidget::UpdateSectorDetail(ASector& ClickedSector)
{
	auto Buildings = ClickedSector.GetBuildings();

	for (int BuildingIdx = 0; BuildingIdx < Buildings.Num(); BuildingIdx++)
	{
		auto BuildingTypes = Buildings[BuildingIdx]->GetTypes();

		for (int TypeIdx = 0; TypeIdx < COL; TypeIdx++)
		{
			TypeTextArray[BuildingIdx * COL + TypeIdx]->SetText(FText::FromString(FString::FromInt(BuildingTypes[TypeIdx])));
		}
		BuildingDetailBorderArray[BuildingIdx]->SetVisibility(ESlateVisibility::Visible);
	}

	for (int EmptyIdx = Buildings.Num(); EmptyIdx < ROW; EmptyIdx++)
	{
		BuildingDetailBorderArray[EmptyIdx]->SetVisibility(ESlateVisibility::Hidden);

	}
}