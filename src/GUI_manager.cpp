#include"GUI_manager.h"
IMAGE Cherry_b;
IMAGE normal_eat1[4];
IMAGE normal_eat2[4];
IMAGE normal_walk1[8];
IMAGE normal_walk2[8];
IMAGE normal_die[13];
IMAGE Egg_boom[6];
IMAGE Egg_pitcher[26];
IMAGE Egg_b[5];
IMAGE background_game[5];
IMAGE Cherry_boom[4];
IMAGE Cherry_tart[9];
IMAGE hotpot[13];
IMAGE hotpot_b[42];

void GUIManager::loading()
{
	loadimage(&background_game[0], "../resources/picture/Screen/background_game1.png", 900, 560);
	loadimage(&background_game[1], "../resources/picture/Screen/lawnmower.png", 50, 40);
	loadimage(&background_game[2], "../resources/picture/Screen/1.png", 100, 120);
	loadimage(&background_game[3], "../resources/picture/Screen/2.png", 100, 120);
	loadimage(&background_game[4], "../resources/picture/Screen/3.png", 100, 120);

	loadimage(&Cherry_b, "../resources/picture/food/Cherrys_tart/Cherry_b/1.png");

	loadImages(normal_eat1, "../resources/picture/mouse/normal_mouse/normal_eat1/eat1_", 4, 1);
	loadImages(normal_eat2, "../resources/picture/mouse/normal_mouse/normal_eat2/eat2_", 4, 1);
	loadImages(normal_walk1, "../resources/picture/mouse/normal_mouse/normal_walk1/walk1_", 8, 1);
	loadImages(normal_walk2, "../resources/picture/mouse/normal_mouse/normal_walk2/walk2_", 8, 1);
	loadImages(normal_die, "../resources/picture/mouse/normal_mouse/normal_die/die_", 13, 1);
	loadImages(Egg_b, "../resources/picture/food/Eggs_pitcher/Eggs/Egg_", 5, 1);
	loadImages(Egg_boom, "../resources/picture/food/Eggs_pitcher/Egg_boom/boom_", 6, 1);
	loadImages(Egg_pitcher, "../resources/picture/food/Eggs_pitcher/Egg_pitcher/", 26, 1);
	loadImages(Cherry_boom, "../resources/picture/food/Cherrys_tart/Cherry_boom/", 4, 2);
	loadImages(Cherry_tart, "../resources/picture/food/Cherrys_tart/Cherry_tart/", 9, 1);
	loadImages(hotpot, "../resources/picture/food/Hots_pot/Hotpot/", 13, 1);
	loadImages(hotpot_b, "../resources/picture/food/Hots_pot/Hotpot_b/", 42, 14);
}

void GUIManager::Draw_background(IMAGE img[])
{
	putimage(0, 0, &img[2]);
	putimage(90, 0, &img[3]);
	for (int i = 1; i <= 6; i++)
		putimage(90+93 * i, 0, &img[3]);
	putimage(745, 0, &img[4]);

	putimage(0, 120, &img[0]);
	for (int i = 0; i < 7;i++)
		this->drawAlpha(&img[1], 70, 160 + 75 * i);
}

void GUIManager::loadImages(IMAGE imgs[], char path[], int n, int begin)
{
	for (int i = 0; i < n; i++)
	{
		char tmpPath[200], frameNo[4];
		strcpy_s(tmpPath, 200, path);
		strcat(strcat(tmpPath, itoa(i + begin, frameNo, 10)), ".png");
		loadimage(&imgs[i], tmpPath);
	}   
}


void GUIManager::drawAlpha(IMAGE *picture, int picture_x, int picture_y)
{
    DWORD *dst = GetImageBuffer();    							// GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD *draw = GetImageBuffer(); 
	DWORD *src = GetImageBuffer(picture); 						//获取picture的显存指针
	int picture_width = picture->getwidth(); 					//获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); 					//获取picture的高度，EASYX自带
	int graphWidth = getwidth();       							//获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     							//获取绘图区的高度，EASYX自带
	int dstX = 0;    											//在显存里像素的角标                                                            
	for (int iy = 0; iy < picture_height; iy++)                 // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width;                 //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24);          //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16);            //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);               //G
			int sb = src[srcX] & 0xff;                          //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; 		//在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  	//公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         	//αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              	//αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void GUIManager::init()
{

	this->loading();
	initgraph(900, 680);
    setbkcolor(WHITE);
}

GUIManager::~GUIManager()
{
	closegraph();
}

int GUIManager::Place_positioning_x(int x, int deta_x)
{
	x = x - 120;
	x = x / 80;
	x = x * 80;
	x = x + 120;
	x = x - deta_x;
	return x;
}

int GUIManager::Place_positioning_y(int y, int deta_y)
{
	y = y - 130;
	y = y / 75;
	y = y * 75;
	y = y + 130;
	y = y - deta_y;
	return y;
}

pair<int, int> GUIManager::positioning(int x, int y)
{
	pair<int, int> a;
	a.first = -1;
	a.second = -1;
	if(x>=120&&x<=840&&y>=130&&y<=655)
	{
		x = x - 120;
		x = x / 80;
		y = y - 130;
		y = y / 75;
		a.first = x;
		a.second = y;
	}
	return a;
}