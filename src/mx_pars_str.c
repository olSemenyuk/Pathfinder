#include "pathfinder.h"

static bool check_name(char *str);
static bool check_dist(char *str);
static bool max_dist(char *str);

char **mx_pars_str(char *str, int i) {
    int t = mx_get_char_index(str, '-');
    int k = mx_get_char_index(str, ',');
    int s = mx_strlen(str);
    int countt = mx_count_symbol(str, '-');
    int countk = mx_count_symbol(str, ',');
    char **pr_str = (char**)malloc(4 * sizeof(char*));

    if (t < 0 || k < 0 || t > k || s < 5 || countk > 1 || countt > 1)
        printerr_line(i);
    pr_str[0] = mx_strndup(str, t);
    pr_str[1] = mx_strndup((str + t + 1), (k - t - 1));
    pr_str[2] = mx_strndup((str + k + 1), (s - k));
    pr_str[3] = NULL;
    if (!check_name(pr_str[0]) || !check_name(pr_str[1]) 
        || !check_dist(pr_str[2]) || mx_strcmp(pr_str[0], pr_str[1]) == 0
        || ((mx_strcmp(pr_str[0], pr_str[1]) != 0) && mx_atoi(pr_str[2]) == 0)) {
        mx_del_strarr(&pr_str);
        printerr_line(i);
    }
    if (!max_dist(pr_str[2])) {
        mx_printerr(MAX_LENGTHS);
        exit(1);
    }
    return pr_str;
}

static bool check_name(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!mx_isalpha(str[i]))
            return false;
    }
    if (mx_strlen(str) <= 0)
        return false;
    return true;
}

static bool check_dist(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!mx_isdigit(str[i]))
            return false;
    }
    if(mx_strlen(str) <= 0)
        return false;
    return true;
}

static bool max_dist(char *str) {
    long long dist = 0;

    for (int i = 0; str[i]; i++) {
        if (dist > (INT_MAX - (str[i] - '0')) / 10)
            return false;
        dist = dist * 10 + (str[i] - '0');
    }
    return dist > 0;
}
