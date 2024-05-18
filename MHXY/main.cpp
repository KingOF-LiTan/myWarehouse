#define _CRT_SECURE_NO_WARNINGS 1
// demo1.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//



/*
1��C���� ������������ ����
2���������
3��������� ���ж� ѭ����
4������ �����ϣ�
5������
6���ṹ�� ���Զ����������ͣ�
7��ָ��
8�����ݽṹ  ��������ʽ�洢����
9���ļ�

�������  ���Ӳ��ӣ�������Ŀ�� ������Ա   ��Ŀ���鳤  ���������   ʱ�� ����   �����Ŀ��

��Ŀ���� ��������
����
���� ���ڲ�  ���⣩
��Ŀչʾ  �׷��ְ�
����
ά��

*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>  //��������    ��Ϸ��ͼ�� ��Ƶ���� OpenCV 
#include <SDL_ttf.h>
#include <SDL_image.h>
int main(int argc, char* argv[])
{
	//1����ʼ��SDL��
	SDL_Init(SDL_INIT_VIDEO);
	//2������SDL���ڣ�������ʾͼƬ��
	SDL_Window* window = SDL_CreateWindow("demo", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//���� λ�� x y  �ߴ� w h ��־
	//��ӡhelloworld
	printf("helloworld\n");
	//3������һ����Ⱦ�� ������ˢ��ͼƬ��
	SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //ʹ��Ӳ������
	//���� ͼƬ ���� �ֿ�ļ���
	//�����ֿⷽ��
	TTF_Init();

	//ͼƬ

	SDL_Texture* image = IMG_LoadTexture(Renderer, "login.jpg");
	SDL_Rect imagerect = { 0,0,640, 480 };
	SDL_RenderCopy(Renderer, image, NULL, &imagerect);

	//���� 
	TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
	if (!font)
	{
		printf("�޷���������");
	}
	SDL_Color textColor = { 255,255,255 };
	SDL_Surface* SurfaceMsg = TTF_RenderText_Solid(font, "helloworld", textColor);

	SDL_Texture* message = SDL_CreateTextureFromSurface(Renderer, SurfaceMsg);

	SDL_Rect textrect = { 0,0,640, 480 };
	SDL_RenderCopy(Renderer, message, NULL, &textrect);
	SDL_RenderPresent(Renderer);

	//SDL  �¼����� 
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
//�������� ͼƬ   ��ͼƬ ���ָ��Ƶ���Ⱦ����
SDL_RenderCopy

//ˢ��
SDL_RenderPresent


*/
