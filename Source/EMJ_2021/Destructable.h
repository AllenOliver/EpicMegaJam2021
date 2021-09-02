// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
class APlayerProjectile;
class AEMJ_2021Character;
#pragma endregion

#include "Destructable.generated.h"

UCLASS()
class EMJ_2021_API ADestructable : public AActor
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

	UFUNCTION(BlueprintCallable, Category = "Death")
		void Destroy();

	UFUNCTION()
		void ShiftDestructable();

#pragma region Overlapping

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion


	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDestroy();
};
