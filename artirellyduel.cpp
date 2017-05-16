
#include "artirellyduel.hpp"

#include "resources.hpp"
#include <stdlib.h>

ArtirellyDuel::ArtirellyDuel() :
    Widget(NULL, 0, 0, 0, 640, 480),
    _ground(this, __IDC__GROUND, 0, 0),
    _player1(this, __IDC__PLAYER1, 0),
    _player2(this, __IDC__PLAYER2, 1),
    _toolbar(this, __IDC__TOOLBAR, 0, 400),
    _bullet(this, __IDC__BULLET, 640, 400) {

    // initialize main window
    gout.open(640, 480);

    // add widgets into queue
    _ground.add(_widgets);
    _toolbar.add(_widgets);
    _player1.add(_widgets);
    _player2.add(_widgets);
    _bullet.add(_widgets);

    // generate a timer event every 25 msec
    gin.timer(25);

    // initialize game
    initialize();
}

void ArtirellyDuel::run() {
    event ev;
    int focus = -1;

    while (gin >> ev) {
        if ((ev.type == ev_mouse) && (ev.button == btn_left)) {
            for (size_t i = 0; i < _widgets.size(); i++) {
                if (_widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                        focus = i;
                } else {
                        _widgets[i]->setFocus(false);
                }
            }
        }
        if (focus != -1) {
            _widgets[focus]->setFocus(true);
            _widgets[focus]->handle(NULL, 0, ev);
        }

        // draw
        for (size_t i = 0; i < _widgets.size(); i++) {
            _widgets[i]->draw();
        }

        gout << refresh;
    }
}

void ArtirellyDuel::updateToolbar() {
    _toolbar._spinButtonPower.setCurrentValue(_currentPlayer->getPower());
    _toolbar._spinButtonAngle.setCurrentValue(_currentPlayer->getAngle());
}


void ArtirellyDuel::initialize() {
  int positionX = 0;
  int positionY = 0;

  // initialize area
  _ground.initialize();

  // generate gravity
  _toolbar._spinButtonGravity.setCurrentValue((rand() % 11) + 5);

  // generate player1 position
  positionX = (rand() % 100) + _player1.getSizeX();
  positionY = _ground.smooth(positionX, _player1.getSizeX() / 2);
  _player1.setPositionX(positionX - (_player1.getSizeX() / 2));
  _player1.setPositionY(_ground.getSizeY() - (positionY + _player1.getSizeY()));
  _player1.setAngle(45);
  _player1.setDisabled(false);

  // generate player2 position
  positionX = _ground.getSizeX() - ((rand() % 100) + _player2.getSizeX());
  positionY = _ground.smooth(positionX, _player2.getSizeX() / 2);
  _player2.setPositionX(positionX - (_player2.getSizeX() / 2));
  _player2.setPositionY(_ground.getSizeY() - (positionY + _player2.getSizeY()));
  _player2.setAngle(45);
  _player2.setDisabled(false);

  // disable bullet
  _bullet.setDisabled(true);

  // set initial state
  if ((rand() % 2) == 0) {
    _state = PLAYER1_SETUP;
  } else {
    _state = PLAYER2_SETUP;
  }

  event ev = { 0, 0, 0, 0, 0, 0};
  handle(NULL, 0, ev);
}

