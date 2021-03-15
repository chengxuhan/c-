/*
 * @Author: ChengXuhan
 * @Date: 2021-03-13 11:31:09
 * @LastEditTime: 2021-03-13 14:55:35
 * @LastEditors: Please set LastEditors
 * @Description: ̰������Ŀ���հ档
 * @FilePath: \Program_Language\Program_snake\Main.c
 */
#define _CRT_SECURE_NO_WARNINGS
#include"snake.h"

int score = 0;//������
int kx = 0;//�û�����asdw����һ���������õ�������ֵ��
int ky = 0;
int lastx = 0;//��¼��β�����ꡣ
int lasty = 0;
int sleepnumber = 300;
int number = 0;


int main(int argc, char const *argv[])
{
    choose();

    //���ù�겻�ɼ���
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof( cci );
    cci.bVisible = FALSE;
    SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cci );//���ù�겻�ɼ���
    
    srand( time( NULL ) );//������������ӡ�

    initsnake();//��ʼ���ߡ�
    initfood();//��ʼ��ʳ�
    initwall();//��ǽ��
    initUI();//���ߺ�ʳ�
    playgame();

    system( "pause" );
    return 0;
}

void choose( void )
{   
    printf( "1��Basic model_����ģʽ��\n" );
    printf( "2��Medium model_�е�ģʽ��\n" );
    printf( "3��Top model_����ģʽ��\n" );
    printf( "5��Infernal model_����ģʽ��\n" );
    printf( "6��Sequential model_˳��ģʽ��\n" );
    printf( "7��exit_�˳�\n" );
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
    //���ߡ�
    COORD coord;//����ƶ���λ�á�

    coord.X = snake.body[ 0 ].X;
    coord.Y = snake.body[ 0 ].Y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( '@' );//����ͷ��

    for( int i = 1; i < snake.size; i++ )
    {
        coord.X = snake.body[ i ].X;
        coord.Y = snake.body[ i ].Y;
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
        putchar( '*' );//������
    }
    //ȥ����β��
    coord.X = lastx;
    coord.Y = lasty;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( ' ' );

    //��ʳ�
    coord.X = food.X;
    coord.Y = food.Y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
    putchar( '#' );

    //�������������꣬���⵲ס��
    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void playgame( void )
{
    char key = 'd';
    //�ж���ײǽ��
    while( ( ( snake.body[0].X >= 0 ) && ( snake.body[0].X <= WIDE ) ) && ( ( snake.body[0].Y >= 0 ) && ( snake.body[0].Y <= HIGH ) ) )
    {
        initUI();//�����ߡ�
        switch ( number )//չʾ�ɼ���
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

        //�����û��������� asdw
        if( kbhit() )//�ж��û��Ƿ񰴰��������������档
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
        

        //��ײ�����塣
        for ( size_t i = 1; i < snake.size; i++ )
        {
            if( ( snake.body[0].X == snake.body[i].X ) && ( snake.body[0].Y == snake.body[i].Y ) )
            {
                gameover();
                return;//��Ϸ������
            }
        }

        //��ͷײʳ��
        if( ( snake.body[0].X == food.X ) && ( snake.body[0].Y == food.Y ) )
        {
            initfood();//ʳ����ʧ��
            snake.size++;//����������
            score += 10;//�ӷ֣�
            if( ( number == 4 ) && ( sleepnumber >= 55 ) )
            {
                sleepnumber -= 10;//���١�
            }
        }

        lastx = snake.body[ snake.size - 1 ].X;//�洢��β���ꡣ
        lasty = snake.body[ snake.size - 1 ].Y;

        //���ƶ���ǰһ���������һ�����帳ֵ��
        for ( size_t i = snake.size - 1; i > 0; i-- )
        {
            snake.body[i].X = snake.body[ i-1 ].X;
            snake.body[i].Y = snake.body[ i-1 ].Y; 
        }
        snake.body[0].X += kx;//��ͷ��������û�����任���޸ġ�
        snake.body[0].Y += ky;
        
        Sleep( sleepnumber );
        //������
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