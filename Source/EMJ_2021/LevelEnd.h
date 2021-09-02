// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEnd.generated.h"

#pragma region Forward Declarations
class UBoxComponent;
class AEMJ_2021Character;
#pragma endregion

UCLASS()
class EMJ_2021_API ALevelEnd : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelEnd();

	UPROPERTY(VisibleAnywhere, Category = "Trigger Box")
		UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BoxExtents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Level Ending")
		void EndLevel();
	UFUNCTION(BlueprintNativeEvent, Category = "Level Ending")
		void OnEndLevel();

#pragma region Overlapping

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion
};
