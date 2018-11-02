// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSystem.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"
#include "ScoreSystemComponent.h"
//#include "PaperCharacter.h"
//#include "GameFramework/Controller.h"
//#include "EngineUtils.h"
//#include "UnrealMathUtility.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "ConstructorHelpers.h"


// Sets default values for this component's properties
UCoinSystem::UCoinSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCoinSystem::BeginPlay()
{
	Super::BeginPlay();

	///////////Load Assets for coins////////////
	FiftyCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Triangle.SPR_Triangle"), NULL, LOAD_None, NULL);
	FiveHundredCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Rectangle.SPR_Rectangle"), NULL, LOAD_None, NULL);
	ThousandCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Poly5.SPR_Poly5"), NULL, LOAD_None, NULL);
	FirstMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/M_Ball1.M_Ball1"), NULL, LOAD_None, NULL);
	SecondMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/M_Collectible.M_Collectible"), NULL, LOAD_None, NULL);
}


// Called every frame
void UCoinSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCoinSystem::SetObjects(APaperCharacter * player, UScoreSystemComponent* score, UPaperSpriteComponent* sprite)
{
	CurrentPlayer = player;
	CurrentScoreSystem = score;
	CurrentSprite = sprite;
	return;
}

void UCoinSystem::SetupCoin()
{
	int32 number = 5;
	if (number == FMath::RandRange(0, 5))
	{
		CoinValue = 500;
		CurrentSprite->SetSprite(FiveHundredCoinSprite);
		CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else
	{
		CoinValue = 50;
		CurrentSprite->SetSprite(FiftyCoinSprite);
		CurrentSprite->SetMaterial(0, SecondMaterial);
	}
}

void UCoinSystem::CoinChange()
{
	if (CurrentScoreSystem->GetSweetSpotComboAmount() > 4 && !ComboOn)
	{
		ComboOn = true;
		if (CoinValue == 50)
		{
			CurrentSprite->SetSprite(ThousandCoinSprite);
			CoinValue = 100;
			CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		else if (CoinValue == 500)
		{
			CurrentSprite->SetSprite(FiftyCoinSprite);
			CoinValue = 1000;
			CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		return;
	}
	else if(CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && ComboOn)
	{
		ComboOn = false;
		if (CoinValue == 100)
		{
			CurrentSprite->SetSprite(FiftyCoinSprite);
			CoinValue = 50;
			CurrentSprite->SetMaterial(0, SecondMaterial);
		}
		else if (CoinValue == 1000)
		{
			CurrentSprite->SetSprite(FiveHundredCoinSprite);
			CoinValue = 500;
			CurrentSprite->SetMaterial(0, SecondMaterial);
		}
		return;
	}
	else
	{
		return;
	}
}

void UCoinSystem::CollidedWithPlayer()
{
	CurrentScoreSystem->AddScore(CoinValue);
	CurrentSprite->SetSprite(nullptr);

}

