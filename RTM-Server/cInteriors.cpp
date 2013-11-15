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
		//------------------------------------------------------
		i++;
	}
	logprintf("[Система имущества]: \tБыло загруженно %d интерьеров", i);
	countInteriors = i;
}

