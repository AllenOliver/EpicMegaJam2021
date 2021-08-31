// Fill out your copyright notice in the Description page of Project Settings.

#include "Constants.h"
#include "EMJ_2021Character.h"
#include "EscapeGameMode_Base.h"

AEMJ_2021Character* UConstants::GetPlayer(UWorld* World)
{
	auto player = UGameplayStatics::GetPlayerCharacter(World, 0);
	AEMJ_2021Character* _playerReturn = Cast<AEMJ_2021Character>(player);
	if (_playerReturn)
	{
		return _playerReturn;
	}
	else
	{
		return nullptr;
	}
}

//AEscapeGameMode_Base* GetEscapeGameMode(UWorld* _world)
//{
//	if (AEscapeGameMode_Base* _escapeGameMode = Cast<AEscapeGameMode_Base>(UGameplayStatics::GetGameMode(_world)))
//		return _escapeGameMode;
//	else return nullptr;
//}