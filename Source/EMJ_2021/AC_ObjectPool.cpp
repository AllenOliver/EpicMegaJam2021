// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_ObjectPool.h"
#include "PoolableObject.h"

UAC_ObjectPool::UAC_ObjectPool()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAC_ObjectPool::BeginPlay()
{
	if (PooledObjectSubclass != NULL)
	{
		/* Check for a valid World */
		UWorld* const World = GetWorld();
		if (World) {
			/* Spawn objects, make them 'inactive' and add them to pool */
			for (int i = 0; i < PoolSize; i++) {
				APoolableObject* PoolableObject = World->SpawnActor<APoolableObject>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableObject->SetActive(false);
				Pool.Add(PoolableObject);
			}
		}
	}
	Super::BeginPlay();
}

APoolableObject* UAC_ObjectPool::GetPooledObject()
{
	for (APoolableObject* PoolableObject : Pool)
	{
		if (!PoolableObject->IsActive()) {
			return PoolableObject;
		}
	}
	/* pool is drained, no inactive objects found */
	return nullptr;
}