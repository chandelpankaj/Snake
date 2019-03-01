#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
int snakeh_x,snakeh_y,snaket_x,snaket_y,direction=1,out=0,highscore,x,y,length=20,breadth=60,mf=20,head1x,head1y,head2x,head2y,headx[1120],heady[1120],len=3,score=0;
long int pause,n,distance;
time_t t;
char board[200][200],menu[5][76]={"\t\tUse arrows keys (or) 'w','s' to move up/down. Press Enter key to Select.","   Play Game","   Select Level","   Read Instructions","   Exit"},
YesNo[3][75]={"\tDo you really want to Quit?", "\tYes", "\tNo"},
game_text[5][25]={"####  ###  #####  ####","#     # #  # # #  #   ","# ##  ###  # # #  ### ","#  #  # #  #   #  #   ","####  # #  #   #  ####"},
over_text[5][25]={"####  #   #  ####  ####","#  #  #   #  #     #  #","#  #  #   #  ###   ####","#  #   # #   #     # # ","####    #    ####  #  #"};
void print_menu();
void select_choice_menu();
void GotoXY();
void set_screen();
void start_game();
void show_levels();
void print_board();
void print_score();
void go_down();
void go_left();
void go_right();
void go_up();
void produce_food();
int check_food();
int check_bite();
void move_snake();
void update_board();
void set_snake();
void give_yes_no();
void check_key_pressed();
//to print the exit screen
void give_yes_no()
{
    int i,selected=0,element,choice=0;
        system("cls");
        GotoXY(0,0);
        for(i=0;i<3;i++)
        {
            printf("%s\n",YesNo[i]);
        }
        GotoXY(4,1);
        printf("->");
        while(selected==0)
        {
            switch(getch())
            {
            case 'w':
                choice=choice+1;
                element= choice%2+1;
                GotoXY(4,element%2+1);
                printf("  ");
                GotoXY(4,element);
                printf("->");
            break;
            case 's':
                choice= choice+1;
                element= choice%2+1;
                GotoXY(4,element%2+1);
                printf("  ");
                GotoXY(4,element);
                printf("->");
            break;
            case 13:
                element=choice%2+1;
                if(element==1)
                exit(0);
                else
                selected=1;
            }
        }
}

//to set the initial snake position
void set_snake()
{
    int i;

    for(i=2;i<5;i++)
	{
		board[3][i]='o';
	}

	snakeh_x=3;
	snakeh_y=4;
	snaket_x=3;
	snaket_y=2;
	headx[2]=3;
	headx[1]=3;
	heady[2]=3;
	heady[1]=4;
	headx[0]=3;
	heady[0]=3;
	board[snakeh_x][snakeh_y]='o';
}

void GotoXY(int i,int j)
{
    COORD cord;
    cord.X=i;
    cord.Y=j;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),cord);
}

void print_score()
{
    GotoXY(76,2);
    printf("%d",score);
    GotoXY(76,3);
    printf("%d",len);
}
//to print the levels menu
void show_levels()
{
    int i;
    length=8;
    breadth=27;
    start_game(1);
    for(i=0;i<length;i++)
	{
	    GotoXY(0,i);
		printf("%s",board[i]);
	}
    GotoXY(10,8);
    printf("(1)");
    start_game(2);
    for(i=0;i<length;i++)
	{
	    GotoXY(30,i);
		printf("%s",board[i]);
	}
	GotoXY(42,8);
    printf("(2)");

	start_game(3);
    for(i=0;i<length;i++)
	{
	    GotoXY(60,i);
		printf("%s",board[i]);
	}
	GotoXY(72,8);
    printf("(3)");

	start_game(4);
    for(i=0;i<length;i++)
	{
	    GotoXY(90,i);
		printf("%s",board[i]);
	}
	GotoXY(102,8);
    printf("(4)");
    start_game(5);
    for(i=0;i<length;i++)
	{
	    GotoXY(0,i+10);
		printf("%s",board[i]);
	}
	GotoXY(10,19);
    printf("(5)");

    start_game(6);
    for(i=0;i<length;i++)
	{
	    GotoXY(30,i+10);
		printf("%s",board[i]);
	}
	GotoXY(42,19);
    printf("(6)");

    start_game(7);
    for(i=0;i<length;i++)
	{
	    GotoXY(60,i+10);
		printf("%s",board[i]);
	}
	GotoXY(72,19);
    printf("(7)");
	length=20;
	breadth=60;
	GotoXY(2,22);
	printf("Press Esc to go back.");
	GotoXY(2,21);
	printf("Enter the level you want to Play:  ");
	i=getche();
	if(i==27)
    {
        system("cls");
        print_menu();
        select_choice_menu();
    }
    else{
	system("cls");
    start_game(i-48);
    }
}

