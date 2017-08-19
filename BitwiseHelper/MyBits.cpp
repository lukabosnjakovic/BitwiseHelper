#include "stdafx.h"
#include "MyBits.h"

// MyBits constructions
MyBits::MyBits(INT16 resolution, CString name)
{
	this->resolution = resolution;
	this->name = name;
	this->bits = new MyBit[resolution]();
	MakeBitsArray();
}

MyBits::MyBits(MyBit * bits, INT16 resolution, CString name)
{
	this->bits = bits;
	this->resolution = resolution;
	this->name = name;
}

// MyBits destruction
MyBits::~MyBits()
{
	delete [] this->bits;
	this->bits = NULL;
}

// Helpers functions
void MyBits::MakeBitsArray() {
	INT16 i;
	MyBit bit;
	for (i = 0; i < this->resolution; i++)
	{
		bit = this->bits[i];
		bit.status = 0;
		bit.name.Format(_T("Bit%d"), i);;
	}
}