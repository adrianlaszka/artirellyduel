#ifndef DIALOG2_HPP_INCLUDED
#define DIALOG2_HPP_INCLUDED

#include "widget.hpp"
#include "button.hpp"
#include "listview.hpp"

class Dialog2 : public Widget {
protected:
  ListView _listViewLeft;
  ListView _listViewRight;
  Button _button;
  ListView _listViewResult;

public:
    Dialog2(Widget * parent, int id, int x, int y, int sx, int sy);
    virtual void add(vector<Widget *> & widgets);
    virtual void handle(Widget * source, int message, event ev);
};

#endif // DIALOG2_HPP_INCLUDED

