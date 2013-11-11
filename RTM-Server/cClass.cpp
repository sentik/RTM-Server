#include "main.h"


//--------------------------------------------------------
struct pClass PlayerClass[MAX_CLASES] = { { 0, 0 } };
struct vClass VehicleClass[ VEH_CLASES ] = { { 0, 0 } };
//--------------------------------------------------------
void cClass::loadVehicleClass()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM class_Vehicles ORDER BY id LIMIT 212");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		VehicleClass[ i ].Group		= atoi(row[ ServerClass::Vehicle::vehiclesClassRows::category ]);
		VehicleClass[ i ].Gear		= atoi(row[ ServerClass::Vehicle::vehiclesClassRows::gear ]);
		VehicleClass[ i ].Power		= atoi(row[ ServerClass::Vehicle::vehiclesClassRows::power ]);
		VehicleClass[ i ].Speed		= atoi(row[ ServerClass::Vehicle::vehiclesClassRows::speed ]);
		//--------------------------------------------------------------------------------------------
		strcpy(VehicleClass[ i ].Name, row[ ServerClass::Vehicle::vehiclesClassRows::name ]);
		i++;
	}
	logprintf("[������� �������]: \t���� ���������� ������� ���������� - %d", i);
}
//--------------------------------------------------------
void cClass::loadPlayerClass()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM `class_Players` LIMIT 300");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while ((row = mysql_fetch_row(result)))
	{
		//-------------------------------------
		PlayerClass[ i ].cSkin		= atoi(row[ ServerClass::Player::playerClassRows::skin]);
		PlayerClass[ i ].cRace		= atoi(row[ ServerClass::Player::playerClassRows::race ]);
		PlayerClass[ i ].cNation	= atoi(row[ ServerClass::Player::playerClassRows::nation ]);
		PlayerClass[ i ].cSex		=(atoi(row[ ServerClass::Player::playerClassRows::sex])) ? ( true ) : ( false );
		PlayerClass[ i ].cPower		= atoi(row[ ServerClass::Player::playerClassRows::power ]);
		PlayerClass[ i ].cSpeed		= atoi(row[ ServerClass::Player::playerClassRows::speed ]);
		PlayerClass[ i ].cAgility	= atoi(row[ ServerClass::Player::playerClassRows::agility ]);
		//-------------------------------------
		//AddPlayerClass(PlayerClass[i].cSkin, DEFAULT_SPAWN, 0.0f, 0, 0, 0, 0, 0, 0);
		i++;
	}
	//------------------------------------------------------------
	logprintf("[������� �������]: \t���� ���������� ������� ������� - %d", i);
}
//-------------------------------------------------------------------------------------------
void cClass::fixText(char * text, int size)
{
	for (int i = 0; i != size; ++i)
	{
		switch (text[i])
		{
		case '�': text[i] = 'a';
			break;
		case '�': text[i] = 'A';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'e';
			break;
		case '�': text[i] = 'E';
			break;
		case '�': text[i] = 'e';
			break;
		case '�': text[i] = 'E';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'k';
			break;
		case '�': text[i] = 'K';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'M';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'H';
			break;
		case '�': text[i] = 'o';
			break;
		case '�': text[i] = 'O';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'p';
			break;
		case '�': text[i] = 'P';
			break;
		case '�': text[i] = 'c';
			break;
		case '�': text[i] = 'C';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'y';
			break;
		case '�': text[i] = 'Y';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = 'x';
			break;
		case '�': text[i] = 'X';
			break;
		case '�': text[i] = '�'; // 160
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '�': text[i] = '�';
			break;
		case '*': text[i] = ']';
			break;
		}
	}
}