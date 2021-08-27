// Copyright Epic Games, Inc. All Rights Reserved.

#include "EMJ_2021GameMode.h"
#include "EMJ_2021Character.h"
#include "UObject/ConstructorHelpers.h"

AEMJ_2021GameMode::AEMJ_2021GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
