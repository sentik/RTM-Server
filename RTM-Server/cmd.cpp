#include "main.h"
using namespace world::Players;

void CMD::makegang(int playerid, char* params)
{
	Player[ playerid ].isAction = PlayerAction::ACTION_GANG_MAKE;
	ShowPlayerDialog(playerid, DLG_GANG_MAKE_INTRO, GUI_MSG, "[Создание банды] Информация", "Для создания банды необходимо пройти 3 этапа:\n1. Указать название банды \n2. Указать цвет банды \n3. Выбрать логово для банды", "Далее", "Отмена");
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

}


PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	char cmd[ 20 ];
	char params[ 128 ];
	sscanf(cmdtext, "/%20s %128[0-9a-zA-Zа-яА-Я\\-\\. ]s", &cmd, &params);
	//==============================================================
	if (strcmp("veh", cmd) == 0)				CMD::veh(playerid, params);
	else if (strcmp("mm", cmd) == 0)			CMD::mm(playerid);
	else if (strcmp("mainmenu", cmd) == 0)		CMD::mm(playerid);
	else if (strcmp("makegang", cmd) == 0)		CMD::makegang(playerid, params);
	else if (strcmp("mg", cmd) == 0)			CMD::makegang(playerid, params);
	else if (strcmp("gang", cmd) == 0)			world::Gangs::showMain(playerid);
	else if (strcmp("saveandexit", cmd) == 0)
	{
		gasProperty::cGas::saveGas();
		cBanks::saveBanks();
	}
	else if (strcmp("fill", cmd) == 0)
	{
		gasProperty::cGas::fillingVehicle(playerid);
	}
	//----------------------------------------------------
	else if (strcmp("tah", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 5))
		{
		}
	}
	else if (strcmp("gotokk", cmd) == 0)
	{
		float pos[ 3 ];
		int sub[ 2 ];
		sub[ 0 ] = 0;
		sub[ 1 ] = 0;
		if (sscanf(params, "%[\\-0-9\\.]lf %e %le %d %d", &pos[ 0 ], &pos[ 1 ], &pos[ 2 ], &sub[ 0 ], &sub[ 1 ]) >= 3)
		{
			SetPlayerPos(playerid, pos[ 0 ], pos[ 1 ], pos[ 2 ]);
			SetPlayerInterior(playerid, sub[ 0 ]);
			SetPlayerVirtualWorld(playerid, sub[ 1 ]);
		}
		sprintf(params, "x: %.4f, y: %.4f, z: %.4f", pos[ 0 ], pos[ 1 ], pos[ 2 ]);
		SendClientMessage(playerid, -1, params);
		//else SendClientMessage(playerid, -1, "Use: /gotokk [Float:X] [Float:Y] [Float:Z] (optional [interiorid] [worldid])");
	}
	else if (strcmp("givemoney", cmd) == 0)
	{
		if (Admins::isAllow(playerid, 5))
		{
			int u;
			float m;
			if (sscanf(params, "%d %f", &u, &m) == 2)
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
	}
	else if (strcmp("makeadmin", cmd) == 0)
	{
		int target = 0, value = 0;
		if (Admins::isAllow(playerid, 5) == false) return true;
		if (sscanf(params, "%d %d", &target, &value) == 2)
		{
			Admins::add(target, value);
		}
		else SendClientMessage(playerid, -1, "Используйте: /makeadmin [ид игрока] [уровень доступа]");
	}
	else if (strcmp("setint", cmd) == 0)
	{
		int target = 0, value = 0;
		if (Admins::isAllow(playerid, 2) == false) return true;
		if (sscanf(params, "%d %d", &target, &value) == 2)
		{
			sprintf(query, "[Информация]: игрок(%d) был перемещен в %d интерьер");
			cPlayer::setCharInterior(target, value);
			SendClientMessage(playerid, -1, query);
		}
		else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид интерьера]");
	}
	else if (strcmp("setworld", cmd) == 0)
	{
		int target = 0, value = 0;
		if (Admins::isAllow(playerid, 2) == false) return true;
		if (sscanf(params, "%d %d", &target, &value) == 2)
		{
			sprintf(query, "[Информация]: игрок(%d) был перемещен в %d вирт. мир");
			cPlayer::setCharWorld(target, value);
			SendClientMessage(playerid, -1, query);
		}
		else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид вирт. мир]");
	}
	//----------------------------------------------------
	else if (strcmp("addproperty", cmd) == 0)
	{
		int target = 0,  price = 0;
		//if (Admins::isAllow(playerid, 4) == false) return true;
		if (sscanf(params, "%d %d", &target, &price) == 2)
		{
			GetPlayerPos(playerid, &Player[ playerid ].pPosX, &Player[ playerid ].pPosY, &Player[ playerid ].pPosZ);
			if (target == PropertyType::prHouse)
				cHouses::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
			else if(target == PropertyType::prBank)
				cBanks::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
			/*if (target == PropertyType::prAutosalon)
				Properties::Shops::ShopVehicle::create(price, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ);
		*/
		}
		else SendClientMessage(playerid, -1, "Используйте: /setint [ид игрока] [ид вирт. мир]");
	}
	return true;
}