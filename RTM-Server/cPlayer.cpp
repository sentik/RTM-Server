#include "main.h"

/*
Рефакторинг OnDialogRespone;
Добавлен CallBack OnDLG для банка;
Исправлен баг с db идом игрока
*/

struct pChar PlayerChar[MAX_PLAYERS][MAX_CHARS] = { { 0, 0 } };
struct rChar RegChar[MAX_PLAYERS] = { { 0, 0 } };
struct pInfo Player[MAX_PLAYERS] = { { 0, 0 } };
int drawPlayerChar[20];
std::mutex mutexUpdate;

void cPlayer::update()
{
	mutexUpdate.lock();
	//-------------------------------------------------
	const bool isTwo = uTime % 2 == 0;		//Кратность 2  UNIX-Time
	const bool isFive = uTime % 5 == 0;		//Кратность 5  UNIX-Time
	const bool isTen = isTwo & isFive;		//Кратность 10 UNIX-Time 
	//-------------------------------------------------

	/*time_t rawtime;
	tm* timeinfo;
	char buffer[48];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	sprintf(buffer, "~w~%02d~p~.~w~%02d~p~.~w~%04d %02d~p~:~w~%02d~p~:~w~%02d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	*/


	time_t rawtime;
	struct tm * timeinfo;
	char buffer[ 144 ];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 144, "~w~%d~p~.~w~%m~p~.~w~%Y %H~p~:~w~%M~p~:~w~%S", timeinfo);
	TextDrawSetString(drawPlayerChar[HEADER_TIME], buffer);

	mutexUpdate.unlock();

	//-------------------------------------------------
	for (int i = 0; i < 10; i++)
	{
		if (Player[ i ].isLogged == false)
		{

			/*if ( Player[i].inIndex == 5656) continue;
			//if (Player[ i ].pClass == 0)
			{
				if (IsPlayerNPC(i))
				{
					if (Player[ i ].pCarid == 0)
					{
						char name[ 16 ];
						GetPlayerName(i, name);

						//Получаем аттач к ид игрока
						strcpy(name, string(name).substr(6, 9).c_str());
						const int p = atoi(name);
						//----------------------------------------------
						//Аттач бота к игроку
						Player[ p ].inIndex = i;
						//----------------------------------------------
						//Аттач поезда к боту
						const int veh = AddStaticVehicle(538, 1759.5978, -1953.7347, 13.121, 270, 1, 1);
						Player[ i ].pCarid = veh;
						PutPlayerInVehicle(i, veh, 0);
						logprintf("player: %d || bot: %d", p, i);
					}
					//----------------------------------------------
				}
			}
			//----------------------------------------------------
			if (isFive)
			{
				if (IsPlayerNPC(Player[i].inIndex))
				{
					cPlayer::Intro::cIntro::updateIntro(i);
					continue;
				}
			}*/
			continue;
		}
		/*
		float hp;
		float ar;
		GetPlayerHealth(i, &hp);
		GetPlayerArmour(i, &ar);
		sprintf(buffer, "(%d) %s %s [{B7FF00}%.2f%% {DCDCDC}%.2f%%{FFFFFF}]", i, Player[ i ].uName, Player[ i ].sName, hp, ar);
		StreamerCall::Native::UpdateDynamic3DTextLabelText(Player[i].pBar, -1, buffer);
		*/

		mutexUpdate.lock();

		if ( extrimeDraws::tutorial::func::tutDraws.size() >= 1 )
		{
			for ( auto id = extrimeDraws::tutorial::func::tutDraws.begin(); id < extrimeDraws::tutorial::func::tutDraws.end(); ++id )
			{
				if ( id->player == INVALID_PLAYER_ID )
				{
					TextDraw(id->draws.body).Destroy();
					TextDraw(id->draws.close).Destroy();
					TextDraw(id->draws.header).Destroy();
					TextDraw(id->draws.text).Destroy();

					extrimeDraws::tutorial::func::tutDraws.erase(id);
				}
				else
				{
					if ( id->closetime <= uTime && id->closetime > 0 )
					{
						PlayerTextDrawDestroy(id->player, id->draws.body);
						PlayerTextDrawDestroy(id->player, id->draws.close);
						PlayerTextDrawDestroy(id->player, id->draws.header);
						PlayerTextDrawDestroy(id->player, id->draws.text);

						extrimeDraws::tutorial::func::tutDraws.erase(id);
					}
				}
			}
		}

		if (Player[ i ].isAction == PlayerAction::ACTION_FREZSETPOS)
		{
			Player[ i ].isAction = PlayerAction::ACTION_NONE;
			TogglePlayerControllable(i, 1);
		}
		if (isTwo)
		{
			if (Player[ i ].isAction == PlayerAction::ACTION_AUTH_PLAYER)
			{

			}
			//==========================================
			else if (Player[ i ].isAction != PlayerAction::ACTION_Death)
			{
				GetPlayerPos(i, &Player[ i ].pPosX, &Player[ i ].pPosY, &Player[ i ].pPosZ);
				GetPlayerFacingAngle(i, &Player[ i ].pPosR);
				Player[ i ].pPosW = GetPlayerVirtualWorld(i);
				Player[ i ].pPosI = GetPlayerInterior(i);
			}
			//==========================================
		}
		if (isTen)
		{
			//==========================================
			if (Player[ i ].isAction == PlayerAction::ACTION_AUTOSHOP)
			{
				Properties::Shops::ShopVehicle::viewCam(i);
			}
			else if (Player[i].isAction == PlayerAction::ACTION_MINERGAME)
			{
				if (Player[i].minerDraw[1] != INVALID_TEXT_DRAW)
				{
					for (int t = 0; t < 20; t++)
					{
						PlayerTextDrawDestroy(i, Player[i].minerDraw[t]);
					}
				}
				CancelSelectTextDraw(i);
				ClearAnimations(i, true);
				Player[i].isAction = PlayerAction::ACTION_NONE;
				if (Player[i].inType == 1) 
					SetPlayerCheckpoint(i, MINER_SH1_CHECKPOS, 4.5f);
				else
					SetPlayerCheckpoint(i, MINER_SH2_CHECKPOS, 4.5f);
			}
			else if (Player[i].isAction == PlayerAction::ACTION_FELGAME)
			{
				if (Player[i].minerDraw[1] != INVALID_TEXT_DRAW)
				{
					for (int t = 0; t < 20; t++)
					{
						PlayerTextDrawDestroy(i, Player[i].minerDraw[t]);
					}
				}
				CancelSelectTextDraw(i);
				ClearAnimations(i, true);
				Player[i].isAction = PlayerAction::ACTION_FELJOB;
			}
			else
			{
				cPlayer::updatePos(i);
			}
		}
		mutexUpdate.unlock();
	}
}

