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
			thread threadProperty(cProperty::enterProperty, playerid);
			threadProperty.join();
		}
		break;
		//-------------------------------------------------------------------------------------
		default:
		{

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
	}
	else if (oldstate == 2 || oldstate == 3)
	{
		Player[playerid].pSeatid = -1;
	}
}