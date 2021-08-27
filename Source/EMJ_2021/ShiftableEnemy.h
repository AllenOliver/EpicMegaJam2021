// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "ShiftableEnemy.generated.h"

UCLASS()
class EMJ_2021_API AShiftableEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShiftableEnemy();

	UPROPERTY(EditAnywhere)
		UAC_Health* Health;
	UPROPERTY(EditAnywhere)
		UAC_Shift* Shift;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void TakeDamage(int Amount, E_COLOR _attackingColor);
};
