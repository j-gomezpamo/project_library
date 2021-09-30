#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>// matriz[columna][serie]
#include<conio.h>
#include<windows.h>
#include<malloc.h>
#include<math.h>


#define TRUE			1
#define FALSE			0

#define SPACE			32
#define BLOCK			219
#define UHALF			223

#define sleep_total	    1000
#define speed_reduce    20

#define size_x			10
#define size_y          20

#define p_score_x       120
#define p_score_y       16
#define game_pos_x		64
#define game_pos_y		4
#define p_futuras_x     120
#define p_futuras_y     4
#define p_instruc_x     12
#define p_instruc_y     16
#define p_guardada_x    40
#define p_guardada_y     4
#define p_stats_x       120
#define p_stats_y       32
#define p_logo_x		8
#define p_logo_y		2
#define p_menu_x		12
#define p_menu_y		32

#define RIGHT			'd'
#define UP				'w'
#define DOWN			'l'
#define FALL			's'
#define LEFT			'a'
#define CWISE			23
#define HOLD			't'

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15

// pantalla pequeña: 30, 120  pantalla grande: 46, 168   pantalla XXL: 48, 168
typedef struct
{
	int rot;
	int figura[5];
	int flag_mov;
	int flag_fall;
	int flag_hold;
	int flag_save;
	int sleep;
	int figuras[16];
	int posicion[7];

	int count_fig[7];
	int figura_P[4][16];
	int figura_Z[2][16];
	int figura_I[2][16];
	int figura_S[2][16];
	int figura_T[4][16];
	int figura_O[16];
	int figura_L[4][16];
	

}tetris;

typedef struct
{
	tetris t;
	char *T;
	int menu;
	char direccion;
	char juego;
	int pantalla[20][10];
	int posicion_x;
	int posicion_y;
	int B;
	int puntos;
	int highscore;
	
}comun;

void titulo(comun *);
void inicializar(comun *);

void TETRIS(comun *);

void row(comun *);
void block(comun *);
void clear(comun *);
void figures(comun *);
void select_figura(comun *, int);
void tetris_logo_mini(comun *);

void print_block(int, int, int);
void stats(comun *);
void mov(comun *);
void menu(comun *, int);
void gotoxy(int, int);
void color(int, int);


int main()
{
	comun C;

	titulo(&C);
	do
	{
		inicializar(&C);
		TETRIS(&C);
		menu(&C, 1);
	} while (C.menu == 1);
	return 0;
}


