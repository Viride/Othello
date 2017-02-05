#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag³ówkowy dodaj¹cy czcionki
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <vector>
#include "Rules.h"

//pionowo x, poziomo y

void check_move(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &change) {
	
	bool move = false;
	check_up(x, y, tab_color, turn, move);
	check_up_right(x, y, tab_color, turn, move);
	check_right(x, y, tab_color, turn, move);
	check_down_right(x, y, tab_color, turn, move);
	check_down(x, y, tab_color, turn, move);
	check_down_left(x, y, tab_color, turn, move);
	check_left(x, y, tab_color, turn, move);
	check_up_left(x, y, tab_color, turn, move);
	if (move == true) 
	{
		tab_color[x][y] = turn;
		change = true;
		move = false;
	}
}
/*
void is_move(std::vector<std::vector<int>>& tab_color, int turn, bool & is_move_b)
{
	bool move = false;
	for (int x = 0;x < 8; x++) {
		for (int y = 0;y < 8; y++) {
			is_move_up(x, y, tab_color, turn, move);
			is_move_up_right(x, y, tab_color, turn, move);
			is_move_right(x, y, tab_color, turn, move);
			is_move_down_right(x, y, tab_color, turn, move);
			is_move_down(x, y, tab_color, turn, move);
			is_move_down_left(x, y, tab_color, turn, move);
			is_move_left(x, y, tab_color, turn, move);
			is_move_up_left(x, y, tab_color, turn, move);
			if (move == true)
			{
				is_move_b = true;
				break;
			}
		}
		if (move == true)
		{
			is_move_b = true;
			break;
		}
	}
}
*/
void is_move2(std::vector<std::vector<int>>& tab_color, int & turn)
{
	bool move = false;
	for (int x = 0;x < 8; x++) {
		for (int y = 0;y < 8; y++) {
			is_move_up(x, y, tab_color, turn, move);
			is_move_up_right(x, y, tab_color, turn, move);
			is_move_right(x, y, tab_color, turn, move);
			is_move_down_right(x, y, tab_color, turn, move);
			is_move_down(x, y, tab_color, turn, move);
			is_move_down_left(x, y, tab_color, turn, move);
			is_move_left(x, y, tab_color, turn, move);
			is_move_up_left(x, y, tab_color, turn, move);
			if (move == true)
			{
				break;
			}
		}
		if (move == true)
		{
			break;
		}
	}
	if (move == false) {
		if (turn == black) turn = white;
		else if (turn == white) turn = black;
	}
}

void check_up(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		for (int i = x-2; i >= 0; i--)
		{
			if (tab_color[x - 1][y] == turn || tab_color[x - 1][y] == 0) break;
			if (tab_color[x - 2][y] == 0) break;
			if ((tab_color[i][y] != 0) && (tab_color[i][y] == turn)) {
				ok = true;
			}
		}
		if (ok == true) {
			move = true;
			int i = x - 1;
			while (tab_color[i][y] != turn  && tab_color[i][y] != 0) {
				tab_color[i][y] = turn;
				i--;
			}
		}
		
	}
}

void is_move_up(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		for (int i = x - 2; i >= 0; i--)
		{
			if (tab_color[x - 1][y] == turn || tab_color[x - 1][y] == 0) break;
			if (tab_color[x - 2][y] == 0) break;
			if ((tab_color[i][y] != 0) && (tab_color[i][y] == turn)) {
				move = true;
			}
		}

	}
}

void check_up_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		int i = x - 2, j = y + 2;
		while ((i >= 0) && (j < 8))
		{
			if (tab_color[x - 1][y + 1] == turn || tab_color[x - 1][y + 1] == 0) break;
			if (tab_color[x - 2][y + 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				ok = true;
			}
			i--;
			j++;
		}
		if (ok == true) {
			move = true;
			int i = x - 1;
			int j = y + 1;

			while (tab_color[i][j] != turn  && tab_color[i][j] != 0) {
				tab_color[i][j] = turn;
				i--;
				j++;
			}
		}

	}
}

void is_move_up_right(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		int i = x - 2, j = y + 2;
		while ((i >= 0) && (j < 8))
		{
			if (tab_color[x - 1][y + 1] == turn || tab_color[x - 1][y + 1] == 0) break;
			if (tab_color[x - 2][y + 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				move = true;
			}
			i--;
			j++;
		}
	}
}

void check_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		for (int i = y + 2; i < 8; i++)
		{
			if (tab_color[x][y + 1] == turn || tab_color[x][y + 1] == 0) break;
			if (tab_color[x][y + 2] == 0) break;
			if ((tab_color[x][i] != 0) && (tab_color[x][i] == turn)) {
				ok = true;
			}
		}
		if (ok == true) {
			move = true;
			int i = y + 1;
			while (tab_color[x][i] != turn && tab_color[x][i] != 0) {
				tab_color[x][i] = turn;
				i++;
			}
		}

	}
}

void is_move_right(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		for (int i = y + 2; i < 8; i++)
		{
			if (tab_color[x][y + 1] == turn || tab_color[x][y + 1] == 0) break;
			if (tab_color[x][y + 2] == 0) break;
			if ((tab_color[x][i] != 0) && (tab_color[x][i] == turn)) {
				move = true;
			}
		}
	}
}

