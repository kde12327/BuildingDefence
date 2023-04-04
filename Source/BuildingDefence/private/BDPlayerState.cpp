// Fill out your copyright notice in the Description page of Project Settings.


#include "BDPlayerState.h"

ABDPlayerState::ABDPlayerState()
{
	CurrentMoney = 250.0f;
	TotalIncome = 0.0f;
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
	TotalIncome += IncomeMoney;
}

int32 ABDPlayerState:: GetCurrentMoney()
{
	return static_cast<int32>(CurrentMoney);

}

int32 ABDPlayerState::GetTotalIncome()
{
	return static_cast<int32>(TotalIncome);
}

bool ABDPlayerState::HasMoney(float Money)
{
	return CurrentMoney >= Money;
}