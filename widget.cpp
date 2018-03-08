#include "widget.hpp"

Widget::Widget(Widget * parent, int id, int x, int y, int sx, int sy)
{
  _parent = parent;
  _id = id;
  _x = x;
  _y = y;
  _size_x = sx;
  _size_y = sy;
  _disabled = false;
  _focus = false;
  _selected = false;
  _border = true;
}

Widget::~Widget() {
}

bool Widget::is_selected(int mouse_x, int mouse_y) const
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}

int Widget::getId() const {
  return (_id);
}

void Widget::setDisabled(bool disabled) {
  _disabled = disabled;
}

void Widget::setFocus(bool focus) {
  _focus = focus;
  if (_focus == true) {
    event e = {0, 0, 0, 0, 0, 0};
    handle(this, __MESSAGE__OnFocus, e);
  }
}

void Widget::setSelected(bool selected) {
  _selected = selected;
}

void Widget::setBorder(bool border) {
  _border = border;
}

void Widget::add(vector<Widget *> & widgets) {
  widgets.push_back(this);
}

void Widget::draw() const {
  if (_disabled == false) {
      if ((_focus == true) || (_selected == true)) {
        gout << move_to(_x - 1, _y - 1) << color(0,200,200) << box(_size_x + 2, _size_y + 2);
      } else {
        gout << move_to(_x - 1, _y - 1) << color(0,0,0) << box(_size_x + 2, _size_y + 2);
      }
  }
  if (_border == true) {
    gout << move_to(_x, _y) << ((_disabled == false) ? color(255,255,255) : color(192,192,192)) << box(_size_x, _size_y);
    gout << move_to(_x + 2, _y + 2) << color(0,0,0) << box(_size_x - 4, _size_y - 4);
  }
}

void Widget::handle(Widget * source, int message, event ev) {
  if (_parent != NULL) {
    _parent->handle(source, message, ev);
  }
}



