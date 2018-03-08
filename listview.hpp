#ifndef LISTVIEW_HPP_INCLUDED
#define LISTVIEW_HPP_INCLUDED

#include <vector>
#include <string>

#include "graphics.hpp"
#include "widget.hpp"
#include "textbox.hpp"

class ListView : public Widget {
protected:
    unsigned int _number;
	unsigned int _position;
	unsigned int _selected;
	vector<string> _values;
	vector<TextBox *> _textBoxes;

public:
    ListView(Widget * parent, int id, int x, int y, int sx, int sy, unsigned int  number);
	virtual ~ListView();
    virtual void add(vector<Widget *> & widgets);
    virtual void draw() const;
    virtual void handle(Widget * source, int message, event ev);

    bool isSelected() const;
    const string & getSelectedText() const;

    void remove();
	void addValue(const string & value);
};


#endif // LISTVIEW_HPP_INCLUDED
