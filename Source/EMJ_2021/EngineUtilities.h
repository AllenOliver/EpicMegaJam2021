// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class EMJ_2021_API EngineUtilities
{
public:
	EngineUtilities();
	~EngineUtilities();

	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out);
};
