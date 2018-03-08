#include "spinbutton.hpp"

#define __SpinButton__IDC_TEXT 1
#define __SpinButton__IDC_DOWN 2
#define __SpinButton__IDC_UP 3

SpinButton::SpinButton(Widget * parent, int id, int x, int y, int sx, int sy, int currentValue, int minValue, int maxValue)
    : Widget(parent, id, x, y, sx, sy),
    _textBox(this, __SpinButton__IDC_TEXT, x + 30, y, sx - 60, sy),
  _buttonDown(this, __SpinButton__IDC_DOWN, x, y, 30, sy, "<"),
  _buttonUp(this, __SpinButton__IDC_UP, x + sx - 30, y, 30, sy, ">") {
  char buffer[128];

  _currentValue = currentValue;
  _minValue = minValue;
  _maxValue = maxValue;

  _textBox.setDisabled(true);
  sprintf(buffer, "%d", _currentValue);
  _textBox.setText(buffer);

  _border = false;
}

void SpinButton::add(vector<Widget *> & widgets) {
  widgets.push_back(this);
  _textBox.add(widgets);
  _buttonDown.add(widgets);
  _buttonUp.add(widgets);
}

void SpinButton::handle(Widget * source, int message, event ev) {
  if (_disabled == false) {
      char buffer[128];

      if ((ev.type == ev_key) && ((ev.keycode == key_pgup) || (ev.keycode == key_up) || (ev.keycode == key_right))) {
        _currentValue = _currentValue + 1;
      }
      if ((ev.type == ev_key) && ((ev.keycode == key_pgdn) || (ev.keycode == key_down) || (ev.keycode == key_left))) {
        _currentValue = _currentValue - 1;
      }

      if (source != NULL) {
          switch (source->getId()) {
          case __SpinButton__IDC_DOWN : {
            if (message == __MESSAGE__OnClick) {
              _currentValue = _currentValue - 1;
            }
            break;
          }
          case __SpinButton__IDC_UP : {
            if (message == __MESSAGE__OnClick) {
              _currentValue = _currentValue + 1;
            }
            break;
          }
          }
      }

      if (_currentValue < _minValue) {
        _currentValue = _minValue;
      }
      if (_currentValue > _maxValue) {
        _currentValue = _maxValue;
      }

      if (_currentValue == _minValue) {
        _buttonDown.setFocus(false);
        _buttonDown.setDisabled(true);
      } else {
        _buttonDown.setDisabled(false);
      }
      if (_currentValue == _maxValue) {
        _buttonUp.setFocus(false);
        _buttonUp.setDisabled(true);
      } else {
        _buttonUp.setDisabled(false);
      }

      sprintf(buffer, "%d", _currentValue);
      _textBox.setText(buffer);
  }

  Widget::handle(source, message, ev);
}
