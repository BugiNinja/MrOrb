// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedComponent.h"


// Sets default values for this component's properties
USpeedComponent::USpeedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DefaultSpeed = 1750;
	// ...
}


// Called when the game starts
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
	// ...

	
}
void USpeedComponent::AddSpeed(int amount)
{
	BaseSpeed += amount;
	UpdateCurrentSpeed();
}
void USpeedComponent::AddSpeedMult(float increasement) 
{
	SpeedMult += increasement;
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

void USpeedComponent::UpdateCurrentSpeed()
{
	CurrentSpeed = BaseSpeed * SpeedMult + BoostedSpeed;
}


// Called every frame
void USpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (boostTime > 0) {
		if (boostTime > peakTime * boostDuration) 
		{
			BoostedSpeed = boostPeak * ((1 - ((boostTime - (peakTime * boostDuration)) / (boostDuration - (peakTime * boostDuration)))));
		}
		else 
		{
			BoostedSpeed = boostPeak * (boostTime / (peakTime * boostDuration));
		}
		
		boostTime -= DeltaTime;
		UpdateCurrentSpeed();
	}
	// ...
}

