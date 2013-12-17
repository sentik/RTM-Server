#include "main.h"

PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{
		//=========================================================================
		if (Player[ u ].isAction == PlayerAction::ACTION_USERENT)	//Действия в AS
		{
			Properties::Shops::ShopVehicle::onGUI(u, draw);
		}
		//=========================================================================
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == PlayerAction::ACTION_AUTH_PLAYER)		return 1;
	//----------------------------------------------------------------------------------------------------------

	if (draw == INVALID_TEXT_DRAW)
	{
		if (Player[u].isAction == PlayerAction::ACTION_PREFELGAME)
		{
			SelectTextDraw(u, 0xB7FF00FF);
		}
	}
	else if (draw == drawPlayerChar[REG_LEFT])		//Назад
	{
		if (Player[u].pClass == 0) Player[u].pClass = MAX_CLASES - 1;
		else Player[u].pClass = clamp(Player[u].pClass - 1, 0, MAX_CLASES);
		cPlayer::preSelectClass(u, Player[u].pClass);
	}
	else if (draw == drawPlayerChar[REG_SELECT])	//Выбрать
	{
		CancelSelectTextDraw(u);
		TogglePlayerSpectating(u, true);
		cPlayer::hideRegDraws(u);
		cPlayer::Intro::cIntro::initTrain(u);
		//cPlayer::hideRegDraws(u), dialogs::showDLGEnterName(u);
		//Player[u].pClass = clamp(Player[u].pClass, 0, MAX_CLASES);
		
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
		//=========================================================
		if (Player[ u ].isAction == PlayerAction::ACTION_MINERGAME)
		{
			Jobs::Miner::cMiner::onGUI(u, draw);
		}
		else if (Player[u].isAction == PlayerAction::ACTION_PREFELGAME || Player[u].isAction == PlayerAction::ACTION_FELGAME)
		{
			fProperty::cFeller::onGUI(u, draw);
		}
		//=========================================================
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	for (int i = 0; i < MAX_CHARS; i++)
	{
		if (draw == PlayerChar[u][i].cUserus)
		{
			logprintf("Clicked : %d[%d] || db:%d || class: %d", i,u, PlayerChar[ u ][ i ].pDB, PlayerChar[ u ][ i ].pClass);
			//================================
			cPlayer::setRegClassSkin(u, i);
			//-----------------------------------
			cPlayer::loadPlayerChar(u, PlayerChar[ u ][ i ].pDB);
			cPlayer::unloadChars(u);
			//================================
			Player[ u ].isAction = PlayerAction::ACTION_NONE;
			Player[ u ].isLogged = true;
			//================================
			cPlayer::SpawnChar(u);
			//==========================================================================
			Player[u].tCents = CreatePlayerTextDraw(u, 636.300000, 77.000000, "$12345678.91");
			PlayerTextDrawAlignment(u, Player[u].tCents, 3);
			PlayerTextDrawBackgroundColor(u, Player[u].tCents, 255);
			PlayerTextDrawFont(u, Player[u].tCents, 3);
			PlayerTextDrawLetterSize(u, Player[u].tCents, 0.589999, 2.299998);
			PlayerTextDrawColor(u, Player[u].tCents, 929443071);
			PlayerTextDrawSetOutline(u, Player[u].tCents, 1);
			PlayerTextDrawSetProportional(u, Player[u].tCents, 1);
			PlayerTextDrawSetSelectable(u, Player[u].tCents, 0);
			break;
		}
	}
	//----------------------------------------------------------------------------------------------------------
	return 1;
}
