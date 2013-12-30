#include "main.h"
using namespace world::Players;

void CMD::makegang(int playerid, char* params)
{
	Player[ playerid ].isAction = PlayerAction::ACTION_GANG_MAKE;
	ShowPlayerDialog
	(
		playerid, 
		DLG_GANG_MAKE_INTRO, 
		GUI_MSG, 
		language::gang::make_Header_Intro,
		language::gang::make_Info_Intro,
		"Далее", 
		"Отмена"
	);
}

void CMD::veh(int playerid, char* params)
{
	//if (Admins::isAllow(playerid, 5) == false) return ;
	//------------------------------------------------------------
	int model;
	int cone = 0;
	int ctwo = 0;
	//------------------------------------------------------------
	if (sscanf(params, "%3d %3d %3d", &model, &cone, &ctwo) >= 1)
	{
		if ( model >= 400 && model <= 611 )
		{
			GetPlayerPos(playerid, &Player[ playerid ].pPosX, &Player[ playerid ].pPosY, &Player[ playerid ].pPosZ);
			GetPlayerFacingAngle(playerid, &Player[ playerid ].pPosR);
			int veh = world::Vehicles::sCreateVehicle(model, Player[playerid].pPosX, Player[playerid].pPosY, Player[playerid].pPosZ, Player[playerid].pPosR, cone, ctwo, -1);
			//-------------------------------------------------------------------
			SetVehicleParamsEx(veh, true, true, false, false, false, false, false);
			world::Vehicles::Vehicle[ veh ].Engine = true;
			world::Vehicles::Vehicle[ veh ].Light = true;
			world::Vehicles::Vehicle[veh].Fuel = 10.0f;
			//-------------------------------------------------------------------
			PutPlayerInVehicle(playerid, veh, 0);
		}
		else SendClientMessage(playerid, -1, language::player::cmd::useVeh);
	}
	else SendClientMessage(playerid, -1, language::player::cmd::useVeh);
}


void CMD::mm(int playerid)
{
	char msg[ 300 ] = "";
	//-------------------------------------------------------
	dialogs::genDLGItem(1, "Статистика игрока", msg);
	dialogs::genDLGItem(2, "Настройки аккаунта", msg);
	dialogs::genDLGItem(3, "Список команд сервера", msg);
	dialogs::genDLGItem(4, "Помощь по игре", msg);
	dialogs::genDLGItem(5, "Сменить персонажа", msg);
	//-------------------------------------------------------
	ShowPlayerDialog(playerid, DLG_MAIN_MENU, GUI_LIST, "[Главное меню]", msg, "Выбрать", "Отмена");
}


void CMD::addproperty(int playerid, char* params)
{
	int target = 0, price = 0;
	if (sscanf(params, "%d %d", &target, &price) == 2)
	{
		GetPlayerPos(playerid, &Player[ playerid ].pPosX, &Player[ playerid ].pPosY, &Player[ playerid ].pPosZ);
		if (target == PropertyType::prHouse)
			cHouses::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
		else if (target == PropertyType::prBank)
			cBanks::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
		else if (target == PropertyType::prBelays)
			Properties::Belays::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);	
		/*if (target == PropertyType::prAutosalon)
		Properties::Shops::ShopVehicle::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
		*/
	}
	else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид вирт. мир]");
}

void CMD::givemoney(int playerid, char* params)
{
	int u;	float m;
	if (sscanf(params, "%d %[0-9\\.\\-]f", &u, &m) == 2)
	{
		if (IsPlayerConnected(u))
		{
			if (Player[ u ].isLogged)
			{
				cPlayer::givePlayerMoney(u, m);
			}
		}
	}
	else SendClientMessage(playerid, -1, "Use: /givemoney [playerid] [money]");
}

void CMD::makeadmin(int playerid, char* params)
{
	int target = 0, value = 0;
	if (sscanf(params, "%d %d", &target, &value) == 2)
	{
		Admins::add(target, value);
	}
	else SendClientMessage(playerid, -1, "Используйте: /makeadmin [ид игрока] [уровень доступа]");
}

