#ifndef SPINBUTTON_HPP_INCLUDED
#define SPINBUTTON_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include "button.hpp"
#include "textbox.hpp"

class SpinButton : public Widget {
protected:
  int _currentValue;
  int _minValue;
  int _maxValue;

  TextBox _textBox;
  Button _buttonDown;
  Button _buttonUp;

public:

    SpinButton(Widget * parent, int id, int x, int y, int sx, int sy, int currentValue, int minValue, int maxValue);
    virtual void add(vector<Widget *> & widgets);
    virtual void handle(Widget * source, int message, event ev);
};


#endif // SPINBUTTON_HPP_INCLUDED