//TODO: Проверить наличие аккаунта
int cPlayer::checkLogin(const char* login)
{
	char qqq[ 144 ];
	sprintf(qqq, "SELECT id FROM player_Accounts WHERE login ='%s' LIMIT 1", login);
	if (safe_query(con, qqq) == 0)
	{
		MYSQL_RES *result = mysql_store_result(con);
		if (mysql_num_rows(result) == 1)
		{
			MYSQL_ROW row = mysql_fetch_row(result);
			return atoi(row[ 0 ]);
		}
	}
	return 0;
}

//TODO: Проверить логин
bool cPlayer::checkPass(int i, const char* passw)
{
	char qqq[ 144 ];
	bool res = false;
	sprintf(qqq, "SELECT NULL FROM player_Accounts WHERE id = '%d' AND passw = MD5(CONCAT('%c', PASSWORD('%s'), '%c'))", i, passw[ 0 ], passw, passw[ strlen(passw) - 1 ]);
	if (safe_query(con, qqq)==0)
	{
		MYSQL_RES *result = mysql_store_result(con);
		res = ( mysql_num_rows(result) == 1 ) ? ( true ) : ( false );
		mysql_free_result(result);
	}
	else res = false;
	return res;
}

//TODO: Зарегестрировать аккаунт
int cPlayer::regPlayer(const char* login, const char* passw)
{
	char qqq[ 144 ];
	sprintf(qqq, "INSERT INTO player_Accounts SET `login` = '%s', passw = MD5(CONCAT('%c', PASSWORD('%s'), '%c'))", login, passw[ 0 ], passw, passw[ strlen(passw) - 1 ]);
	safe_query(con, qqq);
	return mysql_insert_id(con);
}

//TODO: Зарегестрировать персонажа
int cPlayer::regChar(const int u)
{
	char qqq[ 144 ];
	sprintf(qqq, "INSERT INTO player_Character (owner, uname, sname, money, class) VALUES ('%d', '%s', '%s', '%f', '%d')",
		Player[u].pDB, Player[u].uName, Player[u].sName, Player[u].pMoney, Player[u].pClass);
	safe_query(con, qqq);
	//--------------------------------------------------------------------------------------------------------------------
	Player[u].pPosX = REG_SPAWN_X;
	Player[u].pPosY = REG_SPAWN_Y;
	Player[u].pPosZ = REG_SPAWN_Z;
	Player[u].pPosW = REG_SPAWN_WOR;
	Player[u].pPosI = REG_SPAWN_INT;
	return mysql_insert_id(con);
}

/// <summary>
/// Загрузить персонажа игрока
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::loadPlayerChar(int i, int pers)
{

	int zzz = 0;
	char qqq[ 144 ];
	start:
	//-------------------------------------------------------------------------------------------------------------------
	sprintf(qqq, "SELECT * FROM player_Character  WHERE owner = '%d' AND id = %d  LIMIT 1", Player[ i ].pDB, pers);
	if (safe_query(con, qqq) == 0)
	{
		//-------------------------------------------------------------------------------------------------------------------
		MYSQL_RES *result = mysql_store_result(con);
		//-------------------------------------------------------------------------------------------------------------------
		if (mysql_num_rows(result) == 1)
		{
			MYSQL_ROW row = mysql_fetch_row(result);
			Player[ i ].pDB = atoi(row[ PlayerRows::plDB ]);
			Player[ i ].pMoney = atof(row[ PlayerRows::plMoney ]);
			Player[ i ].pClass = atoi(row[ PlayerRows::plClass ]);
			Player[ i ].pPosX = atof(row[ PlayerRows::plPosX ]);
			Player[ i ].pPosY = atof(row[ PlayerRows::plPosY ]);
			Player[ i ].pPosZ = atof(row[ PlayerRows::plPosZ ]);
			Player[ i ].pPosR = atof(row[ PlayerRows::plPosR ]);
			Player[ i ].pPosI = atoi(row[ PlayerRows::plPosI ]);
			Player[ i ].pPosW = atoi(row[ PlayerRows::plPosW ]);
			Player[i].pJob1 = atoi(row[PlayerRows::plJob1]);
			Player[i].pJob2 = atoi(row[PlayerRows::plJob2]);
			//------------------------------------------------
			Player[ i ].AC.Health = atof(row[ PlayerRows::plHealth ]);
			Player[ i ].AC.Armour = atof(row[ PlayerRows::plArmour ]);
			if(Player[ i ].AC.Health < 5) Player[ i ].AC.Health = 5;
			//------------------------------------------------
			strcpy(Player[ i ].uName, row[ PlayerRows::pluName ]);
			strcpy(Player[ i ].sName, row[ PlayerRows::plsName ]);
			//------------------------------------------------
			GivePlayerMoney(i, Player[ i ].pMoney);
			cPlayer::setClassSkin(i);
			//------------------------------------------------
			world::Vehicles::loadPlayerVehs(i);
		}
		mysql_free_result(result);
	}
	else
	{
		zzz++;
		if (zzz == 10) SendClientMessage(i, -1, "Произошла ошибка при загрузке списка персонажей! Сообщите об этом администрации...");
		else 		goto start;
	}
}

