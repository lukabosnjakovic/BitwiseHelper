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

	// Operations
public:

	// Overrides
public:

	// Implementation
public:
	MyBits();
	MyBits(INT16 resolution, CString name);
	MyBits(MyBit * bits, INT16 resolution, CString name);
	~MyBits();

private:
	void MakeBitsArray();
};

