#pragma once
#define background_color al_map_rgb(91, 180, 75)
#define button_color al_map_rgb(61, 133, 220)
#define black_color al_map_rgb(0, 0, 0)
#define black 2
#define white 1


void check_move(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &change);		//Obs³uga sprawdzañ ruchów
void check_up(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);			//Sprawdzenie i robienie ruchu w górê
void check_up_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);		//Dalej odpowiednio wed³ug wskazówek zegara
void check_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_up_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);

//void is_move(std::vector<std::vector<int>> &tab_color, int turn, bool &is_move_b);					
void is_move2(std::vector<std::vector<int>> &tab_color, int &turn);										//Obsuga sprawdzenia czy jest ruch
void is_move_up(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);			//Sprawdzenie czy jest ruch w górê
void is_move_up_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);	//Dalej odpowiednio wed³ug wskazówek zegara
void is_move_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_up_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);

void is_end(std::vector<std::vector<int>> tab_color, bool &end);										//Sprawdzenie czy jest koniec gry
std::pair<int, int> result(std::vector<std::vector<int>> tab_color);									//Zwrócenie wyniku gry

