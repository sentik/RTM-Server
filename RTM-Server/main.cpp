#include "main.h"

/*
http://ru.wikibooks.org/wiki/%D0%A1%D0%B8++
Суровый язык этот с++ Можно не то что в ногу себе выстрелить, а запросто повеситься в абсолютно пустой комнате
Язык содержит слишком много возможностей, они могут быть опасны. © Википедия
*/

MYSQL *con;
logprintf_t logprintf;
//======================================
regex expLogin;
regex expNames;
regex expDate;
//======================================
char strSpeed[13] = "Выносливость";
char strMuscular[13] = "Мускулатура";
char strAgility[13] = "Ловкость";
//======================================
char RaceList[3][16] = { "Монголоидная", "Европиоидная", "Негроидная" };							//Список рас:	Монголоидная, Европиоидная, Негроидная
char Natioins[5][18] = { "Амереканская", "Французская", "Русская", "Итальянская", "Японская" };		//Список наций: Амереканская, Французская, Русская, Итальянская, Японская
char SexArray[2][16] = { "Женщина", "Мужчина" };
char query[512];
//-------------------------------------------------------------------------------------------
int tCount;
int uCount;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * Test plugin was unloaded.");
}
//-------------------------------------------------------------------------------------------
AMX_NATIVE_INFO PluginNatives[] =
{
	{ 0, 0 }
};
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	tCount++;
	if (tCount==200)
	{
		thread threadKey(StreamerCall::Tick);
		threadKey.join();
		//StreamerCall::Tick();
		tCount = 0;
	}
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
//-------------------------------------------------------------------------------------------------------------------
//TODO: Инициализирум регулярные выражения
static void buildRegex()
{
	expLogin = regex("([A-Za-z0-9]){4,16}");
	expNames = regex("([A-ZА-Я]{1,1}[a-zа-я]{2,9}) ([A-ZА-Я]{1,1}[a-zа-яё]{2,9})");
	//expDate  = regex("(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\d\d");
	expDate = regex("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[012]).(19|20)([0-9])([0-9])");
}



