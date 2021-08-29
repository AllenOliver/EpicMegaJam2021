// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelObjectCache.h"
#include "ShiftableEnemy.h"
#include "Destructable.h"
#include "AC_Shift.h"
#include "EMJ_2021Character.h"
#pragma region Built in functions

// Sets default values
ALevelObjectCache::ALevelObjectCache()
{
}

#pragma endregion

#pragma region Public functions

void ALevelObjectCache::PopulateLists()
{
	this->RefreshDestructableList();
	this->RefreshEnemyList();
	this->RefreshShiftableList();
}

void ALevelObjectCache::MassShift()
{
	auto size = GetShiftableCacheSize();
	for (int i = 0; i < size; i++)
	{
		auto shift = ShiftableObjectList[i]->FindComponentByClass<UAC_Shift>();
		if (shift)
		{
			shift->Shift();
		}
	}
}

#pragma endregion

#pragma region Adding and removing

void ALevelObjectCache::RemoveFromCache(AActor* _actor)
{
	if (_actor)
	{
		if (ADestructable* _destructable = Cast<ADestructable>(_actor))
		{
			//Do destructable stuff
			if (this->DestructableList.Contains(_actor))
			{
				this->DestructableList.Remove(_actor);
			}

			//Check for shiftable
			if (_destructable->Shiftable)
			{
				if (this->ShiftableObjectList.Contains(_actor))
				{
					//Remove from shift cache too
					this->ShiftableObjectList.Remove(_actor);
				}
			}
		}
		else if (Is(_actor, AShiftableEnemy::StaticClass()))
		{
			if (this->EnemyList.Contains(_actor))
			{
				this->EnemyList.Remove(_actor);
			}

			if (this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Remove(_actor);
			}
		}
		else if (Is(_actor, AEMJ_2021Character::StaticClass())) // Shew lord Epic, make this name an option on start up.
		{
			if (this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Remove(_actor);
			}

			if (this->_currentPlayer)
			{
				_currentPlayer = NULL;
			}
		}
		else
		{
			//Nothing
		}
	}
}

void ALevelObjectCache::AddToCache(AActor* _actor)
{
	if (_actor)
	{
		if (ADestructable* _destructable = Cast<ADestructable>(_actor))
		{
			//Do destructable stuff
			if (!this->DestructableList.Contains(_actor))
			{
				this->DestructableList.Add(_actor);
			}

			//Check for shiftable
			if (_destructable->Shiftable)
			{
				if (!this->ShiftableObjectList.Contains(_actor))
				{
					//Remove from shift cache too
					this->ShiftableObjectList.Add(_actor);
				}
			}
		}
		else if (AShiftableEnemy* _shiftableEnemy = Cast<AShiftableEnemy>(_actor))
		{
			if (!this->EnemyList.Contains(_actor))
			{
				this->EnemyList.Add(_actor);
			}

			if (!this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Add(_actor);
			}
		}
		else if (AEMJ_2021Character* _player = Cast<AEMJ_2021Character>(_actor)) // Shew lord Epic, make this name an option on start up.
		{
			if (!this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Add(_actor);
			}
			if (!this->_currentPlayer)
			{
				_currentPlayer = Cast<AEMJ_2021Character>(_actor);
			}
		}
		else
		{
			//Nothing
		}
	}
}

#pragma endregion

#pragma region Refreshing Lists

void ALevelObjectCache::RefreshEnemyList()
{
	this->EnemyList.Empty();

	TArray<AShiftableEnemy*> shiftableEnemies;
	//TArray<AShiftableEnemy*> staticColorEnemies;
	FindAllActorsOfType(GetWorld(), shiftableEnemies);
}
void ALevelObjectCache::RefreshDestructableList()
{
	this->DestructableList.Empty(); //clear it

	TArray<ADestructable*> destructables;
	FindAllActorsOfType(GetWorld(), destructables);

	for (int i = 0; i < destructables.Num(); i++)
	{
		this->DestructableList.Add(destructables[i]);
	}
}
void ALevelObjectCache::RefreshShiftableList() //Expensiveeeee
{
	//this->ShiftableObjectList.Empty(); //clear it

	//TArray<AActor*> _shiftables;
	//GetAllActorsWithComponent(GetWorld(), UAC_Shift::StaticClass(), _shiftables);

	//for (int i = 0; i < _shiftables.Num(); i++)
	//{
	//	if (_shiftables[i])
	//		this->ShiftableObjectList.Add(_shiftables[i]);
	//}
}

#pragma endregion

#pragma region Getters

int ALevelObjectCache::GetShiftableCacheSize() { return this->ShiftableObjectList.Num(); }
int ALevelObjectCache::GetDestructableCacheSize() { return this->DestructableList.Num(); }
int ALevelObjectCache::GetEnemyCacheSize() { return this->EnemyList.Num(); }

#pragma endregion