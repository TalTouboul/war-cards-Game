#define _CRT_SECURE_NO_WARNINGS
#define sizeOFuserName 20
#define numOFcards 16
#define sizeOFfullDECK 54
#define sizeOFwarROUND 5
#define len 10
#define wid 61
#define sizeOFpattern 10

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

typedef struct playerDECK
{
	char UserName[sizeOFuserName];
	int PDarr[numOFcards];
	int countercards; 
	int newcard;
} PD;

int  fun_chose_players(char* UserName1, char* UserName2);
void fun_spilts_decks(int* arrDECK, int *PDarr);
int fun_game(PD pd1, PD pd2);
int rec_fun_random_newcard(int* PD);
int fun_war(PD pd1, PD pd2, int* counter1, int* counter2, char exitGAME);
void compare_cards(PD pd1, PD pd2, int* counter1, int* counter2);
void fun_emptyBANK(PD pd, int bank[], int** counter);
void fun_printROUND(PD pd1, PD pd2, int winner);
void fun_strCARD(char s[4][sizeOFpattern], int card1, int card2);
void fun_printLETTER(char pattern[sizeOFpattern]);
void fun_printCARD(char s1[], char s2[]);
void fun_printfWAR(int bank[], char user1[], char user2[], int winner);

int main() 
{
	int i;
	int exitgame;
	PD pd1, pd2;
	int winner;
	int arrDECK[numOFcards] = { 0 };
	
	printf("welcome to war cards game\n\n");
	exitgame = fun_chose_players(pd1.UserName, pd2.UserName);
	if (!exitgame) { return 0; }
	for (i = 0; i < numOFcards; i++) 
	{ 
		arrDECK[i] = 4; 
		pd1.PDarr[i] = 0;
		pd2.PDarr[i] = 0;
	}
	arrDECK[numOFcards - 1] = 2;  //only 2 jokers in the deck
	fun_spilts_decks(arrDECK, pd1.PDarr);
	fun_spilts_decks(arrDECK, pd2.PDarr);
	winner = fun_game(pd1, pd2);
	if (winner == 0) { printf("Well... guess it ended in a draw\n"); }
	if (winner == 1) { printf("the winner is:%s\n", pd1.UserName); }
	if (winner == 2) { printf("the winner is:%s\n", pd2.UserName); }
	
	return 0;
}