void titulo(comun *C)
{

	/*COORD coord;
	SMALL_RECT rect;
	rect.Bottom = 48;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = 168;
	coord.X = 169;
	coord.Y = 49;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &rect);*/

	FILE *fpt;
	int jgpgc[92][92];
	
	printf("\t\t\t\t\texpand window and click enter\n\n");
	system("pause");
	color(BLACK, BLACK);
	system("cls");
	fpt = fopen("jgpgc.txt", "r");

	for (int i = 0; i < 92; i++)
	{
		for (int j = 0; j < 92; j++)
		{
			fscanf(fpt, "%d", &jgpgc[i][j]);

		}
	}

	for (int i = 0; i < 92; i+=2)
	{
		gotoxy(38, i/2 + 1);
		for (int j = 0; j < 92; j++)
		{
			color(jgpgc[i][j], jgpgc[i + 1][j]);
			printf("%c", UHALF);
		}
	}
	Sleep(5000);
	/*FILE *ifpt;
	int i = 0, j = 0, k = 0, x = 100, y;
	size_t size;
	ifpt = fopen("titulo_tetris.txt", "r");
	C->T = (char*)calloc(1, sizeof(char));

	do
	{

		fscanf(ifpt, "%d", &y);
		C->T[k] = y;
		j++;
		fscanf(ifpt, "%c", &y);
		k++;
		if (y == 10)
		{
			if (i == 0)
			{
				x = j;
			}
			while (j < x)
			{

				size = _msize(C->T);
				C->T = (char*)realloc(C->T, size + 1 * sizeof(char));
				C->T[k] = 0;
				k++;
				j++;
			}
			j = 0;
			i++;
		}
		size = _msize(C->T);
		C->T = (char*)realloc(C->T, size + 1 * sizeof(char));
	} while (feof(ifpt) == 0);

	y = i + 1;
	C->T[k] = '\0';
	printf("%s", C->T);

	for (i = 0; i < y; i += 2)
	{
		for (j = 0; j < x; j++)
		{
			color(C->T[i*x + j], C->T[(i + 1)*x + j]);
			printf("%c", 223);
		}
		printf("\n");
	}

	Sleep(5000);
	free(C->T);
	fclose(ifpt);*/
}
void inicializar(comun *C)
{
	FILE *fpt, *ifpt, *ofpt, *jfpt;
	int i, j, k, pos, x, y;
	int jgpgc[16][16];

	C->t.flag_hold = FALSE;
	C->menu = TRUE;
	C->puntos = 0;
	C->t.sleep = sleep_total;
	C->t.flag_save = TRUE;

	fpt = fopen("figuras.txt", "r");
	ifpt = fopen("stats.txt", "r");
	ofpt = fopen("highscore.txt", "r");
	jfpt = fopen("jgpgcmini.txt", "r");

	for (i = 0; i < 7; i++)
	{
		fscanf(ifpt,"%d", &C->t.count_fig[i]);
	}

	fscanf(ofpt,"%d", &C->highscore);
	

	// instrucciones__________________________________________________________________________________________________________________________________
	for (i = 0; i < 6; i ++) 
	{
		for (j = 0; j < 11; j++ )
		{
			if( i == 0 || i == 5 || j == 0 || j == 10)
			print_block(p_instruc_x - 4 + j * 4, p_instruc_y - 2 + i * 2, 7);
		}
	}
	color(BLACK, BLACK);
	for (i = 0; i < 8; i++)
	{
		gotoxy(p_instruc_x, p_instruc_y + i);
		for (j = 0; j < 9; j++)
		{
			printf("    ");
		}
	}
	x = p_instruc_x + 1;
	y = p_instruc_y;
	i = 0;

	gotoxy(x, y + i);
	color(DARKGRAY, BLACK);
	printf("\t\tinstrucciones:"); i++; gotoxy(x, y + i); i++;
	printf(" flecha > : moverse a la derecha"); gotoxy(x, y + i); i++;
	printf(" flecha < : moverse a la izquierda"); gotoxy(x, y + i); i++;
	printf(" flecha v : mover hacia abajo"); gotoxy(x, y + i); i++;
	printf(" flecha ^ : rotar sentido horario"); gotoxy(x, y + i); i++;
	printf(" tecla tab: guardar figura"); gotoxy(x, y + i);
	printf(" tecla esc: menu de pausa");
	
	// game_________________________________________________________________________________________________________________________________________
	for (i = 0; i < size_y + 2; i++)
	{
		for (j = 0; j < size_x + 2; j++)
		{
			if (i == 0 || i == size_y + 1 || j == 0 || j == size_x + 1)
				print_block(game_pos_x - 4 + j * 4, game_pos_y - 2 + i * 2, 7);
		}
	}

	color(WHITE, BLACK);
	for (i = 0; i < size_y * 2; i++)
	{
		gotoxy(game_pos_x, game_pos_y + i);
		for (j = 0; j < size_x; j++)
		{
			printf("%c%c%c%c",SPACE,SPACE,SPACE,SPACE);
		}
	}


	// future pieces___________________________________________________________________________________________________________________
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (i == 0 || i == 3 || j == 0 || j == 9 || j == 3 || j == 6)
				print_block(p_futuras_x - 4 + j * 4, p_futuras_y - 2 + i * 2, 7);
		}
	}

	// saved piece___________________________________________________________________________________________________________________
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if(i == 0 || i == 3 || j == 0 || j == 3)
				print_block(p_guardada_x - 4 + j * 4, p_guardada_y - 2 + i * 2, 7);
		}
	}

	color(BLACK, BLACK);
	for (i = 0; i < 4; i++)
	{
		gotoxy(p_guardada_x, p_guardada_y + i);
		printf("        ");
	}


	// stats_____________________________________________________________________________________________________________________
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (i == 0 || i == 7 || j == 0 || j == 9)
				print_block(p_stats_x - 4 + j * 4, p_stats_y - 2 + i * 2, 7);
		}
	}
	color(BLACK, BLACK);
	for (i = 0; i < 12; i++)
	{
		gotoxy(p_stats_x, p_stats_y + i);
		for (j = 0; j < 8; j++)
		{
			printf("    ");
		}
	}

	// jgpgc mini logo__________________________________________________________________________________________________________________
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			fscanf(jfpt, "%d", &jgpgc[i][j]);
		}
	}

	for (i = 0; i < 16; i+=2)
	{
		gotoxy(p_logo_x, p_logo_y + i/2);
		for (j = 0; j < 16; j++)
		{
			color(jgpgc[i][j], jgpgc[i + 1][j]);
			printf("%c", UHALF);
		}
	}

	// menu_______________________________________________________________________________________________________________

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 11; j++)
		{
			if (i == 0 || i == 7 || j == 0 || j == 10)
				print_block(p_menu_x - 4 + j * 4, p_menu_y - 2 + i * 2, LIGHTGRAY);
		}
	}
	
	tetris_logo_mini(C);

	//score_____________________________________________________________________________________________________________________________________________
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if( i == 0 || i == 5 || j == 0 || j == 9)
				print_block(p_score_x - 4 + j * 4, p_score_y - 2 + i * 2, LIGHTGRAY);
		}
	}
	color(BLACK, BLACK);
	for (i = 0; i < 8; i++)
	{
		gotoxy(p_score_x, p_score_y + i);
		for (j = 0; j < 8; j++)
		{
			printf("    ");
		}
	}

	color(WHITE, BLACK);
	gotoxy(p_score_x + 6, p_score_y + 1);
	printf("puntuacion: 0");
	gotoxy(p_score_x + 6, p_score_y + 3);
	printf("Highscore: %d", C->highscore);
	gotoxy(p_score_x + 6, p_score_y + 5);
	printf("velocidad: 1  de %d", sleep_total / speed_reduce);

	srand(time(NULL));

	for( i = 0; i < 4; i++)
	{
		C->t.figura[i] = rand() % 7;
		C->t.count_fig[C->t.figura[i]]++;
	}

	stats(C);


	// IGUALAR TODOS LOS VALORES DE LA MATRIZ PANTALLA A ESPACIO
	for (i = 0; i < size_y; i++)
	{
		for (j = 0; j < size_x; j++)
		{
			C->pantalla[i][j] = SPACE;
		}
	}


	// GUARDAR DE UN ARCHIVO LA FORMA Y NUMERO DE GIROS DE CADA FIGURA
	for( int fig = 0; fig < 7; fig++)
	{ 
		fscanf(fpt, "%d", &pos);
		pos--;
		C->t.posicion[fig] = pos;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 16; j++)
			{
				fscanf(fpt, "%d", &k);
				switch (fig)
				{
				case 0:
					C->t.figura_P[i][j] = k;
					break;
				case 1:
					C->t.figura_Z[i][j] = k;
					break;
				case 2:
					C->t.figura_I[i][j] = k;					
					break;
				case 3:
					C->t.figura_S[i][j] = k;					
					break;
				case 4:
					C->t.figura_T[i][j] = k;
					break;
				case 5:
					C->t.figura_O[j] = k;			
					break;
				case 6:
					C->t.figura_L[i][j] = k;
					break;

				}
				if (j == 15 && i == pos)
					i = 4;
			}
		}
	}
	fclose(fpt); fclose(ifpt);
}

