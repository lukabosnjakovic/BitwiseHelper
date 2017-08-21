#pragma once
#include "stdafx.h"
#include "MyBit.h"

class MyBits
{
	// Attributes
public:
	MyBit * bits;
	INT16 resolution;
	CString name;
	CCHAR MSBFirst;

	// Operations
public:

	// Overrides
public:

	// Implementation
public:
	MyBits();
	MyBits(INT16 resolution, CString name, CCHAR MSBFirst);
	MyBits(MyBit * bits, INT16 resolution, CString name, CCHAR MSBFirst);
	~MyBits();

private:
	void MakeBitsArray();
};