//-------------------------------------------------------------------------------------------------------------------
//TODO: Загружаем сервер
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)
{
	con = mysql_init(NULL);
	StreamerCall::Load();
	//===========================================
	sampgdk_initialize_plugin(ppPluginData);
	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	//===============================================================================
	logprintf("\n\n*** Rulezz Team GameMode v%s By SeNTike & Serinc ***\n", GAME_VERSION);
	//===============================================================================
	mysql_real_connect(con, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_BASE, 0, NULL, 0);
	mysql_query(con, "SET NAMES cp1251");
	//===============================================================================
	cInteriors::loadInterioList();
	cProperty::loadHouses();
	cProperty::loadHouseInteriors();
	buildRegex();
	//===============================================================================
	for (int i = 0; i < 3; i++) 	cClass::fixText(RaceList[i], strlen(RaceList[i]));
	for (int i = 0; i < 5; i++) 	cClass::fixText(Natioins[i], strlen(Natioins[i]));
	for (int i = 0; i < 2; i++) 	cClass::fixText(SexArray[i], strlen(SexArray[i]));
	//===============================================================================
	cClass::loadVehicleClass();
	cClass::loadPlayerClass();
	//===============================================================================
	cClass::fixText(strSpeed, 13);
	cClass::fixText(strMuscular, 13);
	cClass::fixText(strAgility, 13);
	//===============================================================================
	srand(RANDOM_SEED);
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	/*
	for (int i = 0; i < 1000; i++)
	for (int q = 0; q < 1000; q++)
	{
		StreamerCall::Native::CreateDynamicObject(987, 15.0f + q , 15.0f + i, 2.2f, 0.0f, 0.0f, 0.0f);
	}
	*/
	//-------------------------------------------------------------
	//TODO: Фон формы авторизации
	drawPlayerChar[REG_BG] = TextDrawCreate(100.000000f, 160.000000f, "_");
	TextDrawAlignment(drawPlayerChar[REG_BG], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_BG], 255);
	TextDrawFont(drawPlayerChar[REG_BG], 1);
	TextDrawLetterSize(drawPlayerChar[REG_BG], 0.500000f, 17.000003f);
	TextDrawColor(drawPlayerChar[REG_BG], -1);
	TextDrawSetOutline(drawPlayerChar[REG_BG], 0);
	TextDrawSetProportional(drawPlayerChar[REG_BG], 1);
	TextDrawSetShadow(drawPlayerChar[REG_BG], 1);
	TextDrawUseBox(drawPlayerChar[REG_BG], 1);
	TextDrawBoxColor(drawPlayerChar[REG_BG], 80);
	TextDrawTextSize(drawPlayerChar[REG_BG], 0.000000f, 150.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_BG], 0);
	//-------------------------------------------------------------
	//TODO: Заголовок окна авторизации
	drawPlayerChar[REG_HEADER] = TextDrawCreate(100.000000f, 153.000000f, "Select Craracter");
	TextDrawAlignment(drawPlayerChar[REG_HEADER], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_HEADER], -1778346416);
	TextDrawFont(drawPlayerChar[REG_HEADER], 0);
	TextDrawLetterSize(drawPlayerChar[REG_HEADER], 0.609999f, 1.00000f);
	TextDrawColor(drawPlayerChar[REG_HEADER], -1);
	TextDrawSetOutline(drawPlayerChar[REG_HEADER], 1);
	TextDrawSetProportional(drawPlayerChar[REG_HEADER], 1);
	TextDrawSetSelectable(drawPlayerChar[REG_HEADER], 0);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка назад
	drawPlayerChar[REG_LEFT] = TextDrawCreate(25.000000f, 316.000000f, "ld_beat:left");
	TextDrawAlignment(drawPlayerChar[REG_LEFT], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_LEFT], 0);
	TextDrawFont(drawPlayerChar[REG_LEFT], 4);
	TextDrawLetterSize(drawPlayerChar[REG_LEFT], 0.500000f, 1.100000f);
	TextDrawColor(drawPlayerChar[REG_LEFT], 100);
	TextDrawSetOutline(drawPlayerChar[REG_LEFT], 0);
	TextDrawSetProportional(drawPlayerChar[REG_LEFT], 1);
	TextDrawSetShadow(drawPlayerChar[REG_LEFT], 1);
	TextDrawUseBox(drawPlayerChar[REG_LEFT], 1);
	TextDrawBoxColor(drawPlayerChar[REG_LEFT], 255);
	TextDrawTextSize(drawPlayerChar[REG_LEFT], 30.000000f, 15.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_LEFT], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка вперед
	drawPlayerChar[REG_RIGHT] = TextDrawCreate(145.000000f, 316.000000f, "ld_beat:right");
	TextDrawAlignment(drawPlayerChar[REG_RIGHT], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_RIGHT], 0);
	TextDrawFont(drawPlayerChar[REG_RIGHT], 4);
	TextDrawLetterSize(drawPlayerChar[REG_RIGHT], 0.500000f, 1.100000f);
	TextDrawColor(drawPlayerChar[REG_RIGHT], 100);
	TextDrawSetOutline(drawPlayerChar[REG_RIGHT], 0);
	TextDrawSetProportional(drawPlayerChar[REG_RIGHT], 1);
	TextDrawSetShadow(drawPlayerChar[REG_RIGHT], 1);
	TextDrawUseBox(drawPlayerChar[REG_RIGHT], 1);
	TextDrawBoxColor(drawPlayerChar[REG_RIGHT], 255);
	TextDrawTextSize(drawPlayerChar[REG_RIGHT], 30.000000f, 15.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_RIGHT], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка Выбрать
	drawPlayerChar[REG_SELECT] = TextDrawCreate(100.000000f, 316.000000f, "SELECT");
	TextDrawAlignment(drawPlayerChar[REG_SELECT], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_SELECT], 0);
	TextDrawFont(drawPlayerChar[REG_SELECT], 1);
	TextDrawLetterSize(drawPlayerChar[REG_SELECT], 0.609999f, 1.399999f);
	TextDrawColor(drawPlayerChar[REG_SELECT], 100);
	TextDrawSetOutline(drawPlayerChar[REG_SELECT], 0);
	TextDrawSetProportional(drawPlayerChar[REG_SELECT], 1);
	TextDrawSetShadow(drawPlayerChar[REG_SELECT], 1);
	TextDrawUseBox(drawPlayerChar[REG_SELECT], 1);
	TextDrawBoxColor(drawPlayerChar[REG_SELECT], 0x00000000);
	TextDrawTextSize(drawPlayerChar[REG_SELECT], 15.000000f, 60.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_SELECT], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Фон для кнопок
	drawPlayerChar[REG_BUTTON_BG] = TextDrawCreate(100.000000f, 318.000000f, "_");
	TextDrawAlignment(drawPlayerChar[REG_BUTTON_BG], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_BUTTON_BG], 255);
	TextDrawFont(drawPlayerChar[REG_BUTTON_BG], 1);
	TextDrawLetterSize(drawPlayerChar[REG_BUTTON_BG], 0.500000f, 1.199998f);
	TextDrawColor(drawPlayerChar[REG_BUTTON_BG], -1);
	TextDrawSetOutline(drawPlayerChar[REG_BUTTON_BG], 0);
	TextDrawSetProportional(drawPlayerChar[REG_BUTTON_BG], 1);
	TextDrawSetShadow(drawPlayerChar[REG_BUTTON_BG], 1);
	TextDrawUseBox(drawPlayerChar[REG_BUTTON_BG], 1);
	TextDrawBoxColor(drawPlayerChar[REG_BUTTON_BG], -1778346416);
	TextDrawTextSize(drawPlayerChar[REG_BUTTON_BG], 0.000000f, 150.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_BUTTON_BG], 0);
	//-------------------------------------------------------------
	cObjects::loadObjects("intdoma1");
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, true);
	//==========================================================================
	char message[560];
	//==========================================================================
	strcpy(message, "{FFAF00}===========================================================");
	strcat(message, "\n{FFFFFF}ВЫ можете полностью окунуться в мир RolePlay, только у нас есть:");
	strcat(message, "\n - Реалистичная экономика и гормоничный игровой мир");
	strcat(message, "\n - Различные типы имущества (Дома, Гаражи, Магазины, Бизнесы)");
	strcat(message, "\n - Различные виды работ (Продавец, уборщик, охранник, курьер)");
	strcat(message, "\n - Множество различных банд, мафий и организаций");
	strcat(message, "\n - Качественная и полноценная RP-отыгровка");
	strcat(message, "\n{FFAF00}===========================================================");
	strcat(message, "\n{FFFFFF}Присойденяйся к нам прямо сейчас, окунись в мир RolePlay!");
	//==========================================================================
	ShowPlayerDialog(playerid, DLG_WELCOME, GUI_MSG, "[West-RP]: Приветствие", message, "Далее", "");
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	StreamerCall::Events::OnPlayerConnect(playerid);
	if (IsPlayerNPC(playerid)) return true;
