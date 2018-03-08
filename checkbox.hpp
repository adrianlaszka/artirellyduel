#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class CheckBox : public Widget {
protected:
    bool _checked;
public:
    CheckBox(Widget * parent, int id, int x, int y, int sx, int sy);
    virtual void draw() const ;
    virtual void handle(Widget * source, int message, event ev);
    virtual bool is_checked() const ;
};


#endif // CHECKBOX_HPP_INCLUDED
