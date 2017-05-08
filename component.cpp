#include "component.h"
#include "line.h"
#include <iostream>
Component::Component()
{

}
//comparison function to tell whether line1 goes after line2 in the
//list of lines sequentially.The list is to be ordered by increasing p2.x, then by p2.y
//as described by comes_after.
bool Component::comes_after(const Line& line1,const Line& line2){

    return (line1.p2.x > line2.p2.x) || (line1.p2.x == line2.p2.x && line1.p2.y > line2.p2.y);
}

//This inserts the new_line into the component after noticing it intersects by iteratively finding
//the insertion index. The list is to be ordered by increasing p2.x, then by p2.y
//as described by comes_after.
void Component::insert_line(const Line& new_line){
    std::list<Line>::iterator insert_it = this->lines.begin();
    while(insert_it != this->lines.end()){
        Line current_line = *insert_it;
        if(comes_after(current_line, new_line)){
            this->lines.insert(insert_it, new_line);
            return;
        }
        insert_it++;
    }
    this->lines.push_back(new_line);
}

//This does the same thing as comes_after, but is used as a comparator function for
//the Component::merge function. I wasn't able to figure out how to use the
//member function comes_after without violations. Returns True is line1 goes after line2.
bool merge_lines_cmpfn(const Line& line1, const Line& line2){
    return (line1.p2.x > line2.p2.x) || (line1.p2.x == line2.p2.x && line1.p2.y > line2.p2.y);
}

//This function merges this component with add_comp, removing everything in add_comp
//as by the merge function.
void Component::merge(Component add_comp){
    this->lines.merge(add_comp.lines, merge_lines_cmpfn);
}

//This function checks whether line2 intersects with at least one of the
//lines of the component.
bool Component::in_component(const Line& line2){
    for(std::list<Line>::const_iterator it= this->lines.begin(); it != this->lines.end(); it++){
        Line current_line = *it;
        if(current_line.intersect(line2)){
            return true;
        }
    }
    return false;
}

//This is an implementation of an optimization made to the program,
//removing lines that are no longer relevant to the algorithm.
//Pop off front of list until p2.x > new_line.p1.x.
void Component::truncate_component(const Line& new_line){
    float min_value = new_line.p1.x;
    while(!this->lines.empty()){
        if(this->lines.front().p2.x < min_value){
            this->lines.pop_front();
        }else{
            return;
        }
    }
}
