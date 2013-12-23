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
	safe_query(con, "SELECT class_Property.*, class_Miners.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Miners  WHERE class_Property.property = class_Miners.id AND class_Property.type = 4");
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
		miner[i].fond						= atof(row[Jobs::Miner::minerRows::fond]);
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
			//------------------------------------------------------------------------------------------------------
			if (minerColor == 0)
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xFF000088);
			else if (minerColor == 1)
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xB700FF88);
			else
				PlayerTextDrawColor(u, Player[u].minerDraw[i], 0xFFAF0088);
			//------------------------------------------------------------------------------------------------------
			PlayerTextDrawSetSelectable(u, Player[ u ].minerDraw[ i ], false);
			PlayerTextDrawShow(u, Player[ u ].minerDraw[ i ]);
			//------------------------------------------------------------------------------------------------------
			if (Player[ u ].inIndex == 1)				// Железо
			{
				if (minerColor == 1)
				{
					minerAmount = 1 + rand() % 9;
					Player[ u ].aMinerA += minerAmount;
					sprintf(msg, language::jobs::miner::actionOne, minerAmount, Player[ u ].aMinerA);
				}
				else if (minerColor == 0)
				{
					minerAmount =  1 + rand() % 5;
					Player[ u ].aMinerA -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionOne, minerAmount, Player[ u ].aMinerA);
				}
				else
				{
					sprintf(msg, language::jobs::miner::otherAction);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 2)			//Серебро
			{
				if (minerColor == 1)
				{
					minerAmount = 1 + rand() % 6;
					Player[ u ].aMinerB += minerAmount;
					sprintf(msg, language::jobs::miner::actionTwo, minerAmount, Player[ u ].aMinerB);
				}
				else if (minerColor == 0)
				{
					minerAmount = 1 + rand() % 2;
					Player[ u ].aMinerB -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionTwo, minerAmount, Player[u].aMinerB);
				}
				else
				{
					sprintf(msg, language::jobs::miner::otherAction);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 3)			//Медь
			{
				if (minerColor == 1)
				{
					minerAmount = 1 + rand() % 8;
					Player[ u ].aMinerA += minerAmount;
					sprintf(msg, language::jobs::miner::actionThree, minerAmount, Player[u].aMinerA);
				}
				else if (minerColor == 0)
				{
					minerAmount = 1 + rand() % 4;
					Player[ u ].aMinerA -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionThree, minerAmount, Player[u].aMinerA);
				}
				else
				{
					sprintf(msg, language::jobs::miner::otherAction);
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if (Player[ u ].inIndex == 4)			//Золото
			{
				if (minerColor == 1)
				{
					minerAmount = 1 + rand() % 4;
					Player[ u ].aMinerB += minerAmount;
					sprintf(msg, language::jobs::miner::actionFour, minerAmount, Player[ u ].aMinerB);
				}
				else if (minerColor == 0)
				{
					minerAmount = 1 + rand() % 2;
					Player[ u ].aMinerB -= minerAmount;
					sprintf(msg, language::jobs::miner::disActionFour, minerAmount, Player[u].aMinerB);
				}
				else
				{
					sprintf(msg, language::jobs::miner::otherAction);
				}
			}
			//------------------------------------------------------------------------------------------------------
			if (Player[ u ].aMinerA < 0) Player[ u ].aMinerA = 0;
			if (Player[ u ].aMinerB < 0) Player[ u ].aMinerB = 0;
			//------------------------------------------------------------------------------------------------------
			SendClientMessage(u, -1, msg);
			break;
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
		SendClientMessage(u, -1, "Вы начали добывать, {"MINER_MENU_COLOR"}железо");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH1_SILVER_RADIUS, MINER_SH1_SILVER))
	{
		action = 2;
		Player[u].inIndex = 2;
		SendClientMessage(u, -1, "Вы начали добывать, {"MINER_MENU_COLOR"}серебро");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_CUPRUM_RADIUS, MINER_SH2_CUPRUM))
	{
		action = 2;
		Player[u].inIndex = 3;
		SendClientMessage(u, -1, "Вы начали добывать, {"MINER_MENU_COLOR"}медь");
	}
	else if (cPlayer::isRangeOfPoint(u, MINER_SH2_GOLD_RADIUS, MINER_SH2_GOLD))
	{
		action = 2;
		Player[u].inIndex = 4;
		SendClientMessage(u, -1, "Вы начали добывать, {"MINER_MENU_COLOR"}золото");
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH1_CHECKPOS))
	{
		sprintf(query, "\t\t\t\t\t{FFFFFF}Добыто {"MINER_MENU_COLOR"}[{FFFFFF}Заработано{"MINER_MENU_COLOR"}]\n\t{FFFFFF}Железо: {"MINER_MENU_COLOR"}%d [{FFFFFF}%.2f${"MINER_MENU_COLOR"}]\n\t{FFFFFF}Серебро: {"MINER_MENU_COLOR"}%d [{FFFFFF}%.2f${"MINER_MENU_COLOR"}]",
						Player[u].aMinerA, Jobs::Miner::cMiner::miner[0].zp1*Player[u].aMinerA, 
						Player[u].aMinerB, Jobs::Miner::cMiner::miner[0].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "Железно-серебряная шахта", query, "OK", "");
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::miner[0].a1 += Player[u].aMinerA;
		Jobs::Miner::cMiner::miner[0].a2 += Player[u].aMinerB;
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::updateInfotable(false);
		//----------------------------------------------------------------------------------------------------------------------
		Player[u].minerZP += ( Jobs::Miner::cMiner::miner[0].zp1*Player[u].aMinerA + Jobs::Miner::cMiner::miner[0].zp2*Player[u].aMinerB );
		Player[u].aMinerA = 0;
		Player[u].aMinerB = 0;
	}
	else if (cPlayer::isRangeOfPoint(u, 2.5f, MINER_SH2_CHECKPOS))
	{
		sprintf(query, "\t\t\t\t\t{FFFFFF}Добыто {"MINER_MENU_COLOR"}[{FFFFFF}Заработано{"MINER_MENU_COLOR"}]\n\t{FFFFFF}Медь: {"MINER_MENU_COLOR"}%d [{FFFFFF}%.2f${"MINER_MENU_COLOR"}]\n\t{FFFFFF}Золото: {"MINER_MENU_COLOR"}%d [{FFFFFF}%.2f${"MINER_MENU_COLOR"}]",
			Player[u].aMinerA, Jobs::Miner::cMiner::miner[1].zp1*Player[u].aMinerA,
			Player[u].aMinerB, Jobs::Miner::cMiner::miner[1].zp2*Player[u].aMinerB);
		ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "Золото-медная шахта", query, "OK", "");
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::miner[1].a1 += Player[u].aMinerA;
		Jobs::Miner::cMiner::miner[1].a2 += Player[u].aMinerB;
		//----------------------------------------------------------------------------------------------------------------------
		Jobs::Miner::cMiner::updateInfotable(true);
		//----------------------------------------------------------------------------------------------------------------------
		Player[u].minerZP += ( Jobs::Miner::cMiner::miner[1].zp1*Player[u].aMinerA + Jobs::Miner::cMiner::miner[1].zp2*Player[u].aMinerB );
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
}

