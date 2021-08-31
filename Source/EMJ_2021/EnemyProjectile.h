// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableObject.h"
#include "EnemyProjectile.generated.h"

#pragma region Forward Declarations
class UAC_Shift;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API AEnemyProjectile : public APoolableObject
{
	GENERATED_BODY()
public:
	AEnemyProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Shift* Shift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_COLOR CurrentColor;

public:
	UFUNCTION(BlueprintCallable, Category = "Enemy Projectiles")
		void SetStartColor(E_COLOR _color);
};
