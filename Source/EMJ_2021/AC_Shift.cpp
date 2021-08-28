// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_Shift.h"

// Sets default values for this component's properties
UAC_Shift::UAC_Shift()
{
	// ...
}

void UAC_Shift::Setup()
{
	//TODO: Setup code
	_currentColor = StartColor;
	this->SetCurrentMaterial(_currentColor);
}

void UAC_Shift::Update()
{
	//TODO: Update code.
}

void UAC_Shift::Shift()
{
	if (CanShift)
	{
		if (this->_currentColor == E_COLOR::RED)
		{
			this->SetCurrentMaterial(E_COLOR::BLUE);
		}
		else
		{
			this->SetCurrentMaterial(E_COLOR::RED);
		}
		//Call event
		OnShift().Broadcast();
	}

	//TODO: Cache OG Material, Set new material, Make other things do it.
}

void UAC_Shift::SetCurrentMaterial(E_COLOR _color)
{
	if (_color == E_COLOR::RED)
	{
		this->_currentColor = E_COLOR::RED;
		this->_currentMaterial = this->RedMaterial;
	}
	else
	{
		this->_currentColor = E_COLOR::BLUE;
		this->_currentMaterial = this->BlueMaterial;
	}
}

E_COLOR UAC_Shift::GetCurrentColor() { return this->_currentColor; }

UMaterial* UAC_Shift::GetCurrentMaterial() { return this->_currentMaterial; }