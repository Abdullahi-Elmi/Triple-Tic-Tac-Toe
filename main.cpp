/*
=============================
Name          : main.cpp
Author        : Abdullahi Elmi (260727124)
Description   : Contains only the main function, uses the methods in functions.cpp to run the game
=============================
*/

#include <iostream>
#include <string>
#include "functions.h"

int main()
{
    greetAndInstruct();
    char board[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A'};
    displayBoard(board);
    // Now the "Intialization" of this game is done, we can begin actually taking in player/computer input
    
    bool myTurn = true; 
    //will allow us to switch who's turn it is, when it's true, player's, if false, computer's
    
    while (checkWinner(board) == false)
    {
    // this while loop will keep switching between turns until somebody wins
        if (myTurn)
        {
            int playerChoice;
            std::cout << "\nPlayer's turn: Please input a cell number between 1 & 27\n";
            std::cin >> playerChoice;
            /* This is the player's choice of move. It should be noted that this will cause an infinite error if the user
               inputs something that is not an integer. I'll try and come back to this using a parsing method if I have time
               in order to avoid that*/

            if (checkIfLegal(playerChoice, board)) {
                board[playerChoice - 1] = 'X'; // we subtract one since the array starts at 0, and set the player's choice
                myTurn = false; // need to flip this var so that we give the next turn to the opponent
            }
            else {
                std::cout << "\nI'm sorry, that was an illegal move, please try again\n";
            }
        }
        else 
        {
            std::cout << "\Computer's turn: \n";
            computerMove(board);
            // since this method needs to be void all of the legal and error checking happens there, so we just run this
            myTurn = true;
            // and hand over the turn to the player
        }
        std::cout << "\nCurrent Board State: \n";
        displayBoard(board);
    }

    if (myTurn != true) // since we switch this bool after our turn ends, it's inverse when checking for who won
    {
        std::cout << "\n CONGRATULATIONS Player X!!! Man I want a rematch! \n";
    }
    else {
        std::cout << "\n Computer Won! Welp, better luck next time! (...when will you puny humans learn) \n";
    }
    // and Voila
    return 0;
}