void CMD::setint(int playerid, char* params)
{
	int target = 0, value = 0;
	if (sscanf(params, "%d %d", &target, &value) == 2)
	{
		sprintf(query, "[Информация]: игрок(%d) был перемещен в %d интерьер");
		cPlayer::setCharInterior(target, value);
		SendClientMessage(playerid, -1, query);
	}
	else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид интерьера]");
}

void CMD::setworld(int playerid, char* params)
{
	int target = 0, value = 0;
	if (sscanf(params, "%d %d", &target, &value) == 2)
	{
		sprintf(query, "[Информация]: игрок(%d) был перемещен в %d вирт. мир");
		cPlayer::setCharWorld(target, value);
		SendClientMessage(playerid, -1, query);
	}
	else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид вирт. мир]");
}

void CMD::gotokk(int playerid, char* params)
{
	int sub[ 2 ] = { { 0 } };
	float pos[ 3 ] = { { 0 } };;
	if (sscanf(params, "%[0-9\\.\\-]f %[0-9\\.\\-]f %[0-9\\.\\-]f %d %d", &pos[ 0 ], &pos[ 1 ], &pos[ 2 ], &sub[ 0 ], &sub[ 1 ]) >= 3)
	{
		SetPlayerPos(playerid, pos[ 0 ], pos[ 1 ], pos[ 2 ]);
		SetPlayerInterior(playerid, sub[ 0 ]);
		SetPlayerVirtualWorld(playerid, sub[ 1 ]);
	}
	sprintf(params, "x: %.4f, y: %.4f, z: %.4f", pos[ 0 ], pos[ 1 ], pos[ 2 ]);
	SendClientMessage(playerid, -1, params);
	//else SendClientMessage(playerid, -1, "Use: /gotokk [Float:X] [Float:Y] [Float:Z] (optional [interiorid] [worldid])");
}

void CMD::cmd_goto(int playerid, char* params)
{
	char msg[ 144 ];
	int target = 0, subidx = 0;
	if (sscanf(params, "%d", &target))
	{
		cPlayer::getPlayerPos(target);
		cPlayer::setCharPos(playerid, Player[ target ].pPosX, Player[ target ].pPosY, Player[ target ].pPosZ, true);
		//===========================================================================================================
		sprintf(msg, "Вы телепортировались к игроку [ид: %d]", target), SendClientMessage(playerid, -1, msg);
		sprintf(msg, "Администратор %d телепортировался к вам.", playerid), SendClientMessage(target, -1, msg);
		//===========================================================================================================
	}
	else if (sscanf(params, "%d %d", &subidx, &target))
	{
		cPlayer::getPlayerPos(target);
		cPlayer::setCharPos(subidx, Player[ target ].pPosX, Player[ target ].pPosY, Player[ target ].pPosZ, true);
		//===========================================================================================================
		sprintf(msg, "Вы телепортировались к игроку [ид: %d]", target), SendClientMessage(subidx, -1, msg);
		sprintf(msg, "Администратор %d телепортировал к вам игрока [ид: %d].", playerid, target), SendClientMessage(target, -1, msg);
		sprintf(msg, "Вы телепортировали игрока [ид: %d] к игроку [ид: %d]", subidx, target), SendClientMessage(playerid, -1, msg);
		//===========================================================================================================
	}
}

void CMD::shout(const int playerid, const char* params)
{
	if (strlen(params) > 3)
	{
		char msg[144], names[48];
		//----------------------------------------------------------------
		cPlayer::getName(playerid, names);
		sprintf(msg, language::player::actions::shoutMSG, names, playerid, params);
		//----------------------------------------------------------------
		cChat::ProxDetector(playerid, RADIUS_SHOUT, msg);
		SetPlayerChatBubble(playerid, params, 0xDCDCDCFF, RADIUS_SHOUT, TIME_SHOUT);
	}
	else SendClientMessage(playerid, -1, "Используйте: /s  [текст для крика]");
}

