// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpriteControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRORB_API USpriteControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpriteControllerComponent();

	class UPaperFlipbookComponent* CurrentSpriteFlip;
	class USpeedComponent* CurrentSpeedComponent;

protected:

	UFUNCTION(BlueprintCallable)
		void SetSpriteComponent(UPaperFlipbookComponent * sprite, USpeedComponent* speedcomponent);

	UFUNCTION(BlueprintCallable)
		void SetAnimationSpeedStage();

	UFUNCTION(BlueprintCallable)
		void PlayAnimation();

	void PlayingAnimation();

	//virtual void BeginPlay() override;

	FTimerHandle AnimationPlayingTimer;

	FVector DefaultPlayerSize;
	FVector HitPlayerSize;

	bool bHasDoneFirstAnimation;
	float SpeedStage;
	int CountdownTime;
	int DefaultCountdownTime;

	float XNormalSizeAmount;
	float XSpeedSizeAmount;
	float YNormalSizeAmount;
	float YSpeedSizeAmount;

public:	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	
};