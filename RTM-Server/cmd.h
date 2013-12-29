#pragma once

class CMD
{
	public:
	static void veh(int, char*);
	static void mm(int);

	static void invite(int, char*);
	static void uninvite(int, char*);
	static void makegang(int, char*);
	static void addproperty(int, char*);
	static void givemoney(int, char*);
	static void makeadmin(int, char*);
	static void setint(int, char*);
	static void setworld(int, char*);
	static void gotokk(int, char*); 
	static void cmd_goto( int, char* );
	static void shout(int, char*);
	static void whisper(int, char*);
	static void me(int, char*);
	static void domake(int, char*);
	static void dotry(int, char*);
	static void set_hp(const int, const char *);
	static void gethere(const int, const char *);
	
};

