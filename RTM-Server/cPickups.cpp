#include "main.h"

std::vector<ePickups> world::pickups::cPickups::Pickups;

void world::pickups::cPickups::loadPickups()
{
	MYSQL_ROW row;
	MYSQL_RES *result;
	//--------------------------------------------------------------------------------------
	safe_query(con, "SELECT * FROM class_Pickups ORDER BY id");
	result = mysql_store_result(con);
	while (row = mysql_fetch_row(result))
	{
		ePickups tmp;
		tmp.db = atoi(row[rowsPick::id]);
		tmp.eModel = atoi(row[rowsPick::model_1]);
		tmp.qModel = atoi(row[rowsPick::model_2]);
		strcpy(tmp.eText, row[rowsPick::text_1]);
		strcpy(tmp.qText, row[rowsPick::text_2]);
		tmp.eX = atof(row[rowsPick::x]);
		tmp.qX = atof(row[rowsPick::ex]);
		tmp.eY = atof(row[rowsPick::y]);
		tmp.qY = atof(row[rowsPick::ey]);
		tmp.eZ = atof(row[rowsPick::z]);
		tmp.qZ = atof(row[rowsPick::ez]);
		tmp.eI = atoi(row[rowsPick::int_1]);
		tmp.qI = atoi(row[rowsPick::int_2]);
		tmp.eW = atoi(row[rowsPick::world_1]);
		tmp.qW = atoi(row[rowsPick::world_2]);
		//--------------------------------------------------------------------------------------
		sprintf(query, "%s\nֽאזלטעו [ALT]", tmp.eText);
		StreamerCall::Native::CreateDynamic3DTextLabel(query, -1, tmp.eX, tmp.eY, tmp.eZ, 20.0f, 65535, 65535, true, tmp.eW, tmp.eI);
		StreamerCall::Native::CreateDynamicPickup(tmp.eModel, 23, tmp.eX, tmp.eY, tmp.eZ, tmp.eW, tmp.eI);
		//--------------------------------------------------------------------------------------
		if (tmp.qModel)
		{
			sprintf(query, "%s\nֽאזלטעו [ALT]", tmp.qText);
			StreamerCall::Native::CreateDynamic3DTextLabel(query, -1, tmp.qX, tmp.qY, tmp.qZ, 20.0f, 65535, 65535, true, tmp.qW, tmp.qI);
			StreamerCall::Native::CreateDynamicPickup(tmp.qModel, 23, tmp.qX, tmp.qY, tmp.qZ, tmp.qW, tmp.qI);
		}
		//--------------------------------------------------------------------------------------
		Pickups.insert(Pickups.end(), tmp);
	}
	mysql_free_result(result);
}

void world::pickups::cPickups::actionPickups(const int u)
{
	for (auto id = Pickups.begin(); id != Pickups.end(); id++)
	{
		if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, id->eX, id->eY, id->eZ))
		{
			cPlayer::setCharPos(u, id->qX, id->qY, id->qZ, true);
			cPlayer::setCharWorld(u, id->qW);
			cPlayer::setCharInterior(u, id->qI);
			break;
		}
		else if (cPlayer::isRangeOfPoint(u, ENTER_RADIUS, id->qX, id->qY, id->qZ) && id->qModel)
		{
			cPlayer::setCharPos(u, id->eX, id->eY, id->eZ, true);
			cPlayer::setCharWorld(u, id->eW);
			cPlayer::setCharInterior(u, id->eI);
			break;
		}
	}
}