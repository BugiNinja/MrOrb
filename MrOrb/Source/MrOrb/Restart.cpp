// Fill out your copyright notice in the Description page of Project Settings.

#include "Restart.h"
#include "PaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARestart::ARestart()
{
	PrimaryActorTick.bCanEverTick = true;
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


void ARestart::RestartLevel(APaperCharacter* player, UCameraComponent* cam, USpringArmComponent* arm, float highestPoint, FVector CameraPos, float CameraZoom, float PlayerHeight, float PlayerHighestPoint)
{
	///do smooth transition from current height to start position (lerp)

	player->SetActorLocation(startPosition, false, nullptr, ETeleportType::ResetPhysics);
	arm->SetWorldLocation(CameraPos);
	cam->SetOrthoWidth(CameraZoom);

	highestPoint = player->GetActorLocation().Z;

	UE_LOG(LogTemp, Warning, TEXT("RESTART"));
}
