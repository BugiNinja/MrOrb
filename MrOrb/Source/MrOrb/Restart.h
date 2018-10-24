// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
//#include "UPaperCharacter.h" find correct one
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

	UPROPERTY(EditAnywhere)
		TSubclassOf<USpringArmComponent> a;

		class USpringArmComponent* arm;


	UPROPERTY(EditAnywhere)
		TSubclassOf<UCharacterMovementComponent> c;

		class UCharacterMovementComponent* cha;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void RestartLevel(UCharacterMovementComponent* player, USpringArmComponent* arm, float highestPoint);
	
};
