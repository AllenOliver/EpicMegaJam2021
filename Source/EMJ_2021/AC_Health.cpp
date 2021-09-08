// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_Health.h"

// Sets default values for this component's properties
UAC_Health::UAC_Health() { /*Creation code*/ }

#pragma region Overrides

void UAC_Health::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

void UAC_Health::Setup() { this->_currentHealth = MaxHealth; }

void UAC_Health::Heal(int amount)
{
	int tempHealth = this->_currentHealth + amount;

	if (tempHealth >= this->MaxHealth) { this->_currentHealth = this->MaxHealth; }
	else { this->_currentHealth = tempHealth; }
}

void UAC_Health::TakeDamage(int amount, E_DEATH& Branch)
{
	int tempHealth = this->_currentHealth - amount;

	if (tempHealth <= 0) { Branch = E_DEATH::DIE; }
	else
	{
		this->_currentHealth = tempHealth;
		E_DEATH::LIVE;
	}
}

bool UAC_Health::TakeHit(int amount)
{
	float tempHealth = this->_currentHealth - amount;
	if (this->CheckForDeath(tempHealth))
	{
		_currentHealth = 0;
		return true;
	}
	else
	{
		_currentHealth = tempHealth;
		return false;
	}
}

bool UAC_Health::CheckForDeath(float amount)
{
	if (amount > 0) return true;
	else return false;
}
int UAC_Health::GetCurrentHealth() { return this->_currentHealth; }