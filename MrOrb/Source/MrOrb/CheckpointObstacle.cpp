// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointObstacle.h"
//#include "PaperSprite.h"
//#include "PaperSpriteComponent.h"

// Sets default values
ACheckpointObstacle::ACheckpointObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckpointObstacle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACheckpointObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}