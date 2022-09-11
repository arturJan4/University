#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define M_PI 3.14159265358979323846

// draws an analog clock onto console

double getHourAngleFromInput(int hour,int minute)
{
    //returns hour hand angle(starting from x - axis)
    double fullHour = hour + (double)(minute)/60;

    if(fullHour >= 12.0)
    {
        fullHour -= 12.0;
    }
    double angle = ((double)M_PI/2) * (1 - (fullHour/3));

    return angle;
}

double getMinuteAngleFromInput(int minute)
{
    //returns minute hand angle(starting from x - axis)
    minute = minute % 60;
    double angle = ((double)M_PI/2) * (1 - ((double)minute/15));

    return angle;
}

double fromRadians(double phi)
{
    //converts from radians to degrees
    return ((phi*180)/M_PI);
}

bool inCircle(int r, double x, double y)
{
    return ( ((x * x) + (y * y)) < (r*r));
}

bool isHand(double x, double y, double phi)
{
    double distance = sqrt(x*x + y*y);

    double CurCos = x/distance;
    double CurSin = y/distance;

    double goalCos = cos(phi);
    double goalSin = sin(phi);

    double thinner = distance/3; // without this hand gets bigger with distance
    double thickness = 0.2 / thinner; //acceptable angle differnce

    if(CurCos < goalCos + thickness && CurCos > goalCos - thickness)
    {
        if(CurSin < goalSin + thickness && CurSin > goalSin - thickness)
        {
            return true;
        }
    }

    return false;
}

bool isShorterThanHourHand(int x, int y, int r)
{
    double distance = sqrt(x*x + y * y);
    if(distance < r * 0.6)
        return true;
    else
        return false;
}

int main()
{
    const int radiusClock = 10;
    int hour, minute;
    scanf("%d %d", &hour, &minute);

    double angleHour = getHourAngleFromInput(hour,minute);
    double angleMin = getMinuteAngleFromInput(minute);

    for(double i = radiusClock - 0.5; i >= -radiusClock + 0.5; --i)
    {
        for(double j = -radiusClock + 0.5; j <= radiusClock - 0.5; ++j)
        {
            if(inCircle(radiusClock,j,i))
            {
                if(isShorterThanHourHand(j,i,radiusClock) && isHand(j,i,angleHour))
                    printf("#");
                else if(isHand(j,i,angleMin))
                    printf("X");
                else
                    printf(".");
            }
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}
