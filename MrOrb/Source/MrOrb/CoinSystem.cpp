// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinSystem.h"
#include "ScoreSystemComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

//#include "Kismet/KismetMaterialLibrary.h"
//Runtime/Engine/Classes/Kismet/

UCoinSystem::UCoinSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCoinSystem::BeginPlay()
{
	Super::BeginPlay();

	//Load Assets for coins
	//FiftyCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Triangle.SPR_Triangle"), NULL, LOAD_None, NULL);
	//FiveHundredCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Rectangle.SPR_Rectangle"), NULL, LOAD_None, NULL);
	//ThousandCoinSprite = LoadObject<UPaperSprite>(NULL, TEXT("/Game/Art/Sprites/SPR_Poly5.SPR_Poly5"), NULL, LOAD_None, NULL);
	//FirstMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/SPR_Player1.SPR_Player1"), NULL, LOAD_None, NULL);
	//SecondMaterial = LoadObject<UMaterial>(NULL, TEXT("/Game/Art/Materials/M_Collectible.M_Collectible"), NULL, LOAD_None, NULL);

	//MaterialParameterCollectionAsset->SetVectorParameterValue(ParameterName, ParameterValue);

	//ColorCollection = LoadObject<UMaterialParameterCollection>(NULL, TEXT("/Game/Art/Materials/ColorCollection.ColorCollection"), NULL, LOAD_None, NULL);
	//UMaterialParameterCollectionInstance* inst;
	//inst = GetWorld()->GetParameterCollectionInstance(MaterialParameterCollectionAsset);
	//inst->SetVectorParameterValue(tt);

}

void UCoinSystem::SetObjects(USceneComponent* thisobject, APaperCharacter * player, UScoreSystemComponent* score, UPaperSpriteComponent* sprite, UPaperSpriteComponent* glow, UBoxComponent* collider)
{
	//Assign properties
	CurrentPlayer = player;
	CurrentScoreSystem = score;
	CurrentSprite = sprite;
	ThisObject = thisobject;
	Glow = glow;
	BoxCollider = collider;
	return;
}

void UCoinSystem::SetupCoin()
{
	//Set as 50 coin or 500 coins
	int32 number = 5;

	if (ThisObject->ComponentHasTag("5ComboCoin"))
	{
		CoinValue = 1000;
		Glow->SetVisibility(false);
		CurrentSprite->SetVisibility(false);
		//CurrentSprite->ToggleVisibility();
		//Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 5;
		//CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else if (ThisObject->ComponentHasTag("10ComboCoin"))
	{
		CoinValue = 1000;
		Glow->SetVisibility(false);
		CurrentSprite->SetVisibility(false);
		//CurrentSprite->ToggleVisibility();
		//Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 10;
		//CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else if (ThisObject->ComponentHasTag("15ComboCoin"))
	{
		CoinValue = 1000;
		Glow->SetVisibility(false);
		CurrentSprite->SetVisibility(false);
		//CurrentSprite->ToggleVisibility();
		//Glow->ToggleVisibility();
		bComboCoin = true;
		ComboCoin = 15;
		//CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else if (number == FMath::RandRange(0, 5))
	{
		CoinValue = 500; // 500
		//CurrentSprite->SetSprite(FiveHundredCoinSprite);
		//CurrentSprite->SetMaterial(0, SecondMaterial);
	}
	else
	{
		CoinValue = 50; // 50
		//CurrentSprite->SetSprite(FiftyCoinSprite);
		//CurrentSprite->SetMaterial(0, SecondMaterial);
	}
}

bool UCoinSystem::CollidedWithPlayer()
{
	if (bComboCoin)
	{
		if (bCanPickUp)
		{
			CurrentScoreSystem->AddScore(CoinValue);
			Glow->SetVisibility(false);
			CurrentSprite->SetVisibility(false);
			//CurrentSprite->ToggleVisibility();
			//Glow->ToggleVisibility();
			BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			bResetNeeded = true;
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
		Glow->SetVisibility(false);
		CurrentSprite->SetVisibility(false);
		//Glow->ToggleVisibility();
		//CurrentSprite->ToggleVisibility();
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bResetNeeded = true;
		return true;
	}

}

void UCoinSystem::ResetCoin()
{
	//Glow->ToggleVisibility();
	Glow->SetVisibility(true);
	//CurrentSprite->ToggleVisibility();
	CurrentSprite->SetVisibility(true);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bResetNeeded = false;
	bCanPickUp = false;
	ComboOn = false;
	SetupCoin();
	return;
}

bool UCoinSystem::GetResetNeeded(){	return bResetNeeded;}

void UCoinSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && !ComboOn)
	{
		return;
	}

	else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 14 && ComboCoin == 15 && !ComboOn)
	{
		ComboOn = true;
		Glow->SetVisibility(true);
		CurrentSprite->SetVisibility(true);
		//CurrentSprite->ToggleVisibility();
		//CurrentSprite->SetSprite(FiveHundredCoinSprite);
		//Glow->ToggleVisibility();
		bCanPickUp = true;
		return;
	}
	else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 9 && ComboCoin == 10 && !ComboOn)
	{
		ComboOn = true;
		Glow->SetVisibility(true);
		CurrentSprite->SetVisibility(true);
		//CurrentSprite->ToggleVisibility();
		//CurrentSprite->SetSprite(FiveHundredCoinSprite);
		//Glow->ToggleVisibility();
		bCanPickUp = true;
		return;
	}
	else if (bComboCoin && CurrentScoreSystem->GetSweetSpotComboAmount() > 4 && ComboCoin == 5 && !ComboOn)
	{
		ComboOn = true;
		Glow->SetVisibility(true);
		CurrentSprite->SetVisibility(true);
		//CurrentSprite->ToggleVisibility();
		//CurrentSprite->SetSprite(FiveHundredCoinSprite);
		//Glow->ToggleVisibility();
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

		//UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), ColorCollection, "Collectible 1",Color2);

		//ColorCollection->SetVectorParameterValue(FName(TEXT("Collectible 1")), Color2);

		if (CoinValue == 50)
		{
			//CurrentSprite->SetSprite(FiftyCoinSprite);
			CoinValue = 100; // 100
			//CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		else if (CoinValue == 500)
		{
			//CurrentSprite->SetSprite(FiveHundredCoinSprite);
			CoinValue = 1000; // 1000
			//CurrentSprite->SetMaterial(0, FirstMaterial);
		}
		return;
	}
	else if (CurrentScoreSystem->GetSweetSpotComboAmount() <= 1 && ComboOn && !bComboCoin)
	{
		ComboOn = false;
		//UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), ColorCollection, "Collectible 1", Color2);
		//ColorCollection->SetVectorParameterValue(FName(TEXT("Collectible 1")), Color1);
		//if (CoinValue == 100)
		//{
		//	CurrentSprite->SetSprite(FiftyCoinSprite);
		//	CoinValue = 50; // 50
		//	CurrentSprite->SetMaterial(0, SecondMaterial);
		//}
		//else if (CoinValue == 1000)
		//{
		//	CurrentSprite->SetSprite(FiveHundredCoinSprite);
		//	CoinValue = 500; // 500
		//	CurrentSprite->SetMaterial(0, SecondMaterial);
		//}
		return;
	}
	else
	{
		return;
	}

}

