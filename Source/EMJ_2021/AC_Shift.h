// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/FilterCollection.h"
#include "Components/ActorComponent.h"
#include "AC_Shift.generated.h"

UENUM(BlueprintType)
/* [uint8] An Enum to handle the death branch in BluePrint. */
enum class E_COLOR : uint8
{
	RED,
	BLUE
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/* [Actor Component] Handles shifting between one color and another. */
class EMJ_2021_API UAC_Shift : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_Shift();

	DECLARE_EVENT(UAC_Shift, FChangedEvent)
	FChangedEvent& OnShift() { return _changedEvent; }

	UPROPERTY(EditAnywhere)
		UMaterial* RedMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* BlueMaterial;

	UPROPERTY(EditAnywhere)
		E_COLOR StartColor;

public:

	/**
	 * Set's up the component on game start.
	 */
	void Setup();

	/**
	 * Updates values on this component if needed.
	 */
	void Update();

	UFUNCTION(BlueprintCallable, Category = "Shift Component", meta = (Keyword = "shift", ToolTip = "Shifts this actor to the other color."))
		/**
		 * Shifts this instance to a new color.
		 */
		void Shift();

	UFUNCTION(BlueprintCallable, Category = "Shift Component", meta = (Keyword = "shift", ToolTip = "Gets the object's current color."))
		/**
		 * Returns the current Color.
		 */
		E_COLOR GetCurrentColor();

	UFUNCTION(BlueprintCallable, Category = "Shift Component", meta = (Keyword = "shift", ToolTip = "Sets the object's current Material Instance."))
		/**
		 * Sets the current Material.
		 * @param _color - The E_COLOR& to set this instance to.
		 */
		void SetCurrentMaterial(E_COLOR _color);

	UFUNCTION(BlueprintCallable, Category = "Shift Component", meta = (Keyword = "shift", ToolTip = "Gets the object's current Material Instance."))
		/**
		 * Returns the current Material.
		 */
		UMaterial* GetCurrentMaterial();
private:
	/** Broadcasts whenever the layer changes */
	FChangedEvent _changedEvent;
	E_COLOR _currentColor = E_COLOR::RED;
	UMaterial* _currentMaterial;
};
