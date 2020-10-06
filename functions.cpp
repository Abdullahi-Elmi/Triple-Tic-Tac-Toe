/*
=============================
Name          : functions.cpp
Author        : Abdullahi Elmi (260727124)
Description   : Contains all the helper functions (required by main) to run the tic-tac-toe game
=============================
*/

#include <iostream>
#include <string>

void greetAndInstruct()
{
    std::string yesORno;
    std::cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer\n" <<
        "The board is numbered from 1 to 27 as per the following:\n\n" <<
        "1 | 2 | 3     10 | 11 | 12     19 | 20 | 21\n" <<
        "----------    -------------    -------------\n" <<
        "4 | 5 | 6     13 | 14 | 15     22 | 23 | 24\n" <<
        "----------    -------------    -------------\n" <<
        "7 | 8 | 9     16 | 17 | 18     25 | 26 | 27\n\n" <<
        "Player starts first. Simply input the number of the cell you want to occupy. Players move is marked with X. Computers move is marked with O.\n" <<
        "Start? (y/n): ";
    getline(std::cin, yesORno);
    // So here we first print the entire initial prompt asked of us in the assignment, and take the user's input into a variable denoted yesORno
    if (yesORno == "y" || yesORno == "Y")
    {
        std::cout << "Wonderful! Lets Play!\n";
        // In the case where the user's input was "y" we start the game. main() does the rest from here, so we don't handle anything here
    }
    else if (yesORno == "n" || yesORno == "N")
    {
        std::cout << "Maybe another time then. Have a nice day!";
        exit(EXIT_SUCCESS);
        // in the case where the user's input was "n" we quit the whole program
    }
    // Note: I made it so that uppercase and lowercase is accepted in the response
    else {
        std::cout << "I'm sorry, I couldn't understand what you entered. You can restart the program and try again.";
        exit(EXIT_FAILURE);
        /* we weren't told in the assignment what to do if the user's input was anything besides the two above cases, so I'm just going
           to mention we couldn't understand the user's response and quit anyways. If I have enough time, I'll come back and put the user in
           a loop that only escapes if they enter the accepted binary options. */
    }
}

void displayBoard(char board[])
{
    int cells[3][9];
    int table = 0;

    // This loop creates a 2d array of ints that physically mimics the way the board is actually supposed to look
    while (table < 3)
    {
        //triple nested loop as the value we want (index of the cell on the board) depends on the table/row/column
        int board_index = 9 * table + 1;
        // so first loop has index start at 1 for table 1, 10 for table 2 and 19 for table 3, appropriately
        for (int row = 0; row < 3; row++)
        {
            for (int col = table * 3; col < table * 3 + 3; col++)
            {
                // the column actually depends on the table, we're in, row does not
                char c = board[board_index - 1];
                // get the value of the character at the current index in the board[]
                cells[row][col] = board_index;
                // place the integer appropriate for our current cell
                board_index++;
                if (c == 'X')
                {
                    cells[row][col] = -1;
                }
                if (c == 'O')
                {
                    cells[row][col] = -2;
                }
                // easily identifiable so that we can print the proper values in the next nested loop
            }
        }
        table++;
    }

    // now this loop actually displays the table, we couldn't do it in the above loop as the order "row/table/col" is
    // different
    int row = 0;
    while (row < 3)
    {
        int board_index = 9 * row + 1;
        for (int table = 0; table < 3; table++)
        {
            for (int col = table * 3; col < table * 3 + 3; col++)
            {
                // pretty much the same as the above loop, but swapping the row and table order (since we need to print)
                // one row at a time
                if (cells[row][col] > 0)
                {
                    std::cout << cells[row][col];
                    // just print the cell number if it's positive (the cell hasn't been used yet)
                }
                else
                {
                    if (cells[row][col] == -1)
                    {
                        std::cout << 'X';
                    }
                    else {
                        std::cout << 'O';
                    }
                    // otherwise print the X/O corresponding to our above choice (X=-1, O=-2)
                }
                
                if (col < table * 3 + 2)
                {
                    std::cout << " | ";
                    // this is so we don't print | on the rightside of a table
                }
                board_index++;
            }
            std::cout << "     " ;
            // there should be a big space between each table
        }
        row++;
        std::cout << "\n" << "---------     -------------    -------------\n";
        // we print a separation after every row
    }
    std::cout << "\n";
}

