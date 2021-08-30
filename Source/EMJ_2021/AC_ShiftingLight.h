// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "Math/Color.h"
#include "Constants.h"
#include "AC_ShiftingLight.generated.h"

#pragma region Forward Declarations
class UAC_Shift;
#pragma endregion

/**
 *
 */
UCLASS()
class EMJ_2021_API UAC_ShiftingLight : public UPointLightComponent
{
	GENERATED_BODY()

public:
	// declare light intensity variable
	UPROPERTY(VisibleAnywhere, Category = "Light Component")
		float LightIntensity;

	UPROPERTY(VisibleAnywhere, Category = "Light Component")
		FColor RedLight;

	UPROPERTY(VisibleAnywhere, Category = "Light Component")
		FColor BlueLight;

	UPROPERTY(VisibleAnywhere, Category = "Light Component")
		E_COLOR StartColor;
protected:
private:
	E_COLOR _currentColor;
};
