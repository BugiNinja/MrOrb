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
	Slowing = false;
}

void UScoreSystemComponent::AddScore(int score)
{
	//CurrentScore += score;
	//SetScore();
	bScoreHasChanged = true;
	SecureScore += score;
	if (Countdown <= 0)
	{
		Countdown = (score);

		if (Countdown < 10)
		{
			speed = 0.1f;
		}
		else if (Countdown < 100)
		{
			speed = 0.02f;
		}
		else if (Countdown < 500)
		{
			speed = 0.01f;
		}
		else
		{
			speed = 0.005f;
		}

		GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);
	}
	//else
	//{
	//	ScoreOverFlow += (score);
	//}
}

void UScoreSystemComponent::ResetScore()
{
	CurrentScore = 0;
	SecureScore = 0;
	SetSweetSpotComboAmount(0);
	ScoreRenderText->SetText(FString::FromInt(CurrentScore));
	GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
	Countdown = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RESET"));
	SetScoreUIHeight(0.0f);
	return;
}

//Get functions
int UScoreSystemComponent::GetCurrentScore(){ return CurrentScore; }
int UScoreSystemComponent::GetSweetSpotComboAmount(){ return SweetSpotComboAmount; }

bool UScoreSystemComponent::GetScoreHasChanged(){ return bScoreHasChanged;}

float UScoreSystemComponent::GetScoreUIHeight(){ return ScoreUIHeight; }

//Set functions
void UScoreSystemComponent::SetSweetSpotComboAmount(int amount) {SweetSpotComboAmount = amount; return; }
void UScoreSystemComponent::SetScoreHasChanged(bool changed) { bScoreHasChanged = changed; return; }

void UScoreSystemComponent::SetScoreRenderText(UTextRenderComponent* render)
{
	ScoreRenderText = render;
}

void UScoreSystemComponent::SetScoreUIHeight(float height) { ScoreUIHeight = height; return; }

void UScoreSystemComponent::SetScore()
{
	if (--Countdown < 10)
	{
		if (--Countdown <= -1)
		{
			if (CurrentScore != SecureScore)
			{
				GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("CLEARING TIMER and STARTING"));

				Countdown = (SecureScore - CurrentScore);

				if (Countdown < 10)
				{
					speed = 0.1f;
				}
				else if (Countdown < 100)
				{
					speed = 0.02f;
				}
				else if (Countdown < 500)
				{
					speed = 0.01f;
				}
				else
				{
					speed = 0.005f;
				}

				GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);

			}
			else
			{
				GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
				bScoreHasChanged = false;
				Slowing = false;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ALL DONE!!"));
				return;
			}
		}
		else if(!Slowing)
		{
			Slowing = true;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("SLOWING!!"));
			GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
			speed = 0.1f;
			GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);
		}
	}

		CurrentScore += 1;
		ScoreRenderText->SetText(FString::FromInt(CurrentScore));
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


