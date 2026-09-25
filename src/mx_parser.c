#include "pathfinder.h"

static void mx_stct_entr(t_pars *stct, char **str);
static void mx_add_to_arr(t_pars *stct, char *temp);
static void mx_ivalid_number_of_island(t_pars *stct);
static void mx_write_to_matrix(t_pars *stct, char **temp);

void mx_parser(char *argv[], t_pars *stct) {
    char *file = mx_file_to_str(argv[1]);
    char **str = mx_strsplit(file, '\n');

    line1_is_not_valid(str[0]);
    stct->count_island = mx_atoi(str[0]);
    if (stct->count_island == 0) {
        mx_printerr(INVAlID_NUMBER_ISLAND);
        exit(1);
    }
    mx_create_matrix_dist(stct);

    stct->arr_pars = malloc((stct->count_island + 1) * sizeof(char*));
    stct->arr_count = 0;
    stct->count_bridges = 0;
    stct->total_distance = 0;
    mx_stct_entr(stct, str);
    if (stct->arr_count != stct->count_island) {
        mx_printerr(INVAlID_NUMBER_ISLAND);
        mx_strdel(&file);
        mx_del_strarr(&str);
        mx_del_strarr(&stct->arr_pars);
        exit(1);
    }
    mx_create_matrix_floyd(stct);
    duplicate_bridges(str, stct); // 0 leaks
    mx_strdel(&file);
    mx_del_strarr(&str);
}

static void mx_stct_entr(t_pars *stct, char **str) {
    char **temp;

    stct->arr_count = 0;
    for (int i = 0; i < stct->count_island + 1; i++)
        stct->arr_pars[i] = NULL;
    for (int j = 1; str[j]; j++) {
        temp = mx_pars_str(str[j], j);
        mx_add_to_arr(stct, temp[0]);
        mx_add_to_arr(stct, temp[1]);
        mx_write_to_matrix(stct, temp);
        mx_del_strarr(&temp);
    }
}

static void mx_add_to_arr(t_pars *stct, char *temp) {
    int sup = 0;

    for (int j = 0; stct->arr_pars[j] && j < stct->arr_count; j++) {
        if (mx_strcmp(stct->arr_pars[j], temp) == 0)
            sup = -1;
    }
    if (sup == 0) {
        mx_ivalid_number_of_island(stct);
        stct->arr_pars[stct->arr_count] = mx_strdup(temp);
        stct->arr_count += 1;
    }
}

static void mx_ivalid_number_of_island(t_pars *stct) {
    if (stct->arr_count >= stct->count_island) {
        mx_printerr(INVAlID_NUMBER_ISLAND);
        exit(1);
    }
}

static void mx_write_to_matrix(t_pars *stct, char **temp) {
    int dist = mx_atoi(temp[2]);
    int count = stct->count_island;

    stct->total_distance += dist;
    if (stct->total_distance >= INT_MAX) {
        mx_printerr(MAX_LENGTHS);
        exit(1);
    }
    stct->matrix_dist[mx_get_index(stct, temp[0])][mx_get_index(stct, temp[1])] = dist;
    stct->matrix_dist[mx_get_index(stct, temp[1])][mx_get_index(stct, temp[0])] = dist;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if ((i != j) && (stct->matrix_dist[i][j] == 0))
                stct->matrix_dist[i][j] = INT_MAX;
        }
    }
}