void Jobs::Miner::cMiner::updateText(const int p, const int u)
{
	char msg[256];
	sprintf(Property[p].player, "%s %s", Player[u].uName, Player[u].sName);
	if (!Property[p].link)
	{
		sprintf(msg, "Железо-серебряная шахта");
	}
	else
	{
		sprintf(msg, "Золото-медная шахта");
	}
	sprintf(msg, "%s\nАдрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
		msg,
		cProperty::getZoneName(Property[p].region),
		Property[p].number,
		Property[p].player);
	//------------------------------------------------------------------
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Property[p].text, -1, msg);
}

void Jobs::Miner::cMiner::showDLG(const int u)
{
	char msg[ 256 ] = "";
	Player[ u ].isAction = PlayerAction::ACTION_USEMINERDLG;
	if (Player[ u ].pDB == Property[ Player[ u ].inIndex ].owner)
	{
		dialogs::genDLGItem(1, "Информация", msg, MINER_MENU_COLOR);
		dialogs::genDLGItem(2, "Финансы", msg, MINER_MENU_COLOR);
		dialogs::genDLGItem(3, "Клиент-меню {FF0000}(для разрабов)", msg, MINER_MENU_COLOR);
		//----------------------------------------
		ShowPlayerDialog
			(
				u, 
				DLG_MINER_OWNER_MAIN, GUI_LIST, 
				"Меню владельца шахты",			msg,
				language::dialogs::buttons::btnSelect,
				language::dialogs::buttons::btnClose
			);
		//----------------------------------------
	}
	else
	{
		dialogs::genDLGItem(1, "Информация", msg, MINER_MENU_COLOR);
		dialogs::genDLGItem(2, "Зарплата", msg, MINER_MENU_COLOR);
		dialogs::genDLGItem(3, "Инвертарь {FF0000}(Не работает)", msg, MINER_MENU_COLOR);
		dialogs::genDLGItem(4, "Закупка руды {FF0000}(Не работает)", msg, MINER_MENU_COLOR);
		//----------------------------------------
		ShowPlayerDialog
			(
			u,
			DLG_MINER_CLIENT_MAIN, GUI_LIST,
			"Меню клиента шахты",			msg,
			language::dialogs::buttons::btnSelect,
			language::dialogs::buttons::btnClose
			);
		//----------------------------------------
	}
}

