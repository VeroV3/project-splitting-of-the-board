ilm
chelikman
Online

ilm — 15:11
Ver — 15:11
#include <winbgim.h>
#include <stdio.h>

#define MAX 20
#define BG BLACK
Expand
message.txt
11 KB
this is the current code
tho, i was just working on it rn
so i still got some clean up to do after some errors
ilm — 15:12
okay i will try to add it in git hub
Ver — 15:12
got it
ilm — 15:17
i update it can you see it ?
Ver — 15:18
yep
all good
thx
ilm — 15:18
great
Ver — 15:18
btw, this is how the code looks now in the window, still working on placing that text and making it smaller
Image
ilm — 15:19
good
btw i didn't understand part about changing the color for pieces how it suppose look?
Ver — 15:21
the part when, after the uses clicks on an already placed piece, the color of the pieces he places change?
that one?
ilm — 15:21
yeah
Ver — 15:22
do you not understand the code or how it should look in the window?
ilm — 15:23
approximately
Ver — 15:24
what.. sorry, i don't understand ur answer
so do you not understand the code? or do you not understand how it should look in the window?
ilm — 15:28
I just didn't understand how it should look in the window. Now I understand, thank you.
Ver — 15:28
oh
okay i guess
ilm — 15:29
i will try do a timer
and also we have ip today in 5 ?
Ver — 15:31
yeah, we have the lab at 6pm-8pm
also, i heard it's gonna be an inspection
like, another teacher checking out how the lab goes
so the class should be on the best behaviour and all that
ilm — 15:32
I just saw that stefan wrote that we have today in 5
ilm — 15:33
oh
Ver — 15:33
i just saw that text rn
thanks for letting me know
ilm — 15:34
np
Ver — 16:12
Image
what do you think?
lookign good? :D
made the detection of how many pieces were placed too
ilm — 16:12
that is great!!!
Ver — 16:13
cuz we should have a max of 8 pieces per color so it's 7 pieces we can place besides the ones that are already on the board
and wrote comments describing every phase in the code so we both understand what is done easier
#include <winbgim.h>
int squareSize;          // Size of each square on the board
int boardStartX = 200;   
int boardStartY = 200;   
int board[9][9];         // Our game board 9x9 
int currentColor = 0;    // Which color we're using now (0=no color)
Expand
message.txt
11 KB
ilm — 16:13
i think you already do an half work
Ver — 16:13
can you please update the github place again?
ilm — 16:14
sure
﻿
Ver
veronica_r
 
 
 
me.
#include <winbgim.h>
int squareSize;          // Size of each square on the board
int boardStartX = 200;   
int boardStartY = 200;   
int board[9][9];         // Our game board 9x9 
int currentColor = 0;    // Which color we're using now (0=no color)
int colorCount[8] = {0}; // How many pieces of each color placed
int maxPieces = 7;       // The maximum pieces per color
bool gameRunning = true; //Check if the game is ongoing

// Color array
int colors[8] = {BLACK, RED, BLUE, GREEN, YELLOW, CYAN, LIGHTBLUE, MAGENTA};


void drawOnePiece(int row, int col, int colorNum)
{
    // Compute center of the square
    int x = boardStartX + (col-1) * squareSize;
    int y = boardStartY + (row-1) * squareSize;
    int centerX = x + squareSize/2;
    int centerY = y + squareSize/2;
    
    // Erasing the cell by drawing a black square over any possible content available
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(centerX-20, centerY-20, centerX+20, centerY+20);
    
    // Circle 
    setcolor(colors[colorNum]);
    setfillstyle(SOLID_FILL, colors[colorNum]);
    fillellipse(centerX, centerY, 18, 18);
}

