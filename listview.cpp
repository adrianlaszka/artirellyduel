#include "listview.hpp"

#include <iostream>

ListView::ListView(Widget * parent, int id, int x, int y, int sx, int sy, unsigned int number)
    : Widget(parent, id, x, y, sx, sy) {
	_number = number;
	_position = 0;
	_selected = 0;
	for (unsigned int i = 0; i < _number; i++) {
		TextBox * _textBox = new TextBox(this, i, x, y + (i * (sy / number)), sx, (sy / number));
		_textBoxes.push_back(_textBox);
		if (i == 0) {
            _textBox->setSelected(true);
		}
		_textBox->setBorder(false);
		_textBox->setEdit(false);
	}
}

ListView::~ListView() {
}

void ListView::add(vector<Widget *> & widgets) {
  widgets.push_back(this);
	for (unsigned int i = 0; i < _number; i++) {
		_textBoxes[i]->add(widgets);
	}
}

void ListView::draw() const {
  Widget::draw();

    for (unsigned int i = 0; i < _number; i++) {
      _textBoxes[i]->setFocus(false);
      _textBoxes[i]->setSelected(false);
    }
    if ((_selected < _values.size()) && (_selected < _number)) {
      _textBoxes[_selected]->setSelected(true);
    }

	for (unsigned int i = 0; i < _number; i++) {
		if ((i + _position) < _values.size()) {
			_textBoxes[i]->setText(_values[i + _position]);
		} else {
			_textBoxes[i]->setText("");
		}
	}
}

void ListView::handle(Widget * source, int message, event ev) {

  if (_disabled == false) {
	bool up = false;
	bool down = false;

    if (ev.type == ev_key) {
        switch (ev.keycode) {
        case key_pgup :
        case key_up :
        case key_left : {
			up = true;
            break;
        }
        case key_pgdn :
        case key_down :
        case key_right : {
			down = true;
            break;
        }
        }
    }

    if (ev.type == ev_mouse) {
        switch (ev.button) {
        case btn_wheelup : {
			up = true;
            break;
        }
        case btn_wheeldown : {
			down = true;
            break;
        }
        }
    }

    if (down == true) {
        if ((_selected < (_number - 1)) && (_selected < (_values.size() - 1))) {
          _selected = _selected + 1;
        } else {
          if ((_position + _number) < _values.size()) {
            _position = _position + 1;
          }
        }
    }

    if (up== true) {
      if (_selected > 0) {
        _selected = _selected - 1;
      } else {
        if (_position > 0) {
          _position = _position - 1;
        }
      }
    }


    if (source != NULL) {
        if (message == __MESSAGE__OnFocus) {
            _selected = source->getId();

            if (_selected >= _values.size()) {
              _selected = _values.size() - 1;
            }
        }
    }

  }
}

bool ListView::isSelected() const {
  return ((_selected >= 0) && (_selected < _number));
}

const string & ListView::getSelectedText() const {
  return (_values[_selected]);
}



void ListView::remove() {
    vector<string>::iterator it = _values.begin();

    for (unsigned int i = 0; i < (_position + _selected); i++) {
      it++;
    }

    if (_position >= (_values.size() - _number)) {
      if (_position > 0) {
        _position = _position - 1;
      }
    }

    if (_selected == (_values.size() - 1)) {
      _selected = _selected - 1;
    }

    if (it != _values.end()) {
      _values.erase(it);
    }
}

void ListView::addValue(const string & value) {
	_values.push_back(value);
}
