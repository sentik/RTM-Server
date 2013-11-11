#include "main.h"

struct Property Property[MAX_PROPERTY] = { { 0, 0 } };
struct Houses Houses[MAX_HOUSES] = { { 0, 0 } };


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
/// Действие входа в недвижимость
/// <param name="u">* Ид игрока</param>
/// </summary>
void cProperty::enterProperty(const int u)
{
	for (int i = 0; i < countProperty; i++)
	{
		const int idx = Property[ i ].style;
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ))
		{
			if (!Property[ i ].owner)
			{
				cProperty::buyMessage(u, i);
				break;
			}
			//-----------------------------------------------------------------------------------------------
			cPlayer::setCharPos(u, Interior[ style ].posX, Interior[ style ].posY, Interior[ style ].posZ, true);
			cPlayer::setCharInterior(u, Interior[ style ].posI);
			cPlayer::setCharAngle(u, Interior[ style ].posR);
			cPlayer::setCharWorld(u, i);
			//-----------------------------------------------------------------------------------------------
		}
		else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ style ].posX, Interior[ style ].posY, Interior[ style ].posZ))
		{

		}
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
		Property[countProperty].db		= atoi(row[HouseRows::id]);
		Property[countProperty].bank	= atoi(row[HouseRows::bank]);
		Property[countProperty].owner	= atoi(row[HouseRows::owner]);
		Property[countProperty].price	= atoi(row[HouseRows::price]);
		Property[countProperty].type	= atoi(row[HouseRows::type]);
		Property[ countProperty ].posX  = atof(row[ HouseRows::posx ]);
		Property[ countProperty ].posY  = atof(row[ HouseRows::posy ]);
		Property[countProperty].posZ	=   atof(row[HouseRows::posz]);
		Property[countProperty].property = atoi(row[HouseRows::property]);
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
}