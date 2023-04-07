// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPauseWidget.h"
#include "Components/Button.h"

void UBDPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ToMainButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnToMain")));
	if (nullptr != ToMainButton)
	{
		ToMainButton->OnClicked.AddDynamic(this, &UBDPauseWidget::OnToMainClicked);
	}


	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UBDPauseWidget::OnResumeClicked);
	}

}

void UBDPauseWidget::OnToMainClicked()
{
	OnToMain.Broadcast();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));



}
void UBDPauseWidget::OnResumeClicked()
{
	OnResume.Broadcast();
}