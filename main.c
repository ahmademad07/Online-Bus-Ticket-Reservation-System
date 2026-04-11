#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void selectBusType();
void showroute();
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
char non_ac_seats[1][32][4];
char ac_seats[1][24][4];
char sleeper_seats[1][12][4];
int  non_ac_booked[1][32];
int  ac_booked[1][24];
int  sleeper_booked[1][12];

char divisions[8][20] = {
    "Dhaka", "Chittagong", "Sylhet", "Rajshahi",
    "Khulna", "Barisal", "Rangpur", "Mymensingh"
};

char districts[8][10][20] = {
    {"Dhaka", "Faridpur", "Gazipur", "Gopalganj", "Kishoreganj", "Madaripur", "Manikganj", "Munshiganj", "Narsingdi", "Tangail"},
    {"Bandarban", "Brahmanbaria", "Chandpur", "Chattogram", "Cox's Bazar", "Feni", "Khagrachhari", "Lakshmipur", "Noakhali", "Rangamati"},
    {"Habiganj", "Moulvibazar", "Sunamganj", "Sylhet"},
    {"Bogra", "Joypurhat", "Naogaon", "Natore", "Chapainawabganj", "Pabna", "Rajshahi", "Sirajganj"},
    {"Bagerhat", "Chuadanga", "Jashore", "Jhenaidah", "Khulna", "Kushtia", "Magura", "Meherpur", "Narail", "Satkhira"},
    {"Barguna", "Barisal", "Bhola", "Jhalokathi", "Patuakhali", "Pirojpur"},
    {"Dinajpur", "Gaibandha", "Kurigram", "Lalmonirhat", "Nilphamari", "Panchagarh", "Rangpur", "Thakurgaon"},
    {"Jamalpur", "Mymensingh", "Netrokona", "Sherpur"}
};

int districtCount[8] = {10,10,4,8,10,6,8,4};

int divisionGraph[8][8] = {
    {0,1,1,1,1,1,1,1},
    {1,0,1,1,1,1,1,1},
    {1,1,0,1,1,1,1,1},
    {1,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,1},
    {1,1,1,1,1,0,1,1},
    {1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,0}
};

int selectedFromDiv = -1;
int selectedFromDist = -1;
int selectedToDiv = -1;
int selectedToDist = -1;

struct Node
{
    char seat[4];
    char name[50];
    char phone[15];

    int fromDiv;
    int fromDist;
    int toDiv;
    int toDist;

    time_t issue_time;
    time_t journey_time;

    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;
struct Node* insert(struct Node* root, char seat[],char name[],char phone[],int fromDiv,int fromDist,int toDiv,int toDist,time_t issue_time,time_t journey_time)
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
        newNode->fromDiv = fromDiv;
        newNode->fromDist = fromDist;
        newNode->toDiv = toDiv;
        newNode->toDist = toDist;
        return newNode;
    }

    if(strcmp(seat, root->seat) < 0)
        root->left = insert(root->left,seat, name, phone,fromDiv, fromDist,toDiv, toDist,issue_time,journey_time);
    else
        root->right = insert(root->right,seat, name, phone,fromDiv, fromDist,toDiv, toDist,issue_time,journey_time);

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
        printf("2.Show Route\n");
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
                showroute();
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

