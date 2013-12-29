#include "main.h"
struct eBanks Bank[ MAX_BANKS ];
struct eATM bankATM[ MAX_BANKS ][ 256 ];
int countBanks;
int countATM;


void cBanks::loadBanks()
{
	MYSQL_ROW row;
	//------------------------------------------------------------
	safe_query(con, "SELECT class_Property.*, class_Banks.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Banks  WHERE class_Property.property = class_Banks.db AND class_Property.type = 2");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		Property[ countProperty ].db = atoi(row[ Properties::Bank::BankRows::id ]);
		Property[ countProperty ].bank = atoi(row[ Properties::Bank::BankRows::bank ]);
		Property[ countProperty ].owner = atoi(row[ Properties::Bank::BankRows::owner ]);
		Property[ countProperty ].price = atoi(row[ Properties::Bank::BankRows::price ]);
		Property[ countProperty ].type = atoi(row[ Properties::Bank::BankRows::type ]);
		Property[ countProperty ].posX = atof(row[ Properties::Bank::BankRows::posx ]);
		Property[ countProperty ].posY = atof(row[ Properties::Bank::BankRows::posy ]);
		Property[ countProperty ].posZ = atof(row[ Properties::Bank::BankRows::posz ]);
		Property[ countProperty ].property = atoi(row[ Properties::Bank::BankRows::property ]);
		Property[ countProperty ].style = atoi(row[ Properties::Bank::BankRows::style ]);
		//--------------------------------------------------------------
		strcpy(Bank[ countBanks ].title, row[ Properties::Bank::BankRows::title ]);
		//--------------------------------------------------------------
		if (Property[ countProperty ].owner)
		{
			strcpy(Property[ countProperty ].player, row[ Properties::Bank::BankRows::oName ]);
		}
		Bank[ countBanks ].db = atoi(row[ Properties::Bank::BankRows::db ]);
		Bank[ countBanks ].start = atoi(row[ Properties::Bank::BankRows::start ]);
		Bank[ countBanks ].end = atoi(row[ Properties::Bank::BankRows::end ]);
		Bank[ countBanks ].credit = atof(row[ Properties::Bank::BankRows::credit ]);
		Bank[ countBanks ].deposit = atof(row[ Properties::Bank::BankRows::deposit ]);
		Bank[ countBanks ].pay = atof(row[ Properties::Bank::BankRows::pay ]);
		Bank[ countBanks ].send = atof(row[ Properties::Bank::BankRows::send ]);
		Bank[ countBanks ].fond = atof(row[ Properties::Bank::BankRows::fond ]);
		cBanks::makePick();
		countProperty++;
		countBanks++;
	}
	//-----------------
	cBanks::loadATM();
	//-----------------
	logprintf("[Система Имущества]: \tБыло загруженно банклв \t- %d", countBanks);
}

