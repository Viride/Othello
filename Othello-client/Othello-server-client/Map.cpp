#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag≥Ûwkowy dodajπcy czcionki
#include <allegro5/allegro_ttf.h>



void board() {
	ALLEGRO_FONT *font = al_create_builtin_font();//  wskaünik do czcionki bitmapowej
	ALLEGRO_FONT *font_arial_18 = al_load_font("arial.ttf", 18, 0);//  wskaünik do czcionki bitmapowej
	al_clear_to_color(al_map_rgb(91, 180, 75)); // wyczyszczenie aktualnego bufora ekranu
	al_draw_text(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Witaj w Allegro");

}