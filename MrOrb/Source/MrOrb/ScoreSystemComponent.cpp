// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSystemComponent.h"


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

int UScoreSystemComponent::GetCurrentScore()
{
	return CurrentScore;
}

void UScoreSystemComponent::SetScore()
{
	DefaultScoreInString = FString::FromInt(CurrentScore);
	return;
}