//	Player[playerid] = { { 0 } };
	return true;
}

//SAMPGDK_CALLBACK_EXPORT bool SAMPGDK_CALLBACK_CALL OnPlayerText(int playerid, const char * text);
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int u, const char *text)
{
	char msg[ 144 ];
	sprintf(msg, "%s %s [{FFAF00}%d{FFFFFF}] говорит: {FFAF00}%s", Player[ u ].uName, Player[ u ].sName, u, text);
	cChat::ProxDetector(u, 10.0f, msg);
	return false;
}



//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	StreamerCall::Events::OnPlayerDisconnect(playerid, reason);
//	Player[playerid] = { { 0 } };
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	if (Player[playerid].isLogged)
	{
		cPlayer::setClassSkin(playerid);
		//-------------------------------------------------------
		SetPlayerPos(playerid,
			Player[playerid].pPosX,
			Player[playerid].pPosY,
			Player[playerid].pPosZ);
		//-------------------------------------------------------
		SetPlayerFacingAngle(playerid, Player[playerid].pPosR);
		//-------------------------------------------------------
		SetPlayerInterior(playerid, Player[playerid].pPosI);
		SetPlayerVirtualWorld(playerid, Player[playerid].pPosW);
		//-------------------------------------------------------
	}
	return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	uCount++;
	if (Player[playerid].isLogged && uCount > 25)
	{
		//StreamerCall::Native::Update(playerid);
		thread threadKey(StreamerCall::Native::Update, playerid);
		threadKey.join();
		uCount = 0;
	}
	return true;
}



