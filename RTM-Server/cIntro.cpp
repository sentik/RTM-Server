#include "main.h"

enum introDraw
{
	IT_SNAME,
	IT_SENTIKE,
	IT_AND,
	IT_SERINC,
	IT_PRESENT,
	IT_BG,
	IT_STORY,
};


void cPlayer::Intro::cIntro::initTrain(const int u)
{
	char bot[16];
	//---------------------------
	Player[u].inIndex = -1;
	//---------------------------
	sprintf(bot, "train_%d", u);
	sampgdk_ConnectNPC(bot, "train_sf");
	//---------------------------
	logprintf("on initTrain: %d", Player[ u ].pClass);
	//---------------------------------------------------------------
	TextDrawShowForPlayer(u, drawPlayerChar[HIGHT_TOP]);
	TextDrawShowForPlayer(u, drawPlayerChar[HIGHT_BOTTOM]);
	//---------------------------------------------------------------
	Player[u].minerDraw[IT_SNAME] = CreatePlayerTextDraw(u, 320.000000, 230.000000, "West Role Play");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SNAME], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SNAME], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_SNAME], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SNAME], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_SNAME], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SNAME], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SNAME], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SNAME], 1);
	PlayerTextDrawUseBox(u, Player[u].minerDraw[IT_SNAME], 1);
	PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_SNAME], 838873680);
	PlayerTextDrawTextSize(u, Player[u].minerDraw[IT_SNAME], 0.000000, 735.000000);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SNAME], 0);

	Player[u].minerDraw[IT_SENTIKE] = CreatePlayerTextDraw(u, 260.000000, 211.000000, "Sentike");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SENTIKE], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SENTIKE], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_SENTIKE], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SENTIKE], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_SENTIKE], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SENTIKE], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SENTIKE], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SENTIKE], 1);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SENTIKE], 0);

	Player[u].minerDraw[IT_AND] = CreatePlayerTextDraw(u, 320.000000, 219.000000, "and");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_AND], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_AND], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_AND], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_AND], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_AND], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_AND], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_AND], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_AND], 1);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_AND], 0);

	Player[u].minerDraw[IT_SERINC] = CreatePlayerTextDraw(u, 306.000000, 228.000000, "Serinc");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SERINC], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SERINC], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_SERINC], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SERINC], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_SERINC], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SERINC], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SERINC], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SERINC], 1);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SERINC], 0);

	Player[u].minerDraw[IT_PRESENT] = CreatePlayerTextDraw(u, 320.000000, 220.000000, "PRESENT");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_PRESENT], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_PRESENT], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_PRESENT], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_PRESENT], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_PRESENT], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_PRESENT], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_PRESENT], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_PRESENT], 1);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_PRESENT], 0);

	Player[u].minerDraw[IT_BG] = CreatePlayerTextDraw(u, 320.000000, 1.000000, "_");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_BG], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_BG], 255);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_BG], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_BG], 0.500000, 60.0);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_BG], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_BG], 0);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_BG], 1);
	PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_BG], 1);
	PlayerTextDrawUseBox(u, Player[u].minerDraw[IT_BG], 1);
	PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_BG], 255);
	PlayerTextDrawTextSize(u, Player[u].minerDraw[IT_BG], 0.000000, 690.000000);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_BG], 0);
	PlayerTextDrawShow(u, Player[u].minerDraw[IT_BG]);

	Player[u].minerDraw[IT_STORY] = CreatePlayerTextDraw(u, 320.000000, 385.000000, "_");
	PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_STORY], 2);
	PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_STORY], 838873650);
	PlayerTextDrawFont(u, Player[u].minerDraw[IT_STORY], 1);
	PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_STORY], 0.500000, 1.000000);
	PlayerTextDrawColor(u, Player[u].minerDraw[IT_STORY], -1);
	PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_STORY], 1);
	PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_STORY], 1);
	PlayerTextDrawUseBox(u, Player[u].minerDraw[IT_STORY], 1);
	PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_STORY], 0);
	PlayerTextDrawTextSize(u, Player[u].minerDraw[IT_STORY], 0.000000, 555.000000);
	PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_STORY], 0);	
}

unsigned long createRGBA(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (a & 0xff);
}

