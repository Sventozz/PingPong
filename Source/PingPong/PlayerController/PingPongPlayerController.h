// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

UENUM(BlueprintType)
enum class EAction : uint8
{
	Left,
	Right
};

UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void SetupInputComponent() override;
	void MoveRight(float Value);

private:
	UFUNCTION(Server, Reliable)
	void ServerMoveRight(float Value);
	
};
