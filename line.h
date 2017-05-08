#ifndef LINE_H
#define LINE_H

struct Point{
    float x;
    float y;
};

class Line{
    public:
        Line(float x1, float y1, float x2, float y2);
        bool intersect(const Line& line2);
        Point p1; //this point will be more left p1.x < p2.x
        Point p2;
        bool vertical;
        float slope;
        float yint;
};

#endif // LINE_H
