#include <bits/stdc++.h>
#include <conio.h>   // For kbhit and getch
#include <windows.h> // For console cursor control

using namespace std;

#define MAX_LENGTH 1000

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

// Function to initialize the screen dimensions
void initScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Point structure to represent coordinates
struct Point {
    int xCoord, yCoord;

    Point() {}

    Point(int x, int y) {
        xCoord = x;
        yCoord = y;
    }
};

// Snake class
class Snake {
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];

    Snake(int x, int y) {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength() {
        return length;
    }

    void changeDirection(char newDirection) {
        if (newDirection == DIR_UP && direction != DIR_DOWN) {
            direction = newDirection;
        } else if (newDirection == DIR_DOWN && direction != DIR_UP) {
            direction = newDirection;
        } else if (newDirection == DIR_LEFT && direction != DIR_RIGHT) {
            direction = newDirection;
        } else if (newDirection == DIR_RIGHT && direction != DIR_LEFT) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        switch (direction) {
            case DIR_UP:
                body[0].yCoord--;
                break;
            case DIR_DOWN:
                body[0].yCoord++;
                break;
            case DIR_RIGHT:
                body[0].xCoord++;
                break;
            case DIR_LEFT:
                body[0].xCoord--;
                break;
        }

        // Snake bites itself
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        // Snake eats food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }

        return true;
    }
};

// Board class
class Board {
    Snake* snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board() {
        spawnFood();
        snake = new Snake(10, 10);
        score = 0;
    }

    ~Board() {
        delete snake;
    }

    int getScore() {
        return score;
    }

    void spawnFood() {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    void displayCurrentScore() {
        gotoxy(consoleWidth / 2, 0);
        cout << "Current Score: " << score;
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void draw() {
        system("cls");
        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        displayCurrentScore();
    }

    bool update() {
        bool isAlive = snake->move(food);
        if (!isAlive) {
            return false;
        }

        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();
        }

        return true;
    }

    void getInput() {
        if (kbhit()) {
            int key = getch();

            if (key == 224) { // Special key prefix for arrow keys
                key = getch(); // Get actual keycode
                switch (key) {
                    case 72: // Up arrow
                        snake->changeDirection(DIR_UP);
                        break;
                    case 75: // Left arrow
                        snake->changeDirection(DIR_LEFT);
                        break;
                    case 80: // Down arrow
                        snake->changeDirection(DIR_DOWN);
                        break;
                    case 77: // Right arrow
                        snake->changeDirection(DIR_RIGHT);
                        break;
                }
            }
        }
    }
};

// Main function
int main() {
    srand(time(0));
    initScreen();
    Board* board = new Board();

    while (board->update()) {
        board->getInput();
        board->draw();
        Sleep(100); // Delay for smoother gameplay
    }

    cout << "Game Over" << endl;
    cout << "Final Score: " << board->getScore() << endl;

    delete board;
    return 0;
}



/*
I Am not move the keys of my keyboard #include <bits/stdc++.h>
#include <conio.h> // for key pressing keyboard hit
#include <windows.h> // coordinate systems dram in window

using namespace std;

#define MAX_LENGTH 1000 // macro

//Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';  // these are read only variable

int consoleWidth, consoleHeight; // to show current score


void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // method, gives cosole handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;  // to store buffering
    GetConsoleScreenBufferInfo(hConsole, &csbi);  // buffer information

    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;  // to set the len and bred of console window
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;


}

struct Point
{
    int xCoord;
    int yCoord;

    Point(){
    }

    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};

class Snake
{
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];
    Snake(int x, int y)
    {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }


    int getLength()
    {
        return length;
    }

    void changeDirection(char newDirection)
    {
        if(newDirection == DIR_UP && direction != DIR_DOWN) // up hai down nhi ja skta
        {
            direction = newDirection;
        }else if(newDirection == DIR_DOWN && direction != DIR_UP)
        {
            direction = newDirection;
        }else if(newDirection == DIR_LEFT && direction != DIR_RIGHT)
        {
            direction = newDirection;

        }else if(newDirection == DIR_RIGHT && direction != DIR_LEFT)
        {
            direction = newDirection;
        }
    }

     // To move the snake

    bool move(Point food)
    {
        for(int i= length - 1; i>=0; i--) // length move to 4 --> 3 the snake is running
        {
            body[i] = body[i-1];
        }

        // for head node

        switch(direction)
        {
            int val;
        case DIR_UP:
            val = body[0].yCoord;
            body[0].yCoord = val - 1;
            break;
        case DIR_DOWN:
            val = body[0].yCoord;
            body[0].yCoord = val + 1;
            break;

        case DIR_RIGHT:
            val = body[0].xCoord;
            body[0].xCoord = val + 1;
            break;

        case DIR_LEFT:
            val = body[0].xCoord;
            body[0].xCoord = val - 1;
            break;
        }

        // snake bit itself

        for(int i=1; i<length; i++)
        {
            if (body[0].xCoord < 0 || body[0].xCoord >= consoleWidth ||
    body[0].yCoord < 0 || body[0].yCoord >= consoleHeight) {
    return false;
}
        }

        // snake eats food
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length -1].xCoord, body[length - 1].yCoord);
            length++;
        }

        // Snake bit anything then return true

        return true;
    }
};


class Board
{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board()
    {
       spawnFood();
        snake = new Snake(10, 10); // direction
        score = 0;
    }

    ~Board()
    {
        delete[] snake;
    }

    int getScore()
    {
        return score;
    }

    void spawnFood()
    {
        int x = rand() % (consoleWidth - 1);  // initize my x and y coordinates
        int y = rand() % (consoleHeight - 1);
        food = Point(x,y);
    }

    // to call repeatedly the spawnFood function to provide the food of snake with the help of
    ///

    void gotoxy(int x, int y)  // for solve like coordinates for eg your coord is (2,4) then resolve this issuee
    {
        COORD coord; // this is class COORD
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // to point the your cursor particular point
    }

    void draw()
    {
        system("cls"); // to clear screen
        for(int i=0; i<snake->getLength(); i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;
    }

    bool update()
    {
       bool isAlive = snake->move(food);
       if(isAlive == false)
       {
           return false;
       }

        // snake eats food  bar bar khata rhega food
        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;
            spawnFood();
        }

       return true;
    }

    void getInput()
    {
        if(kbhit())
        {
            int key = getch();
            if(key == 'w' || key == 'W')
            {
                snake->changeDirection(DIR_UP);
            }
            else if(key == 'a' || key == 'A')
            {
                snake->changeDirection(DIR_LEFT);
            }
            else if(key == 's' || key == 'S')
            {
                snake->changeDirection(DIR_DOWN);
            }
            else if(key == 'd' || key == 'D')
            {
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }

};

int main(){
    srand(time(0));
    initScreen();
    Board *board = new Board();

    while(board->update())
    {
        board->getInput();
        board->draw();
        Sleep(100);
    }

    cout << "Game Over" << endl;
    delete board;
    return 0;
}*/
