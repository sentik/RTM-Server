#include "main.h"

struct sMiner   Jobs::Miner::cMiner::miner[MAX_SH];

void Jobs::Miner::cMiner::loadMiner()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Miners.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Miners  WHERE class_Property.property = class_Miners.id AND class_Property.type = 4");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while ((row = mysql_fetch_row(result)))
	{
		Property[countProperty].db			= atoi(row[Jobs::Miner::minerRows::db]);
		Property[countProperty].bank		= atoi(row[Jobs::Miner::minerRows::bank]);
		Property[countProperty].owner		= atoi(row[Jobs::Miner::minerRows::owner]);
		Property[countProperty].price		= atoi(row[Jobs::Miner::minerRows::price]);
		Property[countProperty].type		= atoi(row[Jobs::Miner::minerRows::type]);
		Property[countProperty].posX		= atof(row[Jobs::Miner::minerRows::posX]);
		Property[countProperty].posY		= atof(row[Jobs::Miner::minerRows::posY]);
		Property[countProperty].posZ		= atof(row[Jobs::Miner::minerRows::posZ]);
		Property[countProperty].property	= atoi(row[Jobs::Miner::minerRows::property]);
		//Property[countProperty].style		= atoi(row[Jobs::Miner::minerRows::style]);
		Property[countProperty].region		= atoi(row[Jobs::Miner::minerRows::region]);
		Property[countProperty].number		= atoi(row[Jobs::Miner::minerRows::number]);
		//--------------------------------------------------------------
		miner[i].db							= atoi(row[Jobs::Miner::minerRows::id]);
		miner[i].a1							= atoi(row[Jobs::Miner::minerRows::a1]);
		miner[i].a2							= atoi(row[Jobs::Miner::minerRows::a2]);
		miner[i].procent					= atof(row[Jobs::Miner::minerRows::proc]);
		miner[i].zp1						= atof(row[Jobs::Miner::minerRows::zp1]);
		miner[i].zp2						= atof(row[Jobs::Miner::minerRows::zp2]);
		//--------------------------------------------------------------
		Property[countProperty].link		= i;
		//--------------------------------------------------------------
		if (!i)
		{
			sprintf(query, "Железо-серебряная шахта");
			StreamerCall::Native::CreateDynamicPickup(CLOTH_PICKUP, 23, MINER_SH1_RAZDEVALKA);
			StreamerCall::Native::CreateDynamic3DTextLabel("Раздевалка\nНажмите [ALT]", -1, MINER_SH1_RAZDEVALKA, 5.0f);
		}
		else
		{
			sprintf(query, "Золото-медная шахта");
			StreamerCall::Native::CreateDynamicPickup(CLOTH_PICKUP, 23, MINER_SH2_RAZDEVALKA);
			StreamerCall::Native::CreateDynamic3DTextLabel("Раздевалка\nНажмите [ALT]", -1, MINER_SH2_RAZDEVALKA, 5.0f);
		}
		//--------------------------------------------------------------
		if (Property[countProperty].owner)
		{
			strcpy(Property[countProperty].player, row[Jobs::Miner::minerRows::oName]);
			sprintf(query, "%s\nАдрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", 
							query, 
							cProperty::getZoneName(Property[countProperty].region), 
							Property[countProperty].number, 
							Property[countProperty].player);
		}
		else
		{
			sprintf(query, "%s\nАдрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d",
							query,
							cProperty::getZoneName(Property[countProperty].region),
							Property[countProperty].number,
							Property[countProperty].price);
		}
		//--------------------------------------------------------------
		Property[countProperty].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1, 
																						Property[countProperty].posX,
																						Property[countProperty].posY, 
																						Property[countProperty].posZ, 5.0f);
		Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																						Property[countProperty].posX,
																						Property[countProperty].posY,
																						Property[countProperty].posZ);
		countProperty++;
		i++;
	}
	logprintf("[Система имущества]:\tБыло загруженно шахт\t- %d", i);
}

void Jobs::Miner::cMiner::giveMinerInstrument(const int u)
{
	SetPlayerAttachedObject(u, 8, 18634, 6, 0.065867f, 0.029999f, 0.0f, 80.586486f, 270.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1, -1);
	SetPlayerAttachedObject(u, 7, 18638, 2, 0.160290f, 0.024471f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1, -1);
}

void Jobs::Miner::cMiner::removeMinerInstrument(const int u)
{
	RemovePlayerAttachedObject(u, 8);
	RemovePlayerAttachedObject(u, 7);
}

bool Jobs::Miner::cMiner::getMinerInstrument(const int u)
{
	return (IsPlayerAttachedObjectSlotUsed(u, 8) && IsPlayerAttachedObjectSlotUsed(u, 7));
}

void Jobs::Miner::cMiner::startMinerGame(const int u)
{
	//for test
	if (Player[u].minerDraw[1] != INVALID_TEXT_DRAW)
	{
		for (int i = 0; i < 20; i++)
		{
			PlayerTextDrawDestroy(u, Player[u].minerDraw[i]);
		}
	}

	float	wtd_xpos,
			wtd_ypos,
			wtd_sx,
			wtd_sy,
			wtd_pmx,
			wtd_pmy;

	for (int i = 0; i < 20; i++)
	{
		wtd_xpos	= 1 + rand() % 600;
		wtd_ypos	= 50 + rand() % 350;
		wtd_sx		= 20 + rand() % 80;
		wtd_sy		= 20 + rand() % 80;
		wtd_pmx		= 0 + rand() % 50;
		wtd_pmy		= -60 + rand() % 120;

		Player[u].minerDraw[i] = CreatePlayerTextDraw(u, wtd_xpos, wtd_ypos, "_");
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[i], 0);
		PlayerTextDrawFont(u, Player[u].minerDraw[i], 5);
		PlayerTextDrawLetterSize(u, Player[u].minerDraw[i], 0.5, 1.0);
		PlayerTextDrawColor(u, Player[u].minerDraw[i], -1);
		PlayerTextDrawSetOutline(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawSetProportional(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawUseBox(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[i], 0);
		PlayerTextDrawTextSize(u, Player[u].minerDraw[i], wtd_sx, wtd_sy);
		PlayerTextDrawSetPreviewModel(u, Player[u].minerDraw[i], 896);
		PlayerTextDrawSetPreviewRot(u, Player[u].minerDraw[i], wtd_pmx, 0.0, wtd_pmy, 1.0);
		PlayerTextDrawSetSelectable(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawShow(u, Player[u].minerDraw[i]);
	}
	Player[u].isAction = PlayerAction::ACTION_MINERGAME;
	SelectTextDraw(u, 0x00000055);
}