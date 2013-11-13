#include "main.h"

void cObjects::loadObjects(char name[ ])
{
	char path[ 128 ];
	sprintf(path, "scriptfiles/maps/%s/%s.map", name, name);
	//-----------------------------------
	TiXmlDocument document;
	//-----------------------------------
	document.LoadFile(path);										// ��������� xml
	//-----------------------------------
	TiXmlElement *map = document.FirstChildElement("map");			// ��������� ��������� MAP
	//-----------------------------------
	if (map)
	{
		// ��������� ��������� "<object>" �� ������
		for (TiXmlElement *obj = map->FirstChildElement("object"); obj; obj = obj->NextSiblingElement("object"))
		{
			// �������� ���������
			const int	 model = atoi(obj->Attribute("model"));
			//---------------------------------------------
			const double posX  = atof(obj->Attribute("posX"));
			const double posY  = atof(obj->Attribute("posY"));
			const double posZ  = atof(obj->Attribute("posZ"));
			//---------------------------------------------
			const double rotX = atof(obj->Attribute("rotX"));
			const double rotY = atof(obj->Attribute("rotY"));
			const double rotZ = atof(obj->Attribute("rotZ"));
			//---------------------------------------------
			StreamerCall::Native::CreateDynamicObject(model, posX, posY, posZ, rotX, rotY, rotZ);
		}
		logprintf("[XML Objects]: %s �������� �������", name);
	}
	else logprintf("[XML Objects]: �� ������� ��������� ��������� map ! (%s)", name);
}