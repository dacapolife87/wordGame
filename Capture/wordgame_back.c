#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#define INITIAL_LIFE 5
#define MIN_LEVEL 1
#define MAX_LEVEL 10
#define TRUE 1
#define FALSE 0
#define MAXCHR 32
#define HLFCHR 16
#define SHORTTIME 50000000
#define LONGTIME SHORTTIME*2
#define FAIL	0
#define SUCCESS 1
#define JUSTEND 2
static char lcdDev[] ="/dev/CLCD";
static int lcdFd=(-1);
typedef struct{
    char* quiz[10];
    int choice;
    int playable_flag;
    int levelup_flag;
}GameType;
typedef struct{
    int level, life;
    char* word;
}PlayerType;


int start_game();
void initialize_game(PlayerType*, GameType*);
void display_game(PlayerType*, GameType*);
int check_status(PlayerType*, GameType*);
int end_game(int);
void input_word(char**);
void update_status(PlayerType*, GameType*,int);
int check_word(char*,char*);
void fill_quiz(GameType*);
void SHOW_start_game();
void SHOW_end_game(int);
void SHOW_intro();
void printlcd(char *pre);
void wait(int);
char* lcdWord;

int main()
{
    int menu;
	SHOW_intro();
	printf("WordGame!!\n");
	printf("1:StartGame 2: EndGame \n");
 	scanf("%d",&menu);
	getchar();
	if(menu==1)
	{
        start_game();

	}
	else if(menu==2) end_game(JUSTEND);
	return 0;
}

int start_game()
{
    PlayerType Player;GameType Referee;
	initialize_game(&Player,&Referee);
    SHOW_start_game();
	while(check_status(&Player,&Referee)){
		display_game(&Player,&Referee);
		input_word(&(Player.word));
		update_status(&Player,&Referee,check_word(&(Player.word),(Referee.quiz[Player.level])));
		system("clear");
	}
	return 0;
}
void initialize_game(PlayerType* p, GameType* r)
{
    p->level = 0;
    p->life  = 5;
    p->word = "test";
    r->playable_flag = 1;
    fill_quiz(r);
}
	

void display_game(PlayerType* p,GameType* r )
{
	char text[MAXCHR];
	printf("%s \n", r->quiz[p->level]);
	printf("level %d  life %d \n", (p->level)+1, p->life);
	sprintf(text,"LEVEL:%d  LIFE:%d QUIZ : %s",(p->level)+1,p->life,r->quiz[p->level]);
	printlcd(text);
	wait(SHORTTIME);
}
void input_word(char** word)
{
	printf("Input Answer :  ");
	scanf("%s",word);
	getchar();
	fflush(stdin);
}
int check_word(char* input, char* quiz)
{
	int flag;
	flag = strcmp(input,quiz);
	if(!flag)
	{
			printf("Correct Answer\n\n");
			printlcd("Correct Answer");
			wait(SHORTTIME);
			return TRUE;
	}
	else
	{
			printf("Wrong Answer\n\n");
			printlcd("Wrong Answer");
			wait(SHORTTIME);
			return FALSE;
	}
}
void update_status(PlayerType* p, GameType* r, int flag)
{
	if(flag == TRUE)
	{
		(p->level) +=1;
	}
	else
	{
		(p->life) -=1;
	}
}
int check_status(PlayerType* p,GameType *r)
{
	if(p->level < 10 && p->life > 0 )
		return r->playable_flag = TRUE;
	else if(p->level >= 10)//Success
		return	end_game(SUCCESS);
	else	//Fail
		return end_game(FAIL);
}

int end_game(int flag)
{
    SHOW_end_game(flag);
	return 0;
}


void fill_quiz(GameType* r)
{
    int i = 0;
	for(i = 0; i<10;i++)
	{
		r->quiz[i] = (char*)malloc(16);
	}
	strcpy(r->quiz[0],"apple");
	strcpy(r->quiz[1],"bear");
	strcpy(r->quiz[2],"car");
	strcpy(r->quiz[3],"doctor");
	strcpy(r->quiz[4],"egg");
	strcpy(r->quiz[5],"fire");
	strcpy(r->quiz[6],"grape");
	strcpy(r->quiz[7],"high");
	strcpy(r->quiz[8],"iphone");
	strcpy(r->quiz[9],"jacket");
}


void SHOW_intro()
{
	char str_intro[MAXCHR] = "WORDGAME        EmbededSystem";
	char str_team[MAXCHR] = "08109335 PCJ    08109367 JHJ"; 
	char str_start[MAXCHR] ="1.STARTGAME     2.ENDGAME";
    system("clear");
	printlcd(str_intro);
	wait(LONGTIME);
	printlcd(str_team);
	wait(LONGTIME);
	printlcd(str_start);
	
}
void SHOW_start_game()
{
	char str_begin[MAXCHR] = "The Game begin";
    system("clear");
    printf("The Game begin.\n");
	// print LCD
	printlcd(str_begin);
	wait(SHORTTIME);
}
void SHOW_end_game(int flag)
{
	char str_start[MAXCHR] ="ENDGAME!!       GoodBye!!";
	char str_success[MAXCHR] = "SUCCESS\n";
	char str_fail[MAXCHR] = "FAIL";
	switch(flag)
	{
	 case SUCCESS:
			printf("SUCCESS\n");
			printlcd(str_success);
		break;
	 case FAIL:
			printf("FAIL\n");
			printlcd(str_fail);
		break;
	default:
		break;
	}
	wait(SHORTTIME);
    printf("The END.\n\n");
	printlcd(str_start);
	wait(SHORTTIME);

}

void printlcd(char *av)
{
	int n;
	char    buf[MAXCHR];
	lcdFd =open(lcdDev, O_RDWR);
	memset(buf,0,sizeof(buf));
	n=strlen(av);
	if(n >MAXCHR)
		n=MAXCHR;
	memcpy(buf,av,n);
	write(lcdFd,buf,MAXCHR);
}
void wait(int time)
{
		int i = 0 ;
		for(i = 0 ; i<time; i++){}
}
