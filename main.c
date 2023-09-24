#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NDEBUG 
#include <assert.h>

#define ARRAY_SIZE 200 //array size with bound for user

typedef struct matrix {
    int size; 
    char *arr_p;
} matrix_t;

typedef struct sentence {
    int lenght; 
    char arr[ARRAY_SIZE + 1];
} sentence_t;

typedef struct point {
    int x;
    int y;
} point_t;

typedef enum direction {R, D, L, U} direction_t;

/**
Function removing spaces from sentence
*/
void remove_spaces(char* sentence_p) {
    char* d = sentence_p;
    do {
        while(*d == ' '){
            ++d;
        }
    } while((*sentence_p++ = *d++));
}

/**
Function taking sentence to code from user 
*/ 
void user_input(sentence_t* sentence_p){
    while (1){
        printf("Please enter sentence within %d characters: ", ARRAY_SIZE);
        fgets(sentence_p->arr, ARRAY_SIZE + 1, stdin);
        
        //formating input
        sentence_p->arr[strcspn(sentence_p->arr, "\n")] = '\0';
        remove_spaces(sentence_p->arr);

        sentence_p->lenght = strlen(sentence_p->arr);

        if (sentence_p->lenght != 0){
            break;
        }
        else{
            printf("You didn't enter any valid text!!!\n");
        }
    }
    assert(sentence_p->lenght != 0);
}

/**
Function moving point in curent direction
*/
void move_point(point_t *point_p, direction_t dir){
    point_t u_vect[4] = {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1},
    }; // unit vector with direction

    //move of point in direction
    point_p->x = point_p->x + u_vect[dir].x;
    point_p->y = point_p->y + u_vect[dir].y;
}

/**
Function which allocate array in matrix to required size
*/
void make_matrix(sentence_t *sentence_p, matrix_t *matrix_p){
    matrix_t matrix_temp_p;

    //taking size from sentence
    matrix_temp_p.size =(int)ceil(sqrt(sentence_p->lenght));
    //allocating array of given size
    matrix_temp_p.arr_p = malloc(((int)pow(matrix_temp_p.size,2))*sizeof(char));

    if (matrix_temp_p.arr_p == NULL){
        perror("Matrix array failed!!!");
    }

    *matrix_p = matrix_temp_p;
}

/**
Function which deallocate array from matrix 
*/
void free_matrix(matrix_t *matrix_p){
    free(matrix_p->arr_p);
    matrix_p->arr_p = NULL;
}

/**
Function printing array from matrix with coded text
*/
void fill_matrix(matrix_t* matrix_p, sentence_t* sentence_p){
    direction_t dir = R; //default direction
    point_t point = {(int)floor((matrix_p->size - 1)/2), (int)floor((matrix_p->size - 1)/2)}; //strating point in around center 
    int step_size = 1; //default stepsize

    for (int i = 0; i < (int)pow(matrix_p->size,2);){ // until and of matrix array

        for (int ii = 0; ii < step_size; ii++){ // inserting chars in single direction

            if (i < sentence_p->lenght){ //if index is in range of sentence insert char 
                matrix_p->arr_p[(point.x) + (point.y)*matrix_p->size] = sentence_p->arr[i];
                move_point(&point, dir);
            }
            else{ // out of range print '*'
                matrix_p->arr_p[(point.x) + (point.y)*matrix_p->size] = '*';
                move_point(&point, dir);
            }

            i++;
        }

        if (dir == U || dir == D) step_size++; //increment stepsize afer half of circle 

        dir = (dir + 1) % 4; // change direction
    }
}

/**
Function printing array from matrix with coded text
*/
void print_matrix(matrix_t* matrix){
    printf("\n");

    for (int i = 0; i < (int)pow(matrix->size,2);){ 
        for (int ii = 0; ii < matrix->size; ii++){
            printf("%c  ", matrix->arr_p[i]);
            i++;
        }
        printf("\n");
    }
    printf("\n");
}


int main(void){
    sentence_t sentence;
    matrix_t matrix;

    user_input(&sentence);

    make_matrix(&sentence, &matrix);
    fill_matrix(&matrix, &sentence);
    print_matrix(&matrix);

    free_matrix(&matrix);

    getchar();

    return 0;
}