void print_menu()
{
    int i,j;
    for(i=0;i<5;i++)
    {
        printf("%s    \n",menu[i]);
    }
}

//to select the choice up/down
void select_choice_menu()
{
    int b=1,elem=0,option=0;

    GotoXY(0,1);
    printf("-> %s",menu[1]);
    GotoXY(3,4);
    while(option==0)
    {
        switch(getch())
        {
        case 72:
        case 'w':
            elem=elem+3;
            b=elem%4+1;
            GotoXY(0,0);
            print_menu();
            GotoXY(0,b);
            printf("-> %s",menu[b]);
            break;
        case 's':
        case 80:
            elem++;
            b=elem%4+1;
            GotoXY(0,0);
            print_menu();
            GotoXY(0,b);
            printf("-> %s",menu[b]);
            break;
        case 13:
            option=1;
        }
    }
    set_screen(b);
}

void set_screen(int option)
{
    system("cls");
    switch(option)
    {
    case 1:
        start_game(0);
        break;
    case 2:
        printf("Enter level (1 to 9)\n");
        show_levels();
        break;
    case 3:
            system("cls");
            GotoXY(20,3);
            printf("Use arrow keys (or) 'w','a','s','d' to change the direction of snake.");
            GotoXY(20,5);
            printf("Press 'p' or  Enter  key  anytime  to  Pause the Game.");
            GotoXY(20,6);
            printf("Press any key to resume the Game");
            GotoXY(20,8);
            printf("Don't let the Snake hit the walls or bite itself.");
            GotoXY(20,10);
            printf("Press ESC anytime to Exit Game.");
            getch();
            system("cls");
            print_menu();
            select_choice_menu();
            break;
    case 4:
            give_yes_no();
            system("cls");
            print_menu();
            select_choice_menu();
    }
}