int fun_chose_players(char* UserName1,char* UserName2)
{
	char UserChoose;
	char c[] = "tal";
	int sizeC = sizeof(c);
	printf("choose game mode:\n");
	printf("press [1] vs. tal\npress [2] vs. player\n\nor any key to exit the game...\n\n");
	UserChoose = _getch();
	
	switch (UserChoose)
	{
	case '1':
		strcpy(UserName2, c);
		UserName2[sizeC] = '\0';
		printf("may I ask for your name: ");
		rewind(stdin);
		fgets(UserName1, strlen(UserName1), stdin);
		UserName1[strcspn(UserName1, "\n")] = 0;
		printf("\nhello %s It seems you are brave enough to face against me\n let's see what you got...\n\n ", UserName1);
		break;
	case '2':	
		printf("enter first player's name: ");
		rewind(stdin);
		fgets(UserName1, strlen(UserName1), stdin);
		printf("enter second player's name: ");
		rewind(stdin);
		fgets(UserName2, strlen(UserName2), stdin);
		UserName1[strcspn(UserName1, "\n")] = 0;
		UserName2[strcspn(UserName2, "\n")] = 0;
		printf("\nhello %s and %s it's my honor to meet you both\nlet as start the game...\n\n", UserName1, UserName2);
		break;
	default:
		UserChoose = 0;
		break;
	}
	return UserChoose;
}
void fun_spilts_decks(int *arrDECK, int* PDarr)
{
	int newcard;
	int counterCARDS = 0;
	srand(time(0));
	while (counterCARDS < sizeOFfullDECK/2)
	{
		newcard = ((int)rand() % 14 + 2);
		if (arrDECK[newcard])
		{
			arrDECK[newcard]--;
			PDarr[newcard]++;
			counterCARDS++;
		}
	}	
	
} 
int fun_game(PD pd1, PD pd2)
{
	pd1.countercards = sizeOFfullDECK / 2;
	pd2.countercards = sizeOFfullDECK / 2;
	char exitGAME = ' ';
	int battlewinner = 0;
	while (pd1.countercards > 0 && pd2.countercards > 0)
	{
		if (exitGAME == ' ')
		{
			printf("press the [spacebar] to lay cards\n");
			printf("or any key to go the end game...\n\n");
			exitGAME = _getch();
			system("cls");
		}
		pd1.newcard = rec_fun_random_newcard(pd1.PDarr);
		pd2.newcard = rec_fun_random_newcard(pd2.PDarr);
		if (pd1.newcard > pd2.newcard)
		{
			compare_cards(pd1, pd2, &pd1.countercards, &pd2.countercards);
			battlewinner = 1;
		}
		if (pd1.newcard < pd2.newcard)
		{
			compare_cards(pd2, pd1, &pd2.countercards, &pd1.countercards);
			battlewinner = 2;
		}
		if (exitGAME == ' ') { fun_printROUND(pd1, pd2, battlewinner); }
		if (pd1.newcard == pd2.newcard)
		{
			battlewinner = fun_war(pd1, pd2, &pd1.countercards, &pd2.countercards, exitGAME);
		}
		
	}
	return battlewinner;
}
int rec_fun_random_newcard(int* PD) 
{
	int newcard = (int)rand() % 14 + 2;
	if (PD[newcard])
	{
		return newcard;
	}
	return rec_fun_random_newcard(PD);
}
int fun_war(PD pd1, PD pd2, int* counter1, int* counter2, char exitGAME)
{
	int i;
	int winner = 0;
	int counterWARS = 1;
	int index = 0;
	int* bank = (int*)calloc(numOFcards, sizeof(int));
	assert(bank);
	int sizeOFbank = sizeof(bank) / sizeof(int);
	system("cls");
	while (pd1.newcard == pd2.newcard)
	{
		bank[pd1.newcard]++;
		bank[pd2.newcard]++;
		pd1.PDarr[pd1.newcard]--;
		pd2.PDarr[pd2.newcard]--;
		index++;
		if (exitGAME == ' ')
		{
			for (i = 0; i < wid / 3; i++) { printf(" "); }
			printf("!!!WAR!!!\n\n");
			fun_printROUND(pd1, pd2, winner);
		}
		while (index < sizeOFwarROUND * counterWARS)
		{
			pd1.newcard = rec_fun_random_newcard(pd1.PDarr);
			pd2.newcard = rec_fun_random_newcard(pd2.PDarr);
			bank[pd1.newcard]++;
			bank[pd2.newcard]++;
			pd1.PDarr[pd1.newcard]--;	
			pd2.PDarr[pd2.newcard]--;
			index++;
		}
		*counter1 -= 5;
		*counter2 -= 5;
		counterWARS++;
		if (exitGAME == ' ') { fun_printROUND(pd1, pd2, winner); }
	}
	
	if (pd1.newcard > pd2.newcard) 
	{
		fun_emptyBANK(pd1, bank, &counter1); 
		winner = 1;
	}
	if (pd2.newcard > pd1.newcard) 
	{
		fun_emptyBANK(pd2, bank, &counter2); 
		winner = 2;
	}
	if (exitGAME == ' ') { fun_printfWAR(bank, pd1.UserName, pd2.UserName, winner); }
	free(bank);
	return winner;
}
void compare_cards(PD pd1, PD pd2,int *counter1,int *counter2)
{
	pd1.PDarr[pd2.newcard]++;
	pd2.PDarr[pd2.newcard]--;
	*counter1 += 1;
	*counter2 -= 1;
}
void fun_emptyBANK(PD pd, int bank[], int** counter)
{
	int i;
	for (i = 2; i < numOFcards; i++)
	{
		if (bank[i]) 
		{
			pd.PDarr[i] += bank[i];
			**counter += bank[i];
		}
	}
}
void fun_printROUND(PD pd1, PD pd2, int winner)
{
	int x, y;
	
	char s[4][sizeOFpattern];
	char pattern[2][sizeOFpattern] = { { "||     ||" },{ "|||||||||" } };
	
	fun_strCARD(s, pd1.newcard, pd2.newcard);

	if (winner == 1) { printf("the winner for this round is : % s\n\n", pd1.UserName); }
	if (winner == 2) { printf("the winner for this round is : % s\n\n", pd2.UserName); }

	printf("%s 's card is: ", pd1.UserName);
	for (y = 0; y < wid / 4; y++) { printf(" "); }
	printf("%s 's card is: ", pd2.UserName);
	printf("\n\n");

	for (x = 0; x < len; x++) 
	{
		if (x == 0 || x == len - 1) { fun_printLETTER(pattern[1]); }
		if (x == 1) { fun_printCARD(s[0], s[1]); }
		if (x == len - 2) { fun_printCARD(s[2], s[3]); }
		if (x >= 2 && x < len - 3) { fun_printLETTER(pattern[0]); }
	}

	printf("\n");
	printf("%s's cards left: %d\n", pd1.UserName, pd1.countercards);
	printf("%s's cards left: %d\n", pd2.UserName, pd2.countercards);
	printf("\n");
}
void fun_strCARD(char s[4][sizeOFpattern], int card1, int card2) 
{
	char space[] = { "||     ||" };
	char joker[] = { "||JOKER||" };
	int card[2] = { card1, card2 };
	int i;
	for (i = 0; i < 2; i++) 
	{
		if (card[i] >= 2 && card[i] <= 9) 
		{
			strcpy(s[i], space);
			s[i][2] = card[i] + '0';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern-4] = card[i] + '0';
		}
		if (card[i] == 10) 
		{
			strcpy(s[i], space);
			s[i][2] = '1';
			s[i][3] = '0';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern - 5] = '1';
			s[i + 2][sizeOFpattern - 4] = '0';
		}
		if (card[i] == 11)
		{
			strcpy(s[i], space);
			s[i][2] = 'J';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern - 4] = 'J';
		}
		if (card[i] == 12)
		{
			strcpy(s[i], space);
			s[i][2] = 'Q';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern - 4] = 'Q';
		}
		if (card[i] == 13)
		{
			strcpy(s[i], space);
			s[i][2] = 'K';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern - 4] = 'K';
		}
		if (card[i] == 14)
		{
			strcpy(s[i], space);
			s[i][2] = 'A';
			strcpy(s[i + 2], space);
			s[i + 2][sizeOFpattern - 4] = 'A';
		}
		if (card[i] == 15) 
		{
			strcpy(s[i], joker);
			strcpy(s[i + 2], joker);
		}
	}
}
void fun_printLETTER(char pattern[sizeOFpattern])
{
	int y;
	for (y = 0; y < wid / 6; y++) { printf(" "); }
	printf("%s", pattern);
	for (y = 0; y < wid / 3; y++) { printf(" "); }
	printf("%s", pattern);
	printf("\n");
}
void fun_printCARD(char s1[], char s2[]) 
{
	int y;
	for (y = 0; y < wid / 6; y++) { printf(" "); }
	printf("%s", s1);
	for (y = 0; y < wid / 3; y++) { printf(" "); }
	printf("%s", s2);
	printf("\n");
}
void fun_printfWAR(int bank[], char user1[],char user2[],int winner)
{
	int i, j;
	if (winner == 1) { printf("%s won the war and earned the cards: ", user1); }
	if (winner == 2) { printf("%s won the war and earned the cards: ", user2); }
	for (i = 2; i < numOFcards; i++)
	{
		if (bank[i])
		{
			for (j = 0; j < bank[i]; j++)
			{
				if (i >= 2 && i <= 10) { printf("%d ", i); }
				if (i == 11) { printf("J "); }
				if (i == 12) { printf("Q "); }
				if (i == 13) { printf("K "); }
				if (i == 14) { printf("A "); }
				if (i == 15) { printf("JOKER "); }
			}
		}
	}
printf("\n\n");
}
