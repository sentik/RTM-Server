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

#ifndef STREAMER_H
#define STREAMER_H

#define INVALID_ALTERNATE_ID (-1)
#define INVALID_GENERIC_ID (0xFFFF)

#include "cell.h"
#include "common.h"
#include "item.h"
#include "player.h"

#include <boost/tuple/tuple.hpp>
#include <boost/unordered_set.hpp>

#include <bitset>
#include <map>

class Streamer
{
public:
	Streamer();

	bool setTickRate(std::size_t value);

	std::size_t getVisibleItems(int type);
	bool setVisibleItems(int type, std::size_t value);

	void startAutomaticUpdate();
	void startManualUpdate(streamerPlayer &player, bool getData);

	void processActiveItems();

	boost::unordered_set<Item::SharedArea> attachedAreas;
	boost::unordered_set<Item::SharedObject> attachedObjects;
	boost::unordered_set<Item::SharedTextLabel> attachedTextLabels;
	boost::unordered_set<Item::SharedObject> movingObjects;

	boost::unordered_map<int, int> internalPickups;
private:
	void calculateAverageUpdateTime();

	void performPlayerUpdate(streamerPlayer &player, bool automatic);

	void executeCallbacks(const std::multimap<bool, boost::tuple<int, int> > &areaCallbacks);
	void executeCallbacks(const std::vector<int> &objectCallbacks);

	void processAreas(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processCheckpoints(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processMapIcons(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processObjects(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processPickups(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processRaceCheckpoints(streamerPlayer &player, const std::vector<SharedCell> &cells);
	void processTextLabels(streamerPlayer &player, const std::vector<SharedCell> &cells);

	void processMovingObjects();
	void processAttachedAreas();
	void processAttachedObjects();
	void processAttachedTextLabels();

	std::size_t tickCount;
	std::size_t tickRate;

	boost::tuple<float, float> velocityBoundaries;

	std::size_t visibleMapIcons;
	std::size_t visibleObjects;
	std::size_t visiblePickups;
	std::size_t visibleTextLabels;

	float averageUpdateTime;
	bool processingFinalPlayer;

	template<std::size_t N, typename T>
	inline bool checkPlayer(const std::bitset<N> &a, const T &b, const boost::unordered_set<T> &c, const T &d, const boost::unordered_set<T> &e, const T &f)
	{
		return (a[b] && (c.empty() || c.find(d) != c.end()) && (e.empty() || e.find(f) != e.end()));
	}

	template<class Iterator, class Container>
	bool isLastPlayer(Iterator iterator, const Container &container)
	{
		return ((iterator != container.end()) && (++iterator == container.end()));
	}
};

#endif
