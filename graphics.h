#ifndef GRAPH_H
#define GRAPH_H
#include "observer.h"
#include "window.h"
#include "info.h"
#include "subject.h"
#include <vector>

const int cellWidth = 20;
const int cellHeight = 20;
class GraphicsDisplay: public Observer<Info> {
    std::vector<std::vector<char>> theDisplay;
    Xwindow *w;
    int i;
    public:
        GraphicsDisplay(Xwindow *, int i);
        ~GraphicsDisplay();
        void notify(Subject<Info> &whoFrom) override;        
};

#endif





