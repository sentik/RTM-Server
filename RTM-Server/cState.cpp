#include "cState.h"
#include "main.h"

std::mutex callKeyMutex;
std::mutex callStateMutex;


void cState::callKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	callKeyMutex.lock();
//	sprintf(query, "player: %d || key: %d||%d", playerid, newkeys, oldkeys);
//	SendClientMessage(playerid, -1, query);
	switch (newkeys)
	{
		//-------------------------------------------------------------------------------------
		case 1:
		case 9:
		{		   
			if (Player[playerid].status.state == PLAYER_STATE_DRIVER)
			{
				world::Vehicles::menuVehicle(playerid);
			}
			break;
		}
		//-------------------------------------------------------------------------------------
		case KEY_WALK:
		{
			cPlayer::getPlayerPos(playerid);

			if ( cPlayer::isRangeOfPoint(playerid, 1.0f, TEMP_JOB_POS) )
			{
				cPlayer::Jobs::cJobs::showDLG(playerid);
				break;
			}
			//================================================================
			//����/ ����� � ����
			thread(cProperty::enterProperty, playerid).join();
			thread(world::pickups::cPickups::actionPickups, playerid).join();
			//==========================================================
			//������������� � ��������
			if (Player[ playerid ].status.action == PlayerAction::ACTION_FELJOB)
			{
				fProperty::cFeller::actionTrees(playerid);
			}
			else if (Player[ playerid ].status.action == PlayerAction::ACTION_FARMER)
			{
				Properties::Farms::onAction(playerid);
			}
			else
			{
				Jobs::Miner::cMiner::actionPicks(playerid);
				Properties::Farms::onPickUp(playerid);
			}
			//==========================================================
			for (auto it = world::DropedGuns::DropedGun.begin(); it != world::DropedGuns::DropedGun.end(); ++it)
			{
				if (cPlayer::isRangeOfPoint(playerid, 1.0f, it->second.posX, it->second.posY, it->second.posZ))
				{
					SendClientMessage(playerid, -1, "Good!");
				}
			}
			break;
			//==========================================================
		}
		//-------------------------------------------------------------------------------------
	}
	callKeyMutex.unlock();
}

void cState::callStateChange(int playerid, int newstate, int oldstate)
{
//	sprintf(query, "player: %d || state: %d||%d", playerid, newstate, oldstate);
//	SendClientMessage(playerid, -1, query);
	callStateMutex.lock();
	Player[playerid].status.state = newstate;
	if (newstate == 2 || newstate == 3)
	{
		Player[playerid].status.vehicle = GetPlayerVehicleID(playerid);
		Player[playerid].status.seatid = GetPlayerVehicleSeat(playerid);
		PlayAudioStreamForPlayer(playerid, world::radio::cRadio::Radio.at(world::Vehicles::Vehicle[Player[playerid].status.vehicle].radio).url,
		 0.0, 0.0, 0.0, 50.0, false);
		if (newstate == 2)
		{
			world::Vehicles::showSpeed(playerid);
		}
	}
	else if (oldstate == 2 || oldstate == 3)
	{
		StopAudioStreamForPlayer(playerid);
		Player[playerid].status.seatid = -1;
		if (oldstate == 2)
		{
			world::Vehicles::hideSpeed(playerid);
		}
	}
	callStateMutex.unlock();
}