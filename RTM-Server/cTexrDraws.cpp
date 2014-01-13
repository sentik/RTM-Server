#include "main.h"

PLUGIN_EXPORT bool PLUGIN_CALL  OnPlayerClickTextDraw(const int u, const int draw)
{
	//----------------------------------------------------------------------------------------------------------
	if (Player[u].isLogged)
	{
		//=========================================================================
		if (Player[ u ].status.action == PlayerAction::ACTION_AUTOSHOP)	//Действия в AS
		{
			Properties::Shops::ShopVehicle::onGUI(u, draw);
		}
		//=========================================================================
		if ( draw == INVALID_TEXT_DRAW )
		{
			if ( Player[u].status.action == PlayerAction::ACTION_PREFELGAME )
			{
				SelectTextDraw(u, 0xB7FF00FF);
			}
		}
		for ( std::vector<eTutDraws>::iterator id = extrimeDraws::tutorial::func::tutDraws.begin(); id < extrimeDraws::tutorial::func::tutDraws.end(); ++id )
		{
			if ( id->draws.close == draw )
			{
				TextDraw(id->draws.body).HideForPlayer(u);
				TextDraw(id->draws.close).HideForPlayer(u);
				TextDraw(id->draws.header).HideForPlayer(u);
				TextDraw(id->draws.text).HideForPlayer(u);

				id->countPlayers -= 1;

				if ( id->countPlayers <= 0 )
				{
					extrimeDraws::tutorial::func::tutDraws.erase(id);
				}
			}
		}
		return 1;
	}
	//----------------------------------------------------------------------------------------------------------
	if (draw == drawPlayerChar[REG_LEFT])		//Назад
	{
		if ( Player[u].base.clas == 0 ) Player[u].base.clas = MAX_CLASES - 1;
		else Player[u].base.clas = clamp(Player[u].base.clas - 1, 0, MAX_CLASES);
		cPlayer::preSelectClass(u, Player[u].base.clas);
	}
	else if (draw == drawPlayerChar[REG_SELECT])	//Выбрать
	{
		CancelSelectTextDraw(u);
		TogglePlayerSpectating(u, true);
		cPlayer::hideRegDraws(u);

		Player[u].base.clas = clamp(Player[u].base.clas, 0, MAX_CLASES);
	
		cPlayer::SpawnChar(u);
		cPlayer::setClassSkin(u);
		cPlayer::setCharPos(u, REG_SPAWN_X, REG_SPAWN_Y, REG_SPAWN_Z + 0.5f, false);
		cPlayer::setCharInterior(u, REG_SPAWN_INT);
		cPlayer::setCharWorld(u, REG_SPAWN_WOR);

		Player[ u ].status.action = PlayerAction::ACTION_NONE;

		dialogs::showDLGEnterName(u);


	//	cPlayer::Intro::cIntro::initTrain(u);
		//cPlayer::hideRegDraws(u), dialogs::showDLGEnterName(u);
		
		
	}
	else if ( draw == drawPlayerChar[REG_SELECT_ALT] )	//Выбрать
	{
		cPlayer::hideSelectedCharInfo(u);
		//================================
		cPlayer::loadPlayerChar(u, PlayerChar[u][Player[u].status.inType].pDB);
		cPlayer::unloadChars(u);
		//================================
		Player[u].status.action = PlayerAction::ACTION_NONE;
		Player[u].isLogged = true;
		//================================
		cPlayer::SpawnChar(u);
		//==========================================================================
		Player[u].draws.money = CreatePlayerTextDraw(u, 637.500000, 77.000000, "$12345678.91");
		PlayerTextDrawAlignment(u, Player[u].draws.money, 3);
		PlayerTextDrawBackgroundColor(u, Player[u].draws.money, 255);
		PlayerTextDrawFont(u, Player[u].draws.money, 3);
		PlayerTextDrawLetterSize(u, Player[u].draws.money, 0.599999, 2.199998);
		PlayerTextDrawColor(u, Player[u].draws.money, 929443071);
		PlayerTextDrawSetOutline(u, Player[u].draws.money, 1);
		PlayerTextDrawSetProportional(u, Player[u].draws.money, 1);
		PlayerTextDrawSetSelectable(u, Player[u].draws.money, 0);
	}
	else if ( draw == drawPlayerChar[REG_CREATE] )
	{
		cPlayer::hideSelectedCharInfo(u);
		cPlayer::unloadChars(u);
		cPlayer::showCharMaker(u);
	}
	else if (draw == drawPlayerChar[REG_RIGHT])		//Вперед
	{
		if ( Player[u].base.clas == MAX_CLASES - 1 ) Player[u].base.clas = 1;
		else Player[u].base.clas = clamp(Player[u].base.clas + 1, 0, MAX_CLASES);
		cPlayer::preSelectClass(u, Player[u].base.clas);
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
		if (Player[ u ].status.action == PlayerAction::ACTION_MINERGAME)
		{
			Jobs::Miner::cMiner::onGUI(u, draw);
		}
		else if (Player[u].status.action == PlayerAction::ACTION_PREFELGAME || Player[u].status.action == PlayerAction::ACTION_FELGAME)
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
			Player[u].status.inType = i;
			//================================
			cPlayer::setRegClassSkin(u, i);
			//-----------------------------------
			cPlayer::showSelectedCharInfo(u, i);
			break;
		}
	}
	//----------------------------------------------------------------------------------------------------------
	return 1;
}