//We check if position has neighbor cell of the same color
bool hasNeighbor(int row, int col, int colorNum)
{
    
    // check top neighbor
    if (row > 1)  // not at top edge, we don't want to go outside the board borders
    {
        int upValue = board[row-1][col];
        if (upValue == colorNum || upValue == -colorNum)
            return true;  // found neighbor
    }
    
    // check down neighbor
    if (row < 8)  // not at the bottom edge, not going outside the board
    {
        int downValue = board[row+1][col];
        if (downValue == colorNum || downValue == -colorNum)
            return true; //found neighbor
    }
    
    // checking the left neighbor
    if (col > 1)  // not left edge
    {
        int leftValue = board[row][col-1];
        if (leftValue == colorNum || leftValue == -colorNum)
            return true; //found neighbor
    }
    
    // checking the right neighbor
    if (col < 8)  // Not right edge
    {
        int rightValue = board[row][col+1];
        if (rightValue == colorNum || rightValue == -colorNum)
            return true;
    }
    
    return false;  // if no neighbor is found we get to this point and we return false
}

// How do we handle the mouse clicks
void handleClick()
{
    int x, y, row, col;
    
    // we check if left mouse button was clicked
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        // Get mouse position
        x = mousex();
        y = mousey();
        
        // Clear the click so it doesn't repeat and the function doesn't take the same click again foreverr
        clearmouseclick(WM_LBUTTONDOWN);
        
      
        if (x >= boardStartX && x <= boardStartX + 8*squareSize && y >= boardStartY && y <= boardStartY + 8*squareSize)  // we check if click is inside board area
           
        {
            col = (x - boardStartX) / squareSize + 1; //we compute which cell was clicked (column and row)
            row = (y - boardStartY) / squareSize + 1;
            
            // we se what we have in the coard cell that we clicked
            int squareValue = board[row][col];
            
            // 1. if we clicked on a default piece, a negative number
            if (squareValue < 0)
            {
                // we select this color
                currentColor = -squareValue;  // Make positive so we get the color number to place pieces
                setcolor(WHITE);
                { char tmp[] = "Selected color from initial piece"; outtextxy(50,50,tmp); } //char tmp[] is a temporary variable of type char array to store the text message suggested by the vscde assistand cuz of the char error
                delay(1000);
                setcolor(BLACK);
                bar(50, 50, 300, 70);
            }
            // 2. we clicked on an empty square
            else if (squareValue == 0)
            {
                // we need a color selected first so it won't do anything without it
                if (currentColor == 0)
                {
                    setcolor(RED);
                    { char tmp[] = "First click on a starting piece!"; outtextxy(50,50,tmp); }
                    delay(1000);
                    setcolor(BLACK);
                    bar(50, 50, 300, 70);
                    return;
                }
                
                // Checking if we didn't place too many pieces, more than 7 excepting the starting default piece
                if (colorCount[currentColor] >= maxPieces)
                {
                    setcolor(RED);
                    { char tmp[] = "MAX 7 pieces per color!"; outtextxy(50,50,tmp); }
                    delay(1000);
                    setcolor(BLACK);
                    bar(50, 50, 300, 70);
                    return;
                }
                
                // we are checking the surrounding cells up, down, left, right to see the neighbor colors and see if we can place the piece there so we don't make a random color mush
                if (hasNeighbor(row, col, currentColor))
                {
                    // we place the piece
                    board[row][col] = currentColor;
                    colorCount[currentColor]++;
                    drawOnePiece(row, col, currentColor);
                    
                    //we show a success text
                    setcolor(colors[currentColor]);
                    char msg[50];
                    sprintf(msg, "Placed! %d/7 for this color", colorCount[currentColor]);
                    outtextxy(50, 50, msg);
                    delay(500);
                    setcolor(BLACK);
                    bar(50, 50, 300, 70);
                }
                else
                {
                    // There is no neighbor of the same color found, so in that case we can't place the piece here
                    setcolor(RED);
                    { char tmp[] = "Must touch the same color piece!"; outtextxy(50,50,tmp); }
                    delay(1000);
                    setcolor(BLACK);
                    bar(50, 50, 300, 70);
                }
            }
            // 3. we clicked on the cell that already has a player's piece, a positive value so we don't do anything
            else if (squareValue > 0)
            {
                // Select this color
                currentColor = squareValue;
                setcolor(WHITE);
                char msg[50];
                sprintf(msg, "Now using color %d (%d/7)", currentColor, colorCount[currentColor]);
                outtextxy(50, 50, msg);
                delay(1000);
                setcolor(BLACK);
                bar(50, 50, 300, 70);
            }
        }
        else
        {
            // Clicked outside board so then it's game over
            gameRunning = false;
        }
    }
}

