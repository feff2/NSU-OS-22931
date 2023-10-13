#include <sys/types.h>
#include <time.h>
#include <stdio.h>
char* zone[];

int main()
{

    time_t now;
    struct tm* a;
    time(&now);
    putenv("TZ=PDT");
    printf("%s", ctime(&now));
    a = localtime(&now);
    printf("%d/%d/%d %d:%d %s\n", a->tm_mon + 1, a->tm_mday, a->tm_year, a->tm_hour, a->tm_min, zone[a->tm_isdst]);
    return 0;
}