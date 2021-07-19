#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"

int main()
{
    int choice;
    Passenger*ptr;
    char*p_mob_no;
    int* p_ticket_no;
    int ticket_no,result;
    char* train_no;
    add_trains();
    while(1){

        choice = enterchoice();
        if(choice == 9)
            exit(0);
        switch(choice){
               case 1:
                   view_trains();
                   getch();
                   clrscr();
                   break;
               case 2:
                    ptr = get_passenger_details();
                    clrscr();
                    if(ptr != NULL){
                       ticket_no = book_ticket(*ptr);
                       if(ticket_no==-1){
                        textcolor(LIGHTRED);
                        printf("Booking failed");
                       }
                       else{
                        textcolor(LIGHTGREEN);
                        printf("Booking successful, ticket no. : %d",ticket_no);
                       }
                       textcolor(WHITE);
                       printf("\n\npress any to go back.....");
                       getch();
                       clrscr();
                    }
                    break;
               case 3:
                    clrscr();
                    ticket_no = accept_ticket_no();
                    if(ticket_no!=0)
                        view_ticket(ticket_no);
                    textcolor(WHITE);
                    printf("Press any key to exit");
                    getch();
                    clrscr();
                    break;
               case 4:
                    clrscr();
                    p_mob_no=accept_mob_no();
                    if(p_mob_no!=NULL){
                        p_ticket_no=get_ticket_no(p_mob_no);
                        view_all_tickets(p_mob_no,p_ticket_no);
                    }
                    clrscr();
                    break;
               case 5:
                    clrscr();
                    view_all_bookings();
                    getch();
                    clrscr();
                    break;
               case 6:
                    clrscr();
                    train_no = accept_train_no();
                    if(train_no!=NULL){
                        view_bookings(train_no);
                    }
                    clrscr();
                    break;
               case 7:
                    clrscr();
                    ticket_no=accept_ticket_no();
                    if(ticket_no!=0){
                        result = cancel_ticket(ticket_no);
                        if(result==0){
                            textcolor(LIGHTRED);
                            printf("ERROR!, no results against train no. : %s",train_no);
                        }
                        if(result==1){
                            textcolor(LIGHTGREEN);
                            printf("SUCCESS!, train cancelled successfully");
                        }
                        if(result==2){
                            textcolor(LIGHTRED);
                            printf("ERROR!, train cancellation can't be completed, please try again!");
                        }
                        textcolor(WHITE);
                        printf("\nPress any key to exit...");
                    }
                    getch();
                    clrscr();
                    break;
               case 8:
                    clrscr();
                    train_no=accept_train_no();
                    if(train_no!=0){
                        result = cancel_train(train_no);
                        if(result==0){
                            textcolor(LIGHTRED);
                            printf("ERROR!, no results against ticket no. : %d",ticket_no);
                        }
                        if(result==1){
                            textcolor(LIGHTGREEN);
                            printf("SUCCESS!, your ticket cancelled successfully");
                        }
                        if(result==2){
                            textcolor(LIGHTRED);
                            printf("ERROR!, ticket cancellation can't be completed, please try again!");
                        }
                        textcolor(WHITE);
                        printf("\nPress any key to exit...");
                    }
                    getch();
                    clrscr();
                    break;
               default:
                    textcolor(LIGHTRED);
                    printf("Wrong choice!, Try again");
                    getch();
                    clrscr();

        }
    }

    return 0;
}
