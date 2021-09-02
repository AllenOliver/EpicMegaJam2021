// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructable.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "PlayerProjectile.h"
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

	//Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADestructable::OnOverlapBegin);
	//Mesh->OnComponentEndOverlap.AddDynamic(this, &ADestructable::OnOverlapEnd);
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

E_COLOR ADestructable::GetCurrentColor() { return Shift->GetCurrentColor(); }
// Called every frame
void ADestructable::ShiftDestructable()
{
	if (Shift)
	{
		if (Shift->CanShift)
		{
			Shift->Shift();
		}
	}
}


void ADestructable::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerProjectile::StaticClass()))
		{
			APlayerProjectile* _playerShot = Cast<APlayerProjectile>(OtherActor);
			if (_playerShot) 
			{
				if (_playerShot->GetColor() == Shift->GetCurrentColor()) 
				{
					//Nothing; We want opposites

				}
				else 
				{
					Destroy();

				}
			}
		}
	}
}

void ADestructable::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("We Ended"));
	}
}


void ADestructable::Destroy() { OnDestroy(); }

void ADestructable::OnDestroy_Implementation()
{
	//ALevelObjectCache::instance.AddToCache(this);
}