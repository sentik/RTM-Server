#include "main.h"

std::vector<eTutDraws> extrimeDraws::tutorial::func::tutDraws;

namespace extrimeDraws
{
	namespace tutorial
	{
		void func::showText(const int u, const char * head, const char * text, const bool autoclose, const int closetime)
		{
			char msg[256] = "";

			eTutDraws tmp;

			tmp.closetime = closetime ? (( int ) std::time(0) + closetime) : 0;
			tmp.player = u;
			tmp.global = false;

			tmp.draws.body = CreatePlayerTextDraw(u, 320.000000, 360.000000, "_");
			PlayerTextDrawAlignment(u, tmp.draws.body, 2);
			PlayerTextDrawBackgroundColor(u, tmp.draws.body, 255);
			PlayerTextDrawFont(u, tmp.draws.body, 1);
			PlayerTextDrawLetterSize(u, tmp.draws.body, 0.500000, 9.000000);
			PlayerTextDrawColor(u, tmp.draws.body, -1);
			PlayerTextDrawSetOutline(u, tmp.draws.body, 0);
			PlayerTextDrawSetProportional(u, tmp.draws.body, 1);
			PlayerTextDrawSetShadow(u, tmp.draws.body, 1);
			PlayerTextDrawUseBox(u, tmp.draws.body, 1);
			PlayerTextDrawBoxColor(u, tmp.draws.body, 80);
			PlayerTextDrawTextSize(u, tmp.draws.body, 0.000000, 200.000000);
			PlayerTextDrawSetSelectable(u, tmp.draws.body, 0);
			PlayerTextDraw(tmp.draws.body, u).Show();

			strcpy(msg, head);
			cClass::fixText(msg, 64);
			tmp.draws.header = CreatePlayerTextDraw(u, 320.000000, 360.000000, msg);
			PlayerTextDrawAlignment(u, tmp.draws.header, 2);
			PlayerTextDrawBackgroundColor(u, tmp.draws.header, -589505451);
			PlayerTextDrawFont(u, tmp.draws.header, 1);
			PlayerTextDrawLetterSize(u, tmp.draws.header, 0.400000, 1.099998);
			PlayerTextDrawColor(u, tmp.draws.header, 150);
			PlayerTextDrawSetOutline(u, tmp.draws.header, 1);
			PlayerTextDrawSetProportional(u, tmp.draws.header, 1);
			PlayerTextDrawUseBox(u, tmp.draws.header, 1);
			PlayerTextDrawBoxColor(u, tmp.draws.header, -589505502);
			PlayerTextDrawTextSize(u, tmp.draws.header, 0.000000, 200.000000);
			PlayerTextDrawSetSelectable(u, tmp.draws.header, 0);
			PlayerTextDraw(tmp.draws.header, u).Show();

			if ( !autoclose )
			{
				tmp.draws.close = CreatePlayerTextDraw(u, 414.000000, 358.000000, "X");
				PlayerTextDrawAlignment(u, tmp.draws.close, 2);
				PlayerTextDrawBackgroundColor(u, tmp.draws.close, -939472696);
				PlayerTextDrawFont(u, tmp.draws.close, 1);
				PlayerTextDrawLetterSize(u, tmp.draws.close, 0.609999, 1.500000);
				PlayerTextDrawColor(u, tmp.draws.close, 100);
				PlayerTextDrawSetOutline(u, tmp.draws.close, 0);
				PlayerTextDrawSetProportional(u, tmp.draws.close, 1);
				PlayerTextDrawSetShadow(u, tmp.draws.close, 0);
				PlayerTextDrawUseBox(u, tmp.draws.close, 1);
				PlayerTextDrawBoxColor(u, tmp.draws.close, 0);
				PlayerTextDrawTextSize(u, tmp.draws.close, 10.000000, 10.000000);
				PlayerTextDrawSetSelectable(u, tmp.draws.close, 1);
				PlayerTextDraw(tmp.draws.close, u).Show();

				SelectTextDraw(u, tocolor(150,150,150,200));
			}

			strcpy(msg, text);
			cClass::fixText(msg, 256);
			tmp.draws.text = CreatePlayerTextDraw(u, 320.000000, 380.000000, msg);
			PlayerTextDrawAlignment(u, tmp.draws.text, 2);
			PlayerTextDrawBackgroundColor(u, tmp.draws.text, -926365596);
			PlayerTextDrawFont(u, tmp.draws.text, 1);
			PlayerTextDrawLetterSize(u, tmp.draws.text, 0.400000, 1.000000);
			PlayerTextDrawColor(u, tmp.draws.text, -1);
			PlayerTextDrawSetOutline(u, tmp.draws.text, 0);
			PlayerTextDrawSetProportional(u, tmp.draws.text, 1);
			PlayerTextDrawSetShadow(u, tmp.draws.text, 1);
			PlayerTextDrawUseBox(u, tmp.draws.text, 1);
			PlayerTextDrawBoxColor(u, tmp.draws.text, 0);
			PlayerTextDrawTextSize(u, tmp.draws.text, 0.000000, 200.000000);
			PlayerTextDrawSetSelectable(u, tmp.draws.text, 0);
			PlayerTextDraw(tmp.draws.text, u).Show();

			tutDraws.push_back(tmp);
		}

