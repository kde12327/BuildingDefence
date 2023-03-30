// Fill out your copyright notice in the Description page of Project Settings.


#include "BDSectorHUDWidget.h"
#include "Components/TextBlock.h"


void UBDSectorHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SectorNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSectorName")));
	CommercialIncomeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCommercialIncome")));
	RangeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextRange")));
	IndustrialIncomeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextIndustrialIncome")));
	TouristText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextTourist")));
	BDLOG_S(Warning);
	SectorNameText->SetText(SectorName);

}



void UBDSectorHUDWidget::SetSectorName(FString Name)
{
	//BDCHECK(SectorName.Len() > 0);

	SectorName = FText::FromString(Name);

}

void UBDSectorHUDWidget::UpdateWidget(int32 CommercialIncome, int32 Range, int32 IndustrialIncome, int32 Tourist)
{
	CommercialIncomeText->SetText(FText::FromString(FString::FromInt(CommercialIncome)));
	RangeText->SetText(FText::FromString(FString::FromInt(Range)));
	IndustrialIncomeText->SetText(FText::FromString(FString::FromInt(IndustrialIncome)));
	TouristText->SetText(FText::FromString(FString::FromInt(Tourist)));

}