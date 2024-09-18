// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameMode.generated.h"


UCLASS()
class PINGPONG_API APingPongGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APingPongGameMode();

	virtual void BeginPlay() override;

	void RequestRespawn(APawn* Pawn, AController* Controller);

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;



	TArray<AActor*> PlayerStarts1;
	int32 Selection;
};
