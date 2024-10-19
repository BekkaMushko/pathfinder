#include "../inc/libmx.h"

static int count(const char *str, const char *sub) {
    const char *temp = mx_strstr(str, sub);
    int count = 0;
    while (temp != NULL && mx_strlen(sub) != 0) {
        temp += mx_strlen(sub);
        temp = mx_strstr(temp, sub);
        ++count;
    }
    return count;
}

static void writing(const char *str, const char *sub, const char *replace, char *res) {
    const char *temp = mx_strstr(str, sub);
    int i = 0;
    const char *c = str;
    while (*c != '\0') {
        if (c == temp) {
            for (const char *cc = replace; *cc != '\0'; ++cc) {
                res[i] = *cc;
                ++i;
            }
            temp += mx_strlen(sub);
            temp = mx_strstr(temp, sub);
            c += mx_strlen(sub);
        }
        else {
            res[i] = *c;
            ++i;
            ++c;
        }
    }
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (sub == NULL || str == NULL || replace == NULL)
        return NULL;
    int n = count(str, sub);
    if (n == 0)
        return mx_strdup(str);
    int size = mx_strlen(str) - mx_strlen(sub) * n + mx_strlen(replace) * n;
    char *res = mx_strnew(size);
    if (res == NULL)
        return NULL;
    writing(str, sub, replace, res);
    return res;
}

