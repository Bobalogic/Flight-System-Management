/*
*File: proj.c
*Author: Afonso Palmeira 102696
*Description: A program to manage comercial flights in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INPUTMAX 10000      /*max input lenght*/
#define L_COUNTRY 31        /*max lenght of the country inserted*/
#define L_CITY 51           /*max lenght of the city inserted*/
#define AIRPORTMAX 41       /*max number of airports*/
#define L_ID 6              /*max lenght of an ID*/         
#define AIRPLISTMAX 200     /*max lenght of the airport vector*/
#define FLIGHTLISTMAX 30000 /*max number of flights*/
#define FLIGHTCODEMAX 7     /*max lenght of the flight code*/

/*function prototypes*/
int invalid_date(int nday, int nmonth, int nyear);
int datecomp(int day, int month, int year, int hour, int minute, int day1,
int month1, int year1, int hour1, int minute1);
int no_such(char narr_airID[5], char airID[5]);
int invalid_code(char new_code[7], int size);
int invalid_duration(int ndur_hour, int ndur_min);

void comm_a(char new_airpID[L_ID], char new_ctry[L_COUNTRY],
char new_city[L_CITY]);
void comm_l_listed(char airp_list[AIRPLISTMAX], int airp_number);
void comm_l_empty(int airp_number);
void comm_v_list(char new_code[FLIGHTCODEMAX],char airID[5],char narr_airID[5],
int nday, int nmonth, int nyear, int ndep_hour, int ndep_min, int ndur_hour, 
int ndur_min, int ncap);
void comm_v_empty(int flights_number);
void comm_t(int nday, int nmonth, int nyear);
void comm_c(char a_airID[5]);


/*global variables*/
int airp_number = 0;        /*current number of airports*/
int flights_number = 0;     /*current number of flights*/
int iday = 1;               /*initial day of date*/
int imonth = 1;             /*initial month of date*/
int iyear = 2022;           /*initial year of date*/

struct airport{
    char ID[5];
    char country[32];
    char city[52];
    int flights_number1;
};

struct flight{
    char CODE[FLIGHTCODEMAX];
    char ID_dep[5];
    char ID_arr[5];
    int d_day, d_month, d_year;
    int d_hour, d_min;
    int a_day, a_month, a_year;
    int a_hour, a_min;
    int dur_h, dur_min;
    int capacity;
};

struct airport max_air[AIRPORTMAX];         /*vector of airports*/
struct flight max_flight[FLIGHTLISTMAX];   /*vector of flights*/

/*This fucntion checks if the inserted date is valid or not, which means, 
if the inserted date is in the past of the actual date or if the inserted */
int invalid_date(int nday, int nmonth, int nyear){
    if (nyear < iyear){
        printf("invalid date\n");
        return 1;
    }
    if ((nyear == iyear) && (nmonth < imonth)){
        printf("invalid date\n");
        return 1;
    }
    if (nmonth == imonth){
        if (nday < iday){
            printf("invalid date\n");
            return 1;
        } 
    }
    if ((nyear == (iyear + 1)) && (nmonth > imonth)){
        printf("invalid date\n");
        return 1;
    }
    if ((nyear == (iyear + 1)) && (nmonth == imonth) && (nday > iday)){
        printf("invalid date\n");
        return 1;
    }
return 0;
}

/*This function receives two dates and two hours and will pass to multiple 
verifications to check if the date and the hours are acceptable or not 
according to the the defined criteria*/
int datecomp(int day, int month, int year, int hour, int minute, int day1,
             int month1, int year1, int hour1, int minute1){
    if (year == year1 && month == month1 && day == day1 && 
    hour == hour1 && minute == minute1){
        return 0;
    }
    if (year == year1 && month == month1 && day == day1 && hour == hour1){
        if (minute > minute1){
            return 1;
        }
        return 0;
    }
    if (year == year1 && month == month1 && day == day1 && hour != hour1){
        if (hour > hour1){
            return 1;
        }
        return 0;
    }
    if (year == year1 && month == month1 && day != day1){
        if (day > day1){
            return 1;
        }
        return 0;
    }
    if (year == year1 && month != month1){
        if (month > month1){
            return 1;
        }
        return 0;
    }
    if (year != year1){
        if (year > year1){
            return 1;
        }
        return 0;  
    }
    return 1; 
}