void CMD::whisper(const int playerid, const char* params)
{
	if ( strlen(params) > 3 )
	{
		char msg[144], names[48];
		//----------------------------------------------------------------
		cPlayer::getName(playerid, names);
		sprintf(msg, language::player::actions::whisperMSG, names, playerid, params);
		//----------------------------------------------------------------
		cChat::ProxDetector(playerid, RADIUS_WHISPER, msg);
		SetPlayerChatBubble(playerid, params, 0xDCDCDCFF, RADIUS_WHISPER, TIME_SHOUT);
	}
	else SendClientMessage(playerid, -1, "Используйте: /s  [текст для шопота]");
}

void CMD::me(int playerid, char* params)
{
	if ( strlen(params) > 3 )
	{
		char msg[144], names[48];
		cPlayer::getName(playerid, names);
		//----------------------------------------------------------------
		SetPlayerChatBubble(playerid, params, ACTION_COLOR, RADIUS_ACTIONS, TIME_ACTIONS);
		sprintf(msg, "* %s %s", names, params);
		cChat::ProxDetector(playerid, RADIUS_ACTIONS, msg, ACTION_COLOR);
	}
	else SendClientMessage(playerid, -1, "Используйте: /me [text(Действие от первого лица)]");
}

void CMD::domake(int playerid, char* params)
{

}

void CMD::dotry(int playerid, char* params)
{
	char name[ 24 ] = "";
	char msg[ 144 ] = "";
	const int rnd = rand() % 2;
	cPlayer::getName(playerid, name);
	sprintf(msg, language::player::actions::tryMSG[ rnd ], name, params);
	cChat::ProxDetector(playerid, 50.0f, msg);
}

void CMD::gethere(const int u, const char * params)
{
	int id;
	char msg[144] = "";

	if ( sscanf(params, "veh %d", &id) == 1 )
	{
		if ( IsValidVehicle(id) )
		{
			case_getCar:
			SetVehiclePos(id, Player[u].pPosX, Player[u].pPosY, Player[u].pPosZ);
			SetVehicleVirtualWorld(id, Player[u].pPosW);
			LinkVehicleToInterior(id, Player[u].pPosI);
		}
		else
		{
			SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}транспорт не найден.");
		}
	}
	else if ( sscanf(params, "%d", &id) == 1 )
	{
		if ( IsPlayerConnected(id) )
		{
			cPlayer::setCharInterior(id, Player[u].pPosI);
			cPlayer::setCharWorld(id, Player[u].pPosW);

			if ( Player[id].pState == PLAYER_STATE_DRIVER )
			{
				id = Player[id].pCarid;
				goto case_getCar;
			}
			else
			{
				cPlayer::setCharPos(id, Player[u].pPosX, Player[u].pPosY, Player[u].pPosZ, true);
			}
		}
		else
		{
			SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}игрок не найден.");
		}
	}
	else
	{
		SendClientMessage(u, -1, "Используте: /gethere [ид игрока] или veh [ид транспорта]");
	}
}

void CMD::set_hp(const int u, const char * params)
{
	int id;
	float hp;
	float ar;

	if ( sscanf(params, "%d %f %f", &id, &hp, &ar) == 3 )
	{
		if ( IsPlayerConnected(id) )
		{
			cPlayer::setCharHealth(id, hp);
			cPlayer::setCharArmour(id, ar);
		}
		else
		{
			SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}игрок не найден.");
		}
	}
	else if ( sscanf(params, "%d %f", &id, &hp) == 2 )
	{
		if ( IsPlayerConnected(id) )
		{
			cPlayer::setCharHealth(id, hp);
		}
		else
		{
			SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}игрок не найден.");
		}
	}
	else
	{
		SendClientMessage(u, -1, "Используйте: /sethp [ид игрока] [кол-во здоровья] (опционально [кол-во брони])");
	}
}


PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	char cmd[ 20 ];
	char params[ 128 ];
	sscanf(cmdtext, "/%20s %128[0-9a-zA-Zа-яА-Я\\-\\. ]s", &cmd, &params);
	//==============================================================
	if ( strcmp("veh", cmd) == 0 )
	{
		if ( Admins::isAllow(playerid, 3) ) CMD::veh(playerid, params);
	}
	else if (strcmp("mm", cmd) == 0)			CMD::mm(playerid);
	else if (strcmp("mainmenu", cmd) == 0)		CMD::mm(playerid);
	else if (strcmp("makegang", cmd) == 0)		CMD::makegang(playerid, params);
	else if (strcmp("mg", cmd) == 0)			CMD::makegang(playerid, params);
//	else if (strcmp("gang", cmd) == 0)			world::Gangs::showMain(playerid);
	else if (strcmp("saveandexit", cmd) == 0)
	{
		gasProperty::cGas::saveGas();
		cBanks::saveBanks();
	}
	else if (strcmp("fill", cmd) == 0)
	{
		gasProperty::cGas::fillingVehicle(playerid);
	}
	else if (!strcmp("s", cmd) || !strcmp("shout", cmd))
	{
		CMD::shout(playerid, params);
	}
	else if (!strcmp("w", cmd) || !strcmp("whisper", cmd))
	{
		CMD::whisper(playerid, params);
	}
	else if (strcmp("me", cmd) == 0)
	{
		CMD::me(playerid, params);
	}
	/*else if (strcmp("do", cmd) == 0)
	{
		CMD::domake(playerid, params);
	}
	else if (strcmp("try", cmd) == 0)
	{
		CMD::dotry( playerid, params );
	}*/
	//----------------------------------------------------
	else if (strcmp("gotokk", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 5)) CMD::gotokk(playerid, params);
	}
	else if (strcmp("givemoney", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 5)) CMD::givemoney(playerid, params);
	}
	else if (strcmp("makeadmin", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 5)) CMD::makeadmin(playerid, params);
	}
	else if (strcmp("setint", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 2)) CMD::setint(playerid, params);
	}
	else if (strcmp("setworld", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 2)) CMD::setworld(playerid, params);
	}
	else if (strcmp("addproperty", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 4)) CMD::addproperty(playerid, params);
	}
	else if (strcmp("goto", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 2)) CMD::cmd_goto(playerid, params);
	}
	else if ( strcmp("gethere", cmd) == 0 )
	{
		if ( Admins::isAllow(playerid, 3) ) CMD::gethere(playerid, params);
	}
	/*else if ( strcmp("testtd", cmd) == 0 )
	{
		std::thread(cClass::keyGame, playerid).detach();
	}*/
	else if ( strcmp("testtd", cmd) == 0 )
	{
		extrimeDraws::func::initDraw(playerid, 0);
	}
	else if ( strcmp("sethp", cmd) == 0 )
	{
		if ( Admins::isAllow(playerid, 3) ) CMD::set_hp(playerid, params);
	}
	else if ( strcmp("makeadmin", cmd) == 0 )
	{
		if ( Admins::isAllow(playerid, 5) ) CMD::makeadmin(playerid, params);
	}
	else if (strcmp("belay", cmd) == 0)
	{
		char msg[512];
		sprintf
		(
			msg,
			"Здравствуйте вы хотите застраховать свою жизнь за %d$\
			\nДанная страховка будет покрывать часть стоимости лечения.\
			\nПри попадении в ДТП:  \t\t\t%d%%\
			\nПри огнестрельном ранении: \t\t%d%%\
			\nПри ножевом ранении ранении: \t\t%d%%\
			\nПри травмах и переломах: \t\t%d%%\
			\nПри различных заболеваниях: \t\t%d%%"
		);
		//******************************************
		ShowPlayerDialog
		(
			playerid,
			DLG_BELAY_OWNER_MAIN,
			GUI_LIST,
			"[Страховая компания]: Меню владельца",
			msg,
			language::dialogs::buttons::btnNext,
			language::dialogs::buttons::btnClose
		);
		//******************************************
	}

	return true;
}