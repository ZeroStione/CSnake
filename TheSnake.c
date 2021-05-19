/*
贪吃蛇V0.0.1
Author:MrZero
*/

/*蛇移动思路：先将头结点进行移动处理,之后的结点依次赋值为前一个节点的位置*/

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>


#define START_GAME 1
#define OVER 0
#define INIT_SIGNAL -1
#define STOP_SIGNAL -2
#define SECOND_CHOICE 2
#define THIRED_CHOICE 3
#define SET_WALL 1
#define FRUIT 10
#define SNAKE_PART 5

#define GAME_VALUE int
#define GAME_SIGNAL char

//KeyBoard Signal
#define W_hit_Signal 87
#define w_hit_Signal 119
#define S_hit_Signal 83
#define s_hit_Signal 115
#define A_hit_Signal 65
#define a_hit_Signal 97
#define D_hit_Signal 68
#define d_hit_Signal 100
#define Enter_hit_Signal 13
#define ESC_hit_Signal 27

//Game Screen 
#define GAME_SCREEN_WIDTH 120
#define GAME_SCREEN_HIGTH 30


struct{
	int x_place;
	int y_place;
} SnakePart[200];

void HideCur() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ClearScreen() {
	system("cls");
}

GAME_VALUE Start_Interface(GAME_SIGNAL Key_hit_value, GAME_VALUE MENU_CHOICE) {
	ClearScreen();
	if ((MENU_CHOICE == START_GAME && (Key_hit_value == OVER||(Key_hit_value == W_hit_Signal
		|| Key_hit_value == w_hit_Signal))) || (MENU_CHOICE == SECOND_CHOICE&& (Key_hit_value == W_hit_Signal
|| Key_hit_value == w_hit_Signal))||(MENU_CHOICE == START_GAME&&Key_hit_value==STOP_SIGNAL)){
		printf("\n\n\n\n\n\n                                          ===========贪吃蛇V0.0.1==========\n");
		printf("                                          =       >>\033[40;31;1m[1].START GAME        \033[0m=\n");
		printf("                                          =         [2].排行榜            =\n");
		printf("                                          =         [3].开发者信息        =\n");
		printf("                                          =========== By Mrzero0 ==========\n");
		MENU_CHOICE = START_GAME;
	}
	else if (MENU_CHOICE == START_GAME && (Key_hit_value == S_hit_Signal || Key_hit_value == s_hit_Signal)||
		(MENU_CHOICE == SECOND_CHOICE && Key_hit_value == STOP_SIGNAL)||(MENU_CHOICE == THIRED_CHOICE &&
			(Key_hit_value == W_hit_Signal || Key_hit_value == w_hit_Signal))) {
		printf("\n\n\n\n\n\n                                          ===========贪吃蛇V0.0.1==========\n");
		printf("                                          =         [1].START GAME        =\n");
		printf("                                          =       >>\033[40;31;1m[2].排行榜            \033[0m=\n"); //change word color
		printf("                                          =         [3].开发者信息        =\n");
		printf("                                          =========== By Mrzero0 ==========\n");
		MENU_CHOICE = SECOND_CHOICE;
	}
	else if (MENU_CHOICE == SECOND_CHOICE && (Key_hit_value == S_hit_Signal || Key_hit_value == s_hit_Signal) ||
		(MENU_CHOICE == THIRED_CHOICE && Key_hit_value == STOP_SIGNAL)|| (MENU_CHOICE == THIRED_CHOICE &&
		(Key_hit_value == S_hit_Signal || Key_hit_value == s_hit_Signal))){
		printf("\n\n\n\n\n\n                                          ===========贪吃蛇V0.0.1==========\n");
		printf("                                          =         [1].START GAME        =\n");
		printf("                                          =         [2].排行榜            =\n");
		printf("                                          =       >>\033[40;31;1m[3].开发者信息        \033[0m=\n");
		printf("                                          =========== By Mrzero0 ==========\n");
		MENU_CHOICE = THIRED_CHOICE;
	}

	return MENU_CHOICE;
}