void TETRIS(comun *C)
{
	FILE *fpt, *ifpt;
	int i, j, k, l, highscore = 0;
	int flag_row = FALSE;
	int flag_erase_row = FALSE;
	int flag_speed = FALSE;
	// I,J los uso para los for
	// L guarda la posicion y de la figura
	// K guarda la posicion x de la figura y un uso extra
	// ROT guarda la orientacion de la figura
	// R guarda que pieza se esta usando y un uso extra
	// flag marca cuando la figura ha llegado a un obstaculola 
	// highscore es el valor mas alto guardado de otras partidas
	// a guarda la tecla que introduces en el getch

	fpt = fopen("highscore.txt", "r");

	srand(time(NULL));
	clock_t comienzo = clock();

	while (C->menu == TRUE)
	{

		C->posicion_y = 0;
		C->t.rot = 0;
		C->posicion_x = 4;
		
		if (C->direccion != HOLD || C->t.flag_hold == FALSE)
		{
			C->t.flag_save = TRUE;
			if(C->direccion == HOLD)
				C->t.flag_hold = TRUE;
			for (i = 0; i < 4; i++)
			{
				if (i == 3)
				{
					C->t.figura[i] = rand() % 7;// elegir aleatoriamente la pieza
					C->t.count_fig[C->t.figura[i]]++;
					stats(C);
				}
				else
					C->t.figura[i] = C->t.figura[i + 1];
				select_figura(C, i);
				if (i > 0)
				{
					for (j = 0; j < 4; j++)
					{
						gotoxy(p_futuras_x + 12 * (i - 1), p_futuras_y + j);
						for (k = 0; k < 4; k++)
						{
							if (C->t.figuras[j * 4 + k] == TRUE)
							{
								color(C->t.figura[i] + 9, C->t.figura[i] + 9);
								printf("%c%c", BLOCK, BLOCK);
							}
							else
							{
								color(BLACK, BLACK);
								printf("%c%c", SPACE, SPACE);
							}
						}
					}
				}
			}
		}
		select_figura(C, 0);
	
		C->t.flag_mov = TRUE;
		C->t.flag_fall = TRUE;
		/*if (highscore == 10)
		{
			printf("a");
		}
		highscore++;*/
		//borro de linea y suma de puntos
		l = 0;
		for (i = 0; i < 20; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (C->pantalla[i][j] == SPACE)
					flag_row = FALSE;
			}
			if (flag_row == TRUE)
			{
				l++;
				flag_erase_row = TRUE;
				for (k = i; k > 0; k--)
				{
					for (j = 0; j < 10; j++)
							C->pantalla[k][j] = C->pantalla[k - 1][j];
				}
				C->pantalla[k][j] = SPACE;
			}
			flag_row = TRUE;
		}
			
		if (flag_erase_row == TRUE)
		{
			if (C->t.sleep > 0)
				C->t.sleep -= speed_reduce;
			C->puntos += l * l * 10;
			row(C);

			color(WHITE, BLACK);
			gotoxy(p_score_x + 6, p_score_y + 1);
			printf("puntuacion: %d", C->puntos);
			gotoxy(p_score_x + 6, p_score_y + 3);
			printf("Highscore: %d", C->highscore);
			gotoxy(p_score_x + 6, p_score_y + 5);
			printf("velocidad: %d  de %d",  (sleep_total - C->t.sleep)/speed_reduce + 1,  sleep_total / speed_reduce);

			flag_erase_row = FALSE;
		}

		while(C->t.flag_fall == TRUE)//imp
		{
			if (clock() - comienzo > C->t.sleep) // cada cierto tiempo que ira disminuyendo el bloque bajará automaticamente
			{
				C->direccion = DOWN;
				figures(C);
				comienzo = clock();
			}

			if (_kbhit() == TRUE)
			{
				mov(C);
				if (C->menu == FALSE)
					break;
				figures(C);
			}
			
		}


		for (j = 0; j < 10; j++)  // si una pieza llega arriba del todo, se acaba el juego   IMPORTANTE SOLUCIONAR________________________________________________________
		{
			if (C->pantalla[0][j] != SPACE && C->t.flag_mov == FALSE)
				C->menu = FALSE;
		}
	}

	if (C->puntos > C->highscore)
	{
		ifpt = fopen("highscore.txt", "w");
		fprintf(ifpt, "%d", C->puntos);
		fclose(ifpt);
	}
	fclose(fpt);
}

