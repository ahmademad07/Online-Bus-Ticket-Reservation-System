#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void selectBusType();
void selectroute();
void initializeSeats(int currentBusType);
void showSeats(int currentBusType);
void bookTicket(int currentBusType);
void cancelTicket(int currentBusType);
void printTicket(int currentBusType);
double calculateRefund(double price, double hoursBefore);

int non_ac_price=800;
int ac_price=1600;
int sleeper_price=2000;
int currentBusType = -1;
char from_location[50];
char to_location[50];
char non_ac_seats[1][32][4];
char ac_seats[1][24][4];
char sleeper_seats[1][12][4];
int  non_ac_booked[1][32];
int  ac_booked[1][24];
int  sleeper_booked[1][12];

struct Node
{
    char seat[4];
    char name[50];
    char phone[15];
    time_t issue_time;
    time_t journey_time; 

    struct Node *left;
    struct Node *right;
};

struct Node *non_ac_root = NULL;
struct Node *ac_root = NULL;
struct Node *Sleeper_root = NULL;
struct Node* insert(struct Node* root, char seat[], char name[], char phone[], time_t issue_time,time_t journey_time)
{
    if(root == NULL)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        strcpy(newNode->seat, seat);
        strcpy(newNode->name, name);
        strcpy(newNode->phone, phone);
        newNode->issue_time=issue_time;
        newNode->journey_time=journey_time;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if(strcmp(seat, root->seat) < 0)
        root->left = insert(root->left, seat, name, phone, issue_time,journey_time);
    else
        root->right = insert(root->right, seat, name, phone,issue_time,journey_time);

    return root;
}
struct Node* search(struct Node* root, char seat[])
{
    if(root == NULL || strcmp(root->seat, seat) == 0)
        return root;

    if(strcmp(seat, root->seat) < 0)
        return search(root->left, seat);
    else
        return search(root->right, seat);
}


int main()
{
    int menu;

    while(1)
    {
        printf("\n1.Select Bus Type\n");
        printf("2.Select Route\n");
        printf("3.Show Seats\n");
        printf("4.Book Ticket\n");
        printf("5.Cancel Ticket\n");
        printf("6.Print Ticket\n");
        printf("7.Exit\n");

        scanf("%d",&menu);

        switch(menu)
        {
            case 1:
                selectBusType();
                break;

            case 2:
                selectroute();
                break;

            case 3:
                if(currentBusType == -1)
                    printf("Please select bus type first!\n");
                else
                    showSeats(currentBusType);
                break;

            case 4:
                if(currentBusType == -1)
                    printf("Please select bus type first!\n");
                else
                    bookTicket(currentBusType);
                break;

            case 5:
                if(currentBusType == -1)
                    printf("Please select bus type first!\n");
                else
                    cancelTicket(currentBusType);
                break;

            case 6:
                if(currentBusType == -1)
                    printf("Please select bus type first!\n");
                else
                    printTicket(currentBusType);
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid Option\n");
        }
    }
}

void selectBusType()
{
    printf("Select Bus Type:\n");
    printf("1. Non-AC\n");
    printf("2. AC\n");
    printf("3. Sleeper\n");

    scanf("%d", &currentBusType);

    currentBusType--;

    if(currentBusType < 0 || currentBusType > 2)
    {
        printf("Invalid Bus Type!\n");
        currentBusType = -1;
    }
    else
    {
        initializeSeats(currentBusType);
        if(currentBusType == 0)
            printf("Non-AC Bus Selected\n");
        else if(currentBusType == 1)
            printf("AC Bus Selected\n");
        else
            printf("Sleeper Bus Selected\n");
    }
}
#define DIV 8

const char *divisions[DIV] = {
    "Dhaka", "Chattogram", "Rajshahi", "Khulna",
    "Barishal", "Sylhet", "Rangpur", "Mymensingh"
};

