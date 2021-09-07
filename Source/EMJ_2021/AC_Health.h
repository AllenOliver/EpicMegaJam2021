// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/FilterCollection.h"
#include "Components/ActorComponent.h"
#include "Constants.h"
#include "AC_Health.generated.h"

#pragma region Forward Declarations

#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMJ_2021_API UAC_Health : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_Health();
	void Setup();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		/* [Float] The max amount of health for this instance. */
		int MaxHealth;

	//DECLARE_EVENT(UAC_Health, FChangedEvent)
	//FChangedEvent& OnDie() { return _changedEvent; }
	UFUNCTION(BlueprintCallable, Category = "Health Component", meta = (Keyword = "health", ToolTip = "Get Current Health"))
		/**
		 * Gets the current health value.
		 */
		int GetCurrentHealth();

#pragma region Healing
	UFUNCTION(BlueprintCallable, Category = "Health Component", meta = (Keyword = "health", ToolTip = "Heal this actor"))
		/**
		 * Heal this Actor
		 * @param amount - the amount of health to restore
		 */
		void Heal(int amount);
#pragma endregion

#pragma region Taking hits

	UFUNCTION(BlueprintCallable, Category = "Health Component", meta = (Keyword = "health", ToolTip = "Hurt this actor", ExpandEnumAsExecs = "Branch"))
		/**
		 * Reduces this Actor's Current Health amount.
		 * @param amount - the amount of health to remove.
		 * @param Branch - [BP] Node branches based whether they die or not from the damage.
		 */
		void TakeDamage(int amount, E_DEATH& Branch);

	UFUNCTION()
		/**
		 * Reduces this Actor's Current Health amount.
		 * [For use in code functions. For a BP functions, look above. ^]
		 * @param amount - the amount of health to remove.
		 * @returns True if death, False if lives.
		 */
		bool TakeHit(int amount);

#pragma endregion

protected:
	virtual void BeginPlay() override;

private:

	/* [int] The current amount of health for this instance. */
	int _currentHealth;

	//FChangedEvent _changedEvent;

	UFUNCTION()
		/**
		 * Checks to see if this thing dies.
		 * @returns True if death, False if lives.
		 */
		bool CheckForDeath(float amount);
};
