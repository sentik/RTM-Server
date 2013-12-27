#include "main.h"

namespace extrimeDraws
{
	namespace variables
	{
		struct serDraws extrDraw[10];
	}

//========================================================================================] General
	int func::create(const char * text)
		{
			int current = -1;

			for ( int t = 0; t < sizeof( variables::extrDraw ); t++ )
			{
				if ( variables::extrDraw[t].isCreated == false )
				{
					current = t;
					break;
				}
			}

			strcpy(variables::extrDraw[current].text, text);
			variables::extrDraw[current].isCreated = true;

			return current;
		}
	bool func::destroy(const int draw)
		{
			if ( variables::extrDraw[draw].isCreated == true )
			{
				variables::extrDraw[draw] = serDraws();
				return true;
			}
			return false;
		}
//========================================================================================] Begin settings position & sizes
	void func::setBeginPosition(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textPos.begin.x = x;
			variables::extrDraw[draw].textPos.begin.y = y;
		}
	void func::setBeginTextSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textSize.begin.x = x;
			variables::extrDraw[draw].textSize.begin.y = y;
		}
	void func::setBeginBoxSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textBoxSize.begin.x = x;
			variables::extrDraw[draw].textBoxSize.begin.y = y;
		}
//========================================================================================] End settings position & sizes
	void func::setEndPosition(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textPos.end.x = x;
			variables::extrDraw[draw].textPos.end.y = y;
		}
	void func::setEndTextSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textSize.end.x = x;
			variables::extrDraw[draw].textSize.end.y = y;
		}
	void func::setEndBoxSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textBoxSize.end.x = x;
			variables::extrDraw[draw].textBoxSize.end.y = y;
		}
//========================================================================================] Begin settings colors
	void func::setBeginColorText(const int draw, const int color)
		{
			variables::extrDraw[draw].colFont.begin = color;
		}
	void func::setBeginColorBack(const int draw, const int color)
		{
			variables::extrDraw[draw].colBg.begin = color;
		}
	void func::setBeginColorBox(const int draw, const int color)
		{
			variables::extrDraw[draw].colBox.begin = color;
		}
//========================================================================================] End settings colors
	void func::setEndColorText(const int draw, const int color)
		{
			variables::extrDraw[draw].colFont.end = color;
		}
	void func::setEndColorBack(const int draw, const int color)
		{
			variables::extrDraw[draw].colBg.end = color;
		}
	void func::setEndColorBox(const int draw, const int color)
		{
			variables::extrDraw[draw].colBox.end = color;
		}
//========================================================================================] Etc settings
	void func::toggleBox(const int draw, bool toggle)
		{
			variables::extrDraw[draw].box = toggle;
		}
	void func::toggleOutline(const int draw, bool toggle)
		{
			variables::extrDraw[draw].outline = toggle;
		}
	void func::setFont(const int draw, unsigned char font)
		{
			variables::extrDraw[draw].font = font;
		}
	void func::setAlign(const int draw, unsigned char align)
		{
			variables::extrDraw[draw].alignment = align;
		}
	void func::setShadow(const int draw, unsigned char shadow)
		{
			variables::extrDraw[draw].shadow = shadow;
		}
//========================================================================================] Speed settings
	void func::setSpeedTextPos(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textPos.speed.x = x;
			variables::extrDraw[draw].textPos.speed.y = y;
		}
	void func::setSpeedTextSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textSize.speed.x = x;
			variables::extrDraw[draw].textSize.speed.y = y;
		}
	void func::setSpeedTextBoxSize(const int draw, const float x, const float y)
		{
			variables::extrDraw[draw].textBoxSize.speed.x = x;
			variables::extrDraw[draw].textBoxSize.speed.y = y;
		}
	void func::setSpeedColorText(const int draw, const int color)
		{
			variables::extrDraw[draw].colFont.speed = color;
		}
	void func::setSpeedColorBack(const int draw, const int color)
		{
			variables::extrDraw[draw].colBg.speed = color;
		}
	void func::setSpeedColorBox(const int draw, const int color)
		{
			variables::extrDraw[draw].colBox.speed = color;
		}
