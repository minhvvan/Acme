// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/DeathWidget.h"
#include "Acme/AcmeCharacter.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void UDeathWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnReplay->OnClicked.AddDynamic(this, &UDeathWidget::OnReplayClicked);
	BtnExit->OnClicked.AddDynamic(this, &UDeathWidget::OnExitClicked);
}

void UDeathWidget::OnReplayClicked()
{
	auto PC = GetOwningPlayer();
	if (!PC) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	auto PlayerStart = Cast<APlayerStart>(FoundActors[0]);

	if (PlayerStart)
	{
		FVector Pos = PlayerStart->GetActorLocation();
		Pos.Z += 500;

		//PC->GetPawn()->SetActorLocation(Pos);
		PC->UnPossess();

		AAcmeCharacter* Character = GetWorld()->SpawnActor<AAcmeCharacter>(CharacterClass, Pos, FRotator::ZeroRotator);
		PC->Possess(Character);
	}

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UDeathWidget::OnExitClicked()
{
	//lobby·Î 
	

}
