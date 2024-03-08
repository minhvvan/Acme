// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class ACME_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyPC();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ULobbyWidget> LobbyWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	ULobbyWidget* LobbyWidget;


};
