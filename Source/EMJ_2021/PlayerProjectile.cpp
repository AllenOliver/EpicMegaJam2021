// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"
#include "AC_Shift.h"
#include "Components/BoxComponent.h"


APlayerProjectile::APlayerProjectile()
{
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Shift Component"));
	
	//TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerProjectile::OnOverlapBegin);
	//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APlayerProjectile::OnOverlapEnd);
}


#pragma region Colors

E_COLOR APlayerProjectile::GetColor() { return this->CurrentColor; }

void APlayerProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerProjectile::SetStartColor(E_COLOR _color)
{
	CurrentColor = _color;
	if (Shift)
	{
		Shift->Setup();
		Shift->SetCurrentMaterial(_color);
	}
}
#pragma endregion


#pragma region Overlapping

void APlayerProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr
	if (OtherActor)
	{
		//if (OtherActor != this) { Destroy(); }
	}
}

void APlayerProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

#pragma endregion


#pragma region Destroy Events

void APlayerProjectile::Destroy() { OnDestroy(); }

void APlayerProjectile::OnDestroy_Implementation() {/*Defined in BP*/ }

#pragma endregion
