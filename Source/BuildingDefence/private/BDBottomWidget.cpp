// Fill out your copyright notice in the Description page of Project Settings.


#include "BDBottomWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UBDBottomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RerollButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnReroll")));
	if (nullptr != RerollButton)
	{
		RerollButton->OnClicked.AddDynamic(this, &UBDBottomWidget::OnRerollClicked);
	}

	BuildButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnBuild")));
	if (nullptr != BuildButton)
	{
		BuildButton->OnClicked.AddDynamic(this, &UBDBottomWidget::OnBuildClicked);
	}
	
	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnConfirm")));
	if (nullptr != ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UBDBottomWidget::OnConfirmClicked);
	}

	for (int i = 0; i < 5; i++)
	{
		RulletTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(FString(TEXT("TextRullet")) + FString::FromInt(i)))));

	}
	
	for (int i = 0; i < 5; i++)
	{
		RulletButtonArray.Add(Cast<UButton>(GetWidgetFromName(FName(FString(TEXT("BtnRullet")) + FString::FromInt(i)))));

	}

	MoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextMoney")));

	WaveText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextWave")));

	RerollCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextRerollCost")));

	BuildCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBuildCost")));
	
	IsRulletVisible = false;
}	

void UBDBottomWidget::OnRerollClicked()
{
	BDLOG_S(Warning);
	OnReroll.Broadcast();

}

void UBDBottomWidget::OnBuildClicked()
{
	BDLOG_S(Warning);
	OnBuild.Broadcast();

}

void UBDBottomWidget::OnConfirmClicked()
{
	BDLOG_S(Warning);
	OnConfirm.Broadcast();



}

void UBDBottomWidget::UpdateRullet(ASector& ClickedSector)
{
	BDLOG_S(Warning);
	
	
	
	BDLOG(Warning, TEXT("%d"), RulletTextArray.Num());

	for (int RulletIdx = 0; RulletIdx < 5; RulletIdx++)
	{
		BDCHECK(nullptr != RulletTextArray[RulletIdx]);
		BDLOG(Warning, TEXT("%d"), ClickedSector.RulletTypeArray[RulletIdx]);

		RulletTextArray[RulletIdx]->SetText(BuildingTypeString[static_cast<int32>(ClickedSector.RulletTypeArray[RulletIdx])]);
		RulletButtonArray[RulletIdx]->SetBackgroundColor(BuildingTypeColor[static_cast<int32>(ClickedSector.RulletTypeArray[RulletIdx])]);
	}

}

void UBDBottomWidget::UpdateWidgetByMoney(ASector& ClickedSector, int32 money)
{
	
	RerollCostText->SetText(FText::FromString(FString::FromInt(ClickedSector.GetNeedRerollMoney())));
	BuildCostText->SetText(FText::FromString(FString::FromInt(ClickedSector.GetNeedBuildMoney())));

}

void UBDBottomWidget::SetMoneyText(int32 Money)
{
	MoneyText->SetText(FText::FromString(FString("Money: ") + FString::FromInt(Money)));
}

void UBDBottomWidget::SetWaveText(int32 Wave)
{
	WaveText->SetText(FText::FromString(FString("Wave ") + FString::FromInt(Wave)));
}



void UBDBottomWidget::ShowBuild()
{
	if (!IsRulletVisible)
	{
		PlayAnimation(ShowWidget);
		IsRulletVisible = true;
	}
	BuildButton->SetVisibility(ESlateVisibility::Visible);
}

void UBDBottomWidget::ShowRullet()
{
	if (!IsRulletVisible)
	{
		PlayAnimation(ShowWidget);
		IsRulletVisible = true;
	}
	BuildButton->SetVisibility(ESlateVisibility::Hidden);
}

void UBDBottomWidget::HideRullet()
{
	if (IsRulletVisible)
	{
		PlayAnimation(HideWidget);
		IsRulletVisible = false;
	}
}

