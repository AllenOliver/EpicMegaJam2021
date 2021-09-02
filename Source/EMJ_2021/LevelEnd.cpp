// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelEnd.h"
#include "Components/BoxComponent.h"
#include "EMJ_2021Character.h"

#pragma region Set up
				// Sets default values
ALevelEnd::ALevelEnd()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Set up collision volume

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetBoxExtent(BoxExtents);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);

	//Add collision event binding
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelEnd::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALevelEnd::OnOverlapEnd);

#pragma endregion
}

// Called when the game starts or when spawned
void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#pragma endregion

#pragma region BP / Public Functions

void ALevelEnd::EndLevel() { OnEndLevel(); } //Call event

// == BP Implementations ==

void ALevelEnd::OnEndLevel_Implementation() { /*Defined in BP!*/ }

#pragma endregion

#pragma region Collision

//void ALevelEnd::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor)
//	{
//		if (OtherActor->IsA(AEMJ_2021Character::StaticClass)) { EndLevel(); }
//	}
//}
//
//void ALevelEnd::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//}

void ALevelEnd::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr
	if (OtherActor)
	{
		if (OtherActor->IsA(AEMJ_2021Character::StaticClass()))
		{
			EndLevel();
		}
	}
}

void ALevelEnd::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("We Ended"));
	}
}
#pragma endregion