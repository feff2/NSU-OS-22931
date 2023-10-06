#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern char *tzname[];
main()
{
    time_t now;
    struct tm *sp;
    (void) time( &now );

    printf("%s", ctime( &now ) );

    sp = localtime(&now);
    if (sp->tm_hour+15 > 24){
        int h = (sp->tm_hour+15) - 24;
        int d = (sp->tm_mday+1);
        int m = sp->tm_mon+1;
        int y = sp->tm_year;
        if(sp->tm_mon+1 == 1 || sp->tm_mon+1 == 3 || sp->tm_mon+1 == 5 || sp->tm_mon+1 == 7 || sp->tm_mon+1 == 8|| sp->tm_mon+1 == 10 || sp->tm_mon == 12 && d > 31){
            m = sp->tm_mon+2;
            d = 1;
            if(m > 12){
                y = sp->tm_year+1;
                m = 1;        
           }
        }
        else if(sp->tm_mon+1 == 2 && d > 28){
            m = sp->tm_mon+2;
            d = 1;
        }
        else if(sp->tm_mon+1 == 4 || sp->tm_mon+1 == 6 || sp->tm_mon+1 == 9 || sp->tm_mon == 11 && d > 30){
            m = sp->tm_mon+2;
           d = 1; 
        }

         printf("%d/%d/%02d %d:%02d -08\n",
             m,d,y,h,sp->tm_min);    
    }
    else{
        printf("%d/%d/%02d %d:%02d %s\n",
            sp->tm_mon + 1, sp->tm_mday,
            sp->tm_year, sp->tm_hour,
            sp->tm_min, tzname[sp->tm_isdst]);
        exit(0);

    }   
}

