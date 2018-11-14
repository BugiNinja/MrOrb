// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Restart.generated.h"

UCLASS()
class MRORB_API ARestart : public AActor
{
	GENERATED_BODY()
	
public:	
	ARestart();

	UPROPERTY(EditAnywhere, Category = "Location")
		FVector startPosition;

	UPROPERTY(EditAnywhere, Category = "Location")
		AActor* playerStart;

	UPROPERTY(EditAnywhere, Category = "Player")
		TSubclassOf<class USpringArmComponent> CameraBoom;
		class USpringArmComponent* arm;

	UPROPERTY(EditAnywhere, Category = "Player")
		TSubclassOf<class APaperCharacter> Paper2D;
		class APaperCharacter* player;

	UPROPERTY(EditAnywhere, Category = "Player")
		TSubclassOf<class UCameraComponent> Camera;
		class UCameraComponent* cam;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void RestartLevel(APaperCharacter* player, UCameraComponent* cam, USpringArmComponent* arm, FVector CameraPos, float CameraZoom, float& HighestPoint, float& PlayerHeight);

	UFUNCTION(BlueprintCallable)
		void Continue();
};
