#include "main.h"

struct sProperty		Property	[ MAX_PROPERTY ] = { { 0, 0 } };
struct Houses			Houses		[ MAX_HOUSES ] = { { 0, 0 } };
struct eHouseDesine		HouseDesine	[ MAX_HOUSES ][ 96 ];

int countProperty;
int countHouses;


/// <summary>
/// Сообщение покупки недвижимости
/// <param name="u">* Ид игрока</param>
/// <param name="p">* Ид недвижимости</param>
/// </summary>
void cProperty::buyMessage(const int u, const int p)
{

}


/// <summary>
/// Сообщение покупки недвижимости
/// <param name="u">* Ид игрока</param>
/// <param name="p">* Ид недвижимости</param>
/// </summary>
void cProperty::statusMessage(const int u, const int p)
{

}


/// <summary>
/// Действие входа в недвижимость
/// <param name="u">* Ид игрока</param>
/// </summary>
void cProperty::enterProperty(const int u)
{
	for (int i = 0; i < countProperty; i++)
	{
		const int idx = Property[ i ].style;
		//-----------------------------------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ))
		{
			if (!Property[ i ].owner)
			{
				cProperty::buyMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			if (Property[ i ].status)
			{
				cProperty::statusMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			cPlayer::setCharPos(u, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ, true);
			cPlayer::setCharInterior(u, Interior[ idx ].posI);
			cPlayer::setCharAngle(u, Interior[ idx ].posR);
			cPlayer::setCharWorld(u, i);
			//-----------------------------------------------------------------------------------------------
			break;
		}
		//--------------------------------------------------------------------
		if (Player[ u ].pPosW != i) continue;	//Если игрок не в нужном мире
		//--------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ))
		{
			cPlayer::setCharPos(u, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ, false);
			cPlayer::setCharInterior(u, 0);
			cPlayer::setCharWorld(u, 0);
			cPlayer::setCharAngle(u, 0);
		}
		//--------------------------------------------------------------------
	}
}

/// <summary>
/// Загрузка списка домов
/// </summary>
void cProperty::loadHouses()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Houses.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Houses  WHERE class_Property.property = class_Houses.db AND class_Property.type = 1");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while ((row = mysql_fetch_row(result)))
	{
		Property[countProperty].db			= atoi(row[Properties::Houses::HouseRows::id]);
		Property[countProperty].bank		= atoi(row[Properties::Houses::HouseRows::bank]);
		Property[countProperty].owner		= atoi(row[Properties::Houses::HouseRows::owner]);
		Property[countProperty].price		= atoi(row[Properties::Houses::HouseRows::price]);
		Property[countProperty].type		= atoi(row[Properties::Houses::HouseRows::type]);
		Property[countProperty].posX		= atof(row[Properties::Houses::HouseRows::posx ]);
		Property[countProperty].posY		= atof(row[Properties::Houses::HouseRows::posy ]);
		Property[countProperty].posZ		= atof(row[Properties::Houses::HouseRows::posz]);
		Property[countProperty].property	= atoi(row[Properties::Houses::HouseRows::property]);
		Property[ countProperty ].style		= atoi(row[Properties::Houses::HouseRows::style ]);
		//--------------------------------------------------------------
		strcpy(Property[ countProperty ].player, row[ Properties::Houses::HouseRows::oName ]);
		//--------------------------------------------------------------
		Houses[i].style = atoi(row[Properties::Houses::HouseRows::style]);
		Houses[i].db = atoi(row[Properties::Houses::HouseRows::db]);
		//--------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно домов \t- %d", i);
}

void cProperty::loadHouseInteriors()
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
		HouseDesine[ house ][ slot ].db = atoi(row[ 0 ]);
	//	logprintf("house: %d || slot: %d || db: %d", house, slot, HouseDesine[ house ][ slot ].db);
	}
}