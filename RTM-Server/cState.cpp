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
			thread threadProperty(cProperty::enterProperty);
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