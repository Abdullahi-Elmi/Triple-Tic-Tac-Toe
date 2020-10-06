#pragma once
/*
=============================
Name          : functions.cpp
Author        : Abdullahi Elmi (260727124)
Description   : Header files for all the methods in functions.cpp
=============================
*/
void greetAndInstruct();
void displayBoard(char board[]);
bool checkIfLegal(int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);