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

#include "natives.h"

#include "core.h"
#include "main.h"
#include "utility.h"

#include <boost/chrono.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/a_objects.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/plugin.h>

#include <bitset>
#include <limits>
#include <string>

#include "../streamerlib.h"

namespace StreamerCall
{
	namespace Native
	{
		bool TickRate(int tickrate)
		{
			if (!core->getStreamer()->setTickRate(tickrate))
				return false;
			return true;
		}
		bool MaxItems(int type, size_t value)
		{
			if (!core->getData()->setMaxItems(type, value))
				return false;
			return true;
		}
		bool VisibleItems(int type, size_t value)
		{
			if (!core->getStreamer()->setVisibleItems(type, value))
				return false;
			return true;
		}
		void CellDistance(float celldistance)
		{
			core->getGrid()->cellDistance = celldistance * celldistance;
			core->getGrid()->rebuildGrid();
		}
		void CellSize(float cellsize)
		{
			core->getGrid()->cellSize = cellsize;
			core->getGrid()->rebuildGrid();
		}
		void ProcessActiveItems()
		{
			core->getStreamer()->processActiveItems();
		}
		bool ToggleIdleUpdate(int playerid, int update)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.updateWhenIdle = update != 0;
				return true;
			}
			return false;
		}
		bool ToggleItemUpdate(int playerid, int type, int update)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (type >= 0 && type < STREAMER_MAX_TYPES)
				{
					p->second.enabledItems.set(type, update != 0);
					return true;
				}
			}
			return false;
		}
		bool Update(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				core->getStreamer()->startManualUpdate(p->second, true);
				return true;
			}
			return false;
		}
		bool UpdateEx(int playerid, float x, float y, float z, int worldid, int interiorid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.position = Eigen::Vector3f(x,y,z);
				if (worldid >= 0)
				{
					p->second.worldID = worldid;
				}
				else
				{
					p->second.worldID = GetPlayerVirtualWorld(p->first);
				}
				if (interiorid >= 0)
				{
					p->second.interiorID = interiorid;
				}
				else
				{
					p->second.interiorID = GetPlayerInterior(p->first);
				}
				core->getStreamer()->startManualUpdate(p->second, false);
				return 1;
			}
			return 0;
		}
		/*int Streamer_GetFloatData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_GetFloatData");
			return static_cast<cell>(Manipulation::getFloatData(amx, params));
		}

		int Streamer_SetFloatData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_SetFloatData");
			return static_cast<cell>(Manipulation::setFloatData(amx, params));
		}

		int Streamer_GetIntData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(3, "Streamer_GetIntData");
			return static_cast<cell>(Manipulation::getIntData(amx, params));
		}

		int Streamer_SetIntData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_SetIntData");
			return static_cast<cell>(Manipulation::setIntData(amx, params));
		}

		int Streamer_GetArrayData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(5, "Streamer_GetArrayData");
			return static_cast<cell>(Manipulation::getArrayData(amx, params));
		}

		int Streamer_SetArrayData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(5, "Streamer_SetArrayData");
			return static_cast<cell>(Manipulation::setArrayData(amx, params));
		}


		int Streamer_IsInArrayData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_IsInArrayData");
			return static_cast<cell>(Manipulation::isInArrayData(amx, params));
		}

		int Streamer_AppendArrayData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_AppendArrayData");
			return static_cast<cell>(Manipulation::appendArrayData(amx, params));
		}

		int Streamer_RemoveArrayData(AMX *amx, cell *params)
		{
			CHECK_PARAMS(4, "Streamer_RemoveArrayData");
			return static_cast<cell>(Manipulation::removeArrayData(amx, params));
		}

		int Streamer_GetUpperBound(AMX *amx, cell *params)
		{
			CHECK_PARAMS(1, "Streamer_GetUpperBound");
			switch (static_cast<int>(params[1]))
			{
				case STREAMER_TYPE_OBJECT:
				{
					int objectID = 0;
					for (boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.begin(); o != core->getData()->objects.end(); ++o)
					{
						if (o->first > objectID)
						{
							objectID = o->first;
						}
					}
					return static_cast<cell>(objectID + 1);
				}
				case STREAMER_TYPE_PICKUP:
				{
					int pickupID = 0;
					for (boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.begin(); p != core->getData()->pickups.end(); ++p)
					{
						if (p->first > pickupID)
						{
							pickupID = p->first;
						}
					}
					return static_cast<cell>(pickupID + 1);
				}
				case STREAMER_TYPE_CP:
				{
					int checkpointID = 0;
					for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
					{
						if (c->first > checkpointID)
						{
							checkpointID = c->first;
						}
					}
					return static_cast<cell>(checkpointID + 1);
				}
				case STREAMER_TYPE_RACE_CP:
				{
					int raceCheckpointID = 0;
					for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
					{
						if (r->first > raceCheckpointID)
						{
							raceCheckpointID = r->first;
						}
					}
					return static_cast<cell>(raceCheckpointID + 1);
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					int mapIconID = 0;
					for (boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.begin(); m != core->getData()->mapIcons.end(); ++m)
					{
						if (m->first > mapIconID)
						{
							mapIconID = m->first;
						}
					}
					return static_cast<cell>(mapIconID + 1);
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					int textLabelID = 0;
					for (boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.begin(); t != core->getData()->textLabels.end(); ++t)
					{
						if (t->first > textLabelID)
						{
							textLabelID = t->first;
						}
					}
					return static_cast<cell>(textLabelID + 1);
				}
				case STREAMER_TYPE_AREA:
				{
					int areaID = 0;
					for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
					{
						if (a->first > areaID)
						{
							areaID = a->first;
						}
					}
					return static_cast<cell>(areaID + 1);
				}
				default:
				{
					//logprintf("*** Streamer_GetUpperBound: Invalid type specified");
					return 0;
				}
			}
			return 0;
		}
		*/
		float GetDistanceToItem(float x,float y, float z, int type, int identifierid)
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(identifierid);
					if (o != core->getData()->objects.end())
						return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), o->second->position));
					return 0.0f;
				}
				case STREAMER_TYPE_PICKUP:
				{
					boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(identifierid);
					if (p != core->getData()->pickups.end())
						return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), p->second->position));
					return 0.0f;
				}
				case STREAMER_TYPE_CP:
				{
					boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(identifierid);
					if (c != core->getData()->checkpoints.end())
						return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), c->second->position));
					return 0.0f;
				}
				case STREAMER_TYPE_RACE_CP:
				{
					boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(identifierid);
					if (r != core->getData()->raceCheckpoints.end())
						return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), r->second->position));
					return 0.0f;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(identifierid);
					if (m != core->getData()->mapIcons.end())
						return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), m->second->position));
					return 0.0f;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(identifierid);
					if (t != core->getData()->textLabels.end())
					{
						if (t->second->attach)
							return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), t->second->attach->position));
						else
							return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), t->second->position));
					}
					return 0.0f;
				}
				case STREAMER_TYPE_AREA:
				{
					boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(identifierid);
					if (a != core->getData()->areas.end())
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							{
								if (a->second->attach)
								{
									return static_cast<float>(boost::geometry::distance(Eigen::Vector2f(x,y), Eigen::Vector2f(a->second->attach->position[0], a->second->attach->position[1])));
								}
								else
								{
									return static_cast<float>(boost::geometry::distance(Eigen::Vector2f(x,y), boost::get<Eigen::Vector2f>(a->second->position)));
								}
							}
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Box2D>(a->second->position));
								return static_cast<float>(boost::geometry::distance(Eigen::Vector2f(x, y), centroid));
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								if (a->second->attach)
								{
									return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), a->second->attach->position));
								}
								else
								{
									return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), boost::get<Eigen::Vector3f>(a->second->position)));
								}
							}
							case STREAMER_AREA_TYPE_CUBE:
							{
								Eigen::Vector3f centroid = boost::geometry::return_centroid<Eigen::Vector3f>(boost::get<Box3D>(a->second->position));
								return static_cast<float>(boost::geometry::distance(Eigen::Vector3f(x,y,z), centroid));
							}
							case STREAMER_AREA_TYPE_POLYGON:
							{
								if (z >= boost::get<Polygon2D>(a->second->position).get<1>()[0] && z <= boost::get<Polygon2D>(a->second->position).get<1>()[1])
								{
									Eigen::Vector2f centroid = boost::geometry::return_centroid<Eigen::Vector2f>(boost::get<Polygon2D>(a->second->position).get<0>());
									return static_cast<float>(boost::geometry::distance(Eigen::Vector2f(x,y), centroid));
								}
								return 0.0f;
							}
						}
					}
					return 0.0f;
				}
				default:
				{
					//logprintf("*** Streamer_GetDistanceToItem: Invalid type specified");
					return 0.0f;
				}
			}
			return 0.0f;
		}
	/*
		int Streamer_IsItemVisible(AMX *amx, cell *params)
		{
			CHECK_PARAMS(3, "Streamer_IsItemVisible");
			if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
			{
				boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(static_cast<int>(params[3]));
				if (i != core->getStreamer()->internalPickups.end())
				{
					return 1;
				}
				return 0;
			}
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
			if (p != core->getData()->players.end())
			{
				switch (static_cast<int>(params[2]))
				{
					case STREAMER_TYPE_OBJECT:
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[3]));
						if (i != p->second.internalObjects.end())
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_CP:
					{
						if (p->second.visibleCheckpoint == static_cast<int>(params[3]))
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_RACE_CP:
					{
						if (p->second.visibleRaceCheckpoint == static_cast<int>(params[3]))
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_MAP_ICON:
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(static_cast<int>(params[3]));
						if (i != p->second.internalMapIcons.end())
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_3D_TEXT_LABEL:
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(static_cast<int>(params[3]));
						if (i != p->second.internalTextLabels.end())
						{
							return 1;
						}
					}
					case STREAMER_TYPE_AREA:
					{
						boost::unordered_set<int>::iterator i = p->second.internalAreas.find(static_cast<int>(params[3]));
						if (i != p->second.internalAreas.end())
						{
							return 1;
						}
						return 0;
					}
					default:
					{
						//logprintf("*** Streamer_IsItemVisible: Invalid type specified");
						return 0;
					}
				}
			}
			return 0;
		}

		int Streamer_DestroyAllVisibleItems(AMX *amx, cell *params)
		{
			CHECK_PARAMS(2, "Streamer_DestroyAllVisibleItems");
			if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
			{
				for (boost::unordered_map<int, int>::iterator q = core->getStreamer()->internalPickups.begin(); q != core->getStreamer()->internalPickups.end(); ++q)
				{
					DestroyPickup(q->second);
				}
				core->getStreamer()->internalPickups.clear();
				return 1;
			}
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
			if (p != core->getData()->players.end())
			{
				switch (static_cast<int>(params[2]))
				{
					case STREAMER_TYPE_OBJECT:
					{
						for (boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin(); o != p->second.internalObjects.end(); ++o)
						{
							DestroyPlayerObject(p->first, o->second);
						}
						p->second.internalObjects.clear();
						return 1;
					}
					case STREAMER_TYPE_CP:
					{
						if (p->second.visibleCheckpoint)
						{
							DisablePlayerCheckpoint(p->first);
							p->second.activeCheckpoint = 0;
							p->second.visibleCheckpoint = 0;
						}
						return 1;
					}
					case STREAMER_TYPE_RACE_CP:
					{
						if (p->second.visibleRaceCheckpoint)
						{
							DisablePlayerRaceCheckpoint(p->first);
							p->second.activeRaceCheckpoint = 0;
							p->second.visibleRaceCheckpoint = 0;
						}
						return 1;
					}
					case STREAMER_TYPE_MAP_ICON:
					{
						for (boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin(); m != p->second.internalMapIcons.end(); ++m)
						{
							RemovePlayerMapIcon(p->first, m->second);
						}
						p->second.internalMapIcons.clear();
						return 1;
					}
					case STREAMER_TYPE_3D_TEXT_LABEL:
					{
						for (boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin(); t != p->second.internalTextLabels.end(); ++t)
						{
							DeletePlayer3DTextLabel(p->first, t->second);
						}
						p->second.internalTextLabels.clear();
						return 1;
					}
					case STREAMER_TYPE_AREA:
					{
						p->second.internalAreas.clear();
						return 1;
					}
					default:
					{
						//logprintf("*** Streamer_DestroyAllVisibleItems: Invalid type specified");
						return 0;
					}
				}
			}
			return 0;
		}

		int Streamer_CountVisibleItems(AMX *amx, cell *params)
		{
			CHECK_PARAMS(2, "Streamer_CountVisibleItems");
			if (static_cast<int>(params[2]) == STREAMER_TYPE_PICKUP)
			{
				return static_cast<cell>(core->getStreamer()->internalPickups.size());
			}
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
			if (p != core->getData()->players.end())
			{
				switch (static_cast<int>(params[2]))
				{
					case STREAMER_TYPE_OBJECT:
					{
						return static_cast<cell>(p->second.internalObjects.size());
					}
					case STREAMER_TYPE_CP:
					{
						if (p->second.visibleCheckpoint)
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_RACE_CP:
					{
						if (p->second.visibleRaceCheckpoint)
						{
							return 1;
						}
						return 0;
					}
					case STREAMER_TYPE_MAP_ICON:
					{
						return static_cast<cell>(p->second.internalMapIcons.size());
					}
					case STREAMER_TYPE_3D_TEXT_LABEL:
					{
						return static_cast<cell>(p->second.internalTextLabels.size());
					}
					case STREAMER_TYPE_AREA:
					{
						return static_cast<cell>(p->second.internalAreas.size());
					}
					default:
					{
						//logprintf("*** Streamer_CountVisibleItems: Invalid type specified");
						return 0;
					}
				}
			}
			return 0;
		}
		*/
		int CreateDynamicObject(int modelid,float x, float y, float z, float rx, float ry, float rz, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
			{
				return 0;
			}
			int objectID = Item::Object::identifier.get();
			Item::SharedObject object(new Item::Object);
			object->amx = NULL;
			object->drawDistance = 0.0f;
			object->extraID = 0;
			object->objectID = objectID;
			object->modelID = modelid;
			object->position = Eigen::Vector3f(x,y,z);
			object->rotation = Eigen::Vector3f(rx,ry,rz);
			Utility::addToContainer(object->worlds, worldid);
			Utility::addToContainer(object->interiors, interiorid);
			Utility::addToContainer(object->players, playerid);
			object->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addObject(object);
			core->getData()->objects.insert(std::make_pair(objectID, object));
			return objectID;
		}
		bool DestroyDynamicObject(int objectid)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				Utility::destroyObject(o);
				return true;
			}
			return false;
		}
		bool IsValidDynamicObject(int objectid)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				return true;
			}
			return false;
		}
		bool SetDynamicObjectPos(int objectid, float x, float y, float z)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				Eigen::Vector3f position = o->second->position;
				o->second->position = Eigen::Vector3f(x,y,z);
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						SetPlayerObjectPos(p->first, i->second, o->second->position[0], o->second->position[1], o->second->position[2]);
					}
				}
				if (position[0] != o->second->position[0] || position[1] != o->second->position[1])
				{
					if (o->second->cell)
					{
						core->getGrid()->removeObject(o->second, true);
					}
				}
				if (o->second->move)
				{
					o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(o->second->move->position.get<0>(), o->second->position) / o->second->move->speed) * 1000.0f));
					o->second->move->position.get<1>() = o->second->position;
					o->second->move->position.get<2>() = (o->second->move->position.get<0>() - o->second->position) / static_cast<float>(o->second->move->duration);
					if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
					{
						o->second->move->rotation.get<1>() = o->second->rotation;
						o->second->move->rotation.get<2>() = (o->second->move->rotation.get<0>() - o->second->rotation) / static_cast<float>(o->second->move->duration);
					}
					o->second->move->time = boost::chrono::steady_clock::now();
				}
				return true;
			}
			return false;
		}
		bool GetDynamicObjectPos(int objectid, float &x, float &y, float &z)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					core->getStreamer()->processActiveItems();
				}
				x = o->second->position[0];
				y = o->second->position[1];
				z = o->second->position[2];
				return true;
			}
			return false;
		}
		bool SetDynamicObjectRot(int objectid, float rx, float ry, float rz)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					return false;
				}
				o->second->rotation = Eigen::Vector3f(rz,ry,rz);
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						SetPlayerObjectRot(p->first, i->second, o->second->rotation[0], o->second->rotation[1], o->second->rotation[2]);
					}
				}
				return true;
			}
			return false;
		}
		bool GetDynamicObjectRot(int objectid, float &rx, float &ry, float &rz)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					core->getStreamer()->processActiveItems();
				}
				rx = o->second->rotation[0];
				ry = o->second->rotation[1];
				rz = o->second->rotation[2];
				return true;
			}
			return false;
		}
		int MoveDynamicObject(int objectid, float x, float y, float z, float speed, float rx, float ry, float rz)
		{
			if (!speed)
			{
				return 0;
			}
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->attach)
				{
					//logprintf("MoveDynamicObject: Object is currently attached and cannot be moved");
					return 0;
				}
				Eigen::Vector3f position(x,y,z);
				Eigen::Vector3f rotation(rx,ry,rz);
				o->second->move = boost::intrusive_ptr<Item::Object::Move>(new Item::Object::Move);
				o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(position, o->second->position) / speed) * 1000.0f));
				o->second->move->position.get<0>() = position;
				o->second->move->position.get<1>() = o->second->position;
				o->second->move->position.get<2>() = (position - o->second->position) / static_cast<float>(o->second->move->duration);
				o->second->move->rotation.get<0>() = rotation;
				if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
				{
					o->second->move->rotation.get<1>() = o->second->rotation;
					o->second->move->rotation.get<2>() = (rotation - o->second->rotation) / static_cast<float>(o->second->move->duration);
				}
				o->second->move->speed = speed;
				o->second->move->time = boost::chrono::steady_clock::now();
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						StopPlayerObject(p->first, i->second);
						MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
					}
				}
				core->getStreamer()->movingObjects.insert(o->second);
				return o->second->move->duration;
			}
			return 0;
		}

		bool StopDynamicObject(int objectid)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							StopPlayerObject(p->first, i->second);
						}
					}
					o->second->move.reset();
					core->getStreamer()->movingObjects.erase(o->second);
					return true;
				}
			}
			return true;
		}

		bool IsDynamicObjectMoving(int objectid)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					return true;
				}
			}
			return false;
		}

		bool AttachCameraToDynamicObject(int playerid, int objectid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(objectid);
				if (i != p->second.internalObjects.end())
				{
					AttachCameraToPlayerObject(p->first, i->second);
					return true;
				}
			}
			return false;
		}

		bool AttachDynamicObjectToVehicle(int objectid, int vehicleid, float offsetx, float offsety, float offsetz, float rx, float ry, float rz)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				if (o->second->move)
				{
					//logprintf("AttachDynamicObjectToVehicle: Object is currently moving and cannot be attached");
					return false;
				}
				o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
				o->second->attach->vehicle = vehicleid;
				o->second->attach->offset = Eigen::Vector3f(offsetx,offsety,offsetz);
				o->second->attach->rotation = Eigen::Vector3f(rx,ry,rz);
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
						for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
						{
							if (m->second.main)
							{
								SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
							}
							else if (m->second.text)
							{
								SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
							}
						}
					}
				}
				if (vehicleid != INVALID_GENERIC_ID)
				{
					core->getStreamer()->attachedObjects.insert(o->second);
				}
				else
				{
					o->second->attach.reset();
					core->getStreamer()->attachedObjects.erase(o->second);
					core->getGrid()->removeObject(o->second, true);
				}
				return true;
			}
			return false;
		}

		bool EditDynamicObject(int objectid, int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(objectid);
			if (p != core->getData()->players.end())
			{
				core->getStreamer()->startManualUpdate(p->second, true);
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(playerid);
				if (i != p->second.internalObjects.end())
				{
					EditPlayerObject(p->first, i->second);
					return true;
				}
			}
			return false;
		}

		bool GetDynamicObjectMaterial(int objectid, int index, ObjectMaterial &data)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(index);
				if (m != o->second->materials.end())
				{
					if (m->second.main)
					{
						data.materialColor = m->second.main->materialColor;
						data.modelID = m->second.main->modelID;
						data.textureName.assign(m->second.main->textureName);
						data.txdFileName.assign(m->second.main->txdFileName);
						return true;
					}
				}
			}
			return false;
		}

		bool SetDynamicObjectMaterial(int objectid, int index, ObjectMaterial &data)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				o->second->materials[index].main = boost::intrusive_ptr<Item::Object::Material::Main>(new Item::Object::Material::Main);
				o->second->materials[index].main->modelID = data.modelID;
				o->second->materials[index].main->txdFileName.assign(data.txdFileName);
				o->second->materials[index].main->textureName.assign(data.textureName);
				o->second->materials[index].main->materialColor = data.materialColor;
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						SetPlayerObjectMaterial(p->first, i->second, index, o->second->materials[index].main->modelID, o->second->materials[index].main->txdFileName.c_str(), o->second->materials[index].main->textureName.c_str(), o->second->materials[index].main->materialColor);
					}
				}
				o->second->materials[index].text.reset();
				return true;
			}
			return false;
		}

		bool GetDynamicObjectMaterialText(int objectid, int index, ObjectText &data)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(index);
				if (m != o->second->materials.end())
				{
					if (m->second.text)
					{
						data.materialText.assign(m->second.text->materialText);
						data.materialSize= m->second.text->materialSize;
						data.fontFace.assign(m->second.text->fontFace);
						data.fontSize = m->second.text->fontSize;
						data.bold = m->second.text->bold;
						data.fontColor = m->second.text->fontColor;
						data.backColor = m->second.text->backColor;
						data.textAlignment = m->second.text->textAlignment;
						return true;
					}
				}
			}
			return false;
		}

		bool SetDynamicObjectMaterialText(int objectid, int index, ObjectText &data)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(objectid);
			if (o != core->getData()->objects.end())
			{
				o->second->materials[index].text = boost::intrusive_ptr<Item::Object::Material::Text>(new Item::Object::Material::Text);
				o->second->materials[index].text->materialText.assign(data.materialText);
				o->second->materials[index].text->materialSize = data.materialSize;
				o->second->materials[index].text->fontFace.assign(data.fontFace);
				o->second->materials[index].text->fontSize = data.fontSize;
				o->second->materials[index].text->bold = data.bold;
				o->second->materials[index].text->fontColor = data.fontColor;
				o->second->materials[index].text->backColor = data.backColor;
				o->second->materials[index].text->textAlignment = data.textAlignment;
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
					if (i != p->second.internalObjects.end())
					{
						SetPlayerObjectMaterialText(p->first, i->second, o->second->materials[index].text->materialText.c_str(), index, o->second->materials[index].text->materialSize, o->second->materials[index].text->fontFace.c_str(), o->second->materials[index].text->fontSize, o->second->materials[index].text->bold, o->second->materials[index].text->fontColor, o->second->materials[index].text->backColor, o->second->materials[index].text->textAlignment);
					}
				}
				o->second->materials[index].main.reset();
				return true;
			}
			return false;
		}

		void DestroyAllDynamicObjects()
		{
			Item::Object::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				for (boost::unordered_map<int, int>::iterator o = p->second.internalObjects.begin(); o != p->second.internalObjects.end(); ++o)
				{
					DestroyPlayerObject(p->first, o->second);
				}
				p->second.internalObjects.clear();
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_OBJECT);
			core->getStreamer()->attachedObjects.clear();
			core->getStreamer()->movingObjects.clear();
			core->getData()->objects.clear();
		}

		int CountDynamicObjects()
		{
			return core->getData()->objects.size();
		}

		int CreateDynamicPickup(int modelID, int type, float x, float y, float z, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
			{
				return 0;
			}
			int pickupID = Item::Pickup::identifier.get();
			Item::SharedPickup pickup(new Item::Pickup);
			pickup->amx = 0;
			pickup->extraID = 0;
			pickup->pickupID = pickupID;
			pickup->worldID = 0;
			pickup->modelID = modelID;
			pickup->type = type;
			pickup->position = Eigen::Vector3f(x,y,z);
			Utility::addToContainer(pickup->worlds, worldid);
			Utility::addToContainer(pickup->interiors, interiorid);
			Utility::addToContainer(pickup->players, playerid);
			pickup->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addPickup(pickup);
			core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
			return pickupID;
		}

		bool DestroyDynamicPickup(int pickupid)
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(pickupid);
			if (p != core->getData()->pickups.end())
			{
				Utility::destroyPickup(p);
				return true;
			}
			return false;
		}

		bool IsValidDynamicPickup(int pickupid)
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(pickupid);
			if (p != core->getData()->pickups.end())
				return true;
			return false;
		}

		void DestroyAllDynamicPickups()
		{
			Item::Pickup::identifier.reset();
			for (boost::unordered_map<int, int>::iterator p = core->getStreamer()->internalPickups.begin(); p != core->getStreamer()->internalPickups.end(); ++p)
			{
				DestroyPickup(p->second);
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_PICKUP);
			core->getStreamer()->internalPickups.clear();
			core->getData()->pickups.clear();
		}

		int CountDynamicPickups()
		{
			return core->getData()->pickups.size();
		}

		int CreateDynamicCP(float x, float y, float z, float size, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
			{
				return 0;
			}
			int checkpointID = Item::Checkpoint::identifier.get();
			Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
			checkpoint->amx = 0;
			checkpoint->checkpointID = checkpointID;
			checkpoint->extraID = 0;
			checkpoint->position = Eigen::Vector3f(x,y,z);
			checkpoint->size = size;
			Utility::addToContainer(checkpoint->worlds, worldid);
			Utility::addToContainer(checkpoint->interiors, interiorid);
			Utility::addToContainer(checkpoint->players, playerid);
			checkpoint->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addCheckpoint(checkpoint);
			core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
			return checkpointID;
		}

		bool DestroyDynamicCP(int checkpointid)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(checkpointid);
			if (c != core->getData()->checkpoints.end())
			{
				Utility::destroyCheckpoint(c);
				return true;
			}
			return false;
		}

		bool IsValidDynamicCP(int checkpointid)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(checkpointid);
			if (c != core->getData()->checkpoints.end())
				return true;
			return false;
		}

		bool TogglePlayerDynamicCP(int playerid, int checkpointid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				boost::unordered_set<int>::iterator d = p->second.disabledCheckpoints.find(checkpointid);
				if (toggle)
				{
					if (d != p->second.disabledCheckpoints.end())
					{
						p->second.disabledCheckpoints.quick_erase(d);
						return true;
					}
				}
				else
				{
					if (d == p->second.disabledCheckpoints.end())
					{
						if (p->second.visibleCheckpoint == checkpointid)
						{
							DisablePlayerCheckpoint(p->first);
							p->second.activeCheckpoint = 0;
							p->second.visibleCheckpoint = 0;
						}
						p->second.disabledCheckpoints.insert(checkpointid);
						return true;
					}
				}
			}
			return false;
		}

		bool TogglePlayerAllDynamicCPs(int playerid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.disabledCheckpoints.clear();
				if (!toggle)
				{
					if (p->second.visibleCheckpoint != 0)
					{
						DisablePlayerCheckpoint(p->first);
						p->second.activeCheckpoint = 0;
						p->second.visibleCheckpoint = 0;
					}
					for (boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.begin(); c != core->getData()->checkpoints.end(); ++c)
					{
						p->second.disabledCheckpoints.insert(c->first);
					}
				}
				return true;
			}
			return false;
		}

		bool IsPlayerInDynamicCP(int playerid, int checkpointid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeCheckpoint == checkpointid)
					return true;
			}
			return false;
		}

		int GetPlayerVisibleDynamicCP(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
				return p->second.visibleCheckpoint;
			return 0;
		}

		void DestroyAllDynamicCPs()
		{
			Item::Checkpoint::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				p->second.disabledCheckpoints.clear();
				if (p->second.visibleCheckpoint != 0)
				{
					DisablePlayerCheckpoint(p->first);
					p->second.activeCheckpoint = 0;
					p->second.visibleCheckpoint = 0;
				}
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_CP);
			core->getData()->checkpoints.clear();
		}

		int CountDynamicCPs()
		{
			return core->getData()->checkpoints.size();
		}

		int CreateDynamicRaceCP(int type, float x, float y, float z, float nextx, float nexty, float nextz, float size, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
			{
				return 0;
			}
			int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
			Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
			raceCheckpoint->amx = 0;
			raceCheckpoint->extraID = 0;
			raceCheckpoint->raceCheckpointID = raceCheckpointID;
			raceCheckpoint->type = type;
			raceCheckpoint->position = Eigen::Vector3f(x,y,z);
			raceCheckpoint->next = Eigen::Vector3f(nextx,nexty,nextz);
			raceCheckpoint->size = size;
			Utility::addToContainer(raceCheckpoint->worlds, worldid);
			Utility::addToContainer(raceCheckpoint->interiors, interiorid);
			Utility::addToContainer(raceCheckpoint->players, playerid);
			raceCheckpoint->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addRaceCheckpoint(raceCheckpoint);
			core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
			return raceCheckpointID;
		}

		bool DestroyDynamicRaceCP(int checkpointid)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(checkpointid);
			if (r != core->getData()->raceCheckpoints.end())
			{
				Utility::destroyRaceCheckpoint(r);
				return true;
			}
			return false;
		}

		bool IsValidDynamicRaceCP(int checkpointid)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(checkpointid);
			if (r != core->getData()->raceCheckpoints.end())
				return true;
			return false;
		}

		bool TogglePlayerDynamicRaceCP(int playerid, int checkpointid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				boost::unordered_set<int>::iterator d = p->second.disabledRaceCheckpoints.find(checkpointid);
				if (toggle)
				{
					if (d != p->second.disabledRaceCheckpoints.end())
					{
						p->second.disabledRaceCheckpoints.quick_erase(d);
						return true;
					}
				}
				else
				{
					if (d == p->second.disabledRaceCheckpoints.end())
					{
						if (p->second.visibleRaceCheckpoint == checkpointid)
						{
							DisablePlayerRaceCheckpoint(p->first);
							p->second.activeRaceCheckpoint = 0;
							p->second.visibleRaceCheckpoint = 0;
						}
						p->second.disabledRaceCheckpoints.insert(checkpointid);
						return true;
					}
				}
			}
			return false;
		}

		bool TogglePlayerAllDynamicRaceCPs(int playerid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.disabledRaceCheckpoints.clear();
				if (!toggle)
				{
					if (p->second.visibleRaceCheckpoint != 0)
					{
						DisablePlayerRaceCheckpoint(p->first);
						p->second.activeRaceCheckpoint = 0;
						p->second.visibleRaceCheckpoint = 0;
					}
					for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.begin(); r != core->getData()->raceCheckpoints.end(); ++r)
					{
						p->second.disabledRaceCheckpoints.insert(r->first);
					}
				}
				return true;
			}
			return false;
		}

		bool IsPlayerInDynamicRaceCP(int playerid, int checkpointid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeRaceCheckpoint == checkpointid)
				{
					return true;
				}
			}
			return false;
		}

		int GetPlayerVisibleDynamicRaceCP(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
				return p->second.visibleRaceCheckpoint;
			return 0;
		}

		void DestroyAllDynamicRaceCPs()
		{
			Item::RaceCheckpoint::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				p->second.disabledRaceCheckpoints.clear();
				if (p->second.visibleRaceCheckpoint != 0)
				{
					DisablePlayerRaceCheckpoint(p->first);
					p->second.activeRaceCheckpoint = 0;
					p->second.visibleRaceCheckpoint = 0;
				}
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_RACE_CP);
			core->getData()->raceCheckpoints.clear();
		}

		int CountDynamicRaceCPs()
		{
			return core->getData()->raceCheckpoints.size();
		}

		int CreateDynamicMapIcon(float x, float y, float z, int type, int color, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
			{
				return 0;
			}
			int mapIconID = Item::MapIcon::identifier.get();
			Item::SharedMapIcon mapIcon(new Item::MapIcon);
			mapIcon->amx = 0;
			mapIcon->extraID = 0;
			mapIcon->mapIconID = mapIconID;
			mapIcon->style = 0;
			mapIcon->position = Eigen::Vector3f(x,y,z);
			mapIcon->type = type;
			mapIcon->color = color;
			Utility::addToContainer(mapIcon->worlds, worldid);
			Utility::addToContainer(mapIcon->interiors, interiorid);
			Utility::addToContainer(mapIcon->players, playerid);
			mapIcon->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addMapIcon(mapIcon);
			core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
			return mapIconID;
		}

		bool DestroyDynamicMapIcon(int iconid)
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(iconid);
			if (m != core->getData()->mapIcons.end())
			{
				Utility::destroyMapIcon(m);
				return true;
			}
			return false;
		}

		bool IsValidDynamicMapIcon(int iconid)
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(iconid);
			if (m != core->getData()->mapIcons.end())
				return true;
			return false;
		}

		void DestroyAllDynamicMapIcons()
		{
			Item::MapIcon::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				for (boost::unordered_map<int, int>::iterator m = p->second.internalMapIcons.begin(); m != p->second.internalMapIcons.end(); ++m)
				{
					RemovePlayerMapIcon(p->first, m->second);
				}
				p->second.mapIconIdentifier.reset();
				p->second.internalMapIcons.clear();
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_MAP_ICON);
			core->getData()->mapIcons.clear();
		}

		int CountDynamicMapIcons()
		{
			return core->getData()->mapIcons.size();
		}

		int CreateDynamic3DTextLabel(std::string text, int color, float x, float y, float z, float drawdistance, int AttachPlayerID, int AttachVehicleID, bool testLOS, int worldid, int interiorid, int playerid, float streamdistance)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
			{
				return 0;
			}
			int textLabelID = Item::TextLabel::identifier.get();
			Item::SharedTextLabel textLabel(new Item::TextLabel);
			textLabel->amx = 0;
			textLabel->extraID = 0;
			textLabel->textLabelID = textLabelID;
			textLabel->text.assign(text);
			textLabel->color = color;
			textLabel->position = Eigen::Vector3f(x,y,z);
			textLabel->drawDistance = drawdistance;
			if (AttachPlayerID != INVALID_GENERIC_ID || AttachVehicleID != INVALID_GENERIC_ID)
			{
				textLabel->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
				textLabel->attach->player = AttachPlayerID;
				textLabel->attach->vehicle = AttachVehicleID;
				if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
				{
					textLabel->position.setZero();
				}
				core->getStreamer()->attachedTextLabels.insert(textLabel);
			}
			textLabel->testLOS = testLOS;
			Utility::addToContainer(textLabel->worlds, worldid);
			Utility::addToContainer(textLabel->interiors, interiorid);
			Utility::addToContainer(textLabel->players, playerid);
			textLabel->streamDistance = streamdistance * streamdistance;
			core->getGrid()->addTextLabel(textLabel);
			core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
			return textLabelID;
		}

		bool DestroyDynamic3DTextLabel(int labelid)
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(labelid);
			if (t != core->getData()->textLabels.end())
			{
				Utility::destroyTextLabel(t);
				return true;
			}
			return false;
		}

		bool IsValidDynamic3DTextLabel(int labelid)
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(labelid);
			if (t != core->getData()->textLabels.end())
				return true;
			return false;
		}

		bool GetDynamic3DTextLabelText(int labelid, std::string &out)
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(labelid);
			if (t != core->getData()->textLabels.end())
			{
				out.assign(t->second->text);
				return true;
			}
			return false;
		}

		bool UpdateDynamic3DTextLabelText(int labelid,int color, std::string text)
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(labelid);
			if (t != core->getData()->textLabels.end())
			{
				t->second->color = color;
				t->second->text.assign(text);
				for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
					if (i != p->second.internalTextLabels.end())
					{
						UpdatePlayer3DTextLabelText(p->first, i->second, t->second->color, t->second->text.c_str());
					}
				}
				return true;
			}
			return false;
		}

		void DestroyAllDynamic3DTextLabels()
		{
			Item::TextLabel::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				for (boost::unordered_map<int, int>::iterator t = p->second.internalTextLabels.begin(); t != p->second.internalTextLabels.end(); ++t)
				{
					DeletePlayer3DTextLabel(p->first, t->second);
				}
				p->second.internalTextLabels.clear();
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_3D_TEXT_LABEL);
			core->getStreamer()->attachedTextLabels.clear();
			core->getData()->textLabels.clear();
		}

		int CountDynamic3DTextLabels()
		{
			return core->getData()->textLabels.size();
		}

		int CreateDynamicCircle(float x, float y, float size, int worldid, int interiorid, int playerid)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
			{
				return 0;
			}
			int areaID = Item::Area::identifier.get();
			Item::SharedArea area(new Item::Area);
			area->amx = 0;
			area->areaID = areaID;
			area->extraID = 0;
			area->type = STREAMER_AREA_TYPE_CIRCLE;
			area->position = Eigen::Vector2f(x,y);
			area->size = size * size;
			Utility::addToContainer(area->worlds, worldid);
			Utility::addToContainer(area->interiors, interiorid);
			Utility::addToContainer(area->players, playerid);
			core->getGrid()->addArea(area);
			core->getData()->areas.insert(std::make_pair(areaID, area));
			return areaID;
		}

		int CreateDynamicRectangle(float x1, float y1, float x2, float y2, int worldid, int interiorid, int playerid)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
			{
				return 0;
			}
			int areaID = Item::Area::identifier.get();
			Item::SharedArea area(new Item::Area);
			area->amx = 0;
			area->areaID = areaID;
			area->extraID = 0;
			area->type = STREAMER_AREA_TYPE_RECTANGLE;
			area->position = Box2D(Eigen::Vector2f(x1,y1), Eigen::Vector2f(x2,y2));
			boost::geometry::correct(boost::get<Box2D>(area->position));
			area->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
			Utility::addToContainer(area->worlds, worldid);
			Utility::addToContainer(area->interiors, interiorid);
			Utility::addToContainer(area->players, playerid);
			core->getGrid()->addArea(area);
			core->getData()->areas.insert(std::make_pair(areaID, area));
			return areaID;
		}

		int CreateDynamicSphere(float x, float y, float z, float size, int worldid, int interiorid, int playerid)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
			{
				return 0;
			}
			int areaID = Item::Area::identifier.get();
			Item::SharedArea area(new Item::Area);
			area->amx = 0;
			area->areaID = areaID;
			area->extraID = 0;
			area->type = STREAMER_AREA_TYPE_SPHERE;
			area->position = Eigen::Vector3f(x,y,z);
			area->size = size * size;
			Utility::addToContainer(area->worlds, worldid);
			Utility::addToContainer(area->interiors, interiorid);
			Utility::addToContainer(area->players, playerid);
			core->getGrid()->addArea(area);
			core->getData()->areas.insert(std::make_pair(areaID, area));
			return areaID;
		}

		int CreateDynamicCube(float x1, float y1, float z1, float x2, float y2, float z2, int worldid, int interiorid, int playerid)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
			{
				return 0;
			}
			int areaID = Item::Area::identifier.get();
			Item::SharedArea area(new Item::Area);
			area->amx = 0;
			area->areaID = areaID;
			area->extraID = 0;
			area->type = STREAMER_AREA_TYPE_CUBE;
			area->position = Box3D(Eigen::Vector3f(x1,y1,z1), Eigen::Vector3f(x2,y2,z2));
			boost::geometry::correct(boost::get<Box3D>(area->position));
			area->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
			Utility::addToContainer(area->worlds, worldid);
			Utility::addToContainer(area->interiors, interiorid);
			Utility::addToContainer(area->players, playerid);
			core->getGrid()->addArea(area);
			core->getData()->areas.insert(std::make_pair(areaID, area));
			return areaID;
		}

		int CreateDynamicPolygon(float polygon[], float minz, float maxz, int worldid, int interiorid, int playerid)
		{
			if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
			{
				return 0;
			}
			if (sizeof(polygon) >= 2 && sizeof(polygon) % 2)
			{
				//logprintf("*** CreateDynamicPolygon: Number of points must be divisible by two");
				return 0;
			}
			int areaID = Item::Area::identifier.get();
			Item::SharedArea area(new Item::Area);
			area->amx = 0;
			area->areaID = areaID;
			area->extraID = 0;
			area->type = STREAMER_AREA_TYPE_POLYGON;
			std::vector<Eigen::Vector2f> points;
			for (std::size_t i = 0; i < static_cast<std::size_t>(sizeof(polygon)); i += 2)
			{
				points.push_back(Eigen::Vector2f(polygon[i], polygon[i + 1]));
			}
			boost::geometry::assign_points(boost::get<Polygon2D>(area->position).get<0>(), points);
			boost::geometry::correct(boost::get<Polygon2D>(area->position).get<0>());

			Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position).get<0>());
			area->size = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
			boost::get<Polygon2D>(area->position).get<1>() = Eigen::Vector2f(minz,maxz);
			Utility::addToContainer(area->worlds, worldid);
			Utility::addToContainer(area->interiors, interiorid);
			Utility::addToContainer(area->players, playerid);
			core->getGrid()->addArea(area);
			core->getData()->areas.insert(std::make_pair(areaID, area));
			return areaID;
		}

		bool DestroyDynamicArea(int areaid)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				Utility::destroyArea(a);
				return true;
			}
			return false;
		}

		bool IsValidDynamicArea(int areaid)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				return true;
			}
			return false;
		}

		bool TogglePlayerDynamicArea(int playerid, int areaid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				boost::unordered_set<int>::iterator d = p->second.disabledAreas.find(areaid);
				if (toggle)
				{
					if (d != p->second.disabledAreas.end())
					{
						p->second.disabledAreas.quick_erase(d);
						return true;
					}
				}
				else
				{
					if (d == p->second.disabledAreas.end())
					{
						p->second.disabledAreas.insert(areaid);
						p->second.internalAreas.erase(areaid);
						return true;
					}
				}
			}
			return false;
		}

		bool TogglePlayerAllDynamicAreas(int playerid, bool toggle)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				p->second.disabledAreas.clear();
				if (!toggle)
				{
					for (boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
					{
						p->second.disabledAreas.insert(a->first);
					}
					p->second.internalAreas.clear();
				}
				return true;
			}
			return false;
		}

		bool IsPlayerInDynamicArea(int playerid, int areaid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				boost::unordered_set<int>::iterator i = p->second.internalAreas.find(areaid);
				if (i != p->second.internalAreas.end())
				{
					return true;
				}
			}
			return false;
		}

		bool IsPlayerInAnyDynamicArea(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (!p->second.internalAreas.empty())
				{
					return true;
				}
			}
			return false;
		}

		bool IsPointInDynamicArea(int areaid, float x, float y, float z)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				return Utility::isPointInArea(Eigen::Vector3f(x,y,z), a->second);
			}
			return false;
		}

		bool IsPointInAnyDynamicArea(float x, float y, float z)
		{
			for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = core->getData()->areas.begin(); a != core->getData()->areas.end(); ++a)
			{
				if (Utility::isPointInArea(Eigen::Vector3f(x,y,z), a->second))
				{
					return true;
				}
			}
			return false;
		}

		bool AttachDynamicAreaToObject(int areaid, int objectid, int type, int playerid)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
				{
					//logprintf("*** AttachDynamicAreaToObject: Only circles and spheres may be attached to objects");
					return false;
				}
				if (objectid != INVALID_GENERIC_ID)
				{
					a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
					a->second->attach->object = boost::make_tuple(objectid, type, playerid);
					a->second->attach->player = INVALID_GENERIC_ID;
					a->second->attach->vehicle = INVALID_GENERIC_ID;
					core->getStreamer()->attachedAreas.insert(a->second);
				}
				else
				{
					if (a->second->attach)
					{
						if (a->second->attach->object.get<0>() != INVALID_GENERIC_ID)
						{
							a->second->attach.reset();
							core->getStreamer()->attachedAreas.erase(a->second);
							core->getGrid()->removeArea(a->second, true);
						}
					}
				}
				return true;
			}
			return false;
		}

		bool AttachDynamicAreaToPlayer(int areaid, int playerid)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
				{
					//logprintf("*** AttachDynamicAreaToPlayer: Only circles and spheres may be attached to players");
					return false;
				}
				if (playerid != INVALID_GENERIC_ID)
				{
					a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
					a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
					a->second->attach->player = playerid;
					a->second->attach->vehicle = INVALID_GENERIC_ID;
					core->getStreamer()->attachedAreas.insert(a->second);
				}
				else
				{
					if (a->second->attach)
					{
						if (a->second->attach->player != INVALID_GENERIC_ID)
						{
							a->second->attach.reset();
							core->getStreamer()->attachedAreas.erase(a->second);
							core->getGrid()->removeArea(a->second, true);
						}
					}
				}
				return true;
			}
			return false;
		}

		bool AttachDynamicAreaToVehicle(int areaid, int vehicleid)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(areaid);
			if (a != core->getData()->areas.end())
			{
				if (a->second->type != STREAMER_AREA_TYPE_CIRCLE && a->second->type != STREAMER_AREA_TYPE_SPHERE)
				{
					//logprintf("*** AttachDynamicAreaToVehicle: Only circles and spheres may be attached to vehicles");
					return false;
				}
				if (vehicleid != INVALID_GENERIC_ID)
				{
					a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
					a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
					a->second->attach->player = INVALID_GENERIC_ID;
					a->second->attach->vehicle = vehicleid;
					core->getStreamer()->attachedAreas.insert(a->second);
				}
				else
				{
					if (a->second->attach)
					{
						if (a->second->attach->vehicle != INVALID_GENERIC_ID)
						{
							a->second->attach.reset();
							core->getStreamer()->attachedAreas.erase(a->second);
							core->getGrid()->removeArea(a->second, true);
						}
					}
				}
				return true;
			}
			return false;
		}

		void DestroyAllDynamicAreas()
		{
			Item::Area::identifier.reset();
			for (boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				p->second.disabledAreas.clear();
				p->second.internalAreas.clear();
			}
			core->getGrid()->removeAllItems(STREAMER_TYPE_AREA);
			core->getStreamer()->attachedAreas.clear();
			core->getData()->areas.clear();
		}

		int CountDynamicAreas()
		{
			return core->getData()->areas.size();
		}
	};
};