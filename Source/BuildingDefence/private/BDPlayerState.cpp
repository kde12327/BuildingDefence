// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerState.h"

ABDPlayerState::ABDPlayerState()
{
	CurrentMoney = 100.0f;
}

float ABDPlayerState::GetCurrentMoney() const
{
	return CurrentMoney;
}

bool ABDPlayerState::UseMoney(float Cost)
{
	if (CurrentMoney - Cost >= 0) {
		CurrentMoney -= Cost;
		return true;
	}
	else
	{
		return false;
	}
}

void ABDPlayerState::AddMoney(float IncomeMoney)
{
	CurrentMoney += IncomeMoney;

}