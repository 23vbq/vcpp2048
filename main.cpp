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

const char *colors[] = {"[93m"};

bool moveHandler(char input);
bool moveField(int i, int j, short direction);
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
		system("cls");
		moveHandler(input);
		spawnNew();
		printf("Score: %i\n", score);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (tab[i][j] != 0) printf("|%4i|", tab[i][j]);
				else printf("|%4c|", ' ');
			}
			printf("\n");
		}
		Sleep(250);
		do {
			input = getch();
		} while (!(input == 3 || input < 0));
		if (input < 0) input = getch();
		cin.clear();
		//   cin.ignore(INT_MAX);
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
		for (int p = 0; p < index; p++) {
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					moveField(i, j, 0);
				}
			}
		}
		return true;
	}
	// Left
	if (input == 75) {
		int index = indexOfLatest(1);
		for (int p = 0; p < index; p++) {
			for (int j = 1; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					moveField(i, j, 1);
				}
			}
		}
		return true;
	}
	// Right
	if (input == 77) {
		int index = indexOfLatest(2);
		for (int p = 0; p < index; p++) {
			for (int j = 2; j >= 0; j--) {
				for (int i = 0; i < 4; i++) {
					moveField(i, j, 2);
				}
			}
		}
		return true;
	}
	// Down
	if (input == 80) {
		int index = indexOfLatest(3);
		for (int p = 0; p < index; p++) {
			for (int i = 2; i >= 0; i--) {
				for (int j = 0; j < 4; j++) {
					moveField(i, j, 3);
				}
			}
		}
		return true;
	}
	// Nie ruszo klockiem
	return false;
}
bool moveField(int i, int j, short direction) {
	/*int x = (direction == 0 || direction == 3 ? i : j);
	int y = (direction == 0 || direction == 3 ? j : i);*/
	int x = i;
	int y = j;
	int px = x - (direction == 0 ? 1 : (direction == 3 ? -1 : 0));
	int py = y - (direction == 1 ? 1 : (direction == 2 ? -1 : 0));
	if (tab[px][py] == tab[x][y]) {
		tab[px][py] *= 2;
		tab[x][y] = 0;
		addScore(tab[px][py]);
	} else if (tab[px][py] == 0) {
		tab[px][py] = tab[x][y];
		tab[x][y] = 0;
	} else
		return false;
	return true;
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
void addScore(short add) {
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
