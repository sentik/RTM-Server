#include "main.h"
struct sVehicle   Properties::Shops::ShopVehicle::vehicle[ MAX_VEHSHOPS ];

void Properties::Shops::ShopVehicle::loadShop()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Shop_vehicle.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Shop_vehicle  WHERE class_Property.property = class_Shop_vehicle.db AND class_Property.type = 3");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while (( row = mysql_fetch_row(result) ))
	{
		Property[ countProperty ].db = atoi(row[Properties::Shops::ShopVehicle::vehRows::id ]);
		Property[ countProperty ].bank = atoi(row[Properties::Shops::ShopVehicle::vehRows::bank ]);
		Property[ countProperty ].owner = atoi(row[Properties::Shops::ShopVehicle::vehRows::owner ]);
		Property[ countProperty ].price = atoi(row[Properties::Shops::ShopVehicle::vehRows::price ]);
		Property[ countProperty ].type = atoi(row[Properties::Shops::ShopVehicle::vehRows::type ]);
		Property[ countProperty ].posX = atof(row[Properties::Shops::ShopVehicle::vehRows::posx ]);
		Property[ countProperty ].posY = atof(row[Properties::Shops::ShopVehicle::vehRows::posy ]);
		Property[ countProperty ].posZ = atof(row[Properties::Shops::ShopVehicle::vehRows::posz ]);
		Property[ countProperty ].property = atoi(row[Properties::Shops::ShopVehicle::vehRows::property ]);
		Property[ countProperty ].style = atoi(row[Properties::Shops::ShopVehicle::vehRows::style ]);
		Property[ countProperty ].region = atoi(row[Properties::Shops::ShopVehicle::vehRows::region ]);
		Property[ countProperty ].number = atoi(row[Properties::Shops::ShopVehicle::vehRows::number ]);
		//--------------------------------------------------------------
		vehicle[ i ].db = atoi(row[ Properties::Shops::ShopVehicle::vehRows::db ]);
		vehicle[ i ].type = atoi(row[ Properties::Shops::ShopVehicle::vehRows::category ]);
		vehicle[ i ].spawnR = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnr ]);
		vehicle[ i ].spawnX = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnx ]);
		vehicle[ i ].spawnY = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawny ]);
		vehicle[ i ].spawnZ = atof(row[ Properties::Shops::ShopVehicle::vehRows::spawnz ]);
		//--------------------------------------------------------------
		strcpy(vehicle[ i ].name, row[ Properties::Shops::ShopVehicle::vehRows::name ]);
		//--------------------------------------------------------------
		if (Property[ countProperty ].owner)
		{
			strcpy(Property[ countProperty ].player, row[ Properties::Shops::ShopVehicle::vehRows::oName ]);
			sprintf(query, "[Автосалон]\n{B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", vehicle[ i ].name, cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].player);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_GREEN, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "[Автосалон]\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d", cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].price);
			//=====================================================================================================
			Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_RED, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		//-----------------------------------------------------------------------------------------------------------
		Property[ countProperty ].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
																						Property[ countProperty ].posX,
																						Property[ countProperty ].posY,
																						Property[ countProperty ].posZ, 30.0f);
		//-----------------------------------------------------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно автосалонов \t- %d", i);
	

}