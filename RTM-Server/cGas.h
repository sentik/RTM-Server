#pragma once

#ifndef __cGas__   
#define __cGas__   

#include "configs.h"

struct eGas
{
	int db;
	double fuel;
	int cube;
	char name[20];
};

class cGas
{
	public:
		static void cGas::loadGas();
};


#endif