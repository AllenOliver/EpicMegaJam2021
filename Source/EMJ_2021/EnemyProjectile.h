// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableObject.h"
#include "UShiftable.h"
#include "EnemyProjectile.generated.h"

#pragma region Forward Declarations
class UAC_Shift;
class UCapsuleComponent;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API AEnemyProjectile : public APoolableObject, public IShiftable
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
	UFUNCTION(BlueprintCallable, Category = "Enemy Projectile Color")
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

#pragma region Interface functions
	UFUNCTION(BlueprintCallable, Category = "IShiftable", meta = (Keyword = "on shift", ToolTip = "This entities shift function. Should be called in global event."))
		virtual void OnShift_Implementation() override;
	////UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IShiftable", meta = (Keyword = "color", ToolTip = "Get the objects color"))
	////	E_COLOR GetColor();
	////virtual E_COLOR GetColor_Implementation() override;
	UFUNCTION(BlueprintCallable, Category = "IShiftable", meta = (Keyword = "shiftable", ToolTip = "Get the object's Shiftable Flag"))
		virtual bool CanShift_Implementation() override; // This is the declaration of the implementation
#pragma endregion
};
