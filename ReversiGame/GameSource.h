#pragma once
#include "framework.h"
#include <stdio.h>

#define N 8
#define M 8

int field[N][M] = {
    {0, 0, 0, 0,	0, 0, 0, 0},
    {0, 0, 0, 2,	0, 2, 0, 0},
    {0, 0, 0, 0,	1, 0, 0, 0},
    {0, 0, 0, 2,	1, 2, 0, 0},

    {0, 0, 2, 1,	2, 0, 0, 0},
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
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            else if (field[i][j] == 1) {
                SelectObject(hdc, playerBrush);
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            else if (field[i][j] == 2) {
                SelectObject(hdc, enemyBrush);
                Rectangle(hdc, fieldSize * j, fieldSize * i, (j + 1) * fieldSize, (i + 1) * fieldSize);
            }
            j++;
        }
        i++;
    }
}

#pragma region PlayerMove
bool CheckMoveLeft(HDC hdc, int i, int j, bool wasMovedHere) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 1;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * i, (tmpJ + 1) * fieldSize, (i + 1) * fieldSize);
                if (field[i][tmpJ + 1] == 1) {
                    return true;
                }
                tmpJ++;
            }
        }
    }
    return false;
}

bool CheckMoveRight(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        while (tmpJ > 0) {
            if (field[i][tmpJ] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[i][tmpJ] == 0) {
                return false;
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
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * i, (tmpJ + 1) * fieldSize, (i + 1) * fieldSize);
                if (field[i][tmpJ - 1] == 1) {
                    return true;
                }
                tmpJ--;
            }
        }
    }
    return false;
}

bool CheckMoveDown(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i - 1][j] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpI = i - 1;
        while (tmpI > 0) {
            if (field[tmpI][j] == 1) {
                playerOnLine = true;
                break;
            }
            else if (field[tmpI][j] == 0) {
                return false;
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
                Rectangle(hdc, fieldSize * j, fieldSize * tmpI, (j + 1) * fieldSize, (tmpI + 1) * fieldSize);
                if (field[tmpI - 1][j] == 1) {
                    return true;
                }
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckMoveUp(HDC hdc, int i, int j, bool wasMovedHere) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 1;
                Rectangle(hdc, fieldSize * j, fieldSize * tmpI, (j + 1) * fieldSize, (tmpI + 1) * fieldSize);
                if (field[tmpI + 1][j] == 1) {
                    return true;
                }
                tmpI++;
            }
        }
    }
    return false;
}

