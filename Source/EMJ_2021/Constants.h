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
class UCapsuleComponent;
class UBoxComponent;
struct FVector2D;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Constants", meta = (Keyword = "reset", ToolTip = "Reset this Level"))
		/**
		 * Resets the current level.
		 * @param _world  - Current World Context.
		 * @param _object - The Calling Object [Needed by engine :(].
		 */
		static void ResetCurrentLevel(UWorld* _world, UObject* _object)
	{
		UGameplayStatics::OpenLevel(_object, FName(_world->GetName()), false);
	}

	UFUNCTION(BlueprintCallable, Category = "Game Version")
		FString GetGameVersion();

	UFUNCTION(BlueprintCallable, Category = "Constants", meta = (Keyword = "collision", ToolTip = "Sets up a capsule component"))
		/**
		 * Simplifies setting up a box component.
		 * @param Capsule     - [*] Pointer to a Capsule component.
		 * @param capsuleSize - The size you want the Capsule at runtime.
		 */
		static void SetupCapsule(UCapsuleComponent*& Capsule, FVector2D capsuleSize);

	UFUNCTION(BlueprintCallable, Category = "Constants", meta = (Keyword = "collision", ToolTip = "Sets up a box component"))
		/**
		 * Simplifies setting up a box component.
		 * @param Box     - [*] Pointer to a Box component.
		 * @param boxSize - The size you want the box at runtime.
		 */
		static void SetupBox(UBoxComponent*& Box, FVector boxSize);

	UFUNCTION(BlueprintCallable, Category = "Constants", meta = (Keyword = "color", ToolTip = "Compare color of 2 objects."))
		/**
		 * Reduces this Actor's Current Health amount.
		 * @param amount - the amount of health to remove.
		 * @param Branch - [BP] Node branches based whether they die or not from the damage.
		 */
		static bool CompareColors();
};
/*
UINTERFACE(MinimalAPI, Blueprintable)
class UShiftable : public UInterface
{
	GENERATED_BODY()
};

class EMJ_2021_API IShiftable
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IShiftable", meta = (Keyword = "on shift", ToolTip = "This entities shift function. Should be called in global event."))
		void OnShift();
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IShiftable", meta = (Keyword = "color", ToolTip = "Get the objects color"))
	//	E_COLOR GetColor();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IShiftable", meta = (Keyword = "shiftable", ToolTip = "Get the object's Shiftable Flag"))
		bool CanShift();
};
*/
#pragma region Enums

UENUM(BlueprintType)
/* [uint8] An Enum to handle the color of this object. */
enum class E_COLOR : uint8
{
	RED,
	BLUE,
	NONE
};

UENUM(BlueprintType)
/* [uint8] An Enum to handle the Winning or losing the game. */
enum class E_WIN_OR_LOSS : uint8
{
	WIN,
	LOSE
};

UENUM(BlueprintType)
/* [uint8] An Enum to handle the Winning or losing the game. */
enum class E_DEATH : uint8
{
	LIVE,
	DIE
};

UENUM(BlueprintType)
/* [uint8] An Enum to handle the matching color. */
enum class E_MATCH : uint8
{
	MATCH,
	NO_MATCH
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