// Fill out your copyright notice in the Description page of Project Settings.

#include "ShiftableEnemy.h"

// Sets default values
AShiftableEnemy::AShiftableEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UAC_Health>(TEXT("Enemy Health"));
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Enemy Shift"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AShiftableEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShiftableEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShiftableEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShiftableEnemy::TakeDamage(int Amount, E_COLOR _attackingColor)
{
	if (Shift && Health)
	{
		if (_attackingColor == Shift->GetCurrentColor())
			Health->TakeHit(Amount);
	}
}