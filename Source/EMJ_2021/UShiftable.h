// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UShiftable.generated.h"


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