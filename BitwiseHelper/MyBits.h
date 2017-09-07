#pragma once
#include "stdafx.h"
#include "MyBit.h"
#include <vector>

class MyBits
{
	// Attributes
protected:
	std::vector<MyBit> bits;
	INT16 resolution;
	CString name;
	BOOL MSBFirst;
	UINT32 value;

	// Operations
public:

	// Overrides
public:

	// Implementation
public:
	MyBits();
	MyBits(INT16 resolution, CString name, BOOL MSBFirst);
	MyBits(std::vector<MyBit> bits, INT16 resolution, CString name, BOOL MSBFirst);
	~MyBits();

	// Setters
	void SetBit(INT16 index, BOOL state);
	void SetName(CString name);

	// Getters
	std::vector<MyBit> GetBitsVector();
	MyBit GetBit(INT16 index);
	INT16 GetResolution();
	CString GetName();
	BOOL IsMSBFirst();
	UINT32 GetDecValue();
	CString GetBinValueString();
	CString GetDecValueString();
	CString GetHexValueString();

private:
	void MakeBitsArray();
	void MakeValue(INT16 index, BOOL state);
	void ApplyMask(UINT32 mask, BOOL state);
	void CalculateValue();
	CString GetHexChar(CString hex);
};

