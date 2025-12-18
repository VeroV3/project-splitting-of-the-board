#include <winbgim.h>
#include <stdio.h>

#define MAX 20
#define BG BLACK

// Menu constants
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 20

int side, number;
int width = 400;
int height = 400;
int left = 100;
int top = 100;

bool GameOver;

int GameBoard[MAX][MAX];
int piecesPlaced[8] = {0}; // Counter for placed pieces per color (0-7)
const int MAX_PIECES_PER_COLOR = 7; // Maximum 7 additional pieces per color

int color[8] = {BLACK, RED, BLUE, GREEN, YELLOW, LIGHTCYAN, LIGHTBLUE, MAGENTA};
int col_i = 0; // Current selected color

// Menu variables
int menuLeft, menuTop;
bool button1Clicked = false;
bool button2Clicked = false;
bool button3Clicked = false;

// Function to check if a position has an adjacent piece of the same color
bool HasAdjacentSameColor(int line, int column, int colorIndex)
{
    // Check all 8 directions around the position
    // North
    if (line > 1 && (GameBoard[line-1][column] == colorIndex || GameBoard[line-1][column] == -colorIndex))
        return true;
    // South
    if (line < number && (GameBoard[line+1][column] == colorIndex || GameBoard[line+1][column] == -colorIndex))
        return true;
    // West
    if (column > 1 && (GameBoard[line][column-1] == colorIndex || GameBoard[line][column-1] == -colorIndex))
        return true;
    // East
    if (column < number && (GameBoard[line][column+1] == colorIndex || GameBoard[line][column+1] == -colorIndex))
        return true;
    // North-West
    if (line > 1 && column > 1 && (GameBoard[line-1][column-1] == colorIndex || GameBoard[line-1][column-1] == -colorIndex))
        return true;
    // North-East
    if (line > 1 && column < number && (GameBoard[line-1][column+1] == colorIndex || GameBoard[line-1][column+1] == -colorIndex))
        return true;
    // South-West
    if (line < number && column > 1 && (GameBoard[line+1][column-1] == colorIndex || GameBoard[line+1][column-1] == -colorIndex))
        return true;
    // South-East
    if (line < number && column < number && (GameBoard[line+1][column+1] == colorIndex || GameBoard[line+1][column+1] == -colorIndex))
        return true;
    
    return false;
}

// Function to check if there's a path from initial piece to target position
bool HasPathToInitialPiece(int line, int column, int colorIndex)
{
    // First, check immediate adjacency (simpler check)
    return HasAdjacentSameColor(line, column, colorIndex);
}

// Function to draw a game piece
void DrawingPiece(int line, int column, int v)
{
    int c;
    if (v < 0) c = -v; else c = v;
    int x1, y1, x2, y2, xmiddle, ymiddle;
    setcolor(BG); setfillstyle(SOLID_FILL, BG);
    x1 = left + side * (column - 1); y1 = top + side * (line - 1);
    x2 = x1 + side; y2 = y1 + side;
    xmiddle = (x1 + x2) / 2; ymiddle = (y1 + y2) / 2;
    bar(xmiddle - 20, ymiddle - 20, xmiddle + 20, ymiddle + 20);
    setcolor(color[c]); setfillstyle(SOLID_FILL, color[c]);
    if (v < 0) setcolor(WHITE);
    fillellipse(xmiddle, ymiddle, 18, 18);
}

// Function to draw the vertical menu with piece counters
void DrawVerticalMenu()
{
    // Calculate menu position: left of the board with some margin
    menuLeft = left - BUTTON_WIDTH - BUTTON_MARGIN;
    menuTop = top;  // Align top with board top
    
    // Draw Button 1: "RED"
    setcolor(button1Clicked ? LIGHTGRAY : RED);
    setfillstyle(SOLID_FILL, button1Clicked ? LIGHTGRAY : RED);
    bar(menuLeft, menuTop, 
        menuLeft + BUTTON_WIDTH, 
        menuTop + BUTTON_HEIGHT);
    // Draw current color indicator and game info
    setcolor(WHITE);
    rectangle(menuLeft, menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 20, 
              menuLeft + BUTTON_WIDTH, 
              menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 120);
    
    char currentColorText[50];
    sprintf(currentColorText, "Current: %d", col_i);
    outtextxy(menuLeft + 10, menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 35, currentColorText);
    
    char rulesText[100] = "Rules:";
    outtextxy(menuLeft + 10, menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 60, rulesText);
    char rulesText2[100] = "1. Max 7 pieces/color";
    outtextxy(menuLeft + 10, menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 80, rulesText2);
    char rulesText3[100] = "2. Must be adjacent";
    outtextxy(menuLeft + 10, menuTop + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN) + 100, rulesText3);
}

