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
	// Sets default values for this component's properties
	USpeedComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void UpdateCurrentSpeed();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BaseSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float SpeedMult;
	//BaseSpeed*SpeedMult
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int CurrentSpeed;
	//Default value for BaseSpeed
	UPROPERTY(EditAnywhere)
		int DefaultSpeed;
	//Add Fixed amount to BaseSpeed (CurrentSpeed = BaseSpeed*SpeedMult)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void AddSpeed(int amount);
	//Add Speed by Increasing multiplier (SpeedMult + Increasement)
	UFUNCTION(BlueprintCallable, Category = "SpeedVariable")
		void AddSpeedMult(float Increasement);
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
};
