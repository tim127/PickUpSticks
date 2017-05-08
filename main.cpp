#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "line.h"
#include "component.h"
using namespace std;

bool sort_lines_x1_cmpfn (const Line& line1, const Line& line2) {
  return line1.p1.x < line2.p1.x;
}

bool sort_ints_decrease_cmpfn (int i,int j) { return (j<i); }

//This is an optimization to the overall program. When called, it
//removes any lines from each component that are too far left to ever
//intersect with any lines. When a component has zero line elements, it is removed.
//This fn returns the number of empty components that has been removed.
//These empty components contribute to the end number of components left.
int clean_up_components(vector<Component>& components, const Line& add_line){

    //remove lines from components
    vector<int> empty_components_indices;
    for(unsigned int i = 0; i < components.size(); i++){
        components[i].truncate_component(add_line);
        if(components[i].lines.empty()){
            empty_components_indices.push_back(i);
        }
    }

    //remove empty components
    sort(empty_components_indices.begin(), empty_components_indices.end(), sort_ints_decrease_cmpfn);
    for(int i: empty_components_indices){
        components.erase(components.begin()+i);
    }
    return empty_components_indices.size();
}

//This function adds add_line to the list of components that it intersects with
//and merges components that intersect with add_line. The optimize argument
//tells whether to do clean up on the components object. The number that this function
//returns is the number of components with no more relevant lines, and thus removed from
//components through the clean_up_components function
int add_to_components(const Line& add_line, vector<Component>& components, bool optimize){
  vector<int> in_component_indices;

  //see which components intersect with line
  for(unsigned int i = 0; i < components.size(); i++){
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

  //optimization: remove sticks from components that are irrelevant, and empty
  if(optimize){
    return clean_up_components(components, add_line);
  }else{
    return 0;
  }
}

int main(int argc, char *argv[])
{
  ifstream infile;
  float x1, y1, x2, y2;
  vector<Line> lines;
  vector<Component> components;
  int empty_components_size = 0;

  //YOU CAN CHANGE HERE
  infile.open("//afs/userhome/Documents/pickupsticks/lines_286.txt");
  bool optimize = true;
  //END HERE

  if(!infile.is_open()){
      cout << "Error opening!" << endl;
  }

  while (infile >> x1 >> y1 >> x2 >> y2)
  {
    Line new_line = Line(x1, y1, x2, y2);
    lines.push_back(new_line);
  }

  //The algorithm I propose is dependent on the condition that the lines being sorted by x1
  sort(lines.begin(),lines.end(),sort_lines_x1_cmpfn);

  for(const Line& add_line : lines){
    empty_components_size += add_to_components(add_line, components, optimize);
  }

  int total_groups = components.size() + empty_components_size;

  cout<<"Number of Groups:"<<total_groups<<endl;
}
