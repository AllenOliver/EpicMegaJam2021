// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
