#include "main.h"
using namespace world::Players;


void CMD::veh(int playerid, char* params)
{
	if (Admins::isAllow(playerid, 5) == false) return ;
	//------------------------------------------------------------
	int model;
	int cone = 0;
	int ctwo = 0;
	//------------------------------------------------------------
	if (sscanf(params, "%3d %3d %3d", &model, &cone, &ctwo) >= 1)
	{
		GetPlayerPos(playerid, &Player[ playerid ].pPosX, &Player[ playerid ].pPosY, &Player[ playerid ].pPosZ);
		GetPlayerFacingAngle(playerid, &Player[ playerid ].pPosR);
		int veh = CreateVehicle(model, Player[ playerid ].pPosX, Player[ playerid ].pPosY, Player[ playerid ].pPosZ, Player[ playerid ].pPosR, cone, ctwo, -1);
		//-------------------------------------------------------------------
		SetVehicleParamsEx(veh, true, true, false, false, false, false, false);
		world::Vehicles::Vehicle[ veh ].Engine = true;
		world::Vehicles::Vehicle[ veh ].Light = true;
		world::Vehicles::Vehicle[veh].Fuel = 100.0f;
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


PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char * cmdtext)
{
	char cmd[ 20 ];
	char params[ 128 ];
	sscanf(cmdtext, "/%20s %128[0-9a-zA-Zа-яА-Я ]s", &cmd, &params);
	//==============================================================
	if (strcmp("veh", cmd) == 0)				CMD::veh(playerid, params);
	else if (strcmp("mm", cmd) == 0)			CMD::mm(playerid);
	else if (strcmp("mainmenu", cmd) == 0)		CMD::mm(playerid);
	
	else if (strcmp("tfill", cmd) == 0)
	{
		Player[ playerid ].pDB = 1;
		world::Players::invertory::load(playerid);
		world::Players::invertory::show(playerid);
		//gasProperty::cGas::fillingVehicle(playerid);
	}
	else if (strcmp("fel", cmd) == 0)
	{
		if (fProperty::cFeller::getFellerTool(playerid))
		{
			fProperty::cFeller::removeFellerTool(playerid);
		}
		else
		{
			fProperty::cFeller::giveFellerTool(playerid);
		}
	}
	else if (strcmp("gotokk", cmd) == 0)
	{
		float pos[ 3 ];
		int sub[ 2 ];
		sub[ 0 ] = 0;
		sub[ 1 ] = 0;
		if (sscanf(params, "%f %f %f %d %d", &pos[ 0 ], &pos[ 1 ], &pos[ 2 ], &sub[ 0 ], &sub[ 1 ]) >= 3)
		{
			SetPlayerPos(playerid, pos[ 0 ], pos[ 1 ], pos[ 2 ]);
			SetPlayerInterior(playerid, sub[ 0 ]);
			SetPlayerVirtualWorld(playerid, sub[ 1 ]);
		}
		else SendClientMessage(playerid, -1, "Use: /gotokk [Float:X] [Float:Y] [Float:Z] (optional [interiorid] [worldid])");
	}
	return true;
}