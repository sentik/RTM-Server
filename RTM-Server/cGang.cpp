#include "main.h"




namespace world
{
	namespace gangs
	{
		int count;
		struct sGang Gang[ MAX_GANGS ] = { { 0, 0 } };
		//----------------------------------
		void load()
		{
			MYSQL_ROW row;
			MYSQL_RES *result;
			int slot = -1;
			int gang = 0;
			//===========================================
			safe_query(con, "SELECT * FROM world_Gangs");
			result = mysql_store_result(con);
			while (( row = mysql_fetch_row(result) ))
			{
				Gang[ count ].db		= atoi(row[ 0 ]);
				Gang[ count ].owner		= atoi(row[ 1 ]);
				Gang[ count ].color		= atoi(row[ 2 ]);
				Gang[ count ].rep		= atoi(row[ 3 ]);
				Gang[ count ].prop		= atoi(row[ 5 ]);
				//-----------------------------------
				strcpy(Gang[ count ].name, row[ 4 ]);
				count++;
			}
			mysql_free_result(result);
			//===========================================
			safe_query(con, "SELECT * FROM Gang_Ranks");
			result = mysql_store_result(con);
			while (( row = mysql_fetch_row(result) ))
			{
				if (gang == atoi(row[ 1 ])-1 && slot < 5) slot++;
				else
				{
					gang = atoi(row[ 1 ])-1;
					slot = 0;
				}
				//-----------------------------------
				Gang[ gang ].ranks[ slot ].db			=   atoi(row[ 0 ]);
				Gang[ gang ].ranks[ slot ].useChat		= ( atoi(row[ 3 ]) ) ? ( true ) : (false );
				Gang[ gang ].ranks[ slot ].useVehs		= ( atoi(row[ 4 ]) ) ? ( true ) : ( false );
				Gang[ gang ].ranks[ slot ].useWares		= ( atoi(row[ 5 ]) ) ? ( true ) : ( false );
				Gang[ gang ].ranks[ slot ].useInvite	= ( atoi(row[ 6 ]) ) ? ( true ) : ( false );
				//-----------------------------------
				strcpy(Gang[ gang ].ranks[ slot ].name, row[ 2 ]);
			}
			mysql_free_result(result);
			//===========================================
			logprintf("[Система банд]: Было загруженно %d банд", count);
			//===========================================
			#ifdef DEBUG_GANG
				for (int i = 0; i < count; i++)
				{
					logprintf("===============[%d]=============", i);
					logprintf("name: %s[%d]", Gang[ i ].name, Gang[ i ].db);
				
					for (int r = 0; r < 5; r++)
					{
						logprintf("Rang[%d]: %s[%d]", r, Gang[ i ].ranks[ r ].name, Gang[ i ].ranks[ r ].db);
					}
				}
			#endif
			//===========================================
		}
		//----------------------------------
		void onDLG(int u, int dialogid, int response, int listitem, const char* inputtext)
		{
			if (dialogid == DLG_GANG_MAKE_INTRO)		// Интро
			{
				if (response)
				{
					enter_Name:
					//--------------------------------------------------
					ShowPlayerDialog
					(
						u, 
						DLG_GANG_MAKE_NAME, 
						GUI_INPUT, 
						language::gang::make_Header_Name,
						language::gang::make_Info_Name,
						language::dialogs::buttons::btnNext, 
						"Отмена"
					);
					//--------------------------------------------------
				}
				else Player[u].isAction = PlayerAction::ACTION_NONE;
			}
			//==========================================================
			else if (dialogid == DLG_GANG_MAKE_NAME)
			{
				if (response)
				{
					Player[u ].memIndex = count; //Присваеваем ид банды
					//--------------------------------------------------
					strcpy(Gang[ count ].name, inputtext);
					//--------------------------------------------------
					enter_Color:
					ShowPlayerDialog
					(
						u, 
						DLG_GANG_MAKE_COLOR,
						GUI_INPUT, 
						language::gang::make_Header_Color,
						language::gang::make_Info_Color,
						language::dialogs::buttons::btnNext,
						language::dialogs::buttons::btnBack
					);
					//--------------------------------------------------
					if (Player[ u ].memIndex == 0)				count++;
				}
				else goto enter_Name;
			}
			//==========================================================
			else if (dialogid == DLG_GANG_MAKE_COLOR)
			{
				if (response)
				{
					Gang[ Player[ u ].memIndex ].color = atoi(inputtext);
					enter_PreProperty:
					//--------------------------------------------------
					ShowPlayerDialog
					(
						u, 
						DLG_GANG_MAKE_PRE_PROPERTY, 
						GUI_MSG, 
						language::gang::make_Header_Safe,
						language::gang::make_Info_Safe,
						language::dialogs::buttons::btnNext,
						language::dialogs::buttons::btnBack
					);
					//--------------------------------------------------
				}
				else goto enter_Color;
			}
			//==========================================================
			else if (dialogid == DLG_GANG_MAKE_PRE_PROPERTY)
			{
				if (response)
				{
					char msg[ 1024 ] = "";
					listProp(u, msg);
					//--------------------------------------------------
					ShowPlayerDialog
					(
						u,
						DLG_GANG_MAKE_PROPERTY,
						GUI_LIST,
						language::gang::make_Header_Safe,
						msg,
						language::dialogs::buttons::btnNext,
						language::dialogs::buttons::btnBack
					);
					//--------------------------------------------------
				}
				else goto enter_PreProperty;
			}
			//==========================================================
			else if (dialogid == DLG_GANG_MAKE_PROPERTY)
			{
				//--------------------------------------------------
				SendClientMessage(u, -1, "[Информация]: Вы успешно основали банду!");
				create(u, listitem);
				//--------------------------------------------------
				showOwner(u);
			}
			//==========================================================
			//------------------Меню лидера банды-----------------------
			else if (dialogid == DLG_GANG_OWNER_MAIN)
			{
				char msg[ 512 ] = "";
				const int idx = Player[ u ].memIndex;
				//--------------------------------------------------
				if (listitem == 0)		//Информация о банде
				{
					char name[ sizeof( language::gang::stat_Name ) ];
					//------------------------------------------------
					char repLS[ sizeof( language::gang::stat_RepLS ) ];
					char repSF[ sizeof( language::gang::stat_RepSF ) ];
					char repLV[ sizeof( language::gang::stat_RepLV ) ];
					//------------------------------------------------
					sprintf(name, language::gang::stat_Name, world::gangs::Gang[ idx ].name);
					sprintf(repLS, language::gang::stat_RepLS, 0, 100);
					sprintf(repSF, language::gang::stat_RepSF, 0, 100);
					sprintf(repLV, language::gang::stat_RepLV, 0, 100);
					//------------------------------------------------
					strcat(msg, name);
					strcat(msg, repLS);
					strcat(msg, repSF);
					strcat(msg, repLV);
					//------------------------------------------------
					ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "Информация о банде", msg, "Закрыть", "");
				}
				//--------------------------------------------------
				else if (listitem == 1)	//Список членов банды
				{

				}
				//--------------------------------------------------
				else if (listitem == 2)	//Управление рангами
				{

				}
				//--------------------------------------------------
				else if (listitem == 3)	//Управление бандой
				{

				}
				//--------------------------------------------------
			}
			//==========================================================
		}

