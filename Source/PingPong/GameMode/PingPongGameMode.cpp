// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "PingPong/PlayerController/PingPongPlayerController.h"
#include "PingPong/Pawn/PingPongPawn.h"
#include "Net/UnrealNetwork.h"
#include "PingPong/HUD/PingPongHUD.h"
#include "PingPong/PlayerState/PingPongPlayerState.h"
#include "PingPong/PlayerStart/PingPongPlayerStart.h"
#include "Engine/World.h"
#include "EngineUtils.h"

APingPongGameMode::APingPongGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Pawn/BP_PingPongPawn"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = APingPongHUD::StaticClass();

	PlayerControllerClass = APingPongPlayerController::StaticClass();

	PlayerStateClass = APingPongPlayerState::StaticClass();

}

void APingPongGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void APingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Post Login - Controller Name: %s"), *NewPlayer->GetName());
		
		APingPongPlayerState* PS = Cast<APingPongPlayerState>(NewPlayer->PlayerState);

		if (PS && GameState)
		{
			uint8 NumTeamA = 0;
			uint8 NumTeamB = 0;
			for (APlayerState* It : GameState->PlayerArray)
			{
				APingPongPlayerState* OtherPS = Cast<APingPongPlayerState>(It);
				if (OtherPS)
				{
					if (OtherPS->bTeamB)
					{
						++NumTeamB;
						UE_LOG(LogTemp, Warning, TEXT("Team B: %d"), NumTeamB);

					}
					else
					{
						++NumTeamA;
						UE_LOG(LogTemp, Warning, TEXT("Team A: %d"), NumTeamA);

					}
				}
			}
			if (NumTeamA > NumTeamB)
			{
				PS->bTeamB = true;
			}
		}
	}
}

AActor* APingPongGameMode::ChoosePlayerStart(AController* Player)
{
	if (Player)
	{
		APingPongPlayerState* PS = Cast<APingPongPlayerState>(Player->PlayerState);
		if (PS)
		{
			TArray<APingPongPlayerStart*> Starts;
			for (TActorIterator<APingPongPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->bTeamB == PS->bTeamB)
				{
					Starts.Add(*StartItr);
				}
			}

			 auto PlayerStart =  Starts[FMath::RandRange(0, Starts.Num() - 1)];
			UE_LOG(LogTemp, Warning, TEXT("ChoosePlayerStart: %s"), *PlayerStart->GetName());
			return PlayerStart;
		}
	}

	return NULL;
}
