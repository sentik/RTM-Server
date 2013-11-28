#include "main.h"

/* Немного доработал шахты:
1. Теперь можно потерять -- уронить руду
2. Сообщения шахты теперь локализованы
3. Исправил баг отрицательного значения руды ...
*/
struct sMiner   Jobs::Miner::cMiner::miner[MAX_SH];


/*
Заебал использовать query для сообщений!
Используй новые переменные. query -- глобальная переменная, 
и к ней доступ медленне, чем к локальной.
*/



void Jobs::Miner::cMiner::loadMiner()
{
	int i = 0;
	MYSQL_ROW row;

	world::Vehicles::locked(0, true);

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
			miner[i].infoTable = StreamerCall::Native::CreateDynamicObject(MINER_SH1_INFOTABLE);
		}
		else
		{
			sprintf(query, "Золото-медная шахта");
			StreamerCall::Native::CreateDynamicPickup(CLOTH_PICKUP, 23, MINER_SH2_RAZDEVALKA);
			StreamerCall::Native::CreateDynamic3DTextLabel("Раздевалка\nНажмите [ALT]", -1, MINER_SH2_RAZDEVALKA, 5.0f);
			miner[i].infoTable = StreamerCall::Native::CreateDynamicObject(MINER_SH2_INFOTABLE);
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
	Jobs::Miner::cMiner::updateInfotable(false);
	Jobs::Miner::cMiner::updateInfotable(true);
	logprintf("[Система имущества]:\tБыло загруженно шахт\t- %d", i);
}

/// <summary>
/// Дать инструменты шахтера
/// <param name="u">* Ид игрока</param>
/// </summary>
void Jobs::Miner::cMiner::giveMinerInstrument(const int u)
{
	SetPlayerAttachedObject(u, 8, 18634, 6, 0.065867f, 0.029999f, 0.0f, 80.586486f, 270.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1, -1);
	SetPlayerAttachedObject(u, 7, 18638, 2, 0.160290f, 0.024471f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1, -1);
}


/// <summary>
/// Убрать инструменты шахтера
/// <param name="u">* Ид игрока</param>
/// </summary>
void Jobs::Miner::cMiner::removeMinerInstrument(const int u)
{
	RemovePlayerAttachedObject(u, 8);
	RemovePlayerAttachedObject(u, 7);
}


/// <summary>
/// Проверка  наличия инструмента шахтера
/// <param name="u">* Ид игрока</param>
/// </summary>
bool Jobs::Miner::cMiner::getMinerInstrument(const int u)
{
	return (IsPlayerAttachedObjectSlotUsed(u, 8) && IsPlayerAttachedObjectSlotUsed(u, 7));
}