/*This function verifies if the received airport ID 
exists in the max_air vector, if not it prints the <airID>: no such airport*/
int no_such(char narr_airID[5], char airID[5]){
    int i, checker1 = 0, checker2 = 0; 
    for (i = 0; i < airp_number; i++){
        if (strcmp(narr_airID, max_air[i].ID) == 0){
            checker1 ++;
        }
        if (strcmp(airID, max_air[i].ID) == 0){
            checker2 ++;
        }    
    }
    if (checker1 == 0){
        printf("%s: no such airport ID\n", narr_airID);
        return 0;
    }
    if (checker2 == 0){
        printf("%s: no such airport ID\n", airID);
        return 0;
    }
    return 1;
}

/*This function receives a flight code and will verify if the code
follows the rules of: the code max lenght must be of 6, and if the flight
code is made of just 2 upper letters and then just digits*/
int invalid_code(char new_code[7], int size){
    int i;

    if (size >= 7){
        printf("invalid flight code\n");
        return 0;
    }
    for (i = 0; i < 2; i++){
        if ((isalpha(new_code[i]) && isupper(new_code[i]))){
            continue;
        }
        else{
            printf("invalid flight code\n");
            return 0;
        }
    }
    for (i = 2; i < (size); i++){
        if (isdigit(new_code[i])){
            continue;
        }
        else{
            printf("invalid flight code\n");
            return 0;
        }
    }
    return 1;
}

/*This function receives the duration of the flight and verifies if the
flight duration is at maximum 12:00 hours*/
int invalid_duration(int ndur_hour, int ndur_min){
    if (ndur_hour < 0 || ndur_hour > 12){
        printf("invalid duration\n");
        return 0;
    }
    if (ndur_min < 0 || ndur_min > 59){
        printf("invalid duration\n");
        return 0;
    }
    if (ndur_hour == 12 && ndur_min != 0){
        printf("invalid duration\n");
        return 0;
    }
    return 1;
}

/*Adds a new airport to our max_air(vector of structures). This function 
receives new_airpID(char), new_ctry(char) and new_city(char) as inputs, checks
for errors and if there's no errors it outputs 'airport <new_airpID> and adds 
1 to our airp_number (global variable)*/
void comm_a(char new_airpID[L_ID], char new_ctry[L_COUNTRY],
            char new_city[L_CITY]){
    int i, j;
    /*checks if the ID inserted is valid*/
    if (strlen(new_airpID) != 3){
        printf("invalid airport ID\n");
        return;
    }
    if (airp_number >= 40){
        printf("too many airports\n");
        return;
    }
    for (i = 0; i < 3; i++){
        if (islower(new_airpID[i])){
            printf("invalid airport ID\n");
            return;
        }
    }
    for (j = 0; j < airp_number; j++){
        if (strcmp((max_air[j].ID), new_airpID) == 0){
            printf("duplicate airport\n");
            return;
        }
    }
    /*if no errors continue*/
    strcpy(max_air[airp_number].ID, new_airpID);
    strcpy(max_air[airp_number].country, new_ctry);
    strcpy(max_air[airp_number].city, new_city);
    airp_number++;
    printf("airport %s\n", new_airpID);
}

/*Prints all the airports by the order of input defined in the airp_list
with the command l. Since we want to know what is the order given 
*/
void comm_l_listed(char airp_list[AIRPLISTMAX], int airp_number){
    int i, j, checker = 0;

    char *ID = strtok(airp_list, " ");
    while (ID != NULL){
        /* check for errors*/
        for (j = 0; j < airp_number; j++){
            if (strcmp(max_air[j].ID, ID) == 0){
                checker += 1;
            }
        }
        if (checker == 0){
            printf("%s: no such airport ID\n", ID);
        }
        checker = 0;
        /*if no errors continue and prints all the airports and the 
        rest of their struct with the specific order of IDs given by the user*/
        for (i = 0; i < airp_number; i++){
            if (strcmp(max_air[i].ID, ID) == 0){
                printf("%s %s %s %d\n", max_air[i].ID, max_air[i].city, 
                max_air[i].country, max_air[i].flights_number1);
            };
        }
        ID = strtok(NULL, " ");
    }
}

/*This function prints all the airports that are in the vector
of all airports (max_airp) by alphabetical order*/
void comm_l_empty(int airp_number)
{
    int i, j;
    char idlist[40][4] = {0};
    int ids[AIRPORTMAX] = {0};
    char temp[4] = {0};
    int x;
    /*creates an array of the IDs with their predifined order*/
    for (i = 0; i < airp_number; i++){
        strcpy(idlist[i], max_air[i].ID);
        ids[i] = i;
    }
    /*Bubble sorte by alphabetical order of the IDs*/
    for (i = 1; i < airp_number; i++){
        for (j = 0; j < (airp_number - 1); j++){
            if (strcmp(idlist[j], idlist[j + 1]) > 0){
                strcpy(temp, idlist[j]);
                strcpy(idlist[j], idlist[j + 1]);
                strcpy(idlist[j + 1], temp);
                x = ids[j];
                ids[j] = ids[j+1];
                ids[j+1] = x;
            }
        }
    }
    /*Prints all the airports and the rest of their struct 
    by alphabetical order*/
    for (i = 0; i < airp_number; i++){
        x = ids[i];
        printf("%s %s %s %d\n", max_air[x].ID, max_air[x].city, 
        max_air[x].country, max_air[x].flights_number1);
    }
}

