
//======================================= IMPORTS & DEFINES ======================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#pragma pack(1)

#define MAX 500
#define DEF 64
//================================================================================================//





//========================================== STRUCTURES ==========================================//
// Client struct:
typedef struct Client {
    char first_name[DEF], name[DEF], full_name[DEF];
    int age;
    char gender;    
    char phone_number[DEF];
    char national_id_card[DEF];
    char city[DEF];
    char adress[DEF];
} Client;


// Enumeration:
typedef enum Bool {
    OFF, // False (0)
    ON // True (1)
} Bool;
//================================================================================================//





//========================================== PROTOTYPES ==========================================//
/*------------ MENU COMMANDS ------------*/
char MainMenuDisplay(char);
char ClientManagementMenu(char);
char SeekClientMenu(char);
char DeleteClientMenu(char);
char BillManagementMenu(char);
/*---------------------------------------*/


/*----------------COMMANDS----------------*/
void AddClient(Client[], int);
void DisplayClient(Client[], int);
void DeleteClient(Client[], int, int);
void SameCityClients(Client[], int);
/*----------------------------------------*/


/*-------------SEEK FUNCTIONS-------------*/
Bool HavePhoneNum(Client[], int, int*);
Bool HaveNationalID(Client[], int, int*);
Bool HaveName(Client[], int, int*);
/*----------------------------------------*/


/*------------VERIFY FUNCTIONS------------*/
void VerifyPhoneNum(char[]);
void VerifyNationalID(char[]);
/*----------------------------------------*/


/*----------------- UTIL -----------------*/
void input(char[] , int);
float BillCost(int, int);
char* fusename(char[], char[]); 
/*----------------------------------------*/
//================================================================================================//





//============================================= MAIN =============================================//
int main(){
    Bool in_main_menu = ON, in_cl_management, in_bill_management, in_seek_cl, in_delete_cl;
    Client Cl[MAX], *p_Cl = Cl;

    int cl_nbr = 0;
    char option;
    int pos, *p_pos = &pos;

    int min, sec;


    while(in_main_menu){ 
        //MAIN MENU
        option = MainMenuDisplay(option);
        switch(option){
            case '1': //CLIENT MANAGEMENT
            in_cl_management = ON;
            do {
                option = ClientManagementMenu(option);
                switch(option){
                    case '1': //ADD CLIENT
                    if(cl_nbr < MAX){
                        AddClient(p_Cl, cl_nbr);
                        cl_nbr++;
                    } else {
                        printf("> Can't have more than %d clients in our server.\n", MAX);
                    }
                    break;


                    case '2': //SEEK CLIENT
                    in_seek_cl = ON;
                    do {
                        option = SeekClientMenu(option);
                        switch(option){
                            case '1': //BY PHONE NUMBER
                            if(HavePhoneNum(p_Cl, cl_nbr, p_pos)){
                                DisplayClient(p_Cl, pos);
                            } else {
                                printf("> The desired client was not found in our server.\n");
                            }
                            break;

                            case '2': //BY ID CARD
                            if(HaveNationalID(p_Cl, cl_nbr, p_pos)){
                                DisplayClient(p_Cl, pos);
                            } else {
                                printf("> The desired client was not found in our server.\n");  
                            }
                            break;

                            case '3': //BACK TO CLIENT MANAGEMENT
                            in_seek_cl = OFF;
                            break;
                        }                        
                    } while(in_seek_cl);
                    break;


                    case '3': //DELETE CLIENT
                    in_delete_cl = ON;
                    do {
                        option = DeleteClientMenu(option);
                        switch(option){
                            case '1': //BY PHONE NUMBER
                            if(HavePhoneNum(p_Cl, cl_nbr, p_pos)){
                                DeleteClient(p_Cl, cl_nbr, pos);
                                cl_nbr--;
                                printf("> Clients remaining: %d\n", cl_nbr);
                            } else {
                                printf("> The desired client was not found in our server.\n");
                            }
                            break;

                            case '2': //BY FIRST NAME & NAME
                            if(HaveName(p_Cl, cl_nbr, p_pos)){
                                DeleteClient(p_Cl,cl_nbr, pos);
                                cl_nbr--;
                                printf("> Clients remaining: %d\n", cl_nbr);
                            } else {
                                printf("> The desired client was not found in our server.\n");
                            }
                            break;

                            case '3': //BACK TO CLIENT MANAGEMENT
                            in_delete_cl = OFF;
                            break;
                        }
                    } while(in_delete_cl);
                    break;


                    case '4': //DISPLAY LIST
                    SameCityClients(p_Cl, cl_nbr);
                    break;


                    case '5': //BACK TO MAIN MENU
                    in_cl_management = OFF;
                    break;
                }
                                
            } while(in_cl_management);
            break;



            case '2': //BILL MAMAGEMENT   
            do {
                option = BillManagementMenu(option);
                switch(option){
                    case '1': //WITH SUBSCRIPTION
                    printf("> Bill payed successfully.\n    Cost: 200 DH\n\n");
                    break;

                    case '2': //WITH SUBSCRIPTION
                    printf("> Give us the call duration:\n");
                    BillCost(min, sec);
                    break;

                    case '3': //BACK TO MAIN MENU
                    in_bill_management = OFF;
                    break;
                }         
                                
            } while(in_bill_management);
            break;



            case '3': //END PROGRAM
            return 0;


        }

    }

}
//================================================================================================//





