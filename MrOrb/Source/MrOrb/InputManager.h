// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputManager.generated.h"

UCLASS()
class MRORB_API AInputManager : public APawn
{
	GENERATED_BODY()

public:

	AInputManager();
	bool posessed;
	FString mapName;
	UWorld* world;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UFUNCTION(BlueprintCallable)
		void Restart();

};