//to store user entered level data in the board array
void start_game(int level)
{
    int i,j;
    n=150000;
    for(i=0;i<length;i++)
	{
		for(j=0;j<breadth;j++)
		{
		if(i==0||i==(length-1)||j==0||j==(breadth-1))
		board[i][j]='I';
		else
		board[i][j]=' ';
		}
	}
	switch(level)
	{
    case 2:
        for(j=breadth/4;j<(breadth-breadth/4);j++)
        {
            board[length/3][j]='I';
            board[length-length/3][j]='I';
            mf=21;
        }
        mf=22;
        break;
    case 4:
        start_game(2);
        for(j=length/3;j<length-length/3;j++)
        {
            board[j][breadth/2]='I';
            board[j][(breadth/2)+1]='I';
        }
        board[length/2][breadth/2]=' ';
        board[length/2][breadth/2+1]=' ';
        mf=24;
        n=160000;
        break;
    case 5:
        for(j=length/3;j<=length-length/3;j++)
        {
            board[j][breadth/4]='I';
            board[j][breadth-breadth/4]='I';
        }
        for(j=breadth/4;j<=breadth-breadth/4;j++)
        {
            board[length/3][j]='I';
            board[length-length/3][j]='I';
            if(j==breadth/2-2)
            j=j+3;
        }
        mf=29;
        n=170000;
        break;
    case 6:
        for(i=1;i<length-1;i++)
        {
            for(j=1;j<breadth-1;j++)
            {
                if((i==length/4||i==length-2*(length/5))&&((j>breadth/5&&j<(breadth/5)+breadth/5)||j>breadth-2*(breadth/5)&&j<breadth-breadth/5))
                    board[i][j]='I';
                if((i==2*(length/5)||i==length-length/5)&&(j>breadth/3)&&(j<breadth-breadth/3))
                    board[i][j]='I';
            }
        }
        mf=37;
        n=180000;
        break;
    case 7:
        start_game(5);
        for(i=1;i<length-1;i++)
        {
            for(j=1;j<breadth-1;j++)
            {
                if((i>=length/10&&i<=length-length/10-1&&i!=length/2&&i!=length/2-1)&&(j==breadth/7||j==breadth-breadth/7))
                   board[i][j]='I';
                if((i==length/10||i==length-length/10-1)&&((j>breadth/7&&j<breadth/7+8)||(j<breadth-breadth/7&&j>breadth-breadth/7-8)))
                    board[i][j]='I';
            }

        }
        mf=45;
        n=200000;
        break;
    case 3:
        for(i=length/5;i<length-length/5;i++)
        {
            for(j=breadth/5;j<breadth-breadth/5;j++)
            {
                if((i>=length/5&&i<=length-length/5-1&&i!=length/2&&i!=length/2-1)&&(j==breadth/5||j==breadth-breadth/5-1))
                   board[i][j]='I';
                if((i==length/5||i==length-length/5-1)&&((j>breadth/5&&j<breadth/5+breadth/5)||(j<breadth-breadth/5&&j>breadth-breadth/5-breadth/5)))
                    board[i][j]='I';
            }

        }
        mf=24;
        n=160000;
	}
}
//to change the direction of snake
void go_up()
{
	if(direction!=2)
	direction=0;
}
void go_down()
{
	if(direction!=0)
	direction=2;
}
void go_right()
{
	if(direction!=3)
	direction=1;
}
void go_left()
{
	if(direction!=1)
	direction=3;
}
void produce_food()
{
	x=rand()%length;
	y=rand()%breadth;
	if(board[x][y]==' '&&x!=0)
    {
	board[x][y]='.';
	GotoXY(y,x);
	printf("%c\a",162);
	GotoXY(0,0);
    }
	else
	produce_food();
}
int check_food()
{
	if(board[snakeh_x][snakeh_y]=='.')
	{
		len++;
		produce_food();
		n=n+250;
		score=score+mf+len/10;
		print_score();
		return 1;
	}
	else return 0;
}
//to check whether snake has hit the wall or itself
int check_bite()
{
	if(board[snakeh_x][snakeh_y]=='I'||board[snakeh_x][snakeh_y]=='o')
        out=1;
	else
        out=0;
    return out;
}
//to print the new position of snake
void move_snake()
{
    int a,i;
    a=check_food();
    if(check_bite()==0)
    {
    board[headx[0]][heady[0]]='o';
    GotoXY(heady[0],headx[0]);
    printf("%c",176);
    board[snakeh_x][snakeh_y]='O';
    GotoXY(snakeh_y,snakeh_x);
    printf("%c",178);
    board[snaket_x][snaket_y]=' ';
    GotoXY(snaket_y,snaket_x);
    printf(" ");
    }
    if(a==1)
    {
        GotoXY(heady[0],headx[0]);
        printf("%c",177);
    }

    snaket_x=headx[len-1];
        snaket_y=heady[len-1];
        headx[0]=snakeh_x;
        heady[0]=snakeh_y;
        for(i=0;i<(len-1);i++)
        {
            headx[len-i-1]=headx[len-i-2];
            heady[len-i-1]=heady[len-i-2];
        }
}
//to change the position of snake only in array
void update_board()
{
	if(direction==0)
	{
	    pause=n;
		snakeh_x=snakeh_x-1;
	}
		if(direction==1)
	{
	    pause=0.6*n;
		snakeh_y=snakeh_y+1;
	}
		if(direction==2)
	{
	    pause=n;
		snakeh_x=snakeh_x+1;
	}
		if(direction==3)
	{
	    pause=0.6*n;
		snakeh_y=snakeh_y-1;
	}
}
void print_board()
{
	int i,j;
	GotoXY(0,0);
	for(i=0;i<length;i++)
	{
	    for(j=0;j<breadth;j++)
        {
            if(board[i][j]=='.')
                printf("%c",162);
            else if(board[i][j]=='o')
                printf("%c",176);
            else if(board[i][j]=='O')
                printf("%c",178);
            else if(board[i][j]=='I')
                printf("%c",219);
            else
		printf("%c",board[i][j]);
        }
        printf("\n");
    }

}
void check_key_pressed()
{
    if(kbhit())
		{
		    //switch case to detect the direction of snake from user start here
            switch(getch())
            {
                case 72:
                case 'w':
                case 'W':
                    go_up();
                    break;
                case 80:
                case 's':
                case 'S':
                    go_down();
                    break;
                case 77:
                case 'd':
                case 'D':
                    go_right();
                    break;
                case 75:
                case 'a':
                case 'A':
                    go_left();
                    break;
                case 13:
                case 'p':
                    getch();
                    break;
                case 27:
                    give_yes_no();
                    print_board();
                    GotoXY(62,1);
                    printf("High Score  : %d",highscore);
                    GotoXY(62,2);
                    printf("SCORE       : %d",score);
                    GotoXY(62,3);
                    printf("Snake Length: %d",len);
                    GotoXY(62,4);
                    printf("Distance travelled: %ld",distance);
                    break;
                }
                //switch case ends here
            }

}
void main()
{

	int i=0,j;
	srand((unsigned) time(&t));
	FILE *fp,*fp1;
	start:
	    system("cls");
        len=3;
	    out=0;
	    direction=1;
	    distance=0;
	    for(i=0;i<length;i++)
        {
            for(j=0;j<breadth;j++)
            {
                board[i][j]=' ';
            }
        }
        i=0;
	fp=fopen("highscore.dat","r");
	if(fp==NULL)
    {
        fp1=fopen("highscore.dat","w");
        fprintf(fp1,"%d",0);
        fclose(fp1);
    }
    else
	fscanf(fp,"%d",&highscore);
	fclose(fp);
    print_menu();
    GotoXY(2,4);
    select_choice_menu();
    set_snake();
	print_board();
	produce_food();

	GotoXY(62,1);
	printf("High Score  : %d",highscore);
	GotoXY(62,2);
    printf("SCORE       : 0");
    GotoXY(62,3);
    printf("Snake Length: 3");
    GotoXY(62,4);
    printf("Distance travelled: 0");

    GotoXY(breadth,length);

	switch(getch())
	{
    case 72:
    case 'w':
        direction=0;
        break;
    case 's':
        direction=2;
        break;
	}
	//loop starts
	while(out==0)
	{
	    distance++;
	    n=n-5;
	    GotoXY(82,4);
	    printf("%ld",distance);
		usleep(pause);
        check_key_pressed();

        update_board();
        move_snake();

	}
        // loop ends here

    for(i=0;i<5;i++)        //to print the "Game Over" text
    {
        GotoXY(9,i+5);
        printf("\t\t\t\t");
        GotoXY(12,i+5);
        printf("%s",game_text[i]);
    }
    for(i=0;i<5;i++)
    {
        GotoXY(17,i+11);
        printf("\t\t\t\t");
        GotoXY(20,i+11);
        printf("%s",over_text[i]);
    }
    if(score>highscore)
    {
        fp=fopen("highscore.dat","w");
        fprintf(fp,"%d",score);
        fclose(fp);
        system("cls");
        GotoXY(5,10);
        printf("Conratulations! You made the High score.");
    }

	GotoXY(0,length);
	getch();
	goto start;
}
