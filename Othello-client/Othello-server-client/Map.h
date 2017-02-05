#pragma once
#include <vector>
#define background_color al_map_rgb(91, 180, 75)
#define button_color al_map_rgb(61, 133, 220)
#define black_color al_map_rgb(0, 0, 0)
#define white_color al_map_rgb(255, 255, 255)
#define line_color al_map_rgb(255, 0, 0)
#define width_p 800
#define height_p 700
#define black 2
#define white 1

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "1234"
//#define DEFAULT_ADDRES "192.168.1.10"

typedef struct //Struktura buttonów na ekranie g³ównym
{
	int x_up;
	int y_up;
	int x_down;
	int y_down;
}button;

typedef struct //struktura tablicy do gry
{
	int tab_x_up[8][8];
	int tab_y_up[8][8];
	int tab_x_down[8][8];
	int tab_y_down[8][8];
	int turn;
	bool end;
	std::vector<std::vector<int> > tab_color;

}board;

void board_welcome(int mouse_x, int mouse_y, bool clicked, int &board_id);	//Wyœwietlanie i obs³uga ekranu startowego
void board_offline(int mouse_x, int mouse_y, bool clicked, int &board_id);  //Wyœwietlanie i obs³uga gry offline
void board_online(int mouse_x, int mouse_y, bool clicked, int &board_id, int ConnectSocket); //Wyœwietlanie i obs³uga wysy³ania gry online
void board_online_receive(int mouse_x, int mouse_y, bool clicked, int &board_id, int ConnectSocket); //Wyœwietlanie i obs³uga wysy³ania gry online
void draw_board_offline();													//Rysowanie planszy offline
void draw_board_online();													//Rysowanie planszy online
void init_tab(board &game_board);											//Inicjalizacja struktur
void draw_color(board game_board);											//Malowanie pól
std::pair<int, int> mouse(int mouse_x, int mouse_y, board &game_board);		//Obs³uga myszy
void clear_colors(std::vector<std::vector<int>> &tab_color);				//Inicjalizacja ustawieñ pocz¹tkowych dla pól