//=========================================== FUNCTIONS ==========================================//


/*----------------------------------MENU COMMANDS----------------------------------*/
char MainMenuDisplay(char cmd){
    printf("\n                                                 \n\n");
    printf("                     MAIN MENU                     \n\n");
    printf(" 1. CLIENTS MANAGMENT                                \n");
    printf(" 2. BILLS MANAGMENT                                  \n");
    printf(" 3. EXIT                                             \n");
    printf("                            Input: "); scanf(" %c", &cmd);
    printf("\n                                                 \n\n");    
    return cmd;
}

char ClientManagementMenu(char cmd){
    printf("                 CLIENTS MANAGMENT                 \n\n");
    printf(" 1. Add client                                       \n");
    printf(" 2. Seek client                                      \n");
    printf(" 3. Delete client                                    \n");
    printf(" 4. Display a list of clients from a specific city   \n");
    printf(" 5. MAIN MENU                                        \n");
    printf("                            Input: "); scanf(" %c", &cmd);
    printf("\n                                                   \n");

    return cmd;
}

char SeekClientMenu(char cmd){
    printf("                 SEEK A CLIENT                   \n\n");
    printf(" 1. Phone number                                   \n");
    printf(" 2. ID national card number                        \n");
    printf(" 3. UNDO                                           \n");
    printf("                          Input: "); scanf(" %c", &cmd);
    printf("\n                                                 \n");
    return cmd;
}

char DeleteClientMenu(char cmd){
    printf("                 REMOVING A CLIENT               \n\n");
    printf(" 1. Phone number                                   \n");
    printf(" 2. Full name                                      \n");
    printf(" 3. Undo                                           \n");
    printf("                          Input: "); scanf(" %c", &cmd);
    return cmd;
}

char BillManagementMenu(char cmd){
    printf("                 BILLS MANAGMENT                 \n\n");
    printf(" 1. With subscription                              \n");
    printf(" 2. Without subscription                           \n");
    printf(" 3. MAIN MENU                                      \n");
    printf("                          Input: "); scanf(" %c", &cmd);
    printf("\n                                                 \n");
    return cmd;
}
/*-----------------------------------------------------------------------------*/




/*----------------------------------COMMANDS----------------------------------*/
void AddClient(Client client[], int i){    
    Bool e = ON; int k;
    fflush(stdin);

    printf("    - First name     : ");
    input(client[i].first_name, DEF);

    printf("    - Name           : "); 
    input(client[i].name, DEF);

    strcpy(client[i].full_name, fusename(client[i].first_name, client[i].name));

    for(k = 0; k <= i; k++){
        if(strcmp(client[k].full_name, client[i].full_name) == 0){
            printf("> This client already exist.\n\n");
            e = OFF;
            break;
        } 
    }

    if(e == ON){
        do{
            printf("    - Age            : "); 
            scanf("%d", &client[i].age);
        }while(client[i].age <= 0 || client[i].age > 99);
        fflush(stdin);

        do{  
            printf("    - Gender (M or F): ");
            scanf(" %c", &client[i].gender);
            client[i].gender = toupper(client[i].gender);
        }while(client[i].gender != 'M' && client[i].gender != 'F');
        fflush(stdin);  

        printf("    - Phone number   : "); 
        VerifyPhoneNum(client[i].phone_number);

        printf("    - ID Card        : ");
        VerifyNationalID(client[i].national_id_card);

        printf("    - City           : "); 
        input(client[i].city, DEF);

        printf("    - Adress         : ");
        input(client[i].adress, DEF); 

        printf("\n> Client number %d successfully added!\n\n", i + 1);        
    }
}



void DisplayClient(Client client[], int i){
    printf("> Client found (POS: %d)\n\n", i + 1);
    printf("    - Full name    : %s\n", client[i].full_name);  
    printf("    - Age          : %d\n", client[i].age);
    printf("    - Gender       : %c\n", client[i].gender);
    printf("    - Phone number : %s\n", client[i].phone_number);  
    printf("    - National ID  : %s\n", client[i].national_id_card);
    printf("    - City         : %s\n", client[i].city);
    printf("    - Adress       : %s\n", client[i].adress);  
    printf("\n                        \n");
}



