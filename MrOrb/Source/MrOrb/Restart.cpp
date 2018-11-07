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

void ARestart::RestartLevel(APaperCharacter* player, UCameraComponent* cam, USpringArmComponent* arm, FVector CameraPos, float CameraZoom)
{
	///do smooth transition from current height to start position (lerp) 
	// TODO: take ref to points and level gen and restart both

	arm->SetWorldLocation(CameraPos);
	cam->SetOrthoWidth(CameraZoom);
	player->SetActorLocation(startPosition, false, nullptr, ETeleportType::ResetPhysics);

	UE_LOG(LogTemp, Warning, TEXT("RESTART"));
}