/*This function receives a flight code, the ID of departure and arrival 
of that flight, the date of departure, the duration time and the capacity
of that flight and adds all the information to the vector 
of flights (max_flight)*/
void comm_v_list(char new_code[FLIGHTCODEMAX],char airID[5],char narr_airID[5],
 int nday, int nmonth, int nyear, int ndep_hour, int ndep_min, int ndur_hour, 
 int ndur_min, int ncap)
{
    int i, j, size;
    size = strlen(new_code);

    /*Checking if the flight code is correct*/
    if (invalid_code(new_code, size) == 0){
        return;
    }
    
    /*Checking if the correspondent ID of the departure and of the 
    arrival exists*/
    if (no_such(narr_airID,airID) == 0){
        return;
    }
    
    /*Verifying if the new flight created will exceed the allowed 
    number of flights 30000*/
    if (flights_number == FLIGHTLISTMAX){
        printf("too many flights\n");
        return;
    }
    /*Checking if the date inserted is in the past or if it's more 
    than 1 year after the current day which means i am verifying is the 
    date is valid*/
    if(invalid_date(nday, nmonth, nyear)){
        return;
    }
    /*Checking if the duration of the flight is valid*/
    if (invalid_duration(ndur_hour, ndur_min) == 0){
        return;
    }
    /*Checking if the capacity of the flight inserted is valid*/ 
    if (!(ncap >= 10 && ncap <= 100)){
        printf("invalid capacity\n");
        return;
    }
    /*Checking if there are another flight with the same flight code in the 
    same day*/
    for (i = 0; i < flights_number; i++){
        if (strcmp((max_flight[i].CODE), new_code) == 0){
            for (j = 0; j < flights_number; j++){
                if ((max_flight[j].d_day == nday) && 
                (max_flight[j].d_month == nmonth) && 
                (max_flight[j].d_year == nyear)){
                    printf("flight already exists\n");
                    return;
                }
            }
        }
    }
    /*if no errors continue:
    and creates the new airport and adds him to the vector of airports*/
    strcpy(max_flight[flights_number].CODE,new_code);
    strcpy(max_flight[flights_number].ID_dep,airID);
    strcpy(max_flight[flights_number].ID_arr,narr_airID);
    max_flight[flights_number].d_day = nday;
    max_flight[flights_number].d_month = nmonth;
    max_flight[flights_number].d_year = nyear;
    max_flight[flights_number].d_hour = ndep_hour;
    max_flight[flights_number].d_min = ndep_min;
    max_flight[flights_number].dur_h = ndur_hour;
    max_flight[flights_number].dur_min = ndur_min;
    max_flight[flights_number].capacity = ncap;
    flights_number++;
}

/*This fucntion prints all the flights of the max_flight vector
and their caracteristcs*/
void comm_v_empty(int flights_number){
    int i;
    /*This command based on the total number of flights will iterate the 
    max_flight array and print 1 by one the flight by the order 
    previous inserted and his characteristics*/
    for (i = 0; i < flights_number; i++){
        printf("%s %s %s %02d-%02d-%d %02d:%02d\n", max_flight[i].CODE, 
        max_flight[i].ID_dep, max_flight[i].ID_arr, max_flight[i].d_day, 
        max_flight[i].d_month, max_flight[i].d_year, max_flight[i].d_hour, 
        max_flight[i].d_min);
    }
}

/*This function changes the actual date to the date inserted only if the 
inserted date is valid, which means, if is not in the past or if is no longer
than a year*/
void comm_t(int nday, int nmonth, int nyear){
    if(!(invalid_date(nday, nmonth, nyear))){
        iday = nday;
        imonth = nmonth;
        iyear = nyear;
        printf("%02d-%02d-%02d\n", nday, nmonth, nyear);
    }
}

