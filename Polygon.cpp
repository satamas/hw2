#include <algorithm>
#include <stack>
#include "Polygon.h"

enum {
    UPPER, LOWER
};

std::istream &operator>>(std::istream &in, Polygon &polygon) {
    int vertexNo = 0;
    unsigned long no_of_vertices;
    in >> no_of_vertices;
    Point p;
    in >> p;
    ++vertexNo;
    Vertex *vertex = new Vertex(p);
    vertex->_no = vertexNo;
    polygon.addVertex(vertex);
    for (int i = 1; i < no_of_vertices; ++i) {
        in >> p;
        ++vertexNo;
        Vertex *vertex = new Vertex(p);
        vertex->_no = vertexNo;
        polygon.addVertex(vertex);
    }

    return in;
}


Polygon::Polygon() {
}


int advancePtr(Vertex *&upperVertex, Vertex *&lowerVertex, Vertex *&currentVertex) {
    if (upperVertex->_prev->x < lowerVertex->_next->x) {
        upperVertex = currentVertex = upperVertex->_prev;
        return UPPER;
    } else {
        lowerVertex = currentVertex = lowerVertex->_next;
        return LOWER;
    }
}


void triangulateFanPolygon(Polygon *p, vector<Polygon *> &triangles) {
    Vertex *w = p->_vertex->_prev->_prev;
    while (w->_prev != p->_vertex) {
        triangles.push_back(p->split(p->_vertex, w));
        w = w->_prev;
    }
    triangles.push_back(p);
}

vector<Polygon *> Polygon::triangulate() {
    vector<Polygon *> triangulation;
    Vertex *upperVertex, *lowerVertex, *currentVertex;

    std::vector<Vertex *> chain;
    chain.push_back(_vertex);
    upperVertex = lowerVertex = currentVertex = _vertex;
    advancePtr(upperVertex, lowerVertex, currentVertex);
    chain.push_back(currentVertex);

    while (true) {
        int pos = advancePtr(upperVertex, lowerVertex, currentVertex);
        if (adjacent(currentVertex, chain[chain.size() - 1]) && !adjacent(currentVertex, chain[0])) {
            int side = (pos == UPPER) ? LEFT : RIGHT;
            Vertex *b = chain[chain.size() - 2];
            Vertex *a = chain[chain.size() - 1];
            while ((chain.size() > 1) &&
                    (b->classify(*currentVertex, *a) == side)) {
                if (pos == UPPER) {
                    triangulation.push_back(split(b, currentVertex));
                } else {
                    triangulation.push_back(split(currentVertex, b));
                }
                chain.pop_back();
                a = b;
                b = chain[chain.size() - 2];
            }
            chain.push_back(currentVertex);
        } else if (!adjacent(currentVertex, chain[chain.size() - 1])) {
            Polygon *p;
            if (pos == UPPER) {
                p = split(chain[chain.size() - 1], currentVertex);
                p->_vertex = p->_vertex->_next;
            } else {
                p = split(currentVertex, chain[chain.size() - 1]);
            }
            triangulateFanPolygon(p, triangulation);
            _vertex = chain[chain.size() - 1];
            chain.clear();
            chain.push_back(_vertex);
            chain.push_back(currentVertex);
        } else {
            _vertex = currentVertex;
            triangulateFanPolygon(this, triangulation);
            return triangulation;
        }


    }

}

Polygon *Polygon::split(Vertex *a, Vertex *b) {
    Vertex *aCopy = new Vertex(*a);
    Vertex *bCopy = new Vertex(*b);

    aCopy->_prev->_next = aCopy;
    aCopy->_next = bCopy;
    bCopy->_prev = aCopy;
    bCopy->_next->_prev = bCopy;

    a->_prev = b;
    b->_next = a;

    return new Polygon(aCopy);
}

Polygon::Polygon(Vertex *v) {
    _vertex = v;
}

int Polygon::getSize() {
    resize();
    return size;
}

int Polygon::getDoubledSquare() {
    int doubledSquare = 0;
    Vertex *v = _vertex;
    while (v->_next != _vertex) {
        doubledSquare += v->x * v->_next->y - v->_next->x * v->y;
        v = v->_next;
    }
    doubledSquare += v->x * v->_next->y - v->_next->x * v->y;
    return doubledSquare;
}

Polygon::Polygon(Polygon const &p) {
    Vertex *v = p._vertex;
    while (v->_next != p._vertex) {
        addVertex(new Vertex(*v));
        v = v->_next;
    }
    addVertex(new Vertex(*v));
}
