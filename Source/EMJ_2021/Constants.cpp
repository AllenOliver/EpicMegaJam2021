// Fill out your copyright notice in the Description page of Project Settings.

#include "Constants.h"
#include "EMJ_2021Character.h"
#include "EscapeGameMode_Base.h"
#include "Math/Vector2D.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

//AEMJ_2021Character* UConstants::GetPlayer(UWorld* World)
//{
//	auto player = UGameplayStatics::GetPlayerCharacter(World, 0);
//	AEMJ_2021Character* _playerReturn = Cast<AEMJ_2021Character>(player);
//	if (_playerReturn)
//	{
//		return _playerReturn;
//	}
//	else
//	{
//		return nullptr;
//	}
//}

FString UConstants::GetGameVersion()
{
	FString proj;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		proj,
		GGameIni);
	return proj;
}
void UConstants::SetupCapsule(UCapsuleComponent*& Capsule, FVector2D capsuleSize)
{
	Capsule->InitCapsuleSize(capsuleSize.X, capsuleSize.Y);
	Capsule->SetCollisionProfileName(TEXT("Trigger"));
}

void UConstants::SetupBox(UBoxComponent*& Box, FVector boxSize)
{
	Box->SetBoxExtent(boxSize);
	Box->SetCollisionProfileName(TEXT("Trigger"));
}

bool UConstants::CompareColors()
{
	return false;
}