void row(comun *C)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (C->pantalla[i][j] != SPACE)
			{
				gotoxy(j * 4 + game_pos_x, i * 2 + game_pos_y);
				color(C->pantalla[i][j] + 1, DARKGRAY);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 9, C->pantalla[i][j] + 1);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 9, C->pantalla[i][j] + 1);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 9, C->pantalla[i][j] + 9);
				printf("%c", UHALF);

				gotoxy(j * 4 + game_pos_x, i * 2 + 1 + game_pos_y);
				color(DARKGRAY, DARKGRAY);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 1, DARKGRAY);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 1, DARKGRAY);
				printf("%c", UHALF);
				color(C->pantalla[i][j] + 9, C->pantalla[i][j] + 1);
				printf("%c", UHALF);
			}
			else
			{
				color(WHITE, BLACK);
				gotoxy(j * 4 + game_pos_x, i * 2 + game_pos_y);
				printf("%c%c%c%c",SPACE, SPACE, SPACE, SPACE);

				gotoxy(j * 4 + game_pos_x, i * 2 + 1 + game_pos_y);
				printf("%c%c%c%c", SPACE, SPACE, SPACE, SPACE);
			}
		}
	}
}

void block(comun *C)
{
	int k = 0;

	for (int l = 0; l < 4; l++)
	{
		for (int m = 0; m < 4; m++)
		{
			if (C->t.figuras[k] == TRUE)
			{
				gotoxy(C->posicion_x * 4 + m * 4 + game_pos_x, C->posicion_y * 2 + l * 2 + game_pos_y);
				color(C->t.figura[0] + 1, DARKGRAY);
				printf("%c", UHALF);
				color(C->t.figura[0] + 9, C->t.figura[0] + 1);
				printf("%c", UHALF);
				color(C->t.figura[0] + 9, C->t.figura[0] + 1);
				printf("%c", UHALF);
				color(C->t.figura[0] + 9, C->t.figura[0] + 9);
				printf("%c", UHALF);

				gotoxy(C->posicion_x * 4 + m * 4 + game_pos_x, C->posicion_y * 2 + l * 2 + 1 + game_pos_y);
				color(DARKGRAY, DARKGRAY);
				printf("%c", UHALF);
				color(C->t.figura[0] + 1, DARKGRAY);
				printf("%c", UHALF);
				color(C->t.figura[0] + 1 , DARKGRAY);
				printf("%c", UHALF);
				color(C->t.figura[0] + 9, C->t.figura[0] + 1);
				printf("%c", UHALF);
				/*if (C->posicion_y + l > 19 || C->posicion_x + m > 9 || C->posicion_x + m < 0)
				{
					printf("eee"); system("pause");
				}*/
				C->pantalla[C->posicion_y + l][C->posicion_x + m] = C->t.figura[0];
			}
			k++;
		}
	}

}