/// <summary>
/// Действия с GUI
/// <param name="u">* Ид игрока</param>
/// <param name="draw">* Ид текстдрава</param>
/// </summary>
void Jobs::Miner::cMiner::onGUI(const int u, const int draw)
{
	char msg[ 144 ];
	char minerAmount,	minerColor;
	for (int i = 0; i < 20; i++)
	{
		if (draw == Player[ u ].minerDraw[ i ])
		{
			minerColor = 0 + rand() % 5;
			PlayerTextDrawHide(u, Player[ u ].minerDraw[ i ]);
			PlayerTextDrawColor(u, Player[ u ].minerDraw[ i ], ( minerColor ) ? ( 0xB700FF88 ) : ( 0xFF000088 ));
			PlayerTextDrawSetSelectable(u, Player[ u ].minerDraw[ i ], false);
			PlayerTextDrawShow(u, Player[ u ].minerDraw[ i ]);
			//------------------------------------------------------------------------------------------------------
			if (Player[ u ].inIndex == 1)				// Железо
			{
				if (minerColor)
				{
					minerAmount = rand() % 10;
					Player[ u ].aMinerA += minerAmount;
					sprintf(msg, language::jobs::miner::actionOne, minerAmount, Player[ u ].aMinerA);
				}
				else
				{
					minerAmount = rand() % 5;
					Player[ u ].aMinerA -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionOne, minerAmount, Player[ u ].aMinerA);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 2)			//Серебро
			{
				if (minerColor)
				{
					minerAmount = rand() % 6;
					Player[ u ].aMinerB += minerAmount;
					sprintf(msg, language::jobs::miner::actionTwo, minerAmount, Player[ u ].aMinerB);
				}
				else
				{
					minerAmount = rand() % 2;
					Player[ u ].aMinerB -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionTwo, minerAmount, Player[ u ].aMinerA);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 3)			//Медь
			{
				if (minerColor)
				{
					minerAmount = rand() % 8;
					Player[ u ].aMinerA += minerAmount;
					sprintf(msg, language::jobs::miner::actionThree, minerAmount, Player[ u ].aMinerB);
				}
				else
				{
					minerAmount = rand() % 4;
					Player[ u ].aMinerA -= minerAmount;
					sprintf(msg, language::jobs::miner::actionThree, minerAmount, Player[ u ].aMinerA);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 4)			//Золото
			{
				if (minerColor)
				{
					minerAmount = rand() % 4;
					Player[ u ].aMinerB += minerAmount;
					sprintf(msg, language::jobs::miner::actionFour, minerAmount, Player[ u ].aMinerB);
				}
				else
				{
					minerAmount = rand() % 2;
					Player[ u ].aMinerB -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionFour, minerAmount, Player[ u ].aMinerA);
				}
			}
			//------------------------------------------------------------------------------------------------------
			if (Player[ u ].aMinerA < 0) Player[ u ].aMinerA = 0;
			if (Player[ u ].aMinerB < 0) Player[ u ].aMinerB = 0;
			//------------------------------------------------------------------------------------------------------
			SendClientMessage(u, -1, msg);
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
		SendClientMessage(u, -1, "Вы начали добывать, {B700FF}железо");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH1_SILVER_RADIUS, MINER_SH1_SILVER))
	{
		action = 2;
		Player[u].inIndex = 2;
		SendClientMessage(u, -1, "Вы начали добывать, {B700FF}серебро");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_CUPRUM_RADIUS, MINER_SH2_CUPRUM))
	{
		action = 2;
		Player[u].inIndex = 3;
		SendClientMessage(u, -1, "Вы начали добывать, {B700FF}медь");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_GOLD_RADIUS, MINER_SH2_GOLD))
	{
		action = 2;
		Player[u].inIndex = 4;
		SendClientMessage(u, -1, "Вы начали добывать, {B700FF}золото");
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH1_CHECKPOS))
	{
		sprintf(query, "\t\t\t\t\t{FFFFFF}Добыто {B700FF}[{FFFFFF}Заработано{B700FF}]\n\t{FFFFFF}Железо: {B700FF}%d [{FFFFFF}%.2f${B700FF}]\n\t{FFFFFF}Серебро: {B700FF}%d [{FFFFFF}%.2f${B700FF}]", 
						Player[u].aMinerA, Jobs::Miner::cMiner::miner[0].zp1*Player[u].aMinerA, 
						Player[u].aMinerB, Jobs::Miner::cMiner::miner[0].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "Железно-серебряная шахта", query, "OK", "");
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::miner[0].a1 += Player[u].aMinerA;
		Jobs::Miner::cMiner::miner[0].a2 += Player[u].aMinerB;
		Player[u].aMinerA = 0;
		Player[u].aMinerB = 0;
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::updateInfotable(false);
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH2_CHECKPOS))
	{
		sprintf(query, "\t\t\t\t\t{FFFFFF}Добыто {B700FF}[{FFFFFF}Заработано{B700FF}]\n\t{FFFFFF}Медь: {B700FF}%d [{FFFFFF}%.2f${B700FF}]\n\t{FFFFFF}Золото: {B700FF}%d [{FFFFFF}%.2f${B700FF}]",
			Player[u].aMinerA, Jobs::Miner::cMiner::miner[1].zp1*Player[u].aMinerA,
			Player[u].aMinerB, Jobs::Miner::cMiner::miner[1].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "Золото-медная шахта", query, "OK", "");
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::miner[1].a1 += Player[u].aMinerA;
		Jobs::Miner::cMiner::miner[1].a2 += Player[u].aMinerB;
		Player[u].aMinerA = 0;
		Player[u].aMinerB = 0;
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::updateInfotable(true);
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
			SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}у вас нет инструмента!");
		}
	}
}

void Jobs::Miner::cMiner::updateInfotable(bool i)
{
	struct StreamerCall::Native::ObjectText tmp;

	tmp.backColor = 0xFF000000;
	tmp.bold = true;
	tmp.fontColor = 0xFFFFFFFF;
	tmp.fontFace = "Arial";
	tmp.fontSize = 28;
	tmp.materialSize = 130;
	tmp.textAlignment = 1;

	char msg[200];
	if (!i)
	{
		sprintf(msg, language::jobs::miner::tableSH1, miner[i].zp1, miner[i].zp2, miner[i].a1, miner[i].a2);
	}
	else
	{
		sprintf(msg, language::jobs::miner::tableSH2, miner[i].zp1, miner[i].zp2, miner[i].a1, miner[i].a2);
	}

	tmp.materialText = msg;
	StreamerCall::Native::SetDynamicObjectMaterialText(miner[i].infoTable, 0, tmp);

	/*
	format(string, sizeof(string), "Информация\nСтоимость грамма железа: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма серебра: {B700FF}%.2f$\n{FFFFFF}Склад\nЖелеза грамм: {B700FF}%d\n{FFFFFF}Серебра грамм: {B700FF}%d",
		shInfo[0][shZP][0], shInfo[0][shZP][1], shInfo[0][shAmount][0], shInfo[0][shAmount][1]);
	SetDynamicObjectMaterialText(shInfo[0][shObject], 0, string, OBJECT_MATERIAL_SIZE_512x256, "Arial", 28, 1, 0xFFFFFFFF, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

	format(string, sizeof(string), "Информация\nСтоимость грамма Меди: {B700FF}%.2f$\n{FFFFFF}Стоимость грамма золота: {B700FF}%.2f$\n{FFFFFF}Склад\nМеди грамм: {B700FF}%d\n{FFFFFF}Золота грамм: {B700FF}%d",
		shInfo[1][shZP][0], shInfo[1][shZP][1], shInfo[1][shAmount][0], shInfo[1][shAmount][1]);
	SetDynamicObjectMaterialText(shInfo[1][shObject], 0, string, OBJECT_MATERIAL_SIZE_512x256, "Arial", 28, 1, 0xFFFFFFFF, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	*/
}