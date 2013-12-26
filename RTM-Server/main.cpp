#include "main.h"
/*
http://ru.wikibooks.org/wiki/%D0%A1%D0%B8++
Суровый язык этот с++ Можно не то что в ногу себе выстрелить, а запросто повеситься в абсолютно пустой комнате
Язык содержит слишком много возможностей, они могут быть опасны. © Википедия
*/

MYSQL *con;
std::mutex mutexStreamGlobal;
std::mutex mutexStreamPlayer;
std::mutex mutexMYSQL;


logprintf_t logprintf;
//======================================
regex expLogin;
regex expNames;
regex expDate;
regex expCode;

regex expString;
regex expFloat;
regex expNumber;
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
int uTime;


int safe_query(MYSQL *conn, char query[ ])
{
	mutexMYSQL.lock();
	int res = 	mysql_query(conn, query);
	mutexMYSQL.unlock();
	return res;
}


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	mysql_close(con);
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
	
	if (tCount == 100)
	{
		mutexStreamGlobal.lock();
		StreamerCall::Tick();
		mutexStreamGlobal.unlock();
	}
	else if (tCount==200)
	{
		uTime = getUnixTime();
		//-----------------------------------
		thread(cPlayer::update).detach();
		StreamerCall::Tick();
		//-----------------------------------
		/*thread threadStream(StreamerCall::Tick);
		threadStream.join();*/
		//-----------------------------------
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
	expCode = regex("([0-9]{4,8})");

	expString = regex("([A-zА-я ]){3,20}");
	expFloat = regex("([0-9]{1,5}[\\.]{1,1}[0-9]{1,4})");
	expNumber = regex("([0-9]{1,11})");
}

double fint(double x) // округление в сторону нуля (т.е. меньшее по абсолютному значению)
{
	return x >= 0.
		? floor(x)
		: ceil(x);
}



//-------------------------------------------------------------------------------------------------------------------
//TODO: Загружаем сервер
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)
{
	con = mysql_init(NULL);
	StreamerCall::Load();
	//===========================================
	sampgdk_initialize_plugin(ppPluginData);
	//sampgdk_initialize_plugin(ppPluginData);

	logprintf = (logprintf_t)ppPluginData[PLUGIN_DATA_LOGPRINTF];
	//===============================================================================
	cout << "\a";
	logprintf("\n\n*** Rulezz Team GameMode v%s By SeNTike & Serinc ***\n", GAME_VERSION);
	cout << "\a";
	//===============================================================================
	mysql_real_connect(con, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_BASE, 0, NULL, CLIENT_MULTI_STATEMENTS);
	safe_query(con, "SET NAMES cp1251");
	mysql_set_character_set(con, "cp1251");
	//===============================================================================
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


	/*char *p = "...";
	const char* pc = "Hello, World!"; // pointer to a constant
	pc = p;      // okay

	logprintf(pc);*/

	/*char *res;
	res = (char*)( &language::player::biography::familyPartOne[ 0 ] );

	*( (char)( &language::player::biography::familyPartOne[ 0 ] ) ) = "xuita";


	logprintf(language::player::biography::familyPartOne[ 0 ]);
	*/
	/*char *res = const_cast<char*>( language::player::biography::familyPartOne[0] );
	cClass::fixText(res, 256);*/
	
	
	
	srand(RANDOM_SEED);
	return true;
}

