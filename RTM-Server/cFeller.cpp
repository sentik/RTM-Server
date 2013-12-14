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
			sprintf(query, "{FFFFFF}Лесопилка: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", fProperty::cFeller::Feller[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].player);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
				Property[countProperty].posX,
				Property[countProperty].posY,
				Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}Лесопилка: {FF0000}%s\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", fProperty::cFeller::Feller[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
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
	char msg[112], minerColor; 
	const char fell = Player[u].inType;
	const char slot = Player[u].aMinerB;

	if (Player[u].isAction == PlayerAction::ACTION_PREFELGAME)
	{
		for (int i = 1; i < 10; i++)
		{
			if (draw == Player[u].minerDraw[i])
			{

				for (int t = 0; t < 10; t++)
				{
					PlayerTextDrawDestroy(u, Player[u].minerDraw[t]);
				}

				minerColor = 1 + rand() % 10;

				if (minerColor == i)
				{
					SendClientMessage(u, -1, language::jobs::feller::preActionOne);
					StreamerCall::Native::MoveDynamicObject(fProperty::cFeller::Feller[fell].Trees[slot].obj, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y, fProperty::cFeller::Feller[fell].Trees[slot].z - 1.0f, 1.5f, -90.0f, 0.0f, 0.0f);
					fProperty::cFeller::Feller[fell].Trees[slot].proc = 1.0f;
				}
				else
				{
					SendClientMessage(u, -1, language::jobs::feller::preActionTwo);
				}

				CancelSelectTextDraw(u);
				Player[u].isAction = PlayerAction::ACTION_FELJOB;

				break;
			}
		}
	}
	else
	{
		char minerAmount;
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

					fProperty::cFeller::Feller[fell].Trees[slot].proc += minerAmount;
				}
				else if (minerColor == 5)
				{
					const float hpAmount = (1.0f + rand() % 300) / 100;
					GetPlayerHealth(u, &ftmp);
					SetPlayerHealth(u, ftmp - hpAmount);
					sprintf(msg, language::jobs::feller::actionFour, hpAmount);
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

void fProperty::cFeller::startPreFellerGame(const int u)
{
	float y;

	Player[u].minerDraw[0] = CreatePlayerTextDraw(u, 115.000000, 120.000000, "Tree");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[0], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[0], 0);
	PlayerTextDrawFont(u, Player[u].minerDraw[0], 5);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[0], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[0], -2004318072);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[0], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[0], 0);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[0], 1);
	PlayerTextDrawUseBox(u, Player[u].minerDraw[0], 1);
	PlayerTextDrawBoxColor(u, Player[u].minerDraw[0], 255);
	PlayerTextDrawTextSize(u, Player[u].minerDraw[0], 400.000000, 380.000000);
	PlayerTextDrawSetPreviewModel(u, Player[u].minerDraw[0], 659);
	PlayerTextDrawSetPreviewRot(u, Player[u].minerDraw[0], -16.000000, 0.000000, -55.000000, 1.200000);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[0], false);
	PlayerTextDrawShow(u, Player[u].minerDraw[0]);

	for (int i = 1; i < 10; i++)
	{
		y = 365.0f + (rand() % 7500) / 100;

		Player[u].minerDraw[i] = CreatePlayerTextDraw(u, 318.000000, y, "-");
		PlayerTextDrawAlignment(u, Player[u].minerDraw[i], 2);
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[i], 255);
		PlayerTextDrawFont(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawLetterSize(u, Player[u].minerDraw[i], 1.000000, 1.000000);
		PlayerTextDrawColor(u, Player[u].minerDraw[i], -1);
		PlayerTextDrawSetOutline(u, Player[u].minerDraw[i], 0);
		PlayerTextDrawSetProportional(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawSetShadow(u, Player[u].minerDraw[i], 0);
		PlayerTextDrawUseBox(u, Player[u].minerDraw[i], 1);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[i], 0);
		PlayerTextDrawTextSize(u, Player[u].minerDraw[i], 10.000000, 10.000000);
		PlayerTextDrawSetSelectable(u, Player[u].minerDraw[i], true);
		PlayerTextDrawShow(u, Player[u].minerDraw[i]);
	}
	Player[u].isAction = PlayerAction::ACTION_PREFELGAME;
	SelectTextDraw(u, 0xB7FF00FF);
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
				if (StreamerCall::Native::IsDynamicObjectMoving(fProperty::cFeller::Feller[fell].Trees[slot].obj)) continue;
				else if (cPlayer::isRangeOfPoint(u, 2.5f, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y + 10.0f, fProperty::cFeller::Feller[fell].Trees[slot].z) && fProperty::cFeller::Feller[fell].Trees[slot].proc >= 1.0f)
				{
					if (fProperty::cFeller::Feller[fell].Trees[slot].proc >= 500.0f)
					{
						fProperty::cFeller::Feller[fell].Trees[slot].proc = 0.0f;
						StreamerCall::Native::SetDynamicObjectPos(fProperty::cFeller::Feller[fell].Trees[slot].obj, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y, fProperty::cFeller::Feller[fell].Trees[slot].z - TREE_OFFSET);
						StreamerCall::Native::SetDynamicObjectRot(fProperty::cFeller::Feller[fell].Trees[slot].obj, 0.0f, 0.0f, 0.0f);
						StreamerCall::Native::MoveDynamicObject(fProperty::cFeller::Feller[fell].Trees[slot].obj, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y, fProperty::cFeller::Feller[fell].Trees[slot].z, TREE_SPEED);
					}
					else
					{
						ApplyAnimation(u, "CHAINSAW", "CSAW_G", 3.0, 1, 0, 0, 0, 0, 1);
						Player[u].inType = fell;
						Player[u].aMinerB = slot;
						fProperty::cFeller::startFellerGame(u);
					}
					break;
				}
				else if (cPlayer::isRangeOfPoint(u, 2.5f, fProperty::cFeller::Feller[fell].Trees[slot].x, fProperty::cFeller::Feller[fell].Trees[slot].y, fProperty::cFeller::Feller[fell].Trees[slot].z) && fProperty::cFeller::Feller[fell].Trees[slot].proc == 0.0f)
				{
					ApplyAnimation(u, "CHAINSAW", "CSAW_PART", 3.0, 1, 1, 1, 1, 1, 1);
					Player[u].inType = fell;
					Player[u].aMinerB = slot;
					fProperty::cFeller::startPreFellerGame(u);
					break;
				}
			}
			break;
		}
	}
}

