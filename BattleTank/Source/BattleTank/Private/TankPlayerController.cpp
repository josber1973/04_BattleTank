// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Tick
    // Super
	// AimTowardsCrossHair();

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is possesing: %s"), *(ControlledTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString());

	// Get world location if linetrace through crosshair
	// If it hits the landscape
	    // Tell Controlled Tank to aim at this point
}