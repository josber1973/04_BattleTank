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

	if (GetSightRayHitLocation(HitLocation)) // Has a "side-effect", is going to line trace
	{
	   
		GetControlledTank()->AimAt(HitLocation);
			
	}

	
	    // Tell Controlled Tank to aim at this point
}

// Get world location if linetrace through crosshaihair, true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//HitLocation = FVector(1.0);//Vector 1,1,1
	//Find the crosshair position (mirilla) in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	FVector LookDirection;
	// "De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		//Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	// Line-trace along that LookDirection, and see what we hit (up to max range)

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)// Line Trace Succeeds
	{
		//Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn´t succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
		
}