#include <thread>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <string>

bool finished = false;

double distance(int x1, int y1, int x2, int y2)
{
  return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

std::string twoDigits(int n)
{
  if (n < 10) {
    return "0" + std::to_string(n);
  } else {
    return std::to_string(n);
  }
}


int main()
{
  struct Cat
  {
    int x, y;
    int direction;
  };
  Cat cat;
  cat.x = 0;
  cat.y = 0;
  cat.direction = 1;
  struct Mouse
  {
    int x, y;
    int direction;
  };
  Mouse mouse;
  mouse.x = 50;
  mouse.y = 50;
  mouse.direction = -1;

  std::thread catThread([&]
                        {
  while (!finished) {

    gotoxy(10, 10);
    std::cout << "Gato: " << twoDigits(cat.x) << ", " << twoDigits(cat.y) << std::endl;

    char c = getch();
    if (c == 'a') {
      if(cat.x == 0) continue;
      cat.x -= 1;
    } else if (c == 'd') {
      if(cat.x == 99) continue;
      cat.x += 1;
    } else if (c == 'w') {
      if(cat.y == 99) continue;
      cat.y += 1;
    } else if (c == 's') {
      if(cat.y == 0) continue;
      cat.y -= 1;
    }

  } });

  std::thread mouseThread([&]
                          {
  while (!finished) {
    mouse.x += mouse.direction;
    if (mouse.x <= 0 || mouse.x >= 99) {
      mouse.direction *= -1;
    }

    if (distance(cat.x, cat.y, mouse.x, mouse.y) < 2.0) {
        gotoxy(10, 15);
        std::cout << "¡El gato ha atrapado al ratón!" << std::endl;
        finished = true;
        break;
    }

    gotoxy(10, 5);
    std::cout << "Ratón: " << twoDigits(mouse.x) << ", " << twoDigits(mouse.y) << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  } });

  catThread.join();
  mouseThread.join();

  return 0;
}
