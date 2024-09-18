// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongHUD.h"
#include "GameFramework/PlayerController.h"
#include "PawnOverlay.h"

void APingPongHUD::BeginPlay()
{
	Super::BeginPlay();

	//AddPawnOverlay();
}

void APingPongHUD::AddPawnOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && PawnOverlayClass)
	{
		PawnOverlay = CreateWidget<UPawnOverlay>(PlayerController, PawnOverlayClass);
		PawnOverlay->AddToViewport();
	}
}
