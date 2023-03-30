// Fill out your copyright notice in the Description page of Project Settings.


#include "BDRightWidget.h"
#include "Components/ListView.h"
#include "Sector.h"
#include "BDSectorIncomeListItemData.h"

void UBDRightWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SectorIncomeListView = Cast<UListView>(GetWidgetFromName(TEXT("ListViewSectorIncome")));
	SectorIncomeListView->SetSelectionMode(ESelectionMode::None);

	IsWidgetVisible = false;

}

void UBDRightWidget::ShowIncomeWidget()
{
	if (!IsWidgetVisible)
	{
		PlayAnimation(ShowWidget);
		IsWidgetVisible = true;
	}
}

void UBDRightWidget::HideIncomeWidget()
{
	if (IsWidgetVisible)
	{
		PlayAnimation(HideWidget);
		IsWidgetVisible = false;
	}
}

void UBDRightWidget::UpdateIncomeWidget(TArray<class ASector*>& Sectors)
{

	TArray<UBDSectorIncomeListItemData*> ListData;

	if (Sectors.Num() != 0)
	{
		for (auto Sector : Sectors)
		{
			UBDSectorIncomeListItemData* Data = NewObject<UBDSectorIncomeListItemData>();
			Data->SectorName = Sector->GetSectorName();
			Data->Income = Sector->GetWaveIncome();
			ListData.Add(Data);
		}
		SectorIncomeListView->SetListItems(ListData);

	}

	
}