// Drawing the boardd
void setupBoard()
{
    squareSize = 50;  // Each square is 50 pixels
    
    // First, make all squares empty
    for (int row = 1; row <= 8; row++)// we start from 1 to 8 to make it easier to manage the board without using 0 index start
    {
        for (int col = 1; col <= 8; col++)
        {
            board[row][col] = 0; //we make an empty cell
        }
    }
    
    // the 8 starting pieces from the start example
    board[3][3] = -1;  // RED starting piece
    board[4][3] = -2;  // BLUE starting piece  
    board[5][1] = -3;  // GREEN starting piece
    board[1][3] = -4;  // YELLOW starting piece
    board[3][8] = -5;  // CYAN starting piece
    board[6][8] = -6;  // LIGHTBLUE starting piece
    board[2][7] = -7;  // MAGENTA starting piece
    board[7][5] = -8;  // (Not used - color 0 is BLACK)
}

// Now wedraw the board with all the pieces and everything
void drawBoard()
{
    // we clear the screen
    cleardevice();
    
    //present the game title
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(200, 30, "Splitting of the board game");
    
    // Draw instructions
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(50, 70, "1. Click colored circle to select color");
    outtextxy(50, 90, "2. Place max 7 pieces of same color");
    outtextxy(50, 110, "3. New piece must touch same color");
    
    // Draw board grid
    for (int row = 1; row <= 8; row++)
    {
        for (int col = 1; col <= 8; col++)
        {
            // Draw white square border
            setcolor(WHITE);
            rectangle(boardStartX + (col-1)*squareSize,
                      boardStartY + (row-1)*squareSize,
                      boardStartX + col*squareSize,
                      boardStartY + row*squareSize);
            
            // Draw piece if there is one
            int pieceValue = board[row][col];
            if (pieceValue != 0)
            {
                if (pieceValue < 0)  // Starting piece
                {
                    drawOnePiece(row, col, -pieceValue);
                    // Add white border for starting pieces
                    setcolor(WHITE);
                    int x = boardStartX + (col-1)*squareSize + squareSize/2;
                    int y = boardStartY + (row-1)*squareSize + squareSize/2;
                    circle(x, y, 20);
                }
                else  // Player's piece
                {
                    drawOnePiece(row, col, pieceValue);
                }
            }
        }
    }
    
    // Draw color counters on the right
    setcolor(WHITE);
    outtextxy(650, 100, "PIECES PLACED:");
    for (int i = 1; i <= 7; i++)
    {
        setcolor(colors[i]);
        char counter[50];
        sprintf(counter, "Color %d: %d/7", i, colorCount[i]);
        outtextxy(650, 120 + i*20, counter);
    }
    
    // Show current color
    setcolor(WHITE);
    char current[50];
    if (currentColor == 0)
        sprintf(current, "Current: NONE (click a circle)");
    else
        sprintf(current, "Current: Color %d", currentColor);
    outtextxy(650, 300, current);
}

// MAIN FUNCTION - Where program starts
int main()
{
    // Open graphics window
    initwindow(1000, 800);
    
    // Set up the game
    setupBoard();
    drawBoard();
    
    // Game loop
    while (gameRunning)
    {
        handleClick();
        
        // Small delay to prevent CPU overuse
        delay(10);
    }
    
    // Game ended
    setcolor(WHITE);
    outtextxy(300, 400, "GAME OVER - Click outside board to exit");
    outtextxy(300, 420, "Press any key to close window");
    
    // Wait for key press
    getch();
    
    // Close graphics window
    closegraph();
    
    return 0;
}
