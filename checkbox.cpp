#include "checkbox.hpp"

CheckBox::CheckBox(Widget * parent, int id, int x, int y, int sx, int sy)
    : Widget(parent, id, x + 2, y + 2, sx - 4, sy - 4)
{
    _checked=false;
}

void CheckBox::draw() const
{
    Widget::draw();
    if (_checked) {
        gout << ((_disabled == false) ? color(255,255,255) : color(192,192,192));
        gout << move_to(_x+4, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+5, _y+4) << line(_size_x-8, _size_y-8);
        gout << move_to(_x+_size_x-4, _y+4) << line(-_size_x+8, _size_y-8);
        gout << move_to(_x+_size_x-5, _y+4) << line(-_size_x+8, _size_y-8);
    }
}

void CheckBox::handle(Widget * source, int message, event ev)
{
  if (_disabled == false) {
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ')) {
            _checked = !_checked;
    }
    if (ev.type == ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left) {
        _checked = !_checked;
    }
  }

  Widget::handle(source, message, ev);
}

bool CheckBox::is_checked() const
{
    return _checked;
}
