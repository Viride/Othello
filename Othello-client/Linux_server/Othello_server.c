#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define bufor 1024
#define white 1234567
#define black 1234568

char cbBuf[bufor];
int nBytes;
char text_white[bufor];
char text[bufor];
char text_black[bufor];
char read_white[bufor];
char read_black[bufor];
char finish[bufor];
char ok[bufor];
int flaga=0;
//struktura zawierająca dane, które zostaną przekazane do wątku
struct thread_data_t
{
    int socket;
};

//funkcja opisującą zachowanie wątku - musi przyjmować argument typu (void *) i zwracać (void *)
void *ThreadBehavior(void *t_data)
{
    struct thread_data_t *th_data = (struct thread_data_t*)t_data;
    //dostęp do pól struktury: (*th_data).pole
    while(1){
	bzero(cbBuf,1024);
    	read((*th_data).socket, cbBuf, bufor);
    	printf("%s\n", cbBuf);
	if(cbBuf[0]=='q') break;
    }


    pthread_exit(NULL);
}

//funkcja obsługująca połączenie z nowym klientem
void handleConnection(int player_white, int player_black) {
	//wynik funkcji tworzącej wątek


    strcpy(ok, "ok\n");
    strcpy(finish, "888\n");
	strcpy(text_white,"881\n");
	strcpy(text_black,"882\n");
	write(player_white, text_white, bufor);
	write(player_black, text_black, bufor);
	
		
	read(player_white, read_white, bufor);
	if(strcmp(read_white, ok)!=0){
		printf("blad_white");
    }
	read(player_black, read_black, bufor);
	if(strcmp(read_black, ok)!=0){
		printf("blad_black");
    }
	printf("Gracze podlaczeni\n");
	int stop=0;
	int turn=white;
	while(stop==0){
		if(turn==white){
printf("Tura bialego\n");
			read(player_white, read_white, bufor);
printf("Wysylam czarnemu\n");
			write(player_black, read_white, bufor);
			printf("%s\n", read_white);
			if (read_white[2]==1) turn=white;
			else turn=black;
		}
		else if(turn==black){
printf("Tura czarnego\n");
			read(player_black, read_black, bufor);
printf("Wysylam bialemu\n");
			write(player_white, read_black, bufor);
			printf("%s\n", read_black);
			if (read_white[2]==1) turn=white;
			else turn=white;
		}
        if(strcmp(read_white, finish)==0 || strcmp(read_black, finish)==0){
            stop=1;

        }
	}

}

int main(int argc, char* argv[])
{
   int server_socket_descriptor;
   int connection_socket_descriptor;
   int player_white;
   int player_black;
   int bind_result;
   int listen_result;
   char reuse_addr_val = 1;
   struct sockaddr_in server_address;

   //inicjalizacja gniazda serwera

   memset(&server_address, 0, sizeof(struct sockaddr));
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(SERVER_PORT);

   server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket_descriptor < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
       exit(1);
   }
   setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

   bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
   if (bind_result < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
       exit(1);
   }

   listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
   if (listen_result < 0) {
       fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
       exit(1);
   }

    printf("Praca: start\n");
//   while(1)
//  {
        printf("Czekam na gracza: white\n");
        player_white = accept(server_socket_descriptor, NULL, NULL);
        if (player_white < 0)
        {
            fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            exit(1);
        }
        printf("Czekam na gracza: black\n");
        player_black = accept(server_socket_descriptor, NULL, NULL);
        if (player_black < 0)
        {
            fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            exit(1);
        }

       handleConnection(player_white, player_black);
 //  }
    printf("Praca: koniec\n");
    close(server_socket_descriptor);
    return(0);
}
