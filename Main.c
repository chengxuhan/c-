/*
 * @Author: ChengXuhan
 * @Date: 2021-03-13 11:31:09
 * @LastEditTime: 2021-03-13 14:55:35
 * @LastEditors: Please set LastEditors
 * @Description: 贪吃蛇项目最终版。
 * @FilePath: \Program_Language\Program_snake\Main.c
 */
#define _CRT_SECURE_NO_WARNINGS
#include"snake.h"

int score = 0;//分数。
int kx = 0;//用户按下asdw任意一个按键所得到的坐标值。
int ky = 0;
int lastx = 0;//记录蛇尾的坐标。
int lasty = 0;
int sleepnumber = 300;
int number = 0;


int main(int argc, char const *argv[])
{
    choose();

    //设置光标不可见。
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof( cci );
    cci.bVisible = FALSE;
    SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cci );//设置光标不可见。
    
    srand( time( NULL ) );//播种随机数种子。

    initsnake();//初始化蛇。
    initfood();//初始化食物。
    initwall();//画墙。
    initUI();//画蛇和食物。
    playgame();

    system( "pause" );
    return 0;
}

void choose( void )
{   
    printf( "1、Basic model_基础模式。\n" );
    printf( "2、Medium model_中等模式。\n" );
    printf( "3、Top model_困难模式。\n" );
    printf( "5、Infernal model_地狱模式。\n" );
    printf( "6、Sequential model_顺序模式。\n" );
    printf( "7、exit_退出\n" );
    printf( "Please choose number:\n" );
    scanf( "%d", &number );
    system( "cls" );

    switch ( number )
    {
        case 1:
            sleepnumber = 250;
            break;
        case 2:
            sleepnumber = 150;
            break;
        case 3:
            sleepnumber = 50;
            break;
        case 4:
            sleepnumber = 20;
            break;
        case 5:
            sleepnumber = 300;
            break;
        case 6:
            exit( -1 );
            break;
        
        default:
            printf( "Please enter right number!\n" );
            exit( -1 );
            break;
    }
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
    //去除蛇尾。
    coord.X = lastx;
    coord.Y = lasty;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( ' ' );

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
    while( ( ( snake.body[0].X >= 0 ) && ( snake.body[0].X <= WIDE ) ) && ( ( snake.body[0].Y >= 0 ) && ( snake.body[0].Y <= HIGH ) ) )
    {
        initUI();//更新蛇。
        switch ( number )//展示成绩。
    {
        case 1:
            showscore1();
            break;
        case 2:
            showscore2();
            break;
        case 3:
            showscore3();
            break;
        case 4:
            showscore4();
            break;
        case 5:
            showscore();
            break;
        
        default:
            printf( "Please enter right number!\n" );
            exit( -1 );
            break;
    }

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
            {
                gameover();
                return;//游戏结束。
            }
        }

        //蛇头撞食物
        if( ( snake.body[0].X == food.X ) && ( snake.body[0].Y == food.Y ) )
        {
            initfood();//食物消失；
            snake.size++;//身体增长；
            score += 10;//加分；
            if( ( number == 4 ) && ( sleepnumber >= 55 ) )
            {
                sleepnumber -= 10;//加速。
            }
        }

        lastx = snake.body[ snake.size - 1 ].X;//存储蛇尾坐标。
        lasty = snake.body[ snake.size - 1 ].Y;

        //蛇移动。前一截身体给后一节身体赋值。
        for ( size_t i = snake.size - 1; i > 0; i-- )
        {
            snake.body[i].X = snake.body[ i-1 ].X;
            snake.body[i].Y = snake.body[ i-1 ].Y; 
        }
        snake.body[0].X += kx;//蛇头坐标根据用户坐标变换所修改。
        snake.body[0].Y += ky;
        
        Sleep( sleepnumber );
        //清屏。
    }
    gameover();
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

void gameover( void )
{
    COORD coord;
    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "\tGame Over!\n\n\n\n\n\n" );
}

void showscore1( void )
{
    COORD coord;
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 3;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "W is up!\tS is down!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "A is left!\tD is right!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Your score: %d", score );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 ;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Now difficulty: Basic" );

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void showscore2( void )
{
    COORD coord;
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 3;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "W is up!\tS is down!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "A is left!\tD is right!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Your score: %d", score );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 ;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Now difficulty: Medium" );

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void showscore3( void )
{
    COORD coord;
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 3;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "W is up!\tS is down!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "A is left!\tD is right!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Your score: %d", score );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 ;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Now difficulty: Top" );

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void showscore( void )
{
    COORD coord;
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 3;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "W is up!\tS is down!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "A is left!\tD is right!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Your score: %d", score );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 ;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Now difficulty: %d", ( 300 - sleepnumber ) / 25 );

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void showscore4( void )
{
    COORD coord;
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 3;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "W is up!\tS is down!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "A is left!\tD is right!\n" );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 - 1;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Your score: %d", score );
    coord.X = WIDE / 4 + WIDE;
    coord.Y = HIGH / 2 ;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    printf( "Now difficulty: Infernal" );

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}