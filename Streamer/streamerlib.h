/*Created by Gamer_Z For Streamer Plugin by Ingocnito to be used with SampGDK
 *
 * Copyright (C) 2012 Gamer_Z
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#pragma once
#include <string>

#define STREAMER_TYPE_OBJECT (0)
#define STREAMER_TYPE_PICKUP (1)
#define STREAMER_TYPE_CP (2)
#define STREAMER_TYPE_RACE_CP (3)
#define STREAMER_TYPE_MAP_ICON (4)
#define STREAMER_TYPE_3D_TEXT_LABEL (5)
#define STREAMER_TYPE_AREA (6)

#define STREAMER_AREA_TYPE_CIRCLE (0)
#define STREAMER_AREA_TYPE_RECTANGLE (1)
#define STREAMER_AREA_TYPE_SPHERE (2)
#define STREAMER_AREA_TYPE_CUBE (3)
#define STREAMER_AREA_TYPE_POLYGON (4)

#define STREAMER_OBJECT_TYPE_GLOBAL (0)
#define STREAMER_OBJECT_TYPE_PLAYER (1)
#define STREAMER_OBJECT_TYPE_DYNAMIC (2)

namespace StreamerCall
{
	#define VALUE_NEG_RECENT (-1)//(0xFFFF made the streamer not work? What the hell?)
	bool OnPlayerEditDynamicObject(int playerid, int objectid, int response, float x, float y, float z, float rx, float ry, float rz);
	bool OnPlayerSelectDynamicObject(int playerid,int objectid,int modelid, float x, float y, float z);
	bool OnPlayerPickUpDynamicPickup(int playerid,int pickupid);
	bool OnPlayerEnterDynamicCP(int playerid,int checkpointid);
	bool OnPlayerLeaveDynamicCP(int playerid,int checkpointid);
	bool OnPlayerEnterDynamicRaceCP(int playerid,int checkpointid);
	bool OnPlayerLeaveDynamicRaceCP(int playerid,int checkpointid);
	bool OnPlayerEnterDynamicArea(int playerid, int areaid);
	bool OnPlayerLeaveDynamicArea(int playerid, int areaid);
	bool OnDynamicObjectMoved(int objectid);
	bool Load();
	void Unload();
	void Tick(); 
	namespace Events
	{
		bool OnPlayerConnect(int playerid);
		bool OnPlayerDisconnect(int playerid, int reason);
		bool OnPlayerEditObject(int playerid, int playerobject, int objectid, int response, float x, float y, float z, float rx, float ry, float rz);
		bool OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z);
		bool OnPlayerPickUpPickup(int playerid, int pickupid);
		bool OnPlayerEnterCheckpoint(int playerid);
		bool OnPlayerLeaveCheckpoint(int playerid);
		bool OnPlayerEnterRaceCheckpoint(int playerid);
		bool OnPlayerLeaveRaceCheckpoint(int playerid);
	};
	namespace Native
	{
		struct ObjectMaterial
		{
			int materialColor;
			int modelID;
			std::string textureName;
			std::string txdFileName;
			ObjectMaterial(){}
			ObjectMaterial(int &materialColor, int &modelID, std::string &textureName, std::string&txdFileName)
				: materialColor(materialColor),modelID(modelID),textureName(textureName), txdFileName(txdFileName){}
			~ObjectMaterial(){}
		};
		struct ObjectText
		{
			ObjectText(){}
			~ObjectText(){}
			ObjectText(int &backColor, bool &bold,int &fontColor,std::string &fontFace,int &fontSize,int &materialSize,std::string &materialText,int &textAlignment)
				: backColor(backColor), bold(bold),fontColor(fontColor),fontFace(fontFace),fontSize(fontSize),materialSize(materialSize),materialText(materialText),textAlignment(textAlignment){}
			int backColor;
			bool bold;
			int fontColor;
			std::string fontFace;
			int fontSize;
			int materialSize;
			std::string materialText;
			int textAlignment;
		};

		bool TickRate(int tickrate = 30);
		bool MaxItems(int type, size_t value);
		bool VisibleItems(int type, size_t value);
		void CellDistance(float celldistance);
		void CellSize(float cellsize);
		void ProcessActiveItems();
		bool ToggleIdleUpdate(int playerid, int update);
		bool ToggleItemUpdate(int playerid, int type, int update);
		bool Update(int playerid);
		bool UpdateEx(int playerid, float x, float y, float z, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT);
		float GetDistanceToItem(float x,float y, float z, int type, int identifierid);
		int CreateDynamicObject(int modelid,float x, float y, float z, float rx, float ry, float rz, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamicObject(int objectid);
		bool IsValidDynamicObject(int objectid);
		bool SetDynamicObjectPos(int objectid, float x, float y, float z);
		bool GetDynamicObjectPos(int objectid, float &x, float &y, float &z);
		bool SetDynamicObjectRot(int objectid, float rx, float ry, float rz);
		bool GetDynamicObjectRot(int objectid, float &rx, float &ry, float &rz);
		int MoveDynamicObject(int objectid, float x, float y, float z, float speed, float rx = -1000.0f, float ry = -1000.0f, float rz = -1000.0f);
		bool StopDynamicObject(int objectid);
		bool IsDynamicObjectMoving(int objectid);
		bool AttachCameraToDynamicObject(int playerid, int objectid);
		bool AttachDynamicObjectToVehicle(int objectid, int vehicleid, float offsetx, float offsety, float offsetz, float rx, float ry, float rz);
		bool EditDynamicObject(int objectid, int playerid);
		bool GetDynamicObjectMaterial(int objectid, int index, ObjectMaterial &data);
		bool SetDynamicObjectMaterial(int objectid, int index, ObjectMaterial &data);
		bool GetDynamicObjectMaterialText(int objectid, int index, ObjectText &data);
		bool SetDynamicObjectMaterialText(int objectid, int index, ObjectText &data);
		void DestroyAllDynamicObjects();
		int CountDynamicObjects();
		int CreateDynamicPickup(int modelID, int type, float x, float y, float z, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamicPickup(int pickupid);
		bool IsValidDynamicPickup(int pickupid);
		void DestroyAllDynamicPickups();
		int CountDynamicPickups();
		int CreateDynamicCP(float x, float y, float z, float size, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamicCP(int checkpointid);
		bool IsValidDynamicCP(int checkpointid);
		bool TogglePlayerDynamicCP(int playerid, int checkpointid, bool toggle);
		bool TogglePlayerAllDynamicCPs(int playerid, bool toggle);
		bool IsPlayerInDynamicCP(int playerid, int checkpointid);
		int GetPlayerVisibleDynamicCP(int playerid);
		void DestroyAllDynamicCPs();
		int CountDynamicCPs();
		int CreateDynamicRaceCP(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamicRaceCP(int checkpointid);
		bool IsValidDynamicRaceCP(int checkpointid);
		bool TogglePlayerDynamicRaceCP(int playerid, int checkpointid, bool toggle);
		bool TogglePlayerAllDynamicRaceCPs(int playerid, bool toggle);
		bool IsPlayerInDynamicRaceCP(int playerid, int checkpointid);
		int GetPlayerVisibleDynamicRaceCP(int playerid);
		void DestroyAllDynamicRaceCPs();
		int CountDynamicRaceCPs();
		int CreateDynamicMapIcon(float x, float y, float z, int type, int color, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamicMapIcon(int iconid);
		bool IsValidDynamicMapIcon(int iconid);
		void DestroyAllDynamicMapIcons();
		int CountDynamicMapIcons();
		int CreateDynamic3DTextLabel(std::string text, int color, float x, float y, float z, float drawdistance, int AttachPlayerID = VALUE_NEG_RECENT, int AttachVehicleID = VALUE_NEG_RECENT, bool testLOS = true, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT, float streamdistance = 300.0f);
		bool DestroyDynamic3DTextLabel(int labelid);
		bool IsValidDynamic3DTextLabel(int labelid);
		bool GetDynamic3DTextLabelText(int labelid, std::string &out);
		bool UpdateDynamic3DTextLabelText(int labelid,int color, std::string text);
		void DestroyAllDynamic3DTextLabels();
		int CountDynamic3DTextLabels();
		int CreateDynamicCircle(float x, float y, float size, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT);
		int CreateDynamicRectangle(float x1, float y1, float x2, float y2, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT);
		int CreateDynamicSphere(float x, float y, float z, float size, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT);
		int CreateDynamicCube(float x1, float y1, float z1, float x2, float y2, float z2, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT);	
		int CreateDynamicPolygon(float polygon[], float minz = (float)-0x7F800000, float maxz = (float)0x7F800000, int worldid = VALUE_NEG_RECENT, int interiorid = VALUE_NEG_RECENT, int playerid = VALUE_NEG_RECENT);
		bool DestroyDynamicArea(int areaid);
		bool IsValidDynamicArea(int areaid);
		bool TogglePlayerDynamicArea(int playerid, int areaid, bool toggle);
		bool TogglePlayerAllDynamicAreas(int playerid, bool toggle);
		bool IsPlayerInDynamicArea(int playerid, int areaid);
		bool IsPlayerInAnyDynamicArea(int playerid);
		bool IsPointInDynamicArea(int areaid, float x, float y, float z);
		bool IsPointInAnyDynamicArea(float x, float y, float z);
		void DestroyAllDynamicAreas();
		int CountDynamicAreas();
		bool AttachDynamicAreaToObject(int areaid, int objectid, int type = STREAMER_OBJECT_TYPE_DYNAMIC, int playerid = VALUE_NEG_RECENT);
		bool AttachDynamicAreaToPlayer(int areaid, int playerid);
		bool AttachDynamicAreaToVehicle(int areaid, int vehicleid);
	};
};