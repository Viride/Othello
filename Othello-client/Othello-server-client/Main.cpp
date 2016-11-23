#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

int main(int argc, char** argv){

	al_init(); // inicjowanie biblioteki allegro
	al_install_keyboard(); // instalowanie sterownika klawiatury

	ALLEGRO_KEYBOARD_STATE klawiatura; // utworzenie struktury do odczytu stanu klawiatury
	ALLEGRO_DISPLAY *okno = al_create_display(320, 240);// tworzymy wska�nik okna, i podajemy jego szer. i wys
	al_set_window_title(okno, "Allegro5 kurs pierwsze okno");// podajemy tytu� okna
	
	while (al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE)) //koniec programu gdy wci�niemy klawisz Escape
	{
		printf("fun\n");
		al_get_keyboard_state(&klawiatura);  // odczyt stanu klawiatury
		al_clear_to_color(al_map_rgb(0, 255, 0)); // wyczyszczenie aktualnego bufora ekranu
		al_flip_display(); // wy�wietlenie aktualnego bufora na ekran
	}
	// usuwanie z pami�ci okna, bitmap, audio, font�w ...itd.
	al_rest(3);
	al_destroy_display(okno);
	return 0;
}