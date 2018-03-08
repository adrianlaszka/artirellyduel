#include "dialog2.hpp"

#define __Dialog2__IDC_LISTVIEW_LEFT 1
#define __Dialog2__IDC_LISTVIEW_RIGHT 2
#define __Dialog2__IDC_BUTTON 3
#define __Dialog2__IDC_LISTVIEW_RESULT 4

Dialog2::Dialog2(Widget * parent, int id, int x, int y, int sx, int sy)
    : Widget(parent, id, x, y, sx, sy),
  _listViewLeft(this, __Dialog2__IDC_LISTVIEW_LEFT, x, y, 100, 180, 6),
  _listViewRight(this, __Dialog2__IDC_LISTVIEW_RIGHT, x + 120, y, 100, 180, 6),
  _button(this, __Dialog2__IDC_BUTTON, x + 240, y + 75, 50, 30, ">>"),
  _listViewResult(this, __Dialog2__IDC_LISTVIEW_RESULT, x + 310, y, 220, 180, 6) {
  _listViewLeft.addValue("Kiss G.");
  _listViewLeft.addValue("Nagy J.");
  _listViewLeft.addValue("Gipsz Jakab");
  _listViewLeft.addValue("Kala Pál");
  _listViewLeft.addValue("Egyip Tomi");
  _listViewRight.addValue("La Ferrari");
  _listViewRight.addValue("BMW M3 E92");
  _listViewRight.addValue("Lada Niva");
}

void Dialog2::add(vector<Widget *> & widgets) {
//  widgets.push_back(this);
  _listViewLeft.add(widgets);
  _listViewRight.add(widgets);
  _button.add(widgets);
  _listViewResult.add(widgets);
}

void Dialog2::handle(Widget * source, int message, event ev) {
  if (_disabled == false) {
    if (source != NULL) {
        switch (source->getId()) {
        case __Dialog2__IDC_BUTTON : {
            if (message == __MESSAGE__OnClick) {
                if ((_listViewLeft.isSelected() == true) && (_listViewRight.isSelected() == true)) {
                  string text = _listViewLeft.getSelectedText() + " - " + _listViewRight.getSelectedText();
                  _listViewResult.addValue(text);
                  _listViewLeft.remove();
                  _listViewRight.remove();
                }
            }
            break;
        }
        }
      }
  }

  Widget::handle(source, message, ev);
}