		void func::showTextForAll(const char * head, const char * text, const bool autoclose, const int closetime)
		{
			char msg[256] = "";

			eTutDraws tmp;

			tmp.closetime = closetime ? ( ( int ) std::time(0) + closetime ) : 0;
			tmp.player = INVALID_PLAYER_ID;
			tmp.global = false;

			tmp.draws.body = TextDrawCreate(320.000000, 360.000000, "_");
			TextDrawAlignment(tmp.draws.body, 2);
			TextDrawBackgroundColor(tmp.draws.body, 255);
			TextDrawFont(tmp.draws.body, 1);
			TextDrawLetterSize(tmp.draws.body, 0.500000, 9.000000);
			TextDrawColor(tmp.draws.body, -1);
			TextDrawSetOutline(tmp.draws.body, 0);
			TextDrawSetProportional(tmp.draws.body, 1);
			TextDrawSetShadow(tmp.draws.body, 1);
			TextDrawUseBox(tmp.draws.body, 1);
			TextDrawBoxColor(tmp.draws.body, 80);
			TextDrawTextSize(tmp.draws.body, 0.000000, 200.000000);
			TextDrawSetSelectable(tmp.draws.body, 0);
			TextDraw(tmp.draws.body).ShowForAll();

			strcpy(msg, head);
			cClass::fixText(msg, 64);
			tmp.draws.header = TextDrawCreate(320.000000, 360.000000, msg);
			TextDrawAlignment(tmp.draws.header, 2);
			TextDrawBackgroundColor(tmp.draws.header, -589505451);
			TextDrawFont(tmp.draws.header, 1);
			TextDrawLetterSize(tmp.draws.header, 0.400000, 1.099998);
			TextDrawColor(tmp.draws.header, 150);
			TextDrawSetOutline(tmp.draws.header, 1);
			TextDrawSetProportional(tmp.draws.header, 1);
			TextDrawUseBox(tmp.draws.header, 1);
			TextDrawBoxColor(tmp.draws.header, -589505502);
			TextDrawTextSize(tmp.draws.header, 0.000000, 200.000000);
			TextDrawSetSelectable(tmp.draws.header, 0);
			TextDraw(tmp.draws.header).ShowForAll();

			if ( !autoclose )
			{
				tmp.draws.close = TextDrawCreate(414.000000, 358.000000, "X");
				TextDrawAlignment(tmp.draws.close, 2);
				TextDrawBackgroundColor(tmp.draws.close, -939472696);
				TextDrawFont(tmp.draws.close, 1);
				TextDrawLetterSize(tmp.draws.close, 0.609999, 1.500000);
				TextDrawColor(tmp.draws.close, 100);
				TextDrawSetOutline(tmp.draws.close, 0);
				TextDrawSetProportional(tmp.draws.close, 1);
				TextDrawSetShadow(tmp.draws.close, 0);
				TextDrawUseBox(tmp.draws.close, 1);
				TextDrawBoxColor(tmp.draws.close, 0);
				TextDrawTextSize(tmp.draws.close, 10.000000, 10.000000);
				TextDrawSetSelectable(tmp.draws.close, 1);
				TextDraw(tmp.draws.close).ShowForAll();

				for ( int i = 0; i < MAX_PLAYERS; i++ )
				{
					if ( Player[i].isLogged )
					{
						SelectTextDraw(i, tocolor(150, 150, 150, 200));
					}
				}
			}

			strcpy(msg, text);
			cClass::fixText(msg, 256);
			tmp.draws.text = TextDrawCreate(320.000000, 380.000000, msg);
			TextDrawAlignment(tmp.draws.text, 2);
			TextDrawBackgroundColor(tmp.draws.text, -926365596);
			TextDrawFont(tmp.draws.text, 1);
			TextDrawLetterSize(tmp.draws.text, 0.400000, 1.000000);
			TextDrawColor(tmp.draws.text, -1);
			TextDrawSetOutline(tmp.draws.text, 0);
			TextDrawSetProportional(tmp.draws.text, 1);
			TextDrawSetShadow(tmp.draws.text, 1);
			TextDrawUseBox(tmp.draws.text, 1);
			TextDrawBoxColor(tmp.draws.text, 0);
			TextDrawTextSize(tmp.draws.text, 0.000000, 200.000000);
			TextDrawSetSelectable(tmp.draws.text, 0);
			TextDraw(tmp.draws.text).ShowForAll();

			for ( int i = 0; i < MAX_PLAYERS; i++ )
			{
				if ( Player[i].isLogged )
				{
					tmp.countPlayers += 1;
				}
			}

			tutDraws.push_back(tmp);
		}

