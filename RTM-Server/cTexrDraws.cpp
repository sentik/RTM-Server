#include "main.h"
PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int, const int);
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(const int, const int);



PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{


		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == ACTION_AUTH_PLAYER)
	{
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (draw == drawPlayerChar[REG_LEFT])			//Назад
	{
		if (Player[u].pClass == 0) Player[u].pClass = MAX_CLASES - 1;
		else Player[u].pClass = clamp(Player[u].pClass - 1, 0, MAX_CLASES);
		cPlayer::preSelectClass(u, Player[u].pClass);
	}
	else if (draw == drawPlayerChar[REG_SELECT])	//Выбрать
	{
		cPlayer::hideRegDraws(u), dialogs::showDLGEnterName(u);
		Player[u].pClass = clamp(Player[u].pClass, 0, MAX_CLASES);
	}
	else if (draw == drawPlayerChar[REG_RIGHT])		//Вперед
	{
		if (Player[u].pClass == MAX_CLASES - 1) Player[u].pClass = 1;
		else Player[u].pClass = clamp(Player[u].pClass + 1, 0, MAX_CLASES);
		cPlayer::preSelectClass(u, Player[u].pClass);
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
			//================================
			Player[u].isLogged = true;
			//-----------------------------------
			cPlayer::unloadChars(u);
			cPlayer::loadPlayerChar(u);
			cPlayer::SpawnChar(u);
			break;
		}
	}
	return 1;
}