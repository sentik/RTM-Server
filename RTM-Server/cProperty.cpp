#include "main.h"

struct sProperty		Property	[ MAX_PROPERTY ] = { { 0, 0 } };
int countProperty;

/// <summary>
/// Сообщение покупки недвижимости
/// <param name="u">* Ид игрока</param>
/// <param name="p">* Ид недвижимости</param>
/// </summary>
void cProperty::buyMessage(const int u, const int p)
{
	char msg[ 336 ];
	sprintf(msg, "{FFFFFF}Здраствуйте, вы действительно хотите приобрести эту недвижимость?\nАдрес: {00C0FF}%s {FFFFFF}д: {00C0FF}%d {FFFFFF}|| Стоимость: {00C0FF}%d{FFFFFF}$",
				 cProperty::getZoneName(Property[p].region), Property[p].number, Property[p].price);
	//===============================================
	Player[ u ].inIndex = p;
	//===============================================
	switch (Property[p].type)
	{
		//------------------------------------------
		case PropertyType::prHouse:		//Дома
		{
									sprintf(msg, "%s\nТип: {00C0FF}Дом", msg);
									break;
		}
		case PropertyType::prBank:		//Банки
		{
									sprintf(msg, "%s\nТип: {00C0FF}Банк", msg);
									break;
		}
		case PropertyType::prGas:		//Заправки
		{
									sprintf(msg, "%s\nТип: {00C0FF}Заправка", msg);
									break;
		}
		case PropertyType::prAutosalon:	//Автосалоны
		{
									sprintf(msg, "%s\nТип: {00C0FF}Автосалон", msg);
									break;
		}
		case PropertyType::prMiner:		//Шахты
		{
									sprintf(msg, "%s\nТип: {00C0FF}Шахта", msg);
									break;
		}
		case PropertyType::prFeller:	//Лесопилки
		{
									sprintf(msg, "%s\nТип: {00C0FF}Лесопилка", msg);
									break;
		}
		//------------------------------------------
	}
	ShowPlayerDialog(u, DLG_PROPERTY_BUY, GUI_MSG, "Покупка недвижимости", msg, "Далее", "Отмена");
}


/// <summary>
/// Сообщение плсле покупки недвижимости
/// <param name="u">* Ид игрока</param>
/// </summary>
void cProperty::beforBuy(const int u)
{
	char msg[ 600 ];
	strcpy(msg, "============================================ \n");
	strcat(msg, "\tПоздравляем вас с покупкой недвижимости.	  \n");
	strcat(msg, "============================================ \n");
	strcat(msg, "Каждые 24 часа вы будете получать квитанции, \n");
	strcat(msg, "которые необходимо своевременно оплатить!    \n");
	strcat(msg, "Квитанции можно оплатить в банке или терминале\n");
	strcat(msg, "============================================  \n");
	strcat(msg, "Более подробно, вы можете узнать на форуме    \n");
	strcat(msg, "Или посмотреть список комманд /mm -> Имущество\n");
	strcat(msg, "============================================  \n");
	strcat(msg, "\tВсего хорошего, желаем приятной игры !");
	ShowPlayerDialog(u, DLG_NONE, GUI_MSG, "[Информация]", msg, "Закрыть", "");
}


/// <summary>
/// Сообщение покупки недвижимости
/// <param name="u">* Ид игрока</param>
/// <param name="p">* Ид недвижимости</param>
/// </summary>
void cProperty::statusMessage(const int u, const int p)
{

}


void cProperty::setOwner(const int p, const int owner)
{
	Property[ p ].owner = owner;
	sprintf(query, "UPDATE class_Property SET owner = '%d' WHERE id = %d", owner, Property[ p ].db);
	mysql_query(con, query); 
}


void cProperty::setStatus(const int p, const int status)
{
	Property[ p ].status = status;
	sprintf(query, "UPDATE class_Property SET status = '%d' WHERE id = %d", status, Property[ p ].db);
	mysql_query(con, query);
}



/// <summary>
/// Действие входа в недвижимость
/// <param name="u">* Ид игрока</param>
/// </summary>
void cProperty::enterProperty(const int u)
{
		for (int i = 0; i < countProperty; i++)
		{
			const int idx = Property[ i ].style;
			//-----------------------------------------------------------------------------------------------
			if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ))
			{
				if (!Property[ i ].owner)
				{
					cProperty::buyMessage(u, i);
					break;
				}
				//-----------------------------------------------------------------------------------------------
				if (Property[ i ].status)
				{
					cProperty::statusMessage(u, i);
					break;
				}
				//-----------------------------------------------------------------------------------------------
				cPlayer::setCharPos(u, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ, true);
				cPlayer::setCharInterior(u, Interior[ idx ].posI);
				cPlayer::setCharAngle(u, Interior[ idx ].posR);
				cPlayer::setCharWorld(u, i);
				//-----------------------------------------------------------------------------------------------
				Player[ u ].inIndex = i;
				break;
			}
			//--------------------------------------------------------------------
		//	if (Player[ u ].pPosW != i) continue;	//Если игрок не в нужном мире
			//--------------------------------------------------------------------
			if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].posX, Interior[ idx ].posY, Interior[ idx ].posZ))
			{
				cPlayer::setCharPos(u, Property[ i ].posX, Property[ i ].posY, Property[ i ].posZ, false);
				cPlayer::setCharInterior(u, 0);
				cPlayer::setCharWorld(u, 0);
				cPlayer::setCharAngle(u, 0);
			}
			//--------------------------------------------------------------------
			else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].actX, Interior[ idx ].actY, Interior[ idx ].actZ))
			{
				cProperty::doAct(u);
			}
			//--------------------------------------------------------------------
			else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, Interior[ idx ].subX, Interior[ idx ].subY, Interior[ idx ].subZ))
			{
				cProperty::doSub(u);
			}
		}

	

}

void cProperty::doAct(int u)
{
	const int idx = Player[ u ].inIndex;
	switch (Property[idx].type)
	{
		//----------------------------------------
		case 2:	//Банк. Хранилише
		{
			cBanks::actStuff(u);
		}
		break;
		//----------------------------------------
	}
}

void cProperty::doSub(int u)
{
	const int idx = Player[ u ].inIndex;
	switch (Property[ idx ].type)
	{
		//----------------------------------------
		case 2:	//Банк. Управление счетом
		{
			cBanks::actBill(u);
		}
		break;
		//----------------------------------------
		case 3:
		{
			Properties::Shops::ShopVehicle::preView(u);
		}
		break;
		//----------------------------------------
	}
}