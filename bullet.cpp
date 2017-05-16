
#include "bullet.hpp"

#include "resources.hpp"
#include <math.h>

Bullet::Bullet(Widget * parent, int id, int size_x, int size_y) :
    Widget(parent, id, 0, 0, size_x, size_y) {
    _disabled = false;
    _startPositionX = 0;
    _startPositionY = 0;
    _currentPositionX = 0;
    _currentPositionY = 0;
    _vx = 0;
    _vy = 0;
    _angle = 0.0;
    _moment = 1.0;
    _strength = 0;
}

bool Bullet::isValid() const {
  return ((_currentPositionX > 1) && (_currentPositionX < (_size_x - 1)));
}


int Bullet::getCurrentPositionX() const {
    return (_currentPositionX);
}

int Bullet::getCurrentPositionY() const {
    return (_currentPositionY);
}

int Bullet::getStrength() const {
    return (_strength);
}

void Bullet::draw() const {
  // draw bullet if it is not disabled and valid
  if (_disabled == false) {
      int posX = _currentPositionX;
      int posY = _currentPositionY;

      if (posY < 2) {
        posY = 2;
        gout << color(0, 200, 0);
      } else {
        gout << color(255, 255, 255);
      }

      if (((posX > 1) && (posX < (_size_x - 1))) && ((posY > 1) && (posY < (_size_y - 1)))) {
        gout << move_to(posX - 1, posY - 1) << box(3, 3);
      }
  }
}

void Bullet::fire(int positionX, int positionY, int direction, int angle, int power) {
  _currentPositionX = _startPositionX = positionX;
  _currentPositionY = _startPositionY = positionY;
  _direction = direction;
  _angle = angle;

  // calculate vx and vy (as start speed) based on power and angle values
  _vx = power * cos(DEGREE_TO_RAD(_angle));
  _vy = power * sin(DEGREE_TO_RAD(_angle));

  // reset time
  _moment = 0.0;
  _strength = 50;
}

void Bullet::update(double gravity) {
  // increment moment
  _moment = _moment + 0.05;

  // calculate current position
  if (_direction == 0) {
    _currentPositionX = _startPositionX + (_vx * _moment * cos(DEGREE_TO_RAD(_angle)));
  } else {
    _currentPositionX = _startPositionX - (_vx * _moment * cos(DEGREE_TO_RAD(_angle)));
  }
  _currentPositionY = _startPositionY - ((_vy * _moment * sin(DEGREE_TO_RAD(_angle))) - ((gravity / 2.0) * _moment * _moment));
}

bool Bullet::blast() {
  if (_strength > 0) {
    _strength = _strength - 1;
  }
  return (_strength != 0);
}
