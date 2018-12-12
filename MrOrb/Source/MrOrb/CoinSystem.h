// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRORB_API UCoinSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCoinSystem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CoinValue;

	bool ComboOn;
	bool bComboCoin;
	bool bResetNeeded;
	bool bCanPickUp;

	int ComboCoin;

	class UPaperSpriteComponent* CurrentSprite;
	UPaperSpriteComponent* Glow;
	class APaperCharacter* CurrentPlayer;
	class UScoreSystemComponent* CurrentScoreSystem;
	class USceneComponent* ThisObject;

	class UPaperSprite* FiftyCoinSprite;
	UPaperSprite* FiveHundredCoinSprite;
	UPaperSprite* ThousandCoinSprite;

	//UMaterial* FirstMaterial;
	//UMaterial* SecondMaterial;

	class UBoxComponent* BoxCollider;

	UFUNCTION(BlueprintCallable)
		void SetObjects(USceneComponent* thisobject, APaperCharacter* player, UScoreSystemComponent* score, UPaperSpriteComponent* sprite, UPaperSpriteComponent* glow, UBoxComponent* collider);

	UFUNCTION(BlueprintCallable)
		void SetupCoin();

	UFUNCTION(BlueprintCallable)
		bool CollidedWithPlayer();

	UFUNCTION(BlueprintCallable)
		void ResetCoin();

	UFUNCTION(BlueprintCallable)
		bool GetResetNeeded();
public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
