
#include "toolbar.hpp"

#include "resources.hpp"

Toolbar::Toolbar(Widget * parent, int id, int x, int y) :
    Widget(parent, id, x, y, 640, 80),
    _buttonNewGame(this, __IDC__TOOLBAR__BUTTON__NEW_GAME, x + 550, y + 10, 80, 30, "NEW GAME"),
    _labelAngle(this, __IDC__TOOLBAR__LABEL_ANGLE, x + 10, y + 10, 80, 30),
    _spinButtonAngle(this, __IDC__TOOLBAR__SPINBUTTON__ANGLE, x + 90, y + 10, 120, 30, 0, 0, 90),
    _labelPower(this, __IDC__TOOLBAR__LABEL_POWER, x + 10, y + 40, 80, 30),
    _spinButtonPower(this, __IDC__TOOLBAR__SPINBUTTON__POWER, x + 90, y + 40, 120, 30, 10, 10, 100),
    _labelGravity(this, __IDC__TOOLBAR__LABEL_GRAVITY, x + 320, y + 10, 80, 30),
    _spinButtonGravity(this, __IDC__TOOLBAR__SPINBUTTON__GRAVITY, x + 400, y + 10, 120, 30, 10, 1, 50),
    _buttonFire(this, __IDC__TOOLBAR__BUTTON__FIRE, x + 230, y + 10, 80, 30, "FIRE"),
    _buttonPass(this, __IDC__TOOLBAR__BUTTON__PASS, x + 230, y + 40, 80, 30, "PASS") {
    _labelAngle.setText("ANGLE");
    _labelAngle.setDisabled(true);
    _labelAngle.setBorder(false);
    _labelPower.setText("POWER");
    _labelPower.setDisabled(true);
    _labelPower.setBorder(false);
    _labelGravity.setText("GRAVITY");
    _labelGravity.setDisabled(true);
    _labelGravity.setBorder(false);
}

void Toolbar::add(vector<Widget *> & widgets) {
  widgets.push_back(this);
  _buttonNewGame.add(widgets);
  _labelAngle.add(widgets);
  _spinButtonAngle.add(widgets);
  _labelPower.add(widgets);
  _spinButtonPower.add(widgets);
  _labelGravity.add(widgets);
  _spinButtonGravity.add(widgets);
  _buttonFire.add(widgets);
  _buttonPass.add(widgets);
}
