#include <stdio.h>

int main(){

    double x1, x2, x3;
    double y1, y2, y3;

    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);
    scanf("%lf %lf", &x3, &y3);

    double a12, a23, a31;
    double c12, c23, c31;
    
    double epsilon0 = 0.0000000001;

    a12 = -(y2 - y1) / (x2 - x1 + epsilon0);
    a23 = -(y3 - y2) / (x3 - x2 + epsilon0);
    a31 = -(y1 - y3) / (x1 - x3 + epsilon0);

    c12 = (-a12 * x1) - y1;
    c23 = (-a23 * x2) - y2;
    c31 = (-a31 * x3) - y3;    

    double h12Power2, h23Power2, h31Power2, hPower2;
    double p12Power2, p23Power2, p31Power2;

    p12Power2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    p23Power2 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
    p31Power2 = (x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1);

    double epsilon1 = 0.000000001;
    double epsilon2 = 0.000001;

    double xMin, xMax;
    double yMin, yMax;

    long num = 0;

    int xStart, xEnd;
    int yStart, yEnd;

    if (x1 >= x2 && x1 >= x3){
        xMax = x1;
    }else if (x2 >= x1 && x2 >= x3){
        xMax = x2;
    }else {
        xMax = x3;
    }

    if (x1 <= x2 && x1 <= x3){
        xMin = x1;
    }else if (x2 <= x1 && x2 <= x3){
        xMin = x2;
    }else {
        xMin = x3;
    }
    

    if (y1 >= y2 && y1 >= y3){
        yMax = x1;
    }else if (y2 >= y1 && y2 >= y3){
        yMax = y2;
    }else {
        yMax = y3;
    }

    if (y1 <= y2 && y1 <= y3){
        yMin = y1;
    }else if (y2 <= y1 && y2 <= y3){
        yMin = y2;
    }else {
        yMin = y3;
    }

    xStart = xMin;
    xEnd = xMax;

    yStart = yMin;
    yEnd = yMax;

    for (int i = yStart; i <= yEnd; i++){
        
        for (int j = xStart; j <= xEnd; j++){

            if (j > xMin && i > yMin && j < xMax && i < yMax ){
                
                printf("x %d y %d \n", j, i);                

                h12Power2 = (a12 * j + i + c12) * (a12 * j + i + c12);
                h12Power2 /= (a12 * a12 + 1);

                if (h12Power2 <= epsilon1){
                    continue;
                }
                
                h23Power2 = (a23 * j + i + c23) * (a23 * j + i + c23);
                h23Power2 /= (a23 * a23 + 1);

                if (h23Power2 <= epsilon1){
                    continue;
                }

                h31Power2 = (a31 * j + i + c31) * (a31 * j + i + c31);
                h31Power2 /= (a31 * a31 + 1);

                if (h31Power2 <= epsilon1){
                    continue;
                }

                hPower2 = (a12 * x3 + y3 + c12) * (a12 * x3 + y3 + c12);
                hPower2 /= (a12 * a12 + 1);

                double delta = hPower2 * p12Power2 - h12Power2 * p12Power2 - h23Power2 * p23Power2 - h31Power2 * p31Power2;

                if (delta <= epsilon2 && delta >= -epsilon2 ){
                    num += 1;
                }


                

            }
            
        }
    }
    
    printf("%ld", num);

    return 0;
}