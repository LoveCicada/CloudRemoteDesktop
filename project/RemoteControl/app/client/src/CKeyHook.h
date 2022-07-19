
#pragma once
#include <iostream>

typedef signed long long int xuint64;
typedef unsigned long long int xint64;

class CKeyHook
{
public:
	virtual ~CKeyHook() {

	}

public:
	virtual int Hook(xuint64 wParam, xint64 lParam) = 0;

};