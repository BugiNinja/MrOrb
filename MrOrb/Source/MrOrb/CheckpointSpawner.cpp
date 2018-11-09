// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckpointSpawner.h"
#include "PaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CheckpointObstacle.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ACheckpointSpawner::ACheckpointSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckpointSpawner::BeginPlay()
{
	Super::BeginPlay();
	spawned = false;
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
}

// Called every frame
void ACheckpointSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player != nullptr)
	{
		HighestPoint = GetHighestPoint();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PLAYER POINTER"));
	}


	FVector wantedPosition = FVector(0, 0, cameraBoom->GetComponentLocation().Z + (ViewportSize.Y * 2) + OffsetZ);
	SetActorLocation(wantedPosition);
	
	Distance = GetDistance(HighestPoint, DistanceBetweenSpawns);
	rDistance = FMath::RoundToInt(Distance);

	if (((rDistance % 2) == 1) && !spawned)
	{
		UE_LOG(LogTemp, Warning, TEXT("SPAWN"));
		Spawn();
	}
	else
	{
		if (((rDistance % 2) == 0) && spawned)
		{
			spawned = false;
		}
	}
}

void ACheckpointSpawner::Setup(APaperCharacter* playerPtr, UCameraComponent* cameraPtr, APlayerController* controllerPtr)
{
	player = playerPtr;
	cameraBoom = cameraPtr;
	controller = controllerPtr;
	return;
}

void ACheckpointSpawner::Spawn()
{
	spawned = true;

	//FVector Location(0.0f, 0.0f, 0.0f);
	//FRotator Rotation(0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters SpawnInfo;
	//ACheckpointObstacle* obj = GetWorld()->SpawnActor<ACheckpointObstacle>(Location, Rotation, SpawnInfo);
	//
	//UPaperSpriteComponent* SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("RootComponent"));

	SpawnLöpö();
	
}

float ACheckpointSpawner::GetDistance(float HighestPoint, float DistanceBetweenSpawns)
{
	return HighestPoint / DistanceBetweenSpawns;
}

float ACheckpointSpawner::GetHighestPoint()
{
	if (player->GetActorLocation().Z > HighestPoint)
	{
		return player->GetActorLocation().Z;
	}
	else
	{
		return HighestPoint;
	}
}

void ACheckpointSpawner::SpawnLöpö(AActor* c)
{
	/// wat
	FOutputDeviceNull ar;
	c->CallFunctionByNameWithArguments(TEXT("test"), ar, NULL, true);
}