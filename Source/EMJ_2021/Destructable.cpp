#include "Destructable.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "PlayerProjectile.h"
#include "EMJ_2021Character.h"
#include "Components/StaticMeshComponent.h"
#include "EscapeGameMode_Base.h"
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Constants.h"

ADestructable::ADestructable()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Destructable Trigger Box"));
	Health = CreateDefaultSubobject<UAC_Health>(TEXT("Destrustable Health"));
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Destructable Shift"));

	RootComponent = Mesh;

	UConstants::SetupBox(TriggerBox, TriggerBoxSize);
	TriggerBox->SetupAttachment(RootComponent);
}

#pragma region Overrides
// Called when the game starts or when spawned
void ADestructable::BeginPlay()
{
	Super::BeginPlay();

	if (Health) { Health->Setup(); }
	if (Shift)
	{
		Shift->Setup();
		Shiftable = Shift->CanShift;
	}

	AEscapeGameMode_Base* gameMode = Cast<AEscapeGameMode_Base>(GetWorld()->GetAuthGameMode());

	if (gameMode) { gameMode->ShiftedEvent.AddDynamic(this, &ADestructable::ShiftDestructable); }

	//Add collision
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADestructable::OnOverlapBegin);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADestructable::OnOverlapEnd);
	}
}

// Called every frame
void ADestructable::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
#pragma endregion

#pragma region Interface Methods
void ADestructable::OnShift_Implementation() { ShiftDestructable(); }

//E_COLOR ADestructable::GetColor_Implementation()
//{
//	if (Shift) { return Shift->GetCurrentColor(); }
//	else { return E_COLOR::NONE; }
//}

bool ADestructable::CanShift_Implementation() { return Shiftable; }
#pragma endregion

#pragma region Utils
void ADestructable::TakeHit(int Amount, E_COLOR _attackingColor)
{
	if (Shift && Health)
	{
		if (_attackingColor == Shift->GetCurrentColor())
		{
			if (Health->TakeHit(Amount))
			{
				OnDestroy();
			}
		}
	}
}

E_COLOR ADestructable::GetCurrentColor() { return Shift->GetCurrentColor(); }

void ADestructable::ShiftDestructable() { 
	if (Shift) 
	{ 
		if (Shiftable) 
		{ 
			Shift->Shift(); 
			OnShift_Call();
		} 
	} 
}
#pragma endregion

#pragma region Overlaps
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
				TakeHit(1, _playerShot->GetColor());
				//if (_playerShot->GetColor() == Shift->GetCurrentColor()) { this->OnDestroy(); }
				//else { this->OnDestroy(); }
				_playerShot->OnDestroy();
			}
		}
	}
}

void ADestructable::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ }

#pragma endregion

#pragma region On Shift Event

void ADestructable::OnShift_Call() { OnShifted(); }

void ADestructable::OnShifted_Implementation() { /*Defined in BP!*/ }

#pragma endregion

#pragma region On Hit Event

void ADestructable::OnHit() { E_OnTakeHit(); }

void ADestructable::E_OnTakeHit_Implementation() { /*Defined in BP!*/ }

#pragma endregion

#pragma region Destroy Event
//void ADestructable::Destroy() { OnDestroy(); }

void ADestructable::OnDestroy_Implementation() { /*Defined in BP!*/ }
#pragma endregion