// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"
#include "AC_Shift.h"

AEnemyProjectile::AEnemyProjectile() 
{
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Shift Component"));
}


void AEnemyProjectile::SetStartColor(E_COLOR _color)
{
	CurrentColor = _color;
	if (Shift)
		Shift->Shift();
}