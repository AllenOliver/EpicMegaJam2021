// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Constants.h"

// Sets default values
APoolableObject::APoolableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	UConstants::SetupCapsule(TriggerCapsule, CapsuleSize);

	TriggerCapsule->SetupAttachment(RootComponent);
}

void APoolableObject::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void APoolableObject::Tick(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + Velocity * Direction * DeltaTime);
	Super::Tick(DeltaTime);
}

void APoolableObject::SetLifeSpan(float InLifespan)
{
	Lifespan = InLifespan;
	GetWorldTimerManager().SetTimer(LifespanTimer, this, &APoolableObject::Deactivate, Lifespan, false);
}

void APoolableObject::SetActive(bool InpActive)
{
	Active = InpActive;
	SetActorHiddenInGame(!InpActive);
}

bool APoolableObject::IsActive() { return Active; }

void APoolableObject::SetVelocity(float InVelocity) { Velocity = InVelocity; }

void APoolableObject::SetDirection(FVector InDirection) { Direction = InDirection; }

void APoolableObject::Deactivate() { SetActive(false); }