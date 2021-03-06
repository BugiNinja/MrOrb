// Fill out your copyright notice in the Description page of Project Settings.

#include "SpriteControllerComponent.h"
//#include "PaperSprite.h"
//#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "SpeedComponent.h"
#include "TimerManager.h"

//Debugs
//#include <EngineGlobals.h>
//#include <Runtime/Engine/Classes/Engine/Engine.h>

USpriteControllerComponent::USpriteControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefaultPlayerSize = FVector(1.25f, 1.0, 1.25f);
	HitPlayerSize = DefaultPlayerSize;

	DefaultCountdownTime = 5;  //Set timer here

	XNormalSizeAmount = 0.01f; //
	XSpeedSizeAmount = 0.01f; //  Increase and decrease player size by these on collision
	YNormalSizeAmount = 0.01f; //
	YSpeedSizeAmount = 0.005f; //

	CountdownTime = DefaultCountdownTime;
	bHasDoneFirstAnimation = false;

}

void USpriteControllerComponent::SetSpriteComponent(UPaperFlipbookComponent* sprite, USpeedComponent* speedcomponent)
{
	CurrentSpriteFlip = sprite;
	CurrentSpeedComponent = speedcomponent;
	return;
}

void USpriteControllerComponent::SetAnimationProperties(FVector vector)
{
	SpeedStage = (float)CurrentSpeedComponent->GetStage();
	HitVectorPoint = vector;
	float HitDotP = FVector::DotProduct(HitVectorPoint, CurrentSpriteFlip->GetForwardVector());
	//UE_LOG(LogTemp, Warning, TEXT("HitDotP before %f"), HitDotP);
	if (HitDotP > 1)
	{
		HitDotP = 1;
	}
	if (HitDotP < -1)
	{
		HitDotP = -1;
	}
	//UE_LOG(LogTemp, Warning, TEXT("HitDotP after %f"), HitDotP);
	//UE_LOG(LogTemp, Warning, TEXT("Cos %f"), acosf(-HitDotP));
	float HitAngle = FMath::RadiansToDegrees(acosf(-HitDotP));
	FRotator Rotation = CurrentSpriteFlip->GetComponentRotation();
	Rotation.Pitch += HitAngle;
	Rotation.Roll = 0;
	Rotation.Yaw = 0;
	//UE_LOG(LogTemp, Warning, TEXT("Hit angle %f"), HitAngle);
	//UE_LOG(LogTemp, Warning, TEXT("Rotation %f"), Rotation.Pitch);
	//CurrentSpriteFlip->SetRelativeRotation(Rotation);
	CurrentSpriteFlip->SetRelativeRotationExact(Rotation);

}

void USpriteControllerComponent::PlayAnimation()
{

	GetOwner()->GetWorldTimerManager().SetTimer(AnimationPlayingTimer, this, &USpriteControllerComponent::PlayingAnimation, 0.05f, true, 0.0f);
		
}

void USpriteControllerComponent::PlayingAnimation()
{
	if (--CountdownTime <= 0)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(AnimationPlayingTimer);

		if (!bHasDoneFirstAnimation)
		{
			bHasDoneFirstAnimation = true;
			CountdownTime = DefaultCountdownTime;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Should Start!"));
			PlayAnimation();
		}
		else
		{
			bHasDoneFirstAnimation = false;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Stopping!"));
			CountdownTime = DefaultCountdownTime;
			HitPlayerSize = DefaultPlayerSize;
			return;
		}
	}
	else if (!bHasDoneFirstAnimation)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Animating!"));
		HitPlayerSize = FVector(HitPlayerSize.X - XNormalSizeAmount - (SpeedStage * XSpeedSizeAmount), DefaultPlayerSize.Y, HitPlayerSize.Z + YNormalSizeAmount + (SpeedStage * YSpeedSizeAmount));
		CurrentSpriteFlip->SetRelativeScale3D(HitPlayerSize);
	}
	else if (bHasDoneFirstAnimation)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Returning to normal!"));
		HitPlayerSize = FVector(HitPlayerSize.X + XNormalSizeAmount + (SpeedStage * XSpeedSizeAmount), DefaultPlayerSize.Y, HitPlayerSize.Z - YNormalSizeAmount - (SpeedStage * YSpeedSizeAmount));
		CurrentSpriteFlip->SetRelativeScale3D(HitPlayerSize);
	}

}

//void USpriteControllerComponent::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}


//void USpriteControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

