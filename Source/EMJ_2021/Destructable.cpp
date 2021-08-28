// Fill out your copyright notice in the Description page of Project Settings.

#include "Destructable.h"

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
	//ALevelObjectCache::instance().AddToCache(this);
}

// Called every frame
void ADestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}