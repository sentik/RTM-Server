#include "main.h"

std::vector<eTutDraws> extrimeDraws::tutorial::func::tutDraws;

namespace extrimeDraws
{
	namespace tutorial
	{
		void func::showText(const int u, const char * head, const char * text, bool autoclose, const int closetime)
		{
			char msg[512] = "";

			eTutDraws tmp;

			tmp.closetime = closetime ? (( int ) std::time(0) + closetime) : 0;
			tmp.player = u;

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
			cClass::fixText(msg, 512);
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
			cClass::fixText(msg, 512);
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
	}
}