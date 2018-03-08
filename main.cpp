//Magic Widgets! :D
//MIT LICENSE - so feel free.
//Author: Lászka Adrián

#include "graphics.hpp"
#include "widget.hpp"
#include "checkbox.hpp"
#include "textbox.hpp"
#include "button.hpp"
#include "spinbutton.hpp"
#include "listview.hpp"

#include "dialog1.hpp"
#include "dialog2.hpp"

#include <vector>
using namespace std;
using namespace genv;

void event_loop(vector<Widget*> & widgets) {
    event ev;
    int focus = -1;
    while(gin >> ev ) {
        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                        widgets[i]->setFocus(true);
                        focus = i;
                } else {
                        widgets[i]->setFocus(false);
                }
            }
        }
        if (focus!=-1) {
            widgets[focus]->handle(NULL, 0, ev);
        }
        for (size_t i=0;i<widgets.size();i++) {
            widgets[i]->draw();
        }
        gout << refresh;
    }
}

int main()
{
    gout.open(1000,500);

    vector<Widget*> w;

    CheckBox * c1 = new CheckBox(NULL, 0, 10,10,30,30);
    CheckBox * c2 = new CheckBox(NULL, 0, 10,50,30,30);

    c1->setDisabled(true);

    TextBox * t1 = new TextBox(NULL, 0, 50, 10, 340, 30);
    TextBox * t2 = new TextBox(NULL, 0, 50, 50, 340, 30);

    SpinButton * sb1 = new SpinButton(NULL, 0, 10, 100, 120, 30, 10, 0, 25);
    SpinButton * sb2 = new SpinButton(NULL, 0, 10, 140, 120, 30, 0, -10, 10);

    //////

    Dialog1 * d1 = new Dialog1(NULL, 0, 10, 200, 400, 480);

    //
    //////

    Dialog2 * d2 = new Dialog2(NULL, 0, 420, 200, 430, 180);

    c1->add(w);
    c2->add(w);
    t1->add(w);
    t2->add(w);
    sb1->add(w);
    sb2->add(w);
    d1->add(w);
    d2->add(w);

    event_loop(w);

    return 0;
}
