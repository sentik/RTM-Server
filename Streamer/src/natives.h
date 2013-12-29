/*
 * Copyright (C) 2012 Incognito
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

#ifndef NATIVES_H
#define NATIVES_H

#define STREAMER_OPC (0)
#define STREAMER_OPDC (1)
#define STREAMER_OPEO (2)
#define STREAMER_OPSO (3)
#define STREAMER_OPPP (4)
#define STREAMER_OPEC (5)
#define STREAMER_OPLC (6)
#define STREAMER_OPERC (7)
#define STREAMER_OPLRC (8)

#include <sampgdk/plugin.h>

//logprintf("*** %s: Expecting %d parameter(s), but found %d", n, m, params[0] / 4);
#define CHECK_PARAMS(m, n) \
	if (params[0] != (m * 4)) \
	{ \
	return 0; \
	}

namespace Natives
{
	cell AMX_NATIVE_CALL Streamer_TickRate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_MaxItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_VisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_CellDistance(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_CellSize(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ProcessActiveItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleIdleUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_ToggleItemUpdate(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_Update(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_UpdateEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetFloatData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetFloatData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetIntData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetIntData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_SetArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsInArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_AppendArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_RemoveArrayData(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetUpperBound(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_GetDistanceToItem(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_IsItemVisible(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_DestroyAllVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL Streamer_CountVisibleItems(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectPos(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectPos(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectRot(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectRot(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL MoveDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL StopDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsDynamicObjectMoving(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachCameraToDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicObjectToVehicle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL EditDynamicObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectMaterial(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectMaterial(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamicObjectMaterialText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL SetDynamicObjectMaterialText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicObjects(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicObjects(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPickup(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicPickup(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicPickup(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicPickups(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicPickups(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerVisibleDynamicCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetPlayerVisibleDynamicRaceCP(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicRaceCPs(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicMapIcon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicMapIcon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicMapIcon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicMapIcons(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicMapIcons(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamic3DTextLabel(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL GetDynamic3DTextLabelText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL UpdateDynamic3DTextLabelText(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamic3DTextLabels(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamic3DTextLabels(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCircle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRectangle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicSphere(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCube(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPolygon(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsValidDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL TogglePlayerAllDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPlayerInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPointInDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL IsPointInAnyDynamicArea(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToObject(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToPlayer(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL AttachDynamicAreaToVehicle(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL DestroyAllDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CountDynamicAreas(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicObjectEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPickupEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCPEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRaceCPEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicMapIconEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamic3DTextLabelEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCircleEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicRectangleEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicSphereEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicCubeEx(AMX *amx, cell *params);
	cell AMX_NATIVE_CALL CreateDynamicPolygonEx(AMX *amx, cell *params);
}

#endif
