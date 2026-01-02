#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;     
    struct Node *right;
} Node;

Node* build_structure(int n);
void build_structure_tree(Node *answer, int l, int r);

int main(){

    int n;
    scanf("%d", &n);

    printf("%p", build_structure(n));

    return 0;
}


Node* build_structure(int n) {
    // your code

    Node *answer = (Node *)malloc(sizeof(Node));
    build_structure_tree(answer, 1, n);

    return answer;
}

void build_structure_tree(Node *answer, int l, int r){

    if (l == r){
        answer->value = l;
        return;
    }
    
    int v = (r + l) / 2;

    answer->value = v;

    if (l <= v - 1){

        answer->left = (Node *)malloc(sizeof(Node));
        build_structure_tree(answer->left, l, v - 1);

    }

    if (v + 1 <= r){

        answer->right = (Node *)malloc(sizeof(Node));
        build_structure_tree(answer->right, v + 1, r);
    
    }

}
