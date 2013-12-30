#include "main.h"

namespace Properties
{
	namespace Farms
	{
		int count;
		struct sFarm Farm[ MAX_FARMS ] = {{0, 0}};
		void load()
		{
			MYSQL_ROW row;
			MYSQL_RES *result;
			int slot = -1;
			int farm = 0;
			if (safe_query(con, "SELECT class_Property.*, class_Farms.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Farms  WHERE class_Property.property = class_Farms.id AND class_Property.type = 7"))
			{
				logprintf("Не удалось загрузить фермы");
				return ;
			}
			//------------------------------------------------------------------------------
			result = mysql_store_result(con);
			while (( row = mysql_fetch_row(result) ))
			{
				Property[ countProperty ].db = atoi(row[farmRows::id ]);
				Property[ countProperty ].bank = atoi(row[farmRows::bank ]);
				Property[ countProperty ].owner = atoi(row[farmRows::owner ]);
				Property[ countProperty ].price = atoi(row[farmRows::price ]);
				Property[ countProperty ].type = atoi(row[farmRows::type ]);
				Property[ countProperty ].posX = atof(row[farmRows::x ]);
				Property[ countProperty ].posY = atof(row[farmRows::y ]);
				Property[ countProperty ].posZ = atof(row[farmRows::z ]);
				Property[ countProperty ].property = atoi(row[farmRows::property ]);
				Property[ countProperty ].region = atoi(row[farmRows::region ]);
				Property[ countProperty ].number = atoi(row[farmRows::number ]);
				Property[ countProperty ].style = atoi(row[ farmRows::style ]);
				//===============================================================
				Farm[ count ].db = atoi(row[ farmRows::db]);
				Farm[ count ].minX = atof(row[ farmRows::sX ]);
				Farm[ count ].minY = atof(row[ farmRows::sY ]);
				Farm[ count ].maxX = atof(row[ farmRows::eX ]);
				Farm[ count ].maxY = atof(row[ farmRows::eY ]);
				//===============================================================
				strcpy(Farm[ count ].name, row[ farmRows::name ]);
				//===============================================================
				Farm[ count ].zome = GangZoneCreate(Farm[ count ].minX, Farm[ count ].minY, Farm[ count ].maxX, Farm[ count ].maxY);
				if (Property[ countProperty ].owner)
				{
					strcpy(Property[ countProperty ].player, row[ farmRows::pname ]);
				}
				//===============================================================
				makePick();
				//===============================================================
				countProperty++;
				count++;
			}
			mysql_free_result(result);
			//------------------------------------------------------------------------------
			if (safe_query(con, "SELECT * FROM Farms_WareHouses"))
			{
				logprintf("Не удалось загрузить склады ферм");
				return;
			}
			result = mysql_store_result(con);
			//------------------------------------------------------------------------------
			while (( row = mysql_fetch_row(result) ))
			{
				if (farm == atoi(row[ 1 ]) - 1 && slot < 5) slot++;
				else
				{
					farm = atoi(row[ 1 ]) - 1;
					slot = 0;
				}
				//===============================================================
				Farm[ farm ].WH[ slot ].db = atoi(row[0]);
				Farm[ farm ].WH[ slot ].level = atoi(row[ 2 ]);
				Farm[ farm ].WH[ slot ].style = atoi(row[ 3 ]);
				Farm[ farm ].WH[ slot ].model = atoi(row[ 4 ]);
				//===============================================================
				Farm[ farm ].WH[ slot ].enter.X = atof(row[ 5 ]);
				Farm[ farm ].WH[ slot ].enter.Y = atof(row[ 6 ]);
				Farm[ farm ].WH[ slot ].enter.Z = atof(row[ 7 ]);
				//===============================================================
				Farm[ farm ].WH[ slot ].object.X = atof(row[ 8 ]);
				Farm[ farm ].WH[ slot ].object.Y = atof(row[ 9 ]);
				Farm[ farm ].WH[ slot ].object.Z = atof(row[ 10]);
				//===============================================================
				Farm[ farm ].WH[ slot ].rotation.X = atof(row[ 11 ]);
				Farm[ farm ].WH[ slot ].rotation.Y = atof(row[ 12 ]);
				Farm[ farm ].WH[ slot ].rotation.Z = atof(row[ 13 ]);
				//===============================================================
				Farm[ farm ].WH[ slot ].obj = StreamerCall::Native::CreateDynamicObject
				(
					Farm[ farm ].WH[ slot ].model,
					Farm[ farm ].WH[ slot ].object.X,
					Farm[ farm ].WH[ slot ].object.Y,
					Farm[ farm ].WH[ slot ].object.Z,
					Farm[ farm ].WH[ slot ].rotation.X,
					Farm[ farm ].WH[ slot ].rotation.Y,
					Farm[ farm ].WH[ slot ].rotation.Z,
					0, 0
				);
				//===============================================================
				Farm[ farm ].WH[ slot ].info = StreamerCall::Native::CreateDynamic3DTextLabel
				(
					"Фермерский склад",
					-1,
					Farm[ farm ].WH[ slot ].enter.X,
					Farm[ farm ].WH[ slot ].enter.Y,
					Farm[ farm ].WH[ slot ].enter.Z,
					RADIUS_ACTIONS, 
					INVALID_PLAYER_ID,
					INVALID_VEHICLE_ID,
					true, 0, 0
				);
				//===============================================================
				Farm[ farm ].WH[ slot ].pick = StreamerCall::Native::CreateDynamicPickup
				(
					1318, 23,
					Farm[ farm ].WH[ slot ].enter.X,
					Farm[ farm ].WH[ slot ].enter.Y,
					Farm[ farm ].WH[ slot ].enter.Z,
					0, 0
				);
				//===============================================================
			}
			mysql_free_result(result);
			//------------------------------------------------------------------------------
			if (safe_query(con, "SELECT * FROM farm_Plants"))
			{
				logprintf("Не удалось загрузить склады ферм");
				return;
			}
			result = mysql_store_result(con);
			//------------------------------------------------------------------------------
			slot = -1;
			farm = 0;
			//------------------------------------------------------------------------------
			while (( row = mysql_fetch_row(result) ))
			{
				if (farm == atoi(row[ 1 ]) - 1 && slot < 64) slot++;
				else
				{
					farm = atoi(row[ 1 ]) - 1;
					slot = 0;
				}
				//===============================================================
				Farm[ farm ].item[ slot ].db = atoi(row[ 0 ]);
				Farm[ farm ].item[ slot ].model = atoi(row[ 2 ]);
				Farm[ farm ].item[ slot ].amount = atoi(row[ 7 ]);
				//===============================================================
				Farm[ farm ].item[ slot ].pos.X = atof(row[ 3 ]);
				Farm[ farm ].item[ slot ].pos.Y = atof(row[ 4 ]);
				Farm[ farm ].item[ slot ].pos.Z = atof(row[ 5 ]);
				Farm[ farm ].item[ slot ].proc  = atof(row[ 6 ]);
				//===============================================================
				Farm[ farm ].item[ slot ].obj = StreamerCall::Native::CreateDynamicObject
				(
					Farm[ farm ].item[ slot ].model,
					Farm[ farm ].item[ slot ].pos.X,
					Farm[ farm ].item[ slot ].pos.Y,
					Farm[ farm ].item[ slot ].pos.Z,
					0.0f, 0.0f, 0.0f,
					0, 0
				);
				//===============================================================
			}
			mysql_free_result(result);
			//------------------------------------------------------------------------------
			logprintf("Было загруженно %d ферм", count);
		}