		int func::create(const char * head, const char * text)
		{
			eTutDraws tmp;

			tmp.player = INVALID_PLAYER_ID;
			tmp.global = true;

			strcpy(tmp.head, head);
			strcpy(tmp.text, text);

			cClass::fixText(tmp.head, 64);
			cClass::fixText(tmp.text, 256);

			tutDraws.push_back(tmp);

			return tutDraws.size();
		}

		bool func::destroy(const int number)
		{
			if ( tutDraws.at(number).global == true )
			{
				if ( TextDraw(tutDraws.at(number).draws.body).GetId() != INVALID_TEXT_DRAW )
				{
					TextDraw(tutDraws.at(number).draws.body).Destroy();
					TextDraw(tutDraws.at(number).draws.close).Destroy();
					TextDraw(tutDraws.at(number).draws.header).Destroy();
					TextDraw(tutDraws.at(number).draws.text).Destroy();
				}

				tutDraws.erase(tutDraws.begin + number);
				return true;
			}
			return false;
		}

		void func::show(const int number, const bool autoclose, const int closetime)
		{
			if ( tutDraws.at(number).global == true )
			{
				tutDraws.at(number).closetime = closetime ? ( ( int ) std::time(0) + closetime ) : 0;
				tutDraws.at(number).player = INVALID_PLAYER_ID;

				tutDraws.at(number).draws.body = TextDrawCreate(320.000000, 360.000000, "_");
				TextDrawAlignment(tutDraws.at(number).draws.body, 2);
				TextDrawBackgroundColor(tutDraws.at(number).draws.body, 255);
				TextDrawFont(tutDraws.at(number).draws.body, 1);
				TextDrawLetterSize(tutDraws.at(number).draws.body, 0.500000, 9.000000);
				TextDrawColor(tutDraws.at(number).draws.body, -1);
				TextDrawSetOutline(tutDraws.at(number).draws.body, 0);
				TextDrawSetProportional(tutDraws.at(number).draws.body, 1);
				TextDrawSetShadow(tutDraws.at(number).draws.body, 1);
				TextDrawUseBox(tutDraws.at(number).draws.body, 1);
				TextDrawBoxColor(tutDraws.at(number).draws.body, 80);
				TextDrawTextSize(tutDraws.at(number).draws.body, 0.000000, 200.000000);
				TextDrawSetSelectable(tutDraws.at(number).draws.body, 0);
				TextDraw(tutDraws.at(number).draws.body).ShowForAll();

				tutDraws.at(number).draws.header = TextDrawCreate(320.000000, 360.000000, tutDraws.at(number).head);
				TextDrawAlignment(tutDraws.at(number).draws.header, 2);
				TextDrawBackgroundColor(tutDraws.at(number).draws.header, -589505451);
				TextDrawFont(tutDraws.at(number).draws.header, 1);
				TextDrawLetterSize(tutDraws.at(number).draws.header, 0.400000, 1.099998);
				TextDrawColor(tutDraws.at(number).draws.header, 150);
				TextDrawSetOutline(tutDraws.at(number).draws.header, 1);
				TextDrawSetProportional(tutDraws.at(number).draws.header, 1);
				TextDrawUseBox(tutDraws.at(number).draws.header, 1);
				TextDrawBoxColor(tutDraws.at(number).draws.header, -589505502);
				TextDrawTextSize(tutDraws.at(number).draws.header, 0.000000, 200.000000);
				TextDrawSetSelectable(tutDraws.at(number).draws.header, 0);
				TextDraw(tutDraws.at(number).draws.header).ShowForAll();

				if ( !autoclose )
				{
					tutDraws.at(number).draws.close = TextDrawCreate(414.000000, 358.000000, "X");
					TextDrawAlignment(tutDraws.at(number).draws.close, 2);
					TextDrawBackgroundColor(tutDraws.at(number).draws.close, -939472696);
					TextDrawFont(tutDraws.at(number).draws.close, 1);
					TextDrawLetterSize(tutDraws.at(number).draws.close, 0.609999, 1.500000);
					TextDrawColor(tutDraws.at(number).draws.close, 100);
					TextDrawSetOutline(tutDraws.at(number).draws.close, 0);
					TextDrawSetProportional(tutDraws.at(number).draws.close, 1);
					TextDrawSetShadow(tutDraws.at(number).draws.close, 0);
					TextDrawUseBox(tutDraws.at(number).draws.close, 1);
					TextDrawBoxColor(tutDraws.at(number).draws.close, 0);
					TextDrawTextSize(tutDraws.at(number).draws.close, 10.000000, 10.000000);
					TextDrawSetSelectable(tutDraws.at(number).draws.close, 1);
					TextDraw(tutDraws.at(number).draws.close).ShowForAll();

					for ( int i = 0; i < MAX_PLAYERS; i++ )
					{
						if ( Player[i].isLogged )
						{
							SelectTextDraw(i, tocolor(150, 150, 150, 200));
						}
					}
				}

				tutDraws.at(number).draws.text = TextDrawCreate(320.000000, 380.000000, tutDraws.at(number).text);
				TextDrawAlignment(tutDraws.at(number).draws.text, 2);
				TextDrawBackgroundColor(tutDraws.at(number).draws.text, -926365596);
				TextDrawFont(tutDraws.at(number).draws.text, 1);
				TextDrawLetterSize(tutDraws.at(number).draws.text, 0.400000, 1.000000);
				TextDrawColor(tutDraws.at(number).draws.text, -1);
				TextDrawSetOutline(tutDraws.at(number).draws.text, 0);
				TextDrawSetProportional(tutDraws.at(number).draws.text, 1);
				TextDrawSetShadow(tutDraws.at(number).draws.text, 1);
				TextDrawUseBox(tutDraws.at(number).draws.text, 1);
				TextDrawBoxColor(tutDraws.at(number).draws.text, 0);
				TextDrawTextSize(tutDraws.at(number).draws.text, 0.000000, 200.000000);
				TextDrawSetSelectable(tutDraws.at(number).draws.text, 0);
				TextDraw(tutDraws.at(number).draws.text).ShowForAll();

				for ( int i = 0; i < MAX_PLAYERS; i++ )
				{
					if ( Player[i].isLogged )
					{
						tutDraws.at(number).countPlayers += 1;
					}
				}
			}
		}
		void func::hide(const int number)
		{
			if ( tutDraws.at(number).global == true )
			{
				TextDraw(tutDraws.at(number).draws.body).Destroy();
				TextDraw(tutDraws.at(number).draws.close).Destroy();
				TextDraw(tutDraws.at(number).draws.header).Destroy();
				TextDraw(tutDraws.at(number).draws.text).Destroy();

				tutDraws.at(number).closetime = 0;
				tutDraws.at(number).countPlayers = 0;
			}
		}
	}
}