#include "main.h"


struct iInterior extern Interior[ MAX_INTERIORS ] = { { 0, 0 } };
int countInteriors;

/// <summary>
/// Загрузка списка интерьеров
/// </summary>
void cInteriors::loadInterioList()
{
	int i = 0;
	MYSQL_ROW row;
	//------------------------------------------------------------
	mysql_query(con, "SELECT * FROM class_Interiors");
	MYSQL_RES *result = mysql_store_result(con);
	//------------------------------------------------------------	
	while (( row = mysql_fetch_row(result) ))
	{
		char actName[32] = "", subName[32] = "";
		int actPick = 0, subPick = 0;
		//==========================================================================================
		Interior[ i ].db	= atoi(row[ Interiors::InteriorRows::id ]);
		Interior[ i ].Type	= atoi(row[ Interiors::InteriorRows::type ]);
		Interior[ i ].posI	= atoi(row[ Interiors::InteriorRows::posi ]);
		//------------------------------------------------------
		Interior[ i ].posX  = atof(row[ Interiors::InteriorRows::posx ]);
		Interior[ i ].posY  = atof(row[ Interiors::InteriorRows::posy ]);
		Interior[ i ].posZ  = atof(row[ Interiors::InteriorRows::posz ]);
		Interior[ i ].posR  = atof(row[ Interiors::InteriorRows::posr ]);
		//------------------------------------------------------
		Interior[ i ].actX = atof(row[ Interiors::InteriorRows::actx ]);
		Interior[ i ].actY = atof(row[ Interiors::InteriorRows::acty ]);
		Interior[ i ].actZ = atof(row[ Interiors::InteriorRows::actz ]);
		//------------------------------------------------------
		Interior[ i ].subX = atof(row[ Interiors::InteriorRows::subx ]);
		Interior[ i ].subY = atof(row[ Interiors::InteriorRows::suby ]);
		Interior[ i ].subZ = atof(row[ Interiors::InteriorRows::subz ]);
		//------------------------------------------------------
		Interior[i].pick   = StreamerCall::Native::CreateDynamicPickup(EXIT_PICKUP, 23, 
																	   Interior[ i ].posX, 
																	   Interior[ i ].posY, 
																	   Interior[ i ].posZ);
		//------------------------------------------------------
		Interior[ i ].text = StreamerCall::Native::CreateDynamic3DTextLabel("Выход\nНажмите [ALT]", -1,
																		Interior[ i ].posX,
																		Interior[ i ].posY,
																		Interior[ i ].posZ, 10.0f);
		//==========================================================================================
		switch (Interior[ i ].Type)
		{
			//-----------------------------------------------------
			case 1:	//Дом
			{
				//======================================== 
				strcpy(actName, "Чердак\nНажмите [ALT]");
				actPick = EXIT_PICKUP;
				//======================================== 
				strcpy(subName, "Гардероб\nНажмите [ALT]");
				subPick = CLOTH_PICKUP;
				//======================================== 
			}
			break;
			//-----------------------------------------------------
			case 2:	//Банк
			{
				//======================================== 
				strcpy(actName, "Хранилище\nНажмите [ALT]");
				actPick = EXIT_PICKUP;
				//======================================== 
				strcpy(subName, "Управление счетом\nНажмите [ALT]");
				subPick = INFO_PICKUP;
				//======================================== 
			}
			break;
			//-----------------------------------------------------
			case 3:	//Автосалон
			{
				strcpy(subName, "Каталог\nНажмите [ALT]");
				subPick = INFO_PICKUP;
			}
			break;
			//-----------------------------------------------------
			case 4:
			{

			}
			break;
			//-----------------------------------------------------
		}
		//==========================================================================================
		if (actPick)
		{
			Interior[ i ].actP = StreamerCall::Native::CreateDynamicPickup(actPick, 23,
																		   Interior[ i ].actX,
																		   Interior[ i ].actY,
																		   Interior[ i ].actZ);
			//------------------------------------------------------
			Interior[ i ].actT = StreamerCall::Native::CreateDynamic3DTextLabel(actName, -1,
																				Interior[ i ].actX,
																				Interior[ i ].actY,
																				Interior[ i ].actZ, 10.0f);
		}
		//==========================================================================================
		if (subPick)
		{

			Interior[ i ].subP = StreamerCall::Native::CreateDynamicPickup(subPick, 23,
																		   Interior[ i ].subX,
																		   Interior[ i ].subY,
																		   Interior[ i ].subZ);
			//------------------------------------------------------
			Interior[ i ].subT = StreamerCall::Native::CreateDynamic3DTextLabel(subName, -1,
																				Interior[ i ].subX,
																				Interior[ i ].subY,
																				Interior[ i ].subZ, 10.0f);
		}
		//==========================================================================================
		i++;
	}
	logprintf("[Система имущества]: \tБыло загруженно %d интерьеров", i);
	countInteriors = i;
}

