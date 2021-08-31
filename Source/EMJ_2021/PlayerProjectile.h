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
	UFUNCTION(BlueprintCallable, Category = "Player Projectiles")
		void SetStartColor(E_COLOR _color);
	
};
