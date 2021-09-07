// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UShiftable.h"
#include "ShiftableEnemy.generated.h"

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
class UCapsuleComponent;
class ALevelObjectCache;
class AEMJ_2021Character;
class APlayerProjectile;
struct FVector2D;
#pragma endregion

UCLASS()
class EMJ_2021_API AShiftableEnemy : public APawn, public IShiftable
{
	GENERATED_BODY()

public:
	AShiftableEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Health* Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Shift* Shift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCapsuleComponent* TriggerCapsule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D CapsuleSize;
	UPROPERTY(EditAnywhere)
		bool Shiftable;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		bool TakeHit(int Amount, E_COLOR _attackingColor);

	UFUNCTION(BlueprintCallable, Category = "Color")
		E_COLOR GetColor();
	UFUNCTION(BlueprintCallable, Category = "Enemy Health")
		int GetCurrentHealth();

#pragma region OnHit BP event and Call

	UFUNCTION(BlueprintCallable, Category = "Take Hit")
		void OnHit();
	UFUNCTION(BlueprintNativeEvent, Category = "Take Hit")
		void E_OnTakeHit();

#pragma endregion

#pragma region Death BP event and Call

	UFUNCTION(BlueprintCallable, Category = "Death")
		void Die();
	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDie();

#pragma endregion

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
private:
	void ShiftEnemy();
};