void fProperty::cFeller::updateText(const int p, const int u = -1)
{
	char msg[256];
	if(u != -1) sprintf(Property[p].player, "%s %s", Player[u].uName, Player[u].sName);
	sprintf(msg, "{FFFFFF}Лесопилка: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s", fProperty::cFeller::Feller[Property[p].link].name, cProperty::getZoneName(Property[p].region), Property[p].number, Property[p].player);
	//------------------------------------------------------------------
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Property[p].text, -1, msg);
}

void fProperty::cFeller::onDLG(int u, int dialogid, int response, int listitem, const char* inputtext)
{
	char msg[256];
	const int p = Player[u].inIndex;
	const int l = Property[p].link;

	switch (dialogid)
	{
		case DIALOG_LIST::DLG_FELLEROWNER_MAIN:
		{
			if (response)
			{
				if (listitem == 0)
				{
					sprintf(msg, "Название: %s\nЗарплата: %.2f$\nКол-во древесины: %d\nНаличка: %.2f$\nНомер счёта: %d",
									Feller[l].name, Feller[l].zp, Feller[l].am, Feller[l].fond, Property[p].bank);
					ShowPlayerDialog(u, DLG_FELLEROWNER_EMTY, GUI_MSG, Feller[l].name, msg, language::dialogs::buttons::btnBack, "");
				}
				else if (listitem == 1)
				{
	case_setname:
					sprintf(msg, "Введите название лесопилки.\nТекущие название: %s", Feller[l].name);
					ShowPlayerDialog(u, DLG_FELLEROWNER_SETNAME, GUI_INPUT, Feller[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)
				{
	case_money:
					dialogs::genDLGItem(1, "Зарплата", msg);
					dialogs::genDLGItem(2, "Наличка", msg);
					dialogs::genDLGItem(3, "Номер счёта", msg);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS, GUI_LIST, Feller[l].name, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_EMTY:
		{
			fProperty::cFeller::ownerMenu(u);
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_SETNAME:
		{
			if (response)
			{
				if (regex_match(inputtext, expString))
				{
					strcpy(Feller[l].name, inputtext);
					fProperty::cFeller::updateText(p);
					sprintf(msg, "Название установлено: %s", Feller[l].name);
					ShowPlayerDialog(u, DLG_FELLEROWNER_EMTY, GUI_MSG, Feller[l].name, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_setname;
				}
			}
			else
			{
				fProperty::cFeller::ownerMenu(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_COSTS_EMTY:
		{
goto case_money;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_COSTS:
		{
			if (response)
			{
				if (listitem == 0)
				{
	case_setzp:
					sprintf(msg, "Введите цену за единицу древесины.\nТекущая цена: %.2$", Feller[l].zp);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_ZP, GUI_INPUT, Feller[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 1)
				{
	case_paydep:
					dialogs::genDLGItem(1, "Снять", msg);
					dialogs::genDLGItem(2, "Положить", msg);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_MN, GUI_LIST, Feller[l].name, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)
				{
	case_setbank:
					sprintf(msg, "Введите номер банского счёта.\nТекущей счёт: %d", Property[p].bank);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_BN, GUI_INPUT, Feller[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				fProperty::cFeller::ownerMenu(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_COSTS_ZP:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					Feller[l].zp = atof(inputtext);
					sprintf(msg, "Зарплата установлена: %.2f$", Feller[l].zp);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_EMTY, GUI_MSG, Feller[l].name, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_setzp;
				}
			}
			else
			{
goto case_money;
			}
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_COSTS_BN:
		{
			if (response)
			{
				if (regex_match(inputtext, expCode))
				{
					Property[p].bank = atoi(inputtext);
					sprintf(msg, "Номер счёта установлен: %d", Property[p].bank);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_EMTY, GUI_MSG, Feller[l].name, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_setbank;
				}
			}
			else
			{
goto case_money;
			}
			break;
		}
		case DIALOG_LIST::DLG_FELLEROWNER_COSTS_MN:
		{
			if (response)
			{
				if (listitem == 0)
				{
	case_opay:
					sprintf(msg, "Введите сумму которую хотите снять.\nТекущей баланс: %.2f$", Feller[l].fond);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_MN_PAY, GUI_INPUT, Feller[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else
				{
	case_odep:
					sprintf(msg, "Введите сумму которую хотите положить.\nУ вас в кошельке: %.2f$", Player[u].pMoney);
					ShowPlayerDialog(u, DLG_FELLEROWNER_COSTS_MN_DEP, GUI_INPUT, Feller[l].name, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
goto case_money;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_MONEY_PAY:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					const float value = atof(inputtext);
					if (value <= Feller[l].fond && value > 0)
					{
						Feller[l].fond -= value;
						cPlayer::givePlayerMoney(u, value);
goto case_paydep;
					}
					else
					{
goto case_opay;
					}
				}
				else
				{
goto case_opay;
				}
			}
			else
			{
goto case_paydep;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_MONEY_DEP:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					const float value = atof(inputtext);
					if (value <= Player[u].pMoney && value > 0)
					{
						Feller[l].fond += value;
						cPlayer::givePlayerMoney(u, -value);
goto case_paydep;
					}
					else
					{
goto case_odep;
					}
				}
				else
				{
goto case_odep;
				}
			}
			else
			{
goto case_paydep;
			}
			break;
		}
	}
}

void fProperty::cFeller::ownerMenu(const int u)
{
	Player[u].isAction = PlayerAction::ACTION_USEFELLERDLG;
	char msg[300] = "";
	dialogs::genDLGItem(1, "Информация", msg);
	dialogs::genDLGItem(2, "Название", msg);
	dialogs::genDLGItem(3, "Финансы", msg);
	ShowPlayerDialog(u, DLG_FELLEROWNER_MAIN, GUI_LIST, Feller[Property[Player[u].inIndex].link].name, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnClose);
}

void fProperty::cFeller::clientMenu(const int u)
{

}