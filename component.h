#ifndef COMPONENT_H
#define COMPONENT_H

#include <list>
#include "line.h"
using namespace std;

class Component{
    public:
        Component();
        void insert_line(const Line& new_line);
        void merge(Component add_comp);
        bool in_component(const Line& line2);
        list<Line> lines;  //this list is to be sorted by line.p2.x then by line.p2.y, according to comes_after;
        void truncate_component(const Line& new_line);

    private:
        bool comes_after(const Line& line1, const Line& line2);
};
#endif // COMPONENT_H
