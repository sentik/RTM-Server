#include "main.h"

struct sProperty Property[ MAX_PROPERTY ] = { { 0, 0 } };
struct Houses Houses[MAX_HOUSES] = { { 0, 0 } };
struct eHouseDesine HouseDesine[ MAX_HOUSES ][ 96 ];


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
			cPlayer::setCharPos(u, Interior[ style ].posX, Interior[ style ].posY, Interior[ style ].posZ, true);
			cPlayer::setCharInterior(u, Interior[ style ].posI);
			cPlayer::setCharAngle(u, Interior[ style ].posR);
			cPlayer::setCharWorld(u, i);
			//-----------------------------------------------------------------------------------------------
			break;
		}
		//--------------------------------------------------------------------
		if (Player[ u ].pPosW != i) continue;	//Если игрок не в нужном мире
		//--------------------------------------------------------------------
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ style ].posX, Interior[ style ].posY, Interior[ style ].posZ))
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
		Property[countProperty].db			= atoi(row[HouseRows::id]);
		Property[countProperty].bank		= atoi(row[HouseRows::bank]);
		Property[countProperty].owner		= atoi(row[HouseRows::owner]);
		Property[countProperty].price		= atoi(row[HouseRows::price]);
		Property[countProperty].type		= atoi(row[HouseRows::type]);
		Property[countProperty].posX		= atof(row[HouseRows::posx ]);
		Property[countProperty].posY		= atof(row[HouseRows::posy ]);
		Property[countProperty].posZ		= atof(row[HouseRows::posz]);
		Property[countProperty].property	= atoi(row[HouseRows::property]);
		Property[ countProperty ].style		= atoi(row[HouseRows::style ]);
		//--------------------------------------------------------------
		strcpy(Property[countProperty].player, row[oName]);
		//--------------------------------------------------------------
		Houses[i].style = atoi(row[HouseRows::style]);
		Houses[i].db = atoi(row[HouseRows::db]);
		//--------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно домов \t- %d", i);

	for (int z = 0; z < MAX_HOUSES; z++)
	{
		for (int q = 0; q < 96; q++)
		{
			HouseDesine[ z ][ q ].db = z + q;
			HouseDesine[ z ][ q ].model = 1000 + z + q;
			HouseDesine[ z ][ q ].posX = 777.0f;
			HouseDesine[ z ][ q ].rotY = 554.0f;
		}
	}

}