#include "main.h"


//--------------------------------------------------------
struct pClass PlayerClass[MAX_CLASES] = { { 0, 0 } };
struct vClass VehicleClass[ VEH_CLASES ] = { { 0, 0 } };
struct kgText kgPlayerText[MAX_PLAYERS][16];
std::mutex keyGameMutex;
//--------------------------------------------------------
void cClass::loadVehicleClass()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	safe_query(con, "SELECT * FROM class_Vehicles ORDER BY id LIMIT 212");
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
	safe_query(con, "SELECT * FROM `class_Players` LIMIT 300");
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
	for (int i = 0; i != strlen(text); ++i)
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

//sql functions
bool cClass::sqlSetInt(const char * table, const char * field, const int value, const int id)
{
	char localQuery[96];
	sprintf(localQuery, "UPDATE `%s` SET `%s` = %d WHERE id = %d", table, field, value, id);
	if ( safe_query(con, localQuery) ) return true;
	return false;
}

bool cClass::sqlSetFloat(const char * table, const char * field, const float value, const int id)
{
	char localQuery[96];
	sprintf(localQuery, "UPDATE `%s` SET `%s` = %f WHERE id = %d", table, field, value, id);
	if ( safe_query(con, localQuery) ) return true;
	return false;
}

bool cClass::sqlSetString(const char * table, const char * field, const char * value, const int id)
{
	char localQuery[120];
	sprintf(localQuery, "UPDATE `%s` SET `%s` = '%s' WHERE id = %d", table, field, value, id);
	mysql_real_escape_string(con, localQuery, localQuery, 120);
	if ( safe_query(con, localQuery) ) return true;
	return false;
}

