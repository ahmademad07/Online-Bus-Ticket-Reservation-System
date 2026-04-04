#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void selectBusType();
void showroute();
void initializeSeats();
void showSeats(int busType);
void bookTicket(int busType);
void cancelTicket(int busType);
void printTicket();
int calculateRefund(float price, int hoursBefore);

int currentBusType = -1;
char seats[3][32][4];
int booked[3][32];
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
                printTicket();
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
    printf("1. AC\n");
    printf("2. Non-AC\n");
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
        if(currentBusType == 0)
            printf("AC Bus Selected\n");
        else if(currentBusType == 1)
            printf("Non-AC Bus Selected\n");
        else
            printf("Sleeper Bus Selected\n");
    }
}
void showroute()
{

}
void initializeSeats()
{
    char row;
    int num;
    int index;

    for(int bus = 0; bus < 3; bus++)
    {
        index = 0;
        row = 'A';

        for(int i = 0; i < 8; i++)
        {
            for(num = 1; num <= 4; num++)
            {
                sprintf(seats[bus][index], "%c%d", row, num);
                booked[bus][index] = 0;
                index++;
            }
            row++;
        }
    }
}
void showSeats(int busType)
{
    initializeSeats();
    printf("Seats:\n");

    for(int i=0; i<32; i++)
    {
        if(booked[busType][i] == 0)
            printf("%s ", seats[busType][i]);
        else
            printf("X");

        if((i+1)%2 == 0)
            printf("  ");

        if((i+1)%4 == 0)
            printf("\n");
    }
}

void bookTicket(int busType)
{

}
void cancelTicket(int busType)
{

}
void printTicket()
{

}

