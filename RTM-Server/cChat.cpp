#include "main.h"

void cChat::ProxDetector(const int u, float r, const char *text, const long int color)
{
	//------------------------------------------------
	Player[ u ].pPosI = GetPlayerInterior(u);
	Player[ u ].pPosW = GetPlayerVirtualWorld(u);
	//------------------------------------------------
	GetPlayerPos(u, &Player[ u ].pPosX, 
				 &Player[ u ].pPosY, 
				 &Player[ u ].pPosZ);
	//------------------------------------------------
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (Player[ i ].isLogged == false)			continue;
		if (Player[ i ].pPosI != Player[ u ].pPosI) continue;
		if (Player[ i ].pPosW != Player[ u ].pPosW) continue;
		//------------------------------------------------
		if (!cPlayer::isRangeOfPoint(i, r, 
										Player[ u ].pPosX, 
										Player[ u ].pPosY, 
										Player[ u ].pPosZ)) 
													continue;
		//------------------------------------------------
		SendClientMessage(i, color, text);
	}
}