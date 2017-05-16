#ifndef ARTIRELLYDUEL_HPP_INCLUDED
#define ARTIRELLYDUEL_HPP_INCLUDED

#include <vector>

#include "widget.hpp"
#include "ground.hpp"
#include "artirelly.hpp"
#include "bullet.hpp"
#include "toolbar.hpp"

using namespace std;

class ArtirellyDuel : public Widget {
protected:
    vector<Widget *> _widgets;

    Ground _ground;
    Artirelly _player1;
    Artirelly _player2;
    Toolbar _toolbar;

    Bullet _bullet;

    double moment;

    Artirelly * _currentPlayer;

    typedef enum {
      PLAYER1_SETUP,
      PLAYER2_SETUP,
      BULLET_FIRED,
      BULLET_BLAST,
      BULLET_END,
      GAME_OVER
    } states;

    states _state;

    void updateToolbar();

public:
    ArtirellyDuel();

    // initialize game
    void initialize();
    // run game
    void run();

//  virtual void draw() const ;
    virtual void handle(Widget * widget, int code, event ev);
};

#endif // BUTTON_HPP_INCLUDED

