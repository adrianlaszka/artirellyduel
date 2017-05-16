
#include "artirelly.hpp"

#include "resources.hpp"
#include <math.h>

Artirelly::Artirelly(Widget * parent, int id, int direction) :
    Widget(parent, id, 0, 0, __ARTIRELLY_SIZE_X, __ARTIRELLY_SIZE_Y) {
  _angle = 0;
  _power = 50;
  _direction = direction;
}

void Artirelly::draw() const {
  double vx = 0;
  double vy = 0;
  double positionX = 0;
  double positionY = 0;
  int i = 0;
  int angle = 0;

  if (_selected == true) {
    gout << color(140, 200, 120);
  } else {
    if (_disabled == true) {
        gout << color(40, 40, 20);
    } else {
      gout << color(140, 140, 120);
    }
  }
  gout << move_to(_x, _y) << box(_size_x, _size_y);

  if (_disabled == false) {
      gout << color(80, 80, 80);
      gout << move_to(_x + (_size_x / 2) - (_size_x / 6), _y - (_size_y / 2)) << box(2 * (_size_x / 6), _size_y / 2);

      angle = _angle;
      if (_direction == 1) {
        angle = 180 - angle;
      }

      vx = cos(DEGREE_TO_RAD(angle)) * __ARTIRELLY_BARREL_LENGTH;
      vy = sin(DEGREE_TO_RAD(angle)) * __ARTIRELLY_BARREL_LENGTH;

      gout << color(80, 80, 80);
      positionX = _x + (_size_x / 2);
      positionY = _y - (_size_y / 2);
      for (i = 0; i < __ARTIRELLY_BARREL_LENGTH; i++) {
        gout << move_to(positionX - 1 , positionY - 1) << box(3, 3);
        positionX = positionX + (vx / __ARTIRELLY_BARREL_LENGTH);
        positionY = positionY - (vy / __ARTIRELLY_BARREL_LENGTH);
      }
  }
}

double Artirelly::getBarrelEndX() const {
  double result = 0.0;

  int angle = 0;
  angle = _angle;
  if (_direction == 1) {
    angle = 180 - angle;
  }

  result = cos(DEGREE_TO_RAD(angle)) * __ARTIRELLY_BARREL_LENGTH;

  result = _x + (_size_x / 2) + result;
  printf("BARREL X %lf\n", result);

  return (result);
}

double Artirelly::getBarrelEndY() const {
  double result = 0.0;

  int angle = 0;
  angle = _angle;
  if (_direction == 1) {
    angle = 180 - angle;
  }

  result = sin(DEGREE_TO_RAD(angle)) * __ARTIRELLY_BARREL_LENGTH;;

  result = _y - (_size_y / 2) - result;

  printf("BARREL Y %lf\n", result);

  return (result);
}


int Artirelly::getAngle() const {
    return (_angle);
}

void Artirelly::setAngle(int angle) {
    _angle = angle;
}

int Artirelly::getPower() const {
    return (_power);
}

void Artirelly::setPower(int power) {
    _power = power;
}

int Artirelly::getDirection() const {
    return (_direction);
}

bool Artirelly::isCollided(int positionX, int positionY) const {
  return (is_selected(positionX, positionY));
}
