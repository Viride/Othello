#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag³ówkowy dodaj¹cy czcionki
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "Map.h"
#include "Rules.h"
#include <utility>
#include <Windows.h>
#include <cstdlib>
#include <sstream>

button single{ 200, 200, width_p - 200, height_p - 350 };
button multi{ 200, 400, width_p - 200, height_p - 150 };
board game_board_offline;
board game_board_online;
bool offline_initialized = false;
bool online_initialized = false;

int myColor = 0;

int recvbuflen = DEFAULT_BUFLEN;
char *sendbuf = "ok\n";
char sendbufor[DEFAULT_BUFLEN];
char recvbuf[DEFAULT_BUFLEN];
int iResult;
bool connected_color = false;


void board_welcome(int mouse_x, int mouse_y, bool clicked, int &board_id) {
	
	ALLEGRO_FONT *arial_36 = al_load_font("arial.ttf", 36, 0);//  wskaŸnik do czcionki bitmapowej
	al_clear_to_color(background_color); // wyczyszczenie aktualnego bufora ekranu
	al_draw_filled_rectangle(single.x_up, single.y_up, single.x_down, single.y_down, button_color);
	al_draw_filled_rectangle(multi.x_up, multi.y_up, multi.x_down, multi.y_down, button_color);
	//al_draw_text(arial_36, black_color, 335, 255 , 0, "OFFLINE");
	//al_draw_text(arial_36, black_color, 340, 455, 0, "ONLINE");


	if (mouse_x >= single.x_up && mouse_x <= single.x_down && mouse_y >= single.y_up && mouse_y <= single.y_down) {
		board_id = 1;
		printf("Offline %d \n", board_id);
		if (offline_initialized == false) 
		{
			init_tab(game_board_offline);
			offline_initialized = true;
		}
		clear_colors(game_board_offline.tab_color);
	}
	else if (mouse_x >= multi.x_up && mouse_x <= multi.x_down && mouse_y >= multi.y_up && mouse_y <= multi.y_down) {
		board_id = 2;
		printf("Online %d \n", board_id);
		if (online_initialized == false) 
		{
			init_tab(game_board_online);
			online_initialized = true;
		}
		clear_colors(game_board_online.tab_color);
		connect();
	}
	else {}

	//al_draw_line(50, 200, width - 50, 400, al_map_rgb(0, 0, 255), 5);
}

void board_offline(int mouse_x, int mouse_y, bool clicked, int &board_id)
{
	ALLEGRO_FONT *arial_36 = al_load_font("arial.ttf", 36, 0);//  wskaŸnik do czcionki bitmapowej
	int x = 0, y = 0;
	bool end = false;
	bool change = false;
	draw_board_offline();
	draw_color(game_board_offline);
	is_end(game_board_offline.tab_color, end);
	if (end != true) 
	{
		x = mouse(mouse_x, mouse_y, game_board_offline).first;
		y = mouse(mouse_x, mouse_y, game_board_offline).second;
		if (x != 8 && y != 8) 
		{
			printf("x: %d, y: %d, turn: %d\n", x, y, game_board_offline.turn);
			check_move(x, y, game_board_offline.tab_color, game_board_offline.turn, change);
			if (change == true) 
			{
				if (game_board_offline.turn == black) game_board_offline.turn = white;
				else if (game_board_offline.turn == white) game_board_offline.turn = black;
			}
			is_move2(game_board_offline.tab_color, game_board_offline.turn);
		}
	}
	else 
	{
		for (int i = 8;i > 0;i--) {
			al_draw_filled_rectangle(150, 200, 650, 400, button_color);
			al_draw_text(arial_36, black_color, 240, 270, 0, "WHITE          BLACK");
			al_draw_textf(arial_36, black_color, 288, 300, 0, "%d                    %d", result(game_board_offline.tab_color).first, result(game_board_offline.tab_color).second);
			al_draw_textf(arial_36, black_color, 400, 330, 0, "%d", i);

			al_flip_display();
			Sleep(1000);
		}
		board_id = 0;
	}
}

