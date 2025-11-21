#include <stdio.h>

int main(){
    
    unsigned long long k;
    
    scanf("%llu", &k);

    int areaCount = 0;

    int n = 8;

    //i : 0
    for (int j = 0; j < n; j++){

        int i = 0;

        int digit = (k >> (j + i * n)) & 1;

        if(digit == 0){
                        
            unsigned long long deep = 0;

            unsigned long long zeroxlocations0 = 0;
            unsigned long long zeroxlocations1 = 0;
            unsigned long long zeroxlocations2 = 0;
            unsigned long long zeroxlocations3 = 0;

            unsigned long long zeroylocations0 = 0;
            unsigned long long zeroylocations1 = 0;
            unsigned long long zeroylocations2 = 0;
            unsigned long long zeroylocations3 = 0;

            unsigned long long jCopy = j;
            unsigned long long iCopy = i;

            k += ((unsigned long long)1) << (jCopy + iCopy * n);

            
            if (deep < 21){
                zeroxlocations0 += jCopy << (3 * (deep));
                zeroylocations0 += iCopy << (3 * (deep));
            }else if (deep < 42){
                unsigned long long deep1 = deep - 21; 
                zeroxlocations1 += jCopy << (3 * (deep1));
                zeroylocations1 += iCopy << (3 * (deep1));
            }else if (deep < 63){
                unsigned long long deep2 = deep - 42; 
                zeroxlocations2 += jCopy << (3 * (deep2));
                zeroylocations2 += iCopy << (3 * (deep2));
            }else{
                unsigned long long deep3 = deep - 63; 
                zeroxlocations3 += jCopy << (3 * (deep3));
                zeroylocations3 += iCopy << (3 * (deep3));                    
            }


            while (1){
                

                int done = 0;

                if(iCopy  >= 1){

                    digit = (k >> (jCopy  + (iCopy - 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);



                    }
                }
                
                if (done == 0 && (jCopy + 1) < n){

                    digit = (k >> ((jCopy + 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);



                    }
                }

                if (done == 0 && (iCopy + 1) < n){

                    digit = (k >> (jCopy  + (iCopy + 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);




                    }
                }

                if (done == 0 && jCopy >= 1){

                    digit = (k >> ((jCopy - 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);



                    }
                }

                if(done == 0){
                    if(deep == 0){
                        break;
                    }

                    if (deep < 21){
                        zeroxlocations0 -= ((zeroxlocations0 >> (3 * deep)) & 7) << (3 * deep);
                        zeroylocations0 -= ((zeroylocations0 >> (3 * deep)) & 7) << (3 * deep);
                    }else if (deep < 42){
                        unsigned long long deep1 = deep - 21; 
                        zeroxlocations1 -= ((zeroxlocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                        zeroylocations1 -= ((zeroylocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                    }else if (deep < 63){
                        unsigned long long deep2 = deep - 42;
                        zeroxlocations2 -= ((zeroxlocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                        zeroylocations2 -= ((zeroylocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                    }else{
                        unsigned long long deep3 = deep - 63;
                        zeroxlocations3 -= ((zeroxlocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                        zeroylocations3 -= ((zeroylocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                    }


                    if (deep < 22){
                        jCopy = (zeroxlocations0 >> (3 * (deep - 1))) & 7;
                        iCopy = (zeroylocations0 >> (3 * (deep - 1))) & 7;
                    }else if (deep < 43){
                        unsigned long long deep1 = deep - 21; 
                        jCopy = (zeroxlocations1 >> (3 * (deep1 - 1))) & 7;
                        iCopy = (zeroylocations1 >> (3 * (deep1 - 1))) & 7;
                    }else if (deep < 64){
                        unsigned long long deep2 = deep - 42;
                        jCopy = (zeroxlocations2 >> (3 * (deep2 - 1))) & 7;
                        iCopy = (zeroylocations2 >> (3 * (deep2 - 1))) & 7;
                    }

                    deep -= 1;

                }
                


            }

        }


        

    }

    //i : 7
    for (int j = 0; j < n; j++){

        int i = 7;

        int digit = (k >> (j + i * n)) & 1;

        if(digit == 0){
                        
            unsigned long long deep = 0;

            unsigned long long zeroxlocations0 = 0;
            unsigned long long zeroxlocations1 = 0;
            unsigned long long zeroxlocations2 = 0;
            unsigned long long zeroxlocations3 = 0;

            unsigned long long zeroylocations0 = 0;
            unsigned long long zeroylocations1 = 0;
            unsigned long long zeroylocations2 = 0;
            unsigned long long zeroylocations3 = 0;

            unsigned long long jCopy = j;
            unsigned long long iCopy = i;

            k += ((unsigned long long)1) << (jCopy + iCopy * n);
            
            if (deep < 21){
                zeroxlocations0 += jCopy << (3 * (deep));
                zeroylocations0 += iCopy << (3 * (deep));
            }else if (deep < 42){
                unsigned long long deep1 = deep - 21; 
                zeroxlocations1 += jCopy << (3 * (deep1));
                zeroylocations1 += iCopy << (3 * (deep1));
            }else if (deep < 63){
                unsigned long long deep2 = deep - 42; 
                zeroxlocations2 += jCopy << (3 * (deep2));
                zeroylocations2 += iCopy << (3 * (deep2));
            }else{
                unsigned long long deep3 = deep - 63; 
                zeroxlocations3 += jCopy << (3 * (deep3));
                zeroylocations3 += iCopy << (3 * (deep3));                    
            }


            while (1){
                

                int done = 0;

                if(iCopy  >= 1){

                    digit = (k >> (jCopy  + (iCopy - 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }
                
                if (done == 0 && (jCopy + 1) < n){

                    digit = (k >> ((jCopy + 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && (iCopy + 1) < n){

                    digit = (k >> (jCopy  + (iCopy + 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && jCopy >= 1){

                    digit = (k >> ((jCopy - 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if(done == 0){
                    if(deep == 0){
                        break;
                    }

                    if (deep < 21){
                        zeroxlocations0 -= ((zeroxlocations0 >> (3 * deep)) & 7) << (3 * deep);
                        zeroylocations0 -= ((zeroylocations0 >> (3 * deep)) & 7) << (3 * deep);
                    }else if (deep < 42){
                        unsigned long long deep1 = deep - 21; 
                        zeroxlocations1 -= ((zeroxlocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                        zeroylocations1 -= ((zeroylocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                    }else if (deep < 63){
                        unsigned long long deep2 = deep - 42;
                        zeroxlocations2 -= ((zeroxlocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                        zeroylocations2 -= ((zeroylocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                    }else{
                        unsigned long long deep3 = deep - 63;
                        zeroxlocations3 -= ((zeroxlocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                        zeroylocations3 -= ((zeroylocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                    }


                    if (deep < 22){
                        jCopy = (zeroxlocations0 >> (3 * (deep - 1))) & 7;
                        iCopy = (zeroylocations0 >> (3 * (deep - 1))) & 7;
                    }else if (deep < 43){
                        unsigned long long deep1 = deep - 21; 
                        jCopy = (zeroxlocations1 >> (3 * (deep1 - 1))) & 7;
                        iCopy = (zeroylocations1 >> (3 * (deep1 - 1))) & 7;
                    }else if (deep < 64){
                        unsigned long long deep2 = deep - 42;
                        jCopy = (zeroxlocations2 >> (3 * (deep2 - 1))) & 7;
                        iCopy = (zeroylocations2 >> (3 * (deep2 - 1))) & 7;
                    }

                    deep -= 1;

                }
                    

            }

        }


        

    }

    //j : 0
    for (int i = 0; i < n; i++){

        int j = 0;

        int digit = (k >> (j + i * n)) & 1;

        if(digit == 0){
                        
            unsigned long long deep = 0;

            unsigned long long zeroxlocations0 = 0;
            unsigned long long zeroxlocations1 = 0;
            unsigned long long zeroxlocations2 = 0;
            unsigned long long zeroxlocations3 = 0;

            unsigned long long zeroylocations0 = 0;
            unsigned long long zeroylocations1 = 0;
            unsigned long long zeroylocations2 = 0;
            unsigned long long zeroylocations3 = 0;

            unsigned long long jCopy = j;
            unsigned long long iCopy = i;

            k += ((unsigned long long)1) << (jCopy + iCopy * n);
            
            if (deep < 21){
                zeroxlocations0 += jCopy << (3 * (deep));
                zeroylocations0 += iCopy << (3 * (deep));
            }else if (deep < 42){
                unsigned long long deep1 = deep - 21; 
                zeroxlocations1 += jCopy << (3 * (deep1));
                zeroylocations1 += iCopy << (3 * (deep1));
            }else if (deep < 63){
                unsigned long long deep2 = deep - 42; 
                zeroxlocations2 += jCopy << (3 * (deep2));
                zeroylocations2 += iCopy << (3 * (deep2));
            }else{
                unsigned long long deep3 = deep - 63; 
                zeroxlocations3 += jCopy << (3 * (deep3));
                zeroylocations3 += iCopy << (3 * (deep3));                    
            }


            while (1){
                

                int done = 0;

                if(iCopy  >= 1){

                    digit = (k >> (jCopy  + (iCopy - 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }
                
                if (done == 0 && (jCopy + 1) < n){

                    digit = (k >> ((jCopy + 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && (iCopy + 1) < n){

                    digit = (k >> (jCopy  + (iCopy + 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && jCopy >= 1){

                    digit = (k >> ((jCopy - 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if(done == 0){
                    if(deep == 0){
                        break;
                    }

                    if (deep < 21){
                        zeroxlocations0 -= ((zeroxlocations0 >> (3 * deep)) & 7) << (3 * deep);
                        zeroylocations0 -= ((zeroylocations0 >> (3 * deep)) & 7) << (3 * deep);
                    }else if (deep < 42){
                        unsigned long long deep1 = deep - 21; 
                        zeroxlocations1 -= ((zeroxlocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                        zeroylocations1 -= ((zeroylocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                    }else if (deep < 63){
                        unsigned long long deep2 = deep - 42;
                        zeroxlocations2 -= ((zeroxlocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                        zeroylocations2 -= ((zeroylocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                    }else{
                        unsigned long long deep3 = deep - 63;
                        zeroxlocations3 -= ((zeroxlocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                        zeroylocations3 -= ((zeroylocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                    }


                    if (deep < 22){
                        jCopy = (zeroxlocations0 >> (3 * (deep - 1))) & 7;
                        iCopy = (zeroylocations0 >> (3 * (deep - 1))) & 7;
                    }else if (deep < 43){
                        unsigned long long deep1 = deep - 21; 
                        jCopy = (zeroxlocations1 >> (3 * (deep1 - 1))) & 7;
                        iCopy = (zeroylocations1 >> (3 * (deep1 - 1))) & 7;
                    }else if (deep < 64){
                        unsigned long long deep2 = deep - 42;
                        jCopy = (zeroxlocations2 >> (3 * (deep2 - 1))) & 7;
                        iCopy = (zeroylocations2 >> (3 * (deep2 - 1))) & 7;
                    }

                    deep -= 1;

                }
                    

            }

        }


        

    }

    //j : 7
    for (int i = 0; i < n; i++){

        int j = 7;

        int digit = (k >> (j + i * n)) & 1;

        if(digit == 0){
                        
            unsigned long long deep = 0;

            unsigned long long zeroxlocations0 = 0;
            unsigned long long zeroxlocations1 = 0;
            unsigned long long zeroxlocations2 = 0;
            unsigned long long zeroxlocations3 = 0;

            unsigned long long zeroylocations0 = 0;
            unsigned long long zeroylocations1 = 0;
            unsigned long long zeroylocations2 = 0;
            unsigned long long zeroylocations3 = 0;

            unsigned long long jCopy = j;
            unsigned long long iCopy = i;

            k += ((unsigned long long)1) << (jCopy + iCopy * n);
            
            if (deep < 21){
                zeroxlocations0 += jCopy << (3 * (deep));
                zeroylocations0 += iCopy << (3 * (deep));
            }else if (deep < 42){
                unsigned long long deep1 = deep - 21; 
                zeroxlocations1 += jCopy << (3 * (deep1));
                zeroylocations1 += iCopy << (3 * (deep1));
            }else if (deep < 63){
                unsigned long long deep2 = deep - 42; 
                zeroxlocations2 += jCopy << (3 * (deep2));
                zeroylocations2 += iCopy << (3 * (deep2));
            }else{
                unsigned long long deep3 = deep - 63; 
                zeroxlocations3 += jCopy << (3 * (deep3));
                zeroylocations3 += iCopy << (3 * (deep3));                    
            }


            while (1){
                

                int done = 0;

                if(iCopy >= 1){

                    digit = (k >> (jCopy  + (iCopy - 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }
                
                if (done == 0 && (jCopy + 1) < n){

                    digit = (k >> ((jCopy + 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && (iCopy + 1) < n){

                    digit = (k >> (jCopy  + (iCopy + 1) * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        iCopy += 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if (done == 0 && jCopy >= 1){

                    digit = (k >> ((jCopy - 1)  + iCopy * n)) & 1;

                    if (0 == digit){
                        deep += 1;
                        done = 1;

                        jCopy -= 1;

                        if (deep < 21){
                            zeroxlocations0 += jCopy << (3 * (deep));
                            zeroylocations0 += iCopy << (3 * (deep));
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 += jCopy << (3 * (deep1));
                            zeroylocations1 += iCopy << (3 * (deep1));
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42; 
                            zeroxlocations2 += jCopy << (3 * (deep2));
                            zeroylocations2 += iCopy << (3 * (deep2));
                        }else{
                            unsigned long long deep3 = deep - 63; 
                            zeroxlocations3 += jCopy << (3 * (deep3));
                            zeroylocations3 += iCopy << (3 * (deep3));                    
                        }

                        k += ((unsigned long long)1) << (jCopy + iCopy * n);

                    }
                }

                if(done == 0){
                    if(deep == 0){
                        break;
                    }

                    if (deep < 21){
                        zeroxlocations0 -= ((zeroxlocations0 >> (3 * deep)) & 7) << (3 * deep);
                        zeroylocations0 -= ((zeroylocations0 >> (3 * deep)) & 7) << (3 * deep);
                    }else if (deep < 42){
                        unsigned long long deep1 = deep - 21; 
                        zeroxlocations1 -= ((zeroxlocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                        zeroylocations1 -= ((zeroylocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                    }else if (deep < 63){
                        unsigned long long deep2 = deep - 42;
                        zeroxlocations2 -= ((zeroxlocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                        zeroylocations2 -= ((zeroylocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                    }else{
                        unsigned long long deep3 = deep - 63;
                        zeroxlocations3 -= ((zeroxlocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                        zeroylocations3 -= ((zeroylocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                    }


                    if (deep < 22){
                        jCopy = (zeroxlocations0 >> (3 * (deep - 1))) & 7;
                        iCopy = (zeroylocations0 >> (3 * (deep - 1))) & 7;
                    }else if (deep < 43){
                        unsigned long long deep1 = deep - 21; 
                        jCopy = (zeroxlocations1 >> (3 * (deep1 - 1))) & 7;
                        iCopy = (zeroylocations1 >> (3 * (deep1 - 1))) & 7;
                    }else if (deep < 64){
                        unsigned long long deep2 = deep - 42;
                        jCopy = (zeroxlocations2 >> (3 * (deep2 - 1))) & 7;
                        iCopy = (zeroylocations2 >> (3 * (deep2 - 1))) & 7;
                    }

                    deep -= 1;

                }
                    

            }

        }


        

    }


    //finall

    for (int i = 0; i < n; i++){
        
        for (int j = 0; j < n; j++){

            int digit = (k >> (j + i * n)) & 1;

            if(digit == 0){

                areaCount += 1;
                            
                unsigned long long deep = 0;

                unsigned long long zeroxlocations0 = 0;
                unsigned long long zeroxlocations1 = 0;
                unsigned long long zeroxlocations2 = 0;
                unsigned long long zeroxlocations3 = 0;

                unsigned long long zeroylocations0 = 0;
                unsigned long long zeroylocations1 = 0;
                unsigned long long zeroylocations2 = 0;
                unsigned long long zeroylocations3 = 0;

                unsigned long long jCopy = j;
                unsigned long long iCopy = i;

                k += ((unsigned long long)1) << (jCopy + iCopy * n);
                
                if (deep < 21){
                    zeroxlocations0 += jCopy << (3 * (deep));
                    zeroylocations0 += iCopy << (3 * (deep));
                }else if (deep < 42){
                    unsigned long long deep1 = deep - 21; 
                    zeroxlocations1 += jCopy << (3 * (deep1));
                    zeroylocations1 += iCopy << (3 * (deep1));
                }else if (deep < 63){
                    unsigned long long deep2 = deep - 42; 
                    zeroxlocations2 += jCopy << (3 * (deep2));
                    zeroylocations2 += iCopy << (3 * (deep2));
                }else{
                    unsigned long long deep3 = deep - 63; 
                    zeroxlocations3 += jCopy << (3 * (deep3));
                    zeroylocations3 += iCopy << (3 * (deep3));                    
                }


                while (1){
                    

                    int done = 0;

                    if(iCopy  >= 1){

                        digit = (k >> (jCopy  + (iCopy - 1) * n)) & 1;

                        if (0 == digit){
                            deep += 1;
                            done = 1;

                            iCopy -= 1;

                            if (deep < 21){
                                zeroxlocations0 += jCopy << (3 * (deep));
                                zeroylocations0 += iCopy << (3 * (deep));
                            }else if (deep < 42){
                                unsigned long long deep1 = deep - 21; 
                                zeroxlocations1 += jCopy << (3 * (deep1));
                                zeroylocations1 += iCopy << (3 * (deep1));
                            }else if (deep < 63){
                                unsigned long long deep2 = deep - 42; 
                                zeroxlocations2 += jCopy << (3 * (deep2));
                                zeroylocations2 += iCopy << (3 * (deep2));
                            }else{
                                unsigned long long deep3 = deep - 63; 
                                zeroxlocations3 += jCopy << (3 * (deep3));
                                zeroylocations3 += iCopy << (3 * (deep3));                    
                            }

                            k += ((unsigned long long)1) << (jCopy + iCopy * n);

                        }
                    }
                    
                    if (done == 0 && (jCopy + 1) < n){

                        digit = (k >> ((jCopy + 1)  + iCopy * n)) & 1;

                        if (0 == digit){
                            deep += 1;
                            done = 1;

                            jCopy += 1;

                            if (deep < 21){
                                zeroxlocations0 += jCopy << (3 * (deep));
                                zeroylocations0 += iCopy << (3 * (deep));
                            }else if (deep < 42){
                                unsigned long long deep1 = deep - 21; 
                                zeroxlocations1 += jCopy << (3 * (deep1));
                                zeroylocations1 += iCopy << (3 * (deep1));
                            }else if (deep < 63){
                                unsigned long long deep2 = deep - 42; 
                                zeroxlocations2 += jCopy << (3 * (deep2));
                                zeroylocations2 += iCopy << (3 * (deep2));
                            }else{
                                unsigned long long deep3 = deep - 63; 
                                zeroxlocations3 += jCopy << (3 * (deep3));
                                zeroylocations3 += iCopy << (3 * (deep3));                    
                            }

                            k += ((unsigned long long)1) << (jCopy + iCopy * n);

                        }
                    }

                    if (done == 0 && (iCopy + 1) < n){

                        digit = (k >> (jCopy  + (iCopy + 1) * n)) & 1;

                        if (0 == digit){
                            deep += 1;
                            done = 1;

                            iCopy += 1;

                            if (deep < 21){
                                zeroxlocations0 += jCopy << (3 * (deep));
                                zeroylocations0 += iCopy << (3 * (deep));
                            }else if (deep < 42){
                                unsigned long long deep1 = deep - 21; 
                                zeroxlocations1 += jCopy << (3 * (deep1));
                                zeroylocations1 += iCopy << (3 * (deep1));
                            }else if (deep < 63){
                                unsigned long long deep2 = deep - 42; 
                                zeroxlocations2 += jCopy << (3 * (deep2));
                                zeroylocations2 += iCopy << (3 * (deep2));
                            }else{
                                unsigned long long deep3 = deep - 63; 
                                zeroxlocations3 += jCopy << (3 * (deep3));
                                zeroylocations3 += iCopy << (3 * (deep3));                    
                            }

                            k += ((unsigned long long)1) << (jCopy + iCopy * n);

                        }
                    }

                    if (done == 0 && jCopy >= 1){

                        digit = (k >> ((jCopy - 1)  + iCopy * n)) & 1;

                        if (0 == digit){
                            deep += 1;
                            done = 1;

                            jCopy -= 1;

                            if (deep < 21){
                                zeroxlocations0 += jCopy << (3 * (deep));
                                zeroylocations0 += iCopy << (3 * (deep));
                            }else if (deep < 42){
                                unsigned long long deep1 = deep - 21; 
                                zeroxlocations1 += jCopy << (3 * (deep1));
                                zeroylocations1 += iCopy << (3 * (deep1));
                            }else if (deep < 63){
                                unsigned long long deep2 = deep - 42; 
                                zeroxlocations2 += jCopy << (3 * (deep2));
                                zeroylocations2 += iCopy << (3 * (deep2));
                            }else{
                                unsigned long long deep3 = deep - 63; 
                                zeroxlocations3 += jCopy << (3 * (deep3));
                                zeroylocations3 += iCopy << (3 * (deep3));                    
                            }

                            k += ((unsigned long long)1) << (jCopy + iCopy * n);

                        }
                    }

                    if(done == 0){
                        if(deep == 0){
                            break;
                        }

                        if (deep < 21){
                            zeroxlocations0 -= ((zeroxlocations0 >> (3 * deep)) & 7) << (3 * deep);
                            zeroylocations0 -= ((zeroylocations0 >> (3 * deep)) & 7) << (3 * deep);
                        }else if (deep < 42){
                            unsigned long long deep1 = deep - 21; 
                            zeroxlocations1 -= ((zeroxlocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                            zeroylocations1 -= ((zeroylocations1 >> (3 * deep1)) & 7) << (3 * deep1);
                        }else if (deep < 63){
                            unsigned long long deep2 = deep - 42;
                            zeroxlocations2 -= ((zeroxlocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                            zeroylocations2 -= ((zeroylocations2 >> (3 * deep2)) & 7) << (3 * deep2);
                        }else{
                            unsigned long long deep3 = deep - 63;
                            zeroxlocations3 -= ((zeroxlocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                            zeroylocations3 -= ((zeroylocations3 >> (3 * deep3)) & 7) << (3 * deep3);
                        }


                        if (deep < 22){
                            jCopy = (zeroxlocations0 >> (3 * (deep - 1))) & 7;
                            iCopy = (zeroylocations0 >> (3 * (deep - 1))) & 7;
                        }else if (deep < 43){
                            unsigned long long deep1 = deep - 21; 
                            jCopy = (zeroxlocations1 >> (3 * (deep1 - 1))) & 7;
                            iCopy = (zeroylocations1 >> (3 * (deep1 - 1))) & 7;
                        }else if (deep < 64){
                            unsigned long long deep2 = deep - 42;
                            jCopy = (zeroxlocations2 >> (3 * (deep2 - 1))) & 7;
                            iCopy = (zeroylocations2 >> (3 * (deep2 - 1))) & 7;
                        }

                        deep -= 1;

                    }
                        

                }

            }


            

        }
    }
    


    printf("%d", areaCount);

    return 0;
}