int Judg_effec_input(GAME_SIGNAL Key_hit_value, GAME_VALUE JUDGE_NUM) {
	if (JUDGE_NUM == INIT_SIGNAL) {
		if (Key_hit_value == W_hit_Signal || Key_hit_value == w_hit_Signal || Key_hit_value == S_hit_Signal
			|| Key_hit_value == s_hit_Signal) return START_GAME;
		else if (Key_hit_value == Enter_hit_Signal) return INIT_SIGNAL;
		else return OVER;
	}
	else if (JUDGE_NUM == START_GAME) {
	      if (Key_hit_value == W_hit_Signal || Key_hit_value == w_hit_Signal || Key_hit_value == S_hit_Signal || Key_hit_value == s_hit_Signal
		    || Key_hit_value == A_hit_Signal || Key_hit_value == a_hit_Signal || Key_hit_value == D_hit_Signal || Key_hit_value == d_hit_Signal
			|| Key_hit_value == ESC_hit_Signal) return START_GAME;
	}
	return OVER;
}

//void Create_Fruit(int *Ground) 

void Start_Snake_Game() {
	ClearScreen();
	int higth, width;
	int pos_x, pos_y;
	int Snake_part_size = 0;
	int PART_SIZE = 0;
	int Fruit_sur = 0;
	char Key_opr;
	char Key_Continue = A_hit_Signal;
	int  x_middle_place = 0;
	int  y_middle_place = 0;
	int  x_middle_pos = 0;
	int  y_middle_pos = 0;


	SnakePart[0].y_place = rand() % (GAME_SCREEN_HIGTH - (SET_WALL * 3)) + SET_WALL;
	SnakePart[0].x_place = rand() % (GAME_SCREEN_WIDTH - (SET_WALL * 3)) + SET_WALL;
	

	//system("color 60");  //change BackGround Color
	while (START_GAME) {
		Snake_part_size = 1;
		ClearScreen();
		//Sleep(1000);  //暂停1秒
		int Ground[30][120] = { 0 };
		Key_opr = INIT_SIGNAL;

		
		if (_kbhit()) {
			Key_opr = _getch();
		}
		if (Judg_effec_input(Key_opr, START_GAME)) {
			Key_Continue = Key_opr;
		}
		
		if (Judg_effec_input(Key_Continue, START_GAME)) {
			x_middle_place = SnakePart[0].x_place;
			y_middle_place = SnakePart[0].y_place;
			if ((Key_Continue == W_hit_Signal || Key_Continue == w_hit_Signal) &&
				SnakePart[0].y_place  >= SET_WALL) {
				SnakePart[0].y_place--;
			}
			else if ((Key_Continue == S_hit_Signal || Key_Continue == s_hit_Signal) &&
				SnakePart[0].y_place + 1 <= GAME_SCREEN_HIGTH - SET_WALL) {
				SnakePart[0].y_place++;
			}
			else if ((Key_Continue == A_hit_Signal || Key_Continue == a_hit_Signal) &&
				SnakePart[0].x_place  >= SET_WALL) {
				SnakePart[0].x_place--;
			}
			else if ((Key_Continue == D_hit_Signal || Key_Continue == d_hit_Signal) &&
				SnakePart[0].x_place + 1 <= GAME_SCREEN_WIDTH - SET_WALL) {
				SnakePart[0].x_place++;
			}
			else if (Key_Continue == ESC_hit_Signal) {
				return 0;
			}
		}
				while (Snake_part_size<=PART_SIZE ) {
					x_middle_pos = SnakePart[Snake_part_size].x_place;
					y_middle_pos = SnakePart[Snake_part_size].y_place;
					SnakePart[Snake_part_size].x_place = x_middle_place;
					SnakePart[Snake_part_size].y_place = y_middle_place;
					x_middle_place = x_middle_pos;
					y_middle_place = y_middle_pos;
					Snake_part_size++;
			    }

				Snake_part_size = 0;

				while (Snake_part_size <= PART_SIZE) {
					Ground[SnakePart[Snake_part_size].y_place][SnakePart[Snake_part_size].x_place] = SNAKE_PART;
					Snake_part_size ++;
				}


		if (!Fruit_sur) {
			pos_y = rand() % (GAME_SCREEN_HIGTH - (SET_WALL * 2)) + SET_WALL;
			pos_x = rand() % (GAME_SCREEN_WIDTH - (SET_WALL * 2)) + SET_WALL;
			
			Fruit_sur = 1;
		}
		
		Ground[pos_y][pos_x] = FRUIT;
		higth = 0;
		width = 0;

		for (higth= 0; higth < GAME_SCREEN_HIGTH; higth++) {
			for (width = 0; width < GAME_SCREEN_WIDTH; width++) {
				if (higth < SET_WALL || higth >= GAME_SCREEN_HIGTH-SET_WALL || 
					width < SET_WALL || width >= GAME_SCREEN_WIDTH- SET_WALL) {
					printf("%%");
				}
				else if (Ground[SnakePart[0].y_place][SnakePart[0].x_place]==FRUIT) {  //检测碰撞
					Ground[SnakePart[0].y_place][SnakePart[0].x_place] = SNAKE_PART;
					Fruit_sur = 0;
					PART_SIZE++;

					/*SnakePart[PART_SIZE].y_place = SnakePart[PART_SIZE - 1].y_place - 1;
					if ((PART_SIZE - 2 >= 0 && SnakePart[PART_SIZE].y_place != SnakePart[PART_SIZE - 2].y_place - 1)|| PART_SIZE - 2 < 0){
						Ground[SnakePart[PART_SIZE].y_place][SnakePart[PART_SIZE].x_place] = SNAKE_PART;
					}//生长
					else {
						SnakePart[PART_SIZE].y_place = SnakePart[PART_SIZE - 1].y_place + 1;
						Ground[SnakePart[PART_SIZE].y_place][SnakePart[PART_SIZE].x_place] = SNAKE_PART;
					}*/  ///需写出蛇身赋值至Ground方程

					 
				}
				else if (SnakePart[0].y_place < SET_WALL || SnakePart[0].y_place >= GAME_SCREEN_HIGTH - SET_WALL ||
					SnakePart[0].x_place < SET_WALL || SnakePart[0].x_place >= GAME_SCREEN_WIDTH - SET_WALL) {
					return 0; //撞墙检测
				}

				else if (Ground[higth][width] == 0) {
					printf(" ");
				}
				else if (Ground[higth][width] == FRUIT) {
					printf("o");
				}
				else if (Ground[higth][width] == SNAKE_PART) {
					printf("O");
				}
			}
			if (higth != GAME_SCREEN_HIGTH-1) {
				printf("\n");
			}
		}
		Sleep(200);
	}
	return 0;
}

void Ranking_List() {
	printf("rank");
	return 0;
}

void Devs_Info() {
	printf("Devs");
	return 0;
}

int main() {
	GAME_SIGNAL Key_hit_value=OVER;
	GAME_VALUE START_BOUNDARY = START_GAME;
	GAME_VALUE MENU_CHOICE = START_GAME;
	HideCur();

	while (START_GAME) {
		while (START_BOUNDARY) {
			MENU_CHOICE = Start_Interface(Key_hit_value, MENU_CHOICE);
			Key_hit_value = _getch();
			if (Judg_effec_input(Key_hit_value, INIT_SIGNAL) != OVER) {
				if (Judg_effec_input(Key_hit_value, INIT_SIGNAL) == INIT_SIGNAL) {
					if (MENU_CHOICE == START_GAME) {
						Start_Snake_Game();;
					}
					else if (MENU_CHOICE == SECOND_CHOICE) {
						Ranking_List();
					}
					else {
						Devs_Info();
					}
					Key_hit_value = STOP_SIGNAL;
				}
			}
		    else {
				Key_hit_value = STOP_SIGNAL;
			  }
			}
		}
			//if (Key_hit_value== W_hit_Sinal || Key_hit_value == w_hit_Sinal) {

			//}


		return 0;
}