void cPlayer::Intro::cIntro::drawIntro(const int u)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));//sleep(boost::posix_time::seconds(5));

	PlayAudioStreamForPlayer(u, "https://dl.dropboxusercontent.com/u/69743126/intro.mp3", 0.0, 0.0, 0.0, 50.0, false);

	for ( int i = 0; i < 20; i++ )
	{
		SendClientMessage(u, 255, " ");
	}

	int bggg = 255;

	case_bg:

	if (bggg > 0)
	{
		bggg -= 1;
		PlayerTextDrawHide(u, Player[u].minerDraw[IT_BG]);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_BG], bggg);
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_BG]);

		std::this_thread::sleep_for(std::chrono::milliseconds(25));

		goto case_bg;
	}

	float X = 640.0f;
	float Y = 0.0f;

	int R = 255;
	int G = 255;
	int B = 255;
	int A = 0;
	
	int bR = 0;
	int bG = 0;
	int bB = 0;
	int bA = 0;

	int AA = 0;

	int RR = 0;

	case_sentike:

	if (X > 340.0f) X -= 0.5f;
	if (Y < 300.0f) Y += 0.5f;
	if (A < 255) A += 1;
	if (bA < 255) bA += 1;

	if (Y > 180.0f && AA < 255) AA += 1;

	if (AA > 150 && RR < 200) RR += 1; 

	if (Y < 300.0f)
	{
		check_Sentike:
		PlayerTextDrawDestroy(u, Player[u].minerDraw[IT_SENTIKE]);
		Player[u].minerDraw[IT_SENTIKE] = CreatePlayerTextDraw(u, Y, 211.0, "Sentike");
		if(Player[u].minerDraw[IT_SENTIKE] )
		{
			PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SENTIKE], 2);
			PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SENTIKE], createRGBA(bR, bG, bB, bA));
			PlayerTextDrawFont(u, Player[u].minerDraw[IT_SENTIKE], 1);
			PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SENTIKE], 0.500000, 1.000000);
			PlayerTextDrawColor(u, Player[u].minerDraw[IT_SENTIKE], createRGBA(R, G, B, A));
			PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SENTIKE], 0);
			PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SENTIKE], 1);
			PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SENTIKE], 1);
			PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SENTIKE], 0);
			PlayerTextDrawShow(u, Player[u].minerDraw[IT_SENTIKE]);
		}
		else goto check_Sentike;

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_AND]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_AND], createRGBA(R, RR, B, AA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_AND], createRGBA(bR, bG, bB, AA));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_AND]);

		PlayerTextDrawDestroy(u, Player[u].minerDraw[IT_SERINC]);
		Player[u].minerDraw[IT_SERINC] = CreatePlayerTextDraw(u, X, 228.0, "Serinc");
		PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SERINC], 2);
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SERINC], createRGBA(bR, bG, bB, bA));
		PlayerTextDrawFont(u, Player[u].minerDraw[IT_SERINC], 1);
		PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SERINC], 0.500000, 1.000000);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_SERINC], createRGBA(R, G, B, A));
		PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SERINC], 0);
		PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SERINC], 1);
		PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SERINC], 1);
		PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SERINC], 0);
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_SERINC]);

		std::this_thread::sleep_for(std::chrono::milliseconds(15));

		goto case_sentike;
	}


	std::this_thread::sleep_for(std::chrono::seconds(5));

	bA = 0;

	case_hide:

	if (A > 0)
	{
		A -= 1;
		bA += 1;

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_SERINC]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_SERINC], createRGBA(R, G, B, A));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SERINC], createRGBA(bR, bG, bB, A));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_SERINC]);

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_AND]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_AND], createRGBA(R, RR, B, A));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_AND], createRGBA(bR, bG, bB, A));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_AND]);

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_SENTIKE]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_SENTIKE], createRGBA(R, G, B, A));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SENTIKE], createRGBA(bR, bG, bB, A));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_SENTIKE]);

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_PRESENT]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_PRESENT], createRGBA(R, RR, B, bA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_PRESENT], createRGBA(bR, bG, bB, bA));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_PRESENT]);

		std::this_thread::sleep_for(std::chrono::milliseconds(15));

		goto case_hide;
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));

	int tA = 0;

	case_server:

	if (bA > 0)
	{
		bA -= 1;
		tA += 1;
		
		if(A < 50 && bA < 50) A += 1;

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_PRESENT]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_PRESENT], createRGBA(R, RR, B, bA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_PRESENT], createRGBA(bR, bG, bB, bA));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_PRESENT]);

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_SNAME]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(R, G, B, tA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(bR, bG, bB, tA));
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(50, 0, 50, A));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_SNAME]);

		std::this_thread::sleep_for(std::chrono::milliseconds(15));

		goto case_server;
	}

	std::this_thread::sleep_for(std::chrono::seconds(10));

	X = 230.0f;

	case_end:

	if (X < 450.0f)
	{
		X += 0.5f;

		if (A > 0) A -= 1;
		if (tA > 0) tA -= 1;

		PlayerTextDrawDestroy(u, Player[u].minerDraw[IT_SNAME]);
		Player[u].minerDraw[IT_SNAME] = CreatePlayerTextDraw(u, 320.0, X, "West Role Play");
		PlayerTextDrawAlignment(u, Player[u].minerDraw[IT_SNAME], 2);
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(bR, bG, bB, tA));
		PlayerTextDrawFont(u, Player[u].minerDraw[IT_SNAME], 1);
		PlayerTextDrawLetterSize(u, Player[u].minerDraw[IT_SNAME], 0.500000, 1.000000);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(R, G, B, tA));
		PlayerTextDrawSetOutline(u, Player[u].minerDraw[IT_SNAME], 0);
		PlayerTextDrawSetProportional(u, Player[u].minerDraw[IT_SNAME], 1);
		PlayerTextDrawSetShadow(u, Player[u].minerDraw[IT_SNAME], 1);
		PlayerTextDrawUseBox(u, Player[u].minerDraw[IT_SNAME], 1);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_SNAME], createRGBA(50, 0, 50, A));
		PlayerTextDrawTextSize(u, Player[u].minerDraw[IT_SNAME], 0.000000, 735.000000);
		PlayerTextDrawSetSelectable(u, Player[u].minerDraw[IT_SNAME], 0);
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_SNAME]);

		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		goto case_end;
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));

	A = 0;

	case_story:
	char msg[256] = "";
	PlayerTextDrawSetString(u, Player[ u ].minerDraw[ IT_STORY ], "_");

	if ( A == 0 )
	{
		strcpy(msg, language::player::biography::familyPartOne[0]);
	}
	else if ( A == 1 )
	{
		strcpy(msg, language::player::biography::familyPartTwo[0]);
	}
	else if ( A == 2 )
	{
		strcpy(msg, language::player::biography::familyPartThree[0]);
	}
	else if ( A == 3 )
	{
		strcpy(msg, language::player::biography::familyPartFour[0]);
	}
	else if ( A == 4 )
	{
		strcpy(msg, language::player::biography::familyMotherOne[0]);
	}
	else if (A == 5)
	{
		strcpy(msg, language::player::biography::familyMotherTwo[ 0 ]);
	}
	else if (A == 6)
	{
		strcpy(msg, language::player::biography::familyMotherThree[ 0 ]);
	}
	else if (A == 7)
	{
		strcpy(msg, language::player::biography::familyFatherOne[ 0 ]);
	}
	else if (A == 8)
	{
		strcpy(msg, language::player::biography::familyFatherTwo[ 0 ]);
	}
	else if (A == 9)
	{
		strcpy(msg, language::player::biography::familyFatherThree[ 0 ]);
	}
	else if (A == 10)
	{
		if (strlen(language::player::biography::familyBrotheOne[ 0 ]) < 2)
		{
			A++;
			goto case_story;
		}
		strcpy(msg, language::player::biography::familyBrotheOne[ 0 ]);
	}
	else if (A == 11)
	{
		if (strlen(language::player::biography::familyBrotheTwo[ 0 ]) < 2)
		{
			A++;
			goto case_story;
		}
		strcpy(msg, language::player::biography::familyBrotheTwo[ 0 ]);
	}
	else if (A == 12)
	{
		if (strlen(language::player::biography::familyBrotheThree[ 0 ]) < 2)
		{
			A++;
			goto case_story;
		}
		strcpy(msg, language::player::biography::familyBrotheThree[ 0 ]);
	}
	else if (A == 13)
	{
		strcpy(msg, language::player::biography::familyPartFive[ 0 ]);
	}
	else if (A == 14)
	{
		if (strlen(language::player::biography::familyPartSix[ 0 ]) < 2)
		{
			A++;
			goto case_story;
		}
		strcpy(msg, language::player::biography::familyPartSix[ 0 ]);
	}
	AA = 0;
	bA = 0;

	cClass::fixText(msg, 256);



	PlayerTextDrawSetString(u, Player[u].minerDraw[IT_STORY], msg);

	case_showStory:

	if ( AA < 255 )
	{
		AA += 1;
		if ( bA < 50 ) bA += 1;

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_STORY]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_STORY], createRGBA(255, 255, 255, AA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_STORY], createRGBA(50, 0, 50, bA));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_STORY]);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		goto case_showStory;
	}

	std::this_thread::sleep_for(std::chrono::seconds(20));

	AA = 255;
	bA = 50;

	case_hideStory:

	if ( AA > 0 )
	{
		AA -= 1;
		if ( bA > 0 ) bA -= 1;

		PlayerTextDrawHide(u, Player[u].minerDraw[IT_STORY]);
		PlayerTextDrawColor(u, Player[u].minerDraw[IT_STORY], createRGBA(255, 255, 255, AA));
		PlayerTextDrawBackgroundColor(u, Player[u].minerDraw[IT_STORY], createRGBA(50, 0, 50, bA));
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_STORY]);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		goto case_hideStory;
	}

	A += 1;
	
	if ( A < 15 )
	{
		goto case_story;
	}


	case_bgg:

	if ( bggg < 255 )
	{
		bggg += 1;
		PlayerTextDrawHide(u, Player[u].minerDraw[IT_BG]);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_BG], bggg);
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_BG]);

		std::this_thread::sleep_for(std::chrono::milliseconds(25));

		goto case_bgg;
	}

	Player[u].inIndex = 5656;


	TextDrawHideForPlayer(u, drawPlayerChar[HIGHT_TOP]);
	TextDrawHideForPlayer(u, drawPlayerChar[HIGHT_BOTTOM]);

	TogglePlayerSpectating(u, false);
	cPlayer::SpawnChar(u);
	
	logprintf("on qqqq: %d", Player[ u ].pClass);
	cPlayer::setClassSkin(u);
	cPlayer::setCharPos(u, REG_SPAWN_X, REG_SPAWN_Y, REG_SPAWN_Z, false);
	cPlayer::setCharInterior(u, REG_SPAWN_INT);
	cPlayer::setCharWorld(u, REG_SPAWN_WOR);

	Player[ u ].isAction = PlayerAction::ACTION_NONE;

	dialogs::showDLGEnterName(u);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	case_bggg:

	if ( bggg > 0 )
	{
		bggg -= 1;
		PlayerTextDrawHide(u, Player[u].minerDraw[IT_BG]);
		PlayerTextDrawBoxColor(u, Player[u].minerDraw[IT_BG], bggg);
		PlayerTextDrawShow(u, Player[u].minerDraw[IT_BG]);

		std::this_thread::sleep_for(std::chrono::milliseconds(25));

		goto case_bggg;
	}

	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_AND]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_PRESENT]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_SENTIKE]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_SERINC]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_SNAME]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_BG]);
	PlayerTextDrawDestroy(u, Player[u].minerDraw[introDraw::IT_STORY]);
}

