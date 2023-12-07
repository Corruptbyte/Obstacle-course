// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

     FString Name = GetName();

	 UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);

	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f "), MoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	
	AddActorLocalRotation( RotationVelocity * DeltaTime);
	
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);


}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
	 
	SetActorLocation(CurrentLocation);
	 
     float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
	 
	 if (DistanceMoved > MoveDistance)
	 {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	 }
}