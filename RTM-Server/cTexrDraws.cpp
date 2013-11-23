#include "main.h"
/*
PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int, const int);
PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerClickPlayerTextDraw(const int, const int);
*/


/*

const int shop = Property[ Player[ u ].inIndex ].link;
//======================================================
if (left) vehicle[ shop ].Item--;
else   	  vehicle[ shop ].Item++;
//======================================================

*/


PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{
		//=========================================================================
		if (Player[ u ].isAction == PlayerAction::ACTION_USERENT)	//Действия в AS
		{
			using namespace Properties::Shops;
			const int shop = Property[ Player[ u ].inIndex ].link;
			//----------------------------------------------------------------------
			if (draw == INVALID_TEXT_DRAW)
			{
				Properties::Shops::ShopVehicle::endView(u);
			}
			//----------------------------------------------------------------------			
			else if (draw == drawPlayerChar[ REG_LEFT ])			//Назад
			{
				ShopVehicle::vehicle[ shop ].Item = clamp(ShopVehicle::vehicle[ shop ].Item - 1, 0, 100);
				ShopVehicle::viewList(u, ShopVehicle::vehicle[ shop ].Item);
			}
			else if(draw == drawPlayerChar[ REG_SELECT ])	//Выбрать
			{

			}
			else if (draw == drawPlayerChar[ REG_RIGHT ])	//Вперед
			{
				ShopVehicle::vehicle[ shop ].Item = clamp(ShopVehicle::vehicle[ shop ].Item + 1, 0, 100);
				ShopVehicle::viewList(u, ShopVehicle::vehicle[ shop ].Item);
			}
		}
		//=========================================================================
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == PlayerAction::ACTION_AUTH_PLAYER)		return 1;
	//----------------------------------------------------------------------------------------------------------

	if (draw == INVALID_TEXT_DRAW)
	{

	}
	else if (draw == drawPlayerChar[REG_LEFT])			//Назад
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
	/*if (Player[u].isLogged)
	{

		return 1;
	}*/
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == PlayerAction::ACTION_MINERGAME)
	{
		for (int i = 0; i < 20; i++)
		{
			if (draw == Player[u].minerDraw[i])
			{
				PlayerTextDrawHide(u, Player[u].minerDraw[i]);
				PlayerTextDrawColor(u, Player[u].minerDraw[i], (0 + rand() % 2) ? (0xFF000088) : (0xB7FF0088));
				PlayerTextDrawSetSelectable(u, Player[u].minerDraw[i], false);
				PlayerTextDrawShow(u, Player[u].minerDraw[i]);
			}
		}
		return true;
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
			Player[ u ].isAction = PlayerAction::ACTION_NONE;
			Player[ u ].isLogged = true;
			//================================
			cPlayer::SpawnChar(u);
			break;
		}
	}
	return 1;
}
