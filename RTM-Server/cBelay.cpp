#include "main.h"


namespace Properties
{
	namespace Belays
	{
		int count;
		struct sBelay Belay[ MAX_Belays ];
		//------------------------------------------------
		void load()
		{
			MYSQL_ROW row;
			MYSQL_RES *result;
			int slot = -1;
			int farm = 0;
			cProperty::propertyLoadQuery(PropertyType::prBelays);
			/*if (safe_query(con, "SELECT class_Property.*, class_Belay.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Belay  WHERE class_Property.property = class_Belay.id AND class_Property.type = 9"))
			{
				logprintf("Не удалось загрузить страховые компании");
				return;
			}*/
			//===================================================================================
			result = mysql_store_result(con);
			while (( row = mysql_fetch_row(result) ))
			{
				Property[ countProperty ].db = atoi(row[ rowBelays::id ]);
				Property[ countProperty ].bank = atoi(row[ rowBelays::bank ]);
				Property[ countProperty ].owner = atoi(row[ rowBelays::owner ]);
				Property[ countProperty ].price = atoi(row[ rowBelays::price ]);
				Property[ countProperty ].type = atoi(row[ rowBelays::type ]);
				Property[ countProperty ].posX = atof(row[ rowBelays::x ]);
				Property[ countProperty ].posY = atof(row[ rowBelays::y ]);
				Property[ countProperty ].posZ = atof(row[ rowBelays::z ]);
				Property[ countProperty ].property = atoi(row[ rowBelays::property ]);
				Property[ countProperty ].region = atoi(row[ rowBelays::region ]);
				Property[ countProperty ].number = atoi(row[ rowBelays::number ]);
				Property[ countProperty ].style = atoi(row[ rowBelays::style ]);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				Belay[ count ].db		= atoi(row[ rowBelays::db ]);
				Belay[ count ].price	= atoi(row[ rowBelays::bprice ]);
				Belay[ count ].start	= atoi(row[ rowBelays::tstart ]);
				Belay[ count ].end		= atoi(row[ rowBelays::tend ]);
				Belay[ count ].fond		= atof(row[ rowBelays::balance ]);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				Belay[ count ].perDrive = atoi(row[ rowBelays::perDrive ]);
				Belay[ count ].perEtc	= atoi(row[ rowBelays::perEtc ]);
				Belay[ count ].perFight = atoi(row[ rowBelays::perFight ]);
				Belay[ count ].perFire	= atoi(row[ rowBelays::perFire ]);
				Belay[ count ].perSick	= atoi(row[ rowBelays::perSick ]);
				Belay[ count ].perStab	= atoi(row[ rowBelays::perStab ]);
				Property[countProperty].link = count;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				strcpy(Belay[ count ].name, row[ rowBelays::name]);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (Property[ countProperty ].owner)
				{
					strcpy(Property[ countProperty ].player, row[ rowBelays::pname ]);
				}
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				makePick();
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				countProperty++;
				count++;
			}
			mysql_free_result(result);
			logprintf("Было загруженно %d страховых команий", count);
		}
		//------------------------------------------------
		void makePick()
		{
			char msg[256];
			if (Property[ countProperty ].owner)
			{
				sprintf
				(
					msg,
					"\"%s\" \n Страховая комания \n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
					Belay[ count ].name,
					getSaZoneName(Property[ countProperty ].region),
					Property[ countProperty ].number,
					Property[ countProperty ].player
				);
				//=====================================================================================================
				Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup
				(
					HOUSE_GREEN, 23,
					Property[ countProperty ].posX,
					Property[ countProperty ].posY,
					Property[ countProperty ].posZ,
					0, 0
				);
				//=====================================================================================================
			}
			else
			{
				sprintf
				(
					msg,
					"Страховая комания \n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$",
					getSaZoneName(Property[ countProperty ].region),
					Property[ countProperty ].number,
					Property[ countProperty ].price
				);
				//=====================================================================================================
				Property[ countProperty ].pick = StreamerCall::Native::CreateDynamicPickup
				(
					HOUSE_RED, 23,
					Property[ countProperty ].posX,
					Property[ countProperty ].posY,
					Property[ countProperty ].posZ, 0, 0
				);
				//=====================================================================================================
			}
			Property[ countProperty ].text = StreamerCall::Native::CreateDynamic3DTextLabel
			(
				msg, -1,
				Property[ countProperty ].posX,
				Property[ countProperty ].posY,
				Property[ countProperty ].posZ,
				30.0f
			);
		}
		//-----------------------------------------------------------------------------
		void onAction(const int u)
		{
			const int idx = Player[ u ].status.inIndex;		// Ид проперти
			const int bdx = Player[ u ].status.inIndex;		// Ид страховой
			Player[u].status.action = PlayerAction::ACTION_Belay;
			//---------------------------------
			if (Property[ idx ].owner != Player[ u ].base.db)
			{
				char msg[ 256 ] = "";
				//******************************************
				dialogs::genDLGItem(1, "Информация", msg);
				dialogs::genDLGItem(2, "Статистика", msg);
				dialogs::genDLGItem(3, "Финансирование", msg);
				dialogs::genDLGItem(4, "Остальное", msg);
				//******************************************
				ShowPlayerDialog
				(
					u, 
					DLG_BELAY_OWNER_MAIN, 
					GUI_LIST,
					"[Страховая компания]: Меню владельца",
					msg,
					language::dialogs::buttons::btnNext,
					language::dialogs::buttons::btnClose
				);
				//******************************************
			}
			//=============================================
			else
			{
				char msg[ 512 ] = "";
				sprintf
				(
					msg, 
					"Здравствуйте, вы хотите застраховать свою жизнь за %d$?\
					\nДанная страховка будет покрывать часть стоимости лечения.\
					\nПри попадении в ДТП:  \t\t\t\t\t%d%%\
					\nПри огнестрельном ранении: \t\t\t\t%d%%\
					\nПри ножевом ранении: \t\t\t\t\t\t\t%d%%\
					\nПри травмах и переломах: \t\t\t\t\t%d%%\
					\nПри различных заболеваниях: \t\t\t\t%d%%",
					Belay[bdx].price,
					Belay[bdx].perDrive,
					Belay[bdx].perFire,
					Belay[bdx].perStab,
					Belay[bdx].perFight,
					Belay[bdx].perSick
				);
				//******************************************
				ShowPlayerDialog
				(
					u,
					DLG_BELAY_CLIENT_MAIN,
					GUI_MSG,
					"[Страховая компания]: Страхование жизни",
					msg,
					language::dialogs::buttons::btnNext,
					language::dialogs::buttons::btnClose
				);
				//******************************************
			}
		}
		//-----------------------------------------------------------------------------
		void onDLG(int u, int dialogid, int response, int listitem, const char* inputtext)
		{
			char msg[ 512 ] = "";
			const int idx = Player[ u ].status.inIndex;		// Ид проперти
			const int bdx = Property[idx].link;		// Ид страховой
			if (dialogid == DLG_BELAY_OWNER_MAIN)
			{
				if (response)
				{
					//===============================
					if (listitem == 0)					//Информация
					{
						sprintf
						(
							msg, 
							"Данная страховка будет покрывать часть стоимости лечения.\
							\nПри попадении в ДТП:  \t\t\t\t%d%%\
							\nПри огнестрельном ранении: \t\t\t\t%d%%\
							\nПри ножевом ранении: \t\t\t\t%d%%\
							\nПри травмах и переломах: \t\t\t\t%d%%\
							\nПри различных заболеваниях: \t\t\t%d%%\
							\nСтоимость недельного страхования: \t\t\t%d$",
							Belay[bdx].perDrive,
							Belay[bdx].perFire,
							Belay[bdx].perStab,
							Belay[bdx].perFight,
							Belay[bdx].perSick,
							Belay[bdx].price
						);
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_INFO, 
							GUI_MSG,
							"[Меню владельца]: Информация",	msg,
							language::dialogs::buttons::btnBack,
							""
						);
						//******************************************
					}
					//===============================
					else if (listitem == 1)				//Статистика
					{
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_STATS, 
							GUI_MSG,
							"[Меню владельца]: Статистика",
							"Данный раздел находится в разработке",
							language::dialogs::buttons::btnBack,
							""
						);
						//******************************************
					}
					//===============================
					else if (listitem == 2)				//Финансирование
					{
						msg_Finance:
						strcpy(msg, "");
						dialogs::genDLGItem(1, "Выплаты при ДТП", msg);
						dialogs::genDLGItem(2, "Выплаты при огнестрельном ранении", msg);
						dialogs::genDLGItem(3, "Выплаты при различных заболеваниях", msg);
						dialogs::genDLGItem(4, "Выплаты при травмах и переломах", msg);
						dialogs::genDLGItem(5, "Выплаты при ножевом ранении", msg);
						dialogs::genDLGItem(6, "Назначить стоимость страховки", msg);
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_FINANCE, 
							GUI_LIST,
							"[Меню владельца]: Финансирование",	msg,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
						//******************************************						
					}
					//===============================
					else if (listitem == 3)				//Остальное
					{
						msg_ETC:
						strcpy(msg, "");
						dialogs::genDLGItem(1, "Изменить название", msg);
						dialogs::genDLGItem(2, "Изменить номер счета", msg);
						dialogs::genDLGItem(3, "Изменить время работы", msg);
						dialogs::genDLGItem(4, "Положить на счет", msg);
						dialogs::genDLGItem(5, "Снять со счета", msg);
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_ETC, 
							GUI_LIST,
							"[Меню владельца]: Остальное",	msg,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
						//******************************************			
					}
					//===============================
				}
				else
				{
					Player[u].status.action = PlayerAction::ACTION_NONE;
				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_ETC)
			{
				if(response)
				{
					if (listitem == 0)			// Изменить название
					{
						msg_ETC_Name:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_ETC_NAME,
							GUI_INPUT,
							"[Страховая компания]: Название",
							language::property::belay::etc_Name,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);				
					}
					else if (listitem == 1)		// Изменить номер счета
					{
						msg_ETC_Bank:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_ETC_BANK,
							GUI_INPUT,
							"[Страховая компания]: Название",
							language::property::belay::etc_Bank,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);	
					}
					else if (listitem == 1)		// Изменить время работы
					{
						onAction(u);
					}
				}
				else
				{
					onAction(u);
				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_ETC_NAME)
			{
				if(response)
				{
					if(regex_match(inputtext, expTitlus))
					{
						strcpy(Belay[bdx].name, inputtext);
						cClass::sqlSetString("class_Belay", "name", Belay[bdx].name,    Property[idx].db);
						SendClientMessage(u, -1, "Вы успешно изменили название вашей страховой компании!");
					}
					else goto msg_ETC_Name;
				}
				else goto msg_ETC;
				onAction(u);
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_ETC_BANK)
			{
				if(response)
				{
					const int res = atoi(inputtext);
					if(res > 0)
					{
						Property[idx].bank = res;
						cClass::sqlSetInt("class_Property", "bank", Property[idx].bank,    Property[idx].db);
						SendClientMessage(u, -1, "Вы успешно изменили номер счета вашей страховой компании!");
					}
					else goto msg_ETC_Bank;
				}
				else goto msg_ETC;
				onAction(u);
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_INFO)
			{
				onAction(u);
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_STATS)
			{
				onAction(u);
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_FINANCE)
			{
				if(response)
				{
					if (listitem == 0)			// Выплаты при ДТП
					{
						msg_Drive:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_AUTO,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_DriveBy,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
					}
					else if (listitem == 1)		// Выплаты при различных заболеваниях
					{
						msg_Fire:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_Fire,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_perFire,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
					}
					else if (listitem == 2)		// Выплаты при различных заболеваниях
					{
						msg_Sick:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_Sick,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_perSick,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
					}
					else if (listitem == 3)		// Выплаты при травмах и переломах
					{
						msg_Fight:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_Fight,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_perFight,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
					}			
					else if (listitem == 4)		// Выплаты при  ножевом ранении
					{
						msg_Stab:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_Stab,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_perStab,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
					}				
					else if (listitem == 5)		// стоимость страховки
					{
						msg_Price:
						ShowPlayerDialog
						(
							u,
							DLG_BELAY_OWNER_FINANCE_Price,
							GUI_INPUT,
							language::property::belay::finance_HEADER,
							language::property::belay::finance_Price,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);			
					}
				}
				else
				{
					 onAction(u);
				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_FINANCE_AUTO)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].perDrive) == 1)
					{
						cClass::sqlSetInt("class_Belay", "perDrive", Belay[bdx].perDrive,   Belay[bdx].db);
					}
					else goto msg_Drive;
				}
				goto msg_Finance;
			}
			else if (dialogid == DLG_BELAY_OWNER_FINANCE_Fire)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].perFire) == 1)
					{
						cClass::sqlSetInt("class_Belay", "perFire", Belay[bdx].perFire,   Belay[bdx].db);
					}
					else goto msg_Fire;
				}
				goto msg_Finance;
			}
			else if (dialogid == DLG_BELAY_OWNER_FINANCE_Sick)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].perSick) == 1)
					{
						cClass::sqlSetInt("class_Belay", "perSick", Belay[bdx].perSick,   Belay[bdx].db);
					}
					else goto msg_Sick;
				}
				goto msg_Finance;
			}	
			else if (dialogid == DLG_BELAY_OWNER_FINANCE_Fight)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].perFight) == 1)
					{
						cClass::sqlSetInt("class_Belay", "perFight", Belay[bdx].perFight,   Belay[bdx].db);
					}
					else goto msg_Fight;
				}
				goto msg_Finance;
			}
			else if (dialogid == DLG_BELAY_OWNER_FINANCE_Stab)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].perStab) == 1)
					{
						cClass::sqlSetInt("class_Belay", "perStab", Belay[bdx].perStab,   Belay[bdx].db);
					}
					else goto msg_Stab;
				}
				goto msg_Finance;
			}

			else if (dialogid == DLG_BELAY_OWNER_FINANCE_Price)
			{
				if (response)
				{
					if(sscanf(inputtext, "%d", &Belay[bdx].price) == 1)
					{
						cClass::sqlSetInt("class_Belay", "price", Belay[bdx].price,   Belay[bdx].db);
					}
					else goto msg_Price;
				}
				goto msg_Finance;
			}
			else if (dialogid == DLG_BELAY_CLIENT_MAIN)
			{
				if (response)
				{
					if(cPlayer::checkMoney(u, Belay[bdx].price))
					{
						SendClientMessage(u, -1, "Спасибо, что выбрали именно нашу компанию!");
						cPlayer::givePlayerMoney(u, -Belay[bdx].price);
						regPlayer(u, Belay[bdx].db);
					}
				}
				Player[u].status.action = PlayerAction::ACTION_NONE;
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		//=========================================================================
		void regPlayer(int u, int idb)
		{
			if(checkPlayer(u))
			{
				sprintf
				(
					query, 
					"UPDATE Belay_Clients SET belay=%d, tstart=NOW(), tend=NOW()+7 WHERE player = '%d'",
					idb, Player[u].base.db
				);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				safe_query(con, query);
			}
			else
			{
				sprintf
				(
					query, 
					"INSERT INTO Belay_Clients SET belay=%d, player=%d, tstart=NOW(), tend=NOW()+7",
					idb, Player[u].base.db
				);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				safe_query(con, query);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				Player[u].xuita.belay = mysql_insert_id(con);
			}
		}	

		int searchLocal(int global)
		{
			for(int i = 0; i < count; i++)
			{
				if(global == Belay[i].db) return i;
			}
			return -1;
		}

		void purchase(int u)
		{
			double tBal;
			int resPrice;
			char msg[144];
			const int price = DEFAULT_HEAL_PRICE;								
			const int bdx = Player[u].xuita.belay;
			const int reas = cPlayer::getDeathType(Player[u].xuita.reason);	
			//------------------------------------------------------------------------
			if(reas == DeathTypes::reason_Drive)
				resPrice = (price * Properties::Belays::Belay[bdx].perDrive / 100);
			//------------------------------------------------------------------------
			else if(reas == DeathTypes::reason_Fight)
				resPrice =  (price * Properties::Belays::Belay[bdx].perFight / 100);
			//------------------------------------------------------------------------
			else if(reas == DeathTypes::reason_Fire)
				resPrice = (price * Properties::Belays::Belay[bdx].perFire / 100);
			//------------------------------------------------------------------------
			else if(reas == DeathTypes::reason_Stab)
				resPrice = (price * Properties::Belays::Belay[bdx].perStab / 100);
			//------------------------------------------------------------------------
			if(Properties::Belays::Belay[bdx].fond >= resPrice)
			{
				Properties::Belays::Belay[bdx].fond -= resPrice;
				msg_GOOD:
				//------------------------------------------------------------------------
				sprintf
				(
					msg, 
					"Страховая компания %s оплатила %d/%d$ за лечение",
					Properties::Belays::Belay[bdx].name,
					resPrice, price
				);
				//-----------------------------------------------------------------------
				if(tBal)
				{
					cBanks::giveBalance
					(
						Property[Player[u].status.inIndex].bank,
						-resPrice
					);
				}
			}
			else
			{
				if(Property[Player[u].status.inIndex].bank)
				{
					cBanks::getBalance(Property[Player[u].status.inIndex].bank, &tBal);		
					if(tBal >= resPrice) goto msg_GOOD;
				}
				resPrice = 0;
				//------------------------------------------------------------------------
				sprintf
				(
					msg, 
					"К сожалению, страховая компания %s не смогла оплатить ваши расходы за лечение: %d$",
					Properties::Belays::Belay[bdx].name, price
				);
				//------------------------------------------------------------------------
			}
			GivePlayerMoney(u, -(price-resPrice));
			SendClientMessage(u, -1, msg);
		}

		bool checkPlayer(int u)
		{
			sprintf
			(
				query, 
				"SELECT NULL FROM Belay_Clients WHERE player = '%d' LIMIT 1",
				Player[u].base.db
			);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			safe_query(con,  query);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			MYSQL_RES *result = mysql_store_result(con);
			int num_rows = mysql_num_rows(result);
			mysql_free_result(result);
			return (num_rows == 1) ? (true) : (false);
		}

		void create(int price, float x, float y, float z)
		{
			sProperty tmp;
			sBelay hBel;
			int interior = cInteriors::getRandom(PropertyType::prBelays);
			//--------------------------------------------------------------------------------------------
			sprintf(query, "INSERT INTO class_Belay SET `style` ='%d'", interior), safe_query(con, query);
			hBel.db = mysql_insert_id(con);
			tmp.style = interior;
			//--------------------------------------------------------------------------------------------
			tmp.owner		= tmp.status = tmp.bank = 0;
			tmp.property	= hBel.db;
			tmp.style		= interior;
			tmp.price		= price;
			tmp.posX = x;
			tmp.posY = y;
			tmp.posZ = z;
			tmp.type = PropertyType::prBelays;
			tmp.region = tmp.number = 0;
			//--------------------------------------------------------------------------------------------
			sprintf(query, "INSERT INTO class_Property SET `property` ='%d', type='%d', x='%f', y='%f', z='%f', price='%d'",
				tmp.property, PropertyType::prBelays, x, y, z, price);
			safe_query(con, query);
			//--------------------------------------------------------------------------------------------
			tmp.link = countHouses;
			tmp.db = mysql_insert_id(con);
			Property[ countProperty ] = tmp;
			Belay[count] = hBel;
			//--------------------------------------------------------------------------------------------
			logprintf("db: %d[%d] || owner: %d || style: %d || xyz [%f || %f || %f]", tmp.db, tmp.property, tmp.owner, tmp.style, tmp.posX, tmp.posY, tmp.posZ);
			makePick();
			countProperty++;
			count++;
		}


	//-----------------------
	}
}



