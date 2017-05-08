#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "Component.h"
#include "Line.h"
using namespace std;

bool sort_lines_x1_cmpfn (const Line& line1,const Line& line2) { 
  return line1.p1.x < line2.p1.x;
}
bool sort_ints_decrease_cmpfn (int i,int j) { return (j<i); }

void add_to_components(const Line& add_line, Vector<Component>& components){
  Vector<int> in_component_indices;

  //see which components intersect with line 
  for(int i = 0; i<components.size(); i++){
    if(components[i].in_component(add_line)){
      in_component_indices.push_back(i);
      components[i].insert_line(add_line);
    }
  }

  //make new component if completely alone
  if(in_component_indices.size() == 0){
    Component new_component = Component();
    new_component.insert_line(add_line);
    components.push_back(new_component);
  }

  //merge components that intersect with line
  if(in_component_indices.size() > 1){
    Component merge_component = Component();
    //sort indices from last to first, so when deleting components, doesn't mess with indexing
    sort(in_component_indices.begin(), in_component_indices.end(), sort_ints_decrease_cmpfn);

    //merge with new component, delete from components
    for(int i: in_component_indices){
      merge_component.merge(components[i]);
      components.erase(components.begin()+i);
    }

    components.push_back(merge_component);
  }

}

int main()
{
  ifstream infile("thefile.txt");
  float x1, y1, x2, y2;
  Vector<Line> lines;

  while (infile >> x1 >> y1 >> x2 >> y2)
  { 
    Line new_line = Line(x1, y1, x2, y2);
    lines.push_back(new_line);
  }

  sort(lines.begin(),lines.end(),sort_lines_x1_cmpfn);

  Vector<Component> components;
  for(const Line& add_line : lines){
    add_to_components(line, components);
  }

  return components.size();
}