#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"

//Function to accept user input
int enterchoice()
{
    int choice,i;
    textcolor(LIGHTCYAN);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    textcolor(CYAN);
    for(i=1;i<=80;i++)
    {
        printf("-");
    }
    textcolor(YELLOW);
    printf("\nSelect an option\n");
    printf("\n1 -> View Trains");
    printf("\n2 -> Book Ticket");
    printf("\n3 -> View Ticket");
    printf("\n4 -> View Passenger Tickets");
    printf("\n5 -> View All Bookings");
    printf("\n6 -> View Train Bookings");
    printf("\n7 -> Cancel Ticket");
    printf("\n8 -> Cancel Train");
    printf("\n9 -> Quit");
    textcolor(LIGHTMAGENTA);
    printf("\n\nEnter choice: ");
    scanf("%d",&choice);
    return choice;
}

//Function to add trains in our file
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("f:\\myproject\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("f:\\myproject\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File created and saved!\n");

    }
    else
        printf("File present already.\n");
    fclose(fp);
}

//Function to view all train details
void view_trains()
{
    int i;
    textcolor(CYAN);
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
     for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("f:\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        textcolor(LIGHTCYAN);
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}

//Function to check train number
int check_train_no(char *trainno)
{
    FILE *fp=fopen("f:\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }
    }
    fclose(fp);
    return 0;
}

//Function to check mobile number
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}

//Function to accept passenger details to book ticket
Passenger * get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger name:");
    static Passenger psn;
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
        //fgets() adds "\n" at the end of file,
        //Removing "\n" from the end of name.
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    //checking for name entered as 0.
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    //taking gender input.
    int valid;  //taking valid=1 for verifying input.
    gotoxy(1,2);
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.gender!='M' && psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \b"); /* use space and \b ,space will erase wrong gender and \b will again send the cursur at 1 position back,
                        but if user has written long word then use multiple times \t and again reset cursur position.*/
            textcolor(YELLOW);
            gotoxy(19,2);
        }
    }
    while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    //entering train no as input.
    gotoxy(1,3);    //reset the cursor at the 1st col 3rd row.
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)    //if train no is correct, returns 0, otherwise 1.
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Train No");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }
    while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");   //for clearing previous message.
    gotoxy(1,4);
    printf("Enter traveling class(First AC-F,Second AC-S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')    //checking for invalid input (or zero).
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Traveling class should be F or S (in uppercase)");
            valid=0;
            getch();
            gotoxy(47,4);
            printf(" \b");
            textcolor(YELLOW);
            gotoxy(47,4);
        }
    }
    while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");   //for clearing previous message.
    gotoxy(1,5);
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,30,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';  //replacing '\n' with '\0' at the end of file to make address input.
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(1,25);
        printf("RESERVATION CANCELLED !");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    gotoxy(1,6);
    printf("Enter age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)  //checking for age for 0.
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.age<=0 || psn.age>=126)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(11,6);
            textcolor(YELLOW);
        }
    }
    while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");   //for clearing previous message.
    gotoxy(1,7);
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("RESERVATION CANCELLED !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
    valid=check_mob_no(psn.mob_no);
    if(valid==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Error! Invalid mobile no");
        getch();
        gotoxy(21,7);
        printf("\t\t\t\t\t\t\t");   //for clearing previous message.
        gotoxy(21,7);
        textcolor(YELLOW);
    }
    }while(valid==0);
    return & psn;
}

//Function to get the count of booked tickets
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}

//Function to get the ticket number of last ticket
int last_ticket_no()
{
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return 0;
    }
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

//Function to book a passenger's ticket
int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats in train no %s in class %c is full",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}