void cBanks::loadATM()
{
	int atm = 0;
	int bank = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	safe_query(con, "SELECT bank_ATM.*,class_Banks.name FROM bank_ATM,class_Banks WHERE bank_ATM.owner = class_Banks.db ORDER BY owner");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		char name[ 32 ];
		if (bank == atoi(row[ 1 ]) && atm <  96) atm++;
		else
		{
			bank = atoi(row[ 1 ]);
			atm = 0;
		}

		bankATM[ bank ][ atm ].db =  atoi(row[ Properties::Bank::atm::id ]);
		bankATM[ bank ][ atm ].owner = atoi(row[ Properties::Bank::atm::owner ]);
		bankATM[ bank ][ atm ].balance = atof(row[ Properties::Bank::atm::balance ]);
		bankATM[ bank ][ atm ].percent = atof(row[ Properties::Bank::atm::percent ]);
		//-----------------------------------------------------------------------
		bankATM[ bank ][ atm ].posX = atof(row[ Properties::Bank::atm::posx ]);
		bankATM[ bank ][ atm ].posY = atof(row[ Properties::Bank::atm::posy ]);
		bankATM[ bank ][ atm ].posZ = atof(row[ Properties::Bank::atm::posz ]);
		//-----------------------------------------------------------------------
		bankATM[ bank ][ atm ].rotX = atof(row[ Properties::Bank::atm::rotx ]);
		bankATM[ bank ][ atm ].rotY = atof(row[ Properties::Bank::atm::roty ]);
		bankATM[ bank ][ atm ].rotZ = atof(row[ Properties::Bank::atm::rotz ]);
		//-----------------------------------------------------------------------
		bankATM[ bank ][ atm ].obj = StreamerCall::Native::CreateDynamicObject(BANKOMAT_MODEL, 
																			   bankATM[ bank ][ atm ].posX,
																			   bankATM[ bank ][ atm ].posY,
																			   bankATM[ bank ][ atm ].posZ,
																			   bankATM[ bank ][ atm ].rotX,
																			   bankATM[ bank ][ atm ].rotY,
																			   bankATM[ bank ][ atm ].rotZ);
		//-----------------------------------------------------------------------
		strcpy(name, row[ Properties::Bank::atm::name ]);
		sprintf(query, "{B7FF00}[Банкомат]\n{FFFFFF}Банк: {B7FF00}%s\n{FFFFFF}Комиссия: {B7FF00}%.1f\n{FFFFFF}Использовать [ALT]", name, bankATM[ bank ][ atm ].percent);
		bankATM[ bank ][ atm ].info = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
																					 bankATM[ bank ][ atm ].posX,
																					 bankATM[ bank ][ atm ].posY,
																					 bankATM[ bank ][ atm ].posZ, 20.0f);
		//-----------------------------------------------------------------------
	/*	float pX = bankATM[ bank ][ atm ].posX - 1 * sin(bankATM[ bank ][ atm ].rotZ);
		float pY = bankATM[ bank ][ atm ].posY + 1 * cos(bankATM[ bank ][ atm ].rotZ);

	//	logprintf("x:%f || y:%f|| %d|%s", pX, pY, bank, atm);

		bankATM[ bank ][ atm ].pick = StreamerCall::Native::CreateDynamicPickup(1212, 23, pX, pY, bankATM[ bank ][ atm ].posZ, 0, 0);*/
	}
}

void cBanks::makePick()
{
	//--------------------------------------------------------------
	if (Property[ countProperty ].owner)
	{
		sprintf(query, "{FFFFFF}Банк: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
				Bank[ countBanks ].title,
				cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number,
				Property[ countProperty ].player);
		//=====================================================================================================
		Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																				   Property[ countProperty ].posX,
																				   Property[ countProperty ].posY,
																				   Property[ countProperty ].posZ, 0, 0);
		//=====================================================================================================
	}
	else
	{
		sprintf(query, "{FFFFFF}Банк: {FF0000}%s\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", 
		Bank[ countBanks ].title, cProperty::getZoneName(Property[ countProperty ].region), Property[ countProperty ].number, Property[ countProperty ].price);
		//=====================================================================================================
		Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																				   Property[ countProperty ].posX,
																				   Property[ countProperty ].posY,
																				   Property[ countProperty ].posZ, 0, 0);
		//=====================================================================================================
	}
	//-----------------------------------------------------------------------------------------------------------
	Property[ countProperty ].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
																					Property[ countProperty ].posX,
																					Property[ countProperty ].posY,
																					Property[ countProperty ].posZ, 30.0f);
	//-----------------------------------------------------------------------------------------------------------
}

