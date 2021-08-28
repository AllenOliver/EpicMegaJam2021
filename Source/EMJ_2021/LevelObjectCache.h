// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Destructable.h"
#include "EngineUtils.h"
#include "Containers/Array.h"
#include "ShiftableEnemy.h"
#include "EMJ_2021Character.h"
#include "Engine/World.h"
#include "LevelObjectCache.generated.h"

UCLASS()
class EMJ_2021_API ALevelObjectCache : public AActor
{
	GENERATED_BODY()

public:
	//Singleton
	static ALevelObjectCache& instance() { static ALevelObjectCache _cache; return _cache; };

private:
	ALevelObjectCache();
public:

	//=== CACHING ===
	void RemoveFromCache(AActor* _actor);
	void AddToCache(AActor* _actor);

	// == Getters ==
	int GetShiftableCacheSize();
	int GetDestructableCacheSize();
	int GetEnemyCacheSize();

	// == Refreshing lists ==
	void RefreshEnemyList();
	void RefreshDestructableList();
	void RefreshShiftableList();

	// === BP functions ===
	void MassShift();
	void PopulateLists();

#pragma region Template Helper functions

	template<typename T>
	void FindAllActorsOfType(UWorld* World, TArray<T*>& Out)
	{
		for (TActorIterator<T> It(World); It; ++It)
		{
			Out.Add(*It);
		}
	}

	template<typename T>
	void GetAllActorsWithComponent(UWorld* World, T* Component, TArray<AActor*>& Out)
	{
		TArray<AActor*> _allActors;
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), _allActors);

		for (int i = 0; i < _allActors.Num(); i++)
		{
			TArray<UActorComponent*> _comps;
			_allActors[i]->GetComponents(_comps);
			if (_comps.Contains(T::StaticClass()))
			{
				Out.Add(_allActors[i]);
			}
		}
	}
	template<typename T>
	bool Is(AActor* _actor, T* _type)
	{
		if (T* _possibleMatch = Cast<T>(_actor))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

#pragma endregion

private:
	TArray<AActor*> ShiftableObjectList;
	TArray<AActor*> EnemyList;
	TArray<AActor*> DestructableList;
	AEMJ_2021Character* _currentPlayer;
};
