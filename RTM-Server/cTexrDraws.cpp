#include "main.h"
/*
PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int, const int);
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(const int, const int);
*/


PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	/*
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{


		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == PlayerAction::ACTION_AUTH_PLAYER)
	{
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	*/
	if (draw == INVALID_TEXT_DRAW)
	{
		if (Player[u].isAction == PlayerAction::ACTION_USERENT)
		{
			Properties::Shops::ShopVehicle::endView(u);
		}
	}
	else if (draw == drawPlayerChar[REG_LEFT])			//Назад
	{
		if (Player[u].isAction == PlayerAction::ACTION_USERENT)
		{
			SendClientMessage(u, -1, "Click: Left in rent");
		}
		else
		{
			if (Player[u].pClass == 0) Player[u].pClass = MAX_CLASES - 1;
			else Player[u].pClass = clamp(Player[u].pClass - 1, 0, MAX_CLASES);
			cPlayer::preSelectClass(u, Player[u].pClass);
		}
	}
	else if (draw == drawPlayerChar[REG_SELECT])	//Выбрать
	{
		if (Player[u].isAction == PlayerAction::ACTION_USERENT)
		{
			SendClientMessage(u, -1, "Click: Select in rent");
		}
		else
		{
			cPlayer::hideRegDraws(u), dialogs::showDLGEnterName(u);
			Player[u].pClass = clamp(Player[u].pClass, 0, MAX_CLASES);
		}
	}
	else if (draw == drawPlayerChar[REG_RIGHT])		//Вперед
	{
		if (Player[u].isAction == PlayerAction::ACTION_USERENT)
		{
			SendClientMessage(u, -1, "Click: Right in rent");
		}
		else
		{
			if (Player[u].pClass == MAX_CLASES - 1) Player[u].pClass = 1;
			else Player[u].pClass = clamp(Player[u].pClass + 1, 0, MAX_CLASES);
			cPlayer::preSelectClass(u, Player[u].pClass);
		}
	}
	//----------------------------------------------------------------------------------------------------------
	return 1;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{

		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	for (int i = 0; i < MAX_CHARS; i++)
	{
		if (draw == PlayerChar[u][i].cUserus)
		{
			sprintf(query, "Clicked : %d", i);
			SendClientMessage(u, -1, query);
			//================================
			Player[i].pClass = PlayerChar[u][i].pDB;
			cPlayer::setRegClassSkin(u, i);
			//-----------------------------------
			cPlayer::unloadChars(u);
			cPlayer::loadPlayerChar(u);
			//================================
			Player[ u ].isLogged = true;
			//================================
			cPlayer::SpawnChar(u);
			break;
		}
	}
	return 1;
}