/// <summary>
/// Выгрузить список персонажей
/// <param name="i">* Ид игрока</param>
/// </summary>
void  cPlayer::unloadChars(int i)
{
	TextDrawHideForPlayer(i, drawPlayerChar[REG_BG]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_HEADER]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_BUTTON_BG]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_LEFT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_SELECT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_RIGHT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_CREATE]);
	for (int c = 0; c < MAX_CHARS; c++)
	{
		//------------------------------------------------------
		PlayerTextDrawDestroy(i, PlayerChar[i][c].cUserus);
		PlayerTextDrawDestroy(i, PlayerChar[i][c].cMoney);
		//------------------------------------------------------
//		PlayerChar[i][c] = { { 0 } };
	}
}

/// <summary>
/// Загрузить список персонажей
/// <param name="i">* Ид игрока</param>
/// </summary>
bool cPlayer::loadChars(int i)
{
	int c = 0;
	char tmp[32];
	MYSQL_ROW row;
	sprintf(query, "SELECT id, `class`, money, uname, sname  FROM player_Character WHERE owner = '%d' LIMIT %d", Player[i].pDB, MAX_CHARS), safe_query(con, query);
	//---------------------------------------------
	MYSQL_RES *result = mysql_store_result(con);
	int num_fields = mysql_num_rows(result);
	//---------------------------------------------
	Player[i].isAction = PlayerAction::ACTION_AUTH_PLAYER;
	//---------------------------------------------
	TextDrawShowForPlayer(i, drawPlayerChar[REG_BG]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_HEADER]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_BUTTON_BG]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_CREATE]);
	//---------------------------------------------
	while ((row = mysql_fetch_row(result)))
	{
		PlayerChar[i][c].pDB = atoi(row[0]);
		PlayerChar[i][c].pClass = atoi(row[1]);

		PlayerChar[i][c].pMoney = atof(row[2]);
		strcpy(PlayerChar[i][c].uName, row[3]);
		strcpy(PlayerChar[i][c].sName, row[4]);
		//------------------------------------------------------------------------------------
		cClass::fixText(PlayerChar[i][c].uName, strlen(PlayerChar[i][c].uName));
		cClass::fixText(PlayerChar[i][c].sName, strlen(PlayerChar[i][c].sName));
		sprintf(tmp, "%s %s %d|%d", PlayerChar[ i ][ c ].uName, PlayerChar[ i ][ c ].sName, PlayerChar[ i ][ c ].pDB, PlayerChar[ i ][ c ].pClass);
		//------------------------------------------------------------------------------------
		PlayerChar[i][c].cUserus = CreatePlayerTextDraw(i, 35.0f, 15 * c + 170.0f, tmp);
		PlayerTextDrawBackgroundColor(i, PlayerChar[i][c].cUserus, 80);
		PlayerTextDrawFont(i, PlayerChar[i][c].cUserus, 1);
		PlayerTextDrawLetterSize(i, PlayerChar[i][c].cUserus, 0.30f, 1.0f);
		PlayerTextDrawColor(i, PlayerChar[i][c].cUserus, -1);
		PlayerTextDrawSetOutline(i, PlayerChar[i][c].cUserus, 1);
		PlayerTextDrawSetProportional(i, PlayerChar[i][c].cUserus, 1);
		PlayerTextDrawUseBox(i, PlayerChar[i][c].cUserus, 1);
		PlayerTextDrawBoxColor(i, PlayerChar[i][c].cUserus, -1778346416);
		PlayerTextDrawTextSize(i, PlayerChar[i][c].cUserus, 175.0f, 10.0f);
		//------------------------------------------------------------------------------------
		sprintf(tmp, "~g~ %.2f", PlayerChar[i][c].pMoney);
		//------------------------------------------------------------------------------------
		PlayerChar[i][c].cMoney = CreatePlayerTextDraw(i, 219.0, 15 * c + 170.0f, tmp);
		PlayerTextDrawAlignment(i, PlayerChar[i][c].cMoney, 2);
		PlayerTextDrawBackgroundColor(i, PlayerChar[i][c].cMoney, 80);
		PlayerTextDrawFont(i, PlayerChar[i][c].cMoney, 1);
		PlayerTextDrawLetterSize(i, PlayerChar[i][c].cMoney, 0.30f, 1.0f);
		PlayerTextDrawColor(i, PlayerChar[i][c].cMoney, -1);
		PlayerTextDrawSetOutline(i, PlayerChar[i][c].cMoney, 1);
		PlayerTextDrawSetProportional(i, PlayerChar[i][c].cMoney, 1);
		PlayerTextDrawUseBox(i, PlayerChar[i][c].cMoney, 1);
		PlayerTextDrawBoxColor(i, PlayerChar[i][c].cMoney, -1778346416);
		PlayerTextDrawTextSize(i, PlayerChar[i][c].cMoney, 10.0f, 80.0f);
		//------------------------------------------------------------------------------------
		PlayerTextDrawSetSelectable(i, PlayerChar[i][c].cUserus, true);
		PlayerTextDrawSetSelectable(i, PlayerChar[i][c].cMoney, false);
		PlayerTextDrawShow(i, PlayerChar[i][c].cUserus);
		PlayerTextDrawShow(i, PlayerChar[i][c].cMoney);
		c++;
	}
	SelectTextDraw(i, SELECT_COLORUS);
	//---------------------------------------------
	mysql_free_result(result);
	//---------------------------------------------
	return (num_fields > 0) ? (true) : (false);
}


