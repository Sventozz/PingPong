// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PingPongHUD.generated.h"


UCLASS()
class PINGPONG_API APingPongHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PawnOverlayClass;

	void AddPawnOverlay();


	UPROPERTY()
	class UPawnOverlay* PawnOverlay;

protected:

	virtual void BeginPlay() override;
	
};
