// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSystemComponent.h"
#include "TimerManager.h"
//#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "PlayerSaveData.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

//Debugs
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

UScoreSystemComponent::UScoreSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UScoreSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentScore = 0;
	Countdown = 0;
	ScoreTimer = 0;
	TempScore = 0;
	Slowing = false;
	LoadScoreFromMemory();
	SetLifetimeScore();
}

void UScoreSystemComponent::AddScore(int score)
{
	bScoreHasChanged = true;
	SecureScore += score;

	ChangeScoreInMemory(score);
	SetLifetimeScore();
	TempScore += score;
	ScoreTimer = 1.5f;
	Countdown = SecureScore - CurrentScore;
	ScoreAddRenderText->SetText(FText::FromString("+" + FString::FromInt(TempScore)));
	/*if (Countdown <= 0)
	{
		Countdown = (score);

		if (Countdown < 10)
		{
			speed = 0.1f;
		}
		else if (Countdown < 100)
		{
			speed = 0.02f;
		}
		else if (Countdown < 500)
		{
			speed = 0.01f;
		}
		else
		{
			speed = 0.005f;
		}

		GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);
	}*/
}

void UScoreSystemComponent::ResetScore()
{
	SaveHighScoresToMemory();
	CurrentScore = 0;
	SecureScore = 0;
	SetSweetSpotComboAmount(0);
	ScoreRenderText->SetText(FText::FromString(""));
	ScoreTransparentRenderText->SetText(FText::FromString(""));
	//GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
	Countdown = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RESET"));
	SetScoreUIHeight(0.0f);
	CurrentComboText = 0;
	return;
}

//Get functions
int UScoreSystemComponent::GetCurrentScore(){ return CurrentScore; }
int UScoreSystemComponent::GetSweetSpotComboAmount(){ return SweetSpotComboAmount; }

bool UScoreSystemComponent::GetScoreHasChanged(){ return bScoreHasChanged;}

float UScoreSystemComponent::GetScoreUIHeight(){ return ScoreUIHeight; }

int UScoreSystemComponent::GetHighestLifetimeScore(){ return HighestLifetimeScore;}

int UScoreSystemComponent::GetHighestLifetimeCombo(){ return HighestLifetimeCombo; }

int UScoreSystemComponent::GetHighestLifetimeDistance(){ return HighestLifetimeDistance; }

int UScoreSystemComponent::LoadScoreFromMemory()
{
	UPlayerSaveData* LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	UPlayerSaveData* SaveGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));

	// Check if the save game file exists
	if (UGameplayStatics::DoesSaveGameExist(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex))
	{
		SavedLifetimeScore = LoadGameInstance->PlayerScore;
		HighestLifetimeScore = LoadGameInstance->PlayerHighestScore;
		HighestLifetimeCombo = LoadGameInstance->PlayerHighestCombo;
		HighestLifetimeDistance = LoadGameInstance->PlayerLongestDistance;
	}
	else // Create new save
	{
		SaveGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
		SaveGameInstance->PlayerScore = SavedLifetimeScore;
		SaveGameInstance->PlayerHighestCombo = 0;
		SaveGameInstance->PlayerHighestScore = 0;
		SaveGameInstance->PlayerLongestDistance = 0;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}


	return SavedLifetimeScore;
}

void UScoreSystemComponent::ChangeScoreInMemory(int amounttochange)
{
	UPlayerSaveData* SaveGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	UPlayerSaveData* LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	SaveGameInstance->PlayerHighestScore = HighestLifetimeScore;
	SaveGameInstance->PlayerHighestCombo = HighestLifetimeCombo;
	SaveGameInstance->PlayerLongestDistance = HighestLifetimeDistance;
	int temp = LoadGameInstance->PlayerScore;
	SaveGameInstance->PlayerScore = temp + amounttochange;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	SavedLifetimeScore = SaveGameInstance->PlayerScore;

	return;
}

void UScoreSystemComponent::SaveHighScoresToMemory()
{
	UPlayerSaveData* SaveGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	UPlayerSaveData* LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	LoadGameInstance = Cast<UPlayerSaveData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	SaveGameInstance->PlayerHighestScore = HighestLifetimeScore;
	SaveGameInstance->PlayerHighestCombo =	HighestLifetimeCombo;
	SaveGameInstance->PlayerLongestDistance = HighestLifetimeDistance;
	SaveGameInstance->PlayerScore = SavedLifetimeScore;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

	return;
}

