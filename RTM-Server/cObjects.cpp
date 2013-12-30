#include "main.h"
#include <tinyxml/tinyxml.h>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

void cObjects::loadObjects()
{
	char path[ 128 ];
	sprintf(path, "%s\\scriptfiles\\maps", bfs::current_path().string());
	for (bfs::recursive_directory_iterator rdib(path), rdie; rdib != rdie; ++rdib)
	{
		char tmp[ 128 ];
		sprintf(tmp, "%s\\%s", path, rdib->path().filename().string().c_str());
		//logprintf(tmp);
		//-----------------------------------
		TiXmlDocument document;
		//-----------------------------------
		document.LoadFile(tmp);											// Загружаем xml
		//-----------------------------------
		TiXmlElement *map = document.FirstChildElement("map");			// Загружаем категорию MAP
		//-----------------------------------
		if (map)//dimension
		{
			// Загружаем категорию "<object>" по этапно
			for (TiXmlElement *obj = map->FirstChildElement("object"); obj; obj = obj->NextSiblingElement("object"))
			{
				// Получаем аргументы
				//---------------------------------------------
				const int	model = atoi(obj->Attribute("model"));
				int			posI = atoi(obj->Attribute("interior"));
				int			posW = atoi(obj->Attribute("dimension"));
				//---------------------------------------------
				const float	posX = atof(obj->Attribute("posX"));
				const float	posY = atof(obj->Attribute("posY"));
				const float	posZ = atof(obj->Attribute("posZ"));
				//---------------------------------------------
				const float	rotX = atof(obj->Attribute("rotX"));
				const float	rotY = atof(obj->Attribute("rotY"));
				const float	rotZ = atof(obj->Attribute("rotZ"));
				//---------------------------------------------
				if (posI == 0) posI = -1;
				if (posW == 0) posW = -1;
				StreamerCall::Native::CreateDynamicObject(model, posX, posY, posZ, rotX, rotY, rotZ, posW, posI);
			}
			logprintf("[XML Objects]: %s загружен успешно", rdib->path().filename().string().c_str());
		}
		else logprintf("[XML Objects]: Не удалось загрузить категорию map ! (%s)", rdib->path().filename().string().c_str());
	}
}

void cObjects::removeObjects(const int playerid)
{
	//waxta
	RemoveBuildingForPlayer(playerid, 18400, -1835.9297, -1647.6797, 26.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 18499, -1849.5156, -1701.1563, 32.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 18555, -1813.8047, -1615.5625, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18556, -1907.6172, -1666.6797, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18557, -1857.2969, -1617.9766, 26.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 18560, -1874.3438, -1680.9531, 25.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 18255, -1939.9141, -1731.4844, 24.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 18251, -1907.6172, -1666.6797, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18252, -1888.9766, -1633.2734, 24.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 18253, -1888.8047, -1604.1328, 23.3750, 0.25);
	RemoveBuildingForPlayer(playerid, 18247, -1874.3438, -1680.9531, 25.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 18245, -1849.5156, -1701.1563, 32.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 18248, -1852.2578, -1676.2188, 28.6172, 0.25);
	RemoveBuildingForPlayer(playerid, 18249, -1818.8125, -1675.5391, 27.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 18246, -1857.8359, -1573.3750, 23.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 18250, -1857.2969, -1617.9766, 26.8125, 0.25);
	RemoveBuildingForPlayer(playerid, 18364, -1835.9297, -1647.6797, 26.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 18254, -1813.8047, -1615.5625, 29.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 18608, -1818.4531, -1613.0391, 32.7891, 0.25);
	//waxta 2
	RemoveBuildingForPlayer(playerid, 16574, -430.3984, 2215.6563, 25.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 3361, -476.1406, 2194.5469, 42.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 3406, -480.4219, 2191.6797, 38.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 3406, -480.4219, 2182.8750, 38.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 3425, -466.4297, 2190.2734, 55.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 16051, -386.4297, 2208.4063, 44.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 16170, -430.3984, 2215.6563, 25.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 16637, -389.5938, 2227.9141, 42.9219, 0.25);
	RemoveBuildingForPlayer(playerid, 16054, -427.7734, 2238.2578, 44.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 3350, -429.0547, 2237.8359, 41.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 3276, -449.7656, 2237.7422, 42.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 16052, -338.7891, 2218.2969, 43.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 16629, -337.9141, 2215.2266, 42.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 16630, -341.4531, 2225.5000, 42.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 16635, -339.6875, 2221.1250, 42.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 16636, -340.1250, 2228.1250, 42.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 16690, -358.9375, 2217.6953, 46.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 16628, -331.1172, 2211.4844, 42.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 16631, -335.5234, 2229.6094, 42.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 16634, -336.2969, 2211.5078, 41.9688, 0.25);
	RemoveBuildingForPlayer(playerid, 16410, -327.4922, 2218.4844, 43.3203, 0.25);
	RemoveBuildingForPlayer(playerid, 16627, -322.8984, 2214.8203, 44.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 16632, -329.7969, 2231.6875, 42.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 16633, -327.2656, 2213.0625, 43.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 3276, -454.2109, 2258.0234, 45.2734, 0.25);
	RemoveBuildingForPlayer(playerid, 3276, -454.1094, 2246.6094, 42.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 3276, -455.9766, 2268.2891, 48.6875, 0.25);
	RemoveBuildingForPlayer(playerid, 16053, -400.4453, 2242.2344, 45.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 16689, -367.8281, 2248.8750, 44.4063, 0.25);
	//sprunks
	RemoveBuildingForPlayer(playerid, 1302, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1209, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 955, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1755, 0.0, 0.0, 0.0, 6000.0);
	RemoveBuildingForPlayer(playerid, 1776, 0.0, 0.0, 0.0, 6000.0);
	//lesopilka
	RemoveBuildingForPlayer(playerid, 785, -387.3672, -97.3594, 43.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 785, -449.9375, 10.8359, 46.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 791, -387.3672, -97.3594, 43.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 694, -439.1875, -19.9375, 58.0938, 0.25);
	RemoveBuildingForPlayer(playerid, 791, -449.9375, 10.8359, 46.5391, 0.25);
}