// Fill out your copyright notice in the Description page of Project Settings.


#include "BDCounterWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UBDCounterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("BtnStart")));
	if (nullptr != StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UBDCounterWidget::OnStartClicked);
	}

	CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextCount")));

	ShowStartButtonDelegate.BindDynamic(this, &UBDCounterWidget::ShowStartButtonStarted);
	HideStartButtonDelegate.BindDynamic(this, &UBDCounterWidget::HideStartButtonEnded);


	BindToAnimationStarted(ShowStartButton, ShowStartButtonDelegate);
	BindToAnimationFinished(HideStartButton, HideStartButtonDelegate);


	WaveStarted = false;


}


void UBDCounterWidget::OnStartClicked()
{
	BDLOG_S(Warning);

	if (WaveStarted == false)
	{

		if (UWorld* world = GetWorld())
		{
			CountLeft = 5;
			UpdateCountText();

			// UABGameInstance::CheckUObjectAlive �ݹ� �Լ���
			// ���� 1ȸ�� 5�� �ڿ�, �� �������� �� 1�ʸ��� ����ǰ� �ϴ� Ÿ�̸� ���
			world->GetTimerManager().SetTimer(
				ReadyWaveTimer,    // TimerHandle
				FTimerDelegate::CreateUObject(this, &UBDCounterWidget::OnReadyCountDown),    // FTimerDelegate (TimerManager.h Ȯ��)
				1.0f,    // Interval
				true    // �ݺ� ���� (false : 1ȸ��)
			);
		}

		PlayAnimation(HideStartButton);

		WaveStarted = true;
	}
	

}

void UBDCounterWidget::OnWaveEnd()
{
	BDLOG_S(Warning);

	PlayAnimation(ShowStartButton);

	WaveStarted = false;
}

void UBDCounterWidget::OnReadyCountDown()
{
	CountLeft--;
	UpdateCountText();
	if (CountLeft == 0) 
	{
		if (UWorld* world = GetWorld())
		{
			FTimerManager& timerManager = world->GetTimerManager();

			timerManager.ClearTimer(ReadyWaveTimer);
		}

		OnStart.Broadcast();

	}
}

void UBDCounterWidget::ShowStartButtonStarted()
{
	StartButton->SetVisibility(ESlateVisibility::Visible);
}

void UBDCounterWidget::HideStartButtonEnded()
{
	StartButton->SetVisibility(ESlateVisibility::Hidden);
}

void UBDCounterWidget::UpdateCountText()
{
	CountText->SetText(FText::FromString(FString("Time: ") + FString::FromInt(CountLeft)));
}

void UBDCounterWidget::UpdateWaveLeftText(int32 WaveLeft)
{
	CountText->SetText(FText::FromString(FString("Left: ") + FString::FromInt(WaveLeft)));
}

