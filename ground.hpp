#ifndef GROUND_HPP_INCLUDED
#define GROUND_HPP_INCLUDED

#include "widget.hpp"

class Ground : public Widget {
protected:
    int _altitudes[640];

    void generateAltitudes(int min, int max);

public:
    Ground(Widget * parent, int id, int x, int y);

    virtual void draw() const;

    void initialize();
    int smooth(int x, int e);

    // return true if position is collied with ground
    bool isCollided(int positionX, int positionY) const;
    // decrease altitude at specific position
    void decreaseAltitude(int positionX, int positionY);
};

#endif // GROUND_HPP_INCLUDED