bool checkIfLegal(int cellNbre, char board[])
{
    bool isLegal = false;
    // An assumption here is that [1 <= cellNbre <= 27] since those are the cell indices shown to the player
    if (cellNbre < 1 || cellNbre > 27)
    {
        return isLegal;
        // so if we're given an illegal index, we don't need to bother checking what's at the chosen index
    }
    char chosen = board[cellNbre-1];
    // and so the chosen index within the array is actually cellNbre-1, since the array starts at 0, and the choice of
    // indices, at 1
    if (chosen != 'X' && chosen != 'O') // in the case where the value at the chosen index isn't X or O
    {
        // that means the chosen index is free, and therefore a legal move
        isLegal = true;
    }
    return isLegal;
}

bool checkWinner(char board[])
{ /* **Note** - This doesn't handle ties. Never happens based on how the computer is set up, and the professor said it was
       okay in a discussion announcement*/
    bool gameWon = false;
    int table = 0;
    
    // this while loop handles win conditions within the same table (the usual conditions for tic-tac-toe)
    while (table < 3)
    {
        for (int i = table * 9; i < table * 9 + 7; i += 3)
        {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
            {
                // this for loop checks the win condition of getting a row (within the same table)
                gameWon = true;
                return gameWon;
            }
        }

        for (int i = table * 9; i < table * 9 + 3; i++)
        {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6])
            {
                // this for loop checks the win condition of getting a column (within the same table)
                gameWon = true;
                return gameWon;
            }
        }

        for (int i = table * 9; i < table * 9 + 1; i++)
        {
        // this isn't really a loop, I just want it to run once per while loop (3 times in total)
            if (board[i] == board[i + 4] && board[i + 4] == board[i + 8])
            {
                // this checks the win condition of getting a diagonal \ (within the same table)
                gameWon = true;
                return gameWon;
            }
            if (board[i + 2] == board[i + 4] && board[i + 4] == board[i + 6])
            {
                // this checks the win condition of getting a diagonal / (within the same table)
                gameWon = true;
                return gameWon;
            }
        }
        table++;
    }
    //****************************Win Conditions within Same table - Finished***********************************

    // Now for the win conditions unique to 3D - Tic Tac Toe (conditions that occur across different tables)
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == board[i + 9] && board[i + 9] == board[i + 18])
        {
            // this for loop checks the win conditions that involve the same cell being chosen across all 3 tables
            gameWon = true;
            return gameWon;
        }
    }

    // In order to check for the other 3D conditions, we'll collapse the 3 tables into one, with respect to both
    // 'X' & 'O' (so 1 X table, 1 O table), and check if any of those satisfy normal win conditions
    char X_table[9];
    char O_table[9];
    char junk[9] = { 'B','C','D','E','F','G','H','I','J' }; // used to fill in the spaces of the X & O tables
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 'X' || board[i + 9] == 'X' || board[i + 18] == 'X')
        {
            X_table[i] = 'X';
            // we collapse the corresponding cell among the 3 tables, into 1 that = X if any of the 3 originally did
        }
        else {
            X_table[i] = junk[i];
            // if not, we use one of the junk variables
        }
        // same logic for the O table
        if (board[i] == 'O' || board[i + 9] == 'O' || board[i + 18] == 'O') {
            O_table[i] = 'O';
        }
        else {
            O_table[i] = junk[i];
        }
    }
    // now we can check if either the single X or O tables provide a win (normal tic-tac-toe condition checking)
    for (int i = 0; i < 9; i+=3)
    {
        if (X_table[i] == X_table[i + 1] && X_table[i + 1] == X_table[i + 2])
        {
            gameWon = true;
            return gameWon;
        }
        
        if (O_table[i] == O_table[i + 1] && O_table[i + 1] == O_table[i + 2])
        {
            gameWon = true;
            return gameWon;
        }
        // row condition check
    }

    for (int i = 0; i < 3; i++) {
        if (X_table[i] == X_table[i + 3] && X_table[i + 3] == X_table[i + 6])
        {
            gameWon = true;
            return gameWon;
        }

        if (O_table[i] == O_table[i + 3] && O_table[i + 3] == O_table[i + 6])
        {
            gameWon = true;
            return gameWon;
        }
        // column condition check
    }

    if (X_table[0] == X_table[4] && X_table[4] == X_table[8])
    {
        // this checks the win condition of getting a diagonal \
        gameWon = true;
        return gameWon;
    }
    if (X_table[2] == X_table[4] && X_table[4] == X_table[6])
    {
        // this checks the win condition of getting a diagonal /
        gameWon = true;
        return gameWon;
    }
    if (O_table[0] == O_table[4] && O_table[4] == O_table[8])
    {
        // this checks the win condition of getting a diagonal \
        gameWon = true;
        return gameWon;
    }
    if (O_table[2] == O_table[4] && O_table[4] == O_table[6])
    {
        // this checks the win condition of getting a diagonal /
        gameWon = true;
        return gameWon;
    }
    // ******************************Win Conditions Across tables - Finished***********************************
    return gameWon;
}

