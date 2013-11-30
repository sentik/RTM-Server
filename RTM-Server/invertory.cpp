#include "main.h"
//--------------------------------------------
using namespace world::Players;
vector<eInvertory> invertory::inv[ 1000 ];
vector<eInvertory> invertory::loot[ 1000 ];
//--------------------------------------------

void invertory::load(const int u)
{
	MYSQL_ROW row;
	inv[u].reserve(64);
	loot[ u ].reserve(12);
	//=========================================================================
	sprintf(query, "SELECT * FROM player_Invertory WHERE owner = %d", Player[u].pDB);
	mysql_query(con, query);
	//=========================================================================
	MYSQL_RES *result = mysql_store_result(con);
	while (( row = mysql_fetch_row(result) ))
	{
		eInvertory tmp;
		//----------------------------
		tmp.db		= atoi(row[ 0 ]);
		tmp.model	= atoi(row[ 2 ]);
		tmp.amount  = atoi(row[ 3 ]);
		//----------------------------
		inv[ u ].insert(inv[ u ].end(), tmp);
		//----------------------------
		sprintf(query, "db: %d || model: %d || %d", tmp.db, tmp.model, tmp.amount);
		logprintf(query);
		SendClientMessage(u, -1, query);
	}
	mysql_free_result(result);
	//--------------------------------------------------------------------------------
	sprintf(query, "SELECT * FROM player_Loot WHERE owner = %d", Player[ u ].pDB);
	mysql_query(con, query);
	//=========================================================================
	result = mysql_store_result(con);
	while (( row = mysql_fetch_row(result) ))
	{
		eInvertory tmp;
		//----------------------------
		tmp.db = atoi(row[ 0 ]);
		tmp.model = atoi(row[ 2 ]);
		tmp.amount = atoi(row[ 3 ]);
		//----------------------------
		loot[ u ].insert(inv[ u ].end(), tmp);
		//----------------------------
	}
	mysql_free_result(result);
}

void invertory::show(const int u)
{
	int lineX = 0;
	int lineY = 0;
	SendClientMessage(u, -1, "begin");

	for (auto it = inv[ u ].begin(); it != inv[ u ].end(); it++)
	{
		if (lineX == 6)
		{
			lineX = 0;
			lineY++;
		}
		it->obj = CreatePlayerTextDraw(u, 215.000 + 50 * lineX, 240.000000 + 30 * lineY, "         ");
		PlayerTextDrawAlignment(u, it->obj, 2);
		PlayerTextDrawBackgroundColor(u, it->obj, 255);
		PlayerTextDrawFont(u, it->obj, 1);
		PlayerTextDrawLetterSize(u, it->obj, 0.800000, 2.300000);
		PlayerTextDrawColor(u, it->obj, -1);
		PlayerTextDrawSetOutline(u, it->obj, 0);
		PlayerTextDrawSetProportional(u, it->obj, 1);
		PlayerTextDrawSetShadow(u, it->obj, 1);
		PlayerTextDrawUseBox(u, it->obj, 1);
		PlayerTextDrawBoxColor(u, it->obj, -1);
		PlayerTextDrawTextSize(u, it->obj, 0.000000, 40.000000);
		PlayerTextDrawSetSelectable(u, it->obj, 0);
		PlayerTextDrawShow(u, it->obj);
		SendClientMessage(u, -1, "qqqq");


		lineX++; 
	}


	/*Textdraw1 = CreatePlayerTextDraw(playerid, 215.000000, 241.000000, "         ");
	PlayerTextDrawAlignment(playerid, Textdraw1, 2);
	PlayerTextDrawBackgroundColor(playerid, Textdraw1, 255);
	PlayerTextDrawFont(playerid, Textdraw1, 1);
	PlayerTextDrawLetterSize(playerid, Textdraw1, 0.800000, 2.300000);
	PlayerTextDrawColor(playerid, Textdraw1, -1);
	PlayerTextDrawSetOutline(playerid, Textdraw1, 0);
	PlayerTextDrawSetProportional(playerid, Textdraw1, 1);
	PlayerTextDrawSetShadow(playerid, Textdraw1, 1);
	PlayerTextDrawUseBox(playerid, Textdraw1, 1);
	PlayerTextDrawBoxColor(playerid, Textdraw1, -1);
	PlayerTextDrawTextSize(playerid, Textdraw1, 0.000000, 40.000000);
	PlayerTextDrawSetSelectable(playerid, Textdraw1, 0);*/






}

void invertory::hide(const int u)
{
	for (auto it = loot[ u ].begin(); it != loot[ u ].end(); it++)
	{
		PlayerTextDrawDestroy(u, it->obj);
	}
	//=========================================================
	for (auto it = inv[ u ].begin(); it != inv[ u ].end(); it++)
	{
		PlayerTextDrawDestroy(u, it->obj);
	}
}


void invertory::onGUI(const int u, const int draw)
{

}
