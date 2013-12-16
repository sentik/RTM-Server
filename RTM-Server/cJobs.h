#pragma once

#ifndef ___cJobs___
#define ___cJobs___

namespace cPlayer
{
	namespace Jobs
	{
		class cJobs
		{
			public:
				static bool isInJob(const int, const int);
				static bool setJob(const int, const int);
		};

		enum PlayerJob
		{
			JOB_NONE,
			JOB_MINER,
			JOB_FELLER,
		};
	}
}

#endif