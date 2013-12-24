#pragma once

#ifndef ___cFactMetal___
#define ___cFactMetal___

struct eMetal
{
	int		db;
	int		lvl;
	int		m1;
	int		m2;
	int		m3;
	int		m4;
	int		mat;
	float	cost;
	char	name[24];
};


namespace Properties
{
	namespace Factory
	{
		namespace Metal
		{
			class func
			{
				public:
				static void load();
				static void save();
			};

			static struct eMetal Factm[MAX_FACT_M];

			enum rowsMetal
			{
				id,
				owner,
				property,
				type,
				x,
				y,
				z,
				price,
				bank,
				region,
				number,
				db,
				lvl,
				m1,
				m2,
				m3,
				m4,
				mat,
				cost,
				name,
				pname,
			};
		}
	}
}

#endif