bool CheckMoveDiagonalRightUp(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i + 1][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i + 1;
        while (tmpJ > 0 && tmpI < N) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            tmpI = i;
            while (tmpJ > 0 && tmpI < N) {
                field[tmpI][tmpJ] = 1;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * tmpI, (tmpJ + 1) * fieldSize, (tmpI + 1) * fieldSize);
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

bool CheckMoveDiagonalRightDown(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i - 1][j - 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j - 1;
        int tmpI = i - 1;
        while (tmpJ > 0 && tmpI > 0) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            tmpI = i;
            while (tmpJ > 0 && tmpI > 0) {
                field[tmpI][tmpJ] = 1;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * tmpI, (tmpJ + 1) * fieldSize, (tmpI + 1) * fieldSize);
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

bool CheckMoveDiagonalLeftDown(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i - 1][j + 1] == 2 && (field[i][j] == 0 || wasMovedHere)) {
        bool playerOnLine = false;
        int tmpJ = j + 1;
        int tmpI = i - 1;
        while (tmpJ < M && tmpI > 0) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI > 0) {
                field[tmpI][tmpJ] = 1;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * tmpI, (tmpJ + 1) * fieldSize, (tmpI + 1) * fieldSize);
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

bool CheckMoveDiagonalLeftUp(HDC hdc, int i, int j, bool wasMovedHere) {
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
        if (playerOnLine) {
            HBRUSH playerBrush;
            playerBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, playerBrush);
            tmpJ = j;
            tmpI = i;
            while (tmpJ < M && tmpI < N) {
                field[tmpI][tmpJ] = 1;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * tmpI, (tmpJ + 1) * fieldSize, (tmpI + 1) * fieldSize);
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
bool CheckEnemyMoveLeft(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i][j - 1] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpJ = j - 1;
        while (tmpJ > 0) {
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
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpJ = j;
            while (tmpJ > 0) {
                field[i][tmpJ] = 2;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * i, (tmpJ + 1) * fieldSize, (i + 1) * fieldSize);
                if (field[i][tmpJ - 1] == 2) {
                    return true;
                }
                tmpJ--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveRight(HDC hdc, int i, int j, bool wasMovedHere) {
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
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpJ = j;
            while (tmpJ < M) {
                field[i][tmpJ] = 2;
                Rectangle(hdc, fieldSize * tmpJ, fieldSize * i, (tmpJ + 1) * fieldSize, (i + 1) * fieldSize);
                if (field[i][tmpJ + 1] == 2) {
                    return true;
                }
                tmpJ++;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveDown(HDC hdc, int i, int j, bool wasMovedHere) {
    if (field[i - 1][j] == 1 && (field[i][j] == 0 || wasMovedHere)) {
        bool enemyOnLine = false;
        int tmpI = i - 1;
        while (tmpI > 0) {
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
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpI = i;
            while (tmpI > 0) {
                field[tmpI][j] = 2;
                Rectangle(hdc, fieldSize * j, fieldSize * tmpI, (j + 1) * fieldSize, (tmpI + 1) * fieldSize);
                if (field[tmpI - 1][j] == 2) {
                    return true;
                }
                tmpI--;
            }
        }
    }
    return false;
}

bool CheckEnemyMoveUp(HDC hdc, int i, int j, bool wasMovedHere) {
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
            HBRUSH enemyBrush;
            enemyBrush = CreateSolidBrush(RGB(1, 1, 1));
            SelectObject(hdc, enemyBrush);
            tmpI = i;
            while (tmpI < N) {
                field[tmpI][j] = 2;
                Rectangle(hdc, fieldSize * j, fieldSize * tmpI, (j + 1) * fieldSize, (tmpI + 1) * fieldSize);
                if (field[tmpI + 1][j] == 2) {
                    return true;
                }
                tmpI++;
            }
        }
    }
    return false;
}
#pragma endregion

void EnemyMove(HDC hdc) {
    int i = 0;
    bool moved = false;
    while (i < N) {
        int j = 0;
        int gl;
        while (j < M) {
            bool movedDown = CheckEnemyMoveDown(hdc, i, j, false);
            bool movedUp = CheckEnemyMoveUp(hdc, i, j, movedDown);
            bool movedRight = CheckEnemyMoveRight(hdc, i, j, (movedDown || movedUp));
            bool movedLeft = CheckEnemyMoveLeft(hdc, i, j, (movedDown || movedUp || movedRight));
            if (movedUp || movedDown || movedRight || movedLeft) {
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

bool SelectRectangle(HDC hdc, int x, int y) {
    int i = 0;
    bool moved = false;
    bool founded = false;
    while (i < N) {
        int j = 0;
        while (j < M) {
            if ((j + 1) * fieldSize > x && (i + 1) * fieldSize > y) {
                bool movedRight = CheckMoveRight(hdc, i, j, false);
                moved = moved || movedRight;
                bool movedUp = CheckMoveUp(hdc, i, j, moved);
                moved = moved || movedUp;
                bool movedLeft = CheckMoveLeft(hdc, i, j, moved);
                moved = moved || movedLeft;
                bool movedDown = CheckMoveDown(hdc, i, j, moved);
                moved = moved || movedDown;
                bool movedRightUp = CheckMoveDiagonalRightUp(hdc, i, j, moved);
                moved = moved || movedRightUp;
                bool movedRightDown = CheckMoveDiagonalRightDown(hdc, i, j, moved);
                moved = moved || movedRightDown;
                bool movedLeftDown = CheckMoveDiagonalLeftDown(hdc, i, j, moved);
                moved = moved || movedLeftDown;
                bool movedLeftUp = CheckMoveDiagonalLeftUp(hdc, i, j, moved);
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



