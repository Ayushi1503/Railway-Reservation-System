#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"

int main()
{
    int choice,result=0,ticket_no;
    char * pmob_no;
    char * train_no;
    int * pticket_no;
    Passenger * P;
    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
        switch(choice)
        {
            case 1:
                    clrscr();
                    view_trains();
                    textcolor(WHITE);
                    printf("\n\nPress any key to go back to main screen");
                    getch();
                    clrscr();
                    break;
            case 2:
                    clrscr();
                    P = get_passenger_details();
                    clrscr();
                    if(P!=NULL)
                    {
                        ticket_no=book_ticket(*P);
                    }
                    if(ticket_no==-1)
                    {
                        textcolor(LIGHTRED);
                        printf("Booking Failed");
                    }
                    else if(ticket_no>0)
                    {
                        textcolor(LIGHTGREEN);
                        printf("Ticket Booked successfully.\nYour ticket number is %d.",ticket_no);
                    }
                    textcolor(WHITE);
                    gotoxy(1,25);
                    printf("Press any key to go back to main screen.");
                    getch();
                    clrscr();
                    break;
            case 3:
                    clrscr();
                    ticket_no = accept_ticket_no();
                    if(ticket_no!=0)
                    {
                        view_ticket(ticket_no);
                    }
                    textcolor(WHITE);
                    printf("\n\n\nPress any key to go back to main screen.");
                    getch();
                    clrscr();
                    break;
            case 4:
                    clrscr();
                    pmob_no=accept_mob_no();
                    if(pmob_no!=NULL)
                    {
                        pticket_no=get_ticket_no(pmob_no);
                        view_all_tickets(pmob_no,pticket_no);
                    }
                    textcolor(WHITE);
                    gotoxy(1,25);
                    printf("Press any key to go back to main screen.");
                    getch();
                    clrscr();
                    break;
            case 5:
                    clrscr();
                    view_all_bookings();
                    textcolor(WHITE);
                    printf("\n\n\nPress any key to go back to main screen.");
                    getch();
                    clrscr();
                    break;
            case 6:
                    clrscr();
                    train_no=accept_train_no();
                    if(train_no!=NULL)
                    {
                        view_bookings(train_no);
                    }
                    textcolor(WHITE);
                    printf("\n\n\nPress any key to go back to main screen.");
                    getch();
                    clrscr();
                    break;
            case 7:
                    clrscr();
                    ticket_no=accept_ticket_no();
                    if(ticket_no!=0)
                    {
                        result=cancel_ticket(ticket_no);
                        if(result==0)
                        {
                            textcolor(LIGHTRED);
                            printf("Sorry! No tickets booked against ticket number %d",ticket_no);
                        }
                        else if(result==1)
                        {
                            textcolor(LIGHTGREEN);
                            printf("Ticket number %d successfully canceled",ticket_no);
                        }
                        else if(result==2)
                        {
                            textcolor(LIGHTRED);
                            printf("Sorry! Error in cancellation. Try again!");
                        }
                    }
                    textcolor(WHITE);
                    gotoxy(1,25);
                    printf("Press any key to go back to main screen");
                    getch();
                    clrscr();
                    break;
            case 8:
                    clrscr();
                    train_no=accept_train_no();
                    if(train_no!=0)
                    {
                        result=cancel_train(train_no);
                        if(result==0)
                        {
                            textcolor(LIGHTRED);
                            printf("Sorry! No train available with train no %s",train_no);
                        }
                        else if(result==1)
                        {
                            textcolor(LIGHTCYAN);
                            printf("\nTrain no %s successfully canceled!",train_no);
                        }
                        else if(result==2)
                        {
                            textcolor(LIGHTRED);
                            printf("Sorry! Error in cancellation. Try again!");
                        }
                    }
                    textcolor(WHITE);
                    gotoxy(1,25);
                    printf("\nPress any key to go back to the main screen!");
                    getch();
                    clrscr();
                    break;
            default:
                    textcolor(LIGHTRED);
                    printf("Wrong Choice! Try Again\n");
                    getch();
                    clrscr();
        }
    }
    return 0;
}
