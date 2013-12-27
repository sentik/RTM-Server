#pragma once
#pragma warning(disable: 4305)
class saZones
{
	public:
	saZones();
	~saZones();
};

struct ZonePosition
{
	float
	Xmin,
	Ymin,
	Zmin,
	Xmax,
	Ymax,
	Zmax;
};

struct ZoneData
{
	char* name;
	ZonePosition pos;
};

ZoneData extern gSAZones[ 365 ];
std::stack<int> extern PlayerAreas[ MAX_PLAYERS ];
std::unordered_map<int, std::string> extern ZoneAreas;
