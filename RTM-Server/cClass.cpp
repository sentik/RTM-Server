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
	logprintf("[—истема  лассов]: \tЅыло загруженно классов транспорта - %d", i);
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
	logprintf("[—истема  лассов]: \tЅыло загруженно классов игроков - %d", i);
}
//-------------------------------------------------------------------------------------------
void cClass::fixText(char * text, int size)
{
	for (int i = 0; i != size; ++i)
	{
		switch (text[i])
		{
		case 'а': text[i] = 'a';
			break;
		case 'ј': text[i] = 'A';
			break;
		case 'б': text[i] = 'Ч';
			break;
		case 'Ѕ': text[i] = 'А';
			break;
		case 'в': text[i] = 'Ґ';
			break;
		case '¬': text[i] = 'Л';
			break;
		case 'г': text[i] = 'Щ';
			break;
		case '√': text[i] = 'В';
			break;
		case 'д': text[i] = 'Ъ';
			break;
		case 'ƒ': text[i] = 'Г';
			break;
		case 'е': text[i] = 'e';
			break;
		case '≈': text[i] = 'E';
			break;
		case 'Є': text[i] = 'e';
			break;
		case '®': text[i] = 'E';
			break;
		case 'ж': text[i] = 'Ы';
			break;
		case '∆': text[i] = 'Д';
			break;
		case 'з': text[i] = 'Я';
			break;
		case '«': text[i] = 'И';
			break;
		case 'и': text[i] = 'Ь';
			break;
		case '»': text[i] = 'Е';
			break;
		case 'й': text[i] = 'Э';
			break;
		case '…': text[i] = 'Ж';
			break;
		case 'к': text[i] = 'k';
			break;
		case ' ': text[i] = 'K';
			break;
		case 'л': text[i] = 'Ю';
			break;
		case 'Ћ': text[i] = 'З';
			break;
		case 'м': text[i] = 'ѓ';
			break;
		case 'ћ': text[i] = 'M';
			break;
		case 'н': text[i] = 'Ѓ';
			break;
		case 'Ќ': text[i] = 'H';
			break;
		case 'о': text[i] = 'o';
			break;
		case 'ќ': text[i] = 'O';
			break;
		case 'п': text[i] = '£';
			break;
		case 'ѕ': text[i] = 'М';
			break;
		case 'р': text[i] = 'p';
			break;
		case '–': text[i] = 'P';
			break;
		case 'с': text[i] = 'c';
			break;
		case '—': text[i] = 'C';
			break;
		case 'т': text[i] = '¶';
			break;
		case '“': text[i] = 'П';
			break;
		case 'у': text[i] = 'y';
			break;
		case '”': text[i] = 'Y';
			break;
		case 'ф': text[i] = 'Ш';
			break;
		case '‘': text[i] = 'Б';
			break;
		case 'х': text[i] = 'x';
			break;
		case '’': text[i] = 'X';
			break;
		case 'ц': text[i] = '†'; // 160
			break;
		case '÷': text[i] = 'Й';
			break;
		case 'ч': text[i] = '§';
			break;
		case '„': text[i] = 'Н';
			break;
		case 'ш': text[i] = '•';
			break;
		case 'Ў': text[i] = 'О';
			break;
		case 'щ': text[i] = '°';
			break;
		case 'ў': text[i] = 'К';
			break;
		case 'ь': text[i] = '©';
			break;
		case '№': text[i] = 'Т';
			break;
		case 'ъ': text[i] = 'І';
			break;
		case 'Џ': text[i] = 'Р';
			break;
		case 'ы': text[i] = '®';
			break;
		case 'џ': text[i] = 'С';
			break;
		case 'э': text[i] = '™';
			break;
		case 'Ё': text[i] = 'У';
			break;
		case 'ю': text[i] = 'Ђ';
			break;
		case 'ё': text[i] = 'Ф';
			break;
		case '€': text[i] = 'ђ';
			break;
		case 'я': text[i] = 'Х';
			break;
		case '*': text[i] = ']';
			break;
		}
	}
}