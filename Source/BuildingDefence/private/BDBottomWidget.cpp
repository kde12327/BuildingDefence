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

	for (int i = 0; i < 5; i++)
	{
		RulletTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(FString(TEXT("TextRullet")) + FString::FromInt(i)))));

	}

	//RulletText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextRullet0")));
	//BDCHECK(nullptr != RulletText);
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

void UBDBottomWidget::UpdateRullet(ASector& ClickedSector)
{
	BDLOG_S(Warning);
	//TODO
	//BDCHECK(nullptr != RulletText);
	//RulletText->SetText(FText::FromString(FString::FromInt(1)));
	BDLOG(Warning, TEXT("%d"), RulletTextArray.Num());

	for (int i = 0; i < 5; i++)
	{
		BDCHECK(nullptr != RulletTextArray[i]);
		BDLOG(Warning, TEXT("%d"), ClickedSector.RulletTypeArray[i]);

		RulletTextArray[i]->SetText(BuildingTypeString[static_cast<int32>(ClickedSector.RulletTypeArray[i])]);
	}

}