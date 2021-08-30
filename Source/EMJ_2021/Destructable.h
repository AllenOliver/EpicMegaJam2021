// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
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

	UFUNCTION()
		void ShiftDestructable();
};
