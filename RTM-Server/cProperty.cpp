#include "main.h"

struct Property Property[MAX_PROPERTY] = { { 0, 0 } };
struct Houses Houses[MAX_HOUSES] = { { 0, 0 } };


int countProperty;
int countHouses;


void cProperty::enterProperty()
{
	for (int i = 0; i < countProperty; i++)
	{

	}
}

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
		Property[ countProperty ].posx  = atof(row[ HouseRows::posx ]);
		Property[ countProperty ].posy  = atof(row[ HouseRows::posy ]);
		Property[countProperty].posz	=   atof(row[HouseRows::posz]);
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