void cPlayer::Intro::cIntro::updateIntro(const int u)
{
	srand(time(NULL) + rand() + 123 * rand() + (1 + rand())*time(NULL));

	const int b = Player[ u ].inIndex;
	const float toRadians = 57.29578;
	float x;
	float y;
	float z;
	float a;

	logprintf("updateIntro:: player: %d || bot: %d", u, b);

	if (GetPlayerState(b) != PLAYER_STATE_DRIVER)
	{
		PutPlayerInVehicle(b, Player[b].pCarid, 0);
		//AttachCameraToObject(u, o);
	}
	else if (Player[u].aMinerA != 56)
	{		
		Player[u].aMinerA = 56;
		std::thread(cPlayer::Intro::cIntro::drawIntro, u).detach();
		
	}

	const float radius = 200.0f + (rand() % 10000) / 100;

	GetPlayerPos(b, &x, &y, &z);
	
	GetVehicleZAngle(Player[b].pCarid, &a);

	a += 90.0f;

	const float lrad = 50 + (rand() % 10000) / 100;

	const float lX = x + lrad * cosf(a / toRadians);
	const float lY = y + lrad * sinf(a / toRadians);

	a -= 90.0f;
	a += 70.0f + (rand() % 4000) / 100;

	const float cX = x + radius * cosf(a / toRadians);
	const float cY = y + radius * sinf(a / toRadians);

	const float cZ = z + 2 * (rand() % 5000) / 100;

	//MoveObject(o, cX, cY, cZ, 100.0, 0, 0, 0);
	//AttachObjectToVehicle(o, Player[b].pCarid, cX, cY, cZ, 0, 0, 0);
	InterpolateCameraPos(u, Player[u].pPosX, Player[u].pPosY, Player[u].pPosZ, cX, cY, cZ, 2000, CAMERA_MOVE);
	InterpolateCameraLookAt(u, Player[b].pPosX, Player[b].pPosY, Player[b].pPosZ, lX, lY, z, 2000, CAMERA_MOVE);
	//SetPlayerCameraLookAt(u, x, y, z, CAMERA_CUT);
	//AttachCameraToObject(u, o);

	Player[u].pPosX = cX;
	Player[u].pPosY = cY;
	Player[u].pPosZ = cZ;
	
	Player[b].pPosX = lX;
	Player[b].pPosY = lY;
	Player[b].pPosZ = z;
}


