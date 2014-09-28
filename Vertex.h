#include "Point.h"

#ifndef VERTEX
#define VERTEX



class Vertex : public Point {
public:
    Vertex(Point &p) :
            Point(p) {
    };
    int _no;
    Vertex *_next;
    Vertex *_prev;

    ~Vertex() {
    }
};

inline bool adjacent(Vertex *a, Vertex *b) {
    return (a->_next == b || a->_prev == b);
}

#endif