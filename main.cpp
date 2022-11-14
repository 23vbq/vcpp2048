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

bool moveHandler(char input);
bool isAvalible();
int indexOfLatest(short direction);
void spawnNew();

int main() {
    srand(time(NULL));
    char input;
    system("cls");
    while (input != 3) {
        if (!isAvalible()) break;
        moveHandler(input);
        spawnNew();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("|%i|", tab[i][j]);
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

bool moveHandler(char input) {
    // Up
    if (input == 72) {
        int index = indexOfLatest(0);
        while (index != 0) {
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
            index--;
        }
        return true;
    }
    // Left
    if (input == 75) {
        int index = indexOfLatest(1);
        while (index != 0) {
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
            index--;
        }
        return true;
    }
    // Right
    if (input == 77) {
        int index = indexOfLatest(2);
        while (index != 0) {
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
            index--;
        }
        return true;
    }
    // Down
    if (input == 80) {
        int index = indexOfLatest(3);
        while (index != 0) {
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
            index--;
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
                    index = i + 1;
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
                    index = i + 2;
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
                    index = 4 - i;
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
                    index = 4 - i;
                    break;
                }
            }
        }
    }
    return index;
}
void spawnNew() {
    int x, y;
    do {
        x = rand() % 4;
        y = rand() % 4;
    } while (tab[x][y] != 0);
    tab[x][y] = 2;
}