//Function to accept ticket number from the user
int accept_ticket_no()
{
    textcolor(YELLOW);
    printf("Enter a valid ticket no:");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("Cancelling input...!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Ticket no. should be positive..");
            getch();
            valid=0;
            gotoxy(25,1);
            printf("\t");   //for clearing previous message.
            gotoxy(25,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}

//Function to view a booked ticket
void view_ticket(int ticket_no)
{
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo booking done yet");
        return;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            textcolor(LIGHTGRAY);
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            printf("\n\n");
            found=1;
            break;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no %d found!",ticket_no);
    }
    fclose(fp);
}

//Function to accept mobile number from the user
char* accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid;
    textcolor(YELLOW);
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,11,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("Cancelling input... !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(mob_no);
    if(valid==0)
       {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("Error! Invalid mobile no");
          getch();
          gotoxy(27,1);
          printf("\t\t\t\t\t\t\t");   //for clearing previous message.
          gotoxy(27,1);
          textcolor(YELLOW);
      }
    }while(valid==0);  //Incomplete
    clrscr();
    return mob_no;
}

//Function to get ticket number from mobile number
int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

//Function to view all tickets of a passenger
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    textcolor(LIGHTGRAY);
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("---------------------------");
    textcolor(LIGHTCYAN);
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
}

//Function to accept train number from the user
char* accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");   //for clearing previous message.
            gotoxy(1,25);
            printf("Cancelling input... !");
            getch();
            textcolor(YELLOW);
            clrscr();
            return 0;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("Error! Invalid Train number");
          getch();
          gotoxy(20,1);
          printf("\t\t\t\t\t");   //for clearing previous message.
          gotoxy(20,1);
          textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

//Function to view all bookings of a particular train
void view_bookings(char* train_no)
{
    int found=0,i;
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No Bookings done yet");
        return;
    }
    textcolor(CYAN);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\t  AGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
        printf("-");
    Passenger p;
    int row=3;
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.train_no,train_no)==0)
        {
            found=1;
            printf("%d\t\t%c\t%s",p.ticketno,p.p_class,p.p_name);
            gotoxy(42,row);
            printf("%c\t  %d\t%s\n",p.gender,p.age,p.mob_no);
            row++;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of the bookings in train no %s found!",train_no);
    }
    fclose(fp);
}

//Function to view all bookings
void view_all_bookings()
{
    Passenger p;
    int found=0,i;
    FILE *fp=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return;
    }
    gotoxy(22,1);
    textcolor(GREEN);
    printf("ALL BOOKINGS ARE GIVEN BELOW!");
    gotoxy(22,2);
    for(i=1;i<=29;i++)
        printf("-");
    gotoxy(1,4);
    textcolor(LIGHTMAGENTA);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=78;i++)
        printf("-");
    printf("\n");
    int row=6;
    textcolor(LIGHTCYAN);
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        found= 1;
        printf("%d\t\t%c\t%s",p.ticketno,p.p_class,p.p_name);
        gotoxy(42,row);
        printf("%c\t%d\t%s\n",p.gender,p.age,p.mob_no);
        row++;
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
    }
    fclose(fp);
}

//Function to cancel a ticket
int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("f:\\myproject\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo booking done yet!");
        return -1;
    }
    FILE *fp2=fopen("f:\\myproject\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("f:\\myproject\\temp.dat");
    }
    else
    {
        result=remove("f:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("f:\\myproject\\temp.dat","f:\\myproject\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

//Function to cancel a train
int cancel_train(char *train_no)
{
    int found=0,result;
    Train tr;
    FILE *fp1=fopen("f:\\myproject\\alltrains.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo trains available!");
        return 0;
    }
    FILE *fp2=fopen("f:\\myproject\\temp.dat","wb");
    while(fread(&tr,sizeof(tr),1,fp1)==1)
    {
        if(strcmp(tr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&tr,sizeof(tr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("f:\\myproject\\temp.dat");
    }
    else
    {
        result=remove("f:\\myproject\\alltrains.dat");
        if(result!=0)
            return 2;

        result=rename("f:\\myproject\\temp.dat","f:\\myproject\\alltrains.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
