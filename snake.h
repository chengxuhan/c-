/*
 * @Author: ChengXuhan
 * @Date: 2021-03-13 07:31:49
 * @LastEditTime: 2021-03-13 14:48:32
 * @LastEditors: Please set LastEditors
 * @Description: 贪吃蛇头文件。
 * @FilePath: \Program_Language\Program_snake\snake.h
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

#define WIDE 60//宽度。
#define HIGH 20//高度。

//定义蛇一个身体的对象：
struct BODY
{//坐标。
    int X;
    int Y;
};

struct SNAKE
{
    struct BODY body[ WIDE * HIGH ];
    int size;
    
} snake;

struct FOOD
{
    int X;
    int Y;
} food;

void choose( void );//选择模式。
void initsnake( void );//定义初始化蛇函数。
void initfood( void );//定义初始化食物函数。
void initUI( void );//初始化界面控件。
void playgame( void );//启动游戏。
void initwall( void );//画墙。
void gameover( void );//结束。
void showscore( void );//顺序模式。
void showscore1( void );//基础模式
void showscore2( void );//中等。
void showscore3( void );//困难模式
void showscore4( void );//地狱模式。