		void makePick()
		{
			if (Property[ countProperty ].owner)
			{
				sprintf
				(
					query,
					"Ферма: \"%s\" \n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
					Farm[ count ].name,
					getSaZoneName(Property[ countProperty ].region),
					Property[ countProperty ].number, 
					Property[ countProperty ].player
				);
				//=====================================================================================================
				Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup
				(
					HOUSE_GREEN, 23,
					Property[ countProperty ].posX,
					Property[ countProperty ].posY,
					Property[ countProperty ].posZ, 
					0, 0
				);
				//=====================================================================================================
			}
			else
			{
				sprintf
				(
					query,
					"{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", 
					getSaZoneName(Property[ countProperty ].region), 
					Property[ countProperty ].number, 
					Property[ countProperty ].price
				);
				//=====================================================================================================
				Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup
				(
					HOUSE_RED, 23,
					Property[ countProperty ].posX,
					Property[ countProperty ].posY,
					Property[ countProperty ].posZ, 0, 0
				);
				//=====================================================================================================
			}
			Property[ countProperty ].text = StreamerCall::Native::CreateDynamic3DTextLabel
			(
				query, -1,
				Property[ countProperty ].posX,
				Property[ countProperty ].posY,
				Property[ countProperty ].posZ, 
				30.0f
			);
		}

		void onPickUp(const int u)
		{

		}

		void onAction(const int u)
		{

		}


		void save()
		{

		}

	}


}

/*

DROP FUNCTION IF EXISTS getOwnerName;
DELIMITER $$
CREATE FUNCTION `getOwnerName`(uid int)
RETURNS varchar(32) CHARSET CP1251
BEGIN
DECLARE select_var VARCHAR(32);
SET select_var = (select CONCAT(uname, ' ', sname) from accounts where id = uid);
return select_var;

END;
$$
DELIMITER ;

*/