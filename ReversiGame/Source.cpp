#include "GameSource.h"

#include <stdio.h>


#define N 8
#define M 8

int field[N][M] = {
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 2,	1, 0, 0, 0},

    {0, 0, 0, 1,	2, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0}
};

int originalField[N][M] = {
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 1,	2, 0, 0, 0},

    {0, 0, 0, 2,	1, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 0,	0, 0, 0, 0}
};


int fieldSize = 50;
bool loaded = false;
char filesave[] = "save.txt";

int saveGame() {
    FILE* fin = fopen(filesave, "wt");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fprintf(fin, "%d ", field[i][j]);
        }
        fprintf(fin, "\n");
    }
    fclose(fin);
    return 1;
}

int loadGame() {
    FILE* fin = fopen(filesave, "rt");
    if (fin == NULL) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(fin, "%d", &field[i][j]);
        }
    }
    loaded = true;
    fclose(fin);
    return 1;
}

void DrawField(HDC hdc) {
    if (!loaded) {
        loadGame();
    }
    saveGame();
    HPEN borderPen;
    borderPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, borderPen);

    HBRUSH fieldBrush;
    fieldBrush = CreateSolidBrush(RGB(101, 67, 33));

    HBRUSH playerBrush;
    playerBrush = CreateSolidBrush(RGB(200, 200, 200));

    HBRUSH enemyBrush;
    enemyBrush = CreateSolidBrush(RGB(1, 1, 1));

    int i = 0;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if (field[i][j] == 0) {
                SelectObject(hdc, fieldBrush);
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            else if (field[i][j] == 1) {
                SelectObject(hdc, fieldBrush);
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
                SelectObject(hdc, playerBrush);
                Ellipse(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            else if (field[i][j] == 2) {
                SelectObject(hdc, fieldBrush);
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
                SelectObject(hdc, enemyBrush);
                Ellipse(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            j++;
        }
        i++;
    }
}

#pragma region PlayerMove
bool CheckMoveLeft(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i][j + 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j + 1;
        while (tmpJ < M) {
            if (field[i][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[i][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 1;
                if (field[i][tmpJ + 1] == 1) {
                    return true;
                }
                tmpJ++;
            }
        }
    }
    return false;
}

bool CheckMoveRight(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        while (tmpJ >= 0) {
            if (field[i][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[i][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            while (tmpJ >= 0) {
                field[i][tmpJ] = 1;
                if (field[i][tmpJ - 1] == 1) {
                    return true;
                }
                tmpJ--;
            }
        }
    }
    return false;
}

bool CheckMoveDown(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i - 1][j] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpI = i - 1;
        while (tmpI >= 0) {
            if (field[tmpI][j] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][j] == 0) {
                return false;
            }
            tmpI--;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpI = i;
            while (tmpI >= 0) {
                field[tmpI][j] = 1;
                if (field[tmpI - 1][j] == 1) {
                    return true;
                }
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckMoveUp(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i + 1][j] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpI = i + 1;
        while (tmpI < N) {
            if (field[tmpI][j] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][j] == 0) {
                return false;
            }
            tmpI++;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 1;
                if (field[tmpI + 1][j] == 1) {
                    return true;
                }
                tmpI++;
            }
        }
    }
    return false;
}

bool CheckMoveDiagonalRightUp(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i + 1][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i + 1;
        while (tmpJ >= 0 && tmpI < N) {
            if (field[tmpI][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
            tmpI++;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ >= 0 && tmpI < N) {
                field[tmpI][tmpJ] = 1;
                if (field[tmpI + 1][tmpJ - 1] == 1) {
                    return true;
                }
                tmpJ--;
                tmpI++;
            }
        }
    }
    return false;
}

bool CheckMoveDiagonalRightDown(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i - 1][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i - 1;
        while (tmpJ >= 0 && tmpI >= 0) {
            if (field[tmpI][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
            tmpI--;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ >= 0 && tmpI >= 0) {
                field[tmpI][tmpJ] = 1;
                if (field[tmpI - 1][tmpJ - 1] == 1) {
                    return true;
                }
                tmpJ--;
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckMoveDiagonalLeftDown(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i - 1][j + 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j + 1;
        int tmpI = i - 1;
        while (tmpJ < M && tmpI >= 0) {
            if (field[tmpI][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
            tmpI--;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI >= 0) {
                field[tmpI][tmpJ] = 1;
                if (field[tmpI - 1][tmpJ + 1] == 1) {
                    return true;
                }
                tmpJ++;
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckMoveDiagonalLeftUp(int i, int j, bool wasMovedHere, bool checkHasMove) {
    if (field[i + 1][j + 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j + 1;
        int tmpI = i + 1;
        while (tmpJ < M && tmpI < N) {
            if (field[tmpI][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
            tmpI++;
        }
        if (checkHasMove) {
            return playerOnLine;
        }
        if (playerOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI < N) {
                field[tmpI][tmpJ] = 1;
                if (field[tmpI + 1][tmpJ + 1] == 1) {
                    return true;
                }
                tmpJ++;
                tmpI++;
            }
        }
    }
    return false;
}
#pragma endregion

#pragma region EnemyMoving
bool CheckEnemyMoveLeft(int i, int j, bool wasMovedHere) {
    if (field[i][j - 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j - 1;
        while (tmpJ >= 0) {
            if (field[i][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[i][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
        }
        if (enemyOnLine) {
            tmpJ = j;
            while (tmpJ >= 0) {
                field[i][tmpJ] = 2;

                if (field[i][tmpJ - 1] == 2) {
                    return true;
                }
                tmpJ--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveRight(int i, int j, bool wasMovedHere) {
    if (field[i][j + 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j + 1;
        while (tmpJ < M) {
            if (field[i][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[i][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
        }
        if (enemyOnLine) {
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 2;

                if (field[i][tmpJ + 1] == 2) {
                    return true;
                }
                tmpJ++;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDown(int i, int j, bool wasMovedHere) {
    if (field[i - 1][j] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpI = i - 1;
        while (tmpI >= 0) {
            if (field[tmpI][j] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][j] == 0) {
                return false;
            }
            tmpI--;
        }
        if (enemyOnLine) {
            tmpI = i;
            while (tmpI >= 0) {
                field[tmpI][j] = 2;

                if (field[tmpI - 1][j] == 2) {
                    return true;
                }
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveUp(int i, int j, bool wasMovedHere) {
    if (field[i + 1][j] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpI = i + 1;
        while (tmpI < N) {
            if (field[tmpI][j] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][j] == 0) {
                return false;
            }
            tmpI++;
        }
        if (enemyOnLine) {
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 2;

                if (field[tmpI + 1][j] == 2) {
                    return true;
                }
                tmpI++;
            }
        }
    }
    return false;
}


bool CheckEnemyMoveDiagonalRightUp(int i, int j, bool wasMovedHere) {
    if (field[i + 1][j - 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i + 1;
        while (tmpJ >= 0 && tmpI < N) {
            if (field[tmpI][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
            tmpI++;
        }
        if (enemyOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ >= 0 && tmpI < N) {
                field[tmpI][tmpJ] = 2;

                if (field[tmpI + 1][tmpJ - 1] == 2) {
                    return true;
                }
                tmpJ--;
                tmpI++;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDiagonalRightDown(int i, int j, bool wasMovedHere) {
    if (field[i - 1][j - 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i - 1;
        while (tmpJ >= 0 && tmpI >= 0) {
            if (field[tmpI][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ--;
            tmpI--;
        }
        if (enemyOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ >= 0 && tmpI >= 0) {
                field[tmpI][tmpJ] = 2;

                if (field[tmpI - 1][tmpJ - 1] == 2) {
                    return true;
                }
                tmpJ--;
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDiagonalLeftDown(int i, int j, bool wasMovedHere) {
    if (field[i - 1][j + 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j + 1;
        int tmpI = i - 1;
        while (tmpJ < M && tmpI >= 0) {
            if (field[tmpI][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
            tmpI--;
        }
        if (enemyOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI >= 0) {
                field[tmpI][tmpJ] = 2;
                if (field[tmpI - 1][tmpJ + 1] == 2) {
                    return true;
                }
                tmpJ++;
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDiagonalLeftUp(int i, int j, bool wasMovedHere) {
    if (field[i + 1][j + 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j + 1;
        int tmpI = i + 1;
        while (tmpJ < M && tmpI < N) {
            if (field[tmpI][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            else if (field[tmpI][tmpJ] == 0) {
                return false;
            }
            tmpJ++;
            tmpI++;
        }
        if (enemyOnLine) {
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI < N) {
                field[tmpI][tmpJ] = 2;
                if (field[tmpI + 1][tmpJ + 1] == 2) {
                    return true;
                }
                tmpJ++;
                tmpI++;
            }
        }
    }
    return false;
}
#pragma endregion

void EnemyMove() {
    int i = 0;
    bool moved = false;
    while (i < N) {
        int j = 0;
        while (j < M) {
            bool movedDown = CheckEnemyMoveDown(i, j, false);
            moved = movedDown || moved;
            bool movedUp = CheckEnemyMoveUp(i, j, moved);
            moved = movedUp || moved;
            bool movedRight = CheckEnemyMoveRight(i, j, moved);
            moved = movedRight || moved;
            bool movedLeft = CheckEnemyMoveLeft(i, j, moved);
            moved = movedLeft || moved;
            bool movedRightUp = CheckEnemyMoveDiagonalRightUp(i, j, moved);
            moved = moved || movedRightUp;
            bool movedRightDown = CheckEnemyMoveDiagonalRightDown(i, j, moved);
            moved = moved || movedRightDown;
            bool movedLeftDown = CheckEnemyMoveDiagonalLeftDown(i, j, moved);
            moved = moved || movedLeftDown;
            bool movedLeftUp = CheckEnemyMoveDiagonalLeftUp(i, j, moved);
            moved = moved || movedLeftUp;
            if (moved) {
                break;
            }
            j++;
        }
        if (moved) {
            break;
        }
        i++;
    }
}

bool SelectRectangle(int x, int y) {
    int i = 0;
    bool moved = false;
    bool founded = false;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if ((j + 1) * fieldSize > x && (i + 1) * fieldSize > y) {
                bool movedRight = CheckMoveRight(i, j, false, false);
                moved = moved || movedRight;
                bool movedUp = CheckMoveUp(i, j, moved, false);
                moved = moved || movedUp;
                bool movedLeft = CheckMoveLeft(i, j, moved, false);
                moved = moved || movedLeft;
                bool movedDown = CheckMoveDown(i, j, moved, false);
                moved = moved || movedDown;
                bool movedRightUp = CheckMoveDiagonalRightUp(i, j, moved, false);
                moved = moved || movedRightUp;
                bool movedRightDown = CheckMoveDiagonalRightDown(i, j, moved, false);
                moved = moved || movedRightDown;
                bool movedLeftDown = CheckMoveDiagonalLeftDown(i, j, moved, false);
                moved = moved || movedLeftDown;
                bool movedLeftUp = CheckMoveDiagonalLeftUp(i, j, moved, false);
                moved = moved || movedLeftUp;
                founded = true;
                break;
            }
            j++;
        }
        if (moved) {
            return true;
        }
        else if (founded) {
            return false;
        }
        i++;
    }
    return founded;
}

int CheckEndGame(HDC hdc) {
    int black = 0;
    int white = 0;
    bool hasMove = false;
    bool hasAnyMove;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] == 0) {
                for (int k = 0; k < N; k++) {
                    for (int t = 0; t < M; t++) {
                        bool movedRight = CheckMoveRight(i, j, false, true);
                        hasMove = hasMove || movedRight;
                        bool movedUp = CheckMoveUp(i, j, false, true);
                        hasMove = hasMove || movedUp;
                        bool movedLeft = CheckMoveLeft(i, j, false, true);
                        hasMove = hasMove || movedLeft;
                        bool movedDown = CheckMoveDown(i, j, false, true);
                        hasMove = hasMove || movedDown;
                        bool movedRightUp = CheckMoveDiagonalRightUp(i, j, false, true);
                        hasMove = hasMove || movedRightUp;
                        bool movedRightDown = CheckMoveDiagonalRightDown(i, j, false, true);
                        hasMove = hasMove || movedRightDown;
                        bool movedLeftDown = CheckMoveDiagonalLeftDown(i, j, false, true);
                        hasMove = hasMove || movedLeftDown;
                        bool movedLeftUp = CheckMoveDiagonalLeftUp(i, j, false, true);
                        hasMove = hasMove || movedLeftUp;
                        if (hasMove) {
                            return 1;
                        }
                    }
                }
            }
            else if (field[i][j] == 1) {
                white++;
            }
            else if (field[i][j] == 2) {
                black++;
            }
        }
    }

    if (black > white) {
        TextOutA(hdc, 10, 500, "Фишки черного цвета выиграли", strlen("Фишки черного цвета выиграли"));
    }
    else {
        TextOutA(hdc, 10, 500, "Фишки белого цвета выиграли", strlen("Фишки белого цвета выиграли"));
    }
    return 1;
}