/*void cPlayer::Intro::cIntro::updateIntro(const int u)
{
//»д бота
const int b = 1;

float bX, bY, bZ, bA;
float pX, pY, pZ, pA;


if (GetPlayerState(b) != PLAYER_STATE_DRIVER)
{
PutPlayerInVehicle(b, Player[b].pCarid, 0);
PlayAudioStreamForPlayer(u, "https://dl.dropboxusercontent.com/u/69743126/intro.mp3");
}
//---------------------------------------
GetPlayerPos(b, &bX, &bY, &bZ);
GetVehicleZAngle(Player[ b ].pCarid, &bA);
//---------------------------------------
GetPlayerPos(u, &pX, &pY, &pZ);
GetPlayerFacingAngle(u, &pA);
//---------------------------------------
const int radius = 1;
const float cX = pX + radius * cosf(sqrtf(pow(bX, 2) - pow(pX, 2)));
const float cY = pY + radius * cosf(sqrtf(pow(bY, 2) - pow(bY, 2)));
const float cZ = pZ + rand() % 20 * cosf(sqrtf(pow(bZ, 2) - pow(bZ, 2)));

SetPlayerCameraPos(u, cX, cY, cZ);
SetPlayerCameraLookAt(u, pX, pY, pZ, CAMERA_MOVE);
}
*/
/*
void cPlayer::Intro::cIntro::updateIntro(const int u)
{
//»д бота
const int b = 1;
float x;
float y;
float z;
float a;

if (GetPlayerState(b) != PLAYER_STATE_DRIVER)
{
PutPlayerInVehicle(b, Player[b].pCarid, 0);
PlayAudioStreamForPlayer(u, "https://dl.dropboxusercontent.com/u/69743126/intro.mp3");
}
GetPlayerPos(b, &x, &y, &z);
GetVehicleZAngle(Player[b].pCarid, &a);

const int radius = 150.0f + ((float)(rand() % 40));

a = a + 70.0f + ((float)(rand() % 40));

//const float cX = x + radius * cosf(a / 57.29578);
//const float cY = y + radius * sinf(a / 57.29578);


srand(time(NULL) + rand() + 123 * rand() + ( 1 + rand() )*time(NULL));
const float per1 = ( 1 + rand() % 6 ) * 23.29578;
const float per2 = ( 1 + rand() % 6 ) * 24.29578;


logprintf("per: %f || per: %f", per1, per2);

const float cX = x + radius * cosf(a / per1);
const float cY = y + radius * sinf(a / per2);

const float cZ = z + 2*((float)(rand() % 100));




SetPlayerCameraPos(u, cX, cY, cZ);
SetPlayerCameraLookAt(u, x, y, z, CAMERA_MOVE);
}
*/