#pragma once

#ifndef __cGas__   
#define __cGas__   

#include "configs.h"

struct eGas
{
	int		db;
	float	cost;
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
			static void cGas::saveGas();
			static void cGas::fillingVehicle(const int);
			static void cGas::fillingVehicleProcess(const int, const int);
			static void cGas::updateText(const int, const int);
			static void cGas::ownerMenu(const int);
			static void cGas::onDLG(const int, const int, const int, const int, const char*);
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
		cost,
		pname,
	};
}




#endif