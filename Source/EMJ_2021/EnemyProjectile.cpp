// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"
#include "Components/CapsuleComponent.h"
#include "AC_Shift.h"

AEnemyProjectile::AEnemyProjectile()
{
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Shift Component"));
}

void AEnemyProjectile::SetStartColor(E_COLOR _color)
{
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlapEnd);

	if (Shift)
	{
		Shift->Setup();
		Shift->SetCurrentMaterial(_color);
	}
}
E_COLOR AEnemyProjectile::GetColor() { return this->CurrentColor; }

#pragma region Destroy Events
void AEnemyProjectile::Destroy() { OnDestroy(); }

void AEnemyProjectile::OnDestroy_Implementation() { /*Defined in BP!*/ }
#pragma endregion

#pragma region Overlaps
void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor != this) { OnDestroy(); }
	}
}

void AEnemyProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
#pragma endregion

#pragma region Interface Functions

void AEnemyProjectile::OnShift_Implementation() { if (Shift) { if (Shift->CanShift) { Shift->Shift(); } } }

bool AEnemyProjectile::CanShift_Implementation() { return Shift->CanShift; }

#pragma endregion