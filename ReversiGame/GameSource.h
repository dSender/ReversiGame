#pragma once
#include "framework.h"
#include <stdio.h>

int saveGame();

int loadGame();

void DrawField(HDC hdc);

#pragma region PlayerMove
bool CheckMoveLeft(int i, int j, bool wasMovedHere, bool checkHasMove);


bool CheckMoveRight(int i, int j, bool wasMovedHere, bool checkHasMove);

bool CheckMoveDown(int i, int j, bool wasMovedHere, bool checkHasMove);

bool CheckMoveUp(int i, int j, bool wasMovedHere, bool checkHasMove);

bool CheckMoveDiagonalRightUp(int i, int j, bool wasMovedHere, bool checkHasMove);


bool CheckMoveDiagonalRightDown(int i, int j, bool wasMovedHere, bool checkHasMove);


bool CheckMoveDiagonalLeftDown(int i, int j, bool wasMovedHere, bool checkHasMove);


bool CheckMoveDiagonalLeftUp(int i, int j, bool wasMovedHere, bool checkHasMove);
#pragma endregion

#pragma region EnemyMoving
bool CheckEnemyMoveLeft(int i, int j, bool wasMovedHere);

bool CheckEnemyMoveRight(int i, int j, bool wasMovedHere);

bool CheckEnemyMoveDown(int i, int j, bool wasMovedHere);


bool CheckEnemyMoveUp(int i, int j, bool wasMovedHere);


bool CheckEnemyMoveDiagonalRightUp(int i, int j, bool wasMovedHere);

bool CheckEnemyMoveDiagonalRightDown(int i, int j, bool wasMovedHere);


bool CheckEnemyMoveDiagonalLeftDown(int i, int j, bool wasMovedHere);


bool CheckEnemyMoveDiagonalLeftUp(int i, int j, bool wasMovedHere);

#pragma endregion

void EnemyMove();


bool SelectRectangle(int x, int y);

int CheckEndGame(HDC hdc);



