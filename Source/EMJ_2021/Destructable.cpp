// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructable.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "EMJ_2021Character.h"
#include "Components/StaticMeshComponent.h"
#include "EscapeGameMode_Base.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Sets default values
ADestructable::ADestructable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UAC_Health>(TEXT("Destrustable Health"));
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Destructable Shift"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ADestructable::BeginPlay()
{
	Super::BeginPlay();

	if (Health)
		Health->Setup();
	if (Shift)
	{
		Shift->Setup();
		Shiftable = Shift->CanShift;
	}

	AEscapeGameMode_Base* gameMode = Cast<AEscapeGameMode_Base>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		gameMode->ShiftedEvent.AddDynamic(this, &ADestructable::ShiftDestructable);
	}
}

// Called every frame
void ADestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestructable::TakeHit(int Amount, E_COLOR _attackingColor)
{
	if (Shift && Health)
	{
		if (_attackingColor == Shift->GetCurrentColor()) 
		{
			if (Health->TakeHit(Amount)) 
			{
				Destroy();
			}
		}
			
	}
}

E_COLOR ADestructable::GetCurrentColor()
{
	if (Shift) 
		return Shift->GetCurrentColor();
	else 
		return E_COLOR();
}
// Called every frame
void ADestructable::ShiftDestructable()
{
	if (Shift)
	{
		if (Shiftable)
		{
			Shift->Shift();
		}
	}
}

void ADestructable::Destroy() { OnDestroy(); }

void ADestructable::OnDestroy_Implementation()
{
	//ALevelObjectCache::instance.AddToCache(this);
}