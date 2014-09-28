#include <iostream>
#include <string>
#include "Polygon.h"

using std::cin;
using std::cout;

void checkTriangulation(Polygon polygon){
    int realDoubledSquare = polygon.getDoubledSquare();
    vector<Polygon *> triangulation = polygon.triangulate();
    int doubledSquare = 0;
    for (Polygon * p : triangulation) {
        if(p->getSize() != 3){
            std::cerr << "Not a tringle in the triangulation." << std::endl;
        }
        doubledSquare += p->getDoubledSquare();
    }
    if(doubledSquare != realDoubledSquare){
        std::cerr << "Square of triangles is " << doubledSquare << ", but original polygon sqare is " << realDoubledSquare <<std::endl;
    }
}

int main(int argc, const char* argv[]) {
    Polygon polygon;
    cin >> polygon;

    if( (argc > 1) && (std::string(argv[1]) == "-t") ){
        checkTriangulation(polygon);
    } else {
        for (Polygon *p : polygon.triangulate()) {
            for(int i = 0; i < 2 ; ++i) {
                if (p->_vertex->_no > p->_vertex->_next->_no) {
                    p->_vertex = p->_vertex->_next;
                }
            }
            for(int i = 0; i < 2 ; ++i) {
                if (p->_vertex->_no > p->_vertex->_prev->_no) {
                    p->_vertex = p->_vertex->_prev;
                }
            }
            cout << '(';
            cout << p->_vertex->_no;
            cout << ',';
            cout << p->_vertex->_next->_no;
            cout << ',';
            cout << p->_vertex->_next->_next->_no;
            cout << ')' << std::endl;
        }
    }
    return 0;
}