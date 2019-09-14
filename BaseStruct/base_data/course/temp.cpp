/*************************************************************************
	> File Name: temp.cpp
	> Author: 
	> Mail: 
	> Created Time: 日  8/18 10:58:17 2019
 ************************************************************************/

#include <iostream>
using namespace std;

int find(char *arm, char *model, int *next) {
    for (int i = 0, match = -1; arm[i]; ++i) {
        while (match >= 0 && model[match + 1] != arm[i]) {
            match = next[match];
        }
        if (model[match + 1] == arm[i]) match++;
        if (match == strlen(model) - 1) return i - match;
    }
    return -1;
}

void get_next(char *model, int *next) {
    next[0] = -1;
    for (int i = 1, match = -1; model[i]; ++i) {
        while (match >= 0 && model[match + 1] != model[i]) {
            match = next[match];
        }
        if (model[match + 1] == model[i]) match++;
        next[i] = match;
    }
    return ;
}

int main() {
    char arm[10000], model[10000];
    cin >> arm;
    cin >> model;
    int *next = (int *)calloc(sizeof(int), strlen(model) + 1);
    get_next(model, next);
    int ans = find(arm, model, next);
    if (ans != -1){
        cout << ans << endl;
    } else {
        cout << "NO!" << endl;
    }
    return 0;
}
