#pragma once
#include "framework.h"

#define N 8
#define M 8

int field[N][M] = {
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

void DrawField(HDC hdc) {

    HPEN borderPen;
    borderPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, borderPen);

    HBRUSH fieldBrush;
    fieldBrush = CreateSolidBrush(RGB(100, 100, 100));

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
                Rectangle(hdc, fieldSize * i, fieldSize * j, (i + 1) * fieldSize, (j + 1) * fieldSize);
            }
            else if (field[i][j] == 1) {
                SelectObject(hdc, playerBrush);
                Rectangle(hdc, fieldSize * i, fieldSize * j, (i + 1) * fieldSize, (j + 1) * fieldSize);
            }
            else if (field[i][j] == 2) {
                SelectObject(hdc, enemyBrush);
                Rectangle(hdc, fieldSize * i, fieldSize * j, (i + 1) * fieldSize, (j + 1) * fieldSize);
            }
            j++;
        }
        i++;
    }
}

void CheckMoveRight(HDC hdc, int i, int j) {
    if (field[i + 1][j] == 2) {
        bool playerOnLine = false;
        int tmpI = i + 1;
        while (tmpI < N) {
            if (field[tmpI][j] == 1) {
                playerOnLine = true;
                break;
            }
            tmpI++;
        }
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 1;
                Rectangle(hdc, fieldSize * tmpI, fieldSize * j, (tmpI + 1) * fieldSize, (j + 1) * fieldSize);
                if (field[tmpI + 1][j] == 1) {
                    break;
                }
                tmpI++;
            }
        }
        
    }
}

void CheckMoveLeft(HDC hdc, int i, int j) {
    if (field[i - 1][j] == 2) {
        bool playerOnLine = false;

        int tmpI = i - 1;
        while (tmpI > 0) {
            if (field[tmpI][j] == 1) {
                playerOnLine = true;
                break;
            }
            tmpI--;
        }
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpI = i;
            while (tmpI > 0) {
                field[tmpI][j] = 1;
                Rectangle(hdc, fieldSize * tmpI, fieldSize * j, (tmpI + 1) * fieldSize, (j + 1) * fieldSize);
                if (field[tmpI - 1][j] == 1) {
                    break;
                }
                tmpI--;
            }
        }
    }
}

void CheckMoveDown(HDC hdc, int i, int j) {
    if (field[i][j + 1] == 2) {
        bool playerOnLine = false;

        int tmpJ = j + 1;
        while (tmpJ < M) {
            if (field[i][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            tmpJ++;
        }
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 1;
                Rectangle(hdc, fieldSize * i, fieldSize * tmpJ, (i + 1) * fieldSize, (tmpJ + 1) * fieldSize);
                if (field[i][tmpJ+1] == 1) {
                    break;
                }
                tmpJ++;
            }
        }

    }
}

void CheckMoveUp(HDC hdc, int i, int j) {
    if (field[i][j - 1] == 2) {
        bool playerOnLine = false;

        int tmpJ = j - 1;
        while (tmpJ > 0) {
            if (field[i][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            tmpJ--;
        }
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            while (tmpJ > 0) {
                field[i][tmpJ] = 1;
                Rectangle(hdc, fieldSize * i, fieldSize * tmpJ, (i + 1) * fieldSize, (tmpJ + 1) * fieldSize);
                if (field[i][tmpJ - 1] == 1) {
                    break;
                }
                tmpJ--;
            }
        }
    }
}

bool CheckEnemyMoveLeft(HDC hdc, int i, int j) {
    if (field[i - 1][j] == 1 && field[i][j] == 0) {
        bool enemyOnLine = false;

        int tmpI = i - 1;
        while (tmpI > 0) {
            if (field[tmpI][j] == 2) {
                enemyOnLine = true;
                break;
            }
            tmpI--;
        }
        if (enemyOnLine) {
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpI = i;
            while (tmpI > 0) {
                field[tmpI][j] = 2;
                Rectangle(hdc, fieldSize * tmpI, fieldSize * j, (tmpI + 1) * fieldSize, (j + 1) * fieldSize);
                if (field[tmpI - 1][j] == 2) {
                    return true;
                    break;
                }
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveRight(HDC hdc, int i, int j) {
    if (field[i + 1][j] == 1 && field[i][j] == 0) {
        bool enemyOnLine = false;

        int tmpI = i + 1;
        while (tmpI < N) {
            if (field[tmpI][j] == 2) {
                enemyOnLine = true;
                break;
            }
            tmpI++;
        }
        if (enemyOnLine) {
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 2;
                Rectangle(hdc, fieldSize * tmpI, fieldSize * j, (tmpI + 1) * fieldSize, (j + 1) * fieldSize);
                if (field[tmpI + 1][j] == 2) {
                    return true;
                    break;
                }
                tmpI++;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDown(HDC hdc, int i, int j) {
    if (field[i][j + 1] == 1 && field[i][j] == 0) {
        bool enemyOnLine = false;

        int tmpJ = j + 1;
        while (tmpJ < M) {
            if (field[i][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            tmpJ++;
        }
        if (enemyOnLine) {
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 2;
                Rectangle(hdc, fieldSize * i, fieldSize * tmpJ, (i + 1) * fieldSize, (tmpJ + 1) * fieldSize);
                if (field[i][tmpJ - 1] == 2) {
                    return true;
                    break;
                }
                tmpJ++;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveUp(HDC hdc, int i, int j) {
    if (field[i][j - 1] == 1 && field[i][j] == 0) {
        bool enemyOnLine = false;

        int tmpJ = j - 1;
        while (tmpJ > 0) {
            if (field[i][tmpJ] == 2) {
                enemyOnLine = true;
                break;
            }
            tmpJ--;
        }
        if (enemyOnLine) {
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpJ = j;
            while (tmpJ > 0) {
                field[i][tmpJ] = 2;
                Rectangle(hdc, fieldSize * i, fieldSize * tmpJ, (i + 1) * fieldSize, (tmpJ + 1) * fieldSize);
                if (field[i][tmpJ + 1] == 2) {
                    return true;
                    break;
                }
                tmpJ--;
            }
        }
    }
    return false;
}

void EnemyMove(HDC hdc) {
    int i = 0;
    bool moved = false;
    while (i < N) {
        int j = 0;
        while (j < M) {
            bool movedLeft = CheckEnemyMoveLeft(hdc, i, j);
            bool movedRight = CheckEnemyMoveRight(hdc, i, j);
            bool movedDown = CheckEnemyMoveDown(hdc, i, j);
            bool movedUp = CheckEnemyMoveUp(hdc, i, j);
            if (movedLeft || movedRight || movedDown || movedUp) {
                moved = true;
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

void SelectRectangle(HDC hdc, int x, int y) {
    int i = 0;
    bool founded = false;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if ((i + 1) * fieldSize > x && (j + 1) * fieldSize > y && ) {
                CheckMoveRight(hdc, i, j);
                CheckMoveLeft(hdc, i, j);
                CheckMoveDown(hdc, i, j);
                CheckMoveUp(hdc, i, j);
                founded = true;
                break;
            }
            j++;
        }
        if (founded) {
            break;
        }
        i++;
    }
}