void clear(comun *C)
{
	int k = 0;
	color(WHITE, BLACK);
	for (int l = 0; l < 4; l++)
	{
		for (int m = 0; m < 4; m++)
		{
			if (C->t.figuras[k] == TRUE)
			{
				gotoxy(C->posicion_x * 4 + m * 4 + game_pos_x, C->posicion_y * 2 + l * 2 + game_pos_y);
				printf("%c%c%c%c", SPACE,SPACE,SPACE,SPACE);

				gotoxy(C->posicion_x * 4 + m * 4 + game_pos_x, C->posicion_y * 2 + l * 2 + 1 + game_pos_y);
				printf("%c%c%c%c", SPACE,SPACE,SPACE,SPACE);
				C->pantalla[C->posicion_y + l][C->posicion_x + m] = SPACE;
			}
			k++;
		}
	}
}
void figures(comun *C)
{
	int i, j, k = 0; 

	C->t.flag_mov = TRUE;
	C->t.flag_fall = TRUE;

	clear(C);

	if (C->direccion == DOWN)
		C->posicion_y++;

	else if (C->direccion == LEFT)
		C->posicion_x--;

	else if (C->direccion == RIGHT)
		C->posicion_x++;

	else if(C->direccion == CWISE)
	{
		C->t.rot++;
		if (C->t.rot > C->t.posicion[C->t.figura[0]])
			C->t.rot = 0;
		select_figura(C, 0);
	}

	else if (C->direccion == HOLD && C->t.flag_save == TRUE)
	{
		j = C->t.figura[0];
		if(C->t.flag_hold == TRUE)C->t.figura[0] = C->t.figura[4];
		C->t.figura[4] = j;
		select_figura(C, 4);
		for (j = 0; j < 4; j++)
		{
			gotoxy(p_guardada_x, p_guardada_y + j);
			for (k = 0; k < 4; k++)
			{
				if (C->t.figuras[j * 4 + k] == TRUE)
				{
					color(C->t.figura[4] + 9, C->t.figura[4] + 9);
					printf("%c%c", BLOCK, BLOCK);
				}
				else
				{
					color(BLACK, BLACK);
					printf("%c%c",SPACE,SPACE);
				}
			}
		}
		C->t.flag_save = FALSE;
		C->t.flag_fall = FALSE;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (C->t.figuras[k] == TRUE)
			{
				if (C->pantalla[i + C->posicion_y][j + C->posicion_x] != SPACE || C->posicion_y + i > 19 || C->posicion_x + j > 9 || C->posicion_x + j < 0)
				{
					if (C->direccion == DOWN)
						C->t.flag_fall = FALSE;

					C->t.flag_mov = FALSE;
				}
			}
			k++;
		}
	}

	if (C->t.flag_mov == FALSE || C->t.flag_fall == FALSE)
	{

		if (C->direccion == DOWN) C->posicion_y--;

		else if (C->direccion == LEFT)  C->posicion_x++;

		else if (C->direccion == RIGHT)  C->posicion_x--;

		else if (C->direccion == CWISE) 
		{ 
			C->t.rot--; 
			if (C->t.rot < 0)
				C->t.rot = C->t.posicion[C->t.figura[0]];
			select_figura(C, 0);
		}
		
	}
	if(C->direccion != HOLD) block(C);
}
void select_figura(comun *C, int i)
{
	for (int k = 0; k < 16; k++)
	{
		switch (C->t.figura[i])
		{
		case 0:
			C->t.figuras[k] = C->t.figura_P[C->t.rot][k];
			break;
		case 1:
			C->t.figuras[k] = C->t.figura_Z[C->t.rot][k];
			break;
		case 2:
			C->t.figuras[k] = C->t.figura_I[C->t.rot][k];
			break;
		case 3:
			C->t.figuras[k] = C->t.figura_S[C->t.rot][k];
			break;
		case 4:
			C->t.figuras[k] = C->t.figura_T[C->t.rot][k];
			break;
		case 5:
			C->t.figuras[k] = C->t.figura_O[k];
			break;
		case 6:
			C->t.figuras[k] = C->t.figura_L[C->t.rot][k];
			break;
		}
	}
}
void tetris_logo_mini(comun *C)
{
	FILE *fpt;
	int tetris[24][36];

	fpt = fopen("tetris_logo_mini.txt", "r");

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 36; j++)
		{
			fscanf(fpt, "%d", &tetris[i][j]);

		}
	}

	for (int i = 0; i < 24; i += 2)
	{
		gotoxy(p_menu_x, p_menu_y + i / 2);
		for (int j = 0; j < 36; j++)
		{
			color(tetris[i][j], tetris[i + 1][j]);
			printf("%c", UHALF);
		}
	}

}