//Mini-Game lowrider style
void cClass::keyGame(const int u)
{
	keyGameMutex.lock();

	Player[u].isKeyGame = true;

	//char msg[144];

	kgPlayerText[u][0].tid = CreatePlayerTextDraw(u, 280.000000, 250.000000, "LD_BEAT:cring");
	PlayerTextDrawAlignment(u, kgPlayerText[u][0].tid, 2);
	PlayerTextDrawBackgroundColor(u, kgPlayerText[u][0].tid, 255);
	PlayerTextDrawFont(u, kgPlayerText[u][0].tid, 4);
	PlayerTextDrawLetterSize(u, kgPlayerText[u][0].tid, 0.500000, 1.000000);
	PlayerTextDrawColor(u, kgPlayerText[u][0].tid, -1);
	PlayerTextDrawSetOutline(u, kgPlayerText[u][0].tid, 0);
	PlayerTextDrawSetProportional(u, kgPlayerText[u][0].tid, 1);
	PlayerTextDrawSetShadow(u, kgPlayerText[u][0].tid, 1);
	PlayerTextDrawUseBox(u, kgPlayerText[u][0].tid, 1);
	PlayerTextDrawBoxColor(u, kgPlayerText[u][0].tid, 255);
	PlayerTextDrawTextSize(u, kgPlayerText[u][0].tid, 80.000000, 80.000000);
	PlayerTextDrawSetSelectable(u, kgPlayerText[u][0].tid, 0);
	PlayerTextDrawShow(u, kgPlayerText[u][0].tid);

	keyGameMutex.unlock();

	for ( int t = 1; t < 12; t++ )
	{
		keyGameMutex.lock();
		kgPlayerText[u][t].y = 274.0f;
		kgPlayerText[u][t].x = 450.0f + (80.0f * t);
		kgPlayerText[u][t].key = rand() % 8;
		kgPlayerText[u][t].alpha = 0;

		kgPlayerText[u][t].tid = CreatePlayerTextDraw(u, kgPlayerText[u][t].x, kgPlayerText[u][t].y, kgKeys[kgPlayerText[u][t].key]);
		PlayerTextDrawAlignment(u, kgPlayerText[u][t].tid, 2);
		PlayerTextDrawBackgroundColor(u, kgPlayerText[u][t].tid, 0);
		PlayerTextDrawFont(u, kgPlayerText[u][t].tid, 4);
		PlayerTextDrawLetterSize(u, kgPlayerText[u][t].tid, 0.500000, 1.000000);
		PlayerTextDrawColor(u, kgPlayerText[u][t].tid, tocolor(255, 255, 255, kgPlayerText[u][t].alpha));
		PlayerTextDrawSetOutline(u, kgPlayerText[u][t].tid, 0);
		PlayerTextDrawSetProportional(u, kgPlayerText[u][t].tid, 1);
		PlayerTextDrawSetShadow(u, kgPlayerText[u][t].tid, 1);
		PlayerTextDrawUseBox(u, kgPlayerText[u][t].tid, 1);
		PlayerTextDrawBoxColor(u, kgPlayerText[u][t].tid, 255);
		PlayerTextDrawTextSize(u, kgPlayerText[u][t].tid, 30.000000, 30.000000);
		PlayerTextDrawSetSelectable(u, kgPlayerText[u][t].tid, 0);
		keyGameMutex.unlock();
	}

	

	//300.000000, 270.000000
	for ( int i = 0; i < 5000; i++ )
	{
		keyGameMutex.lock();
		for ( int t = 1; t < 12; t++ )
		{
			if ( kgPlayerText[u][t].x < 100.0f )
			{
				kgPlayerText[u][t].x = 450.0f + (80.0f * t);
				kgPlayerText[u][t].key = rand() % 8;
			}
			else if ( kgPlayerText[u][t].x == 290.0f)
			{
				Player[u].kgUD = 0;
				Player[u].kgLR = 0;
				//SendClientMessage(u, -1, "Current key: null");
			}
			else if ( kgPlayerText[u][t].x == 320.0f)
			{
				if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_DOWN )
				{
					Player[u].kgUD = 128;
					Player[u].kgLR = 0;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_DOWNLEFT )
				{
					Player[u].kgUD = 128;
					Player[u].kgLR = -128;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_DOWNRIGHT )
				{
					Player[u].kgUD = 128;
					Player[u].kgLR = 128;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_LEFT)
				{
					Player[u].kgUD = 0;
					Player[u].kgLR = -128;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_RIGHT )
				{
					Player[u].kgUD = 0;
					Player[u].kgLR = 128;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_UP )
				{
					Player[u].kgUD = -128;
					Player[u].kgLR = 0;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_UPLEFT )
				{
					Player[u].kgUD = -128;
					Player[u].kgLR = -128;
				}
				else if ( kgPlayerText[u][t].key == kgKeys::KG_KEY_UPRIGHT )
				{
					Player[u].kgUD = -128;
					Player[u].kgLR = 128;
				}
				//sprintf(msg, "Current key: %s", kgKeys[kgPlayerText[u][t].key]);
				//SendClientMessage(u, -1, msg);
			}
			else if ( kgPlayerText[u][t].x < 430.0f && kgPlayerText[u][t].x > 300.5f)
			{
				if ( kgPlayerText[u][t].alpha < 255 )
				{
					kgPlayerText[u][t].alpha += 1;
				}
			}
			else if ( kgPlayerText[u][t].x < 298.0f )
			{
				if ( kgPlayerText[u][t].alpha > 0 )
				{
					kgPlayerText[u][t].alpha -= 1;
				}
			}
			kgPlayerText[u][t].x -= 0.5f;
			PlayerTextDrawDestroy(u, kgPlayerText[u][t].tid);
			kgPlayerText[u][t].tid = CreatePlayerTextDraw(u, kgPlayerText[u][t].x, kgPlayerText[u][t].y, kgKeys[kgPlayerText[u][t].key]);
			PlayerTextDrawAlignment(u, kgPlayerText[u][t].tid, 2);
			PlayerTextDrawBackgroundColor(u, kgPlayerText[u][t].tid, 0);
			PlayerTextDrawFont(u, kgPlayerText[u][t].tid, 4);
			PlayerTextDrawLetterSize(u, kgPlayerText[u][t].tid, 0.500000, 1.000000);
			PlayerTextDrawColor(u, kgPlayerText[u][t].tid, tocolor(255, 255, 255, kgPlayerText[u][t].alpha));
			PlayerTextDrawSetOutline(u, kgPlayerText[u][t].tid, 0);
			PlayerTextDrawSetProportional(u, kgPlayerText[u][t].tid, 1);
			PlayerTextDrawSetShadow(u, kgPlayerText[u][t].tid, 1);
			PlayerTextDrawUseBox(u, kgPlayerText[u][t].tid, 1);
			PlayerTextDrawBoxColor(u, kgPlayerText[u][t].tid, 255);
			PlayerTextDrawTextSize(u, kgPlayerText[u][t].tid, 30.000000, 30.000000);
			PlayerTextDrawSetSelectable(u, kgPlayerText[u][t].tid, 0);
			PlayerTextDrawShow(u, kgPlayerText[u][t].tid);
		}
		keyGameMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	keyGameMutex.lock();
	Player[u].isKeyGame = false;
	keyGameMutex.unlock();

	for ( int i = 0; i < 256; i++ )
	{
		keyGameMutex.lock();
		for ( int t = 0; t < 12; t++ )
		{
			if ( kgPlayerText[u][t].alpha > 0 ) kgPlayerText[u][t].alpha -= 1;
			PlayerTextDrawHide(u, kgPlayerText[u][t].tid);
			PlayerTextDrawColor(u, kgPlayerText[u][t].tid, tocolor(255, 255, 255, kgPlayerText[u][t].alpha));
			if ( t == 0 ) PlayerTextDrawBackgroundColor(u, kgPlayerText[u][0].tid, tocolor(0, 0, 0, kgPlayerText[u][t].alpha));
			PlayerTextDrawShow(u, kgPlayerText[u][t].tid);
		}
		keyGameMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	keyGameMutex.lock();

	for ( int t = 0; t < 12; t++ )
	{
		PlayerTextDrawDestroy(u, kgPlayerText[u][t].tid);
	}

	GameTextForPlayer(u, "~y~MINI-GAME DONE!", 3000, 3);

	keyGameMutex.unlock();
}

void cClass::updateKeyGame(const int u)
{
	keyGameMutex.lock();

	int key;
	int lr;
	int ud;

	GetPlayerKeys(u, &key, &ud, &lr);

	if ( Player[u].kgLR == 0 && Player[u].kgUD == 0)
	{
		
	}
	else
	{
		if ( lr == 0 && ud == 0 )
		{
			
		}
		else
		{
			if ( lr == Player[u].kgLR && ud == Player[u].kgUD)
			{
				GameTextForPlayer(u, "~g~GOOD", 1000, 3);
			}
			else
			{
				GameTextForPlayer(u, "~r~BAD", 1000, 3);
			}
			Player[u].kgLR = 0;
			Player[u].kgUD = 0;
		}
	}

	keyGameMutex.unlock();
}