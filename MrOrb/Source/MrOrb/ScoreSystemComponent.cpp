// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSystemComponent.h"

UScoreSystemComponent::UScoreSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ScoreToAdd = 10;
}

void UScoreSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentScore = 0;
	SetScore();
}

void UScoreSystemComponent::AddScore(int score)
{
	CurrentScore += score;
	SetScore();
	return;
}

void UScoreSystemComponent::ResetScore()
{
	CurrentScore = 0;
	SetSweetSpotComboAmount(0);
	SetScore();
	return;
}

//Get functions
int UScoreSystemComponent::GetCurrentScore(){ return CurrentScore; }
int UScoreSystemComponent::GetSweetSpotComboAmount(){ return SweetSpotComboAmount; }

//Set functions
void UScoreSystemComponent::SetSweetSpotComboAmount(int amount) {SweetSpotComboAmount = amount; return; }
void UScoreSystemComponent::SetScore(){ DefaultScoreInString = FString::FromInt(CurrentScore); return; } //Debug

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


