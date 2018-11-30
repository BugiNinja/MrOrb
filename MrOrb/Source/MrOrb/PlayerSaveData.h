// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveData.generated.h"

/**
 * 
 */
UCLASS()
class MRORB_API UPlayerSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int PlayerScore;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int PlayerHighestCombo;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int PlayerLongestDistance;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int PlayerHighestScore;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPlayerSaveData();
	
};