// Function to check if menu button was clicked
void CheckMenuClick(int x, int y)
{
    // Reset all button clicked states
    button1Clicked = false;
    button2Clicked = false;
    button3Clicked = false;
    
    // Check Button 1 (RED)
    if (x >= menuLeft && x <= menuLeft + BUTTON_WIDTH &&
        y >= menuTop && y <= menuTop + BUTTON_HEIGHT)
    {
        button1Clicked = true;
        col_i = 1;  // RED color index
    }
    
    // Check Button 2 (BLUE)
    else if (x >= menuLeft && x <= menuLeft + BUTTON_WIDTH &&
             y >= menuTop + BUTTON_HEIGHT + BUTTON_MARGIN && 
             y <= menuTop + 2 * BUTTON_HEIGHT + BUTTON_MARGIN)
    {
        button2Clicked = true;
        col_i = 2;  // BLUE color index
    }
    
    // Check Button 3 (GREEN)
    else if (x >= menuLeft && x <= menuLeft + BUTTON_WIDTH &&
             y >= menuTop + 2 * (BUTTON_HEIGHT + BUTTON_MARGIN) && 
             y <= menuTop + 3 * BUTTON_HEIGHT + 2 * BUTTON_MARGIN)
    {
        button3Clicked = true;
        col_i = 3;  // GREEN color index
    }
}

// Modified PlacingPiece function with adjacency check
void PlacingPiece()
{
    int line, column, x, y;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
       clearmouseclick(WM_LBUTTONDOWN);
       x = mousex(); y = mousey();
       
       // Check if click is on menu buttons
       if (x >= menuLeft && x <= menuLeft + BUTTON_WIDTH)
       {
           CheckMenuClick(x, y);
           // Redraw menu to show clicked state
           DrawVerticalMenu();
       }
       // Check if click is on game board
       else if (!(x >= left && x <= left + width && y >= top && y <= top + height))
       {
          GameOver = true;
       }
       else
       {
          line = (y - top) / side + 1; 
          column = (x - left) / side + 1;
          
          // Check if cell is empty
          if (GameBoard[line][column] == 0)
          {
              // Check if color has remaining pieces
              if (piecesPlaced[col_i] >= MAX_PIECES_PER_COLOR)
              {
                  // Show message (temporarily)
                  setcolor(RED);
                  outtextxy(left, top + height + 20, "No more pieces for this color!");
                  delay(1000);
                  // Clear message
                  setcolor(BG);
                  bar(left, top + height + 20, left + 300, top + height + 40);
                  return;
              }
              
              // Check adjacency to same color pieces
              if (HasPathToInitialPiece(line, column, col_i))
              {
                  // Place the piece
                  GameBoard[line][column] = col_i;
                  piecesPlaced[col_i]++;  // Increment counter
                  DrawingPiece(line, column, col_i);
                  
                  // Update menu counters
                  DrawVerticalMenu();
              }
              else
              {
                  // Show error message (temporarily)
                  setcolor(RED);
                  outtextxy(left, top + height + 20, "Must be adjacent to same color!");
                  delay(1000);
                  // Clear message
                  setcolor(BG);
                  bar(left, top + height + 20, left + 300, top + height + 40);
              }
          }
          else if (GameBoard[line][column] > 0)
          {
              // If clicking on a player-placed piece, allow color change
              col_i = GameBoard[line][column];
              // Update menu to show current color
              DrawVerticalMenu();
          }
          else if (GameBoard[line][column] < 0)
          {
              // If clicking on initial piece, take its color
              col_i = -GameBoard[line][column];
              // Update menu to show current color
              DrawVerticalMenu();
          }
       }
     }
}

void InitializingBoard()
{
    number = 8;
    
    // Initialize piece counters based on initial pieces
    for (int i = 0; i < 8; i++) piecesPlaced[i] = 0;
    
    // Place initial pieces (these don't count toward the 7-piece limit)
    GameBoard[3][3] = -1;  // RED
    GameBoard[4][3] = -2;  // BLUE
    GameBoard[5][1] = -3;  // GREEN
    GameBoard[1][3] = -4;  // YELLOW
    GameBoard[3][8] = -5;  // LIGHTCYAN
    GameBoard[6][8] = -6;  // LIGHTBLUE
    GameBoard[2][7] = -7;  // MAGENTA
    GameBoard[7][5] = -8;  // BLACK (but won't be used as color 0)
}

void DrawingBoard()
{
   int i, j;
   side = width / number;
   top = (getmaxy() - width) / 2; 
   left = (getmaxx() - height) / 2;
   
   setbkcolor(BG); 
   clearviewport(); 
   setcolor(BLUE);
   
   // Draw grid
   for (i = 1; i <= number; i++)
   {
       for (j = 1; j <= number; j++)
       {
           setcolor(WHITE);
           rectangle(left + side * (i - 1), top + side * (j - 1), 
                     left + side * i, top + side * j);
           // Draw piece if exists
           if (GameBoard[i][j] != 0)
           {
               DrawingPiece(i, j, GameBoard[i][j]);
           }
       }
   }
}

int main()
{
   initwindow(1000, 800);
   
   // Draw game title
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
   outtextxy(350, 30, "COLOR PATH GAME");
   
   InitializingBoard();
   DrawingBoard();
   DrawVerticalMenu();  // Draw the menu
   
   GameOver = false;
   
   do
   {
      PlacingPiece();
   }
   while (!GameOver);
   
   getch(); 
   closegraph();
   return 0;
}
