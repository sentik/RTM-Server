#include "main.h"

struct eFeller  fProperty::cFeller::Feller[MAX_FELL];
int fProperty::cFeller::models[ 8 ];

void fProperty::cFeller::loadFeller()
{
	models[1] = 656;
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT class_Property.*, class_Feller.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Feller  WHERE class_Property.property = class_Feller.id AND class_Property.type = 6");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while ((row = mysql_fetch_row(result)))
	{
		Property[countProperty].db			= atoi(row[fProperty::rowsFeller::id]);
		Property[countProperty].bank		= atoi(row[fProperty::rowsFeller::bank]);
		Property[countProperty].owner		= atoi(row[fProperty::rowsFeller::owner]);
		Property[countProperty].price		= atoi(row[fProperty::rowsFeller::price]);
		Property[countProperty].type		= atoi(row[fProperty::rowsFeller::type]);
		Property[countProperty].posX		= atof(row[fProperty::rowsFeller::x]);
		Property[countProperty].posY		= atof(row[fProperty::rowsFeller::y]);
		Property[countProperty].posZ		= atof(row[fProperty::rowsFeller::z]);
		Property[countProperty].property	= atoi(row[fProperty::rowsFeller::property]);
		Property[countProperty].region		= atoi(row[fProperty::rowsFeller::region]);
		Property[countProperty].number		= atoi(row[fProperty::rowsFeller::number]);
		//--------------------------------------------------------------
		fProperty::cFeller::Feller[i].db	= atoi(row[fProperty::rowsFeller::db]);
		fProperty::cFeller::Feller[i].zp	= atof(row[fProperty::rowsFeller::zp]);
		fProperty::cFeller::Feller[i].am	= atof(row[fProperty::rowsFeller::am]);
		fProperty::cFeller::Feller[i].maxX	= atof(row[fProperty::rowsFeller::maxX]);
		fProperty::cFeller::Feller[i].maxY	= atof(row[fProperty::rowsFeller::maxY]);
		fProperty::cFeller::Feller[i].maxZ	= atof(row[fProperty::rowsFeller::maxZ]);
		fProperty::cFeller::Feller[i].minX	= atof(row[fProperty::rowsFeller::minX]);
		fProperty::cFeller::Feller[i].minY	= atof(row[fProperty::rowsFeller::minY]);
		fProperty::cFeller::Feller[i].minZ	= atof(row[fProperty::rowsFeller::minZ]);
		//--------------------------------------------------------------
		strcpy(fProperty::cFeller::Feller[i].name, row[fProperty::rowsFeller::name]);
		//--------------------------------------------------------------
		Property[countProperty].link = i;
		//--------------------------------------------------------------
		if (Property[countProperty].owner)
		{
			strcpy(Property[countProperty].player, row[fProperty::rowsFeller::pname]);
			sprintf(query, "{FFFFFF}Лесопилка: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", gasProperty::cGas::Gas[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].player);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}Лесопилка: {FF0000}%s\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", gasProperty::cGas::Gas[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		//-----------------------------------------------------------------------------------------------------------
		Property[countProperty].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
			Property[countProperty].posX,
			Property[countProperty].posY,
			Property[countProperty].posZ, 30.0f);
		//-----------------------------------------------------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно лесопилок \t- %d", i);
}

void fProperty::cFeller::loadTrees()
{
	int slot = 0;
	int fell = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM class_Feller_items ORDER BY fid");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------
	while (( row = mysql_fetch_row(result) ))
	{
		if (fell == atoi(row[ 1 ]) - 1 && slot < MAX_FELL_TREE) slot++;
		else
		{
			fell = atoi(row[ 1 ]) - 1;
			slot = 0;
		}
		//==================================================
		Feller[ fell ].Trees[ slot ].db		= atoi(row[ 0 ]);
		Feller[ fell ].Trees[ slot ].proc	= atof(row[ 2 ]);
		Feller[ fell ].Trees[ slot ].x		= atof(row[ 3 ]);
		Feller[ fell ].Trees[ slot ].y		= atof(row[ 4 ]);
		Feller[ fell ].Trees[ slot ].z		= atof(row[ 5 ]); 
		Feller[ fell ].Trees[ slot ].type	= atoi(row[ 6 ]);
		//==================================================
		Feller[ fell ].Trees[ slot ].obj = StreamerCall::Native::CreateDynamicObject(
											models[ Feller[ fell ].Trees[ slot ].type ],
											Feller[ fell ].Trees[ slot ].x,
											Feller[ fell ].Trees[ slot ].y,
											Feller[fell].Trees[slot].z - TREE_OFFSET,
											0.0, 0.0, 0.0, 0, 0);
		//==================================================
		StreamerCall::Native::MoveDynamicObject(
								Feller[fell].Trees[slot].obj,
								Feller[fell].Trees[slot].x,
								Feller[fell].Trees[slot].y,
								Feller[fell].Trees[slot].z, TREE_SPEED);
	}
}

