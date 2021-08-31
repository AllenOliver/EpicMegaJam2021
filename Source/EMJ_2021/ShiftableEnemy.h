// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShiftableEnemy.generated.h"

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
class ALevelObjectCache;
class AEMJ_2021Character;
#pragma endregion

UCLASS()
class EMJ_2021_API AShiftableEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShiftableEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAC_Health* Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void ShiftEnemy();

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void TakeHit(int Amount, E_COLOR _attackingColor);

	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnDie();

private:
	AEMJ_2021Character* _player;
};
