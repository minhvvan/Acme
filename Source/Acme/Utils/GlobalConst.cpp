// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalConst.h"


const FString GlobalConst::FireElementName =	FString::Printf(TEXT("불 원소"));
const FString GlobalConst::WaterElementName =	FString::Printf(TEXT("물 원소"));
const FString GlobalConst::EarthElementName =	FString::Printf(TEXT("땅 원소"));
const FString GlobalConst::AirElementName =		FString::Printf(TEXT("공기 원소"));
const FString GlobalConst::IceElementName =		FString::Printf(TEXT("얼음 원소"));
const FString GlobalConst::ThunderElementName = FString::Printf(TEXT("번개 원소"));

const FString GlobalConst::EquipActionName =		FString::Printf(TEXT("장비하기"));
const FString GlobalConst::DismantleActionName =	FString::Printf(TEXT("해제하기"));
const FString GlobalConst::InstallActionName =		FString::Printf(TEXT("설치하기"));
const FString GlobalConst::ConsumeActionName =		FString::Printf(TEXT("소비하기"));
const FString GlobalConst::DumpActionName =			FString::Printf(TEXT("버리기"));

const FName GlobalConst::HandSocket =			FName(TEXT("Weapon_Hand_Socket"));
const FName GlobalConst::BackSocket =			FName(TEXT("Weapon_Back_Socket"));

GlobalConst::GlobalConst()
{
}

GlobalConst::~GlobalConst()
{
}
