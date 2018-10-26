// Fill out your copyright notice in the Description page of Project Settings.

#include "InputManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"

AInputManager::AInputManager()
{
	PrimaryActorTick.bCanEverTick = true;
	posessed = false;
}

void AInputManager::BeginPlay()
{
	Super::BeginPlay();
}

void AInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInputManager::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// assaing InputEvent "release" to restart function 
	InputComponent->BindAction("Finger1", IE_Released, this, &AInputManager::Restart); // is this only called when pawn is posessed ?? 
}

void AInputManager::Restart()
{
	UE_LOG(LogTemp, Warning, TEXT("RESTART"));
	//UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName()), false);
}