void computerMove(char board[])
{
    bool winningMove = false;
    char board_copy[27];
    // copy of the board for the computer to use in order to check if its hypothetical moves would cause it to win
    for (int i = 0; i < 27; i++) {
        board_copy[i] = board[i];
    }

    for (int i = 0; i < 27; i++) {
        if (checkIfLegal(i + 1, board_copy)) // using "i + 1" to correspond with the 1-27 range given to player
        {
        // of course we only check if this can net us the win, if the move is legal in the first place
            char temp = board_copy[i]; // we want our copy board to go back to normal after each iteration
            board_copy[i] = 'O';
            if (checkWinner(board_copy)) // now we're testing to see if this legal move will get the computer the win
            {
                board[i] = 'O';
                winningMove = true;
                return;
                // if it does, then we make the move and leave
            }
            board_copy[i] = temp; // if our move wasn't a winning move, we reset the chosen move, and try the next legal
        }
    }

    char board_copy_two[27];
    // copy of the board for the computer to use in order to check if its hypothetical moves would cause it to win
    for (int i = 0; i < 27; i++) {
        board_copy_two[i] = board[i];
    }
    /* **Note**: board_copy should be the same, but I didn't really wanna risk errors if I could, and so just created a
                 2nd copy for the 2nd half of the computer's strategy. */
    
    if (!winningMove) // in the case where no move allows us to win, we pivot to blocking the opponent
    {
        for (int i = 0; i < 27; i++) {
            if (checkIfLegal(i + 1, board_copy_two))
            {
            // the move needs to be legal for the comp to block it (and for it to even be a winning move for the opponent)
                char temp = board_copy_two[i]; 
                // we want our copy board to go back to normal after each iteration
                board_copy_two[i] = 'X';
                if (checkWinner(board_copy_two)) // now we're testing to see if this legal move will get the player the win
                {
                // if it does, then we need to choose it in order to block the player opponent
                    board[i] = 'O';
                    winningMove = true;
                    return;
                    // if it does, then we make the move and leave
                }
                board_copy_two[i] = temp; // if our move wasn't a winning move, we reset the chosen move, and try the next legal
            }
        }
    }
    /* in the case where no move allows us OR the opponent to win, we choose random (could use more AI, but wasn't 
       specified, and I don't think I'll have the time)*/
    if (!winningMove) {
        for (int i = 0; i < 27; i++) {
            if (checkIfLegal(i + 1, board))
            {
                board[i] = 'O';
                return;
                // just pick the legal move with the lowest cell index for now
            }
        }
    }
}