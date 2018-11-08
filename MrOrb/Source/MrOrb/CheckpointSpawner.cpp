// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointSpawner.h"
#include "PaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"

ACheckpointSpawner::ACheckpointSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACheckpointSpawner::BeginPlay()
{
	Super::BeginPlay();
	APaperCharacter* player = player;
	UCameraComponent* cameraBoom = cameraBoom;
	spawned = false;
}

void ACheckpointSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ViewportSize = FVector2D(GEngine->GetWorld()->GetGameViewport()->GetViewportSize);

	if (player->GetActorLocation().Z > HighestPoint)
	{
		HighestPoint = player->GetActorLocation().Z;
	}

	FVector wantedPosition = FVector(0,0, cameraBoom->GetComponentLocation().Z + (ViewportSize.Y * 2) + OffsetZ);
	SetActorLocation(wantedPosition);

	Distance = GetDistance(HighestPoint, DistanceBetweenSpawns);
	int rDistance = FMath::RoundToInt(Distance);


	if (((rDistance % 2) == 1) && !spawned)
	{
		Spawn();
	}
	else
	{
		if(((rDistance % 2) == 0) && spawned)
		{
			spawned = false;
		}
	}

}

float GetDistance(float HighestPoint, float DistanceBetweenSpawns)
{
	return HighestPoint / DistanceBetweenSpawns;
}

void Spawn()
{

}
