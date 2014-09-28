#ifndef POINT
#define POINT

enum {
    LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION
};

struct Point {
    int x;
    int y;

    Point(int _x = 0, int _y = 0) :
            x(_x), y(_y) {
    }

    Point operator - (Point& p ){
        return Point(x-p.x, y-p.y);
    }

    int classify(Point &p0, Point &p1) {
        Point p2 = *this;
        Point a = p1 - p0;
        Point b = p2 - p0;
        double sa = a.x * b.y - b.x * a.y;
        if (sa > 0.0)
            return LEFT;
        if (sa < 0.0)
            return RIGHT;
        if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
            return BEHIND;
        if (a.sqLength() < b.sqLength())
            return BEYOND;
        if (p0 == p2)
            return ORIGIN;
        if (p1 == p2)
            return DESTINATION;
        return BETWEEN;
    }

    friend std::istream &operator>>(std::istream &in, Point &point) {
        char tmp;
        in >> tmp;
        in >> point.x;
        in >> tmp;
        in >> point.y;
        in >> tmp;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, Point &point) {
        out << '(';
        out << point.x;
        out << ',';
        out << point.y;
        out << ')';
        return out;
    }

    bool operator==(Point other) {
        return ((x == other.x) && (y = other.y));
    }

    int sqLength(){
        return x*x + y*y;
    }
};

#endif