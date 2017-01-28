#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag³ówkowy dodaj¹cy czcionki
#include <allegro5/allegro_ttf.h>
#include "Map.h"

//#define width 800
//#define height 700

int mouse_x;
int mouse_y;
int board_id = 0;
bool clicked = false;
bool done = false;

void init() {
	al_install_keyboard(); // instalowanie sterownika klawiatury
	al_init_primitives_addon();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
}



int main(int argc, char** argv){

	al_init(); // inicjowanie biblioteki allegro
	init();
	

	al_set_new_window_position(300, 30);
	ALLEGRO_DISPLAY *display = al_create_display(width_p, height_p);// tworzymy wskaŸnik okna, i podajemy jego szer. i wys
	al_set_window_title(display, "Othello");// podajemy tytu³ okna
	


	//EVENTY
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());


	board_welcome(mouse_x, mouse_y, clicked, board_id);



	while (!done) //koniec programu gdy wciœniemy klawisz Escape
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_UP) 
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
			{
				done = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) 
		{
			if (board_id == 0) {
				board_welcome(mouse_x, mouse_y, clicked, board_id);
			}
		}
		else if (ev.type = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1) {
				mouse_x = ev.mouse.x;
				mouse_y = ev.mouse.y;
				switch (board_id)
				{
				case 0:
					board_welcome(mouse_x, mouse_y, clicked, board_id);
					break;
				case 1:
					board_offline(mouse_x, mouse_y, clicked, board_id);
					break;
				case 2:
					board_online(mouse_x, mouse_y, clicked, board_id);
					break;
				}

			}
			//tu bêdzie odwo³anie do ob³sugi klikniêcia
		}
		
		al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
	}

	//al_rest(3);
	al_destroy_display(display);
	return 0;
}