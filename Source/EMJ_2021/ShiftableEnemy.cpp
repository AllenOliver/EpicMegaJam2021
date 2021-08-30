// Fill out your copyright notice in the Description page of Project Settings.

#include "ShiftableEnemy.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "Constants.h"
#include "EscapeGameMode_Base.h"
#include "EMJ_2021Character.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AShiftableEnemy::AShiftableEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UAC_Health>(TEXT("Enemy Health"));
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Enemy Shift"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	RootComponent = Mesh;

	//auto _rawPlayer = UConstants::GetPlayer(GetWorld());
	//auto _playerCast = Cast<AEMJ_2021Character>(_rawPlayer);
	//UConstants::GetPlayer(GetWorld())->ShiftedEvent.AddDynamic(this, &AShiftableEnemy::ShiftEnemy);
}

// Called when the game starts or when spawned
void AShiftableEnemy::BeginPlay()
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
		gameMode->ShiftedEvent.AddDynamic(this, &AShiftableEnemy::ShiftEnemy);
	}

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

void AShiftableEnemy::ShiftEnemy()
{
	if (Shift) 
	{
		if (Shiftable) 
		{
			Shift->Shift();
		}
	}
}

void AShiftableEnemy::TakeHit(int Amount, E_COLOR _attackingColor)
{
	if (Shift && Health)
	{
		if (_attackingColor == Shift->GetCurrentColor())
			Health->TakeHit(Amount);
	}
}
void AShiftableEnemy::OnDie_Implementation()
{
	//ALevelObjectCache::instance.AddToCache(this);
}