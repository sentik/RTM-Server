#include "main.h"

void cChat::ProxDetector(const int u, float r, const char *text, const long int color)
{
	//------------------------------------------------
	Player[ u ].pos.interior = GetPlayerInterior(u);
	Player[ u ].pos.world = GetPlayerVirtualWorld(u);
	//------------------------------------------------
	GetPlayerPos(u, &Player[ u ].pos.x, 
				 &Player[ u ].pos.y, 
				 &Player[ u ].pos.z);
	//------------------------------------------------
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (Player[ i ].isLogged == false)			continue;
		if (Player[ i ].pos.interior != Player[ u ].pos.interior) continue;
		if (Player[ i ].pos.world != Player[ u ].pos.world) continue;
		//------------------------------------------------
		if (!cPlayer::isRangeOfPoint(i, r, 
										Player[ u ].pos.x, 
										Player[ u ].pos.y, 
										Player[ u ].pos.z)) 
													continue;
		//------------------------------------------------
		SendClientMessage(i, color, text);
	}
}