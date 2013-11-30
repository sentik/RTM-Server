#pragma once

#ifndef __cGas__   
#define __cGas__   

#include "configs.h"

struct eGas
{
	int		db;
	float	fuel;
	float	minX;
	float	minY;
	float	minZ;
	float	maxX;
	float	maxY;
	float	maxZ;
	char	name[20];
};

namespace gasProperty
{
	class cGas
	{
		public:
			static void cGas::loadGas();
			static void cGas::fillingVehicle(const int);
			static struct eGas cGas::Gas[MAX_GAS];
	};

	enum rowsGas
	{
		id,
		owner,
		property,
		type,
		x,
		y,
		z,
		price,
		bank,
		region,
		number,
		db,
		fuel,
		minX,
		minY,
		minZ,
		maxX,
		maxY,
		maxZ,
		name,
		pname,
	};
}




#endif