void board_online(int mouse_x, int mouse_y, bool clicked, int &board_id, int ConnectSocket)
{
	if (connected_color == false) {
		iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
		if (recvbuf[2] == '1') myColor = white;
		else myColor = black;
		printf("Moj kolor to: %d\n", myColor);
		iResult = send(ConnectSocket, sendbuf, DEFAULT_BUFLEN, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
		}
		connected_color = true;
	}
	
	ALLEGRO_FONT *arial_36 = al_load_font("arial.ttf", 36, 0);//  wskaŸnik do czcionki bitmapowej

	if (game_board_online.turn == myColor && game_board_online.end != true) {

		int x = 0, y = 0;
		int send_number;
		game_board_online.end = false;
		bool change = false;
		draw_board_online();
		draw_color(game_board_online);
		is_end(game_board_online.tab_color, game_board_online.end);
		if (game_board_online.end != true)
		{

			if (game_board_online.turn == myColor) {
				x = mouse(mouse_x, mouse_y, game_board_online).first;
				y = mouse(mouse_x, mouse_y, game_board_online).second;
				if (x != 8 && y != 8)
				{
					//printf("x: %d, y: %d, turn: %d\n", x, y, game_board_online.turn);
					check_move(x, y, game_board_online.tab_color, game_board_online.turn, change);
					if (change == true)
					{
						if (game_board_online.turn == black)
						{
							game_board_online.turn = white;
							sendbufor[0] = x;
							sendbufor[1] = y;
							sendbufor[2] = game_board_online.turn;
							/*send_number = x * 100 + y * 10 + game_board_online.turn;
							std::string s = std::to_string(send_number);
							char const *sendbufor = s.c_str();*/
							printf("Wyslalem:: x: %c, y: %c, turn: %c\n", sendbufor[0]+48, sendbufor[1]+48, sendbufor[2]+48);
							iResult = send(ConnectSocket, sendbufor, DEFAULT_BUFLEN, 0);
							if (iResult == SOCKET_ERROR) {
								printf("send failed: %d\n", WSAGetLastError());
							}
						}
						else if (game_board_online.turn == white)
						{
							game_board_online.turn = black;
							sendbufor[0] = x;
							sendbufor[1] = y;
							sendbufor[2] = game_board_online.turn;
							/*send_number = x * 100 + y * 10 + game_board_online.turn;
							std::string s = std::to_string(send_number);
							char const *sendbufor = s.c_str();*/
							printf("Wyslalem:: x: %c, y: %c, turn: %c\n", sendbufor[0]+48, sendbufor[1]+48, sendbufor[2]+48);
							iResult = send(ConnectSocket, sendbufor, DEFAULT_BUFLEN, 0);
							if (iResult == SOCKET_ERROR) {
								printf("send failed: %d\n", WSAGetLastError());
							}
						}

					}
					is_move2(game_board_online.tab_color, game_board_online.turn);
				}
			}
		}
		else
		{
			sendbuf = "888\n";
			iResult = send(ConnectSocket, sendbuf, DEFAULT_BUFLEN, 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
			}
			for (int i = 8;i > 0;i--) {
				al_draw_filled_rectangle(150, 200, 650, 400, button_color);
				al_draw_text(arial_36, black_color, 240, 270, 0, "WHITE          BLACK");
				al_draw_textf(arial_36, black_color, 288, 300, 0, "%d                    %d", result(game_board_online.tab_color).first, result(game_board_online.tab_color).second);
				al_draw_textf(arial_36, black_color, 400, 330, 0, "%d", i);
				al_flip_display();
				Sleep(1000);
			}
			board_id = 0;
		
		
		}
		draw_board_online();
		draw_color(game_board_online);
	}
}