void showroute()
{
    printf("\nSelect From Division:\n");
    for(int i=0;i<8;i++)
        printf("%d. %s\n",i,divisions[i]);

    scanf("%d",&selectedFromDiv);

    if(selectedFromDiv < 0 || selectedFromDiv >= 8) return;

    printf("\nSelect From District:\n");
    for(int i=0;i<districtCount[selectedFromDiv];i++)
        printf("%d. %s\n",i,districts[selectedFromDiv][i]);

    scanf("%d",&selectedFromDist);

    printf("\nSelect To Division:\n");
    for(int i=0;i<8;i++)
        if(divisionGraph[selectedFromDiv][i])
            printf("%d. %s\n",i,divisions[i]);

    scanf("%d",&selectedToDiv);

    if(selectedToDiv < 0 || selectedToDiv >= 8) return;

    printf("\nSelect To District:\n");
    for(int i=0;i<districtCount[selectedToDiv];i++)
        printf("%d. %s\n",i,districts[selectedToDiv][i]);

    scanf("%d",&selectedToDist);

    printf("\nRoute Selected Successfully\n");
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
     else if(currentBusType==1)
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
            if(non_ac_booked[0][i]==0)
                printf("%s ", non_ac_seats[0][i]);
            else
                printf("XX ");

            if((i+1)%4==0)
                printf("\n");
        }
    }

    else if(currentBusType==1)
    {
        for(int i=0; i<24; i++)
        {
            if(ac_booked[0][i]==0)
                printf("%s ", ac_seats[0][i]);
            else
                printf("XX ");

            if((i+1)%3==0)
                printf("\n");
        }
    }

    else if(currentBusType==2)
    {
        for(int i=0; i<12; i++)
        {
            if(sleeper_booked[0][i]==0)
                printf("%s ", sleeper_seats[0][i]);
            else
                printf("XX ");

            if((i+1)%2==0)
                printf("\n");
        }
    }
}

void selectBusType()
{
    printf("1.Non-AC\n2.AC\n3.Sleeper\n");
    scanf("%d",&currentBusType);
    currentBusType--;

    if(currentBusType < 0 || currentBusType > 2)
    {
        printf("Invalid Bus Type\n");
        currentBusType = -1;
        return;
    }

    initializeSeats(currentBusType);
}

void bookTicket(int currentBusType)
{


    if(currentBusType==0)
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

           root = insert(root, seat_no, name, phone, selectedFromDiv,selectedFromDist,selectedToDiv,selectedToDist,issue_time,journey_time);

           printf("\nSeat booked successfully!\n");
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

           root = insert(root, seat_no, name, phone, selectedFromDiv,selectedFromDist,selectedToDiv,selectedToDist,issue_time,journey_time);
           printf("\nSeat booked successfully!\n");
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

           root = insert(root, seat_no, name, phone, selectedFromDiv,selectedFromDist,selectedToDiv,selectedToDist,issue_time,journey_time);
           printf("\nSeat booked successfully!\n");
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
    struct Node* found = search(root, seat_no);

    if(found == NULL)
    {
    printf("No booking found for this seat!\n");
    }

    else
    {
        root = deletion(root, seat_no);
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
    struct Node* found = search(root, seat_no);

    if(found == NULL)
    {
    printf("No booking found for this seat!\n");
    }
    else
    {
        root = deletion(root, seat_no);
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
        struct Node* found = search(root, seat_no);

        if(found == NULL)
        {
            printf("No booking found for this seat!\n");
        }
    else
    {
        root = deletion(root, seat_no);
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
        double diff_seconds = difftime(cancel_time, found->journey_time);
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

    struct Node* result = search(root, seat_no);

    if(result == NULL)
    {
        printf("No booking found for this seat!\n");
        return;
    }

    char timeStr[20], dateStr[20];
    char jtime[20], jdate[20];

    strftime(timeStr, sizeof(timeStr), "%I:%M %p", localtime(&result->issue_time));
    strftime(dateStr, sizeof(dateStr), "%d-%m-%Y", localtime(&result->issue_time));

    strftime(jtime, sizeof(jtime), "%I:%M %p", localtime(&result->journey_time));
    strftime(jdate, sizeof(jdate), "%d-%m-%Y", localtime(&result->journey_time));
    char *busType[] = {"Non-AC", "AC", "Sleeper"};
    printf("\n====== TICKET DETAILS ======\n");
    printf("Bus Type       : %s\n", busType[currentBusType]);
    printf("Seat Number    : %s\n", result->seat);
    printf("Name           : %s\n", result->name);
    printf("Phone          : %s\n", result->phone);

    printf("From           : %s (%s)\n",
        divisions[result->fromDiv],
        districts[result->fromDiv][result->fromDist]);

    printf("To             : %s (%s)\n",
        divisions[result->toDiv],
        districts[result->toDiv][result->toDist]);

    printf("Date Of Issue  : %s\n", dateStr);
    printf("Issued At      : %s\n", timeStr);
    printf("Date Of Journey: %s\n", jdate);
    printf("Departure Time : %s\n", jtime);

    printf("============================\n");

}

