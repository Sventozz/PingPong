// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "PingPong/Pawn/PingPongPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"



void APingPongPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

}

void APingPongPlayerController::SetupInputComponent()
{
	//Super::SetupInputComponent();

	//InputComponent->BindAxis("MoveRight", this, &APingPongPlayerController::MoveRight);

}

void APingPongPlayerController::MoveRight(float Value)
{
	//ServerMoveRight(Value);
}

void APingPongPlayerController::ServerMoveRight_Implementation(float Value)
{
	//if (Value == 0)
	//{
	//	GetPawn<APingPongPawn>()->StopMove();
	//}
	//if (Value > 0)
	//{
	//	GetPawn<APingPongPawn>()->AccelerateRight();
	//}
	//else
	//{
	//	GetPawn<APingPongPawn>()->AccelerateLeft();
	//}
}