#define _CRT_SECURE_NO_WARNINGS 1
// demo1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



/*
1、C基础 基本数据类型 变量
2、输入输出
3、控制语句 （判断 循环）
4、数组 （复合）
5、函数
6、结构体 （自定义数据类型）
7、指针
8、数据结构  （链表（链式存储））
9、文件

需求分析  （接不接，成立项目组 分配人员   项目组组长  需求分析书   时间 内容   拆解项目，

项目开发 分配任务
编码
测试 （内测  公测）
项目展示  甲方爸爸
上线
维护

*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>  //第三方库    游戏（图像 音频处理） OpenCV 
#include <SDL_ttf.h>
#include <SDL_image.h>
int main(int argc, char* argv[])
{
	//1、初始化SDL库
	SDL_Init(SDL_INIT_VIDEO);
	//2、创建SDL窗口（可以显示图片）
	SDL_Window* window = SDL_CreateWindow("demo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//标题 位置 x y  尺寸 w h 标志
	//打印helloworld
	printf("helloworld\n");
	//3、创建一个渲染器 （绘制刷新图片）
	SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //使用硬件加速
	//进行 图片 或者 字库的加载
	//加载字库方法
	TTF_Init();

	//图片

	SDL_Texture* image = IMG_LoadTexture(Renderer, "login.jpg");
	SDL_Rect imagerect = { 0,0,640, 480 };
	SDL_RenderCopy(Renderer, image, NULL, &imagerect);

	//字体 
	TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
	if (!font)
	{
		printf("无法加载字体");
	}
	SDL_Color textColor = { 255,255,255 };
	SDL_Surface* SurfaceMsg = TTF_RenderText_Solid(font, "helloworld", textColor);

	SDL_Texture* message = SDL_CreateTextureFromSurface(Renderer, SurfaceMsg);

	SDL_Rect textrect = { 0,0,640, 480 };
	SDL_RenderCopy(Renderer, message, NULL, &textrect);
	SDL_RenderPresent(Renderer);

	//SDL  事件方法 
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}


	return 0;
}


/*
SDL_Init
SDL_CreateWindow
SDL_CreateRenderer
//加载文字 图片   把图片 文字复制到渲染器中
SDL_RenderCopy

//刷新
SDL_RenderPresent


*/
