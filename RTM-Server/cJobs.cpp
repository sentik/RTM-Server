#include "main.h"

bool cPlayer::Jobs::cJobs::isInJob(const int u, const int j)
{
	if (Player[u].pJob1 == j)
		return true;
	else if (Player[u].pJob2 == j)
		return true;
	return false;
}

bool cPlayer::Jobs::cJobs::setJob(const int u, const int j)
{
	if (Player[u].pJob1 == cPlayer::Jobs::PlayerJob::JOB_NONE)
	{
		Player[u].pJob1 = j;
		return true;
	}
	else if (Player[u].pJob2 == cPlayer::Jobs::PlayerJob::JOB_NONE)
	{
		Player[u].pJob2 = j;
		return true;
	}
	return false;
}
