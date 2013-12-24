#include "main.h"

struct eMetal Properties::Factory::Metal::Factm[MAX_FACT_M];

void Properties::Factory::Metal::func::load()
{
	int i = 0;
	MYSQL_ROW row;
	safe_query(con, "SELECT class_Property.*, class_FactoryMetal.*, getOwnerName(class_Property.owner) as pname FROM class_Property, class_FactoryMetal  WHERE class_Property.property = class_FactoryMetal.id AND class_Property.type = 8");
	MYSQL_RES *res = mysql_store_result(con);

	while ( row = mysql_fetch_row(res) )
	{
		Property[countProperty].db			= atoi(row[Properties::Factory::Metal::rowsMetal::id]);
		Property[countProperty].bank		= atoi(row[Properties::Factory::Metal::rowsMetal::bank]);
		Property[countProperty].owner		= atoi(row[Properties::Factory::Metal::rowsMetal::owner]);
		Property[countProperty].price		= atoi(row[Properties::Factory::Metal::rowsMetal::price]);
		Property[countProperty].type		= atoi(row[Properties::Factory::Metal::rowsMetal::type]);
		Property[countProperty].posX		= atof(row[Properties::Factory::Metal::rowsMetal::x]);
		Property[countProperty].posY		= atof(row[Properties::Factory::Metal::rowsMetal::y]);
		Property[countProperty].posZ		= atof(row[Properties::Factory::Metal::rowsMetal::z]);
		Property[countProperty].property	= atoi(row[Properties::Factory::Metal::rowsMetal::property]);
		Property[countProperty].region		= atoi(row[Properties::Factory::Metal::rowsMetal::region]);
		Property[countProperty].number		= atoi(row[Properties::Factory::Metal::rowsMetal::number]);
		//--------------------------------------------------------------------------------------------------------------]
		Factm[i].db							= atoi(row[Properties::Factory::Metal::rowsMetal::db]);
		Factm[i].lvl						= atoi(row[Properties::Factory::Metal::rowsMetal::lvl]);
		Factm[i].m1							= atoi(row[Properties::Factory::Metal::rowsMetal::m1]);
		Factm[i].m2							= atoi(row[Properties::Factory::Metal::rowsMetal::m2]);
		Factm[i].m3							= atoi(row[Properties::Factory::Metal::rowsMetal::m3]);
		Factm[i].m4							= atoi(row[Properties::Factory::Metal::rowsMetal::m4]);
		Factm[i].mat						= atoi(row[Properties::Factory::Metal::rowsMetal::mat]);
		Factm[i].cost						= atof(row[Properties::Factory::Metal::rowsMetal::cost]);

		strcpy(Factm[i].name, row[Properties::Factory::Metal::rowsMetal::name]);

		Property[countProperty].link = i;
		//--------------------------------------------------------------
		if ( Property[countProperty].owner )
		{
			strcpy(Property[countProperty].player, row[Properties::Factory::Metal::rowsMetal::pname]);
			sprintf
			(
				query,
				"{FFFFFF}Завод: {B7FF00}%s\n{FFFFFF}Адрес: {B7FF00}%s {FFFFFF}д: {B7FF00}%d\n{FFFFFF}Владелец: {B7FF00}%s",
				Factm[i].name,
				cProperty::getZoneName(Property[countProperty].region),
				Property[countProperty].number,
				Property[countProperty].player
			);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																					 Property[countProperty].posX,
																					 Property[countProperty].posY,
																					 Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		else
		{
			sprintf(query, "{FFFFFF}Завод: {FF0000}%s\n{FFFFFF}Адрес: {FF0000}%s {FFFFFF}д: {FF0000}%d\n{FFFFFF}Стоимость: {FF0000}%d$", Factm[i].name, cProperty::getZoneName(Property[countProperty].region), Property[countProperty].number, Property[countProperty].price);
			//=====================================================================================================
			Property[countProperty].pick = StreamerCall::Native::CreateDynamicPickup(DOLLAR_PICKUP, 23,
																					 Property[countProperty].posX,
																					 Property[countProperty].posY,
																					 Property[countProperty].posZ, 0, 0);
			//=====================================================================================================
		}
		Property[countProperty].text = StreamerCall::Native::CreateDynamic3DTextLabel(query, -1,
																					  Property[countProperty].posX,
																					  Property[countProperty].posY,
																					  Property[countProperty].posZ, 30.0f);
		//-----------------------------------------------------------------------------------------------------------
		countProperty++;
		i++;
	}
	logprintf("[Система Имущества]: \tБыло загруженно заводов(метал) \t- %d", i);
}

void Properties::Factory::Metal::func::save()
{

}