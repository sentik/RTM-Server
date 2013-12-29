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

#include "../streamerlib.h"

#include "core.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/unordered_map.hpp>

#include <sampgdk/a_samp.h>
#include <sampgdk/plugin.h>

#include <set>

namespace StreamerCall
{
	namespace Events
	{
		bool OnPlayerConnect(int playerid)
		{
			if (playerid >= 0 && playerid < MAX_PLAYERS)
			{
				boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
				if (p == core->getData()->players.end())
				{
					streamerPlayer player(playerid);
					core->getData()->players.insert(std::make_pair(playerid, player));
				}
			}
			return true;
		}

		bool OnPlayerDisconnect(int playerid, int reason)
		{
			core->getData()->players.erase(playerid);
			return true;
		}

		bool OnPlayerEditObject(int playerid, int playerobject, int objectid, int response, float x, float y, float z, float rx, float ry, float rz)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
				{
					if (i->second == objectid)
					{
						return StreamerCall::OnPlayerEditDynamicObject(playerid,i->first,response,x,y,z,rx,ry,rz);
					}
				}
			}
			return true;
		}

		bool OnPlayerSelectObject(int playerid, int type, int objectid, int modelid, float x, float y, float z)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				for (boost::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
				{
					if (i->second == objectid)
					{
						return StreamerCall::OnPlayerSelectDynamicObject(playerid,i->first,modelid,x,y,z);
					}
				}
			}
			return true;
		}

		bool OnPlayerPickUpPickup(int playerid, int pickupid)
		{
			for (boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.begin(); i != core->getStreamer()->internalPickups.end(); ++i)
			{
				if (i->second == pickupid)
				{
					return StreamerCall::OnPlayerPickUpDynamicPickup(playerid,i->first);	
				}
			}
			return true;
		}

		bool OnPlayerEnterCheckpoint(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeCheckpoint != p->second.visibleCheckpoint)
				{
					p->second.activeCheckpoint = p->second.visibleCheckpoint;
					return StreamerCall::OnPlayerEnterDynamicCP(playerid,p->second.visibleCheckpoint);
				}
			}
			return true;
		}

		bool OnPlayerLeaveCheckpoint(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeCheckpoint == p->second.visibleCheckpoint)
				{
					p->second.activeCheckpoint = 0;
					return StreamerCall::OnPlayerLeaveDynamicCP(playerid,p->second.activeCheckpoint);
				}
			}
			return true;
		}

		bool OnPlayerEnterRaceCheckpoint(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeRaceCheckpoint != p->second.visibleRaceCheckpoint)
				{
					p->second.activeRaceCheckpoint = p->second.visibleRaceCheckpoint;
					return StreamerCall::OnPlayerEnterDynamicRaceCP(playerid,p->second.visibleRaceCheckpoint);
				}
			}
			return true;
		}

		bool OnPlayerLeaveRaceCheckpoint(int playerid)
		{
			boost::unordered_map<int, streamerPlayer>::iterator p = core->getData()->players.find(playerid);
			if (p != core->getData()->players.end())
			{
				if (p->second.activeRaceCheckpoint == p->second.visibleRaceCheckpoint)
				{
					p->second.activeRaceCheckpoint = 0;
					return StreamerCall::OnPlayerLeaveDynamicRaceCP(playerid,p->second.activeRaceCheckpoint);
				}
			}
			return true;
		}
	}
}