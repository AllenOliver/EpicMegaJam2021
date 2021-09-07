// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableObject.h"
#include "PlayerProjectile.generated.h"

#pragma region Forward Declarations
class UAC_Shift;
class UCapsuleComponent;
class UStaticMeshComponent;
struct FVector2D;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API APlayerProjectile : public APoolableObject, public IShiftable
{
	GENERATED_BODY()
public:
	APlayerProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Projectile", meta = (Keyword = "shift", ToolTip = "the Shift Component on this"))
		UAC_Shift* Shift;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Projectile", meta = (Keyword = "damage", ToolTip = "Amount of damage this does."))
		int Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Projectile", meta = (Keyword = "hit", ToolTip = "Whether this component has collided or not"))
		bool HasHit;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Player Projectile", meta = (Keyword = "color", ToolTip = "Sets the starting color of this projectile."))
		void SetStartColor(E_COLOR _color);
	UFUNCTION(BlueprintCallable, Category = "Player Projectile", meta = (Keyword = "color", ToolTip = "Gets the current color of this projectile."))
		E_COLOR GetColor();

	UFUNCTION(BlueprintCallable, Category = "Player Projectile", meta = (Keyword = "death", ToolTip = "Calls the death event."))
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
