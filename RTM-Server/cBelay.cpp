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
			if (safe_query(con, "SELECT class_Property.*, class_Belay.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_Belay  WHERE class_Property.property = class_Belay.id AND class_Property.type = 9"))
			{
				logprintf("�� ������� ��������� ��������� ��������");
				return;
			}
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
			logprintf("���� ���������� %d ��������� �������", count);
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
					"\"%s\" \n ��������� ������� \n{FFFFFF}�����: {B7FF00}%s {FFFFFF}�: {B7FF00}%d\n{FFFFFF}��������: {B7FF00}%s",
					Belay[ count ].name,
					cProperty::getZoneName(Property[ countProperty ].region),
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
					"��������� ������� \n{FFFFFF}�����: {FF0000}%s {FFFFFF}�: {FF0000}%d\n{FFFFFF}���������: {FF0000}%d$",
					cProperty::getZoneName(Property[ countProperty ].region),
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
			const int idx = Player[ u ].inIndex;		// �� ��������
			const int bdx = Player[ u ].inIndex;		// �� ���������
			Player[u].isAction = PlayerAction::ACTION_Belay;
			//---------------------------------
			if (Property[ idx ].owner != Player[ u ].pDB)
			{
				char msg[ 256 ] = "";
				//******************************************
				dialogs::genDLGItem(1, "����������", msg);
				dialogs::genDLGItem(2, "����������", msg);
				dialogs::genDLGItem(3, "��������������", msg);
				dialogs::genDLGItem(4, "���������", msg);
				//******************************************
				ShowPlayerDialog
				(
					u, 
					DLG_BELAY_OWNER_MAIN, 
					GUI_LIST,
					"[��������� ��������]: ���� ���������",
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
					"������������, �� ������ ������������ ���� ����� �� %d$?\
					\n������ ��������� ����� ��������� ����� ��������� �������.\
					\n��� ��������� � ���:  \t\t\t\t\t%d%%\
					\n��� ������������� �������: \t\t\t\t%d%%\
					\n��� ������� �������: \t\t\t\t\t\t\t%d%%\
					\n��� ������� � ���������: \t\t\t\t\t%d%%\
					\n��� ��������� ������������: \t\t\t\t%d%%",
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
					"[��������� ��������]: ����������� �����",
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
			const int idx = Player[ u ].inIndex;		// �� ��������
			const int bdx = Property[idx].link;		// �� ���������

			if (dialogid == DLG_BELAY_OWNER_MAIN)
			{
				if (response)
				{
					//===============================
					if (listitem == 0)					//����������
					{
						sprintf
						(
							msg, 
							"������ ��������� ����� ��������� ����� ��������� �������.\
							\n��� ��������� � ���:  \t\t\t\t%d%%\
							\n��� ������������� �������: \t\t\t\t%d%%\
							\n��� ������� �������: \t\t\t\t%d%%\
							\n��� ������� � ���������: \t\t\t\t%d%%\
							\n��� ��������� ������������: \t\t\t%d%%\
							\n��������� ���������� �����������: \t\t\t%d$",
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
							"[���� ���������]: ����������",	msg,
							language::dialogs::buttons::btnBack,
							""
						);
						//******************************************
					}
					//===============================
					else if (listitem == 1)				//����������
					{
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_STATS, 
							GUI_MSG,
							"[���� ���������]: ����������",
							"������ ������ ��������� � ����������",
							language::dialogs::buttons::btnBack,
							""
						);
						//******************************************
					}
					//===============================
					else if (listitem == 2)				//��������������
					{
						msg_Finance:
						strcpy(msg, "");
						dialogs::genDLGItem(1, "������� ��� ���", msg);
						dialogs::genDLGItem(2, "������� ��� ������������� �������", msg);
						dialogs::genDLGItem(3, "������� ��� ��������� ������������", msg);
						dialogs::genDLGItem(4, "������� ��� ������� � ���������", msg);
						dialogs::genDLGItem(5, "������� ��� ������� �������", msg);
						dialogs::genDLGItem(6, "��������� ��������� ���������", msg);
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_FINANCE, 
							GUI_LIST,
							"[���� ���������]: ��������������",	msg,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
						//******************************************						
					}
					//===============================
					else if (listitem == 4)				//���������
					{
						msg_ETC:
						strcpy(msg, "");
						dialogs::genDLGItem(1, "�������� ��������", msg);
						dialogs::genDLGItem(2, "�������� ����� �����", msg);
						dialogs::genDLGItem(3, "�������� ����� ������", msg);
						dialogs::genDLGItem(4, "�������� �� ����", msg);
						dialogs::genDLGItem(5, "����� �� �����", msg);
						//******************************************
						ShowPlayerDialog
						(
							u, 
							DLG_BELAY_OWNER_ETC, 
							GUI_LIST,
							"[���� ���������]: ���������",	msg,
							language::dialogs::buttons::btnNext,
							language::dialogs::buttons::btnBack
						);
						//******************************************			
					}
					//===============================
				}
				else
				{
					Player[u].isAction = PlayerAction::ACTION_NONE;
				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_ETC)
			{
				if(response)
				{
					if (listitem == 0)			// �������� ��������
					{

					}
					else if (listitem == 1)		// �������� ����� �����
					{

					}
					else if (listitem == 1)		// �������� ����� ������
					{

					}
				}
				else
				{
					onAction(u);
				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_INFO)
			{
				onAction(u);
			}
			else if (dialogid == DLG_BELAY_OWNER_STATS)
			{
				onAction(u);
			}
			else if (dialogid == DLG_BELAY_OWNER_FINANCE)
			{
				if(response)
				{
					if (listitem == 0)			// ������� ��� ���
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
					else if (listitem == 1)		// ������� ��� ��������� ������������
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
					else if (listitem == 2)		// ������� ��� ��������� ������������
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
					else if (listitem == 3)		// ������� ��� ������� � ���������
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
					else if (listitem == 4)		// ������� ���  ������� �������
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
					else if (listitem == 5)		// ��������� ���������
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
						SendClientMessage(u, -1, "�������, ��� ������� ������ ���� ��������!");
						cPlayer::givePlayerMoney(u, -Belay[bdx].price);
						regPlayer(u, Belay[bdx].db);
					}
				}
				Player[u].isAction = PlayerAction::ACTION_NONE;
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
					idb, Player[u].pDB
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
					idb, Player[u].pDB
				);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				safe_query(con, query);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				Player[u].belay = mysql_insert_id(con);
			}
		}	
		bool checkPlayer(int u)
		{
			sprintf
			(
				query, 
				"SELECT NULL FROM Belay_Clients WHERE player = '%d' LIMIT 1",
				Player[u].pDB
			);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			safe_query(con,  query);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			MYSQL_RES *result = mysql_store_result(con);
			int num_rows = mysql_num_rows(result);
			mysql_free_result(result);
			return (num_rows == 1) ? (true) : (false);
		}
	}
}
