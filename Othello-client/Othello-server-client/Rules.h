#pragma once
#define background_color al_map_rgb(91, 180, 75)
#define button_color al_map_rgb(61, 133, 220)
#define black_color al_map_rgb(0, 0, 0)
#define black 33
#define white 34


void check_move(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &change);
void check_up(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_up_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_down_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void check_up_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move(std::vector<std::vector<int>> &tab_color, int turn, bool &is_move_b);
void is_move_up(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_up_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down_right(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_down_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_move_up_left(int x, int y, std::vector<std::vector<int>> &tab_color, int turn, bool &move);
void is_end(std::vector<std::vector<int>> tab_color, bool &end);
std::pair<int, int> result(std::vector<std::vector<int>> tab_color);