void board_online_receive(int mouse_x, int mouse_y, bool clicked, int &board_id, int ConnectSocket)
{
	
	if (game_board_online.turn != myColor && game_board_online.end != true) {
		int x = 0, y = 0, turn = 0;
		iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
		///obsuga odebranej wiadomosci
		x = recvbuf[0];
		y = recvbuf[1];
		turn = recvbuf[2];
		printf("Otrzymalem:: x: %d, y: %d, turn: %d\n", x, y, turn);
		bool change = false;
		draw_board_online();
		draw_color(game_board_online);
		is_end(game_board_online.tab_color, game_board_online.end);
		if (game_board_online.end != true)
		{

			if (x != 8 && y != 8)
			{
				//printf("x: %d, y: %d, turn: %d\n", x, y, game_board_online.turn);
				check_move(x, y, game_board_online.tab_color, game_board_online.turn, change);
				if (change == true)
				{
					if (game_board_online.turn == black)
					{
						game_board_online.turn = white;
					}
					else if (game_board_online.turn == white)
					{
						game_board_online.turn = black;
					}

				}
				is_move2(game_board_online.tab_color, game_board_online.turn);
			}

		}
		else
		{
			ALLEGRO_FONT *arial_36 = al_load_font("arial.ttf", 36, 0);//  wskaŸnik do czcionki bitmapowej

			sendbuf = "888\n";
			iResult = send(ConnectSocket, sendbuf, DEFAULT_BUFLEN, 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
			}
			for (int i = 8;i > 0;i--) {
				al_draw_filled_rectangle(150, 200, 650, 400, button_color);
				al_draw_text(arial_36, black_color, 240, 270, 0, "WHITE          BLACK");
				al_draw_textf(arial_36, black_color, 288, 300, 0, "%d                    %d", result(game_board_online.tab_color).first, result(game_board_online.tab_color).second);
				al_draw_textf(arial_36, black_color, 400, 330, 0, "%d", i);
				al_flip_display();
				Sleep(1000);
			}
			board_id = 0;
		}
		draw_board_online();
		draw_color(game_board_online);
	}
	
}

void draw_board_offline()
{
	al_clear_to_color(background_color); // wyczyszczenie aktualnego bufora ekranu

	al_draw_line(100, 75, 100, 675, line_color, 1);
	al_draw_line(175, 75, 175, 675, line_color, 1);
	al_draw_line(250, 75, 250, 675, line_color, 1);
	al_draw_line(325, 75, 325, 675, line_color, 1);
	al_draw_line(400, 75, 400, 675, line_color, 1);
	al_draw_line(475, 75, 475, 675, line_color, 1);
	al_draw_line(550, 75, 550, 675, line_color, 1);
	al_draw_line(625, 75, 625, 675, line_color, 1);
	al_draw_line(700, 75, 700, 675, line_color, 1);

	al_draw_line(100, 75, 700, 75, line_color, 1);
	al_draw_line(100, 150, 700, 150, line_color, 1);
	al_draw_line(100, 225, 700, 225, line_color, 1);
	al_draw_line(100, 300, 700, 300, line_color, 1);
	al_draw_line(100, 375, 700, 375, line_color, 1);
	al_draw_line(100, 450, 700, 450, line_color, 1);
	al_draw_line(100, 525, 700, 525, line_color, 1);
	al_draw_line(100, 600, 700, 600, line_color, 1);
	al_draw_line(100, 675, 700, 675, line_color, 1);
}

void draw_board_online()
{
	al_clear_to_color(background_color); // wyczyszczenie aktualnego bufora ekranu
	al_draw_line(100, 75, 100, 675, line_color, 1);
	al_draw_line(175, 75, 175, 675, line_color, 1);
	al_draw_line(250, 75, 250, 675, line_color, 1);
	al_draw_line(325, 75, 325, 675, line_color, 1);
	al_draw_line(400, 75, 400, 675, line_color, 1);
	al_draw_line(475, 75, 475, 675, line_color, 1);
	al_draw_line(550, 75, 550, 675, line_color, 1);
	al_draw_line(625, 75, 625, 675, line_color, 1);
	al_draw_line(700, 75, 700, 675, line_color, 1);

	al_draw_line(100, 75, 700, 75, line_color, 1);
	al_draw_line(100, 150, 700, 150, line_color, 1);
	al_draw_line(100, 225, 700, 225, line_color, 1);
	al_draw_line(100, 300, 700, 300, line_color, 1);
	al_draw_line(100, 375, 700, 375, line_color, 1);
	al_draw_line(100, 450, 700, 450, line_color, 1);
	al_draw_line(100, 525, 700, 525, line_color, 1);
	al_draw_line(100, 600, 700, 600, line_color, 1);
	al_draw_line(100, 675, 700, 675, line_color, 1);

}

