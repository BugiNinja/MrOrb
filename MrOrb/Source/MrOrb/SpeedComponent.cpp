// Fill out your copyright notice in the Description page of Project Settings.

#include "SpeedComponent.h"


// Sets default values for this component's properties
USpeedComponent::USpeedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USpeedComponent::BeginPlay()
{
	Super::BeginPlay();
	BaseSpeed = DefaultSpeed;
	SpeedMult = 1;
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
void USpeedComponent::UpdateCurrentSpeed() 
{
	CurrentSpeed = BaseSpeed * SpeedMult;
}


// Called every frame
void USpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

