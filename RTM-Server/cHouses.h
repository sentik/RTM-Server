#pragma once

#include "configs.h"

class cHouses
{
	public:
	static void cHouses::loadHouses();
	static void cHouses::loadHouseInteriors();
	static void cHouses::createHouseInterior(int);
	//-------------------------------------------
};


struct Houses
{
	int db;
	int style;
	int world;
};
struct Houses extern Houses[ MAX_HOUSES ];
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
	enum propertyTypes
	{
		Property_None,
		Property_House,
	};

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