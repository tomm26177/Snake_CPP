

#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <iostream>
#include <unistd.h>

    using namespace std;

const int WIDTH = 50;
const int HEIGHT = 20;

int snakeX, snakeY;
int fruitX, fruitY;
int score;

int tailX[100], tailY[100];
int nTail = 0;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);
  srand(time(NULL));
  dir = STOP;
  snakeX = WIDTH / 2;
  snakeY = HEIGHT / 2;
  fruitX = rand() % WIDTH;
  fruitY = rand() % HEIGHT;
  score = 0;
}

void Draw() {
  clear();
  for (int i = 0; i < WIDTH + 2; i++)
    mvprintw(0, i, "#");
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (j == 0)
        mvprintw(i + 1, j, "#");
      if (i == snakeY && j == snakeX)
        mvprintw(i + 1, j, "O");
      else if (i == fruitY && j == fruitX)
        mvprintw(i + 1, j, "F");
      else {
        bool printTail = false;
        for (int k = 0; k < nTail; k++) {
          if (tailX[k] == j && tailY[k] == i) {
            mvprintw(i + 1, j, "o");
            printTail = true;
          }
        }
        if (!printTail)
          mvprintw(i + 1, j, " ");
      }
      if (j == WIDTH - 1)
        mvprintw(i + 1, j + 1, "#");
    }
  }
  for (int i = 0; i < WIDTH + 2; i++)
    mvprintw(HEIGHT + 1, i, "#");
  mvprintw(HEIGHT + 2, 0, "Score: %d", score);
  refresh();
}

void Input() {
  keypad(stdscr, TRUE);
  halfdelay(1);
  int c = getch();
  switch (c) {
  case KEY_LEFT:
    dir = LEFT;
    break;
  case KEY_RIGHT:
    dir = RIGHT;
    break;
  case KEY_UP:
    dir = UP;
    break;
  case KEY_DOWN:
    dir = DOWN;
    break;
  case 27:
    endwin();
    exit(0);
    break;
  }
}

void Logic() {
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = snakeX;
  tailY[0] = snakeY;
  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
  switch (dir) {
  case LEFT:
    snakeX--;
    break;
  case RIGHT:
    snakeX++;