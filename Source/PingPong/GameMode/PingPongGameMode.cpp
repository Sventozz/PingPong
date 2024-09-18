// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "PingPong/PlayerController/PingPongPlayerController.h"
#include "PingPong/Pawn/PingPongPawn.h"
#include "Net/UnrealNetwork.h"



APingPongGameMode::APingPongGameMode()
{
}

void APingPongGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts1);
	Selection = PlayerStarts1.Num() - 1;
}

void APingPongGameMode::RequestRespawn(APawn* Pawn, AController* Controller)
{
	if (Pawn)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pawn Reset/Destrot - Name: %s"), *Pawn->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Found Player Starts: %d | Selection: %d"), PlayerStarts1.Num(), Selection);

		//Pawn->Reset();
		//Pawn->Destroy();

		RestartPlayerAtPlayerStart(Controller, PlayerStarts1[Selection]);
		PlayerStarts1.RemoveAt(PlayerStarts1.Num() - 1);
		Selection -= 1;


		UE_LOG(LogTemp, Warning, TEXT("Player Starts Array Num: %d | Selection: %d"), PlayerStarts1.Num(), Selection);


	}
}

void APingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (NewPlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Restart Player Controller Name: %s"), *NewPlayer->GetName());


	}

	//UE_LOG(LogTemp, Warning, TEXT("PostLogin - PC: %s"), *NewPlayer->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("PostLogin - Pawn: %s"), *NewPlayer->GetPawn());


	// Waiting Player UI !!! 

	/*APingPongPlayerController* BlasterPlayerController = Cast<APingPongPlayerController>(NewPlayer);
	APingPongPawn* Pawn = Cast<APingPongPawn>(BlasterPlayerController->GetPawn());
	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn Name: %s"), *Pawn->GetName());
		Pawn->Reset();
		Pawn->Destroy();

	}
	if (BlasterPlayerController)
	{

		UE_LOG(LogTemp, Warning, TEXT("Player Controller Name: %s"), *BlasterPlayerController->GetName());
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(BlasterPlayerController, PlayerStarts[Selection]);

	}*/


	//int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	//if (NumberOfPlayers == 2)
	//{
	//	UWorld* World = GetWorld();
	//	if (World)
	//	{
	//		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	//		{
	//		}
	//	}
	//	//UE_LOG(LogTemp, Warning, TEXT("Start Match !!!"));
	//}
}


//void APingPongGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//}

