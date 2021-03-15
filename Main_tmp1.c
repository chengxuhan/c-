/*
 * @Author: ChengXuhan
 * @Date: 2021-03-12 21:56:16
 * @LastEditTime: 2021-03-13 11:27:57
 * @LastEditors: Please set LastEditors
 * @Description: 贪吃蛇项目测试版。
 * @FilePath: \Program_Language\Program_snake\Main.c
 */
#define _CRT_SECURE_NO_WARNINGS
#include"snake.h"

int score = 0;//分数。
int kx = 0;//用户按下asdw任意一个按键所得到的坐标值。
int ky = 0;


int main(int argc, char const *argv[])
{
    
    srand( time( NULL ) );//播种随机数种子。

    initsnake();//初始化蛇。
    initfood();//初始化食物。
    initUI();//画蛇和食物。
    playgame();

    //打印分数。

    system( "pause" );
    return 0;
}

void initsnake( void )
{
    snake.size = 2;

    snake.body[0].X = WIDE / 2;
    snake.body[0].Y = HIGH / 2;

    snake.body[1].X = WIDE / 2 - 1;
    snake.body[1].Y = HIGH / 2;
}

void initfood( void )
{
    food.X = rand() % WIDE;
    food.Y = rand() % HIGH;
}

void initUI( void )
{
    //画蛇。
    COORD coord;//光标移动的位置。

    coord.X = snake.body[ 0 ].X;
    coord.Y = snake.body[ 0 ].Y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( '@' );//画蛇头。

    for( int i = 1; i < snake.size; i++ )
    {
        coord.X = snake.body[ i ].X;
        coord.Y = snake.body[ i ].Y;
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
        putchar( '*' );//画蛇身。
    }

    //画食物。
    coord.X = food.X;
    coord.Y = food.Y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( '#' );

    //设置最后的输出光标，避免挡住。
    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void playgame( void )
{
    char key = 'd';
    //判断蛇撞墙。
    while( ( ( snake.body[0].X >= 0 ) && ( snake.body[0].X < WIDE ) ) && ( ( snake.body[0].Y >= 0 ) && ( snake.body[0].Y < WIDE ) ) )
    {
        initwall();//画墙.
        initUI();//更新蛇。

        //接受用户按键输入 asdw
        if( kbhit() )//判断用户是否按按键。按键返回真。
        {
            key = getch();
        }

        switch ( key )
        {
            case 'w':
                kx = 0; ky = -1;
                break;
            case 'a':
                kx = -1; ky = 0;
                break;
            case 's':
                kx = 0; ky = 1;
                break;
            case 'd':
                kx = 1; ky = 0;
                break;
            default:
                break;
        }
        

        //蛇撞到身体。
        for ( size_t i = 1; i < snake.size; i++ )
        {
            if( ( snake.body[0].X == snake.body[i].X ) && ( snake.body[0].Y == snake.body[i].Y ) )
            return;//游戏结束。
        }

        //蛇头撞食物
        if( ( snake.body[0].X == food.X ) && ( snake.body[0].Y == food.Y ) )
        {
            initfood();//食物消失；
            snake.size++;//身体增长；
            score += 10;//加分；
            //加速。
        }

        //蛇移动。前一截身体给后一节身体赋值。
        for ( size_t i = snake.size - 1; i > 0; i-- )
        {
            snake.body[i].X = snake.body[ i-1 ].X;
            snake.body[i].Y = snake.body[ i-1 ].Y; 
        }
        snake.body[0].X += kx;//蛇头坐标根据用户坐标变换所修改。
        snake.body[0].Y += ky;
        
        Sleep( 100 );
        //清屏。
        system( "cls" );
    }
    return;
}

void initwall( void )
{
    for (size_t i = 0; i <= HIGH; i++)
    {
        for( int j = 0; j <= WIDE; j++ )
            if( j == WIDE )
                printf( "|" );
            else if( i == HIGH )
                printf( "_" );
            else
                printf( " " );
        printf( "\n" );
    }
    
}