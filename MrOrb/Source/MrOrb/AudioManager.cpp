// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
//#include "Audio.h"

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UAudioComponent* AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;
	audiomanager = AudioComponent;
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::PlaySoundEffectsByMgl(FString soundName)
{
	/* BOOP */


	//audiomanager->Create2DSound();

	// spawn 2d sound
	// play it 
	// demolish self
}