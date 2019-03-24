// displays today's name in UTC.
#include <stdio.h>
#include <time.h>
int main(void){
    char *day_name[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",};
    char *month_name[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Now", "Dec"};

    // now try playing with time functions.
    time_t t = time(NULL);
    struct tm *buf = gmtime(&t);
    int month = buf->tm_mon;
    int day = buf->tm_wday;

    printf("it is %s\n", month_name[month]);

    printf("it is %s\n", day_name[day]);
}
