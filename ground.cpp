
#include "ground.hpp"

#include <stdlib.h>

#include <stdio.h>

void Ground::generateAltitudes(int min, int max) {
   if ((max - min) == 1) {
     // ..
   } else {
     int p = (rand() % (max - min - 1)) + min + 1;
     int delta = (max - min) / 4;

     _altitudes[p] = ((_altitudes[min] + _altitudes[max]) / 2) - delta + (rand() % ((2 * delta) + 1));
     if (_altitudes[p] < 50) {
       _altitudes[p] = 50;
     }

     generateAltitudes(min, p);
     generateAltitudes(p, max);
   }
}

Ground::Ground(Widget * parent, int id, int x, int y) :
    Widget(parent, id, x, y, 640, 400) {
}

void Ground::draw() const {
  int x = 0;

  gout << color(0, 0, 180);
  gout << move_to(0, 0) << box(_size_x, _size_y);

  gout << color(240, 200, 30);
  for (x = 0; x < _size_x; x++) {
    gout << move_to(_x + x, _y + _size_y - 1) << line_to(_x + x, _y + _size_y - 1 - _altitudes[x]);
  }
}

void Ground::initialize() {
    _altitudes[0] = (rand() % 150) + 50;
    _altitudes[_size_x - 1] = (rand() % 150) + 50;

    generateAltitudes(0, _size_x - 1);
}


int Ground::smooth(int x, int e) {
  int m = _altitudes[x];
  int i = 0;

  for (i = (x - e); i < (x + e); i++) {
    if (_altitudes[i] < m) {
      m = _altitudes[i];
    }
  }

  for (i = (x - e); i < (x + e); i++) {
    _altitudes[i] = m;
  }

  return (m);
}

bool Ground::isCollided(int positionX, int positionY) const {
  bool result = false;

  if ((positionX >= 0) && (positionX < _size_x)) {
    if (_altitudes[positionX] > (_size_y - positionY)) {
        result = true;
    }
  }

  return (result);
}

void Ground::decreaseAltitude(int positionX, int positionY) {
  if ((positionX >= 0) && (positionX < _size_x)) {
    if ((_altitudes[positionX] >= 12) && (isCollided(positionX, positionY) == true)) {
      _altitudes[positionX] = _altitudes[positionX] - 2;
    }
  }
}