//========================================================================================] Actions
	void func::initDraw(const int u, const int draw)
		{
			//Positions & sizes
			variables::extrDraw[draw].textPos.cur[u] = variables::extrDraw[draw].textPos.begin;
			variables::extrDraw[draw].textSize.cur[u] = variables::extrDraw[draw].textSize.begin;
			variables::extrDraw[draw].textBoxSize.cur[u] = variables::extrDraw[draw].textBoxSize.begin;
			//Colors
			variables::extrDraw[draw].colFont.cur[u] = variables::extrDraw[draw].colFont.begin;
			variables::extrDraw[draw].colBox.cur[u] = variables::extrDraw[draw].colBox.begin;
			variables::extrDraw[draw].colBg.cur[u] = variables::extrDraw[draw].colBg.begin;

			variables::extrDraw[draw].textPos.anim[u] = true;

			std::thread(func::animateDraw, u, draw).detach();
		}
	void func::animateDraw(const int u, const int draw)
		{
	case_start: //for test

			if ( variables::extrDraw[draw].id[u] != INVALID_TEXT_DRAW )
			{
				PlayerTextDrawDestroy(u, variables::extrDraw[draw].id[u]);
			}

			if ( variables::extrDraw[draw].textPos.anim[u] == true )
			{
				if ( variables::extrDraw[draw].textPos.cur[u].x == variables::extrDraw[draw].textPos.end.x && variables::extrDraw[draw].textPos.cur[u].y == variables::extrDraw[draw].textPos.end.y )
				{
					variables::extrDraw[draw].textPos.anim[u] = false;
				}
				else
				{
					if ( variables::extrDraw[draw].textPos.cur[u].x != variables::extrDraw[draw].textPos.end.x )
					{
						variables::extrDraw[draw].textPos.cur[u].x += variables::extrDraw[draw].textPos.speed.x;
						if ( variables::extrDraw[draw].textPos.cur[u].x > variables::extrDraw[draw].textPos.end.x && variables::extrDraw[draw].textPos.end.x > variables::extrDraw[draw].textPos.begin.x )
						{
							variables::extrDraw[draw].textPos.cur[u].x = variables::extrDraw[draw].textPos.end.x;
						}
						else if ( variables::extrDraw[draw].textPos.cur[u].x < variables::extrDraw[draw].textPos.end.x && variables::extrDraw[draw].textPos.end.x < variables::extrDraw[draw].textPos.begin.x )
						{
							variables::extrDraw[draw].textPos.cur[u].x = variables::extrDraw[draw].textPos.end.x;
						}
					}

					if ( variables::extrDraw[draw].textPos.cur[u].y != variables::extrDraw[draw].textPos.end.y )
					{
						variables::extrDraw[draw].textPos.cur[u].y += variables::extrDraw[draw].textPos.speed.y;
						if ( variables::extrDraw[draw].textPos.cur[u].y > variables::extrDraw[draw].textPos.end.y && variables::extrDraw[draw].textPos.end.y > variables::extrDraw[draw].textPos.begin.y )
						{
							variables::extrDraw[draw].textPos.cur[u].y = variables::extrDraw[draw].textPos.end.y;
						}
						else if ( variables::extrDraw[draw].textPos.cur[u].y < variables::extrDraw[draw].textPos.end.y && variables::extrDraw[draw].textPos.end.y < variables::extrDraw[draw].textPos.begin.y )
						{
							variables::extrDraw[draw].textPos.cur[u].y = variables::extrDraw[draw].textPos.end.y;
						}
					}
				}
			}
			else
			{
				std::this_thread::yield();
			}

			variables::extrDraw[draw].id[u] = CreatePlayerTextDraw(u, variables::extrDraw[draw].textPos.cur[u].x, variables::extrDraw[draw].textPos.cur[u].y, variables::extrDraw[draw].text);
			PlayerTextDrawAlignment(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].alignment);
			PlayerTextDrawBackgroundColor(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].colBg.cur[u]);
			PlayerTextDrawFont(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].font);
			PlayerTextDrawLetterSize(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].textSize.cur[u].x, variables::extrDraw[draw].textSize.cur[u].y);
			PlayerTextDrawColor(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].colFont.cur[u]);
			PlayerTextDrawSetOutline(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].outline);
			PlayerTextDrawSetShadow(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].shadow);
			PlayerTextDrawUseBox(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].box);
			PlayerTextDrawBoxColor(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].colBox.cur[u]);
			PlayerTextDrawTextSize(u, variables::extrDraw[draw].id[u], variables::extrDraw[draw].textBoxSize.cur[u].x, variables::extrDraw[draw].textBoxSize.cur[u].y);
			PlayerTextDrawShow(u, variables::extrDraw[draw].id[u]);

			std::this_thread::sleep_for(std::chrono::milliseconds(30));

			if ( variables::extrDraw[draw].textPos.anim[u] )
				goto case_start;

			GameTextForPlayer(u, "~r~end thread", 1000, 1);
		}
}
/*
namespace moveDraws
{
	struct sDraws Draw[ 10 ];

	/// <summary>
	/// Создать текст драв
	/// <param name="i">* Ид игрока</param>
	/// </summary>
	int create(char name[], bool color = false, bool pos = false)
	{
		static int count;
		Draw[count].checkPos = pos;
		Draw[count].checkColor = color;
		strcpy(Draw[count].text, name);
		count++;
		return count-1;
	}

	void setBegin(int draw, float x, float y)
	{
		Draw[draw].begin.x = x;
		Draw[draw].begin.y = y;
	}

	void setEnd(int draw, float x, float y)
	{
		Draw[draw].end.x = x;
		Draw[draw].end.y = y;
	}

	void setSpeed(int draw, float x, float y)
	{
		Draw[draw].speed.x = x;
		Draw[draw].speed.y = y;
	}

	void setColor(int draw, int begin, int end, int speed)
	{
		Draw[draw].colSpeed = speed;
		Draw[draw].color[0] = begin;
		Draw[draw].color[1] = end;
	}


	void initDraw(int u, int draw)
	{
		Draw[draw].isMove[u] = true;
		Draw[draw].cur[u].x = Draw[draw].begin.x;
		Draw[draw].cur[u].y = Draw[draw].begin.y;
		Draw[draw].curColor[u] = Draw[draw].color[0];
	}

	void setStatus(int u, int draw, bool status)
	{
		Draw[draw].isMove[u]  = status;
	}


	bool getStatus(int u, int draw)
	{
		return Draw[draw].isMove[u];
	}


	void updatePos(int u, int draw)
	{
		Draw[draw].cur[u].x += Draw[draw].speed.x;
		Draw[draw].cur[u].y += Draw[draw].speed.y;
		//-----------------------------------
		if(Draw[draw].checkPos)
		{
			if(Draw[draw].cur[u].x >= Draw[draw].end.x)
			{
				Draw[draw].cur[u].x = Draw[draw].end.x;
				Draw[draw].isMove[u] = false;
			}
			else if(Draw[draw].cur[u].y >= Draw[draw].end.y)
			{
				Draw[draw].cur[u].y = Draw[draw].end.y;
				Draw[draw].isMove[u] = false;
			}
			else if(Draw[draw].cur[u].x <= Draw[draw].begin.x)
			{
				Draw[draw].cur[u].x = Draw[draw].begin.x;
				Draw[draw].isMove[u] = false;
			}
			else if(Draw[draw].cur[u].y <= Draw[draw].begin.y)
			{
				Draw[draw].cur[u].y = Draw[draw].begin.y;
				Draw[draw].isMove[u] = false;
			}
		}
	}

	void updateColor(int u, int draw)
	{
		Draw[draw].curColor[u] += Draw[draw].colSpeed;
		//-----------------------------------
		PlayerTextDrawColor
		(
			u,
			Player[u].pDraw, 
			Draw[draw].curColor[u]
		);
		//-----------------------------------
		if(Draw[draw].checkColor)
		{
			if(Draw[draw].curColor[u] <= Draw[draw].color[0])
			{
				Draw[draw].curColor[u] = Draw[draw].color[0];
				Draw[draw].isMove[u] = false;
			}
			else if(Draw[draw].curColor[u] >= Draw[draw].color[1])
			{
				Draw[draw].curColor[u] = Draw[draw].color[1];
				Draw[draw].isMove[u] = false;
			}
		}
		//-----------------------------------
	}

	void moveDraw(int u, int draw)
	{
		//-----------------------------------
		if(Player[u].pDraw != -1)
		{
			PlayerTextDrawDestroy(u, Player[u].pDraw);
		}
		if(Draw[draw].isMove[u])
		{
			//-----------------------------------
			updatePos(u, draw);
			//-----------------------------------
			Player[u].pDraw = CreatePlayerTextDraw
			(
				u, 
				Draw[draw].cur[u].x,
				Draw[draw].cur[u].y,
				Draw[draw].text
			);
			//-----------------------------------
			updateColor(u, draw);
			//-----------------------------------
			PlayerTextDrawShow(u, Player[u].pDraw);
		}
	}
}
*/