void check_down_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		int i = x + 2, j = y + 2;
		while ((i < 8) && (j < 8))
		{
			if (tab_color[x + 1][y + 1] == turn || tab_color[x + 1][y + 1] == 0) break;
			if (tab_color[x + 2][y + 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				ok = true;
			}
			i++;
			j++;
		}
		if (ok == true) {
			move = true;
			int i = x + 1;
			int j = y + 1;

			while (tab_color[i][j] != turn  && tab_color[i][j] != 0) {
				tab_color[i][j] = turn;
				i++;
				j++;
			}
		}

	}
}

void is_move_down_right(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		int i = x + 2, j = y + 2;
		while ((i < 8) && (j < 8))
		{
			if (tab_color[x + 1][y + 1] == turn || tab_color[x + 1][y + 1] == 0) break;
			if (tab_color[x + 2][y + 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				move = true;
			}
			i++;
			j++;
		}
	}
}

void check_down(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		for (int i = x + 2; i < 8; i++)
		{
			if (tab_color[x + 1][y] == turn || tab_color[x + 1][y] == 0) break;
			if (tab_color[x + 2][y] == 0) break;
			if ((tab_color[i][y] != 0) && (tab_color[i][y] == turn)) {
				ok = true;
			}
		}
		if (ok == true) {
			move = true;
			int i = x + 1;
			while (tab_color[i][y] != turn  && tab_color[i][y] != 0) {
				tab_color[i][y] = turn;
				i++;
			}
		}

	}
}

void is_move_down(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		for (int i = x + 2; i < 8; i++)
		{
			if (tab_color[x + 1][y] == turn || tab_color[x + 1][y] == 0) break;
			if (tab_color[x + 2][y] == 0) break;
			if ((tab_color[i][y] != 0) && (tab_color[i][y] == turn)) {
				move = true;
			}
		}
	}
}

void check_down_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		int i = x + 2, j = y - 2;
		while ((i < 8) && (j >= 0))
		{
			if (tab_color[x + 1][y - 1] == turn || tab_color[x + 1][y - 1] == 0) break;
			if (tab_color[x + 2][y - 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				ok = true;
			}
			i++;
			j--;
		}
		if (ok == true) {
			move = true;
			int i = x + 1;
			int j = y - 1;

			while (tab_color[i][j] != turn  && tab_color[i][j] != 0) {

				tab_color[i][j] = turn;
				i++;
				j--;
			}
		}

	}
}

void is_move_down_left(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		int i = x + 2, j = y - 2;
		while ((i >= 0) && (j >= 0))
		{
			if (tab_color[x + 1][y - 1] == turn || tab_color[x + 1][y - 1] == 0) break;
			if (tab_color[x + 2][y - 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				move = true;
			}
			i++;
			j--;
		}
	}
}

void check_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		for (int i = y - 2; i >= 0; i--)
		{
			if (tab_color[x][y - 1] == turn || tab_color[x][y - 1] == 0) break;
			if (tab_color[x][y - 2] == 0) break;
			if ((tab_color[x][i] != 0) && (tab_color[x][i] == turn)) {
				ok = true;
			}
		}
		if (ok == true) {
			move = true;
			int i = y - 1;
			while (tab_color[x][i] != turn  && tab_color[x][i] != 0) {
				tab_color[x][i] = turn;
				i--;
			}
		}

	}
}

void is_move_left(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		for (int i = y - 2; i >= 0; i--)
		{
			if (tab_color[x][y - 1] == turn || tab_color[x][y - 1] == 0) break;
			if (tab_color[x][y - 2] == 0) break;
			if ((tab_color[x][i] != 0) && (tab_color[x][i] == turn)) {
				move = true;
			}
		}
	}
}

void check_up_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move)
{
	if (tab_color[x][y] == 0) {
		bool ok = false;
		int i = x - 2, j = y - 2;
		while ((i >= 0) && (j >= 0))
		{
			if (tab_color[x - 1][y - 1] == turn || tab_color[x - 1][y - 1] == 0) break;
			if (tab_color[x - 2][y - 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				ok = true;
			}
			i--;
			j--;
		}
		if (ok == true) {
			move = true;
			int i = x - 1;
			int j = y - 1;

			while (tab_color[i][j] != turn  && tab_color[i][j] != 0) {
				tab_color[i][j] = turn;
				i--;
				j--;
			}
		}

	}
}

void is_move_up_left(int x, int y, std::vector<std::vector<int>>& tab_color, int turn, bool & move)
{
	if (tab_color[x][y] == 0) {
		int i = x - 2, j = y - 2;
		while ((i >= 0) && (j >= 0))
		{
			if (tab_color[x - 1][y - 1] == turn || tab_color[x - 1][y - 1] == 0) break;
			if (tab_color[x - 2][y - 2] == 0) break;
			if ((tab_color[i][j] != 0) && (tab_color[i][j] == turn)) {
				move = true;
			}
			i--;
			j--;
		}
	}
}

void is_end(std::vector<std::vector<int>> tab_color, bool & end)
{
	int white_score = 0; 
	int black_score = 0;
	for (int x = 0;x < 8; x++) {
		for (int y = 0;y < 8; y++) {
			if (tab_color[x][y] == white) white_score++;
			if (tab_color[x][y] == black) black_score++;
		}
	}
	if ((white_score + black_score) == 64) end = true;
	if (white_score == 0 || black_score == 0) end = true;
}

std::pair<int, int> result(std::vector<std::vector<int>> tab_color)
{
	int white_score = 0;
	int black_score = 0;
	for (int x = 0;x < 8; x++) {
		for (int y = 0;y < 8; y++) {
			if (tab_color[x][y] == white) white_score++;
			if (tab_color[x][y] == black) black_score++;
		}
	}
	return std::pair<int, int>(white_score, black_score);
}







