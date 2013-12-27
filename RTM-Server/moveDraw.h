#pragma once

struct s2dCord
{
	float	x;
	float	y;
};
/*
struct sDraws
{
	char text[64];					// Текст
	s2dCord begin;					// Начало кординат
	s2dCord end;					// Конец кординат
	s2dCord cur[MAX_PLAYERS];		// Текущие кординаты
	int	curColor [MAX_PLAYERS];
	int colSpeed;
	int	color[2];					// Цвет [Начало] [Конец]
	s2dCord speed;					// Скорость [UD] [RL]

	float sizeFont[4];
	
	
	
	bool isMove[MAX_PLAYERS];



	bool checkPos;
	bool checkColor;

};

namespace moveDraws
{
	struct sDraws extern Draw[ 10 ];
	int create(char name[], bool color, bool pos);
	void setBegin(int draw, float x, float y);
	void setEnd(int draw, float x, float y);
	void moveDraw(int u, int draw);
	void initDraw(int u, int draw);
	void setSpeed(int draw, float x, float y);
	void setColor(int draw, int begin, int end, int speed);
	bool getStatus(int u, int draw);
	void setStatus(int u, int draw, bool status);
	void updateColor(int u, int draw);
	void updatePos(int u, int draw);
}
*/
//---------------------------------------------------------------] Experimental
struct serColors
{
	int				begin;
	int				end;
	int				speed;
	int				cur[10];
	bool			anim[10];
};

struct serSizes
{
	s2dCord			begin;
	s2dCord			end;
	s2dCord			speed;
	s2dCord			cur[10];
	bool			anim[10];
};

struct serDraws
{
	char			text[64];					
	serSizes		textPos;
	serSizes		textSize;
	serSizes		textBoxSize;
	serColors		colFont;
	serColors		colBg;
	serColors		colBox;
	bool			outline;
	bool			box;
	bool			isCreated;
	unsigned char	alignment;
	unsigned char	shadow;
	unsigned char	font;
	unsigned char	id[10];
};

namespace extrimeDraws
{
	namespace variables
	{
		struct serDraws extern extrDraw[10];
	}

	class func
	{
		public:
		//General
		static int create(const char * text);
		static bool destroy(const int draw);
		//Begin settings position & sizes
		static void setBeginPosition(const int draw, const float x, const float y);			
		static void setBeginTextSize(const int draw, const float x, const float y);			
		static void setBeginBoxSize(const int draw, const float x, const float y);
		//Begin settings colors
		static void setBeginColorText(const int draw, const int color);
		static void setBeginColorBack(const int draw, const int color);
		static void setBeginColorBox(const int draw, const int color);
		//End settings position & sizes
		static void setEndPosition(const int draw, const float x, const float y);
		static void setEndTextSize(const int draw, const float x, const float y);
		static void setEndBoxSize(const int draw, const float x, const float y);
		//End settings colors
		static void setEndColorText(const int draw, const int color);
		static void setEndColorBack(const int draw, const int color);
		static void setEndColorBox(const int draw, const int color);
		//Etc settings
		static void toggleBox(const int draw, bool toggle);
		static void toggleOutline(const int draw, bool toggle);
		static void setFont(const int draw, unsigned char font);
		static void setAlign(const int draw, unsigned char align);
		static void setShadow(const int draw, unsigned char shadow);
		//Speed settings
		static void setSpeedTextPos(const int draw, const float x, const float y);
		static void setSpeedTextSize(const int draw, const float x, const float y);
		static void setSpeedTextBoxSize(const int draw, const float x, const float y);
		static void setSpeedColorText(const int draw, const int color);
		static void setSpeedColorBack(const int draw, const int color);
		static void setSpeedColorBox(const int draw, const int color);
		//Actions
		static void initDraw(const int u, const int draw);
		static void animateDraw(const int u, const int draw);
	};
}