void init_tab(board &game_board)
{
	for (int i = 0;i < 9;i++) {
		std::vector<int> temp;
		for (int j = 0;j < 9;j++) {
			temp.push_back(0);
		}
		game_board.tab_color.push_back(temp);
	}
	int x = 100;
	int y = 75;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			game_board.tab_x_up[j][i]=x;
			game_board.tab_x_down[j][i]=x+74;
			game_board.tab_y_up[i][j]=y;
			game_board.tab_y_down[i][j]=y+74;
			game_board.tab_color[i][j] = 0;
		}
		x = x + 75;
		y = y + 75;
	}
	game_board.end = false;
	/*game_board.tab_color[3][3] = white;
	game_board.tab_color[3][4] = black;
	game_board.tab_color[4][3] = black;
	game_board.tab_color[4][4] = white;*/
	/*game_board.tab_color[0][0] = black;
	game_board.tab_color[1][1] = white;
	game_board.tab_color[2][2] = white;*/
	//game_board.tab_color[2][4] = black;
	game_board.turn = white;
	printf("Initializing complete\n");
}

void draw_color(board game_board)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game_board.tab_color[i][j] == black) 
			{
				al_draw_filled_rectangle(game_board.tab_x_up[i][j], game_board.tab_y_up[i][j], game_board.tab_x_down[i][j], game_board.tab_y_down[i][j], black_color);
			}
			else if (game_board.tab_color[i][j] == white)
			{
				al_draw_filled_rectangle(game_board.tab_x_up[i][j], game_board.tab_y_up[i][j], game_board.tab_x_down[i][j], game_board.tab_y_down[i][j], white_color);
			}
		}
	}
	if (game_board.turn == white) {
		//al_draw_filled_rectangle(0, 0, 99, 700, white_color);
		//al_draw_filled_rectangle(701, 0, 800, 700, white_color);
		al_draw_filled_rounded_rectangle(150, 20, 650, 60, 5, 5, white_color);

	}
	else 
	{
		//al_draw_filled_rectangle(0, 0, 99, 700, black_color);
		//al_draw_filled_rectangle(701, 0, 800, 700, black_color);
		al_draw_filled_rounded_rectangle(150, 20, 650, 60, 5, 5, black_color);
	}
}


std::pair<int, int> mouse(int mouse_x, int mouse_y, board &game_board)
{
	std::pair<int, int> mouse_cords;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (mouse_y > game_board.tab_y_up[i][j] && mouse_y < game_board.tab_y_down[i][j] &&
				(mouse_x > game_board.tab_x_up[i][j] && mouse_x < game_board.tab_x_down[i][j])) 
			{
				mouse_cords.first = i;
				mouse_cords.second = j;
				return mouse_cords;
			}

		}
	}
	mouse_cords.first = 8;
	mouse_cords.second = 8;
	return mouse_cords;
	
}

void connect()
{
}

void clear_colors(std::vector<std::vector<int>>& tab_color)
{
	for (int i = 0;i < 8; i++) {
		for (int j = 0;j < 8; j++) {
			tab_color[i][j] = 0;
		}
	}
	tab_color[3][3] = white;
	tab_color[3][4] = black;
	tab_color[4][3] = black;
	tab_color[4][4] = white;
	//tab_color[0][0] = black;
	//tab_color[1][1] = white;
	//tab_color[2][2] = white;
	//tab_color[2][4] = black;
	/*tab_color[0][0] = white;
	tab_color[1][1] = black;
	tab_color[2][2] = black;
	tab_color[4][4] = black;*/

}