void stats(comun *C)
{
	FILE *ifpt;
	double sum = 0.00;
	int i, j;
	double porcentage[7];

	ifpt = fopen("stats.txt", "w");

	for (i = 0; i < 7; i++)
	{
		sum += C->t.count_fig[i];
	}
	for (i = 0; i < 7; i++)
	{
		porcentage[i] = round((	C->t.count_fig[i] / sum) * 60.00);
		color(i + 9, BLACK);
		gotoxy(p_stats_x + 3 + 4 * i, p_stats_y + 1);
		printf("%d", C->t.count_fig[i]);
		for (j = 0; j < 10; j++)
		{
			color(BLACK, BLACK);
			gotoxy(p_stats_x + 3 + i * 4, p_stats_y + 11 - j);
			printf("  ");
		}
	}
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < porcentage[i]; j++)
		{
			color(i + 9, i + 9);
			gotoxy(p_stats_x + 3 + i * 4, p_stats_y + 11 - j);
			printf("%c%c", BLOCK, BLOCK);
		}
	}
	for (i = 0; i < 7; i++)
	{
		fprintf(ifpt, "%d", C->t.count_fig[i]);
		fprintf(ifpt, " ");
	}
	fclose(ifpt);
}
void print_block(int x, int y, int col)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoxy(x, y);
			color(col, DARKGRAY);
			printf("%c", UHALF);
			color(col + DARKGRAY, col);
			printf("%c", UHALF);
			color(col + DARKGRAY, col);
			printf("%c", UHALF);
			color(col + DARKGRAY, col + DARKGRAY);
			printf("%c", UHALF);

			gotoxy(x, y + 1);
			color(DARKGRAY, DARKGRAY);
			printf("%c", UHALF);
			color(col, DARKGRAY);
			printf("%c", UHALF);
			color(col, DARKGRAY);
			printf("%c", UHALF);
			color(col + DARKGRAY, col);
			printf("%c", UHALF);
		}
	}
}
void mov(comun *C)
{
	C->direccion = _getch();
	if (C->direccion == 224)
		C->direccion = _getch();

	switch (C->direccion)
	{
	case 75://a
		C->direccion = LEFT;
		break;
	case 77://d
		C->direccion = RIGHT;
		break;
	case 72://w
		C->direccion = CWISE;
		break;
	case 80://s
		C->direccion = DOWN;
		break;
	case 13: //intro
		C->direccion = 'r';
		break;
	case 27: //esc
		menu(C, 0);
		break;
	case 9: //tab
		C->direccion = HOLD;
		break;
	case ' ':
		C->direccion = ' ';
		break;
	}
}
void menu(comun *C, int flag)
{
	FILE *fpt;
	int i, j, k;
	char a = 'a';
	int menu[14][36];
	color(BLACK, BLACK);
	for (i = 0; i < 12; i++)
	{
		gotoxy(p_menu_x, p_menu_y + i);
		for (j = 0; j < 9; j++)
		{
			printf("    ");
		}
	}

	C->menu = TRUE;
	color(DARKGRAY, BLACK);
	fpt = fopen("sino_mini.txt", "r");

	gotoxy(p_menu_x, p_menu_y); // 64 6
	if (flag == 0)
	{
		printf("PAUSA, QUIERES CONTINUAR EL JUEGO?");
	}

	if (flag == 1)
	{
		printf("Quieres jugar una partida nueva?");
	}


	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 36; j++)
		{
			fscanf(fpt, "%d", &menu[i][j]);
		}
	}
	for (i = 0; i < 14; i+=2)
	{
		gotoxy(p_menu_x, p_menu_y + i / 2 + 2);
		for (j = 0; j < 36; j++)
		{
			color(menu[i][j], menu[i + 1][j]);
			printf("%c", UHALF);
		}
	}

	color(DARKGRAY, BLACK);

	while (a != 'i')
	{
		gotoxy(p_menu_x, p_menu_y + 10);
		if (a == 'a')
		{
			for (i = 0; i < 18; i++)
				printf("%c", BLOCK);
			for (i = 0; i < 18; i++)
				printf(" ");
		}
		if (a == 'd')
		{
			for (i = 0; i < 18; i++)
				printf(" ");
			for (i = 0; i < 18; i++)
				printf("%c", BLOCK);
		}
		a = _getch();
		if (a == 224)
			a = _getch();
		switch (a)
		{
		case 77:
			a = 'd';
			C->menu = FALSE;
			break;
		case 75:
			a = 'a';
			C->menu = TRUE;
			break;
		case 13:
			a = 'i';
			break;
		}
	}
	tetris_logo_mini(C);
	fclose(fpt);

}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void color(int A, int B)
{
	int X = A + B * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X);
}