		void showOwner(int u)
		{
			char msg[ 256 ] = "";
			dialogs::genDLGItem(1, "Информация о банде", msg);
			dialogs::genDLGItem(2, "Список членов банды", msg);
			dialogs::genDLGItem(3, "Управление рангами", msg);
			dialogs::genDLGItem(4, "Управление бандой", msg);
			Player[ u ].isAction = PlayerAction::ACTION_GANG_MAKE;
			ShowPlayerDialog(u, DLG_GANG_OWNER_MAIN, GUI_LIST, "[Меню банды] Информация", msg, language::dialogs::buttons::btnNext, "Отмена");
		}
		//----------------------------------
		void showPlayer(int u)
		{

		}
		//----------------------------------
		void create(int u, int listitem)
		{
			const int idx = Player[u].memIndex;			//Ид банды
			Gang[ idx ].owner = Player[ u ].pDB;		//Ид владельца
			Gang[ idx ].prop = Property[ getProp(u, listitem) ].db;
			//-------------------------------------------------------
			Gang[ idx ].rep = 0;
			//-------------------------------------------------------
			sprintf
			(
				query, 
				"INSERT INTO world_Gangs SET owner='%d',color='%d',name='%s',property='%d'", 
				Gang[ idx ].owner,
				Gang[ idx ].color,
				Gang[ idx ].name,
				Gang[ idx ].prop
			),	mysql_query(con, query);
			Gang[ idx ].db = mysql_insert_id(con);
			//-------------------------------------------------------	
			const char names[ 5 ][ 16 ] = { "Соучастник", "Барыга", "Капитан", "Консильери", "Босс" };
			const bool asses[ 5 ][ 4 ] =
			{	//Чат	Тачки  склад  приглос
				{ true, false, false, false },	//Соучастник
				{ true, true, false, false },	//Барыга
				{ true, true, true, true },	//Капитан
				{ true, false, false, true },	//Консильери
				{ true, false, false, true }	//Босс
			};
			//-------------------------------------------------------
			for (int i = 0; i < 5; i++)
			{
				strcpy(Gang[ idx ].ranks[ i ].name, names[ i ]);
				Gang[ idx ].ranks[ i ].useChat = asses[ i ][ 0 ];
				Gang[ idx ].ranks[ i ].useVehs = asses[ i ][ 1 ];
				Gang[ idx ].ranks[ i ].useWares = asses[ i ][ 2 ];
				Gang[ idx ].ranks[ i ].useInvite = asses[ i ][ 3 ];
				//=================================================
				sprintf
				(
					query, 
					"INSERT INTO Gang_Ranks SET gang='%d',name='%s',uchat='%d',uvehs='%d',uwares='%d',uinvite='%d'",
					Gang[ idx ].db, Gang[ idx ].ranks[ i ].name,
					Gang[ idx ].ranks[ i ].useChat,
					Gang[ idx ].ranks[ i ].useVehs,
					Gang[ idx ].ranks[ i ].useWares,
					Gang[ idx ].ranks[ i ].useInvite
				),  mysql_query(con, query);
				//=================================================
				Gang[ idx ].ranks[ i ].db = mysql_insert_id(con);
			}
			//-------------------------------------------------------
		}
		//----------------------------------
		int getProp(int u, int item)
		{
			int l = 0;
			for (int i = 0; i < countProperty; i++)
			{
				if (Property[ i ].owner != Player[ u ].pDB) continue;
				if (Property[ i ].type != 1)				continue;
				if (item == l)								return i;
				l++;
			}
			return 0;
		}
		//----------------------------------
		void listProp(int u, char res[])
		{
			int l = 1;
			char tmp[64] = "";
			for (int i = 0; i < countProperty; i++)
			{
				if (Property[ i ].owner != Player[ u ].pDB) continue;
				if (Property[ i ].type == 1)
				{
					sprintf
					(
						tmp,
						"%s д. %d \t\t [ДОМ]", 
						getSaZoneName(Property[ i ].region),
						Property[i].number
					);
					dialogs::genDLGItem(l, tmp, res);
					l++;
				}
			}

		}
		//----------------------------------
	}

}