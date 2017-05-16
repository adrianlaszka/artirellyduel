#ifndef TOOLBARD_HPP_INCLUDED
#define TOOLBARD_HPP_INCLUDED

#include "widget.hpp"
#include "button.hpp"
#include "spinbutton.hpp"
#include "textbox.hpp"

class Toolbar : public Widget {
public:
    Button _buttonNewGame;

    TextBox _labelAngle;
    SpinButton _spinButtonAngle;
    TextBox _labelPower;
    SpinButton _spinButtonPower;
    TextBox _labelGravity;
    SpinButton _spinButtonGravity;
    Button _buttonFire;
    Button _buttonPass;

    Toolbar(Widget * parent, int id, int x, int y);

    virtual void add(vector<Widget *> & widgets);
};

#endif // TOOLBARD_HPP_INCLUDED



