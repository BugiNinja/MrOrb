// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSystem.h"
#include "ScoreSystemComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

UCoinSystem::UCoinSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoinSystem::BeginPlay()
{
	Super::BeginPlay();

	//Load Assets for coins
	FiftyCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Triangle.SPR_Triangle"), NULL, LOAD_None, NULL);
	FiveHundredCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Rectangle.SPR_Rectangle"), NULL, LOAD_None, NULL);
	ThousandCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Poly5.SPR_Poly5"), NULL, LOAD_None, NULL);
	FirstMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/M_Ball1.M_Ball1"), NULL, LOAD_None, NULL);
	SecondMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/M_Collectible.M_Collectible"), NULL, LOAD_None, NULL);
}

void UCoinSystem::SetObjects(APaperCharacter * player, UScoreSystemComponent* score, UPaperSpriteComponent* sprite)
{
	//Assign properties
	CurrentPlayer = player;
	CurrentScoreSystem = score;
	CurrentSprite = sprite;
	return;
}

void UCoinSystem::SetupCoin()
{
	//Set as 50 coin or 500 coins
	int32 number = 5;
	//if (this->ComponentHasTag(TEXT("ComboCoin")))
	//{
	//	bComboCoin = true;
	//}
	if (number == FMath::RandRange(0, 5))
	{
		CoinValue = 500; // 500
		CurrentSprite->SetSprite(FiveHundredCoinSprite);
		CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else
	{
		CoinValue = 50; // 50
		CurrentSprite->SetSprite(FiftyCoinSprite);
		CurrentSprite->SetMaterial(0, SecondMaterial);
	}
}

void UCoinSystem::CollidedWithPlayer()
{
	//Player has collided with this object
	CurrentScoreSystem->AddScore(CoinValue);
	CurrentSprite->SetSprite(nullptr);

}

void UCoinSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Change coins on runtime depending on Combo
	if (CurrentScoreSystem->GetSweetSpotComboAmount() > 4 && !ComboOn)
	{
		ComboOn = true;
		if (CoinValue == 50)
		{
			CurrentSprite->SetSprite(ThousandCoinSprite);
			CoinValue = 100; // 100
			CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		else if (CoinValue == 500)
		{
			CurrentSprite->SetSprite(FiftyCoinSprite);
			CoinValue = 1000; // 1000
			CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		return;
	}
	else if (CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && ComboOn)
	{
		ComboOn = false;
		if (CoinValue == 100)
		{
			CurrentSprite->SetSprite(FiftyCoinSprite);
			CoinValue = 50; // 50
			CurrentSprite->SetMaterial(0, SecondMaterial);
		}
		else if (CoinValue == 1000)
		{
			CurrentSprite->SetSprite(FiveHundredCoinSprite);
			CoinValue = 500; // 500
			CurrentSprite->SetMaterial(0, SecondMaterial);
		}
		return;
	}
	else
	{
		return;
	}

}