void fProperty::cFeller::onGUI(const int u, const int draw)
{
	char msg[112];
	char minerAmount, minerColor;
	float ftmp;
	for (int i = 0; i < 20; i++)
	{
		if (draw == Player[u].minerDraw[i])
		{
			minerColor = 0 + rand() % 6;
			PlayerTextDrawHide(u, Player[u].minerDraw[i]);
			//------------------------------------------------------------------------------------------------------
			if (minerColor == 0)
			{
				minerAmount = 1 + rand() % 8;
				Player[u].aMinerA -= minerAmount;
				sprintf(msg, language::jobs::feller::actionOne, minerAmount, Player[u].aMinerA);
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xFF000088);
			}
			else if (minerColor == 1)
			{
				minerAmount = 1 + rand() % 24;
				Player[u].aMinerA += minerAmount;
				sprintf(msg, language::jobs::feller::actionTwo, minerAmount, Player[u].aMinerA);
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xB7FF0088);
			}
			else if (minerColor == 5)
			{
				minerAmount = 1 + rand() % 300;
				GetPlayerHealth(u, &ftmp);
				SetPlayerHealth(u, ftmp - (minerAmount/100));
				sprintf(msg, language::jobs::feller::actionFour, minerAmount);
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xB700B788);
			}
			else
			{
				strcpy(msg, language::jobs::feller::actionThree);
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xFFAF0088);
			}
			//------------------------------------------------------------------------------------------------------
			PlayerTextDrawSetSelectable(u, Player[u].minerDraw[i], false);
			PlayerTextDrawShow(u, Player[u].minerDraw[i]);
			SendClientMessage(u, -1, msg);
		}
	}
}

void fProperty::cFeller::giveFellerTool(const int u)
{
	Player[u].isAction = PlayerAction::ACTION_FELJOB;
	SetPlayerAttachedObject(u, 5, 19036, 2, 0.097140, 0.030915, 0.0, 85.865409, 87.990005, 0.0, 1.0, 1.0, 1.0, -1, -1);
	SetPlayerAttachedObject(u, 4, 341, 6, -0.029709, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, -1, -1);
}

bool fProperty::cFeller::getFellerTool(const int u)
{
	return (IsPlayerAttachedObjectSlotUsed(u, 5) && IsPlayerAttachedObjectSlotUsed(u, 4));
}

void fProperty::cFeller::removeFellerTool(const int u)
{
	Player[u].isAction = PlayerAction::ACTION_NONE;
	RemovePlayerAttachedObject(u, 5); 
	RemovePlayerAttachedObject(u, 4);
}

void fProperty::cFeller::startFellerGame(const int u)
{
	float	wtd_xpos,
		wtd_ypos,
		wtd_sx,
		wtd_sy,
		wtd_pmx,
		wtd_pmy;

	for (int i = 0; i < 20; i++)
	{
		wtd_xpos = 1 + rand() % 600;
		wtd_ypos = 50 + rand() % 350;
		wtd_sx = 40 + rand() % 80;
		wtd_sy = 40 + rand() % 80;
		wtd_pmx = 0 + rand() % 50;
		wtd_pmy = -60 + rand() % 120;

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
		PlayerTextDrawSetPreviewModel(u, Player[u].minerDraw[i], 1463);
		PlayerTextDrawSetPreviewRot(u, Player[u].minerDraw[i], wtd_pmx, 0.0, wtd_pmy, 1.0);
		PlayerTextDrawSetSelectable(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawShow(u, Player[u].minerDraw[i]);
	}
	Player[u].isAction = PlayerAction::ACTION_FELGAME;
	SelectTextDraw(u, 0x00000055);
}

void fProperty::cFeller::actionTrees(const int u)
{
	for (int fell = 0; fell < MAX_FELL; fell++)
	{
		if (cPlayer::isPlayerInCube(u, fProperty::cFeller::Feller[fell].minX, fProperty::cFeller::Feller[fell].minY, fProperty::cFeller::Feller[fell].minZ, fProperty::cFeller::Feller[fell].maxX, fProperty::cFeller::Feller[fell].maxY, fProperty::cFeller::Feller[fell].maxZ))
		{
			for (int slot = 0; slot < MAX_FELL_TREE; slot++)
			{
				if (cPlayer::isRangeOfPoint(u, 2.5f, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y, fProperty::cFeller::Feller[fell].Trees[slot].z))
				{
					fProperty::cFeller::startFellerGame(u);
					break;
				}
			}
			break;
		}
	}
}