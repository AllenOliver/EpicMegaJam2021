// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableObject.h"
#include "PlayerProjectile.generated.h"

#pragma region Forward Declarations
class UAC_Shift;
#pragma endregion

/**
 * 
 */
UCLASS()
class EMJ_2021_API APlayerProjectile : public APoolableObject
{
	GENERATED_BODY()
public:
	APlayerProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Shift* Shift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_COLOR CurrentColor;

public:
	virtual void Tick(float DeltaSeconds) override;


	UFUNCTION(BlueprintCallable, Category = "Player Projectiles")
		void SetStartColor(E_COLOR _color);	
	UFUNCTION(BlueprintCallable, Category = "Player Projectiles")
		E_COLOR GetColor();

	UFUNCTION(BlueprintCallable, Category = "Death")
		void Destroy();
	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDestroy();

#pragma region Overlapping

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion
	
};