void cBanks::create(int price, float x, float y, float z)
{
	sProperty tmp;
	eBanks htmp;
	int interior = cInteriors::getRandom(PropertyType::prBank);
	//--------------------------------------------------------------------------------------------
	strcpy(htmp.title, "Новый банк");
	htmp.credit = htmp.deposit = htmp.pay = 0.75f;
	//--------------------------------------------------------------------------------------------
	sprintf(query, "INSERT INTO class_Banks SET `credit` ='%f',`deposit` ='%f',`pay` ='%f',`send` ='%f', name='%s', style='%d'", 
			htmp.credit, htmp.credit, htmp.credit, htmp.credit, htmp.title, interior);
	safe_query(con, query);
	htmp.db = mysql_insert_id(con);
	//--------------------------------------------------------------------------------------------
	tmp.owner = tmp.status = tmp.bank = 0;
	tmp.property = htmp.db;
	tmp.style = interior;
	tmp.price = price;
	tmp.posX = x;
	tmp.posY = y;
	tmp.posZ = z;
	tmp.type = PropertyType::prBank;
	tmp.region = tmp.number = 0;
	//--------------------------------------------------------------------------------------------
	sprintf(query, "INSERT INTO class_Property SET `property` ='%d', type='%d', x='%f', y='%f', z='%f', price='%d'",
			tmp.property, PropertyType::prBank, x, y, z, price);
	safe_query(con, query);
	//--------------------------------------------------------------------------------------------
	tmp.link = countBanks;
	tmp.db = mysql_insert_id(con);
	Property[ countProperty ] = tmp;
	Bank[ countBanks ] = htmp;
	//--------------------------------------------------------------------------------------------
	cBanks::makePick();
	countProperty++;
	countBanks++;
}

void cBanks::actStuff(int u)
{
	char msg[300] = "";
	dialogs::genDLGItem(1, "Информация", msg);
	dialogs::genDLGItem(2, "Проценты", msg);
	dialogs::genDLGItem(3, "Название", msg);
	dialogs::genDLGItem(4, "Финансы", msg);
	ShowPlayerDialog(u, DLG_BANKOWNER_MAIN, GUI_LIST, "[Банк]: Управление", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnClose);
	Player[u].isAction = PlayerAction::ACTION_BANKBILL;
}

void cBanks::actBill(int u)
{
	char msg[ 300 ] = "";
	Player[ u ].isAction = PlayerAction::ACTION_BANKBILL;
	dialogs::genDLGItem(1, "Информация о процентах", msg);
	dialogs::genDLGItem(2, "Управление счетами", msg);
	dialogs::genDLGItem(3, "Завести счет", msg);
	ShowPlayerDialog(u, DLG_BANK_BILLING, GUI_LIST, "[Банк]: Менеджер счетов", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnClose);
}

