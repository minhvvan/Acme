// Fill out your copyright notice in the Description page of Project Settings.


#include "Util.h"

void UUtil::DebugPrint(const FString& msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%s"), *msg));
}