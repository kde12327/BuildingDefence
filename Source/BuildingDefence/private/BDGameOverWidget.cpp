// Fill out your copyright notice in the Description page of Project Settings.


#include "BDGameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UBDGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LastWaveText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextLastWave")));

	TotalIncomeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextTotalIncome")));

	ToMainButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnToMain")));

	if (nullptr != ToMainButton)
	{
		ToMainButton->OnClicked.AddDynamic(this, &UBDGameOverWidget::OnToMainClicked);
	}


}

void UBDGameOverWidget::SetLastWave(int32 Wave)
{
	LastWaveText->SetText(FText::FromString(FString("LastWave: ") + FString::FromInt(Wave)));

}

void UBDGameOverWidget::SetTotalIncome(int32 Income)
{
	TotalIncomeText->SetText(FText::FromString(FString("TotalIncome: ") + FString::FromInt(Income)));

}
void UBDGameOverWidget::OnToMainClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));

}
