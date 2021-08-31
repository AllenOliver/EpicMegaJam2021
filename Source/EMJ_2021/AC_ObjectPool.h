// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_ObjectPool.generated.h"

#pragma region Forward Declarations
class APoolableObject;
#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMJ_2021_API UAC_ObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_ObjectPool();
	virtual void BeginPlay() override;

	APoolableObject* GetPooledObject();

private:
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
		TSubclassOf<class APoolableObject> PooledObjectSubclass;

	UPROPERTY(EditAnywhere, Category = "ObjectPool")
		int PoolSize = 200;

	TArray<APoolableObject*> Pool;
};
