// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedComponent.h"



USpeedComponent::USpeedComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DefaultSpeed = 1750;
}


void USpeedComponent::BeginPlay()
{
	Super::BeginPlay();
	BaseSpeed = DefaultSpeed;
	SpeedMult = 1;
	boostDuration = 0;
	peakTime = 0;
	boostPeak = 0;
	boostTime = 0;
	BoostedSpeed = 0;
	UpdateCurrentSpeed();
	Stage = 1;
	StageAmount = 3;
	StageMult = 0.5;
	BoostScale = 0;
}


void USpeedComponent::AddSpeed(int amount)
{
	BaseSpeed += amount;
	UpdateCurrentSpeed();
}
void USpeedComponent::DecreaseSpeed(int amount)
{
	BaseSpeed -= amount;
	UpdateCurrentSpeed();
}
void USpeedComponent::AddSpeedMult(float increasement) 
{
	SpeedMult += increasement;
	UpdateCurrentSpeed();
}
void USpeedComponent::DecreaseSpeedMult(float decreasement)
{
	SpeedMult -= decreasement;
	UpdateCurrentSpeed();
}
void USpeedComponent::MultSpeedMult(float percentage)
{
	SpeedMult = SpeedMult * percentage;
	UpdateCurrentSpeed();
}
void USpeedComponent::ResetSpeed()
{
	BaseSpeed = DefaultSpeed;
	SpeedMult = 1;
	UpdateCurrentSpeed();
}
void USpeedComponent::ResetBaseSpeed()
{
	BaseSpeed = DefaultSpeed;
	UpdateCurrentSpeed();
}
void USpeedComponent::ResetSpeedMult()
{
	SpeedMult = 1;
	UpdateCurrentSpeed();
}
void USpeedComponent::Boost(int Intesity, float Scale, float Duration, float Peak) 
{
	boostDuration = Duration;
	boostTime = boostDuration;
	peakTime = Peak;
	peakTime = 1 - peakTime;
	boostPeak = Intesity + CurrentSpeed * Scale;
}
void USpeedComponent::ResetBoost()
{
	BoostedSpeed = 0;
	boostTime = 0;
	UpdateCurrentSpeed();
}

void USpeedComponent::UpdateCurrentSpeed()
{
	CurrentSpeed = BaseSpeed * SpeedMult * (1 + Stage * StageMult);
	CurrentBoostedSpeed = CurrentSpeed + BoostedSpeed;
}

void USpeedComponent::AddSpeedInStages(int amount) 
{
	Stage += amount;
	if (StageAmount != 0) {
		if (Stage > StageAmount)
		{
			Stage = StageAmount;
		}
	}
}

int USpeedComponent::GetStage()
{
	return Stage;
}

void USpeedComponent::SetStageSpeedAmount(float Percentage)
{
	StageMult = Percentage;
}

void USpeedComponent::SetStageAmount(int amount) 
{
	StageAmount = amount;
}

void USpeedComponent::ResetStages() 
{
	Stage = 1;
}


// Called every frame
void USpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (boostTime > 0) {
		// Increse Boosted Speed Until Peak
		if (boostTime > peakTime * boostDuration) 
		{
			BoostScale = ((1 - ((boostTime - (peakTime * boostDuration)) / (boostDuration - (peakTime * boostDuration)))));
			BoostedSpeed = boostPeak * BoostScale;
		}
		// Decrease Boosted Speed After Peak
		else 
		{
			BoostScale = (boostTime / (peakTime * boostDuration));
			BoostedSpeed = boostPeak * BoostScale;
		}
		boostTime -= DeltaTime;
		UpdateCurrentSpeed();
	}
}