// Districts under each division
const char *districts[DIV][20] = {
    // Dhaka (13)
    {"Dhaka","Gazipur","Narsingdi","Manikganj","Munshiganj","Narayanganj","Tangail","Kishoreganj","Madaripur","Shariatpur","Faridpur","Gopalganj","Rajbari"},
    
    // Chattogram (11)
    {"Chattogram","Cox's Bazar","Comilla","Feni","Brahmanbaria","Rangamati","Khagrachari","Bandarban","Noakhali","Lakshmipur","Chandpur"},
    
    // Rajshahi (8)
    {"Rajshahi","Bogura","Pabna","Natore","Naogaon","Chapainawabganj","Joypurhat","Sirajganj"},
    
    // Khulna (10)
    {"Khulna","Bagerhat","Satkhira","Jessore","Narail","Magura","Jhenaidah","Kushtia","Meherpur","Chuadanga"},
    
    // Barishal (6)
    {"Barishal","Bhola","Patuakhali","Pirojpur","Barguna","Jhalokati"},
    
    // Sylhet (4)
    {"Sylhet","Moulvibazar","Habiganj","Sunamganj"},
    
    // Rangpur (8)
    {"Rangpur","Dinajpur","Kurigram","Gaibandha","Nilphamari","Lalmonirhat","Thakurgaon","Panchagarh"},
    
    // Mymensingh (4)
    {"Mymensingh","Netrokona","Jamalpur","Sherpur"}
};

int district_count[DIV] = {13,11,8,10,6,4,8,4};
void selectroute()
{
    int fromDiv, toDiv;
    int fromDist, toDist;

    printf("\n==== SELECT SOURCE (FROM) ====\n");
    for(int i = 0; i < DIV; i++)
        printf("%d. %s\n", i+1, divisions[i]);

    scanf("%d", &fromDiv);
    fromDiv--;

    if(fromDiv < 0 || fromDiv >= DIV)
    {
        printf("Invalid Division!\n");
        return;
    }

    printf("\nSelect District:\n");
    for(int i = 0; i < district_count[fromDiv]; i++)
        printf("%d. %s\n", i+1, districts[fromDiv][i]);

    scanf("%d", &fromDist);
    fromDist--;

    if(fromDist < 0 || fromDist >= district_count[fromDiv])
    {
        printf("Invalid District!\n");
        return;
    }

    // TO
    printf("\n==== SELECT DESTINATION (TO) ====\n");
    for(int i = 0; i < DIV; i++)
        printf("%d. %s\n", i+1, divisions[i]);

    scanf("%d", &toDiv);
    toDiv--;

    if(toDiv < 0 || toDiv >= DIV)
    {
        printf("Invalid Division!\n");
        return;
    }

    printf("\nSelect District:\n");
    for(int i = 0; i < district_count[toDiv]; i++)
        printf("%d. %s\n", i+1, districts[toDiv][i]);

    scanf("%d", &toDist);
    toDist--;

    if(toDist < 0 || toDist >= district_count[toDiv])
    {
        printf("Invalid District!\n");
        return;
    }

    sprintf(from_location, "%s, %s", districts[fromDiv][fromDist], divisions[fromDiv]);
    sprintf(to_location, "%s, %s", districts[toDiv][toDist], divisions[toDiv]);

printf("\n====== ROUTE SELECTED ======\n");
printf("FROM: %s\n", from_location);
printf("TO  : %s\n", to_location);
printf("============================\n");
}

void initializeSeats(int currentBusType)
{
    char row;
    int num;
    int index;

        index = 0;
        row = 'A';
    if(currentBusType==0)
    {   
        index = 0;
        row = 'A';
       
        for(int i = 0; i < 8; i++)
        {
           
             for(num = 1; num <= 4; num++)
            {
                sprintf( non_ac_seats[0][index], "%c%d", row, num);
                non_ac_booked[0][index] = 0;
                index++;
            }
            row++;
        }
      
    }
    if(currentBusType==1)
    {
        index = 0;
        row = 'A';
         for(int i = 0; i < 8; i++)
        {
            for(num = 1; num <= 3; num++)
            {
                sprintf( ac_seats[0][index], "%c%d", row, num);
                ac_booked[0][index] = 0;
                index++;
            }
            row++;
        }
  
    }
    else if(currentBusType==2)
    {
        index = 0;
        row = 'A';
        for(int i = 0; i < 6; i++)
        {
            for(num = 1; num <= 2; num++)
            {
                sprintf( sleeper_seats[0][index], "%c%d", row, num);
                sleeper_booked[0][index] = 0;
                index++;
            }
            row++;
        }
       
    }


}
void showSeats(int currentBusType)
{
    printf("Seats:\n");
    if(currentBusType==0)
    {
        for(int i=0; i<32; i++)
    {
        if( non_ac_booked[0][i] == 0)
            printf("%s ", non_ac_seats[0][i]);
        else
            printf("XX ");

        if((i+1)%2 == 0)
            printf("  ");

        if((i+1)%4 == 0)
            printf("\n");
    }
    }
    if(currentBusType==1)
    {
        for(int i=0; i<24; i++)
    {
        if(ac_booked[0][i] == 0)
            printf("%s ", ac_seats[0][i]);
        else
            printf("XX ");

        if((i % 3) == 1)
            printf("  ");

        if((i % 3) == 2)
            printf("\n");
    }
    }
    if(currentBusType==2)
    {
        for(int i=0; i<12; i++)
    {
        if(sleeper_booked[0][i] == 0)
            printf("%s ", sleeper_seats[0][i]);
        else
            printf("XX ");

        if((i+1)%2 != 0)
            printf("  ");

        if((i+1)%2 == 0)
            printf("\n");
    }
    }

}

