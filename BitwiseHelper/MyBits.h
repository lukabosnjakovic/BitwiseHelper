#pragma once
#include "stdafx.h"
#include "MyBit.h"

class MyBits
{
	// Attributes
protected:
	MyBit * bits;
	INT16 resolution;
	CString name;
	CCHAR MSBFirst;
	UINT32 value;

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

	// Setters
	void SetBit(INT16 index, CCHAR state);
	void SetName(CString name);

	// Getters
	MyBit * GetBitsArray();
	MyBit GetBit(INT16 index);
	INT16 GetResolution();
	CString GetName();
	CCHAR IsMSBFirst();
	UINT32 GetDecValue();
	CString GetBinValueString();
	CString GetDecValueString();
	CString GetHexValueString();

private:
	void MakeBitsArray();
	void MakeValue(INT16 index, CCHAR state);
	void ApplyMask(UINT32 mask, CCHAR state);
	void CalculateValue();
	CString GetHexChar(CString hex);
};

