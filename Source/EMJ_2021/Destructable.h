// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UShiftable.h"
#include "Destructable.generated.h"

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
class UBoxComponent;
class APlayerProjectile;
class AEMJ_2021Character;
#pragma endregion

UCLASS()
class EMJ_2021_API ADestructable : public AActor, public IShiftable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestructable();

	UPROPERTY(EditAnywhere)
		UAC_Health* Health;
	UPROPERTY(EditAnywhere)
		UAC_Shift* Shift;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerBox;
	UPROPERTY(EditAnywhere)
		FVector TriggerBoxSize;
	UPROPERTY(EditAnywhere)
		bool Shiftable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void TakeHit(int Amount, E_COLOR _attackingColor);

	UFUNCTION(BlueprintCallable, Category = "Color")
		E_COLOR GetCurrentColor();

	////UFUNCTION(BlueprintCallable, Category = "Death")
	////	void Destroy();
	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDestroy();

	UFUNCTION(BlueprintCallable, Category = "Hit Event")
		void OnHit();
	UFUNCTION(BlueprintNativeEvent, Category = "Hit Event")
		void E_OnTakeHit();

	UFUNCTION(BlueprintCallable, Category = "Hit Event")
		void OnShift_Call();
	UFUNCTION(BlueprintNativeEvent, Category = "Hit Event")
		void OnShifted();

	UFUNCTION()
		void ShiftDestructable();

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