void bookTicket(int currentBusType)
{
    if(strlen(from_location) == 0 || strlen(to_location) == 0)
{
    printf("Please select route first!\n");
    return;
}

    else if(currentBusType==0)
    {
        printf("Ticket Price Is:%d\n",non_ac_price);
        char seat_no[4];
        printf("ENTER SEAT NO TO BOOK: ");
        scanf("%s", seat_no);
        for(int i=0; i<32; i++)
    {
        if(strcmp(non_ac_seats[0][i],seat_no)==0)
        {

        if(non_ac_booked[0][i]==0)
        {
           non_ac_booked[0][i]=1; 
           char name[50], phone[15];
           time_t issue_time=time(NULL);
           printf("Enter Name: ");
           scanf(" %[^\n]", name);
           printf("Enter Phone: ");
           scanf("%s", phone);
           char date[20], timeStr[10];

           printf("Enter Date (DD/MM/YYYY): ");
           scanf("%s", date);

           printf("Enter Time (HH:MM): ");
           scanf("%s", timeStr);
           printf("Seat booked successfully!\n");

           struct tm journey = {0};

           sscanf(date, "%d/%d/%d",
           &journey.tm_mday,
           &journey.tm_mon,
           &journey.tm_year);

           sscanf(timeStr, "%d:%d",
           &journey.tm_hour,
           &journey.tm_min);

           journey.tm_mon -= 1;        // months start from 0
           journey.tm_year -= 1900;    // years since 1900

           time_t journey_time = mktime(&journey);
    
           non_ac_root = insert(non_ac_root, seat_no, name, phone, issue_time,journey_time);
           break;
        }
        else
        {
            printf("SEAT IS ALREADY BOOKED");
            break;
        }
    }   
    
        
    }
    } 
    else if(currentBusType==1)
    {
        printf("Ticket Price Is:%d\n",ac_price);
        char seat_no[4];
        printf("ENTER SEAT NO TO BOOK: ");
        scanf("%s", seat_no);
        for(int i=0; i<24; i++)
    {
       if(strcmp(ac_seats[0][i],seat_no)==0)
        {
            if(ac_booked[0][i]==0)
            {
                ac_booked[0][i]=1;
                char name[50], phone[15];
                time_t issue_time=time(NULL);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Phone: ");
                scanf("%s", phone);
                char date[20], timeStr[10];

           printf("Enter Date (DD/MM/YYYY): ");
           scanf("%s", date);

           printf("Enter Time (HH:MM): ");
           scanf("%s", timeStr);
           printf("Seat booked successfully!\n");
           
           struct tm journey = {0};

           sscanf(date, "%d/%d/%d",
           &journey.tm_mday,
           &journey.tm_mon,
           &journey.tm_year);

           sscanf(timeStr, "%d:%d",
           &journey.tm_hour,
           &journey.tm_min);

           journey.tm_mon -= 1;        // months start from 0
           journey.tm_year -= 1900;    // years since 1900

           time_t journey_time = mktime(&journey);
            
           ac_root = insert(ac_root, seat_no, name, phone, issue_time,journey_time);
           break;
        }
            
            else
        {
            printf("SEAT IS ALREADY BOOKED");
            break;
        }
        }
        
        
    }
    }
    else if(currentBusType==2)
    {
        printf("Ticket Price Is:%d\n",sleeper_price);
        char seat_no[4];
        printf("ENTER SEAT NO TO BOOK: ");
        scanf("%s", seat_no);
        
    for(int i=0; i<12; i++)
    {
      if(strcmp(sleeper_seats[0][i],seat_no)==0)
        { 
            if(sleeper_booked[0][i]==0)
            {
                sleeper_booked[0][i]=1;
                char name[50], phone[15];
                time_t issue_time=time(NULL);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Phone: ");
                scanf("%s", phone); 
                 char date[20], timeStr[10];

           printf("Enter Date (DD/MM/YYYY): ");
           scanf("%s", date);

           printf("Enter Time (HH:MM): ");
           scanf("%s", timeStr);
           printf("Seat booked successfully!\n");
           
           struct tm journey = {0};

           sscanf(date, "%d/%d/%d",
           &journey.tm_mday,
           &journey.tm_mon,
           &journey.tm_year);

           sscanf(timeStr, "%d:%d",
           &journey.tm_hour,
           &journey.tm_min);

           journey.tm_mon -= 1;        // months start from 0
           journey.tm_year -= 1900;    // years since 1900

           time_t journey_time = mktime(&journey);

           Sleeper_root = insert(Sleeper_root, seat_no, name, phone,issue_time,journey_time);
           break;
            }
               
           else
        {
            printf("SEAT IS ALREADY BOOKED");
            break;
        }
        }
        
    }
    }
    
}
struct Node* findmin(struct Node* root)
{
    while(root->left!=NULL)
    root=root->left;
    return root;
}
struct Node* deletion(struct Node* root, char seat[])
{
    if(root == NULL)
        return root;