/*This function receives an airport ID, of departure, and then prints all the
flights whose origin is from the ID received, their destiny airport
and the date and time of departure*/
void comm_p(char d_airID[5], struct flight sortlist[FLIGHTLISTMAX]){
    int i, j, checker = 0;
    struct flight temp;

    /*Checks if the airport ID given of departure exists */
    for (i = 0; i < flights_number; i++){
      if(strcmp(d_airID, max_air[i].ID) == 0){
          checker ++;
      }
    }
    if (checker == 0)
    {
        printf("%s: no such airport ID\n", d_airID);
        return;
    }

    /*if no errors continue:*/
    
    sortlist = max_flight;
    
    /*Inserts in the a new vector with the IDs of the depertures airports
    the new ID given*/
    for(i=0;i<flights_number-1;i++){
        for(j=0;j< flights_number-i-1;j++){
            if(datecomp(sortlist[j].d_day, sortlist[j].d_month, 
            sortlist[j].d_year,sortlist[j].d_hour,sortlist[j].d_min,
            sortlist[j+1].d_day,sortlist[j+1].d_month,sortlist[j+1].d_year,
            sortlist[j+1].d_hour,sortlist[j+1].d_min) == 1){
                    temp = sortlist[j];
                    sortlist[j] = sortlist[j+1];
                    sortlist[j+1] = temp;
            }
        }
    }

    /*Prints all the flights of existing that departures of the ID given*/
    for (j = 0; j < flights_number ; j++){
        if(strcmp(sortlist[j].ID_dep, d_airID) == 0){
            printf("%s %s %02d-%02d-%d %02d:%02d\n", sortlist[j].CODE, 
            sortlist[j].ID_arr, sortlist[j].d_day, sortlist[j].d_month, 
            sortlist[j].d_year, sortlist[j].d_hour, sortlist[j].d_min);
        }
    }
}

void comm_c(char a_airID[5]){
    int i,y = 0, checker = 0;
    struct flight max_flight1[5000];

    /*Checks if the airport ID given of arrival exists */
    for (i = 0; i < flights_number; i++){
      if(strcmp(a_airID, max_air[i].ID) == 0){
          checker ++;
      }
    }
    if (checker == 0){
        printf("%s: no such airport ID\n", a_airID);
        return;
    }
    /*if no errors continue:*/
    for (i = 0; i < airp_number; i++){
        if(strcmp(a_airID, max_air[i].ID)==0){
            strcpy(max_flight1[y].ID_dep, a_airID);
            y++;
        }
    }
    printf("Error");
    return;
}

/*Reads the input line with some scanfs until de input command line is 'q', 
because the 'q' command closes the program*/
int main()
{
    struct flight sortlist[FLIGHTLISTMAX];
    char comm, new_airpID[L_ID] = {0}, new_ctry[L_COUNTRY] = {0}, new_city[L_CITY] = {0};
    char airp_list[AIRPLISTMAX] = {0};
    char new_code[FLIGHTCODEMAX] = {0}, a_airID[5] = {0};
    char narr_airID[5] = {0}, d_airID[5] = {0}, airID[5] = {0};
    int nday, nmonth, nyear, ndep_hour, ndep_min, ndur_hour, ndur_min, ncap;

    while (1)
    {
        scanf("%c", &comm);
        if (comm == 'a'){
            scanf("%s %s %[^\n]", new_airpID, new_ctry, new_city);
            comm_a(new_airpID, new_ctry, new_city);
        }
        if (comm == 'l'){
            scanf("%[^\n]", airp_list);
            if (strlen(airp_list) == 0){
                comm_l_empty(airp_number);
            }
            else{
                comm_l_listed(airp_list, airp_number);
            }
        }
        if(comm == 'v'){
            if (getchar() == '\n'){
                comm_v_empty(flights_number);
            }
            else{
            scanf("%s%s%s%d-%d-%d%d:%d%d:%d%d",new_code,airID,narr_airID,&nday,
            &nmonth,&nyear,&ndep_hour,&ndep_min,&ndur_hour,&ndur_min,&ncap);
            comm_v_list(new_code,airID,narr_airID,nday,nmonth,nyear,ndep_hour,
            ndep_min,ndur_hour,ndur_min,ncap);
            }
        }
        if (comm == 'p'){
            scanf("%s", d_airID);
            comm_p(d_airID, sortlist);
        }
        if (comm == 'c'){
            scanf("%s", a_airID);
            comm_c(a_airID);
        }  
        if (comm == 't'){
            scanf("%d-%d-%d", &nday, &nmonth, &nyear);
            comm_t(nday, nmonth, nyear);
        }
/*-------------------------------------------------------*/
        /* Terminates the program */
        if (comm == 'q'){
            exit(0);
        }
    }
    return 0;
}
