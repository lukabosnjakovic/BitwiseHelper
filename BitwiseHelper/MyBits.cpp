#include "stdafx.h"
#include "MyBits.h"

// MyBits constructions
MyBits::MyBits()
{
	this->bits = NULL;
	this->name = "";
	this->resolution = NULL;
	this->MSBFirst = TRUE;
}

MyBits::MyBits(INT16 resolution, CString name, CCHAR MSBFirst)
{
	this->resolution = resolution;
	this->name = name;
	this->MSBFirst = MSBFirst;
	this->bits = new MyBit[resolution]();
	MakeBitsArray();
}

MyBits::MyBits(MyBit * bits, INT16 resolution, CString name, CCHAR MSBFirst)
{
	this->bits = bits;
	this->resolution = resolution;
	this->name = name;
	this->MSBFirst = MSBFirst;
}

// MyBits destruction
MyBits::~MyBits()
{
	if (this->bits != NULL) {
		delete[] this->bits;
		this->bits = NULL;
	}
}

// Helpers functions
void MyBits::MakeBitsArray() {
	INT16 i, b;
	MyBit bit;

	if (this->MSBFirst)
		b = resolution - 1;
	else
		b = 0;
	for (i = 0; i < this->resolution; i++)
	{
		bit.status = 0;
		bit.name.Format(_T("Bit %d"), b);;
		this->bits[i] = bit;
		if (MSBFirst)
			b--;
		else
			b++;
	}
}