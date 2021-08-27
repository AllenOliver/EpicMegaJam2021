// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_Health.h"

// Sets default values for this component's properties
UAC_Health::UAC_Health()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAC_Health::Setup()
{
	this->_currentHealth = MaxHealth;
}

void UAC_Health::Heal(float amount)
{
	int tempHealth = this->_currentHealth + amount;

	if (tempHealth >= this->MaxHealth)
		this->_currentHealth = this->MaxHealth;
	else
		this->_currentHealth = tempHealth;
}

void UAC_Health::TakeDamage(float amount, EDeath& Branch)
{
	int tempHealth = this->_currentHealth - amount;

	if (tempHealth <= 0)
		Branch = EDeath::Died;
	else
	{
		this->_currentHealth = tempHealth;
		EDeath::Lived;
	}
}

bool UAC_Health::TakeHit(float amount)
{
	float tempHealth = this->_currentHealth - amount;
	if (CheckForDeath(tempHealth))
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
	if (amount > _currentHealth) return true;
	else return false;
}

// Called when the game starts
void UAC_Health::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UAC_Health::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}