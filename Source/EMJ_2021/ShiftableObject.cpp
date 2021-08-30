// Fill out your copyright notice in the Description page of Project Settings.

#include "ShiftableObject.h"
#include "LevelObjectCache.h"
#include "AC_Shift.h"
#include "AC_Health.h"
#include "EMJ_2021Character.h"

// Sets default values
AShiftableObject::AShiftableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_health = CreateDefaultSubobject<UAC_Health>(TEXT("Enemy Health"));
	_shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Enemy Shift"));
	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	RootComponent = _mesh;
}

// Called when the game starts or when spawned
void AShiftableObject::BeginPlay()
{
	Super::BeginPlay();

	if (_health)
		_health->Setup();
	if (_shift)
	{
		_shift->Setup();
		Shiftable = _shift->CanShift;
	}
}

// Called every frame
void AShiftableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShiftableObject::Shift()
{
	if (Shiftable)
	{
		if (_shift)
			_shift->Shift();
	}
}