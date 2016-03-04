#include <stdio.h>
#include <string.h>
#define INITIAL_LIFE 5
#define MIN_LEVEL 1
#define MAX_LEVEL 10
#define TRUE 1
#define FALSE 0
/*
    게임에 필요한 내용
    문제, 게임시작종료플래그
*/
typedef struct{
    char* quiz[10];
    int choice;
    int playable_flag;
    int levelup_flag;
}GameType;
/*
    플레이어에 필요한 내용
    레벨, 생명, 입력할 내용,
*/
typedef struct{
    int level, life;
    char* word;
}PlayerType;


void start_game();
void initialize_game(PlayerType*, GameType*);
void display_status(PlayerType*);
void display_word(PlayerType*, GameType*);
int check_status(PlayerType*, GameType*);
int end_game();
void input_word(char*);
void update_status(PlayerType*, GameType*,int);
int check_word(char*,char*);
void fill_quiz(GameType*);
void SHOW_start_game();
void SHOW_end_game();

int main()
{
    int menu;
	printf("WordGame!!\n");
	printf("1:StartGame 2: EndGame \n");
 	scanf("%d",&menu);
	getchar();          // return 처리
	if(menu==1)
	{
        start_game();
	}
	else if(menu==2) end_game();
	return 0;
}

void start_game()
{
    PlayerType Player;GameType Referee;
	initialize_game(&Player,&Referee);
    SHOW_start_game();
	while(check_status(&Player,&Referee)){
		display_status(&Player);
		display_word(&Player,&Referee);
		input_word(&(Player.word));
		update_status(&Player,&Referee,check_word(&(Player.word),(Referee.quiz[Player.level])));
		system("cls");
	}
	end_game();

}
void initialize_game(PlayerType* p, GameType* r)
{
    p->level = 0;
    p->life  = 5;
    p->word = "test";
    r->playable_flag = 1;
    fill_quiz(r);
}
void display_status(PlayerType* p)
{
	printf("level %d  life %d \n", (p->level)+1, p->life);
}
void display_word(PlayerType* p,GameType* r )
{
	printf("%s \n", r->quiz[p->level]);
}
void input_word(char* word)
{
	printf("단어를 입력하세요  :  ");
	scanf("%s",word);
}
int check_word(char* input, char* quiz)
{
	int flag = strcmp(input,quiz);
    if(flag)
		printf("오답\n\n");
	else
		printf("정답\n\n");
	return flag;
}
void update_status(PlayerType* p, GameType* r, int flag)
{
	if(flag == 0)
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
	else
		return r->playable_flag = FALSE;
	
		
}

int end_game()
{
    SHOW_end_game();
	return 0;
}


void fill_quiz(GameType* r)
{
    r->quiz[0] = "apple";
    r->quiz[1] = "banana";
    r->quiz[2] = "strawberry";
    r->quiz[3] = "rasberry";
    r->quiz[4] = "wartermelon";
    r->quiz[5] = "mango";
    r->quiz[6] = "lemon";
    r->quiz[7] = "grape";
    r->quiz[8] = "orange";
    r->quiz[9] = "plum";
}



void SHOW_start_game()
{
    system("cls");
    printf("게임을 시작합니다.\n");
}
void SHOW_end_game()
{
    printf("The END.");
}