/// <summary>
/// Установить скин игрока в соответствии с классом
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::setClassSkin(int p)
{
	SetPlayerSkin(p, PlayerClass[Player[p].pClass].cSkin);
	sprintf(query, "class: %d || skin: %d", Player[p].pClass, PlayerClass[Player[p].pClass].cSkin);
	SendClientMessage(p, -1, query);
}


/// <summary>
/// Установить скин игрока в соответствии с классом
/// <param name="i">* Ид игрока</param>
/// <param name="c">* Ид класса</param>
/// </summary>
void cPlayer::setRegClassSkin(int p, char c)
{
	SetPlayerVirtualWorld(p, p);
	SetPlayerSkin(p, PlayerClass[PlayerChar[p][c].pClass].cSkin);
}

/// <summary>
/// Выбор класса игрока при регистрации
/// <param name="i">* Ид игрока</param>
/// <param name="c">* Ид класса</param>
/// </summary>
void cPlayer::preSelectClass(int i, int c)
{
	logprintf("Called %d/%d class", c, MAX_CLASES);
	PlayerTextDrawSetString(i, RegChar[i].rSpeed[1], perkCalculate(PlayerClass[c].cSpeed).c_str());
	PlayerTextDrawSetString(i, RegChar[i].rPower[1], perkCalculate(PlayerClass[c].cPower).c_str());
	PlayerTextDrawSetString(i, RegChar[i].rAgility[1], perkCalculate(PlayerClass[c].cAgility).c_str());
	PlayerTextDrawSetString(i, RegChar[i].rRace, RaceList[PlayerClass[c].cRace]);
	PlayerTextDrawSetString(i, RegChar[i].rNation, Natioins[PlayerClass[c].cNation]);
	PlayerTextDrawSetString(i, RegChar[i].rSex, SexArray[PlayerClass[c].cSex]);
	SetPlayerSkin(i, PlayerClass[c].cSkin);
}

/// <summary>
/// Удалить текстдравы выбора класса
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::destRegDraws(const int i)
{

	PlayerTextDrawDestroy(i, RegChar[i].rSpeed[0]);
	PlayerTextDrawDestroy(i, RegChar[i].rSpeed[1]);
	//------------------------------------------
	PlayerTextDrawDestroy(i, RegChar[i].rPower[0]);
	PlayerTextDrawDestroy(i, RegChar[i].rPower[1]);
	//------------------------------------------
	PlayerTextDrawDestroy(i, RegChar[i].rAgility[0]);
	PlayerTextDrawDestroy(i, RegChar[i].rAgility[1]);
	//------------------------------------------
	PlayerTextDrawDestroy(i, RegChar[i].rRace);
	PlayerTextDrawDestroy(i, RegChar[i].rNation);
	PlayerTextDrawDestroy(i, RegChar[i].rSex);
	//RegChar[i] = { { 0 } };
}

/// <summary>
/// Скрыть текстдравы регистрации
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::hideRegDraws(const int i)
{
	PlayerTextDrawHide(i, RegChar[i].rSpeed[0]);
	PlayerTextDrawHide(i, RegChar[i].rSpeed[1]);
	//------------------------------------------
	PlayerTextDrawHide(i, RegChar[i].rPower[0]);
	PlayerTextDrawHide(i, RegChar[i].rPower[1]);
	//------------------------------------------
	PlayerTextDrawHide(i, RegChar[i].rAgility[0]);
	PlayerTextDrawHide(i, RegChar[i].rAgility[1]);
	//------------------------------------------
	PlayerTextDrawHide(i, RegChar[i].rRace);
	PlayerTextDrawHide(i, RegChar[i].rNation);
	PlayerTextDrawHide(i, RegChar[i].rSex);
	//------------------------------------------
	TextDrawHideForPlayer(i, drawPlayerChar[REG_HEADER_CLASS]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_BG]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_LEFT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_RIGHT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_SELECT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_BUTTON_BG]);
}


/// <summary>
/// Заспавнить игрока
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::SpawnChar(const int i)
{
	CancelSelectTextDraw(i);
	TogglePlayerControllable(i, 0);
	Player[i].isAction = PlayerAction::ACTION_FREZSETPOS;
	TogglePlayerSpectating(i, false);
	SetCameraBehindPlayer(i);
	SpawnPlayer(i);
}

