// Fill out your copyright notice in the Description page of Project Settings.


#include "BDBottomWidget.h"
#include "Components/Button.h"


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