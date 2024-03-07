// Fill out your copyright notice in the Description page of Project Settings.


#include "Acme/Widget/GamePausedWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void UGamePausedWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BtnReplay->OnClicked.AddDynamic(this, &UGamePausedWidget::OnReplayClicked);
	BtnExit->OnClicked.AddDynamic(this, &UGamePausedWidget::OnExitClicked);
}

void UGamePausedWidget::OnReplayClicked()
{
	auto PC = GetOwningPlayer();
	if (!PC) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	auto PlayerStart = Cast<APlayerStart>(FoundActors[0]);

	if (PlayerStart)
	{
		GetWorld()->GetAuthGameMode()->RestartPlayerAtTransform(PC, PlayerStart->GetTransform());

		FVector Pos = PlayerStart->GetActorLocation();
		Pos.Z += 50;

		PC->GetPawn()->SetActorLocation(Pos);
	}

	PC->SetInputMode(FInputModeGameOnly());
	PC->bShowMouseCursor = false;

	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UGamePausedWidget::OnExitClicked()
{

}
