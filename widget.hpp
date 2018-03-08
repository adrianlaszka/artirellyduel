#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include <stdio.h>
#include <vector>

#include "graphics.hpp"

using namespace std;
using namespace genv;

#define __MESSAGE__OnClick 1
#define __MESSAGE__OnFocus 2

class Widget {
protected:
    Widget * _parent;
    int _x, _y, _size_x, _size_y;
    int _id;
    bool _disabled;
    bool _focus;
    bool _selected;
    bool _border;

public:
    Widget(Widget * parent, int id, int x, int y, int sx, int sy);
    virtual ~Widget();
    virtual bool is_selected(int mouse_x, int mouse_y) const;

    int getId() const;
    void setDisabled(bool disabled);
    void setFocus(bool focus);
    void setSelected(bool selected);
    void setBorder(bool border);

    virtual void add(vector<Widget *> & widgets);

    virtual void draw() const;
    virtual void handle(Widget * source, int message, event ev);
};


#endif // WIDGETS_HPP_INCLUDED