    if(strcmp(seat, root->seat) < 0)
        root->left= deletion(root->left, seat);
    else if(strcmp(seat, root->seat)>0)
        root->right= deletion(root->right, seat);
    else
    {
        // Node With One Child or No Child
        if(root->left==NULL)
        {
            struct Node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct Node* temp=root->left;
            free(root);
            return temp;
        }
        // Node with two children
        struct Node* temp=findmin(root->right);
        strcpy(root->seat,temp->seat);
        strcpy(root->name,temp->name);
        root->journey_time = temp->journey_time;
        root->issue_time = temp->issue_time;
        strcpy(root->phone,temp->phone);
        root->right=deletion(root->right,temp->seat);
    }
    return root;
}
double calculateRefund(double price, double hoursBefore)
{
    double refund;
    if(hoursBefore>=16)
    {
        refund=price-(price*.15);
        return refund;
    }
    else 
    {
        refund=0;
        return refund;
    }
}
void cancelTicket(int currentBusType)
{
    char seat_no[4];
    printf("Enter Seat No To Cancel:");
    scanf("%s",seat_no);
    if(currentBusType==0)
    {
    struct Node* found = search(non_ac_root, seat_no);

    if(found == NULL)
    {
    printf("No booking found for this seat!\n");
    }
    
    else
    { 
        non_ac_root = deletion(non_ac_root, seat_no);
        printf("Booking Cancelled\n");
        int i=0;
        while(i<32)
        {
            if(strcmp(non_ac_seats[0][i],seat_no)==0)
            {
               non_ac_booked[0][i]=0; 
               break;
            }
            i++;
        }
        time_t cancel_time=time(NULL);
        char time[30];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&cancel_time));
        char date[30];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&cancel_time));
        double diff_seconds = difftime( found->journey_time,cancel_time);
        double diff_hours = diff_seconds / 3600;
        double refund=calculateRefund(non_ac_price,diff_hours);
        printf("Refund Amount:%lf\n",refund);
    }
    }
    if(currentBusType==1)
    {
    struct Node* found = search(ac_root, seat_no);

    if(found == NULL)
    {
    printf("No booking found for this seat!\n");
    }
    else
    { 
        ac_root = deletion(ac_root, seat_no);
        printf("Booking Cancelled\n");
        int i=0;
        while(i<24)
        {
            if(strcmp(ac_seats[0][i],seat_no)==0)
            {
               ac_booked[0][i]=0; 
               break;
            }
            i++;
        }
        time_t cancel_time=time(NULL);
        char time[30];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&cancel_time));
        char date[30];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&cancel_time));
        double diff_seconds = difftime(found->journey_time,cancel_time);
        double diff_hours = diff_seconds / 3600;
        double refund=calculateRefund(ac_price,diff_hours);
        printf("Refund Amount:%lf\n",refund);
    }
    }
    if(currentBusType==2)
    {
        struct Node* found = search(Sleeper_root, seat_no);

        if(found == NULL)
        {
            printf("No booking found for this seat!\n");
        }
    else
    { 
        Sleeper_root = deletion(Sleeper_root, seat_no);
        printf("Booking Cancelled\n");
        int i=0;
        while(i<12)
        {
            if(strcmp(sleeper_seats[0][i],seat_no)==0)
            {
               sleeper_booked[0][i]=0; 
               break;
            }
            i++;
        }
        time_t cancel_time=time(NULL);
        char time[30];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&cancel_time));
        char date[30];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&cancel_time));
        double diff_seconds = difftime( found->journey_time,cancel_time);
        double diff_hours = diff_seconds / 3600;
        double refund=calculateRefund(sleeper_price,diff_hours);
        printf("Refund Amount:%lf\n",refund);
        
    }
    }
}
void printTicket(int currentBusType)
{
    char seat_no[4];
    printf("Enter seat number: ");
    scanf("%s", seat_no);
    if(currentBusType==0)
    {
    struct Node* result = search(non_ac_root, seat_no);

    if(result == NULL)
    {
        printf("No booking found for this seat!\n");
    }
    else
    {
        char time[20];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&result->issue_time));
        char date[20];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&result->issue_time));
        char jtime[20];
        strftime(jtime,sizeof(jtime),"%I:%M %p",localtime(&result->journey_time));
        char jdate[20];
        strftime(jdate,sizeof(jdate),"%d-%m-%Y",localtime(&result->journey_time));
        printf("\n====== TICKET DETAILS ======\n");
        printf("Seat Number    : %s\n", result->seat);
        printf("Name           : %s\n", result->name);
        printf("Phone          : %s\n", result->phone);
        printf("Date Of Issue  : %s\n",date);
        printf("Issued At      : %s\n", time);
        printf("Date Of Journey: %s\n",jdate);
        printf("Departure Time : %s\n",jtime);
        printf("From           : %s\n",from_location);
        printf("To             : %s\n",to_location);
        printf("==============================\n");
    }
    }
    else if(currentBusType==1)
    {
    struct Node* result = search(ac_root, seat_no);

    if(result == NULL)
    {
        printf("No booking found for this seat!\n");
    }
    else
    {
        char time[50];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&result->issue_time));
        char date[50];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&result->issue_time));
        char jtime[20];
        strftime(jtime,sizeof(jtime),"%I:%M %p",localtime(&result->journey_time));
        char jdate[20];
        strftime(jdate,sizeof(jdate),"%d-%m-%Y",localtime(&result->journey_time));
        printf("\n====== TICKET DETAILS ======\n");
        printf("Seat Number    : %s\n", result->seat);
        printf("Name           : %s\n", result->name);
        printf("Phone          : %s\n", result->phone);
        printf("Date Of Issue  : %s\n",date);
        printf("Issued At      : %s\n", time);
        printf("Date Of Journey: %s\n",jdate);
        printf("Departure Time : %s\n",jtime);
        printf("From           : %s\n",from_location);
        printf("To             : %s\n",to_location);
        printf("==============================\n");
    }
    }
    else if(currentBusType==2)
    {
    struct Node* result = search(Sleeper_root, seat_no);

    if(result == NULL)
    {
        printf("No booking found for this seat!\n");
    }
    else
    {
        char time[50];
        strftime(time,sizeof(time),"%I:%M %p",localtime(&result->issue_time));
        char date[50];
        strftime(date,sizeof(date),"%d-%m-%Y",localtime(&result->issue_time));
        char jtime[20];
        strftime(jtime,sizeof(jtime),"%I:%M %p",localtime(&result->journey_time));
        char jdate[20];
        strftime(jdate,sizeof(jdate),"%d-%m-%Y",localtime(&result->journey_time));
        printf("\n====== TICKET DETAILS ======\n");
        printf("Seat Number    : %s\n", result->seat);
        printf("Name           : %s\n", result->name);
        printf("Phone          : %s\n", result->phone);
        printf("Date Of Issue  : %s\n",date);
        printf("Issued At      : %s\n", time);
        printf("Date Of Journey: %s\n",jdate);
        printf("Departure Time : %s\n",jtime);
        printf("From           : %s\n",from_location);
        printf("To             : %s\n",to_location);
        printf("==============================\n");
    }
    }      
}