//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit()
{
	//"demo"( );
	Properties::Shops::ShopVehicle::loadShop();
	Jobs::Miner::cMiner::loadMiner();
	fProperty::cFeller::loadFeller();
	fProperty::cFeller::loadTrees();
	//-------------------------------------------------------------
	cBanks::loadBanks();
	gasProperty::cGas::loadGas();
	//-------------------------------------------------------------
	cInteriors::loadInterioList();
	cHouses::loadHouses();
	cHouses::loadHouseInteriors();
	Properties::Farms::load();
	Properties::Belays::load();
	//-------------------------------------------------------------
	cObjects::loadObjects();
	//-------------------------------------------------------------
	world::Players::Admins::init();
	world::gangs::load();
	world::DropedGuns::loadGuns();
	world::pickups::cPickups::loadPickups();
	world::radio::cRadio::loadRadio();
	initTextDraws();
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(false);
	sprintf(query, "RTM-GM v%s", GAME_VERSION);
	SetGameModeText(query);
	ShowNameTags(false);
	StreamerCall::Native::CreateDynamicPickup(INFO_PICKUP, 23, TEMP_JOB_POS);
	StreamerCall::Native::CreateDynamic3DTextLabel("Филиал трудо-занятности\nНажмите [ALT]", -1, TEMP_JOB_POS, 5.0f);
	cout << "\a";
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid)
{
	if (IsPlayerNPC(playerid) == false)
	{
		SpawnPlayer(playerid);
		TogglePlayerSpectating(playerid, true);
		//==========================================================================
		char message[ 800 ];
		//==========================================================================
		strcpy(message, "{078ad6}===========================================================");
		strcat(message, "\n{7d67dd}Вы можете полностью окунуться в мир RolePlay, только у нас есть:");
		strcat(message, "\n {ffffff}- {5c84e9}Реалистичная экономика и гормоничный игровой мир");
		strcat(message, "\n {ffffff}- {5c84e9}Различные типы имущества (Дома, Гаражи, Магазины, Бизнесы)");
		strcat(message, "\n {ffffff}- {5c84e9}Различные виды работ (Продавец, уборщик, охранник, курьер)");
		strcat(message, "\n {ffffff}- {5c84e9}Множество различных банд, мафий и организаций");
		strcat(message, "\n {ffffff}- {5c84e9}Качественная и полноценная RP-отыгровка");
		strcat(message, "\n{078ad6}===========================================================");
		strcat(message, "\n{7d67dd}Присойденяйся к нам прямо сейчас, окунись в мир RolePlay!");
		//==========================================================================
		ShowPlayerDialog(playerid, DLG_WELCOME, GUI_MSG, "[West-RP]: Приветствие", message, "Далее", "");
	}
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid)
{
	if (IsPlayerNPC(playerid) == false)
	{
		for (int i = 0; i < Properties::Farms::count; i++)
		{
			GangZoneShowForPlayer(playerid, Properties::Farms::Farm[ i ].zome, 0x00ff6c96);
		}

		StreamerCall::Events::OnPlayerConnect(playerid);
		Player[ playerid ].pBar = StreamerCall::Native::CreateDynamic3DTextLabel(" ", -1, 0.0f, 0.0f, 0.13f, 20.0f, playerid);
		cObjects::removeObjects(playerid);
		cPlayer::PreloadAnimLib(playerid);
	}
	return false;
}

//SAMPGDK_CALLBACK_EXPORT bool SAMPGDK_CALLBACK_CALL OnPlayerText(int playerid, const char * text);
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerText(int u, const char *text)
{
	char msg[ 144 ];
	sprintf(msg, "%s %s [{FFAF00}%d{FFFFFF}] говорит: {FFAF00}%s", Player[ u ].uName, Player[ u ].sName, u, text);
	cChat::ProxDetector(u, 10.0f, msg);
	SetPlayerChatBubble(u, text, 0xFFAF00FF, 20.0f, 15000);
	return false;
}



PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerDeath(int playerid, int killerid, int reason)
{
	if (Player[ playerid ].isLogged)
		SendClientMessage(playerid, -1, "Вы авторизованны!");
	Player[ playerid ].isAction = PlayerAction::ACTION_Death;
	//-------------------------------------
	Player[ playerid ].pPosX = 1170.984f;
	Player[ playerid ].pPosY = -1323.432f;
	Player[ playerid ].pPosZ = 15.298f;
	//-------------------------------------
	SendClientMessage(playerid, -1, "Вы умерли =((");
	return false;
}

