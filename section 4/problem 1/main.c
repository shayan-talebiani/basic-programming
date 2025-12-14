#include <stdio.h>


void set_picture(int m, int n, int picture[m][n]);
void set_cv_layer(int k, int p, int picture[k][p]);


void set_output_padding(int m, int n, int picture[m][n],
                        int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding], 
                        int padding);

void set_output_cv(int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding],
                int m_output_cv, int n_output_cv, int output_cv[m_output_cv][n_output_cv],
                int k, int p, int cv_layer[k][p], int stride);


void print_output(int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding]);


int main(){

    int m, n;
    scanf("%d %d", &m, &n);
    
    int picture[m][n];
    set_picture(m, n, picture);

    int k, p;
    scanf("%d %d", &k, &p);
    
    int cv_layer[k][p];
    set_cv_layer(k, p, cv_layer);

    int padding, stride;
    scanf("%d", &padding);
    scanf("%d", &stride);    


    //set up output padding 
    int m_output_padding = m + 2 * padding;
    int n_output_padding = n + 2 * padding;
    
    int output_padding[m_output_padding][n_output_padding];

    set_output_padding(m, n, picture, m_output_padding, n_output_padding, output_padding, padding);

    //set up output cv
    int m_output_cv = 1 + (m_output_padding - k) / stride;
    int n_output_cv = 1 + (n_output_padding - p) / stride;
    
    int output_cv[m_output_cv][n_output_cv];
    
    set_output_cv(m_output_padding, n_output_padding, output_padding, m_output_cv, n_output_cv, output_cv, k, p, cv_layer, stride);


    print_output(m_output_cv, n_output_cv, output_cv);


    return 0;
}


void set_picture(int m, int n, int picture[m][n]){
    
    for (int i = 0; i < m; i++){

        for (int j = 0; j < n; j++){

            int input;
            scanf("%d", &input);

            picture[i][j] = input;

        }

    }
    
}

void set_cv_layer(int k, int p, int picture[k][p]){
    
    for (int i = 0; i < k; i++){

        for (int j = 0; j < p; j++){

            int input;
            scanf("%d", &input);

            picture[i][j] = input;

        }

    }

}


void set_output_padding(int m, int n, int picture[m][n], 
                        int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding], 
                        int padding){

    for (int i = 0; i < m_output_padding; i++){

        for (int j = 0; j < n_output_padding; j++){

            if (i > padding - 1 && j > padding - 1 && i < m_output_padding - padding && j < n_output_padding - padding){

                output_padding[i][j] = picture[i - padding][j - padding];
            
            }else{
                
                output_padding[i][j] = 0;
            
            }

        }

    }

}

void set_output_cv(int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding],
                int m_output_cv, int n_output_cv, int output_cv[m_output_cv][n_output_cv],
                int k, int p, int cv_layer[k][p], int stride){

    for (int i = 0; i < m_output_cv; i++){

        for (int j = 0; j < n_output_cv; j++){

            int i_output_padding = i * stride;
            int j_output_padding = j * stride;
            
            output_cv[i][j] = 0;

            for (int i_cv = 0; i_cv < k; i_cv++){

                for (int j_cv = 0; j_cv < p; j_cv++){

                    output_cv[i][j] += output_padding[i_output_padding + i_cv][j_output_padding + j_cv] * cv_layer[i_cv][j_cv];

                }   

            }
            

        }

    }



}


void print_output(int m_output_padding, int n_output_padding, int output_padding[m_output_padding][n_output_padding]){

    for (int i = 0; i < m_output_padding; i++){

        for (int j = 0; j < n_output_padding; j++){

            printf("%d ", output_padding[i][j]);

        }

        printf("\n");

    }

}