void Jobs::Miner::cMiner::onDLG(const int u, const int dialogid, const int response, const int listitem, const char * inputtext)
{
	char msg[256] = "";
	const int p = Player[u].inIndex;
	const int l = Property[p].link;

	switch (dialogid)
	{
		//------------------------------------------------------------------------------------------] Client
		case DLG_MINER_CLIENT_MAIN:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
					sprintf
					(	
						msg,
						"Зарплата за %s: \t\t %f$\nЗарплата за %s: \t\t%f$",
						language::jobs::miner::listMetall[l], miner[l].zp1,
						language::jobs::miner::listMetall[l+2], miner[l].zp1
					);
					ShowPlayerDialog
					(
						u,
						DLG_MINER_CLIENT_INFO,
						GUI_MSG,
						"Информация о шахте",
						msg,
						language::dialogs::buttons::btnBack,
						""
					);
				}
				else if ( listitem == 1 )
				{
					dialogs::genDLGItem(1, "Обналичить", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(2, "Банковский перевод", msg, MINER_MENU_COLOR);
					ShowPlayerDialog(u, DLG_MINER_CLIENT_MONEY, GUI_LIST, "Зарплата", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else
				{
					Jobs::Miner::cMiner::showDLG(u);
				}
			}
			else
			{
				Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DLG_MINER_CLIENT_MONEY:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
					const float money = Player[u].minerZP;
					const int exp = floor(money / 100);

					sprintf(msg, "{FFFFFF}Заработано: {"MINER_MENU_COLOR"}%.2f$ {FFFFFF}+ ({"MINER_MENU_COLOR"}%d EXP{FFFFFF})", money, exp);

					if ( Jobs::Miner::cMiner::miner[l].fond > money )
					{
						cPlayer::giveExp(u, exp);
						Jobs::Miner::cMiner::miner[l].fond -= money;
						cPlayer::givePlayerMoney(u, money);
						Player[u].minerZP = 0;
					}
					else
					{
						SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}шахта не может оплатить ваш труд.");
					}

					ShowPlayerDialog(u, DLG_MINER_CLIENT_INFO, GUI_MSG, "Зарплата", msg, language::dialogs::buttons::btnOK, "");
				}
				else if ( listitem == 1 )
				{
	case_bank:
					ShowPlayerDialog(u, DLG_MINER_CLIENT_MONEY_BANK, GUI_INPUT, "Зарплата", "{FFFFFF}Введите номер банкского счёта", language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Jobs::Miner::cMiner::showDLG(u);
			}
			break;
		}
		case DLG_MINER_CLIENT_MONEY_BANK:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expCode) )
				{
					const int num = atoi(inputtext);
					if ( cBanks::isValidNumber(num) )
					{
						const float money = Player[u].minerZP;
						const int exp = floor(money / 100);
						double value;
						cBanks::getBalance(Property[p].bank, &value);

						sprintf(msg, "{FFFFFF}Заработано: {"MINER_MENU_COLOR"}%.2f$ {FFFFFF}+ ({"MINER_MENU_COLOR"}%d EXP{FFFFFF})", money, exp);

						if ( value > money )
						{
							cPlayer::giveExp(u, exp);
							cBanks::giveBalance(Property[p].bank, -money);
							cBanks::giveBalance(num, money);
							Player[u].minerZP = 0;
						}
						else
						{
							SendClientMessage(u, -1, "{FF0000}Ошибка: {FFFFFF}шахта не может оплатить ваш труд.");
						}

						ShowPlayerDialog(u, DLG_MINER_CLIENT_INFO, GUI_MSG, "Зарплата", msg, language::dialogs::buttons::btnOK, "");
					}
					else
					{
goto case_bank;
					}
				}
				else
				{
goto case_bank;
				}
			}
			else
			{
				Jobs::Miner::cMiner::showDLG(u);
			}
			break;
		}
		case DLG_MINER_OWNER_INFO:
		case DLG_MINER_CLIENT_INFO:
		{
			Jobs::Miner::cMiner::showDLG(u);
			break;
		}
		//------------------------------------------------------------------------------------------] Owner
		case DLG_MINER_OWNER_MAIN:
		{
			if (response)
			{
				if (listitem == 0)		//Информация
				{
					sprintf(msg, 
							"Зарплата за %s: \t\t %.2f$\nЗарплата за %s: \t\t%.2f$",
							language::jobs::miner::listMetall[l], miner[l].zp1,
							language::jobs::miner::listMetall[l+2], miner[l].zp2
					);
					ShowPlayerDialog
					(
						u, 
						DLG_MINER_OWNER_INFO, 
						GUI_MSG, 
						"Информация о шахте", 
						msg,
						language::dialogs::buttons::btnBack,
						""
					);
				}
				else if (listitem == 1)	//Финансы
				{
	case_finans:
					strcpy(msg, "");
					dialogs::genDLGItem(1, "Наличные", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(2, "Номер счёта", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(3, "Зарплата", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(4, "Процент продажи", msg, MINER_MENU_COLOR);
					ShowPlayerDialog(u, DLG_MINER_OWNER_FINANS, GUI_LIST, "sdsad", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if ( listitem == 2 )
				{
					dialogs::genDLGItem(1, "Информация", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(2, "Зарплата", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(3, "Инвертарь (Не работает)", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(4, "Закупка руды (Не работает)", msg, MINER_MENU_COLOR);
					//----------------------------------------
					ShowPlayerDialog
					(
						u,
						DLG_MINER_CLIENT_MAIN, GUI_LIST,
						"Меню клиента шахты", msg,
						language::dialogs::buttons::btnSelect,
						language::dialogs::buttons::btnClose
					);
					//----------------------------------------
				}
			}
			else
			{
				Player[ u ].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DLG_MINER_OWNER_FINANS:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
	case_omoney:
					strcpy(msg, "");
					dialogs::genDLGItem(1, "Снять", msg, MINER_MENU_COLOR);
					dialogs::genDLGItem(2, "Положить", msg, MINER_MENU_COLOR);
					ShowPlayerDialog(u, DLG_MINER_OWNER_MONEY, GUI_LIST, "Наличные", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if ( listitem == 1 )
				{
	case_oBN:
					sprintf(msg, "{FFFFFF}Введите номер банкского счёта который будет привязан к шахте.\nТекущей счёт: {"MINER_MENU_COLOR"}%d", Property[p].bank);
					ShowPlayerDialog(u, DLG_MINER_OWNER_BN, GUI_INPUT, "Банковский счёт", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if ( listitem == 2 )
				{
	case_oZP:
					sprintf(msg, "{FFFFFF}[{"MINER_MENU_COLOR"}%.2f${FFFFFF}]\t{"MINER_MENU_COLOR"}%s\n{FFFFFF}[{"MINER_MENU_COLOR"}%.2f${FFFFFF}]\t{"MINER_MENU_COLOR"}%s", 
							miner[l].zp1, language::jobs::miner::listMetall[l],
							miner[l].zp2, language::jobs::miner::listMetall[l+2]);
					ShowPlayerDialog(u, DLG_MINER_OWNER_ZP, GUI_LIST, "Зарплата", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if ( listitem == 3 )
				{
	case_oProcent:
					sprintf(msg, "{FFFFFF}Введите процент продажи.\nТекущей процент: {"MINER_MENU_COLOR"}%.1f%%", miner[l].procent);
					ShowPlayerDialog(u, DLG_MINER_OWNER_SELLP, GUI_INPUT, "Процент продажи", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Jobs::Miner::cMiner::showDLG(u);
			}
			break;
		}
		case DLG_MINER_OWNER_MONEY:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
	case_oPay:
					sprintf(msg, "{FFFFFF}Введите сумму которую хотите снять.\nБаланс шахты: {"MINER_MENU_COLOR"}%.2f$", miner[l].fond);
					ShowPlayerDialog(u, DLG_MINER_OWNER_MONEY_PAY, GUI_INPUT, "Снять", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else
				{
	case_oDep:
					sprintf(msg, "{FFFFFF}Введите сумму которую хотите положить.\nУ вас в кошельке: {"MINER_MENU_COLOR"}%.2f$", Player[u].pMoney);
					ShowPlayerDialog(u, DLG_MINER_OWNER_MONEY_DEP, GUI_INPUT, "Снять", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
goto case_finans;
			}
			break;
		}
		case DLG_MINER_OWNER_MONEY_PAY:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expFloat) )
				{
					const float money = atof(inputtext);
					if ( money > 0 && miner[l].fond > money )
					{
						miner[l].fond -= money;
						cPlayer::givePlayerMoney(u, money);
goto case_finans;
					}
					else
					{
goto case_oPay;
					}
				}
				else
				{
goto case_oPay;
				}
			}
			else
			{
goto case_omoney;
			}
			break;
		}
		case DLG_MINER_OWNER_MONEY_DEP:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expFloat) )
				{
					const float money = atof(inputtext);
					if ( money > 0 && Player[u].pMoney > money )
					{
						miner[l].fond += money;
						cPlayer::givePlayerMoney(u, -money);
						goto case_finans;
					}
					else
					{
goto case_oDep;
					}
				}
				else
				{
goto case_oDep;
				}
			}
			else
			{
goto case_omoney;
			}
			break;
		}
		case DLG_MINER_OWNER_BN:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expCode) )
				{
					const int num = atoi(inputtext);
					if ( cBanks::isValidNumber(num) )
					{
						Property[p].bank = num;
						goto case_finans;
					}
					else
					{
goto case_oBN;
					}
				}
				else
				{
goto case_oBN;
				}
			}
			else
			{
goto case_finans;
			}
			break;
		}
		case DLG_MINER_OWNER_ZP:
		{
			if ( response )
			{
				if ( listitem == 0 )
				{
	case_metalOne:
					sprintf(msg, "{FFFFFF}Введите стоимость оплаты труда за {"MINER_MENU_COLOR"}1 {FFFFFF}грамм {"MINER_MENU_COLOR"}%s.\n{FFFFFF}Текущая стоимость: {"MINER_MENU_COLOR"}%.2f$", language::jobs::miner::listMetall[l], Jobs::Miner::cMiner::miner[l].zp1);
					ShowPlayerDialog(u, DLG_MINER_OWNER_ZP_M1, GUI_INPUT, "Зарплата", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else
				{
	case_metalTwo:
					sprintf(msg, "{FFFFFF}Введите стоимость оплаты труда за {"MINER_MENU_COLOR"}1 {FFFFFF}грамм {"MINER_MENU_COLOR"}%s.\n{FFFFFF}Текущая стоимость: {"MINER_MENU_COLOR"}%.2f$", language::jobs::miner::listMetall[l+2], Jobs::Miner::cMiner::miner[l].zp2);
					ShowPlayerDialog(u, DLG_MINER_OWNER_ZP_M2, GUI_INPUT, "Зарплата", msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
goto case_finans;
			}
			break;
		}
		case DLG_MINER_OWNER_ZP_M1:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expFloat) )
				{
					const float cost = atof(inputtext);
					if ( cost > 0.00f && cost < 10.0f )
					{
						Jobs::Miner::cMiner::miner[l].zp1 = cost;
						Jobs::Miner::cMiner::updateInfotable(( l ? ( true ) : ( false ) ));
goto case_finans;
					}
					else
					{
goto case_metalOne;
					}
				}
				else
				{
goto case_metalOne;
				}
			}
			else
			{
goto case_oZP;
			}
			break;
		}
		case DLG_MINER_OWNER_ZP_M2:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expFloat) )
				{
					const float cost = atof(inputtext);
					if ( cost > 0.00f && cost < 10.0f )
					{
						Jobs::Miner::cMiner::miner[l].zp2 = cost;
						Jobs::Miner::cMiner::updateInfotable(( l ? ( true ) : ( false ) ));
goto case_finans;
					}
					else
					{
goto case_metalTwo;
					}
				}
				else
				{
goto case_metalTwo;
				}
			}
			else
			{
goto case_oZP;
			}
			break;
		}
		case DLG_MINER_OWNER_SELLP:
		{
			if ( response )
			{
				if ( regex_match(inputtext, expFloat) )
				{
					const float procent = atof(inputtext);
					if ( procent > 0.00f && procent < 100.0f )
					{
						Jobs::Miner::cMiner::miner[l].procent = procent;
goto case_finans;
					}
					else
					{
goto case_oProcent;
					}
				}
				else
				{
goto case_oProcent;
				}
			}
			else
			{
goto case_finans;
			}
			break;
		}
	}
}