#include "dialog1.hpp"

#define __Dialog1__IDC_TEXTBOX 1
#define __Dialog1__IDC_BUTTON_ADD 2
#define __Dialog1__IDC_BUTTON_REMOVE 3
#define __Dialog1__IDC_LISTVIEW 4

Dialog1::Dialog1(Widget * parent, int id, int x, int y, int sx, int sy)
    : Widget(parent, id, x, y, sx, sy),
  _textBox(this, __Dialog1__IDC_TEXTBOX, x, y, 200, 30),
  _buttonAdd(this, __Dialog1__IDC_BUTTON_ADD, x + 220, y, 150, 30, "Add"),
  _buttonRemove(this, __Dialog1__IDC_BUTTON_REMOVE, x + 220, y + 50, 150, 30, "Remove"),
  _listView(this, __Dialog1__IDC_LISTVIEW, x, y + 50, 200, 180, 6) {
	_listView.addValue("Bekescsaba");
	_listView.addValue("Budapest");
	_listView.addValue("Debrecen");
	_listView.addValue("Eger");
	_listView.addValue("Gyor");
	_listView.addValue("Kaposvar");
	_listView.addValue("Kecskemet");
	_listView.addValue("Miskolc");
	_listView.addValue("Nyiregyhaza");
	_listView.addValue("Pecs");
	_listView.addValue("Salgotarjan");
	_listView.addValue("Szeged");
	_listView.addValue("Szekszard");
	_listView.addValue("Szekesfehervar");
	_listView.addValue("Szolnok");
	_listView.addValue("Szombathely");
	_listView.addValue("Tatabanya");
	_listView.addValue("Veszprem");
	_listView.addValue("Zalaegerszeg");
}

void Dialog1::add(vector<Widget *> & widgets) {
  widgets.push_back(this);
  _textBox.add(widgets);
  _buttonAdd.add(widgets);
  _buttonRemove.add(widgets);
  _listView.add(widgets);
}

void Dialog1::handle(Widget * source, int message, event ev) {
  if (_disabled == false) {
      if (source != NULL) {
        switch (source->getId()) {
        case __Dialog1__IDC_BUTTON_ADD : {
            if (message == __MESSAGE__OnClick) {
                string text = _textBox.getText();

                if (text.length() > 0) {
                  _listView.addValue(text);
                }
            }
            break;
        }
        case __Dialog1__IDC_BUTTON_REMOVE : {
            if (message == __MESSAGE__OnClick) {
                _listView.remove();
            }
            break;
        }
        }
      }
  }

  Widget::handle(source, message, ev);
}
