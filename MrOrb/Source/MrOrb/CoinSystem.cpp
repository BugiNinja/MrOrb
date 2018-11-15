// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSystem.h"
#include "ScoreSystemComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

//Debugs
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

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

void UCoinSystem::SetObjects(USceneComponent* thisobject, APaperCharacter * player, UScoreSystemComponent* score, UPaperSpriteComponent* sprite, UPaperSpriteComponent* glow)
{
	//Assign properties
	CurrentPlayer = player;
	CurrentScoreSystem = score;
	CurrentSprite = sprite;
	ThisObject = thisobject;
	Glow = glow;
	return;
}

void UCoinSystem::SetupCoin()
{
	//Set as 50 coin or 500 coins
	int32 number = 5;

	if (ThisObject->ComponentHasTag("5ComboCoin"))
	{
		CoinValue = 500; // 500
		CurrentSprite->SetSprite(nullptr);
		Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 5;
		CurrentSprite->SetMaterial(0, FirstMaterial);
	}
	else if (ThisObject->ComponentHasTag("10ComboCoin"))
	{
		CoinValue = 500; // 500
		CurrentSprite->SetSprite(nullptr);
		Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 10;
		CurrentSprite->SetMaterial(0, FirstMaterial);
	}
	else if (ThisObject->ComponentHasTag("15ComboCoin"))
	{
		CoinValue = 500; // 500
		CurrentSprite->SetSprite(nullptr);
		Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 15;
		CurrentSprite->SetMaterial(0, FirstMaterial);
	}
	else if (number == FMath::RandRange(0, 5))
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

bool UCoinSystem::CollidedWithPlayer()
{
	if (bComboCoin)
	{
		if (bCanPickUp)
		{
			CurrentScoreSystem->AddScore(CoinValue);
			CurrentSprite->SetSprite(nullptr);
			return true;
		}
		else
		{
			return false;;
		}
	}
	else
	{
		//Player has collided with this object
		CurrentScoreSystem->AddScore(CoinValue);
		CurrentSprite->SetSprite(nullptr);
		return true;
	}

}

void UCoinSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 14 && ComboCoin == 15 && !ComboOn)
	{
		ComboOn = true;
		ThisObject->SetVisibility(true);
		CurrentSprite->SetSprite(FiveHundredCoinSprite);
		Glow->ToggleVisibility();
		bCanPickUp = true;
		return;
	}
	else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 9 && ComboCoin == 10 && !ComboOn)
	{
		ComboOn = true;
		ThisObject->SetVisibility(true);
		CurrentSprite->SetSprite(FiveHundredCoinSprite);
		Glow->ToggleVisibility();
		bCanPickUp = true;
		return;
	}
	else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 4 && ComboCoin == 5 && !ComboOn)
	{
		ComboOn = true;
		ThisObject->SetVisibility(true);
		CurrentSprite->SetSprite(FiveHundredCoinSprite);
		Glow->ToggleVisibility();
		bCanPickUp = true;
		return;
	}
	//else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && ComboOn)
	//{
	//	ComboOn = false;
	//	CurrentSprite->SetSprite(nullptr);
	//	Glow->ToggleVisibility();
	//	bCanPickUp = false;
	//	return;
	//}

	//Change coins on runtime depending on Combo
	else if (CurrentScoreSystem->GetSweetSpotComboAmount() > 4 && !ComboOn && !bComboCoin)
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
	//else if (CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && ComboOn && !bComboCoin)
	//{
	//	ComboOn = false;
	//	if (CoinValue == 100)
	//	{
	//		CurrentSprite->SetSprite(FiftyCoinSprite);
	//		CoinValue = 50; // 50
	//		CurrentSprite->SetMaterial(0, SecondMaterial);
	//	}
	//	else if (CoinValue == 1000)
	//	{
	//		CurrentSprite->SetSprite(FiveHundredCoinSprite);
	//		CoinValue = 500; // 500
	//		CurrentSprite->SetMaterial(0, SecondMaterial);
	//	}
	//	return;
	//}
	else
	{
		return;
	}

}

