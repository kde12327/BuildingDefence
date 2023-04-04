// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"



DECLARE_LOG_CATEGORY_EXTERN(BuildingDefence, Log, All);
#define BDLOG_CALLINFO (FString(__FUNCTION__) +  TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define BDLOG_S(Verbosity) UE_LOG(BuildingDefence, Verbosity, TEXT("%s"), *BDLOG_CALLINFO)
#define BDLOG(Verbosity, Format, ...) UE_LOG(BuildingDefence, Verbosity, TEXT("%s %s"), *BDLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define BDCHECK(Expr, ...) { if(!(Expr)) { BDLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

enum class BuildingType
{
	RESIDENCE,
	COMMERCE,
	INDUSTRY,
	TOURISM,
	END,
	NONE,
};

static const FText BuildingTypeString[] =
{ 
	FText::FromString(FString("RESIDENCE")),
	FText::FromString(FString("COMMERCE")),
	FText::FromString(FString("INDUSTRY")),
	FText::FromString(FString("TOURISM")),
	FText::FromString(FString("END")),
	FText::FromString(FString("-"))
};

static const FColor BuildingTypeColor[] =
{
	FColor::Red,
	FColor::Yellow,
	FColor::Green,
	FColor::Blue,
	FColor::Silver,
	FColor::Black,
};

static const int32 WaveTax[] =
{
	0,
	100,
	200,
	300,
	500,
	800,
	1300,
	2100,
	3400,
	5500,
	8900,
};