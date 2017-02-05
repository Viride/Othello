#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h> // Plik nag³ówkowy dodaj¹cy czcionki
#include <allegro5/allegro_ttf.h>
#include "Map.h"
#include <fstream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


int mouse_x;
int mouse_y;
int board_id = 0;
bool connected = false;
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

	std::fstream plik;
	plik.open("adres.txt", std::ios::in);
	if (plik.good() == true)
	{
		printf("Uzyskano dostep do pliku!\n");
		//tu operacje na pliku
	}
	else printf("Nie uzyskano dostepu do pliku!\n");


	char dane[16];
	plik.getline(dane, 16); //wczytanie CA£EGO jednego wiersza danych
	plik.close();
	///ADDED
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}


	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;


	// Resolve the server address and port
	iResult = getaddrinfo(dane, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	SOCKET ConnectSocket = INVALID_SOCKET;
	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
		ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

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
		else if (ev.type = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //gdy wcisniemy przycisk myszki uruchomia sie odpowiednie eventy
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
					//£¹czenie z serverem
					if (connected == false) {
						iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
						if (iResult == SOCKET_ERROR) {
							closesocket(ConnectSocket);
							ConnectSocket = INVALID_SOCKET;
						}
						freeaddrinfo(result);

						if (ConnectSocket == INVALID_SOCKET) {
							printf("Unable to connect to server!\n");
							WSACleanup();
							return 1;
						}
						printf("Polaczony\n");
						connected = true;
					}
					board_online(mouse_x, mouse_y, clicked, board_id, ConnectSocket); //Wysy³anie ruchu
					al_flip_display();
					board_online_receive( mouse_x, mouse_y, clicked, board_id, ConnectSocket); //Odbiór ruchu
					break;
				}

			}
		}
		
		al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
	}

	//Sprz¹tanie
	al_destroy_display(display);
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}