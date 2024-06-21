#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>

#define USERS_DATABASE  ".USERS.csv"
#define TOKENS_DATABASE ".TOKENS.csv"

#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 32


char login_choice = 0;

char username[MAX_USERNAME_LENGTH] = {0};
char password[MAX_PASSWORD_LENGTH] = {0};

void show_initial_menu(){
    
    do{
        printf("insert \"L\" if you want to login, insert \"R\" if you want to register a new user: ");
        scnaf(" %c",&login_choice);
        login_choice = tolower(login_choice);
    }while( login_choice != 'l' || login_choice != 'r');

    
}

bool verify_username_and_password(){
    char founded_username[] = search_for_username();
    char founded_password[] = search_password_with_username();

    if( !strcmp(founded_password, password) && !strcmp(founded_username, username)){
        return true;
    }

    return false;

}

char* search_for_username(){
    FILE *users_fp = fopen(USERS_DATABASE, "rt");

    while( !feof(users_fp) ){
        int count = 0;
        char *csv, token;
        fscnaf(users_fp, "%s", csv);
        token = strtok(csv, ",");

        while (token != NULL) {
            if (count == 2) {
                return token;
            }

            token = strtok(NULL, ",");
            count++;
        }
    }

}

void show_login_menu(){
    bool login_successful = false;

    do{
        printf("inserisci lo user (massimo 32 caratteri): ");
        fgets(username, MAX_USERNAME_LENGTH, stdin);
        printf("inserisci la password (massimo 32 caratteri): ");
        fgets(password, MAX_PASSWORD_LENGTH, stdin);

        login_successful = verify_username_and_password();

        if(!login_successful){
            printf("Username o passwod sbagliati, ma non ti dico quale");
        }

    }while(!login_successful);

}

void show_register_menu(){

}

void process_login_choice(){
    switch (login_choice){
        case 'l':
            show_login_menu();
            break;
        case 'r':
            show_register_menu();
            break;
    }

}


void main(void){
    show_initial_menu();
    
    process_login_choice();


    return;
}