void ArtirellyDuel::handle(Widget * widget, int code, event ev) {
    if (widget != NULL) {
        switch (widget->getId()) {
        case __IDC__TOOLBAR__BUTTON__NEW_GAME : {
            switch (code) {
            case __MESSAGE__OnClick : {
              initialize();
              break;
            }
            }
            break;
        }
        case __IDC__TOOLBAR__SPINBUTTON__ANGLE : {
            SpinButton * spinButton = (SpinButton *)widget;
            _currentPlayer->setAngle(spinButton->getCurrentValue());
            break;
        }
        case __IDC__TOOLBAR__SPINBUTTON__POWER : {
            SpinButton * spinButton = (SpinButton *)widget;
            _currentPlayer->setPower(spinButton->getCurrentValue());
            break;
        }
        // if button click on PASS next state is BULLET_END
        case __IDC__TOOLBAR__BUTTON__PASS: {
            switch (code) {
            case __MESSAGE__OnClick : {
              // set state to BULLET_END
              if ((_state == PLAYER1_SETUP) || (_state == PLAYER2_SETUP)) {
                _state = BULLET_END;
              }
              break;
            }
            }
            break;
        }
        // if button click on FIRE next state is BULLET_FIRED
        case __IDC__TOOLBAR__BUTTON__FIRE: {
            switch (code) {
            case __MESSAGE__OnClick : {
              if ((_state == PLAYER1_SETUP) || (_state == PLAYER2_SETUP)) {
                  // fire bullet
                  _bullet.fire(_currentPlayer->getBarrelEndX(), _currentPlayer->getBarrelEndY(), _currentPlayer->getDirection(), _currentPlayer->getAngle(), _currentPlayer->getPower());

                  // enable bullet
                  _bullet.setDisabled(false);

                  // set state to BULLET_FIRED
                  _state = BULLET_FIRED;
              }
              break;
            }
            }
            break;
        }
        }
    }

    switch (_state) {
    case PLAYER1_SETUP : {
        _currentPlayer = &_player1;
        _player1.setSelected(true);
        _player2.setSelected(false);
        break;
    }
    case PLAYER2_SETUP : {
        _currentPlayer = &_player2;
        _player1.setSelected(false);
        _player2.setSelected(true);
        break;
    }
    case BULLET_FIRED: {
        if (ev.type == ev_timer) {
          // update bullet position with gravity value
          _bullet.update(_toolbar._spinButtonGravity.getCurrentValue() / 2.0);

          if (_bullet.isValid() == false) {
            // set next state to BULLET_END
            _state = BULLET_END;
          } else {
            // bullet is collided by player 1
            if (_player1.isCollided(_bullet.getCurrentPositionX(), _bullet.getCurrentPositionY()) == true) {
                // disable player 1
                _player1.setDisabled(true);

                // set state to game over
                _state = GAME_OVER;

            // bullet is collided by player 2
            } else if (_player2.isCollided(_bullet.getCurrentPositionX(), _bullet.getCurrentPositionY()) == true) {
                // disable player 2
                _player2.setDisabled(true);

                // set state to game over
                _state = GAME_OVER;

             // if bullet is collided by ground at its own position
             } else if (_ground.isCollided(_bullet.getCurrentPositionX(), _bullet.getCurrentPositionY()) == true) {
                // set state to BULLET_BLAST
                _state = BULLET_BLAST;
            }
          }
        }
        break;
    }
    case BULLET_BLAST : {
      if (ev.type == ev_timer) {
        if (_bullet.blast() == true) {
            // make a random blast on ground
            _ground.decreaseAltitude(_bullet.getCurrentPositionX() + ((rand() % _bullet.getStrength()) / 2) - (_bullet.getStrength() / 4), _bullet.getCurrentPositionY() + ((rand() % _bullet.getStrength()) / 2) - (_bullet.getStrength() / 4));
        } else {
            // set state to BULLET_END
            _state = BULLET_END;
        }
      }
      break;
    }
    case BULLET_END : {
      // disable bullet
      _bullet.setDisabled(true);

      if (_currentPlayer->getId() == __IDC__PLAYER1) {
        // set state to PLAYER2_SETUP
        _state = PLAYER2_SETUP;
      } else if (_currentPlayer->getId() == __IDC__PLAYER2) {
        // set state to PLAYER1_SETUP
        _state = PLAYER1_SETUP;
      }
      break;
    }
    case GAME_OVER : {
        _player1.setSelected(false);
        _player2.setSelected(false);

        // disable bullet
        _bullet.setDisabled(true);
        break;
    }
    }

    updateToolbar();
}