//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerDisconnect(int playerid, int reason)
{
	Player[playerid].isLogged = false;
	StreamerCall::Native::DestroyDynamic3DTextLabel(Player[playerid].pBar);
	StreamerCall::Events::OnPlayerDisconnect(playerid, reason);
//	Player[playerid] = { { 0 } };
	return true;
}
//-------------------------------------------------------------------------------------------
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerSpawn(int playerid)
{
	if (Player[ playerid ].isLogged)
	{
		cPlayer::setClassSkin(playerid);
		Player[ playerid ].isAction = PlayerAction::ACTION_NONE;
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
		cPlayer::updateMoney(playerid);
		PlayerTextDrawShow(playerid, Player[playerid].tCents);
		TextDrawShowForPlayer(playerid, drawPlayerChar[HEADER_BG]);
		TextDrawShowForPlayer(playerid, drawPlayerChar[HEADER_TIME]);
	}
	else if (sampgdk_IsPlayerNPC( playerid ))
		logprintf("npc suka! %d", playerid);

	return true;
}



PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerUpdate(int playerid)
{
	if (Player[ playerid ].isLogged)
	{
		uCount++;
		if (Player[playerid].pState == PLAYER_STATE_DRIVER)
		{
			world::Vehicles::updateSpeed(playerid);
		}
		//================================================
		if(uCount > 10)
		{
			mutexStreamPlayer.lock();
			StreamerCall::Native::Update(playerid);
			mutexStreamPlayer.unlock();
			uCount = 0;
		}
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


static int getUnixTime()
{
	return (int)std::time(0);
}

bool OnPlayerCommandReceived(int playerid, std::string command, std::string params)
{
	return true;
}

void OnPlayerCommandExecuted(int playerid, std::string, std::string params, bool success)
{

}

//note that the 'command' is always in lower-case because of the transformation done in the main processing step
bool OnUnknownCommand(int playerid, std::string command, std::string params)
{
	return true;
}


static void initTextDraws()
{
	//-------------------------------------------------------------
	//TODO: Фон формы авторизации
	drawPlayerChar[ REG_BG ] = TextDrawCreate(100.000000f, 160.000000f, "_");
	TextDrawAlignment(drawPlayerChar[ REG_BG ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_BG ], 255);
	TextDrawFont(drawPlayerChar[ REG_BG ], 1);
	TextDrawLetterSize(drawPlayerChar[ REG_BG ], 0.500000f, 17.000003f);
	TextDrawColor(drawPlayerChar[ REG_BG ], -1);
	TextDrawSetOutline(drawPlayerChar[ REG_BG ], 0);
	TextDrawSetProportional(drawPlayerChar[ REG_BG ], 1);
	TextDrawSetShadow(drawPlayerChar[ REG_BG ], 1);
	TextDrawUseBox(drawPlayerChar[ REG_BG ], 1);
	TextDrawBoxColor(drawPlayerChar[ REG_BG ], 80);
	TextDrawTextSize(drawPlayerChar[ REG_BG ], 0.000000f, 150.000000f);
	TextDrawSetSelectable(drawPlayerChar[ REG_BG ], 0);
	//-------------------------------------------------------------
	//TODO: Заголовок окна авторизации
	drawPlayerChar[ REG_HEADER ] = TextDrawCreate(100.000000f, 153.000000f, "Select Craracter");
	TextDrawAlignment(drawPlayerChar[ REG_HEADER ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_HEADER ], -1778346416);
	TextDrawFont(drawPlayerChar[ REG_HEADER ], 0);
	TextDrawLetterSize(drawPlayerChar[ REG_HEADER ], 0.609999f, 1.00000f);
	TextDrawColor(drawPlayerChar[ REG_HEADER ], -1);
	TextDrawSetOutline(drawPlayerChar[ REG_HEADER ], 1);
	TextDrawSetProportional(drawPlayerChar[ REG_HEADER ], 1);
	TextDrawSetSelectable(drawPlayerChar[ REG_HEADER ], 0);
	//-------------------------------------------------------------
	//TODO: Заголовок окна авторизации
	drawPlayerChar[REG_HEADER_CLASS] = TextDrawCreate(100.000000f, 153.000000f, "Select Class");
	TextDrawAlignment(drawPlayerChar[REG_HEADER_CLASS], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_HEADER_CLASS], -1778346416);
	TextDrawFont(drawPlayerChar[REG_HEADER_CLASS], 0);
	TextDrawLetterSize(drawPlayerChar[REG_HEADER_CLASS], 0.609999f, 1.00000f);
	TextDrawColor(drawPlayerChar[REG_HEADER_CLASS], -1);
	TextDrawSetOutline(drawPlayerChar[REG_HEADER_CLASS], 1);
	TextDrawSetProportional(drawPlayerChar[REG_HEADER_CLASS], 1);
	TextDrawSetSelectable(drawPlayerChar[REG_HEADER_CLASS], 0);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка назад
	drawPlayerChar[ REG_LEFT ] = TextDrawCreate(25.000000f, 316.000000f, "ld_beat:left");
	TextDrawAlignment(drawPlayerChar[ REG_LEFT ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_LEFT ], 0);
	TextDrawFont(drawPlayerChar[ REG_LEFT ], 4);
	TextDrawLetterSize(drawPlayerChar[ REG_LEFT ], 0.500000f, 1.100000f);
	TextDrawColor(drawPlayerChar[ REG_LEFT ], 100);
	TextDrawSetOutline(drawPlayerChar[ REG_LEFT ], 0);
	TextDrawSetProportional(drawPlayerChar[ REG_LEFT ], 1);
	TextDrawSetShadow(drawPlayerChar[ REG_LEFT ], 1);
	TextDrawUseBox(drawPlayerChar[ REG_LEFT ], 1);
	TextDrawBoxColor(drawPlayerChar[ REG_LEFT ], 255);
	TextDrawTextSize(drawPlayerChar[ REG_LEFT ], 30.000000f, 15.000000f);
	TextDrawSetSelectable(drawPlayerChar[ REG_LEFT ], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка вперед
	drawPlayerChar[ REG_RIGHT ] = TextDrawCreate(145.000000f, 316.000000f, "ld_beat:right");
	TextDrawAlignment(drawPlayerChar[ REG_RIGHT ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_RIGHT ], 0);
	TextDrawFont(drawPlayerChar[ REG_RIGHT ], 4);
	TextDrawLetterSize(drawPlayerChar[ REG_RIGHT ], 0.500000f, 1.100000f);
	TextDrawColor(drawPlayerChar[ REG_RIGHT ], 100);
	TextDrawSetOutline(drawPlayerChar[ REG_RIGHT ], 0);
	TextDrawSetProportional(drawPlayerChar[ REG_RIGHT ], 1);
	TextDrawSetShadow(drawPlayerChar[ REG_RIGHT ], 1);
	TextDrawUseBox(drawPlayerChar[ REG_RIGHT ], 1);
	TextDrawBoxColor(drawPlayerChar[ REG_RIGHT ], 255);
	TextDrawTextSize(drawPlayerChar[ REG_RIGHT ], 30.000000f, 15.000000f);
	TextDrawSetSelectable(drawPlayerChar[ REG_RIGHT ], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка Выбрать
	drawPlayerChar[ REG_SELECT ] = TextDrawCreate(100.000000f, 316.000000f, "SELECT");
	TextDrawAlignment(drawPlayerChar[ REG_SELECT ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_SELECT ], 0);
	TextDrawFont(drawPlayerChar[ REG_SELECT ], 1);
	TextDrawLetterSize(drawPlayerChar[ REG_SELECT ], 0.609999f, 1.399999f);
	TextDrawColor(drawPlayerChar[ REG_SELECT ], 100);
	TextDrawSetOutline(drawPlayerChar[ REG_SELECT ], 0);
	TextDrawSetProportional(drawPlayerChar[ REG_SELECT ], 1);
	TextDrawSetShadow(drawPlayerChar[ REG_SELECT ], 1);
	TextDrawUseBox(drawPlayerChar[ REG_SELECT ], 1);
	TextDrawBoxColor(drawPlayerChar[ REG_SELECT ], 0x00000000);
	TextDrawTextSize(drawPlayerChar[ REG_SELECT ], 15.000000f, 60.000000f);
	TextDrawSetSelectable(drawPlayerChar[ REG_SELECT ], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Кнопка Выбрать
	drawPlayerChar[REG_CREATE] = TextDrawCreate(100.000000f, 316.000000f, "CREATE");
	TextDrawAlignment(drawPlayerChar[REG_CREATE], 2);
	TextDrawBackgroundColor(drawPlayerChar[REG_CREATE], 0);
	TextDrawFont(drawPlayerChar[REG_CREATE], 1);
	TextDrawLetterSize(drawPlayerChar[REG_CREATE], 0.609999f, 1.399999f);
	TextDrawColor(drawPlayerChar[REG_CREATE], 100);
	TextDrawSetOutline(drawPlayerChar[REG_CREATE], 0);
	TextDrawSetProportional(drawPlayerChar[REG_CREATE], 1);
	TextDrawSetShadow(drawPlayerChar[REG_CREATE], 1);
	TextDrawUseBox(drawPlayerChar[REG_CREATE], 1);
	TextDrawBoxColor(drawPlayerChar[REG_CREATE], 0x00000000);
	TextDrawTextSize(drawPlayerChar[REG_CREATE], 15.000000f, 60.000000f);
	TextDrawSetSelectable(drawPlayerChar[REG_CREATE], 1);
	//-------------------------------------------------------------
	//TODO: Регистрация. Фон для кнопок
	drawPlayerChar[ REG_BUTTON_BG ] = TextDrawCreate(100.000000f, 318.000000f, "_");
	TextDrawAlignment(drawPlayerChar[ REG_BUTTON_BG ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ REG_BUTTON_BG ], 255);
	TextDrawFont(drawPlayerChar[ REG_BUTTON_BG ], 1);
	TextDrawLetterSize(drawPlayerChar[ REG_BUTTON_BG ], 0.500000f, 1.199998f);
	TextDrawColor(drawPlayerChar[ REG_BUTTON_BG ], -1);
	TextDrawSetOutline(drawPlayerChar[ REG_BUTTON_BG ], 0);
	TextDrawSetProportional(drawPlayerChar[ REG_BUTTON_BG ], 1);
	TextDrawSetShadow(drawPlayerChar[ REG_BUTTON_BG ], 1);
	TextDrawUseBox(drawPlayerChar[ REG_BUTTON_BG ], 1);
	TextDrawBoxColor(drawPlayerChar[ REG_BUTTON_BG ], -1778346416);
	TextDrawTextSize(drawPlayerChar[ REG_BUTTON_BG ], 0.000000f, 150.000000f);
	TextDrawSetSelectable(drawPlayerChar[ REG_BUTTON_BG ], 0);
	//-------------------------------------------------------------
	//TODO: Игра. Фон спидометра
	drawPlayerChar[SPD_BG] = TextDrawCreate(580.000000, 300.000000, "_");
	TextDrawAlignment( drawPlayerChar[SPD_BG], 2);
	TextDrawBackgroundColor( drawPlayerChar[SPD_BG], 255);
	TextDrawFont( drawPlayerChar[SPD_BG], 1);
	TextDrawLetterSize( drawPlayerChar[SPD_BG], 0.500000, 5.000000);
	TextDrawColor( drawPlayerChar[SPD_BG], -1);
	TextDrawSetOutline( drawPlayerChar[SPD_BG], 0);
	TextDrawSetProportional( drawPlayerChar[SPD_BG], 1);
	TextDrawSetShadow( drawPlayerChar[SPD_BG], 1);
	TextDrawUseBox( drawPlayerChar[SPD_BG], 1);
	TextDrawBoxColor( drawPlayerChar[SPD_BG], 80);
	TextDrawTextSize( drawPlayerChar[SPD_BG], 0.000000, 120.000000);
	TextDrawSetSelectable( drawPlayerChar[SPD_BG], 0);

	// In OnPlayerConnect prefferably, we procced to create our textdraws:
	drawPlayerChar[SHOP_HEADER_VEHICLE] = TextDrawCreate(100.000000, 153.000000, "Vehicle Shop");
	TextDrawAlignment(drawPlayerChar[SHOP_HEADER_VEHICLE], 2);
	TextDrawBackgroundColor(drawPlayerChar[SHOP_HEADER_VEHICLE], -1778346416);
	TextDrawFont(drawPlayerChar[SHOP_HEADER_VEHICLE], 0);
	TextDrawLetterSize(drawPlayerChar[SHOP_HEADER_VEHICLE], 0.500000, 1.000000);
	TextDrawColor(drawPlayerChar[SHOP_HEADER_VEHICLE], -1);
	TextDrawSetOutline(drawPlayerChar[SHOP_HEADER_VEHICLE], 1);
	TextDrawSetProportional(drawPlayerChar[SHOP_HEADER_VEHICLE], 1);
	TextDrawSetSelectable(drawPlayerChar[SHOP_HEADER_VEHICLE], 0);

	drawPlayerChar[ INVERTORY_BG ] = TextDrawCreate(320.000000, 225.000000, "                ");
	TextDrawAlignment(drawPlayerChar[ INVERTORY_BG ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ INVERTORY_BG ], 255);
	TextDrawFont(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawLetterSize(drawPlayerChar[ INVERTORY_BG ], 2.289999, 18.400003);
	TextDrawColor(drawPlayerChar[ INVERTORY_BG ], -1);
	TextDrawSetOutline(drawPlayerChar[ INVERTORY_BG ], 0);
	TextDrawSetProportional(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawSetShadow(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawUseBox(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawBoxColor(drawPlayerChar[ INVERTORY_BG ], 255);
	TextDrawTextSize(drawPlayerChar[ INVERTORY_BG ], 81.000000, 285.000000);
	TextDrawSetSelectable(drawPlayerChar[ INVERTORY_BG ], 0);
	//--------------------------------------------------------------------------------
	drawPlayerChar[ INVERTORY_BG ] = TextDrawCreate(353.000000, 186.000000, "                     ");
	TextDrawAlignment(drawPlayerChar[ INVERTORY_BG ], 2);
	TextDrawBackgroundColor(drawPlayerChar[ INVERTORY_BG ], 255);
	TextDrawFont(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawLetterSize(drawPlayerChar[ INVERTORY_BG ], 3.099999, 24.499998);
	TextDrawColor(drawPlayerChar[ INVERTORY_BG ], -1);
	TextDrawSetOutline(drawPlayerChar[ INVERTORY_BG ], 0);
	TextDrawSetProportional(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawSetShadow(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawUseBox(drawPlayerChar[ INVERTORY_BG ], 1);
	TextDrawBoxColor(drawPlayerChar[ INVERTORY_BG ], 16711935);
	TextDrawTextSize(drawPlayerChar[ INVERTORY_BG ], 1.000000, 384.000000);
	TextDrawSetSelectable(drawPlayerChar[ INVERTORY_BG ], 0);
	//--------------------------------------------------------------------------------
	//TODO: Server Name
	drawPlayerChar[ HEADER_BG ] = TextDrawCreate(320.000000, 1.000000, "~w~West-RP ~p~[~w~west-rp.ru~p~]");
	//drawPlayerChar[HEADER_BG] = TextDrawCreate(320.000000, 1.000000, "~w~World Of RPG ~p~[~w~worpg.ru~p~]");
	TextDrawAlignment(drawPlayerChar[HEADER_BG], 2);
	TextDrawBackgroundColor(drawPlayerChar[HEADER_BG], -1778346416);
	TextDrawFont(drawPlayerChar[HEADER_BG], 1);
	TextDrawLetterSize(drawPlayerChar[HEADER_BG], 0.500000, 1.000000);
	TextDrawColor(drawPlayerChar[HEADER_BG], -1);
	TextDrawSetOutline(drawPlayerChar[HEADER_BG], 1);
	TextDrawSetProportional(drawPlayerChar[HEADER_BG], 1);
	TextDrawUseBox(drawPlayerChar[HEADER_BG], 1);
	TextDrawBoxColor(drawPlayerChar[HEADER_BG], -1778346416);
	TextDrawTextSize(drawPlayerChar[HEADER_BG], 1.000000, 640.000000);
	TextDrawSetSelectable(drawPlayerChar[HEADER_BG], 0);
	//--------------------------------------------------------------------------------
	//TODO: Server Time
	drawPlayerChar[HEADER_TIME] = TextDrawCreate(640.000000, 1.000000, "~w~20~p~.~w~11~p~.~w~2013 15~p~:~w~55~p~:~w~05");
	TextDrawAlignment(drawPlayerChar[HEADER_TIME], 3);
	TextDrawBackgroundColor(drawPlayerChar[HEADER_TIME], -1778346416);
	TextDrawFont(drawPlayerChar[HEADER_TIME], 1);
	TextDrawLetterSize(drawPlayerChar[HEADER_TIME], 0.500000, 1.000000);
	TextDrawColor(drawPlayerChar[HEADER_TIME], -1);
	TextDrawSetOutline(drawPlayerChar[HEADER_TIME], 1);
	TextDrawSetProportional(drawPlayerChar[HEADER_TIME], 1);
	TextDrawSetSelectable(drawPlayerChar[HEADER_TIME], 0);
	
	//--------------------------------------------------------------------------------
	/*Эффект фильма*/

	drawPlayerChar[HIGHT_TOP] = TextDrawCreate(320.000000, 0.000000, "_");
	TextDrawAlignment(drawPlayerChar[HIGHT_TOP], 2);
	TextDrawFont(drawPlayerChar[HIGHT_TOP], 1);
	TextDrawLetterSize(drawPlayerChar[HIGHT_TOP], 0.500000, 10.000000);
	TextDrawUseBox(drawPlayerChar[HIGHT_TOP], 1);
	TextDrawBoxColor(drawPlayerChar[HIGHT_TOP], 255);
	TextDrawTextSize(drawPlayerChar[HIGHT_TOP], 1.000000, 640.000000);
	TextDrawSetSelectable(drawPlayerChar[HIGHT_TOP], 0);

	drawPlayerChar[HIGHT_BOTTOM] = TextDrawCreate(320.000000, 360.000000, "_");
	TextDrawAlignment(drawPlayerChar[HIGHT_BOTTOM], 2);
	TextDrawFont(drawPlayerChar[HIGHT_BOTTOM], 1);
	TextDrawLetterSize(drawPlayerChar[HIGHT_BOTTOM], 0.500000, 10.000000);
	TextDrawUseBox(drawPlayerChar[HIGHT_BOTTOM], 1);
	TextDrawBoxColor(drawPlayerChar[HIGHT_BOTTOM], 255);
	TextDrawTextSize(drawPlayerChar[HIGHT_BOTTOM], 1.000000, 640.000000);
	TextDrawSetSelectable(drawPlayerChar[HIGHT_BOTTOM], 0);
}

