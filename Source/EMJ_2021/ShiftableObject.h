// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ShiftableObject.generated.h"

#pragma region Forward Declaration
class UAC_Health;
class UAC_Shift;
class UStaticMeshComponent;
class ALevelObjectCache;
#pragma endregion

UCLASS()
class EMJ_2021_API AShiftableObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShiftableObject();

	UPROPERTY(EditAnywhere)
		UAC_Health* _health;
	UPROPERTY(EditAnywhere)
		UAC_Shift* _shift;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* _mesh;

	bool Shiftable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shift();
	void TakeHit(int _amount);
};
