#include "Line.h"
#include <iostream>
using namespace std;

//Line Organization / Conventions:
//The line created will have p1.x < p2.x , if x's are equal (i.e vertical), p1.y has lower y1 than y2.
//If line is vertical, will have 0 slope and 0 y-int.
Line::Line(float x1, float y1, float x2, float y2){
  bool switch_points;

  if(x1 == x2){
      this->vertical = true;
      if(y1 <= y2){
        switch_points = false;
      }else{
        switch_points = true;
      }
  }else if(x1 < x2){
    this->vertical = false;
    switch_points = false;

  }else{
    this->vertical = false;
    switch_points = true;
  }

  if(switch_points){
    this->p1.x = x2;
    this->p1.y = y2;
    this->p2.x = x1;
    this->p2.y = y1;
  }else{
    this->p1.x = x1;
    this->p1.y = y1;
    this->p2.x = x2;
    this->p2.y = y2;
  }

  if(!this->vertical){
    this->slope = (y2 - y1)/(x2-x1);
    this->yint = -1*this->slope*x1 + y1;
  }else{ //need to always check first that line is vertical
    this->slope = 0;
    this->yint = 0;
  }
}

//This function checks whether this line intersects with line2.
//The intersection is found by solving the two linear equations of
//the y=mx+b form, and checking if that intersection is within the
//range of the line segments. Edge cases with undefined slope (vertical line)
//or parallel slopes are also considered.
bool Line::intersect(const Line& line2){
  bool overlap_x, overlap_y;
  float intersect_x, intersect_y;

  if(this->vertical && line2.vertical){
    overlap_x = (this->p1.x == line2.p1.x);
    overlap_y = this->p1.y <= line2.p2.y && line2.p1.y <= this->p2.y; //vertical line segments overlap
    return overlap_x && overlap_y;
  }else if(this->vertical){
    intersect_x = this->p1.x;
    intersect_y = line2.slope*this->p1.x + line2.yint;
  }else if(line2.vertical){
    intersect_x = line2.p1.x;
    intersect_y = this->slope*line2.p1.x + this->yint;
  }else if(this->slope == line2.slope){
      if(this->yint != line2.yint) return false; //parallel but not same y-int
      return this->p1.x <= line2.p2.x && line2.p1.x <= this->p2.x; //parallel line segments overlap
  }else{
    intersect_x = (this->yint - line2.yint)/(line2.slope - this->slope);
    intersect_y = this->slope*intersect_x + this->yint;
  }

  //checks to see whether intersection lies in both ranges; overlap_y might not be necessary.
  bool overlap_x_1 = (this->p1.x <= intersect_x) && (this->p2.x >= intersect_x);
  bool overlap_x_2 = (line2.p1.x <= intersect_x) && (line2.p2.x >= intersect_x);
  overlap_x = overlap_x_1 && overlap_x_2;

  bool overlap_y_1 = ((this->p1.y <= intersect_y) && (this->p2.y >= intersect_y)) ||
          ((this->p2.y <= intersect_y) && (this->p1.y >= intersect_y));
  bool overlap_y_2 = ((line2.p1.y <= intersect_y) && (line2.p2.y >= intersect_y)) ||
          ((line2.p2.y <= intersect_y) && (line2.p1.y >= intersect_y));
  overlap_y = overlap_y_1 && overlap_y_2;

  return overlap_x && overlap_y;
}
