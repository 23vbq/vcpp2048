#include <conio.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;

/*
 * -32 72	- Up		- 0
 * -32 75	- Left		- 1
 * -32 77	- Right 	- 2
 * -32 80	- Down		- 3
 */
short tab[4][4] = {0};
int score = 0;

bool moveHandler(char input);
bool isAvalible();
int indexOfLatest(short direction);
void spawnNew();
void addScore(short add);

int main() {
    srand(time(NULL));
    char input;
    system("cls");
    // tab[2][2] = 2;
    // tab[2][1] = 2;
    // tab[2][0] = 4;
    while (input != 3) {
        if (!isAvalible()) break;
        moveHandler(input);
        spawnNew();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if(tab[i][j] != 0) printf("|%4i|", tab[i][j]);
                else printf("|%4c|", ' ');
            }
            printf("\n");
        }
        Sleep(250);
        do {
            input = getch();
        } while (!(input == 3 || input < 0));
        if (input < 0) input = getch();
        system("cls");
    }
    if (!isAvalible()) printf("\nPrzegrales\n");
    return 0;
}

/*
 * Handle input for move
 *
 * @return true if correct input
 */
bool moveHandler(char input) {
    // Up
    if (input == 72) {
        int index = indexOfLatest(0);
        for(int p = 0; p < index; p++) {
            for (int i = 1; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (tab[i - 1][j] == tab[i][j]) {
                        tab[i - 1][j] *= 2;
                        tab[i][j] = 0;
                    } else if (tab[i - 1][j] == 0) {
                        tab[i - 1][j] = tab[i][j];
                        tab[i][j] = 0;
                    } else {
                        continue;
                    }
                }
            }
        }
        return true;
    }
    // Left
    if (input == 75) {
        int index = indexOfLatest(1);
        for(int p = 0; p < index; p++) {
            for (int j = 1; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    if (tab[i][j - 1] == tab[i][j]) {
                        tab[i][j - 1] *= 2;
                        tab[i][j] = 0;
                    } else if (tab[i][j - 1] == 0) {
                        tab[i][j - 1] = tab[i][j];
                        tab[i][j] = 0;
                    } else {
                        continue;
                    }
                }
            }
        }
        return true;
    }
    // Right
    if (input == 77) {
        int index = indexOfLatest(2);
        for(int p = 0; p < index; p++) {
            for (int j = 2; j >= 0; j--) {
                for (int i = 0; i < 4; i++) {
                    if (tab[i][j + 1] == tab[i][j]) {
                        tab[i][j + 1] *= 2;
                        tab[i][j] = 0;
                    } else if (tab[i][j + 1] == 0) {
                        tab[i][j + 1] = tab[i][j];
                        tab[i][j] = 0;
                    } else {
                        continue;
                    }
                }
            }
        }
        return true;
    }
    // Down
    if (input == 80) {
        int index = indexOfLatest(3);
        for(int p = 0; p < index; p++) {
            for (int i = 2; i >= 0; i--) {
                for (int j = 0; j < 4; j++) {
                    if (tab[i + 1][j] == tab[i][j]) {
                        tab[i + 1][j] *= 2;
                        tab[i][j] = 0;
                    } else if (tab[i + 1][j] == 0) {
                        tab[i + 1][j] = tab[i][j];
                        tab[i][j] = 0;
                    } else {
                        continue;
                    }
                }
            }
        }
        return true;
    }

    // Nie ruszo klockiem
    return false;
}
bool isAvalible() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tab[i][j] == 0) return true;
        }
    }
    return false;
}
int indexOfLatest(short direction) {
    int index = -1;

    // Up
    if (direction == 0) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tab[i][j] != 0) {
                    index = i;
                    break;
                }
            }
        }
    }
    // Left
    else if (direction == 1) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                if (tab[i][j] != 0) {
                    index = j;
                    break;
                }
            }
        }
    }
    // Right
    else if (direction == 2) {
        for (int j = 3; j >= 0; j--) {
            for (int i = 0; i < 4; i++) {
                if (tab[i][j] != 0) {
                    index = 3 - j;
                    break;
                }
            }
        }
    }
    // Down
    else if (direction == 3) {
        for (int i = 3; i >= 0; i--) {
            for (int j = 0; j < 4; j++) {
                if (tab[i][j] != 0) {
                    index = 3 - i;
                    break;
                }
            }
        }
    }
    return index;
}
void addScore(short add){
    score += add;
}
void spawnNew() {
    int x, y;
    do {
        x = rand() % 4;
        y = rand() % 4;
    } while (tab[x][y] != 0);
    tab[x][y] = 2;
}
