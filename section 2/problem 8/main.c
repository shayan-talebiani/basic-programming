#include <stdio.h>

int main(){

    double x1, x2, x3;
    double y1, y2, y3;

    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);
    scanf("%lf %lf", &x3, &y3);

    double a12, a23, a31;
    double b12, b23, b31;

    int v = 0;
    
    double epsilon = 0.0000001;
    
    if(x2 == x1){
        v = 12;
    }else{
        a12 = (y2 - y1) / (x2 - x1 );
        b12 = (-a12 * x1) + y1;
    }

    if(x2 == x3){
        v = 23;
    }else{
        a23 = (y3 - y2) / (x3 - x2 );
        b23 = (-a23 * x2) + y2;
    }

    if(x3 == x1){
        v = 31;
    }else{
        a31 = (y1 - y3) / (x1 - x3 );
        b31 = (-a31 * x3) + y3;   
    }


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
        yMax = y1;
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

    double xEndDouble = xEnd;
    double yEndDouble = yEnd;

    for (double i = yStart; i <= yEndDouble; i++){
        
        for (double j = xStart; j <= xEndDouble; j++){

            if (j > xMin && i > yMin && j < xMax && i < yMax ){

                if(v != 12){

                    if ( (a12 * j + b12) <= (i + epsilon) && (a12 * j + b12) >= (i - epsilon) ){
                        continue;
                    }
                }

                if(v != 23){
                 
                    if ( (a23 * j + b23) <= (i + epsilon) && (a23 * j + b23) >= (i - epsilon) ){
                        continue;
                    }
                }

                if(v != 31){
                    
                    if ( (a31 * j + b31) <= (i + epsilon) && (a31 * j + b31) >= (i - epsilon) ){
                        continue;
                    }        
                }

                double xCross, yCross;

                // 3 p, 1 2

                if(x3 != j && v != 12){
                    
                    double ap3 = (y3 - i) / (x3 - j);
                    double bp3 = (-ap3 * x3) + y3;
                    
                    if ( ap3 == a12 ){
                        continue;
                    }            

                    xCross = -(bp3 - b12) / (ap3 - a12);
                    yCross = (ap3 * b12 - a12 * bp3) / (ap3 - a12);

                }else if(x3 == j && v != 12){    
                 
                    xCross = x3;
                    yCross = a12 * x3 + b12;

                }else if(x3 != j && v == 12){
                    
                    double ap3 = (y3 - i) / (x3 - j);
                    double bp3 = (-ap3 * x3) + y3;

                    xCross = x1;
                    yCross = ap3 * x1 + bp3;

                }else{
                    continue;
                }
                

                if ((( xCross <= j  && xCross >= x3  ) || ( xCross >= j  && xCross <= x3  )) && 
                    (( yCross <= i  && yCross >= y3  ) || ( yCross >= i  && yCross <= y3 )) ){
                    continue;
                }

                // 1 p, 2 3

                if(x1 != j && v != 23){
                    
                    double ap1 = (y1 - i) / (x1 - j);
                    double bp1 = (-ap1 * x1) + y1;
                    
                    if ( ap1 == a23 ){
                        continue;
                    }            

                    xCross = -(bp1 - b23) / (ap1 - a23);
                    yCross = (ap1 * b23 - a23 * bp1) / (ap1 - a23);

                }else if(x1 == j && v != 23){    
                 
                    xCross = x1;
                    yCross = a23 * x1 + b23;

                }else if(x1 != j && v == 23){
                    
                    double ap1 = (y1 - i) / (x1 - j);
                    double bp1 = (-ap1 * x1) + y1;

                    xCross = x2;
                    yCross = ap1 * x2 + bp1;

                }else{
                    continue;
                }
                

                if ((( xCross <= j  && xCross >= x1  ) || ( xCross >= j  && xCross <= x1  )) && 
                    (( yCross <= i  && yCross >= y1  ) || ( yCross >= i  && yCross <= y1 )) ){
                    continue;
                }

                // 2 p, 3 1

                if(x2 != j && v != 31){
                    
                    double ap2 = (y2 - i) / (x2 - j);
                    double bp2 = (-ap2 * x2) + y2;
                    
                    if ( ap2 == a31 ){
                        continue;
                    }            

                    xCross = -(bp2 - b31) / (ap2 - a31);
                    yCross = (ap2 * b31 - a31 * bp2) / (ap2 - a31);

                }else if(x2 == j && v != 31){    
                 
                    xCross = x2;
                    yCross = a31 * x2 + b31;

                }else if(x2 != j && v == 31){
                    
                    double ap2 = (y2 - i) / (x2 - j);
                    double bp2 = (-ap2 * x2) + y2;

                    xCross = x1;
                    yCross = ap2 * x1 + bp2;

                }else{
                    continue;
                }

                if ((( xCross <= j  && xCross >= x2  ) || ( xCross >= j  && xCross <= x2  )) && 
                    (( yCross <= i  && yCross >= y2  ) || ( yCross >= i  && yCross <= y2 )) ){
                    continue;
                }

                num += 1;

            }
            
        }
    }
    
    printf("%ld", num);

    return 0;
}