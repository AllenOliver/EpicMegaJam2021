// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"
#include "AC_Shift.h"


AEnemyProjectile::AEnemyProjectile() 
{
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Shift Component"));

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlapBegin);
	StaticMesh->OnComponentEndOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlapEnd);
}

E_COLOR AEnemyProjectile::GetColor() { return this->CurrentColor; }

void AEnemyProjectile::Destroy() { OnDestroy(); }

void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor != this) { Destroy(); }
	}
}

void AEnemyProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemyProjectile::OnDestroy_Implementation() { /*Defined in BP!*/ }

void AEnemyProjectile::SetStartColor(E_COLOR _color)
{
	CurrentColor = _color;
	if (Shift)
		Shift->Shift();
}