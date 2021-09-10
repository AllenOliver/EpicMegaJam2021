// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Containers/Array.h"
#include "Encryption.generated.h"

struct FPythagoreanTriangle;

/**
 *
 */
UCLASS()
class ATLANTIS_API UEncryption : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	FString Alphabet;

private:
	int p = 5;
	int q = 3;
	FString _inText;
	FString _encryptedText;
	TArray<FPythagoreanTriangle> _Triples;
	TArray<FPythagoreanTriangle> _Key;

public:

	UFUNCTION()
		void Encrypt();
};