void DeleteClient(Client client[], int i, int j){
    int k;
    for(k = j; k < i; k++){
        client[k] = client[++k];
    }
}



void SameCityClients(Client client[], int i){
    Bool e = OFF; int k;
    char city[DEF];

    fflush(stdin);
    printf("> Select a city: ");
    input(city, DEF);

    for(k = 0; k < i; k++){
        if(strcmp(client[k].city, city) == 0){
            e = ON;
        }
    }

    if(e == OFF){
        printf("> Either the city does not exist or no customers live there.\n\n");
    } else {
        printf("> List of clients living in %s\n\n", city);        
        for(k = 0; k < i; k++){
            if(strcmp(client[k].city, city) == 0){
                printf("    -> Full name: %s\n", client[k].full_name);
                printf("    -> TEL: %s\n\n", client[k].phone_number);
            }
        }
    }
}
/*----------------------------------------------------------------------------*/




/*-------------------------------SEEK FUNCTIONS-------------------------------*/
Bool HavePhoneNum(Client client[], int i, int *j){
    Bool e = OFF; int k;
    char phone_number[DEF];
    
    fflush(stdin);
    printf("> Give the phone number of the client: ");
    VerifyPhoneNum(phone_number);

    for(k = 0; k <= i; k++){
        if(strcmp(client[k].phone_number, phone_number) == 0){
            e = ON; *j = k; break;
        }
    }   
    return e;
}


Bool HaveNationalID(Client client[], int i, int *j){
    Bool e = OFF; int k;
    char national_id[DEF];

    fflush(stdin);
    printf("> Give the national ID of the client: ");
    VerifyNationalID(national_id);

    for(k = 0; k <= i; k++){
        if(strcmp(client[k].national_id_card, national_id) == 0){
            e = ON; *j = k; break;
        }
    }
    return e;
}


Bool HaveName(Client client[], int i, int *j){
    Bool e = OFF; int k;
    char full_name[DEF];

    fflush(stdin);
    printf("> Give the full name of the client: ");
    input(full_name, DEF);

    for(k = 0; k <= i; k++){
        if(strcmp(client[k].full_name, full_name) == 0){
            e = ON; *j = k; break;
        }
    }
    return e;
}
/*----------------------------------------------------------------------------*/




/*------------------------------VERIFY FUNCTIONS------------------------------*/
void VerifyPhoneNum(char string[]){
    Bool e = OFF;

    do {
        fflush(stdin);        
        int j, digit_length, digit = 0;
        input(string, DEF);
        digit_length = strlen(string);
        for(j = 0; j < digit_length; j++){
            if((string[j] >= '0' && string[j] <= '9') && (string[0] == '0')){
                digit++;
            }
        }  

        if(digit == 10){
            e = ON;          
        } else {
            printf("    - Must be 10 digits starting with '0'\n");
            printf("    - Try again: ");
        }    

    } while(e == OFF); 
}

void VerifyNationalID(char string[]){
    Bool e = OFF;

    do {
        fflush(stdin);        
        int j, sequence_length, sequence = 2;
        input(string, DEF);
        sequence_length = strlen(string);
        for(j = 2; j < sequence_length; j++){
            if(/**/(string[j]>='0' && string[j]<='9') && 
            ((string[0]>='A' && string[0]<='Z') || (string[1]>='A' && string[1]<='Z'))/**/){
                sequence++;
            }
        }  

        if(sequence == 8){
            e = ON;          
        } else {
            printf("    - Must be 8 sequences starting with 2 capital letters.\n");
            printf("    - Try again: ");
        }    

    } while(e == OFF);
}
/*----------------------------------------------------------------------------*/




/*------------------------------------UTIL------------------------------------*/
void input(char string[], int n){
    int ch_ascii, i = 0;

    while((ch_ascii = getchar()) != '\n'){
        if(i < n)
            string[i++] = ch_ascii;
    }
    string[i] = '\0';
}

float BillCost(int m, int s){
    int k, t;
    float cost = 0;

    printf("Minutes: "); scanf("%d", &m);
    printf("Seconds: "); scanf("%d", &s);
    printf("Call duration: %d:%d\n", m, s);

    t = (m *60) + s;

    for(k = 0; k <= t; k += 20){
        if(k <= 180){
            cost += 1.4;
        } else {
            cost += 1.2;
        }
    }

    printf("> Total cost: %.2f DH\n\n", cost);
}

char* fusename(char first_name[], char name[]){
    char tmp_first_name[DEF];
    char tmp_name[DEF];
    char full_name[DEF];

    strcpy(tmp_first_name, first_name);
    strcpy(tmp_name, name);

    return strcpy(full_name, strcat(strcat(tmp_first_name, " "), tmp_name));
}
/*----------------------------------------------------------------------------*/
//================================================================================================//
