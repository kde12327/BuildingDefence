// Fill out your copyright notice in the Description page of Project Settings.


#include "BDSectorIncomeListItem.h"
#include "Components/TextBlock.h"
#include "BDSectorIncomeListItemData.h"

void UBDSectorIncomeListItem::NativeConstruct()
{
	Super::NativeConstruct();

	SectorNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSectorName")));
	SectorIncomeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSectorIncome")));

}

void UBDSectorIncomeListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (nullptr != SectorNameText && nullptr != SectorIncomeText)
	{
		UBDSectorIncomeListItemData* ItemData = Cast<UBDSectorIncomeListItemData>(ListItemObject);
		SectorNameText->SetText(FText::FromString(ItemData->SectorName));
		SectorIncomeText->SetText(FText::FromString(FString::FromInt(ItemData->Income)));

	}
	
}

void UBDSectorIncomeListItem::NativeOnItemSelectionChanged(bool bIsSelected)
{

}