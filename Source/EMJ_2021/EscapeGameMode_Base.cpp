// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameMode_Base.h"
#include "ShiftableEnemy.h"
#include "Destructable.h"
#include "Kismet/GameplayStatics.h"
#include "AC_Shift.h"
#include "EMJ_2021Character.h"

#pragma region Public functions

// Gameplay
void AEscapeGameMode_Base::StartGame()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (myCharacter)
	{
		if (AEMJ_2021Character* _cast = Cast<AEMJ_2021Character>(myCharacter))
		{
			_currentPlayer = _cast;
			UE_LOG(LogTemp, Warning, TEXT("Yes cast :)"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No cast :("));
		}
	}

	//PopulateLists();
}

void AEscapeGameMode_Base::WinGame() { OnWinGame(); }


void AEscapeGameMode_Base::OpenLevel(UWorld* _world, FString _levelName)
{
	if (_world)
	{
		FString _currentMapName = _world->GetMapName();

		if (_levelName != "") 
		{
			if (_currentMapName != _levelName)
				UGameplayStatics::OpenLevel(_world, FName(*_levelName));
			else 
				this->ResetLevel();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Level name is empty. Doing nothing >:D"));
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("World not defined. Doing nothing >:D"));
	}

}

void AEscapeGameMode_Base::RespawnPlayer()
{
	//GetWorld()->GetAuthGameMode()->RestartPlayer(GetWorld()->GetFirstPlayerController());
	//or
	UConstants::ResetCurrentLevel(GetWorld(), this);
}

//Helper functions

void AEscapeGameMode_Base::PopulateLists()
{
	this->RefreshDestructableList();
	this->RefreshEnemyList();
	this->RefreshShiftableList();
}

void AEscapeGameMode_Base::MassShift()
{
	ShiftedEvent.Broadcast();
}

void AEscapeGameMode_Base::OnWinGame_Implementation()
{
}

#pragma endregion

#pragma region Adding and removing

void AEscapeGameMode_Base::RemoveFromCache(AActor* _actor)
{
	if (_actor)
	{
		if (ADestructable* _destructable = Cast<ADestructable>(_actor))
		{
			//Do destructable stuff
			if (this->DestructableList.Contains(_actor))
			{
				this->DestructableList.Remove(_actor);
			}

			//Check for shiftable
			if (_destructable->Shiftable)
			{
				if (this->ShiftableObjectList.Contains(_actor))
				{
					//Remove from shift cache too
					this->ShiftableObjectList.Remove(_actor);
				}
			}
		}
		else if (Is(_actor, AShiftableEnemy::StaticClass()))
		{
			if (this->EnemyList.Contains(_actor))
			{
				this->EnemyList.Remove(_actor);
			}

			if (this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Remove(_actor);
			}
		}
		else if (Is(_actor, AEMJ_2021Character::StaticClass())) // Shew lord Epic, make this name an option on start up.
		{
			if (this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Remove(_actor);
			}

			if (this->_currentPlayer)
			{
				_currentPlayer = NULL;
			}
		}
		else
		{
			//Nothing
		}
	}
}

void AEscapeGameMode_Base::AddToCache(AActor* _actor)
{
	if (_actor)
	{
		if (ADestructable* _destructable = Cast<ADestructable>(_actor))
		{
			//Do destructable stuff
			if (!this->DestructableList.Contains(_actor))
			{
				this->DestructableList.Add(_actor);
			}

			//Check for shiftable
			if (_destructable->Shiftable)
			{
				if (!this->ShiftableObjectList.Contains(_actor))
				{
					//Remove from shift cache too
					this->ShiftableObjectList.Add(_actor);
				}
			}
		}
		else if (AShiftableEnemy* _shiftableEnemy = Cast<AShiftableEnemy>(_actor))
		{
			if (!this->EnemyList.Contains(_actor))
			{
				this->EnemyList.Add(_actor);
			}

			if (!this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Add(_actor);
			}
		}
		else if (AEMJ_2021Character* _player = Cast<AEMJ_2021Character>(_actor)) // Shew lord Epic, make this name an option on start up.
		{
			if (!this->ShiftableObjectList.Contains(_actor))
			{
				//Remove from shift cache too
				this->ShiftableObjectList.Add(_actor);
			}
			if (!this->_currentPlayer)
			{
				_currentPlayer = Cast<AEMJ_2021Character>(_actor);
			}
		}
		else
		{
			//Nothing
		}
	}
}

#pragma endregion

#pragma region Refreshing Lists

void AEscapeGameMode_Base::RefreshEnemyList()
{
	this->EnemyList.Empty();

	TArray<AShiftableEnemy*> shiftableEnemies;
	//TArray<AShiftableEnemy*> staticColorEnemies;
	FindAllActorsOfType(GetWorld(), shiftableEnemies);
}
void AEscapeGameMode_Base::RefreshDestructableList()
{
	this->DestructableList.Empty(); //clear it

	TArray<ADestructable*> destructables;
	FindAllActorsOfType(GetWorld(), destructables);

	for (int i = 0; i < destructables.Num(); i++)
	{
		this->DestructableList.Add(destructables[i]);
	}
}
void AEscapeGameMode_Base::RefreshShiftableList() //Expensiveeeee
{
	//this->ShiftableObjectList.Empty(); //clear it

	//TArray<AActor*> _shiftables;
	//GetAllActorsWithComponent(GetWorld(), UAC_Shift::StaticClass(), _shiftables);

	//for (int i = 0; i < _shiftables.Num(); i++)
	//{
	//	if (_shiftables[i])
	//		this->ShiftableObjectList.Add(_shiftables[i]);
	//}
}

#pragma endregion

#pragma region Getters

int AEscapeGameMode_Base::GetShiftableCacheSize() { return this->ShiftableObjectList.Num(); }
int AEscapeGameMode_Base::GetDestructableCacheSize() { return this->DestructableList.Num(); }
int AEscapeGameMode_Base::GetEnemyCacheSize() { return this->EnemyList.Num(); }
AEMJ_2021Character* AEscapeGameMode_Base::GetPlayerCharacter()
{
	if (_currentPlayer) return _currentPlayer;
	else return NULL;
}

#pragma endregion

//== DEBUG ==

void AEscapeGameMode_Base::Debug_Shift()
{
	MassShift();
}

void AEscapeGameMode_Base::Reset_Level()
{
	this->RestartGame();
	//RespawnPlayer();
}

void AEscapeGameMode_Base::Shift_Player()
{
	if (_currentPlayer)
	{
		_currentPlayer->ShiftColors();
	}
}

void AEscapeGameMode_Base::Level_Win() { WinGame(); }

<<<<<<< Updated upstream
void AEscapeGameMode_Base::Level_Lose() {  }
=======
void AEscapeGameMode_Base::Level_Lose() { LoseGame(); }
>>>>>>> Stashed changes
