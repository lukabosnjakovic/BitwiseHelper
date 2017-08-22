#include "stdafx.h"
#include "MyBits.h"

// MyBits constructions
MyBits::MyBits()
{
	this->bits = NULL;
	this->name = _T("New Bit Mask");
	this->resolution = NULL;
	this->MSBFirst = TRUE;
	this->value = 0;
}

MyBits::MyBits(INT16 resolution, CString name, CCHAR MSBFirst)
{
	this->resolution = resolution;
	this->name = name;
	this->MSBFirst = MSBFirst;
	this->bits = new MyBit[resolution]();
	MakeBitsArray();
	this->value = 0;
}

MyBits::MyBits(MyBit * bits, INT16 resolution, CString name, CCHAR MSBFirst)
{
	this->bits = bits;
	this->resolution = resolution;
	this->name = name;
	this->MSBFirst = MSBFirst;
	CalculateValue();
}

// MyBits destruction
MyBits::~MyBits()
{
	if (this->bits != NULL) {
		delete[] this->bits;
		this->bits = NULL;
	}
}

void MyBits::SetBit(INT16 index, CCHAR state)
{
	if(IsMSBFirst())
		this->bits[this->resolution - index - 1].state = state;
	else
		this->bits[index].state = state;
	MakeValue(index, state);
}

void MyBits::SetName(CString name)
{
	this->name = name;
}

MyBit * MyBits::GetBitsArray()
{
	return this->bits;
}

MyBit MyBits::GetBit(INT16 index)
{
	return this->bits[index];
}

INT16 MyBits::GetResolution()
{
	return this->resolution;
}

CString MyBits::GetName()
{
	return this->name;
}

CCHAR MyBits::IsMSBFirst()
{
	return this->MSBFirst;
}

UINT32 MyBits::GetDecValue()
{
	return this->value;
}

CString MyBits::GetBinValueString()
{
	CString tmp, output = _T("0b");
	for (INT16 i = 0; i < this->resolution; i++)
	{
		tmp.Format(_T("%d"), this->bits[i].state);
		output += tmp;
	}
	return output;
}

CString MyBits::GetDecValueString()
{
	CString output;
	output.Format(_T("%d"), this->value);
	return output;
}

CString MyBits::GetHexValueString()
{
	CString tmp, tmp2, output = _T("0x");
	for (INT16 i = 0; i < this->resolution; i++)
	{
		tmp.Format(_T("%d"), this->bits[i].state);
		tmp2 += tmp;
		if ((i + 1) % 4 == 0)
		{
			output += GetHexChar(tmp2);
			tmp2 = _T("");
		}
	}
	return output;
}

// Helpers functions
void MyBits::MakeBitsArray() {
	INT16 i, b;
	MyBit bit;

	if (IsMSBFirst())
		b = resolution - 1;
	else
		b = 0;
	for (i = 0; i < this->resolution; i++)
	{
		bit.state = 0;
		bit.name.Format(_T("Bit %d"), b);;
		this->bits[i] = bit;
		if (IsMSBFirst())
			b--;
		else
			b++;
	}
}

void MyBits::MakeValue(INT16 index, CCHAR state)
{
	UINT32 tmp;
	tmp = 1;
	if (IsMSBFirst())
		tmp <<= this->resolution - index - 1;
	else
		tmp <<= index;
	ApplyMask(tmp, state);
}

void MyBits::ApplyMask(UINT32 mask, CCHAR state)
{
	if (state)
		this->value |= mask;
	else
		this->value ^= mask;
}

void MyBits::CalculateValue()
{
	for (INT16 i = 0; i < this->resolution; i++)
		MakeValue(i, this->bits[i].state);
}

CString MyBits::GetHexChar(CString hex)
{
	if(hex == "0000")
		return _T("0");
	if (hex == "0001")
		return _T("1");
	if (hex == "0010")
		return _T("2");
	if (hex == "0011")
		return _T("3");
	if (hex == "0100")
		return _T("4");
	if (hex == "0101")
		return _T("5");
	if (hex == "0110")
		return _T("6");
	if (hex == "0111")
		return _T("7");
	if (hex == "1000")
		return _T("8");
	if (hex == "1001")
		return _T("9");
	if (hex == "1010")
		return _T("A");
	if (hex == "1011")
		return _T("B");
	if (hex == "1100")
		return _T("C");
	if (hex == "1101")
		return _T("D");
	if (hex == "1110")
		return _T("E");
	if (hex == "1111")
		return _T("F");

	return _T("");
}
