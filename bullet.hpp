
#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "widget.hpp"

class Bullet : public Widget {
protected:
    // start position x
    int _startPositionX;
    // start position y
    int _startPositionY;

    // start position x
    int _currentPositionX;
    // start position y
    int _currentPositionY;

    // start speed x
    double _vx;
    // start speed y
    double _vy;

    // direction
    int _direction;
    // angle
    int _angle;

    // moment
    double _moment;

    // strength
    int _strength;

public:
    Bullet(Widget * parent, int id, int size_x, int size_y);

    virtual void draw() const;

    // return true if bullet in widget area
    bool isValid() const;

    // get current position x
    int getCurrentPositionX() const;
    // get current position y
    int getCurrentPositionY() const;
    // get strength
    int getStrength() const;

    // fire bullet
    void fire(int positionX, int positionY, int direction, int angle, int power);
    // update position
    void update(double gravity);

    // decrease strength and return false when strength is 0
    bool blast();
};

#endif // BULLET_HPP_INCLUDED
