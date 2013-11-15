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
		vehicle[ i ].db = atoi(row[ Properties::Shops::ShopVehicle::vehRows::db ]);
	}

	

}