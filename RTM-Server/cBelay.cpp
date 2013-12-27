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
			
			const int idx = Player[ u ].inIndex;
			//---------------------------------
			if (Property[ idx ].owner == Player[ u ].pDB)
			{
				char msg[ 256 ];
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
				char msg[ 512 ];
				sprintf
				(
					msg, 
					"������������ �� ������ ������������ ���� ����� �� %d$\
					\n������ ��������� ����� ��������� ����� ��������� �������.\
					\n��� ��������� � ���:  \t\t\t%d%%\
					\n��� ������������� �������: \t\t\t%d%%\
					\n��� ������� ������� �������: \t\t%d%%\
					\n��� ������� � ���������: \t\t\t%d%%\
					\n��� ��������� ������������: \t\t%d%%"
				);
				//******************************************
				ShowPlayerDialog
				(
					u,
					DLG_BELAY_OWNER_MAIN,
					GUI_MSG,
					"[��������� ��������]: ���� ���������",
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
			if (dialogid == DLG_BELAY_OWNER_MAIN)
			{
				if (response)
				{
					//===============================
					if (listitem == 0)					//����������
					{
						
					}
					//===============================
					else if (listitem == 1)				//����������
					{

					}
					//===============================
					else if (listitem == 2)				//��������������
					{

					}
					//===============================
					else if (listitem == 4)				//���������
					{

					}
					//===============================
				}
				else
				{

				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if (dialogid == DLG_BELAY_OWNER_MAIN)
			{
				if (response)
				{

				}
				else
				{

				}
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}
}
