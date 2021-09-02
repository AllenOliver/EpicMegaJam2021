// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Constants.generated.h"

#pragma region Forward Declaration
class AEMJ_2021Character;
class AEscapeGameMode_Base;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		static void ResetCurrentLevel(UWorld* _world, UObject* _object) { UGameplayStatics::OpenLevel(_object, FName(_world->GetName()), false); }

	//UFUNCTION(BlueprintCallable, Category = "Gameplay")
	//	static AEMJ_2021Character* GetPlayer(UWorld* World);
};

#pragma region Enums

UENUM(BlueprintType)
/* [uint8] An Enum to handle the color of this object. */
enum class E_COLOR : uint8
{
	RED,
	BLUE
};

UENUM(BlueprintType)
/* [uint8] An Enum to handle the Winning or losing the game. */
enum class E_WIN_OR_LOSS : uint8
{
	WIN,
	LOSE
};

#pragma endregion

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