//Set functions
void UScoreSystemComponent::SetSweetSpotComboAmount(int amount) 
{
	if (amount == 0)
	{
		CurrentComboText = 0;
	}
	SweetSpotComboAmount = amount; 
	return; 
}
void UScoreSystemComponent::SetScoreHasChanged(bool changed) { bScoreHasChanged = changed; return; }
void UScoreSystemComponent::SetScoreRenderText(UTextRenderComponent* render){ ScoreRenderText = render; }
void UScoreSystemComponent::SetScoreAddRenderText(UTextRenderComponent* render) { ScoreAddRenderText = render; }
void UScoreSystemComponent::SetComboRenderText(UTextRenderComponent * render){	ScoreComboText = render; }
void UScoreSystemComponent::SetScoreTransparentRenderText(UTextRenderComponent * render) { ScoreTransparentRenderText = render; }
void UScoreSystemComponent::SetScoreUIHeight(float height) { ScoreUIHeight = height; return; }

void UScoreSystemComponent::SetLifetimeScore() 
{ 
	LoadScoreFromMemory();
	SavedLifetimeScoreInString = FString::FromInt(SavedLifetimeScore);
}

void UScoreSystemComponent::SetScore()
{
	//if (--Countdown < 10)
	//{
	//	if (--Countdown <= -1)
	//	{
	//		if (CurrentScore != SecureScore)
	//		{
	//			GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
	//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("CLEARING TIMER and STARTING"));

	//			Countdown = (SecureScore - CurrentScore);

	//			if (Countdown < 10)
	//			{
	//				speed = 0.1f;
	//			}
	//			else if (Countdown < 100)
	//			{
	//				speed = 0.02f;
	//			}
	//			else if (Countdown < 500)
	//			{
	//				speed = 0.01f;
	//			}
	//			else
	//			{
	//				speed = 0.001f;
	//			}

	//			GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);

	//		}
	//		else
	//		{
	//			GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
	//			bScoreHasChanged = false;
	//			Slowing = false;
	//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ALL DONE!!"));
	//			return;
	//		}
	//	}
	//	else if(!Slowing)
	//	{
	//		Slowing = true;
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("SLOWING!!"));
	//		GetOwner()->GetWorldTimerManager().ClearTimer(Timer);
	//		speed = 0.1f;
	//		GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UScoreSystemComponent::SetScore, speed, true, 0.0f);
	//	}
	//}

	//	CurrentScore += 1;
		
		speed = (ScoreTimer * ScoreTimer) / (1.5f*1.5f);
		CurrentScore = FMath::FloorToInt(FMath::Lerp(SecureScore, SecureScore-Countdown,speed));
		ScoreString = FString::FromInt(CurrentScore);
		ScoreRenderText->SetText(FText::FromString(ScoreString));
		ScoreTransparentRenderText->SetText(FText::FromString(ScoreString));
		
}


//Calculate combo 
int UScoreSystemComponent::CalculateCombo(int combo)
{
	if (combo % 5 != 0)
	{
		return 0;
	}

	else if (combo % 5 == 0 && combo <= 30)
	{
		return 1;
	}

	else if (combo % 10 == 0 && combo > 30 && combo <= 50)
	{
		return 1;
	}
	else if (combo == 70)
	{
		return 1;
	}
	else if (combo % 50 && combo >= 100)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int UScoreSystemComponent::DisplayComboText()
{
	CurrentComboText += 1;
	return CurrentComboText;
}

void UScoreSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SecureScore > HighestLifetimeScore)
	{
		HighestLifetimeScore = SecureScore;
	}

	if (GetSweetSpotComboAmount() > HighestLifetimeCombo)
	{
		HighestLifetimeCombo = GetSweetSpotComboAmount();
	}

	if (GetSweetSpotComboAmount() != CurrentCombo)
	{
		CurrentCombo = SweetSpotComboAmount;
		if (CurrentCombo == 0)
		{
			ScoreComboText->SetText(FText::FromString(""));
		}
		else
		{
			ComboString = FString::FromInt(CurrentCombo);
			ScoreComboText->SetText(FText::FromString("x"+ComboString));
		}
	}
	if (ScoreTimer > 0) {
		ScoreTimer -= DeltaTime;
		if (ScoreTimer < 0) ScoreTimer = 0;
		SetScore();
	}
	else {
		TempScore = 0;
		ScoreAddRenderText->SetText(FText::FromString(""));
	}
	//if (bDoOnce && SweetSpotComboAmount < 5)
	//{
	//	inst = GetWorld()->GetParameterCollectionInstance(MaterialParameterCollectionAsset);
	//	inst->SetVectorParameterValue();
	//	bDoOnce = false;
	//}
	//if (SweetSpotComboAmount >= 5 && !bDoOnce)
	//{
	//	bDoOnce = true;
	//}

}


