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
	class UTextRenderComponent* ScoreRenderText;
	UTextRenderComponent* ScoreTransparentRenderText;
	UTextRenderComponent* ScoreAddRenderText;
	UTextRenderComponent* ScoreComboText;
	//class UMaterialParameterCollection* MaterialParameterCollectionAsset;
	//class UColorCollection
	//class UMaterialParameterCollectionInstance* inst;

	UFUNCTION(BlueprintCallable)
		void AddScore(int score);
	UFUNCTION(BlueprintCallable)
		void ResetScore();
	UFUNCTION(BlueprintCallable)
		int CalculateCombo(int combo);
	UFUNCTION(BlueprintCallable)
		int DisplayComboText();

	UFUNCTION(BlueprintCallable)
		int GetCurrentScore();
	UFUNCTION(BlueprintCallable)
		int GetSweetSpotComboAmount();
	UFUNCTION(BlueprintCallable)
		bool GetScoreHasChanged();
	UFUNCTION(BlueprintCallable)
		float GetScoreUIHeight();
	UFUNCTION(BlueprintCallable)
		int GetHighestLifetimeScore();
	UFUNCTION(BlueprintCallable)
		int GetHighestLifetimeCombo();
	UFUNCTION(BlueprintCallable)
		int GetHighestLifetimeDistance();


	UFUNCTION(BlueprintCallable) //Load Score
		int LoadScoreFromMemory();  
	UFUNCTION(BlueprintCallable) //Change score by specific amount
		void ChangeScoreInMemory(int amounttochange); 
	UFUNCTION(BlueprintCallable) // Save
		void SaveHighScoresToMemory();

	UFUNCTION(BlueprintCallable) 
		void SetLifetimeScore();
	UFUNCTION(BlueprintCallable)
		void SetSweetSpotComboAmount(int amount);
	UFUNCTION(BlueprintCallable)
		void SetScoreHasChanged(bool changed);
	UFUNCTION(BlueprintCallable)
		void SetScoreRenderText(UTextRenderComponent* render);
	UFUNCTION(BlueprintCallable)
		void SetScoreAddRenderText(UTextRenderComponent* render);
	UFUNCTION(BlueprintCallable)
		void SetComboRenderText(UTextRenderComponent* render);
	UFUNCTION(BlueprintCallable)
		void SetScoreTransparentRenderText(UTextRenderComponent* render);
	UFUNCTION(BlueprintCallable)
		void SetScoreUIHeight(float height);

	void SetScore();


protected:
	virtual void BeginPlay() override;

	FTimerHandle Timer;
	int Countdown;
	int SecureScore;
	int CurrentCombo;
	int TempScore;
	int CurrentComboText;

	float speed;
	float ScoreUIHeight;

	bool Slowing;
	bool bDoOnce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ScoreTimer;

	FString ScoreString;
	FString ComboString;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString SavedLifetimeScoreInString;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	FString DefaultScoreInString;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SweetSpotComboAmount;;

	//SAVED STATS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SavedLifetimeScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int HighestLifetimeScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int HighestLifetimeCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int HighestLifetimeDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bScoreHasChanged;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
