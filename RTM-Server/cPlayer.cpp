#include "main.h"

struct pChar PlayerChar[MAX_PLAYERS][MAX_CHARS] = { { 0, 0 } };
struct rChar RegChar[MAX_PLAYERS] = { { 0, 0 } };
struct pInfo Player[MAX_PLAYERS] = { { 0, 0 } };
int drawPlayerChar[10];

int qqqq;

void cPlayer::update()
{
	//-------------------------------------------------
	bool isTwo = uTime % 2 == 0;		//Кратность 2  UNIX-Time
	bool isFive = uTime % 5 == 0;		//Кратность 5  UNIX-Time
	bool isTen = isTwo & isFive;		//Кратность 10 UNIX-Time 
	//-------------------------------------------------
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (Player[ i ].isLogged == false) continue;
		if (Player[ i ].isAction == PlayerAction::ACTION_FREZSETPOS)
		{
			Player[ i ].isAction = PlayerAction::ACTION_NONE;
			TogglePlayerControllable(i, 1);
		}
		if (isTwo)
		{
			cPlayer::updatePos(i);
		}
		
		if (Player[i].isAction == PlayerAction::ACTION_USERENT)
		{
			qqqq++;
			if (qqqq % 10 == 0)
			{
				Properties::Shops::ShopVehicle::viewCam(i);
				qqqq = 0;
			}
		}
	}
}

//TODO: Проверить наличие аккаунта
int cPlayer::checkLogin(const char* login)
{
	sprintf(query, "SELECT id FROM player_Accounts WHERE login ='%s' LIMIT 1", login);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(result);
	return (mysql_num_rows(result)) ? (atoi(row[0])) : (0);
}

//TODO: Проверить логин
bool cPlayer::checkPass(int i, const char* passw)
{
	sprintf(query, "SELECT NULL FROM player_Accounts WHERE id = '%d' AND passw = MD5(CONCAT('%c', PASSWORD('%s'), '%c'))", i, passw[0], passw, passw[strlen(passw) - 1]);
	mysql_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	return (mysql_num_rows(result)) ? (true) : (false);
}

//TODO: Зарегестрировать аккаунт
int cPlayer::regPlayer(const char* login, const char* passw)
{
	sprintf(query, "INSERT INTO player_Accounts SET `login` = '%s', passw = MD5(CONCAT('%c', PASSWORD('%s'), '%c'))", login, passw[0], passw, passw[strlen(passw) - 1]);
	mysql_query(con, query);
	return mysql_insert_id(con);
}

//TODO: Зарегестрировать персонажа
int cPlayer::regChar(const int u)
{
	sprintf(query, "INSERT INTO player_Character (owner, uname, sname, money, class) VALUES ('%d', '%s', '%s', '%f', '%d')",
		Player[u].pDB, Player[u].uName, Player[u].sName, Player[u].pMoney, Player[u].pClass);
	mysql_query(con, query);
	return mysql_insert_id(con);
}

/// <summary>
/// Загрузить персонажа игрока
/// <param name="i">* Ид игрока</param>
/// </summary>
void cPlayer::loadPlayerChar(int i)
{
	//-------------------------------------------------------------------------------------------------------------------
	sprintf(query, "SELECT * FROM player_Character  WHERE owner = '%d' AND id = %d LIMIT 1", Player[i].pDB, Player[i].pClass), mysql_query(con, query);
	//-------------------------------------------------------------------------------------------------------------------
	MYSQL_RES *result = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(result);
	//-------------------------------------------------------------------------------------------------------------------
	Player[i].pDB		= atoi(row[PlayerRows::plDB]);
	Player[i].pMoney	= atof(row[PlayerRows::plMoney]);
	Player[i].pClass	= atoi(row[PlayerRows::plClass]);
	Player[i].pPosX		= atof(row[PlayerRows::plPosX]);
	Player[i].pPosY		= atof(row[PlayerRows::plPosY]);
	Player[i].pPosZ		= atof(row[PlayerRows::plPosZ]);
	Player[i].pPosR		= atof(row[PlayerRows::plPosR]);
	Player[i].pPosI		= atoi(row[PlayerRows::plPosI]);
	Player[i].pPosW		= atoi(row[PlayerRows::plPosW]);
	//------------------------------------------------
	strcpy(Player[i].uName, row[PlayerRows::pluName]);
	strcpy(Player[i].sName, row[PlayerRows::plsName]);
	//------------------------------------------------
	GivePlayerMoney(i, Player[ i ].pMoney);
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
	sprintf(query, "SELECT id, `class`, money, uname, sname  FROM player_Character WHERE owner = '%d' LIMIT %d", Player[i].pDB, MAX_CHARS), mysql_query(con, query);
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
		sprintf(tmp, "%s %s", PlayerChar[i][c].uName, PlayerChar[i][c].sName);
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
	sprintf(msg, "К сожаления у вас не хватает %.2f$\nТребуется всего: %.2f$", value - Player[ u ].pMoney, value);
	ShowPlayerDialog(u, DIALOG_LIST::DLG_NONE, GUI_MSG, "[Информация]: Недостаточно средств", msg, "Закрыть", "");
	//=========================================
	return false;
}

void cPlayer::givePlayerMoney(const int u, float value)
{
	//=============================
	GivePlayerMoney(u, value);
	Player[ u ].pMoney += value;
	//=============================
	sprintf(query, "UPDATE player_Character SET money = '%f' WHERE id = '%d'", Player[ u ].pMoney, Player[ u ].pDB);
	mysql_query(con, query);
	//=============================
}

void cPlayer::updatePos(const int u)
{
	GetPlayerPos(u, &Player[ u ].pPosX, &Player[ u ].pPosY, &Player[ u ].pPosZ);
	GetPlayerFacingAngle( u, &Player[ u ].pPosR );
	Player[ u ].pPosW = GetPlayerVirtualWorld(u);
	Player[ u ].pPosI = GetPlayerInterior(u);
	//================================================================================
	sprintf(query, "UPDATE player_Character SET posx='%f', posy='%f', posz='%f', posr='%f', posi='%d', posw='%d', posp='%d' WHERE id = '%d'", 
			Player[ u ].pPosX, Player[ u ].pPosY, Player[ u ].pPosZ, Player[ u ].pPosR, Player[ u ].pPosI, Player[ u ].pPosW,
			Player[ u ].inIndex, Player[ u ].pDB);
	//================================================================================
	//mysql_query(con, query);
}


void cPlayer::getPlayerPos(const int i)
{
	GetPlayerPos(i, &Player[ i ].pPosX, &Player[ i ].pPosY, &Player[ i ].pPosZ);
}