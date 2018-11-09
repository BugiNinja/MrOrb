// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSystemComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"

//Debugs
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

UScoreSystemComponent::UScoreSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ScoreToAdd = 10;
}

void UScoreSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentScore = 0;
	Countdown = 0;
}

void UScoreSystemComponent::AddScore(int score)
{
	//CurrentScore += score;
	//SetScore();
	bScoreHasChanged = true;
	SecureScore += score;
	if (Countdown <= 0)
	{
		Countdown = (score) + 1;
		if (Countdown < 100)
		{
			speed = 0.005f;
		}
		else if (Countdown < 500)
		{
			speed = 0.005f;
		}
		else 
		{
			speed = 0.005f;
		}
		GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);
	}
	else
	{
		ScoreOverFlow += (score) + 1;
	}

	//for (size_t i = 0; i < score; i++)
	//{
	//	CurrentScore += 1;
	//	SetScore();
	//}
	//return;
}

void UScoreSystemComponent::ResetScore()
{
	CurrentScore = 0;
	SecureScore = 0;
	SetSweetSpotComboAmount(0);
	ScoreRenderText->SetText(FString::FromInt(CurrentScore));
	return;
}

//Get functions
int UScoreSystemComponent::GetCurrentScore(){ return CurrentScore; }
int UScoreSystemComponent::GetSweetSpotComboAmount(){ return SweetSpotComboAmount; }

bool UScoreSystemComponent::GetScoreHasChanged(){ return bScoreHasChanged;}

//Set functions
void UScoreSystemComponent::SetSweetSpotComboAmount(int amount) {SweetSpotComboAmount = amount; return; }
void UScoreSystemComponent::SetScoreHasChanged(bool changed) { bScoreHasChanged = changed; return; }

void UScoreSystemComponent::SetScoreRenderText(UTextRenderComponent* render)
{
	ScoreRenderText = render;
}

void UScoreSystemComponent::SetScore()
{
	if (Countdown < 100)
	{
		speed = 0.005f;
	}
	else if (Countdown < 500)
	{
		speed = 0.005f;
	}
	else
	{
		speed = 0.005f;
	}

	if (ScoreOverFlow != 0)
	{
		Countdown += ScoreOverFlow;
		ScoreOverFlow = 0;
	}
	if (--Countdown <= 0)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
		bScoreHasChanged = false;
		if (CurrentScore != SecureScore) // This should not happen
		{
			CurrentScore = SecureScore;
			ScoreRenderText->SetText(FString::FromInt(CurrentScore));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("THIS SHOULD NOT HAPPEN"));
		}
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Increasing!"));
	CurrentScore += 1;
	ScoreRenderText->SetText(FString::FromInt(CurrentScore));
	//DefaultScoreInString = FString::FromInt(CurrentScore);  
} 

//Calculate combo and display text
int UScoreSystemComponent::CalculateCombo(int combo)
{
	if (combo < 5)
	{
		return 0;
	}
	else if (combo % 15 == 0)
	{
		return 3;
	}
	else if (combo % 10 == 0)
	{
		return 2;
	}
	else if (combo % 5 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


