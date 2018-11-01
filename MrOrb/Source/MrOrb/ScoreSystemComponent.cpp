// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UScoreSystemComponent::UScoreSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DefaultScore = 0;
	ScoreToAdd = 10;
}


// Called when the game starts
void UScoreSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentScore = DefaultScore;
	SetScore();

	//////
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
}


// Called every frame
void UScoreSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	SetScore();
	return;
}

int UScoreSystemComponent::GetCurrentScore(){ return CurrentScore; }

int UScoreSystemComponent::GetSweetSpotComboAmount(){ return SweetSpotComboAmount; }

int UScoreSystemComponent::CalculateCombo(int combo)
{
	if (combo < 2)
	{
		return 0;
	}
	else if (combo == 2)
	{
		return 1;
	}
	else if (combo % 10 == 0)
	{
		return 3;
	}
	else if (combo % 5 == 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void UScoreSystemComponent::SetSweetSpotComboAmount(int amount)
{
	SweetSpotComboAmount = amount;
	return;
}

void UScoreSystemComponent::SetScore()
{
	DefaultScoreInString = FString::FromInt(CurrentScore);
	return;
}


