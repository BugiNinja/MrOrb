// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRORB_API UScoreSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreSystemComponent();

	UFUNCTION(BlueprintCallable)
		void AddScore(int score);
	UFUNCTION(BlueprintCallable)
		void ResetScore();
	UFUNCTION(BlueprintCallable)
		int CalculateCombo(int combo);

	UFUNCTION(BlueprintCallable)
		int GetCurrentScore();
	UFUNCTION(BlueprintCallable)
		int GetSweetSpotComboAmount();

	UFUNCTION(BlueprintCallable)
		void SetSweetSpotComboAmount(int amount);

	void SetScore(); //Debug

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString DefaultScoreInString;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) //Does nothing yet
		int HighScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ScoreToAdd;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SweetSpotComboAmount;;

public:


};
