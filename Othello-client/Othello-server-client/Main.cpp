#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag≥Ûwkowy dodajπcy czcionki
#include <allegro5/allegro_ttf.h>
#include "Map.h"

void init() {
	al_install_keyboard(); // instalowanie sterownika klawiatury
	al_init_primitives_addon();
	al_install_mouse();
}



int main(int argc, char** argv){

	al_init(); // inicjowanie biblioteki allegro
	init();
	
	al_set_new_window_position(300, 30);
	ALLEGRO_DISPLAY *display = al_create_display(800, 700);// tworzymy wskaünik okna, i podajemy jego szer. i wys
	al_set_window_title(display, "Othello");// podajemy tytu≥ okna
	
	//KLAWIATURA I MYSZKA
	ALLEGRO_KEYBOARD_STATE klawiatura; // utworzenie struktury do odczytu stanu klawiatury
	al_get_keyboard_state(&klawiatura);

	//EVENTY
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	
	
	while (!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE)) //koniec programu gdy wciúniemy klawisz Escape
	{
		ALLEGRO_EVENT ev;

		al_get_keyboard_state(&klawiatura);  // odczyt stanu klawiatury
		board();
		al_flip_display(); // wyúwietlenie aktualnego bufora na ekran
	}

	//al_rest(3);
	al_destroy_display(display);
	return 0;
}