/// <summary>
/// Установить позицию игрока
/// <param name="i">* Ид игрока</param>
/// <param name = "x">* Позиция игрока X</param>
/// <param name = "y">* Позиция игрока Yy</param>
/// <param name = "z">* Позиция игрока Z</param>
/// </summary>
void cPlayer::setCharPos(const int i, float x, float y, float z, bool isFreeze = false)
{
	//------------------------------
	Player[i].pPosX = x;
	Player[i].pPosY = y;
	Player[i].pPosZ = z;
	//------------------------------
	SetPlayerPos(i, Player[i].pPosX, Player[i].pPosY, Player[i].pPosZ);
	//------------------------------
	if (isFreeze)
	{
		TogglePlayerControllable(i, false);
		Player[i].isAction = PlayerAction::ACTION_FREZSETPOS;
	}
}
//http://developer.alexanderklimov.ru/articles/xmlcomment.php
/// <summary>
/// Установить угол поворота
/// <param name="i">Ид игрока</param>
/// <param name = "a">Угол поворота</param>
/// </summary>
void cPlayer::setCharAngle(const int i, float a = -369)
{
	Player[i].pPosR = a;
	SetPlayerFacingAngle(i, Player[i].pPosR);
}

/// <summary>
/// Установить интерьер
/// <param name="i">Ид игрока</param>
/// <param name = "interior">Ид интерьера</param>
/// </summary>
void cPlayer::setCharInterior(const int i, const int interior)
{
	Player[i].pPosI = interior;
	SetPlayerInterior(i, Player[i].pPosI);
}

/// <summary>
/// Установить виртуальный мир
/// <param name="i">Ид игрока</param>
/// <param name = "world">Ид виртуального мира</param>
/// </summary>
void cPlayer::setCharWorld(const int i, const int world)
{
	Player[i].pPosW = world;
	SetPlayerVirtualWorld(i, Player[i].pPosW);
}

void cPlayer::camSelectChar(int i)
{
	TogglePlayerSpectating(i, false);
	SpawnPlayer(i);
	SetPlayerPos(i, CREG_SKIN_POS);
	SetPlayerCameraPos(i, CREG_CAMR_POS);
	SetPlayerCameraLookAt(i, CREG_SKIN_POS, CAMERA_MOVE);
}


