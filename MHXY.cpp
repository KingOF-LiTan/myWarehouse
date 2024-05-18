#define _CRT_SECURE_NO_WARNINGS 1

#include <SDL.h>
#include <bits/stdc++.h>
//#include "Renderer.h"
#include	<SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>


bool isMainMenu = true;
//ȫ�ֱ���

bool IsPointInsideRect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}
//�ж��Ƿ���ui�ڵ��
void RenderMainMenu(SDL_Renderer* Renderer) {
    // �������˵�������
    // ...
    SDL_Texture* message = nullptr;  // ���� message ����
    SDL_Texture* img = nullptr;      // ���� img ����

    // ��ȾͼƬ
    img = IMG_LoadTexture(Renderer, "login.png");
    SDL_Rect imgRect = { 0, 0, 1920, 1080 };
    SDL_RenderCopy(Renderer, img, NULL, &imgRect);
    //logo
    SDL_Texture* logo = IMG_LoadTexture(Renderer, "logo.png");
    SDL_Rect logoRect = { 560, 70, 800, 600 };
    SDL_RenderCopy(Renderer, logo, NULL, &logoRect);
    //������ť ͼƬ����
    SDL_Texture* loginButtomimage = IMG_LoadTexture(Renderer, "img//loginButton.png");
    SDL_Rect loginBtRect = { 770, 800, 420, 142 };
    SDL_RenderCopy(Renderer, loginButtomimage, NULL, &loginBtRect);
    //�˳���ť
     SDL_Texture* outButtomimage = IMG_LoadTexture(Renderer, "img//out1.png");
    SDL_Rect outBtRect = { 790, 950, 386, 104 };
    SDL_RenderCopy(Renderer, outButtomimage, NULL, &outBtRect); 
    //������
     SDL_Texture* wjhimage = IMG_LoadTexture(Renderer, "img//start.png");
    SDL_Rect jhRect = { 100, 100, 567, 669 };
    SDL_RenderCopy(Renderer, wjhimage, NULL, &jhRect);
    // SDL_RenderCopy(Renderer, message, NULL, &textrect);
     //ˢ�½��� λ�ڳ���β��
    SDL_RenderPresent(Renderer);
}//�������˵�
//���˵�
void RenderGamePlay(SDL_Renderer* Renderer) {
    // ������Ϸ���������
    // ...
    SDL_Texture* message = nullptr;  // ���� message ����
    SDL_Texture* img = nullptr;      // ���� img ����

    // ��Ⱦ����ͼƬ
    img = IMG_LoadTexture(Renderer, "img//warBg.png");
    SDL_Rect imgRect = { 0, 0, 1920, 1080 };
    SDL_RenderCopy(Renderer, img, NULL, &imgRect);

    // �洢��Ϸ��������
    SDL_Texture* loginButtomimage = IMG_LoadTexture(Renderer, "img//rong_0.png");
    SDL_Rect loginBtRect = { 233, 600, 71, 111 };
    SDL_RenderCopy(Renderer, loginButtomimage, NULL, &loginBtRect);

    // ���ص�������
    char birdname[32];
    SDL_Texture* birdimage[10];
    SDL_Rect birdimageRect = { 100, 300, 142, 143 };
    for (int i = 0; i < 10; i++) {
        memset(birdname, 0, sizeof(birdname));
        sprintf_s(birdname, "img//enemy//enemy01_%d.png", i);
        birdimage[i] = IMG_LoadTexture(Renderer, birdname);
    }
    //����2
    char peoplename[32];
    SDL_Texture* peopleimage[10];
    SDL_Rect peopleimageRect = { 100, 600, 156, 141 };
    for (int i = 0; i < 10; i++) {
        memset(peoplename, 0, sizeof(peoplename));
        sprintf_s(peoplename, "img//enemy//enemy02_%d.png", i);
        peopleimage[i] = IMG_LoadTexture(Renderer, peoplename);
    }
    //����3
    char people2name[32];
    SDL_Texture* people2image[10];
    SDL_Rect people2imageRect = { 300, 400,156, 141 };
    for (int i = 0; i < 10; i++) {
        memset(people2name, 0, sizeof(people2name));
        sprintf_s(people2name, "img//enemy//enemy03_%d.png", i);
        people2image[i] = IMG_LoadTexture(Renderer, people2name);
    }
    SDL_Event event;
    bool quit = false;
    int num = 0;
    while (!quit) {
        // ��Ⱦ����
        SDL_Delay(60);
        SDL_RenderClear(Renderer);

        // ��Ⱦ����ͼƬ
        img = IMG_LoadTexture(Renderer, "img//warBg.png");
        SDL_Rect imgRect = { 0, 0, 1920, 1080 };
        SDL_RenderCopy(Renderer, img, NULL, &imgRect);

        // ��Ⱦ����
        SDL_RenderCopy(Renderer, birdimage[num], NULL, &birdimageRect);
        SDL_RenderCopy(Renderer, peopleimage[num], NULL, &peopleimageRect);
        SDL_RenderCopy(Renderer, people2image[num], NULL, &people2imageRect);
        num++;
        if (num == 10) {
            num = 0;
        }
        SDL_RenderPresent(Renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // ˢ�½��� λ�ڳ���β��
    SDL_RenderPresent(Renderer);
}
//��Ϸ��
Mix_Chunk* soundEffect = nullptr; // ����Ϊȫ�ֱ���

void Audio() {
    soundEffect = Mix_LoadWAV("music//war.wav");
    if (soundEffect == nullptr) {
        std::cout << "Failed to load sound effect: " << Mix_GetError() << std::endl;
    }
}

// �� main �����г�ʼ����Ч

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("mhxy", 100, 100, 1920, 1080, SDL_WINDOW_SHOWN);
    SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    // ��ʼ������������
   TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
   // if (!font) {
  //      printf("��������ʧ��");
   // }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // �����ʼ��ʧ�ܵ����
        std::cout << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        // ����ѡ���˳���Ϸ���ȡ������ʩ
    }
    SDL_Event event;
    bool quit = false;
    SDL_Rect loginBtRect = { 770, 800, 420, 142 };
    SDL_Rect outBtRect = { 790, 950, 386, 104 };
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            if (isMainMenu) {
                RenderMainMenu(Renderer);
                int channel = Mix_PlayChannel(-1, soundEffect, 0); // ������Чһ�Σ�-1��ʾʹ�õ�һ�����õ�ͨ��
                if (channel == -1) {
                    // ������ʧ�ܵ����
                    std::cout << "Failed to play sound effect: " << Mix_GetError() << std::endl;
                    // ����ѡ���˳���Ϸ���ȡ������ʩ
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;

                    if (IsPointInsideRect(x,y,loginBtRect)) {
                        isMainMenu = false;
                    }
                    if (IsPointInsideRect(x, y, outBtRect)) {
                        quit = true;
                        //SDL_DestroyRenderer(Renderer);
                        SDL_DestroyWindow(window);
                        TTF_Quit();
                        SDL_Quit();
                    }
                }
            }
            else {
                RenderGamePlay(Renderer);
                


                // ������Ϸ�е��¼�
            }
        }

        SDL_RenderPresent(Renderer);
    }

    // ��Ϸ�˳�����������

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