//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	thread threadKey(cState::callKeyStateChange, playerid, newkeys, oldkeys);
	threadKey.join();
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerStateChange(int playerid, int newstate, int oldstate)
{
	thread threadKey(cState::callStateChange, playerid, newstate, oldstate);
	threadKey.join();
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmd)
{
	sprintf(query, "playr: %d cmd: %s", playerid, cmd);
	SendClientMessage(playerid, -1, query);
	if (strcmp("/veh", cmd) == 0)
	{
		GetPlayerPos(playerid, &Player[playerid].pPosX, &Player[playerid].pPosY, &Player[playerid].pPosZ);
		int veh = CreateVehicle(562, Player[playerid].pPosX, Player[playerid].pPosY, Player[playerid].pPosZ, 0, 0, 0, -1);
		PutPlayerInVehicle(playerid, veh, 0);
	}
	return true;
}
//-------------------------------------------------------------------------------------------
namespace StreamerCall
{
	bool OnPlayerEditDynamicObject(int playerid, int objectid, int response, float x, float y, float z, float rx, float ry, float rz)
	{
		return true;
	}
	bool OnPlayerSelectDynamicObject(int playerid, int objectid, int modelid, float x, float y, float z)
	{
		return true;
	}
	bool OnPlayerPickUpDynamicPickup(int playerid, int pickupid)
	{
		return true;
	}
	bool OnPlayerEnterDynamicCP(int playerid, int checkpointid)
	{
		return true;
	}
	bool OnPlayerLeaveDynamicCP(int playerid, int checkpointid)
	{
		return true;
	}
	bool OnPlayerEnterDynamicRaceCP(int playerid, int checkpointid)
	{
		return true;
	}
	bool OnPlayerLeaveDynamicRaceCP(int playerid, int checkpointid)
	{
		return true;
	}
	bool OnPlayerEnterDynamicArea(int playerid, int areaid)
	{
		return true;
	}
	bool OnPlayerLeaveDynamicArea(int playerid, int areaid)
	{
		return true;
	}
	bool OnDynamicObjectMoved(int objectid)
	{
		return true;
	}
};

//streamer stuff so not added to extension library, browse more
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEditObject(int playerid, bool playerobject, int objectid, int response, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ)
{
	return StreamerCall::Events::OnPlayerEditObject(playerid, playerobject, objectid, response, fX, fY, fZ, fRotX, fRotY, fRotZ);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
{
	return StreamerCall::Events::OnPlayerSelectObject(playerid, type, objectid, modelid, x, y, z);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerPickUpPickup(int playerid, int pickupid)
{
	return StreamerCall::Events::OnPlayerPickUpPickup(playerid, pickupid);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterCheckpoint(int playerid)
{
	return StreamerCall::Events::OnPlayerEnterCheckpoint(playerid);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveCheckpoint(int playerid)
{
	return StreamerCall::Events::OnPlayerLeaveCheckpoint(playerid);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerEnterRaceCheckpoint(int playerid)
{
	return StreamerCall::Events::OnPlayerEnterRaceCheckpoint(playerid);
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerLeaveRaceCheckpoint(int playerid)
{
	return StreamerCall::Events::OnPlayerLeaveRaceCheckpoint(playerid);
}
