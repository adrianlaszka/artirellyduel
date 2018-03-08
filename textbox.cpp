#include "textbox.hpp"

TextBox::TextBox(Widget * parent, int id, int x, int y, int sx, int sy)
    : Widget(parent, id, x + 2, y + 2, sx - 4, sy - 4) {
	_edit = true;
}

void TextBox::draw() const {
    Widget::draw();
    gout << move_to(_x + 5, _y + 18) << ((_disabled == false) ? color(255,255,255) : color(192,192,192)) << text(_text);
}

void TextBox::handle(Widget * source, int message, event ev) {
  if (_disabled == false) {
	if (_edit == true) {
		if (ev.type == ev_key) {
			switch (ev.keycode) {
			case key_escape :
			case key_enter : {
				_focus = false;
				break;
			}
			case key_backspace : {
				_text = _text.substr(0, _text.length() - 1);
				break;
			}
			default : {
				if ((ev.keycode >= 32) && (ev.keycode < 127)) {
					string t = _text + (char)ev.keycode;
					if (gout.twidth(t) < (_size_x - 14)) {
					  _text = t;

					}
				}
				break;
			}
			}
		}
	}
  }

  Widget::handle(source, message, ev);
}

const string & TextBox::getText() const {
    return (_text);
}


void TextBox::setText(const string & text) {
  _text = text;
}

void TextBox::setEdit(bool edit) {
  _edit = edit;
}
