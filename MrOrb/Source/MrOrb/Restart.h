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

	UPROPERTY(EditAnywhere)
		AActor* playerStart;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void RestartLevel(AActor* player, float highestPoint);
	
};
