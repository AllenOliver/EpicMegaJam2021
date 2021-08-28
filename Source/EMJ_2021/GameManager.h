// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMJ_2021Character.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UENUM(BlueprintType)
/* [uint8] An Enum to handle the death branch in BluePrint. */
enum class E_LEVELTYPE : uint8
{
	CLEAR_ENEMIES,
	ESCAPE
};

UCLASS()
class EMJ_2021_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameManager();
	static AGameManager& instance() { static AGameManager _cache; return _cache; };

	UPROPERTY(EditAnywhere)
		int NumberOfLives;
	UPROPERTY(EditAnywhere)
		E_LEVELTYPE LevelType;
	UPROPERTY(EditAnywhere)
		AActor* PlayerStart;
	UPROPERTY(EditAnywhere)
		AEMJ_2021Character* CurrentPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	int EnemiesToClear;
	FVector* LastDeathSpot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RespawnPlayer();
	void SetupLevel();
};
