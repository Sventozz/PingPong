// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "PingPong/GameMode/PingPongGameMode.h"


APingPongPawn::APingPongPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Platform);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bReplicates = true;
}

void APingPongPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		NetUpdateFrequency = 1;

		UE_LOG(LogTemp, Warning, TEXT("Pawn Name: %s"), *GetName());
		APingPongGameMode* PingPongGameMode = GetWorld()->GetAuthGameMode<APingPongGameMode>();
		if (PingPongGameMode)
		{
			PingPongGameMode->RequestRespawn(this, GetController());
		}

	}
}

void APingPongPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APingPongPawn, ServerState);
}

void APingPongPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		FPingPongMove Move;
		Move.DeltaTime = DeltaTime;
		Move.SteeringThrow = SteeringThrow1;
		Move.Throttle = Throttle;
		//TODO: Set time

		Server_SendMove(Move);

		SimulateMove(Move);
	}


}

void APingPongPawn::OnRep_ServerState()
{
	SetActorTransform(ServerState.Tranform);
	Velocity = ServerState.Velocity;
}

void APingPongPawn::SimulateMove(FPingPongMove Move)
{
	FVector Force = GetActorForwardVector() * MaxDrivingForce * Move.Throttle;

	Force += GetAirResistance();
	Force += GetRollingResistance();

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);

	UpdateLocationFromVelocity(Move.DeltaTime);
}

FVector APingPongPawn::GetAirResistance()
{
	return - Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector APingPongPawn::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float NormalForce = Mass * AccelerationDueToGravity;
	return -Velocity.GetSafeNormal() * RollingResistanceCoefficient * NormalForce;
}

void APingPongPawn::ApplyRotation(float DeltaTime, float SteeringThrow)
{
	float DeltaLocation = FVector::DotProduct(GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * SteeringThrow;
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);

	AddActorWorldRotation(RotationDelta);
}

void APingPongPawn::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult Hit;
	AddActorWorldOffset(Translation, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

void APingPongPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APingPongPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APingPongPawn::MoveRight);

}

void APingPongPawn::MoveForward(float Value)
{
	Throttle = Value;
}

void APingPongPawn::MoveRight(float Value)
{
	SteeringThrow1 = Value;
}

void APingPongPawn::Server_SendMove_Implementation(FPingPongMove Move)
{
	SimulateMove(Move);

	ServerState.LastMove = Move;
	ServerState.Tranform = GetActorTransform();
	ServerState.Velocity = Velocity;
}

bool APingPongPawn::Server_SendMove_Validate(FPingPongMove Move)
{
	return true; //TODO: Make better validation
}