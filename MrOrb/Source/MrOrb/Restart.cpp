// Fill out your copyright notice in the Description page of Project Settings.

#include "Restart.h"
#include "PaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"

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

void ARestart::RestartLevel(APaperCharacter* player, USpringArmComponent* arm, float highestPoint)
{
	// Disable players trail mby??

	//player->SetActorLocation(startPosition);
	//arm->SetRelativeLocation(startPosition);
	//highestPoint = 0;



	// Reset points
	// Activate players trail
}

