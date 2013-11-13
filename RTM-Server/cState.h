#pragma once
#ifndef __cState__   
#define __cState__   

class cState
{
	public:
		static void cState::callKeyStateChange(int playerid, int newkeys, int oldkeys);
		static void cState::callStateChange(int playerid, int newstate, int oldstate);
};

#endif 