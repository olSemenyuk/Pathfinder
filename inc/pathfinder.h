#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "stdbool.h"
#include "limits.h"
#include "malloc/malloc.h"
#include "libmx.h"

#define INVALID_USAGE "usage: ./pathfinder [filename]\n"
#define LINE1_IS_INVALID "error: line 1 is not valid\n"
#define INVALID_NUMBER_ISLANDS "error: invalid number of islands\n"


typedef struct s_pars {
    int count_island;
    char **arr_pars;
    char **arr_pars1;
    int arr_count;
    int count_bridges;
    long long total_distance;
    char **arr_bridges;
    int **matrix_dist;
    int **matrix_floyd;
} t_pars;

typedef struct s_backpath {
    int size;
    int *path;
    int meme;
} t_backpath;
 
#define INVALID_USAGE "usage: ./pathfinder [filename]\n"
#define LINE1_IS_NOT_VALID "error: line 1 is not valid\n"
#define INVAlID_NUMBER_ISLAND "error: invalid number of islands\n"
#define DUPLICATE "error: duplicate bridges\n"
#define MAX_LENGTHS "error: sum of bridges lengths is too big\n"

//errors
void file_does_not_exist(char *argv[]);
void file_is_empty(char *argv[]);
void invalid_usage(int argc);
void line1_is_not_valid(char *str);
void printerr_line(int i);
void duplicate_bridges(char **file, t_pars *stct);
void error_dup1(t_pars *stct);

//parser
void mx_parser(char *argv[], t_pars *stct);
char **mx_pars_str(char *str, int i);
void mx_create_matrix_dist(t_pars *stct);
void mx_create_matrix_floyd(t_pars *stct);
int mx_get_index(t_pars *stct, char *c);

//floyd_warshall_algorithm
void mx_floyd(t_pars *stct);
void mx_find_all_path(t_pars *stct, int first, int last);
void mx_back_path(t_pars *stct, t_backpath *stack);
void mx_output(t_pars *stct, t_backpath *stack);
void mx_int_print(int n);


#endif
