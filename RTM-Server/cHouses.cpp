#include "main.h"

struct Houses			Houses[ MAX_HOUSES ] = { { 0, 0 } };
struct eHouseDesine		HouseDesine[ MAX_HOUSES ][ 96 ];
int countHouses;


/// <summary>
/// Загрузка списка домов
/// </summary>
void cHouses::loadHouses()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Houses.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Houses  WHERE class_Property.property = class_Houses.db AND class_Property.type = 1");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while (( row = mysql_fetch_row(result) ))
	{
		Property[ countProperty ].db = atoi(row[ Properties::Houses::HouseRows::id ]);
		Property[ countProperty ].bank = atoi(row[ Properties::Houses::HouseRows::bank ]);
		Property[ countProperty ].owner = atoi(row[ Properties::Houses::HouseRows::owner ]);
		Property[ countProperty ].price = atoi(row[ Properties::Houses::HouseRows::price ]);
		Property[ countProperty ].type = atoi(row[ Properties::Houses::HouseRows::type ]);
		Property[ countProperty ].posX = atof(row[ Properties::Houses::HouseRows::posx ]);
		Property[ countProperty ].posY = atof(row[ Properties::Houses::HouseRows::posy ]);
		Property[ countProperty ].posZ = atof(row[ Properties::Houses::HouseRows::posz ]);
		Property[ countProperty ].property = atoi(row[ Properties::Houses::HouseRows::property ]);
		Property[ countProperty ].style = atoi(row[ Properties::Houses::HouseRows::style ]);
		Property[countProperty].region = atoi(row[Properties::Houses::HouseRows::region]);
		Property[countProperty].number = atoi(row[Properties::Houses::HouseRows::number]);
		//--------------------------------------------------------------
		//--------------------------------------------------------------
		Houses[ i ].style = atoi(row[ Properties::Houses::HouseRows::style ]);
		Houses[ i ].db = atoi(row[ Properties::Houses::HouseRows::db ]);
		//--------------------------------------------------------------
		if (Property[ countProperty ].owner)
		{
			strcpy(Property[countProperty].player, row[Properties::Houses::HouseRows::oName]);
			sprintf(query, "{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].player);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_GREEN, 23,
																					   Property[ countProperty ].posX,
																					   Property[ countProperty ].posY,
																					   Property[ countProperty ].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(HOUSE_RED, 23,
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
		Houses[ i ].world = countProperty;
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно домов \t- %d", i);
}

void cHouses::loadHouseInteriors()
{
	int slot = 0;
	int house = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM interior_House ORDER BY house");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		if (house == atoi(row[ 1 ]) && slot < 96) slot++;
		else
		{
			house = atoi(row[ 1 ]);
			slot = 0;
		}
		HouseDesine[ house ][ slot ].db = atoi(row[ Properties::Houses::Desine::DesineRows::id ]);
		HouseDesine[ house ][ slot ].model = atoi(row[ Properties::Houses::Desine::DesineRows::model ]);
		//------------------------------------------------------------------------------------------------
		HouseDesine[ house ][ slot ].posX = atof(row[ Properties::Houses::Desine::DesineRows::posx ]);
		HouseDesine[ house ][ slot ].posY = atof(row[ Properties::Houses::Desine::DesineRows::posy ]);
		HouseDesine[ house ][ slot ].posZ = atof(row[ Properties::Houses::Desine::DesineRows::posz ]);
		//------------------------------------------------------------------------------------------------
		HouseDesine[ house ][ slot ].rotX = atof(row[ Properties::Houses::Desine::DesineRows::rotx ]);
		HouseDesine[ house ][ slot ].rotY = atof(row[ Properties::Houses::Desine::DesineRows::roty ]);
		HouseDesine[ house ][ slot ].rotZ = atof(row[ Properties::Houses::Desine::DesineRows::rotz ]);
		//------------------------------------------------------------------------------------------------
		HouseDesine[ house ][ slot ].obj = StreamerCall::Native::CreateDynamicObject(
			HouseDesine[ house ][ slot ].model,
			HouseDesine[ house ][ slot ].posX,
			HouseDesine[ house ][ slot ].posY,
			HouseDesine[ house ][ slot ].posZ,
			HouseDesine[ house ][ slot ].rotX,
			HouseDesine[ house ][ slot ].rotY,
			HouseDesine[ house ][ slot ].rotZ, Houses[ house ].world, Interior[ Houses[ house ].style ].posI);
		//------------------------------------------------------------------------------------------------

		//	logprintf("house: %d || slot: %d || db: %d", house, slot, HouseDesine[ house ][ slot ].db);
	}
}