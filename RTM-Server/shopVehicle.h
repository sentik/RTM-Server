#pragma once

#include "configs.h"
#define MAX_VEHSHOPS 32

struct sVehicle
{
	int db;
	int type;
	char name[ 32 ];
	float spawnX;
	float spawnY;
	float spawnZ;
	float spawnR;
	float angle;
	//-----------------------------
	int Textdraw[15];
	int Item;			//Индекс
	int	Car;			//Ид авто
	bool Used;
};

struct eItem
{
	int DB;
	int Model;
	int Amount;
	int Price;
};




namespace Properties
{
	namespace Shops
	{
		class ShopVehicle
		{
			public:
			static char Gear[ 3 ][ 16 ];
			static char Group[ 4 ][ 16 ];
			static struct sVehicle  ShopVehicle::vehicle[ MAX_VEHSHOPS ];
			static struct eItem		ShopVehicle::items[MAX_VEHSHOPS][20];
			static int count;
			static void ShopVehicle::loadShop();
			static void ShopVehicle::preView(const int);
			static void ShopVehicle::viewList(const int, const int);
			static void ShopVehicle::viewCam(const int);
			static void ShopVehicle::initTextDraws(const int, const int);
			static void ShopVehicle::endView(const int);
			static void ShopVehicle::listView(const int, bool);
			enum vehRows
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
				category,
				style,
				name,
				spawnx,
				spawny,
				spawnz,
				spawnr,
				oName,
			};
			enum itemRows
			{
				bid,
				model,
				cost,
				amount,
			};
			enum drawNames
			{
				gear,
				group,
				speedText,
				power,
				fuel,
				control,
				controlValue,
				speed,
				speedValue,
				costVeh,
			};

		};



	}
}
