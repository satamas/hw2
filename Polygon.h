#ifndef POLYGON
#define POLYGON

#include <vector>
#include <iostream>
#include "Vertex.h"

using std::vector;

class Polygon {
public:

    Polygon();
    Polygon(Vertex * v);
    Polygon(Polygon const & p);

    vector<Polygon *> triangulate();
    int getSize();
    friend std::istream &operator>>(std::istream &in, Polygon &polygon);

    int getDoubledSquare();

    void addVertex(Vertex * vertex){
        if(_vertex == nullptr){
            _vertex = vertex;
            _vertex->_next = _vertex;
            _vertex->_prev = _vertex;
        } else{
            vertex->_next = _vertex;
            vertex->_prev = _vertex->_prev;
            vertex->_next->_prev = vertex;
            vertex->_prev->_next = vertex;
        }
    }

    ~Polygon(){
        Vertex * current = _vertex;
        Vertex * next = _vertex->_next;
        while (next != _vertex){
            delete current;
            current = next;
            next = current->_next;
        }
        delete current;
    }

    Polygon * split(Vertex * a, Vertex * b);
    Vertex *_vertex = nullptr;
private:
    void resize(){
        size = 0;
        if(_vertex != nullptr){
            ++size;
            Vertex * v = _vertex->_next;
            while (v != _vertex){
                ++size;
                v = v->_next;
            }
        }
    }
    int size;
};

#endif