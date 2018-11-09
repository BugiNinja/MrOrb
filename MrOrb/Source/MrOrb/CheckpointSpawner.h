// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "CheckpointSpawner.generated.h"

UCLASS()
class MRORB_API ACheckpointSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointSpawner();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class APaperCharacter> playerPointer;
	class APaperCharacter* player;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraComponent> cameraPointer;
	class UCameraComponent* cameraBoom;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class APlayerController> playerControllerPointer;
	class APlayerController* controller;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Setup(APaperCharacter* playerPtr, UCameraComponent* cameraPtr, APlayerController* controllerPtr);

	//UFUNCTION(BlueprintCallable)
	//	void SpawnLöpö(AActor* c);

	void Spawn();
	float GetDistance(float a, float b);
	float GetHighestPoint();

	float DistanceBetweenSpawns = 5000;
	float HighestPoint = 0;
	float OffsetZ = 300;
	float Distance = 0;
	int rDistance = 0;
	FVector2D ViewportSize;
	bool spawned = false;

};