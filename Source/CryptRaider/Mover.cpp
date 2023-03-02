// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	
	UE_LOG(LogTemp, Display, TEXT("%s"), *Owner->GetActorNameOrLabel());
	
	OriginLocation = Owner->GetActorLocation();
	

	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bShouldMoving)
	{
		TargetLocation = OriginLocation + MovingOffset;
		Moving(DeltaTime, TargetLocation);
	}
	else 
	{
		TargetLocation = OriginLocation;
		Moving(DeltaTime, TargetLocation);
	}

	
	
	// ...
}

void UMover::Moving(float DeltaTime, FVector Target)
{
	FVector CurrentLocation = Owner->GetActorLocation();
	
	float Speed = MovingOffset.Length() / 4;
	
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	
	Owner->SetActorLocation(NewLocation);

}

void UMover::SetShouldMove(bool bNewShouldMoving)
{
	bShouldMoving = bNewShouldMoving;
}

