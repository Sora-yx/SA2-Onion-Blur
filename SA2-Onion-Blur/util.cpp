#include "pch.h"

void __cdecl AddConstantAttrSADX(NJD_FLAG _and, NJD_FLAG _or)
{
	nj_constant_attr_and_ |= _and;
	nj_constant_attr_or_ |= _or | NJD_FLAG_DOUBLE_SIDE;
}