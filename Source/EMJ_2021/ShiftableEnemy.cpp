#pragma region Includes

#include "ShiftableEnemy.h"
#include "AC_Health.h"
#include "AC_Shift.h"
#include "Constants.h"
#include "EscapeGameMode_Base.h"
#include "EMJ_2021Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerProjectile.h"
#include "Math/Vector2D.h"

#pragma endregion

AShiftableEnemy::AShiftableEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UAC_Health>(TEXT("Enemy Health"));
	Shift = CreateDefaultSubobject<UAC_Shift>(TEXT("Enemy Shift"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Mesh"));
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Enemy Trigger Capsule"));

	RootComponent = Mesh;

	UConstants::SetupCapsule(TriggerCapsule, CapsuleSize);

	TriggerCapsule->SetupAttachment(RootComponent);
}

#pragma region Overrides

void AShiftableEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Set up components
	if (Health) { Health->Setup(); }
	if (Shift)
	{
		Shift->Setup();
		Shiftable = Shift->CanShift;
	}

	//Add to the shifting global event
	AEscapeGameMode_Base* gameMode = Cast<AEscapeGameMode_Base>(GetWorld()->GetAuthGameMode());

	if (gameMode) { gameMode->ShiftedEvent.AddDynamic(this, &AShiftableEnemy::ShiftEnemy); }

	//Add collision
	if (TriggerCapsule)
	{
		TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AShiftableEnemy::OnOverlapBegin);
		TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AShiftableEnemy::OnOverlapEnd);
	}
}

// Called every frame
void AShiftableEnemy::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AShiftableEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) { Super::SetupPlayerInputComponent(PlayerInputComponent); }

#pragma endregion

#pragma region Public Methods
void AShiftableEnemy::ShiftEnemy() { if (Shift != nullptr) { if (Shiftable) { Shift->Shift(); } } }

bool AShiftableEnemy::TakeHit(int Amount, E_COLOR _attackingColor)
{
	if (Shift && Health)
	{
		if (_attackingColor == Shift->GetCurrentColor())
		{
			if (Health->TakeHit(Amount)) { return true; } //Die
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
}

E_COLOR AShiftableEnemy::GetColor() { return Shift->GetCurrentColor(); }

int AShiftableEnemy::GetCurrentHealth() { return Health->GetCurrentHealth(); }
#pragma endregion

#pragma region Events and Calls

void AShiftableEnemy::Die() { OnDie(); }

void AShiftableEnemy::OnDie_Implementation() { /*Defined in BP*/ }

void AShiftableEnemy::OnHit() { E_OnTakeHit(); }

void AShiftableEnemy::E_OnTakeHit_Implementation() { /*Defined in BP*/ }

#pragma endregion

#pragma region Overlapping
void AShiftableEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if Actors do not equal nullptr
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerProjectile::StaticClass()))
		{
			APlayerProjectile* _playerShot = Cast<APlayerProjectile>(OtherActor);
			if (_playerShot)
			{
				if (_playerShot->GetColor() == Shift->GetCurrentColor()) { /*Nothing; We want opposites*/ }
				else
				{
					if (TakeHit(1, _playerShot->GetColor()))
					{
						Destroy();
					}
					else
					{
						/*The actor survives*/
						OnHit();
					}
				}
			}
		}
	}
}

void AShiftableEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

#pragma endregion

#pragma region Interface Methods
void AShiftableEnemy::OnShift_Implementation() { if (Shift != nullptr) { if (Shiftable) { Shift->Shift(); } } }

bool AShiftableEnemy::CanShift_Implementation() { return Shift->CanShift; }

#pragma endregion