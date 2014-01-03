#include "main.h"

PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{
		//=========================================================================
		if (Player[ u ].isAction == PlayerAction::ACTION_AUTOSHOP)	//Действия в AS
		{
			Properties::Shops::ShopVehicle::onGUI(u, draw);
		}
		//=========================================================================
		if ( draw == INVALID_TEXT_DRAW )
		{
			if ( Player[u].isAction == PlayerAction::ACTION_PREFELGAME )
			{
				SelectTextDraw(u, 0xB7FF00FF);
			}
		}
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isAction == PlayerAction::ACTION_AUTH_PLAYER)		return 1;
	//----------------------------------------------------------------------------------------------------------
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

		Player[ u ].pClass = clamp(Player[ u ].pClass, 0, MAX_CLASES);
	
		cPlayer::SpawnChar(u);
		cPlayer::setClassSkin(u);
		cPlayer::setCharPos(u, REG_SPAWN_X, REG_SPAWN_Y, REG_SPAWN_Z, false);
		cPlayer::setCharInterior(u, REG_SPAWN_INT);
		cPlayer::setCharWorld(u, REG_SPAWN_WOR);

		Player[ u ].isAction = PlayerAction::ACTION_NONE;

		dialogs::showDLGEnterName(u);


	//	cPlayer::Intro::cIntro::initTrain(u);
		//cPlayer::hideRegDraws(u), dialogs::showDLGEnterName(u);
		
		
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
		else
		{
			for ( std::vector<eTutDraws>::iterator id = extrimeDraws::tutorial::func::tutDraws.begin(); id < extrimeDraws::tutorial::func::tutDraws.end(); ++id )
			{
				if ( id->draws.close == draw )
				{
					PlayerTextDrawDestroy(u, id->draws.body);
					PlayerTextDrawDestroy(u, id->draws.close);
					PlayerTextDrawDestroy(u, id->draws.header);
					PlayerTextDrawDestroy(u, id->draws.text);

					extrimeDraws::tutorial::func::tutDraws.erase(id);
				}
			}
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
			Player[u].tCents = CreatePlayerTextDraw(u, 637.500000, 77.000000, "$12345678.91");
			PlayerTextDrawAlignment(u, Player[u].tCents, 3);
			PlayerTextDrawBackgroundColor(u, Player[u].tCents, 255);
			PlayerTextDrawFont(u, Player[u].tCents, 3);
			PlayerTextDrawLetterSize(u, Player[u].tCents, 0.599999, 2.199998);
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
