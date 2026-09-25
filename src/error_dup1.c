#include "pathfinder.h"

static void for_err(t_pars *stct, int i);

void error_dup1(t_pars *stct) {
    for (int i = 0; i < stct->count_bridges; i++) {
        for_err(stct, i * 2);
    }
}

static void for_err(t_pars *stct, int i) {
    for (int k = i + 2; k < stct->count_bridges * 2; k += 2) {
        if ((mx_strcmp(stct->arr_bridges[i], stct->arr_bridges[k]) == 0) && 
            (mx_strcmp(stct->arr_bridges[i + 1], stct ->arr_bridges[k + 1]) == 0)) {
            mx_printerr(DUPLICATE);
            mx_del_strarr(&stct->arr_pars1);
            mx_del_strarr(&stct->arr_pars);
            exit(1);
        }
        if ((mx_strcmp(stct->arr_bridges[i], stct->arr_bridges[k + 1]) == 0) && 
            (mx_strcmp(stct->arr_bridges[i + 1], stct ->arr_bridges[k]) == 0)) {
            mx_printerr(DUPLICATE);
            mx_del_strarr(&stct->arr_pars1);
            mx_del_strarr(&stct->arr_pars);
            exit(1);
       }
    }
}
