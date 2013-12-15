#pragma once

#ifndef __cHouses__   
#define __cHouses__   

#include "configs.h"

class cHouses
{
	public:
	static void cHouses::loadHouses();
	static void cHouses::loadHouseInteriors();
	static void cHouses::createHouseInterior(int);
	static void cHouses::updateText(const int, const int);
	static void cHouses::create(int, float, float, float);
	static void cHouses::makePick();
	//-------------------------------------------
};

struct sHouses
{
	int db;
	int style;
	int world;
};
struct sHouses extern Houses[ MAX_HOUSES ];
extern int countHouses;

struct eHouseDesine
{
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	int model;
	int obj;
	int db;
};
struct eHouseDesine extern HouseDesine[ MAX_HOUSES ][ MAX_DIS_OBJ ];


namespace Properties
{
	namespace Houses
	{
		enum HouseRows
		{
			id,
			owner,
			property,
			type,
			posx,
			posy,
			posz,
			price,
			bank,
			region,
			number,
			db,
			style,
			oName,
		};

		namespace Desine
		{
			enum DesineRows
			{
				id,
				owner,
				model,
				posx,
				posy,
				posz,
				rotx,
				roty,
				rotz
			};
		}
	}
}

#endif 