// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EngineUtils.h"
#include "Constants.h"

#include "EscapeGameMode_Base.generated.h"

#pragma region Forward Declarations
class AShiftableEnemy;
class ADestructable;
class UAC_Shift;
class AEMJ_2021Character;
#pragma endregion

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShift);
UCLASS()
class EMJ_2021_API AEscapeGameMode_Base : public AGameMode
{
	GENERATED_BODY()
		//Variables
public:
	UPROPERTY(EditAnywhere)
		TArray<AActor*> AdditionalShiftables;

	UPROPERTY(EditAnywhere)
		AEMJ_2021Character* _currentPlayer;

	UPROPERTY(EditAnywhere)
		bool _gameIsPlaying;

	UPROPERTY(BlueprintAssignable)
		FShift ShiftedEvent;

#pragma region Debug Console Commands

	UFUNCTION(Exec, Category = ExecFunctions)
		void Debug_Shift();
	UFUNCTION(Exec, Category = ExecFunctions)
		void Reset_Level();
	UFUNCTION(Exec, Category = ExecFunctions)
		void Shift_Player();
	UFUNCTION(Exec, Category = ExecFunctions)
		void Level_Win();
	//UFUNCTION(Exec, Category = ExecFunctions)
	//	void Level_Lose();
	//UFUNCTION(Exec, Category = ExecFunctions)
	//	void Open_Level();

#pragma endregion

protected:
private:
	TArray<AActor*> ShiftableObjectList;
	TArray<AActor*> EnemyList;
	TArray<AActor*> DestructableList;
	//AEMJ_2021Character* _currentPlayer;

	//FUNCTIONS
public:
	// === GameMode Code ===
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		virtual void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		virtual void WinGame();

	UFUNCTION(BlueprintCallable)
		void OpenLevel(UWorld* _world, FString _levelName);

	UFUNCTION(BlueprintNativeEvent, Category = "Death")
		void OnWinGame();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		virtual void RespawnPlayer();

	//=== CACHING ===
	void RemoveFromCache(AActor* _actor);

	void AddToCache(AActor* _actor);

	// == Getters ==
	UFUNCTION(BlueprintCallable, Category = "Caching")
		int GetShiftableCacheSize();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		int GetDestructableCacheSize();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		int GetEnemyCacheSize();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		AEMJ_2021Character* GetPlayerCharacter();

	// === BP functions ===
	UFUNCTION(BlueprintCallable, Category = "Caching")
		void MassShift();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		void PopulateLists();

	// == Refreshing lists ==
	UFUNCTION(BlueprintCallable, Category = "Caching")
		void RefreshEnemyList();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		void RefreshDestructableList();

	UFUNCTION(BlueprintCallable, Category = "Caching")
		void RefreshShiftableList();

protected:
private:
};
