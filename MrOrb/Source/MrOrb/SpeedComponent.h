// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRORB_API USpeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpeedComponent();

protected:
	int boostPeak;
	float peakTime;
	float boostDuration;
	
	virtual void BeginPlay() override;
	void UpdateCurrentSpeed();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BaseSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SpeedMult;
	//additional speed from boost
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BoostedSpeed;
	//Remaining Boost in seconds
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float boostTime;
	//BaseSpeed * SpeedMult
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentSpeed;
	//CurrentSpeed + Boost
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentBoostedSpeed;
	//Default value for BaseSpeed
	UPROPERTY(EditAnywhere)
		int DefaultSpeed;
	//Add Fixed amount to BaseSpeed (BaseSpeed + Amount)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void AddSpeed(int Amount);
	//Remove Fixed amount of BaseSpeed (BaseSpeed - Amount)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void DecreaseSpeed(int Amount);
	//Add Speed by Increasing multiplier (SpeedMult + Increasement)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void AddSpeedMult(float Increasement);
	//Remove Speed by Decreasing multiplier (SpeedMult - Increasement)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void DecreaseSpeedMult(float Decreasement);
	//Multiply Speed multiplier (SpeedMult * Persentage)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void MultSpeedMult(float Percentage);
	//Reset BaseSpeed to Default and SpeedMult to 1
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void ResetSpeed();
	//Reset BaseSpeed to Default
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void ResetBaseSpeed();
	//Reset SpeedMult to 1
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void ResetSpeedMult();
	//Reset BoostSpeed to 0
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void ResetBoost();
	//Additional speed for limited time, Intesity = fixed amount, Scale = percentage of objects speed, Duration = boost length in seconds, Peak = 0.0-1.0 when moving fastest 
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void Boost(int Intesity,float Scale, float Duration, float Peak);
};
