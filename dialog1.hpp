#ifndef DIALOG1_HPP_INCLUDED
#define DIALOG1_HPP_INCLUDED

#include "widget.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "listview.hpp"

class Dialog1 : public Widget {
protected:
  TextBox _textBox;
  Button _buttonAdd;
  Button _buttonRemove;
  ListView _listView;

public:
    Dialog1(Widget * parent, int id, int x, int y, int sx, int sy);
    virtual void add(vector<Widget *> & widgets);
    virtual void handle(Widget * source, int message, event ev);
};


#endif // DIALOG1_HPP_INCLUDED

