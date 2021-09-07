// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UShiftable.h"
#include "PoolableObject.generated.h"

#pragma region Forward Declarations
class UStaticMeshComponent;
class UCapsuleComponent;
class UConstants;
#pragma endregion

UCLASS()
class EMJ_2021_API APoolableObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolableObject();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetLifeSpan(float InLifespan) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return ProjectileMesh; }

	void SetActive(bool InpActive);
	bool IsActive();

	/* velocity and direction for 'sparkling mode' */
	void SetVelocity(float InVelocity);
	void SetDirection(FVector InDirection);

public:
	/* actor's visual representation */
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		UCapsuleComponent* TriggerCapsule;
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		FVector2D CapsuleSize;

	UPROPERTY(EditAnywhere)
		float Lifespan = 5.0f;
	UPROPERTY(EditAnywhere)
		FTimerHandle LifespanTimer;
	UPROPERTY(EditAnywhere)
		bool Active;
	UPROPERTY(EditAnywhere)
		float Velocity = 100.0f;
	UPROPERTY(EditAnywhere)
		FVector Direction;

	void Deactivate();
};