void cBanks::accMenu(int u)
{
	char msg[ 300 ] = "";
	dialogs::genDLGItem(1, "Информация о счете", msg);
	dialogs::genDLGItem(2, "Пополнить счет", msg);
	dialogs::genDLGItem(3, "Обналичить счет", msg);
	dialogs::genDLGItem(4, "Перевести на счет", msg);
	ShowPlayerDialog(u, DLG_BANK_ACC_BILLING, GUI_LIST, "[Банк]: Менеджер счетов", msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
}

void cBanks::onDLG(int u, int dialogid, int response, int listitem, const char* inputtext)
{
	char msg[256] = "";
	const int p = Player[u].inIndex;
	const int l = Property[p].link;

	switch (dialogid)
	{
		case DIALOG_LIST::DLG_BANK_BILLING:
		{
			if (response)
			{
				if (listitem == 0)				//Проценты
				{
					char credit[sizeof(language::property::bank::percentCredit)],
						 deposi[sizeof(language::property::bank::percentDeposi)],
						 send[sizeof(language::property::bank::percentSend)],
						 pay[sizeof(language::property::bank::percentPay)];
					//------------------------------------------------------
					sprintf(credit, language::property::bank::percentCredit, Bank[l].credit);
					sprintf(send, language::property::bank::percentSend, Bank[l].send);
					sprintf(deposi, language::property::bank::percentDeposi, Bank[l].deposit);
					sprintf(pay, language::property::bank::percentPay, Bank[l].pay);
					//------------------------------------------------------
					strcpy(msg, credit), strcat(msg, send);
					strcat(msg, deposi), strcat(msg, pay);
					//------------------------------------------------------
					ShowPlayerDialog(u, DLG_BANK_PERCENT, GUI_MSG, language::property::bank::percentHeader, msg, language::dialogs::buttons::btnBack, "");
				}
				else if (listitem == 1)			//Управление счетами
				{
	case_numbers:
					MYSQL_ROW row;
					MYSQL_RES *res;

					sprintf(msg, "SELECT id,balance FROM bank_Accounts WHERE player = %d ORDER BY id ASC", Player[u].pDB);
					safe_query(con, msg);
					res = mysql_store_result(con);

					sprintf(msg, "Указать номер счёта\n");
					while (row = mysql_fetch_row(res))
					{
						sprintf(msg, "%s [%d] %.2f$\n", msg, atoi(row[0]), atof(row[1]));
					}

					mysql_free_result(res);

					ShowPlayerDialog(u, DLG_BANK_SELECTACC, GUI_LIST, language::property::bank::Header_Acc_BILL, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)			//Завести счет
				{
	case_make:
					sprintf(msg, language::property::bank::Acc_Make, Player[u].uName, Player[u].sName);
					ShowPlayerDialog(u, DLG_BABK_MAKE_ACC, GUI_INPUT, language::property::bank::Header_Acc_MAKE, msg, language::dialogs::buttons::btnNext, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_PERCENT:
		{
			cBanks::actBill(u);
			break;
		}
		case DIALOG_LIST::DLG_BABK_MAKE_ACC:
		{
			if (response)
			{
				if (regex_match(inputtext, expCode))
				{
					const int acc = createAcc(Bank[l].db, Player[u].pDB, atoi(inputtext));
					sprintf(msg, language::property::bank::afterMake, acc, atoi(inputtext));
					ShowPlayerDialog(u, DLG_BANK_PERCENT, GUI_MSG, language::property::bank::Header_Acc_MAKE, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_make;
				}
			}
			else
			{
				cBanks::actBill(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_SELECTACC:
		{
			if (response)
			{
				if (listitem == 0)
				{

				}
				else
				{
					int idx = 1;
					MYSQL_ROW row;
					MYSQL_RES *res = nullptr;

					sprintf(msg, "SELECT id,pass FROM bank_Accounts WHERE player = %d ORDER BY id ASC", Player[u].pDB);
					safe_query(con, msg);
					res = mysql_store_result(con);

					while (row = mysql_fetch_row(res))
					{
						if (listitem == idx)
						{						
							Player[u].inType = atoi(row[0]);
							Player[u].aMinerA = atoi(row[1]);
							cBanks::accMenu(u);
							break;
						}
						else
						{
							idx++;
						}
					}
					mysql_free_result(res);
	case_entercode:
					sprintf(msg, language::property::bank::enterCode, Player[u].inType);
					ShowPlayerDialog(u, DLG_BANK_SELECTPASS, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnNext, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				cBanks::actBill(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_SELECTPASS:
		{
			if (response)
			{
				if (regex_match(inputtext, expCode))
				{
					if (Player[u].aMinerA == atoi(inputtext))
					{
						cBanks::accMenu(u);
					}
					else
					{
goto case_entercode;
					}
				}
				else
				{
goto case_entercode;
				}
			}
			else
			{
goto case_numbers;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_ACC_BILLING:
		{
			if (response)
			{
				if (listitem == 0)
				{
					MYSQL_ROW row;
					MYSQL_RES *res;

					sprintf(msg, "SELECT status,balance,stamp FROM bank_Accounts WHERE id = %d LIMIT 1", Player[u].inType);
					safe_query(con, msg);
					res = mysql_store_result(con);
					row = mysql_fetch_row(res);

					sprintf(msg, "{FFFFFF}Номер счёта: {84ecff}%d\n{FFFFFF}Статус: {84ecff}%d\n{FFFFFF}Баланс: {84ecff}%.2f$\n{FFFFFF}Штамп открытия: {84ecff}%s", Player[u].inType, atoi(row[0]), atof(row[1]), row[2]);

					mysql_free_result(res);
					ShowPlayerDialog(u, DLG_BANK_EMTY2, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnBack, "");
				}
				else if (listitem == 1)
				{
	case_pay:
					sprintf(msg, "{FFFFFF}Введите сумму которую хотите положить.\nУ вас в кошельке: {84ecff}%.2f$", Player[u].pMoney);
					ShowPlayerDialog(u, DLG_BANK_PAY, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)
				{
	case_take:
					double value;
					cBanks::getBalance(Player[u].inType, &value);
					sprintf(msg, "{FFFFFF}Введите сумму которую хотите обналичить.\nТекущей баланс: {84ecff}%.2f$", value);
					ShowPlayerDialog(u, DLG_BANK_TAKE, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 3)
				{
	case_trans:
					double value;
					cBanks::getBalance(Player[u].inType, &value);
					sprintf(msg, language::property::bank::startTransfer, value);
					ShowPlayerDialog(u, DLG_BANK_TRANS, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
goto case_numbers;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_EMTY2:
		{
			cBanks::accMenu(u);
			break;
		}
		case DIALOG_LIST::DLG_BANK_TAKE:
		{
			if (response)
			{
				double value;
				const double sourceValue = atof(inputtext);
				cBanks::getBalance(Player[u].inType, &value);
				if (sourceValue > 0 && sourceValue <= value)
				{
					const float percent = (sourceValue / 100) * Bank[l].pay;
					const float afterValue = sourceValue - percent;
					Bank[l].fond += percent;
					cPlayer::givePlayerMoney(u, afterValue);
					cBanks::giveBalance(Player[u].inType, -sourceValue);
					sprintf(msg, language::property::bank::afterTake, afterValue, percent);
					ShowPlayerDialog(u, DLG_BANK_EMTY2, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_take;
				}
			}
			else
			{
				cBanks::accMenu(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_PAY:
		{
			if (response)
			{
				const double payValue = atof(inputtext);
				if (Player[u].pMoney >= payValue && payValue > 0)
				{
					cPlayer::givePlayerMoney(u, -payValue);
					cBanks::giveBalance(Player[u].inType, payValue);
					sprintf(msg, language::property::bank::afterPay, payValue);
					ShowPlayerDialog(u, DLG_BANK_EMTY2, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_pay;
				}
			}
			else
			{
				cBanks::accMenu(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANK_TRANS:
		{
			if (response)
			{
				double transValue = 0.0f;
				int number = 0;
				if (sscanf(inputtext, "%lf %d", &transValue, &number) == 2)
				{
					double value;
					cBanks::getBalance(Player[u].inType, &value);
					if (transValue >= value && transValue > 0)
					{
						const float percent = (transValue / 100) * Bank[l].send;
						const float afterValue = transValue - percent;
						Bank[l].fond += percent;
						cBanks::giveBalance(Player[u].inType, -afterValue);
						cBanks::giveBalance(number, afterValue);
						sprintf(msg, language::property::bank::afterTransfer, afterValue, percent);
						ShowPlayerDialog(u, DLG_BANK_EMTY2, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnOK, "");
					}
					else
					{
goto case_trans;
					}
				}
				else
				{
goto case_trans;
				}
			}
			else
			{
				cBanks::accMenu(u);
			}
			break;
		}
			//------------------------] Control
		case DIALOG_LIST::DLG_BANKOWNER_MAIN:
		{
			if (response)
			{
				if (listitem == 0)
				{
					sprintf(msg, "Title: %s\nFond: %.2f$", Bank[l].title, Bank[l].fond);
					ShowPlayerDialog(u, DLG_BANKOWNER_EMTY, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnBack, "");
				}
				else if (listitem == 1)
				{
	case_percents:
					sprintf(msg, "Кредит\t\t%.1f%%\nВклад\t\t%.1f%%\nПеревод\t\t%.1f%%\nОплата\t\t%.1f%%", Bank[l].credit, Bank[l].deposit, Bank[l].send, Bank[l].pay);
					ShowPlayerDialog(u, DLG_BANKOWNER_PERCENTS, GUI_LIST, Bank[l].title, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 2)
				{
	case_setname:
					sprintf(msg, "Введите новое название банка.\nТекущие название: %s", Bank[l].title);
					ShowPlayerDialog(u, DLG_BANKOWNER_SETNAME, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else if (listitem == 3)
				{
					dialogs::genDLGItem(1, "Снять", msg);
					dialogs::genDLGItem(2, "Положить", msg);
					ShowPlayerDialog(u, DLG_BANKOWNER_MONEY, GUI_LIST, Bank[l].title, msg, language::dialogs::buttons::btnSelect, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_EMTY:
		{
			cBanks::actStuff(u);
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_PERCENTS:
		{
			if (response)
			{
				if (listitem == 0)
				{
	case_pCredit:
					sprintf(msg, "Введите новый процент кредита.\nТекущей процент: %.1f%%", Bank[l].credit);
				}
				else if (listitem == 1)
				{
	case_pDeposit:
					sprintf(msg, "Введите новый процент вклада.\nТекущей процент: %.1f%%", Bank[l].deposit);
				}
				else if (listitem == 2)
				{
	case_pSend:
					sprintf(msg, "Введите новый процент перевода.\nТекущей процент: %.1f%%", Bank[l].send);
				}
				else if (listitem == 3)
				{
	case_pPay:
					sprintf(msg, "Введите новый процент оплаты.\nТекущей процент: %.1f%%", Bank[l].pay);
				}
				Player[u].inIndex = listitem + 1;
				ShowPlayerDialog(u, DLG_BANKOWNER_PERCENTS_SET, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
			}
			else
			{
				cBanks::actStuff(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_PERCENTS_SET:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					const float percent = atof(inputtext);
					if (Player[u].inIndex == 1)
					{
						Bank[l].credit = percent;
						sprintf(msg, "Процент кредита установлен: %.1f%%", percent);
					}
					else if (Player[u].inIndex == 2)
					{
						Bank[l].deposit = percent;
						sprintf(msg, "Процент вклада установлен: %.1f%%", percent);
					}
					else if (Player[u].inIndex == 3)
					{
						Bank[l].send = percent;
						sprintf(msg, "Процент перевода установлен: %.1f%%", percent);
					}
					else if (Player[u].inIndex == 4)
					{
						Bank[l].pay = percent;
						sprintf(msg, "Процент оплаты установлен: %.1f%%", percent);
					}
					ShowPlayerDialog(u, DLG_BANKOWNER_EMTY, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
					if (Player[u].inIndex == 1)
goto case_pCredit;
					else if (Player[u].inIndex == 2)
goto case_pDeposit;
					else if (Player[u].inIndex == 3)
goto case_pSend;
					else if (Player[u].inIndex == 4)
goto case_pPay;
				}
			}
			else
			{
goto case_percents;
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_SETNAME:
		{
			if (response)
			{
				if (regex_match(inputtext, expString))
				{
					sprintf(Bank[l].title, inputtext);
					cBanks::updateText(p, -1);
					sprintf(msg, "Название установлено: %s", Bank[l].title);
					ShowPlayerDialog(u, DLG_BANKOWNER_EMTY, GUI_MSG, Bank[l].title, msg, language::dialogs::buttons::btnOK, "");
				}
				else
				{
goto case_setname;
				}
			}
			else
			{
				cBanks::actStuff(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_MONEY:
		{
			if (response)
			{
				if (listitem == 0)
				{
	case_oPay:
					sprintf(msg, "Введите сумму которую хотите обналичить.\nТекущей баланс: %.2f$", Bank[l].fond);
					ShowPlayerDialog(u, DLG_BANKOWNER_MONEY_PAY, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
				else
				{
	case_oDep:
					sprintf(msg, "Введите сумму которую хотите положить.\nУ вас в кошельке: %.2f$", Player[u].pMoney);
					ShowPlayerDialog(u, DLG_BANKOWNER_MONEY_DEP, GUI_INPUT, Bank[l].title, msg, language::dialogs::buttons::btnDone, language::dialogs::buttons::btnBack);
				}
			}
			else
			{
				cBanks::actStuff(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_MONEY_PAY:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					const double value = atof(inputtext);
					if (Bank[l].fond >= value)
					{
						Bank[l].fond -= value;
						cPlayer::givePlayerMoney(u, value);
						ShowPlayerDialog(u, DLG_BANKOWNER_EMTY, GUI_MSG, Bank[l].title, "Операция выполнена успешно.", language::dialogs::buttons::btnOK, "");
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
				cBanks::actStuff(u);
			}
			break;
		}
		case DIALOG_LIST::DLG_BANKOWNER_MONEY_DEP:
		{
			if (response)
			{
				if (regex_match(inputtext, expFloat))
				{
					const double value = atof(inputtext);
					if (Player[u].pMoney >= value)
					{
						Bank[l].fond += value;
						cPlayer::givePlayerMoney(u, -value);
						ShowPlayerDialog(u, DLG_BANKOWNER_EMTY, GUI_MSG, Bank[l].title, "Операция выполнена успешно.", language::dialogs::buttons::btnOK, "");
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
				cBanks::actStuff(u);
			}
			break;
		}
	}
}

/// <summary>
/// Узнать баланс счета
/// <param name="num">* Ид счета</param>
/// <param name="res">* Баланс</param>
/// </summary>
void cBanks::getBalance(int num, double *res)
{
	MYSQL_ROW row;
	//-----------------------------
	sprintf(query, "SELECT `balance` FROM bank_Accounts WHERE id='%d'", num),	safe_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------
	*res = ( row = mysql_fetch_row(result) ) ? (atof(row[ 0 ])) : (0);
}

/// <summary>
/// Узнать существует ли счёт
/// <param name="num">* Ид счета</param>
/// </summary>
bool cBanks::isValidNumber(int num)
{
	//-----------------------------
	sprintf(query, "SELECT NULL FROM bank_Accounts WHERE id='%d'", num), safe_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------
	return (mysql_num_rows(result)) ? true : false;
}

/// <summary>
/// Установить баланс счета
/// <param name="num">* Ид счета</param>
/// <param name="value">* Баланс</param>
/// </summary>
void cBanks::setBalance(int num, double value)
{
	sprintf(query, "UPDATE bank_Accounts SET `balance`='%.2f' WHERE id='%d'", value, num);
	safe_query(con, query);
}

/// <summary>
/// Добавить сумму на счет
/// <param name="num">* Ид счета</param>
/// <param name="value">* Сумма</param>
/// </summary>
void cBanks::giveBalance(int num, double value)
{
	sprintf(query, "UPDATE bank_Accounts SET `balance`=`balance` + '%.2f'  WHERE id='%d'", value, num);
	safe_query(con, query);
}

/// <summary>
/// Принадлежит счет банку
/// <param name="num">* Ид счета</param>
/// <param name="bank">* Ид банка</param>
/// </summary>
bool cBanks::atBank(int num, double bank)
{
	//-----------------------------
	sprintf(query, "SELECT `NULL` FROM bank_Accounts WHERE id='%d' AND owner='%d'", num, bank), safe_query(con, query);
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------
	return ( mysql_num_rows(result) ) ? ( true ) : ( false );
}

int cBanks::createAcc(int bank, int player, int pass)
{
	//------------------------------------------------------------------
	sprintf(query, "INSERT INTO bank_Accounts (owner, player, pass) VALUES (%d, %d, %d)", bank, player, pass);
	safe_query(con, query);
	//------------------------------------------------------------------
	return mysql_insert_id(con);
}

void cBanks::updateText(const int p, const int u = -1)
{
	char msg[256];
	if (u != -1) sprintf(Property[p].player, "%s %s", Player[u].uName, Player[u].sName);
	sprintf(msg, "{FFFFFF}Банк: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
		Bank[Property[p].link].title,
		cProperty::getZoneName(Property[p].region), Property[p].number,
		Property[p].player);
	//------------------------------------------------------------------
	StreamerCall::Native::UpdateDynamic3DTextLabelText(Property[p].text, -1, msg);
}

void cBanks::saveBanks()
{
	for (int i = 0; i < MAX_BANKS; i++)
	{
		char msg[184];
		sprintf(msg, "UPDATE class_Banks SET credit = %.1f, deposit = %.1f, pay = %.1f, send = %.1f, name = '%s', fond = %.2f WHERE id = %d",
					  Bank[i].credit, Bank[i].deposit, Bank[i].pay, Bank[i].send, Bank[i].title, Bank[i].fond, Bank[i].db);
		safe_query(con, msg);
	}
}
