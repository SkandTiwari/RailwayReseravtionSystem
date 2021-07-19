#include "conio2.h"
#include "rlyres.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* enter choice main screen*/

int enterchoice(){
    int choice;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");

    for(int i=0; i<80; i++)
        printf("-");

    printf("\n\nSelect an option");
    printf("\n1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket No\n5- View All Bookings\n6- View Train Bookings\n");
    printf("7- Cancel Ticket\n8- Cancel Train\n9- Quit");
    printf("\n\nEnter choice : ");

    scanf("%d",&choice);

    return choice;
}

// For adding trains in the list

void add_trains(){
    Train alltrains[4] = {
        {"123","BPL","GWL",2100,1500},
        {"546","BPL","DEL",3500,2240},
        {"345","HBJ","AGR",1560,1135},
        {"126","HBJ","MUM",4500,3360},


    };
    FILE *fptr = fopen("D:\\RailwayReservationSystem\\alltrains.dat","rb");
    if(fptr == NULL){
        fptr = fopen("D:\\RailwayReservationSystem\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fptr);
        printf("File created and saved");
    }
    else
        printf("File already exists");
    fclose(fptr);
}

// for viewing trains

void view_trains(){
    clrscr();
    FILE * fptr;
    Train info;
    int i = 0;
    printf("\n\nTRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOND AC FAIR\n");

    for(int i=0; i<80; i++)
        printf("-");

    fptr = fopen("D:\\RailwayReservationSystem\\alltrains.dat","rb");
    while(fread(&info, sizeof(info), 1, fptr) == 1){
        printf("\n%s\t\t%s\t%s\t%d\t\t%d\n", info.train_no, info.from, info.to, info.fac_fare, info.sac_fare);
    }
    printf("\n\n\n\n");
    textcolor(RED);
    gotoxy(1,25);
    printf("Press any key to exit");
    fclose(fptr);
}

// checks the availability of input train no.

int check_train_no(char* ptr){
    FILE*fptr = fopen("D:\\RailwayReservationSystem\\alltrains.dat","rb");
    Train info;
    while(fread(&info, sizeof(info), 1, fptr) == 1){
        if(strcmp(ptr,info.train_no) == 0){
            fclose(fptr);
            return 1;
        }
    }
    fclose(fptr);
    return 0;
}
int check_mob_no(char*p_mob){
    if(strlen(p_mob) != 10){
        return 0;
    }
    while(*p_mob!='\0'){
            if(isdigit(*p_mob)==0)
                return 0;
            p_mob++;
    }
    return 1;
}

Passenger*get_passenger_details(){
    clrscr();
    gotoxy(40,1);
    textcolor(LIGHTGREEN);
    printf("press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("Enter passenger name : ");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *cptr;
    cptr = strchr(psn.p_name,'\n');
    *cptr = '\0';
    if(strcmp(psn.p_name,"0")==0){
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("RESERVATION CANCELLED!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }

    int valid;
    printf("Enter gender M/F : ");
    do{
        valid = 1;
        fflush(stdin);
        scanf("%c", &psn.gender);
        if(psn.gender == '0'){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.gender!='M'&&psn.gender!='F'){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Gender should be either M or F(in uppercase letters)");
            valid = 0;
            getch();
            gotoxy(21,2);
            printf("\b");
            textcolor(YELLOW);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t\t");
    gotoxy(1,3);
    printf("Enter train number : ");
    do{
        fflush(stdin);
        scanf("%s",&psn.train_no);
        if(strcmp(psn.train_no,"0") == 0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid = check_train_no(psn.train_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("NOT FOUND!, Re-enter correct train no.");
            getch();
            gotoxy(21,3);
            printf("\t\t\t\t\t\t");
            gotoxy(21,3);
            textcolor(YELLOW);
        }
        }while(valid == 0);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t\t");
        gotoxy(1,4);
        printf("Enter Traveling class, First AC (F), Second AC (S) : ");
        do{
        valid = 1;
        fflush(stdin);
        scanf("%c", &psn.p_class);
        if(psn.p_class == '0'){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.p_class!='F'&&psn.p_class!='S'){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Travelling should be either S or F (in uppercase letters)");
            valid = 0;
            getch();
            gotoxy(54,4);
            printf("\b");
            textcolor(YELLOW);
        }
    }while(valid == 0);
     gotoxy(1,25);
     printf("\t\t\t\t\t\t\t\t\t");
     gotoxy(1,5);
     printf("Enter address : ");
     fflush(stdin);
     fgets(psn.address,20,stdin);
     char *aptr;
     cptr = strchr(psn.address,'\n');
     *aptr = '\0';
     if(strcmp(psn.address,"0")==0){
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");
        printf("RESERVATION CANCELLED!");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
     }
     printf("Enter your age : ");
     do{
        valid = 1;
        fflush(stdin);
        scanf("%d", &psn.age);
        if(psn.age == 0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age < -1){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, age should be positive");
            valid = 0;
            getch();
            gotoxy(18,6);
            printf("\t\t\t\t\t\t");
            gotoxy(18,6);
            textcolor(YELLOW);
        }
    }while(valid == 0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,7);
    printf("Enter Mobile no : ");
    do{
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        aptr = strchr(psn.mob_no, '\n');
        *aptr = '\0';
        if(strcmp(psn.mob_no,"0")==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("RESERVATION CANCELLED!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_mob_no(&psn.mob_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Invalid mobile no.");
            getch();
            gotoxy(18,7);
            printf("\t\t\t\t\t\t");
            gotoxy(18,7);
            textcolor(YELLOW);
        }
    }while(valid == 0);
    return &psn;
}
int get_booked_ticket_count(char*train_no,char tc){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        return 0;
    }
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fptr)==1){
            if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc){
                count++;
            }
            fclose(fptr);
            return count;
        }

    }
int last_ticket_no(){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        return 0;
    }
    Passenger pr;
    fseek(fptr,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fptr);
    fclose(fptr);
    return pr.ticketno;
}

int book_ticket(Passenger psn){
    int ticket_count = get_booked_ticket_count(psn.train_no, psn.p_class);
    if(ticket_count == 2){
        textcolor(LIGHTRED);
        printf("All seats are full in train no. : %d",psn.train_no);
        return -1;
    }
    int ticket_no = last_ticket_no()+1;
    psn.ticketno = ticket_no;
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","ab");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("Sorry!, file can't be opened");
        return -1;
    }
    fwrite(&psn,sizeof(psn),1,fptr);
    fclose(fptr);
    return ticket_no;
}

int accept_ticket_no(){
    printf("Enter a valid ticket number : ");
    int valid;
    int ticket_no;
    do{
        valid = 1;
        scanf("%d",&ticket_no);
        if(ticket_no==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(ticket_no<0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, ticket no. should be positive");
            valid = 0;
            getch();
            gotoxy(31,1);
            printf("\t\t\t\t\t\t");
            gotoxy(31,2);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}

void view_ticket(int ticket_no){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTGREEN);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    int found = 0;
    while(fread(&psn,sizeof(psn),1,fptr) == 1){
        if(psn.ticketno==ticket_no){
            printf("\nNAME : %s\nGENDER : %c\nTRAIN NO. : %s\nCLASS : %c\nADDRESS : %s\nAGE : %d\nMOBILE NO : %s\nTICKET NO. : %d\n\n",psn.p_name,psn.gender,psn.train_no,psn.p_class,psn.address,psn.age,psn.mob_no,psn.ticketno);
            found = 1;
            break;
        }
    }
    if(found==0){
        textcolor(LIGHTRED);
        printf("NOT FOUND!, no result found for ticket no : %d\n",ticket_no);
    }
    fclose(fptr);

}

char*accept_mob_no(){
    static char mob_no[12];
    int valid;
    char*pos;
    printf("Enter your mobile no. : ");
    do{
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos = strchr(mob_no,'\n');
        if(pos!=NULL){
            *pos = '\0';
        }
        if(strcmp(mob_no,"0")==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_mob_no(mob_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Invalid mobile no.");
            getch();
            gotoxy(25,1);
            printf("\t\t\t\t\t\t");
            gotoxy(25,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int*get_ticket_no(char*mob_no){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return NULL;
    }
    Passenger psn;
    int count = 0;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(psn.mob_no,mob_no)==0){
            count++;
        }
    }
    if(!count){
        fclose(fptr);
        return NULL;
    }
    int*p=(int*)malloc((count+1)*sizeof(int));
    rewind(fptr);
    int i=0;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(psn.mob_no,mob_no)==0){
            *(p+i) = psn.ticketno;
            i++;
        }
    }
    *(p+1)=-1;
    fclose(fptr);
    return p;
}

void view_all_tickets(char*mob_no,int*tno){
    if(tno == NULL){
        textcolor(LIGHTRED);
        printf("No tickets found for Mobile no. : %s\n",mob_no);
        textcolor(WHITE);
        printf("Press any key to go back");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following tickets are booked for Mobile no. : %s\n",mob_no);
    int i = 0;
    printf("\n\nTICKET NUMBERS\n\n");
    for(int j=0;j<80;j++)
        printf("-");
    while(*(tno+i)!=-1){
        printf("%d\n",*(tno+i));
        i++;
    }
    textcolor(WHITE);
    printf("\nPress any key to exit...");
    textcolor(YELLOW);
    getch();
    free(tno);
}

char*accept_train_no(){
    static char train_no[5];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train no : ");
    do{
        fflush(stdin);
        scanf("%s",&train_no);
        if(strcmp(train_no,"0")==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_train_no(train_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Invalid Train Number");
            getch();
            gotoxy(18,1);
            printf("\t\t\t\t\t\t");
            gotoxy(18,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char*train_no){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    int found=0;
    printf("TICKET NO.\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO.\n");
    for(int i=0;i<80;i++)
        printf("-");
    int row = 3;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(train_no,psn.train_no)==0){
            printf("%d\t\t%c\t%s",psn.ticketno,psn.p_class,psn.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",psn.gender,psn.age,psn.mob_no);
            row++;
            found = 1;
        }
    }
    if(!found){
        textcolor(LIGHTRED);
        printf("No bookings found for train no. : %s",train_no);
    }
    textcolor(WHITE);
    printf("\nPress any key to exit.....");
    getch();
    fclose(fptr);
}

int cancel_ticket(int ticket_no){
    int result;
    FILE*fptr1 = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr1 == NULL){
        textcolor(LIGHTRED);
        printf("File not found!");
        return -1;
    }
    FILE*fptr2 = fopen("D:\\RailwayReservationSystem\\temp.dat","wb");
    Passenger psn;
    int found=0;
    while(fread(&psn,sizeof(psn),1,fptr1)==1){
        if(psn.ticketno==ticket_no){
            found = 1;
        }
        else{
            fwrite(&psn,sizeof(psn),1,fptr2);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    if(found==0){
        remove("D:\\RailwayReservationSystem\\temp.dat");
    }
    else{
        result = remove("D:\\RailwayReservationSystem\\allbookings.dat");
        if(result!=0)
            return 2;
        result = rename("D:\\RailwayReservationSystem\\temp.dat", "D:\\RailwayReservationSystem\\allbookings.dat");
        if(result!=0){
        return 2;
        }
    }
    return found;
}

int cancel_train(char*train_no){
    int result;
    FILE*fptr1 = fopen("D:\\RailwayReservationSystem\\alltrains.dat","rb");
    if(fptr1 == NULL){
        textcolor(LIGHTRED);
        printf("File not found!");
        return -1;
    }
    FILE*fptr2 = fopen("D:\\RailwayReservationSystem\\temptrain.dat","wb");
    Train trn;
    int found=0;
    while(fread(&trn,sizeof(trn),1,fptr1)==1){
        if(strcmp(trn.train_no,train_no)==0){
            found = 1;
        }
        else{
            fwrite(&trn,sizeof(trn),1,fptr2);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    if(found==0){
        remove("D:\\RailwayReservationSystem\\temptrain.dat");
    }
    else{
        result = remove("D:\\RailwayReservationSystem\\alltrains.dat");
        if(result!=0)
            return 2;
        result = rename("D:\\RailwayReservationSystem\\temptrain.dat", "D:\\RailwayReservationSystem\\alltrains.dat");
        if(result!=0){
        return 2;
        }
    }
    return found;
}
void view_all_bookings(){
    FILE*fptr;
    fptr = fopen("D:\\RailwayReservationSystem\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    printf("TICKET NO.\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO.\n");
    for(int i=0;i<80;i++)
        printf("-");
    int row = 3;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
            printf("%d\t\t%c\t%s",psn.ticketno,psn.p_class,psn.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",psn.gender,psn.age,psn.mob_no);
            row++;
    }
    gotoxy(1,25);
    textcolor(WHITE);
    printf("Press any key to Exit");
}





