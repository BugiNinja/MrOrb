// Fill out your copyright notice in the Description page of Project Settings.

#include "Restart.h"


ARestart::ARestart()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ARestart::BeginPlay()
{
	Super::BeginPlay();
	startPosition = playerStart->GetActorLocation();
}

void ARestart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARestart::RestartLevel(AActor* player, float highestPoint)
{
	// Disable players trail
	player->SetActorLocation(startPosition);
	highestPoint = 0;
	//cameraBoom->SetActorLocation(startPosition);
	// Reset points
	// Activate players trail
}