//TODO: Вывести форму создания персонажа
void cPlayer::showCharMaker(int i)
{
	/*
	TogglePlayerSpectating(i, false);
	SpawnPlayer(i);
	SetPlayerPos(i, CREG_SKIN_POS);
	SetPlayerCameraPos(i, CREG_CAMR_POS);
	SetPlayerCameraLookAt(i, CREG_SKIN_POS, CAMERA_MOVE);*/
	//-------------------------------------------------------------------------------------------------------------
	TextDrawShowForPlayer(i, drawPlayerChar[REG_HEADER_CLASS]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_BG]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_BUTTON_BG]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_LEFT]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_RIGHT]);
	TextDrawShowForPlayer(i, drawPlayerChar[REG_SELECT]);
	TextDrawHideForPlayer(i, drawPlayerChar[REG_CREATE]);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rSpeed[0] = CreatePlayerTextDraw(i, 30.000000f, 170.000000f, strSpeed);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rSpeed[0], 80);
	PlayerTextDrawFont(i, RegChar[i].rSpeed[0], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rSpeed[0], 0.32000f, 1.0000f);
	PlayerTextDrawColor(i, RegChar[i].rSpeed[0], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rSpeed[0], 1);
	PlayerTextDrawSetProportional(i, RegChar[i].rSpeed[0], 1);
	PlayerTextDrawUseBox(i, RegChar[i].rSpeed[0], 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rSpeed[0], -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rSpeed[0], 175.000000f, 0.000000f);
	PlayerTextDrawSetSelectable(i, RegChar[i].rSpeed[0], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rSpeed[1] = CreatePlayerTextDraw(i, 140.000000f, 170.000000f, perkCalculate(10).c_str());
	PlayerTextDrawAlignment(i, RegChar[i].rSpeed[1], 2);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rSpeed[1], 255);
	PlayerTextDrawFont(i, RegChar[i].rSpeed[1], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rSpeed[1], 0.500000f, 1.000000f);
	PlayerTextDrawColor(i, RegChar[i].rSpeed[1], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rSpeed[1], 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rSpeed[1], 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rSpeed[1], 0);
	PlayerTextDrawSetSelectable(i, RegChar[i].rSpeed[1], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rPower[0] = CreatePlayerTextDraw(i, 30.000000f, 185.000000f, strMuscular);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rPower[0], 80);
	PlayerTextDrawFont(i, RegChar[i].rPower[0], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rPower[0], 0.32000f, 1.0000f);
	PlayerTextDrawColor(i, RegChar[i].rPower[0], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rPower[0], 1);
	PlayerTextDrawSetProportional(i, RegChar[i].rPower[0], 1);
	PlayerTextDrawUseBox(i, RegChar[i].rPower[0], 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rPower[0], -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rPower[0], 175.000000f, 0.000000f);
	PlayerTextDrawSetSelectable(i, RegChar[i].rPower[0], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rPower[1] = CreatePlayerTextDraw(i, 140.000000f, 185.000000f, perkCalculate(8).c_str());
	PlayerTextDrawAlignment(i, RegChar[i].rPower[1], 2);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rPower[1], 255);
	PlayerTextDrawFont(i, RegChar[i].rPower[1], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rPower[1], 0.500000f, 1.000000f);
	PlayerTextDrawColor(i, RegChar[i].rPower[1], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rPower[1], 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rPower[1], 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rPower[1], 0);
	PlayerTextDrawSetSelectable(i, RegChar[i].rPower[1], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rAgility[0] = CreatePlayerTextDraw(i, 30.000000f, 200.000000f, strAgility);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rAgility[0], 80);
	PlayerTextDrawFont(i, RegChar[i].rAgility[0], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rAgility[0], 0.32000f, 1.0000f);
	PlayerTextDrawColor(i, RegChar[i].rAgility[0], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rAgility[0], 1);
	PlayerTextDrawSetProportional(i, RegChar[i].rAgility[0], 1);
	PlayerTextDrawUseBox(i, RegChar[i].rAgility[0], 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rAgility[0], -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rAgility[0], 175.000000f, 0.000000f);
	PlayerTextDrawSetSelectable(i, RegChar[i].rAgility[0], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rAgility[1] = CreatePlayerTextDraw(i, 140.000000f, 200.000000f, perkCalculate(8).c_str());
	PlayerTextDrawAlignment(i, RegChar[i].rAgility[1], 2);
	PlayerTextDrawBackgroundColor(i, RegChar[i].rAgility[1], 255);
	PlayerTextDrawFont(i, RegChar[i].rAgility[1], 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rAgility[1], 0.500000f, 1.000000f);
	PlayerTextDrawColor(i, RegChar[i].rAgility[1], -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rAgility[1], 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rAgility[1], 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rAgility[1], 0);
	PlayerTextDrawSetSelectable(i, RegChar[i].rAgility[1], 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rNation = CreatePlayerTextDraw(i, 30.000000, 270.000000, "RACE ~l~EUROPIAN");
	PlayerTextDrawBackgroundColor(i, RegChar[i].rNation, 80);
	PlayerTextDrawFont(i, RegChar[i].rNation, 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rNation, 0.500000, 1.000000);
	PlayerTextDrawColor(i, RegChar[i].rNation, -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rNation, 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rNation, 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rNation, 0);
	PlayerTextDrawUseBox(i, RegChar[i].rNation, 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rNation, -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rNation, 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(i, RegChar[i].rNation, 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rRace = CreatePlayerTextDraw(i, 30.000000, 285.000000, "Nation ~l~American");
	PlayerTextDrawBackgroundColor(i, RegChar[i].rRace, 80);
	PlayerTextDrawFont(i, RegChar[i].rRace, 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rRace, 0.500000, 1.000000);
	PlayerTextDrawColor(i, RegChar[i].rRace, -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rRace, 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rRace, 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rRace, 0);
	PlayerTextDrawUseBox(i, RegChar[i].rRace, 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rRace, -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rRace, 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(i, RegChar[i].rRace, 0);
	//-------------------------------------------------------------------------------------------------------------
	RegChar[i].rSex = CreatePlayerTextDraw(i, 30.000000, 300.000000, "Sex ~l~Male");
	PlayerTextDrawBackgroundColor(i, RegChar[i].rSex, 80);
	PlayerTextDrawFont(i, RegChar[i].rSex, 1);
	PlayerTextDrawLetterSize(i, RegChar[i].rSex, 0.500000, 1.000000);
	PlayerTextDrawColor(i, RegChar[i].rSex, -1);
	PlayerTextDrawSetOutline(i, RegChar[i].rSex, 0);
	PlayerTextDrawSetProportional(i, RegChar[i].rSex, 1);
	PlayerTextDrawSetShadow(i, RegChar[i].rSex, 0);
	PlayerTextDrawUseBox(i, RegChar[i].rSex, 1);
	PlayerTextDrawBoxColor(i, RegChar[i].rSex, -1778346416);
	PlayerTextDrawTextSize(i, RegChar[i].rSex, 175.000000, 0.000000);
	PlayerTextDrawSetSelectable(i, RegChar[i].rSex, 0);
	//-------------------------------------------------------------------------------------------------------------
	Player[i].isAction = PlayerAction::ACTION_NONE;
	PlayerTextDrawShow(i, RegChar[i].rSpeed[0]);
	PlayerTextDrawShow(i, RegChar[i].rPower[0]);
	PlayerTextDrawShow(i, RegChar[i].rAgility[0]);
	//--------------------------------------------
	PlayerTextDrawShow(i, RegChar[i].rSpeed[1]);
	PlayerTextDrawShow(i, RegChar[i].rPower[1]);
	PlayerTextDrawShow(i, RegChar[i].rAgility[1]);
	//--------------------------------------------
	PlayerTextDrawShow(i, RegChar[i].rNation);
	PlayerTextDrawShow(i, RegChar[i].rRace);
	PlayerTextDrawShow(i, RegChar[i].rSex);
	//--------------------------------------------
	SelectTextDraw(i, SELECT_COLORUS);
	cPlayer::preSelectClass(i, 0);
}

bool cPlayer::isRangeOfPoint(int i, float r, float x, float y, float z)
{
	float ra = pow(r, 2);
	if (pow(Player[ i ].pPosZ - z, 2) > ra) return false;
	return pow(Player[ i ].pPosX - x, 2) + pow(Player[ i ].pPosY - y, 2) < ra;
}

bool cPlayer::checkMoney(const int u, float value)
{
	if (Player[ u ].pMoney >= value) return true;
	//=========================================
	char msg[ 128 ];
	//=========================================
	sprintf(msg, "{FFFFFF}К сожаления у вас не хватает: \t\t\t{FF0000}%.2f$\n{FFFFFF}Требуется всего: \t\t\t\t{FF0000}%.2f$", value - Player[ u ].pMoney, value);
	ShowPlayerDialog(u, DIALOG_LIST::DLG_NONE, GUI_MSG, "[Информация]: Недостаточно средств", msg, "Закрыть", "");
	//=========================================
	return false;
}

void cPlayer::givePlayerMoney(const int u, float value)
{
	char msg[80];
	if (value > 0.0f)
	{
		sprintf(msg, "~g~+%.2f", value);
	}
	else
	{
		sprintf(msg, "~r~%.2f", value);
	}
	GameTextForPlayer(u, msg, 500, 1);
	//=============================
	Player[ u ].pMoney += value;
	//=============================
	sprintf(msg, "UPDATE player_Character SET money = '%.2f' WHERE id = '%d'", Player[u].pMoney, Player[u].pDB);
	safe_query(con, msg);
	//=============================
	cPlayer::updateMoney(u);
}

void cPlayer::updateMoney(const int u)
{
	char buff[16];
	sprintf(buff, "%0.02f", Player[u].pMoney);
	PlayerTextDrawSetString(u, Player[u].tCents, buff);
	//=============================
	ResetPlayerMoney(u);
	GivePlayerMoney(u, floor(Player[u].pMoney));
}

void cPlayer::updatePos(const int u)
{
	char qqq[256];
	GetPlayerPos(u, &Player[ u ].pPosX, &Player[ u ].pPosY, &Player[ u ].pPosZ);
	GetPlayerFacingAngle( u, &Player[ u ].pPosR );
	Player[ u ].pPosW = GetPlayerVirtualWorld(u);
	Player[ u ].pPosI = GetPlayerInterior(u);
	//================================================================================
	sprintf(qqq, "UPDATE player_Character SET posx='%.4f', posy='%.4f', posz='%.4f', posr='%.2f', posi='%d', posw='%d', posp='%d', pHP='%.2f' WHERE id = '%d'", 
			Player[ u ].pPosX, Player[ u ].pPosY, Player[ u ].pPosZ, Player[ u ].pPosR, Player[ u ].pPosI, Player[ u ].pPosW, Player[ u ].AC.Health,
			Player[ u ].inIndex, Player[ u ].pDB);
	//================================================================================	
	safe_query(con, qqq);
}


void cPlayer::getPlayerPos(const int i)
{
	GetPlayerPos(i, &Player[ i ].pPosX, &Player[ i ].pPosY, &Player[ i ].pPosZ);
}

bool cPlayer::isPlayerInCube(const int u, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	const float x = Player[u].pPosX;
	const float y = Player[u].pPosY;
	const float z = Player[u].pPosZ;
	//================================================================================
	return (x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ) ? true : false;
}

void cPlayer::giveExp(const int u, const int exp)
{
	char msg[16];
	if (exp > 0)
	{
		sprintf(msg, "~y~+%d EXP", exp);
	}
	else
	{
		sprintf(msg, "~r~%d EXP", exp);
	}
	Player[u].pExp += exp;
	SetPlayerScore(u, Player[u].pExp);
	GameTextForPlayer(u, msg, 3500, 5);
}


void cPlayer::getName(const int playerid, char name[])
{
	sprintf(name, "%s %s", Player[ playerid ].uName, Player[ playerid ].sName);
}

/*void cPlayer::EffectCamera(const int playerid)
{
	static Float:derg;
	new Float:radi = 500 + random(2500);
	new Float:XX = 0 + radi*floatsin(derg, degrees);
	new Float:YY = 0 + radi*floatcos(derg, degrees);
	SetPlayerCameraPos(playerid, XX, YY, 100 + random(100));
	SetPlayerCameraLookAt(playerid, -2500 + random(5000), -2500 + random(5000), -400 + random(600), CAMERA_MOVE);
	derg -= 1.5 + random(10);
	return true;
}*/


void cPlayer::PreloadAnimLib(const int playerid)
{
	ApplyAnimation(playerid, "AIRPORT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "Attractors", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BAR", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BASEBALL", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BD_FIRE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "benchpress", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BF_injection", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKED", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKEH", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKELEAP", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKES", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKEV", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BIKE_DBZ", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BMX", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BOX", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BSKTBALL", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BUDDY", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BUS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CAMERA", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CAR", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CAR_CHAT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CASINO", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CHAINSAW", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CHOPPA", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CLOTHES", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COACH", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COLT45", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COP_DVBYZ", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CRIB", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DAM_JUMP", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DANCING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DILDO", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DODGE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DOZER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DRIVEBYS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FAT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FIGHT_B", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FIGHT_C", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FIGHT_D", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FIGHT_E", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FINALE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FINALE2", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "Flowers", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FOOD", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "Freeweights", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GANGS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GHANDS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GHETTO_DB", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "goggles", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRAFFITI", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRAVEYARD", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GRENADE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "GYMNASIUM", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "HAIRCUTS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "HEIST9", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_HOUSE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_OFFICE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_SHOP", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "JST_BUISNESS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "KART", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "KISSING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "KNIFE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "LAPDAN1", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "LAPDAN2", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "LAPDAN3", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "LOWRIDER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MD_CHASE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MEDIC", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MD_END", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MISC", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MTB", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "MUSCULAR", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "NEVADA", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ON_LOOKERS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "OTB", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PARACHUTE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PARK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PAULNMAC", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PED", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PLAYER_DVBYS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PLAYIDLES", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "POLICE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "POOL", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "POOR", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PYTHON", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "QUAD", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "QUAD_DBZ", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RIFLE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RIOT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ROB_BANK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ROCKET", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RUSTLER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RYDER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SCRATCHING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SHAMAL", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SHOTGUN", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SILENCED", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SKATE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SPRAYCAN", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "STRIP", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SUNBATHE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWAT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWEET", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWIM", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SWORD", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TANK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TATTOOS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TEC", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TRAIN", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "TRUCK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "UZI", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "VAN", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "VENDING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "VORTEX", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "WAYFARER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "WEAPONS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "WUZI", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SNM", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BLOWJOBZ", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SEX", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BOMBER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "RAPPING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SHOP", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "BEACH", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "SMOKING", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FOOD", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "ON_LOOKERS", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "DEALER", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CRACK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "CARRY", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "COP_AMBIENT", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "PARK", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "INT_HOUSE", "null", 0, 0, 0, 0, 0, 0, 0);
	ApplyAnimation(playerid, "FOOD", "null", 0, 0, 0, 0, 0, 0, 0);
	ClearAnimations(playerid, true);
}

//sAC

void cPlayer::updateHealthBar(const int u)
{
	char msg[88];
	sprintf(msg, "(%d) %s %s [{B7FF00}%.2f%% {DCDCDC}%.2f%%{FFFFFF}]", u, Player[u].uName, Player[u].sName, Player[u].AC.Health, Player[u].AC.Armour);
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Player[u].pBar, -1, msg);
}

void cPlayer::setCharHealth(const int u, const float value)
{
	Player[u].AC.Health = value;
	SetPlayerHealth(u, value);
	cPlayer::updateHealthBar(u);
}

void cPlayer::setCharArmour(const int u, const float value)
{
	Player[u].AC.Armour = value;
	SetPlayerArmour(u, value);
	cPlayer::updateHealthBar(u);
}

void cPlayer::onPlayerGiveDamage(const int u, const int damagedid, const float amount, const unsigned char weaponid)
{
	float hp;

	if ( weaponid == 0 || weaponid == 1 || ( weaponid >= 10 && weaponid <= 14 ) )
	{
		hp = (0.0f + rand() % 400) / 100;
	}
	else if ( weaponid == 2 || weaponid == 3 || ( weaponid >= 5 && weaponid <= 7 ) || weaponid == 15 )
	{
		hp = ( 2.0f + rand() % 400 ) / 100;
	}
	else if ( weaponid == 4 || weaponid == 8 )
	{
		hp = ( 8.0f + rand() % 1000 ) / 100;
	}
	else if ( weaponid == 22 || weaponid == 23 )
	{
		hp = ( 15.0f + rand() % 500 ) / 100;
	}
	else if ( weaponid == 24 )
	{
		hp = ( 20.0f + rand() % 600 ) / 100;
	}
	else if ( weaponid == 25 )
	{
		hp = ( 35.0f + rand() % 2000 ) / 100;
	}
	else if ( weaponid == 26 )
	{
		hp = ( 50.0f + rand() % 2500 ) / 100;
	}
	else if ( weaponid == 27 )
	{
		hp = ( 30.0f + rand() % 1000 ) / 100;
	}
	else if ( weaponid == 28 || weaponid == 32 )
	{
		hp = ( 5.0f + rand() % 1000 ) / 100;
	}
	else if ( weaponid == 29 )
	{
		hp = ( 10.0f + rand() % 500 ) / 100;
	}
	else if ( weaponid == 30 ) //AK47
	{
		hp = ( 30.0f + rand() % 1500 ) / 100;
	}
	else if ( weaponid == 31 ) //M16
	{
		hp = ( 20.0f + rand() % 1500 ) / 100;
	}
	else if ( weaponid == 33 )
	{
		hp = ( 30.0f + rand() % 500 ) / 100;
	}
	else if ( weaponid == 34 )
	{
		hp = ( 100.0f + rand() % 5000 ) / 100;
	}
	else if ( weaponid == 35 || weaponid == 36 )
	{
		hp = ( 150.0f + rand() % 10000 ) / 100;
	}
	else if ( weaponid == 39 )
	{
		hp = ( 150.0f + rand() % 5000 ) / 100;
	}
	else if ( weaponid == 41 || weaponid == 42 )
	{
		hp = 0.1f;
	}
	else if ( u != INVALID_PLAYER_ID )
	{
		hp = ( amount + rand() % 1000 ) / 100;
	}

	if ( Player[damagedid].AC.Armour > 0.00f )
	{
		hp = hp / 2;
		Player[damagedid].AC.Armour -= (hp / 5);
		SetPlayerArmour(damagedid, Player[damagedid].AC.Armour);
	}

	cPlayer::setCharHealth(damagedid, Player[damagedid].AC.Health - hp);
}

void cPlayer::onPlayerTakeDamage(const int u, const int issuerid, const float amount, const unsigned char weaponid)
{
	if ( weaponid <= 0 || weaponid >= 42 )
	{
		cPlayer::setCharHealth(u, Player[u].AC.Health - amount);
	}
}



int cPlayer::getDeathType(int reason)
{
	if(reason == 15)					return DeathTypes::reason_Fight;
	if(reason == 8)						return DeathTypes::reason_Stab;
	if(reason == 9)						return DeathTypes::reason_Stab;
	if(reason == 4)						return DeathTypes::reason_Stab;
	if(reason >= 0 && reason <=7)		return DeathTypes::reason_Fight;
	if(reason >= 51 && reason <=54)		return DeathTypes::reason_Fight;
	if(reason == 49 || reason == 50)	return DeathTypes::reason_Drive;	
	return DeathTypes::reason_Fire;
}