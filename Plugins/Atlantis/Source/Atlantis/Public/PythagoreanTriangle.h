// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "PythagoreanTriangle.generated.h"

/**
 *
 */
USTRUCT()
struct FPythagoreanTriangle
{
	GENERATED_BODY()

		UPROPERTY()
		float A;
	UPROPERTY()
		float B;
	UPROPERTY()
		float C;

	FPythagoreanTriangle()
	{
		A = 0;
		B = 0;
		C = 0;
	}
	/*
	* Sets
	*/
	void SetTriangleValues(float _a, float _b, float _c)
	{
		A = _a;
		B = _b;
		C = _c;
	}

	void SetA(float _a) { A = _a; }

	void SetB(float _b) { B = _b; }

	void SetC(float _c) { C = _c; }

	float GetHypotenuse() { return FMath::Sqrt(FMath::Pow(A, 2) + FMath::Pow(B, 2)); }
};
