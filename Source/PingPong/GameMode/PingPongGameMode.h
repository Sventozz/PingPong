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
	APingPongGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	void PostLogin(APlayerController* NewPlayer) override;

	AActor* ChoosePlayerStart(AController* Player);
	
	bool ShouldSpawnAtStartSpot(AController* Player) { return false; }

};
