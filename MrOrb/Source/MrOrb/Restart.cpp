// Fill out your copyright notice in the Description page of Project Settings.

#include "Restart.h"
#include "PaperCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

ARestart::ARestart()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARestart::BeginPlay()
{
	Super::BeginPlay();
	startPosition = playerStart->GetActorLocation();

	dead = false;
}

void ARestart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ARestart::RestartLevel(APaperCharacter* player, USpringArmComponent* arm, float highestPoint)
{
	// Disable players trail mby?? // do smooth transition from current height to start position (lerp)

	

	player->SetActorLocation(startPosition);
	arm->SetRelativeLocation(startPosition);
	highestPoint = 0;

	dead = false; // and stuff


	UE_LOG(LogTemp, Warning, TEXT("RESTART"));


	// Reset points
	// Activate players trail
}


bool ARestart::WaitForTouch(ETouchIndex::Type FingerIndex)
{
	if(pressed)
		UE_LOG(LogTemp, Warning, TEXT("true"));
	if(!pressed)
		UE_LOG(LogTemp, Warning, TEXT("false"));

	if (FingerIndex == ETouchIndex::Touch1)
	{
		if (ETouchType::Began)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pressed"));
			pressed = true;
			return false;
		}

		if (ETouchType::Ended && pressed == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ended"));
			pressed = false;
			return true;
		}
	}
	return false;
}


//void ARestart::EnableGameOverUI()
//{
//	if (WidgetTemplate)
//	{
//		if (!WidgetInstance) 
//		{ 
//			WidgetInstance = CreateWidget(this, WidgetTemplate);
//		}
//
//		if (!WidgetInstance->GetIsVisible())
//		{
//			WidgetInstance->AddToViewport();
//		}
//
//		/// USEFUL PARTS FOR UI WIDGETS
//
//		//WidgetInstance->RemoveFromViewport();
//		//WidgetInstance = nullptr;
//		//FInputModeGameOnly GameMode;
//		//SetInputMode(GameMode);
//		//FSlateApplication::Get().SetFocusToGameViewport();
//		//bShowMouseCursor = false;
//
//	}
//}

