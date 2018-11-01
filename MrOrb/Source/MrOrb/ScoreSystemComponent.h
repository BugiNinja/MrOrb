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
	// Sets default values for this component's properties
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

	void SetScore();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int DefaultScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString DefaultScoreInString;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int HighScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ScoreToAdd;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SweetSpotComboAmount;

	///////
	ACharacter * player;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
