// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"
#include "AC_Shift.h"

APlayerProjectile::APlayerProjectile()
{
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Shift Component"));
}

void APlayerProjectile::SetStartColor(E_COLOR _color)
{
	CurrentColor = _color;
	if (Shift)
	{
		Shift->Setup();
		Shift->Shift();
	}
}