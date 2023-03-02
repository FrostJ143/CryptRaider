// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerArea.h"
#include "Mover.h"

UTriggerArea::UTriggerArea()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerArea::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor* Actor = GetAcceptableActor();
	if (Mover == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Mover null!"));
	}
	else 
	{
		if (Actor == nullptr)
		{
			Mover->SetShouldMove(false);
		}
		else 
		{
			UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
			if (Component != nullptr)
			{
				Component->SetSimulatePhysics(false);
				Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			}
			Mover->SetShouldMove(true);
		}
	}
}

AActor* UTriggerArea::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(AcceptableTagName) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerArea::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}