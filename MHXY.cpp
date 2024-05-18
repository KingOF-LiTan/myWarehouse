#define _CRT_SECURE_NO_WARNINGS 1

#include <SDL.h>
#include <bits/stdc++.h>
//#include "Renderer.h"
#include	<SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>


bool isMainMenu = true;
//全局变量

bool IsPointInsideRect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}
//判断是否在ui内点击
void RenderMainMenu(SDL_Renderer* Renderer) {
    // 绘制主菜单的内容
    // ...
    SDL_Texture* message = nullptr;  // 定义 message 变量
    SDL_Texture* img = nullptr;      // 定义 img 变量

    // 渲染图片
    img = IMG_LoadTexture(Renderer, "login.png");
    SDL_Rect imgRect = { 0, 0, 1920, 1080 };
    SDL_RenderCopy(Renderer, img, NULL, &imgRect);
    //logo
    SDL_Texture* logo = IMG_LoadTexture(Renderer, "logo.png");
    SDL_Rect logoRect = { 560, 70, 800, 600 };
    SDL_RenderCopy(Renderer, logo, NULL, &logoRect);
    //创建按钮 图片叠加
    SDL_Texture* loginButtomimage = IMG_LoadTexture(Renderer, "img//loginButton.png");
    SDL_Rect loginBtRect = { 770, 800, 420, 142 };
    SDL_RenderCopy(Renderer, loginButtomimage, NULL, &loginBtRect);
    //退出按钮
     SDL_Texture* outButtomimage = IMG_LoadTexture(Renderer, "img//out1.png");
    SDL_Rect outBtRect = { 790, 950, 386, 104 };
    SDL_RenderCopy(Renderer, outButtomimage, NULL, &outBtRect); 
    //启动！
     SDL_Texture* wjhimage = IMG_LoadTexture(Renderer, "img//start.png");
    SDL_Rect jhRect = { 100, 100, 567, 669 };
    SDL_RenderCopy(Renderer, wjhimage, NULL, &jhRect);
    // SDL_RenderCopy(Renderer, message, NULL, &textrect);
     //刷新界面 位于程序尾部
    SDL_RenderPresent(Renderer);
}//绘制主菜单
//主菜单
void RenderGamePlay(SDL_Renderer* Renderer) {
    // 绘制游戏界面的内容
    // ...
    SDL_Texture* message = nullptr;  // 定义 message 变量
    SDL_Texture* img = nullptr;      // 定义 img 变量

    // 渲染背景图片
    img = IMG_LoadTexture(Renderer, "img//warBg.png");
    SDL_Rect imgRect = { 0, 0, 1920, 1080 };
    SDL_RenderCopy(Renderer, img, NULL, &imgRect);

    // 存储游戏人物纹理
    SDL_Texture* loginButtomimage = IMG_LoadTexture(Renderer, "img//rong_0.png");
    SDL_Rect loginBtRect = { 233, 600, 71, 111 };
    SDL_RenderCopy(Renderer, loginButtomimage, NULL, &loginBtRect);

    // 加载敌人纹理
    char birdname[32];
    SDL_Texture* birdimage[10];
    SDL_Rect birdimageRect = { 100, 300, 142, 143 };
    for (int i = 0; i < 10; i++) {
        memset(birdname, 0, sizeof(birdname));
        sprintf_s(birdname, "img//enemy//enemy01_%d.png", i);
        birdimage[i] = IMG_LoadTexture(Renderer, birdname);
    }
    //敌人2
    char peoplename[32];
    SDL_Texture* peopleimage[10];
    SDL_Rect peopleimageRect = { 100, 600, 156, 141 };
    for (int i = 0; i < 10; i++) {
        memset(peoplename, 0, sizeof(peoplename));
        sprintf_s(peoplename, "img//enemy//enemy02_%d.png", i);
        peopleimage[i] = IMG_LoadTexture(Renderer, peoplename);
    }
    //敌人3
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
        // 渲染敌人
        SDL_Delay(60);
        SDL_RenderClear(Renderer);

        // 渲染背景图片
        img = IMG_LoadTexture(Renderer, "img//warBg.png");
        SDL_Rect imgRect = { 0, 0, 1920, 1080 };
        SDL_RenderCopy(Renderer, img, NULL, &imgRect);

        // 渲染敌人
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

    // 刷新界面 位于程序尾部
    SDL_RenderPresent(Renderer);
}
//游戏中
Mix_Chunk* soundEffect = nullptr; // 声明为全局变量

void Audio() {
    soundEffect = Mix_LoadWAV("music//war.wav");
    if (soundEffect == nullptr) {
        std::cout << "Failed to load sound effect: " << Mix_GetError() << std::endl;
    }
}

// 在 main 函数中初始化音效

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("mhxy", 100, 100, 1920, 1080, SDL_WINDOW_SHOWN);
    SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    // 初始化字体和纹理等
   TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
   // if (!font) {
  //      printf("字体载入失败");
   // }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // 处理初始化失败的情况
        std::cout << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        // 可以选择退出游戏或采取其他措施
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
                int channel = Mix_PlayChannel(-1, soundEffect, 0); // 播放音效一次，-1表示使用第一个可用的通道
                if (channel == -1) {
                    // 处理播放失败的情况
                    std::cout << "Failed to play sound effect: " << Mix_GetError() << std::endl;
                    // 可以选择退出游戏或采取其他措施
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
                


                // 处理游戏中的事件
            }
        }

        SDL_RenderPresent(Renderer);
    }

    // 游戏退出后的清理操作

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
