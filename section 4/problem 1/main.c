#include <stdio.h>


void set_picture(int m, int n, int picture[m][n]);
void set_cv_layer(int k, int p, int picture[k][p]);



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



    int m_output_padding = m + 2 * padding;
    int n_output_padding = n + 2 * padding;
    
    int m_output_cv = 1 + (m_output_cv - k) / stride;
    int n_output_cv = 1 + (n_output_cv - p) / stride;
    
    int output_cv[m_output_cv][n_output_cv];






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
