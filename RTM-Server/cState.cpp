#include "cState.h"
#include "main.h"


void cState::callKeyStateChange(int playerid, int newkeys, int oldkeys)
{
	sprintf(query, "player: %d || key: %d||%d", playerid, newkeys, oldkeys);
	SendClientMessage(playerid, -1, query);
	switch (newkeys)
	{
		//-------------------------------------------------------------------------------------
		case KEY_SUBMISSION:
		{		   

		}
		break;
		//-------------------------------------------------------------------------------------
		case KEY_WALK:
		{
			cPlayer::getPlayerPos(playerid);
			//==========================================================
			thread threadProperty(cProperty::enterProperty, playerid);
			threadProperty.join();
			//==========================================================
			for (auto it = world::DropedGuns::DropedGun.begin(); it != world::DropedGuns::DropedGun.end(); ++it)
			{
				if (cPlayer::isRangeOfPoint(playerid, 1.0f, it->second.posX, it->second.posY, it->second.posZ))
				{
					SendClientMessage(playerid, -1, "Good!");
				}
			}
			//==========================================================
		}
		break;
		//-------------------------------------------------------------------------------------
		default:
		{
			if (Player[playerid].pSeatid == 0)
			{
				if (newkeys & Player[playerid].vcKey && Player[playerid].vcKey != 0)
				{
					cVehicle::menuVehicle(playerid);
				}
			}
		}
		break;
		//-------------------------------------------------------------------------------------
	}
}

void cState::callStateChange(int playerid, int newstate, int oldstate)
{
	sprintf(query, "player: %d || state: %d||%d", playerid, newstate, oldstate);
	SendClientMessage(playerid, -1, query);
	Player[playerid].pState = newstate;
	if (newstate == 2 || newstate == 3)
	{
		Player[playerid].pCarid = GetPlayerVehicleID(playerid);
		Player[playerid].pSeatid = GetPlayerVehicleSeat(playerid);
		if (newstate == 2)
		{
			cVehicle::showSpeed(playerid);
		}
	}
	else if (oldstate == 2 || oldstate == 3)
	{
		Player[playerid].pSeatid = -1;
		if (oldstate == 2)
		{
			cVehicle::hideSpeed(playerid);
		}
	}
}