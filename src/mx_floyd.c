//#include "../inc/pathfinder.h"
#include "pathfinder.h"

void mx_floyd(t_pars *stct) {
    int temp = stct->count_island;
    int new_dist;

    for (int k = 0; k < temp; k++) {
        for (int i = 0; i < temp; i++) {
            for (int j = 0; j < temp; j++) {
                if (stct->matrix_dist[i][k] == INT_MAX
                    || stct->matrix_dist[k][j] == INT_MAX)
                    continue;
                new_dist = stct->matrix_dist[i][k] + stct->matrix_dist[k][j];
                if (new_dist < stct->matrix_dist[i][j])
                    stct->matrix_dist[i][j] = new_dist;
            }
        }
    }
}
