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
			sprintf(query, "������-���������� �����");
			StreamerCall::Native::CreateDynamicPickup(CLOTH_PICKUP, 23, MINER_SH1_RAZDEVALKA);
			StreamerCall::Native::CreateDynamic3DTextLabel("����������\n������� [ALT]", -1, MINER_SH1_RAZDEVALKA, 5.0f);
		}
		else
		{
			sprintf(query, "������-������ �����");
			StreamerCall::Native::CreateDynamicPickup(CLOTH_PICKUP, 23, MINER_SH2_RAZDEVALKA);
			StreamerCall::Native::CreateDynamic3DTextLabel("����������\n������� [ALT]", -1, MINER_SH2_RAZDEVALKA, 5.0f);
		}
		//--------------------------------------------------------------
		if (Property[countProperty].owner)
		{
			strcpy(Property[countProperty].player, row[Jobs::Miner::minerRows::oName]);
			sprintf(query, "%s\n�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s", 
							query, 
							cProperty::getZoneName(Property[countProperty].region), 
							Property[countProperty].number, 
							Property[countProperty].player);
		}
		else
		{
			sprintf(query, "%s\n�����: {FF0000}%s {FFFFFF}�: {FF0000}%d\n{FFFFFF}���������: {FF0000}%d",
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
	logprintf("[������� ���������]:\t���� ���������� ����\t- %d", i);
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


void Jobs::Miner::cMiner::onGUI(const int u, const int draw)
{
	char minerAmount,
		minerColor;
	for (int i = 0; i < 20; i++)
	{
		if (draw == Player[ u ].minerDraw[ i ])
		{
			minerColor = 0 + rand() % 5;
			PlayerTextDrawHide(u, Player[ u ].minerDraw[ i ]);
			PlayerTextDrawColor(u, Player[ u ].minerDraw[ i ], ( minerColor ) ? ( 0xB700FF88 ) : ( 0xFF000088 ));
			PlayerTextDrawSetSelectable(u, Player[ u ].minerDraw[ i ], false);
			PlayerTextDrawShow(u, Player[ u ].minerDraw[ i ]);

			if (minerColor)
			{
				if (Player[ u ].inIndex == 1)
				{
					minerAmount = rand() % 10;
					Player[ u ].aMinerA += minerAmount;
					sprintf(query, "�� ������: {B700FF}%d {FFFFFF}����� ������, ����� {B700FF}%d{FFFFFF} �����", minerAmount, Player[ u ].aMinerA);
				}
				else if (Player[ u ].inIndex == 2)
				{
					minerAmount = rand() % 7;
					Player[ u ].aMinerB += minerAmount;
					sprintf(query, "�� ������: {B700FF}%d {FFFFFF}����� �������, ����� {B700FF}%d{FFFFFF} �����", minerAmount, Player[ u ].aMinerB);
				}
				else if (Player[ u ].inIndex == 3)
				{
					minerAmount = rand() % 8;
					Player[ u ].aMinerA += minerAmount;
					sprintf(query, "�� ������: {B700FF}%d {FFFFFF}����� ����, ����� {B700FF}%d{FFFFFF} �����", minerAmount, Player[ u ].aMinerA);
				}
				else if (Player[ u ].inIndex == 4)
				{
					minerAmount = rand() % 4;
					Player[ u ].aMinerB += minerAmount;
					sprintf(query, "�� ������: {B700FF}%d {FFFFFF}����� ������, ����� {B700FF}%d{FFFFFF} �����", minerAmount, Player[ u ].aMinerB);
				}
			}
			else
			{
				sprintf(query, "�� ������: {B700FF}������� �������� :)");
			}
			SendClientMessage(u, -1, query);
		}
	}
}

void Jobs::Miner::cMiner::startMinerGame(const int u)
{
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

void Jobs::Miner::cMiner::actionPicks(const int u)
{
	char action = 0;
	if (cPlayer::isRangeOfPoint(u, 1.0f, MINER_SH1_RAZDEVALKA))
	{
		action = 1;
		Player[u].inType = 1;
	}
	else if (cPlayer::isRangeOfPoint(u, 1.0f, MINER_SH2_RAZDEVALKA))
	{
		action = 1;
		Player[u].inType = 2;
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH1_IRON_RADIUS, MINER_SH1_IRON))
	{
		action = 2;
		Player[u].inIndex = 1;
		SendClientMessage(u, -1, "�� ������ ��������, {B700FF}������");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH1_SILVER_RADIUS, MINER_SH1_SILVER))
	{
		action = 2;
		Player[u].inIndex = 2;
		SendClientMessage(u, -1, "�� ������ ��������, {B700FF}�������");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_CUPRUM_RADIUS, MINER_SH2_CUPRUM))
	{
		action = 2;
		Player[u].inIndex = 3;
		SendClientMessage(u, -1, "�� ������ ��������, {B700FF}����");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_GOLD_RADIUS, MINER_SH2_GOLD))
	{
		action = 2;
		Player[u].inIndex = 4;
		SendClientMessage(u, -1, "�� ������ ��������, {B700FF}������");
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH1_CHECKPOS))
	{
		sprintf(query, "\t\t\t{FFFFFF}������ {B700FF}[{FFFFFF}����������{B700FF}]\n{FFFFFF}������: {B700FF}%d [{FFFFFF}%.2f${B700FF}]\n{FFFFFF}�������: {B700FF}%d [{FFFFFF}%.2f${B700FF}]", 
						Player[u].aMinerA, Jobs::Miner::cMiner::miner[0].zp1*Player[u].aMinerA, 
						Player[u].aMinerB, Jobs::Miner::cMiner::miner[0].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "�������-���������� �����", query, "OK", "");
		Player[u].aMinerA = 0;
		Player[u].aMinerB = 0;
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH2_CHECKPOS))
	{
		sprintf(query, "\t\t\t{FFFFFF}������ {B700FF}[{FFFFFF}����������{B700FF}]\n{FFFFFF}����: {B700FF}%d [{FFFFFF}%.2f${B700FF}]\n{FFFFFF}������: {B700FF}%d [{FFFFFF}%.2f${B700FF}]",
			Player[u].aMinerA, Jobs::Miner::cMiner::miner[1].zp1*Player[u].aMinerA,
			Player[u].aMinerB, Jobs::Miner::cMiner::miner[1].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "������-������ �����", query, "OK", "");
		Player[u].aMinerA = 0;
		Player[u].aMinerB = 0;
	}

	if (action == 1)
	{
		if (Jobs::Miner::cMiner::getMinerInstrument(u))
		{
			Jobs::Miner::cMiner::removeMinerInstrument(u);
		}
		else
		{
			Jobs::Miner::cMiner::giveMinerInstrument(u);
		}
	}
	else if (action == 2)
	{
		if (Jobs::Miner::cMiner::getMinerInstrument(u))
		{
			ApplyAnimation(u, "SWORD", "sword_4", 3.0f, true, false, false, false, 0, true);
			Jobs::Miner::cMiner::startMinerGame(u);
		}
		else
		{
			SendClientMessage(u, -1, "{FF0000}������: {FFFFFF}� ��� ��� �����������!");
		}
	}
}