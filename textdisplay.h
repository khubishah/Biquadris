#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include <string>
#include "observer.h"
#include "subject.h"
#include "cell.h"
#include <vector>
#include "info.h"

class TextDisplay: public Observer<Info>{
    std::vector<std::vector<char>> theDisplay;
    int boardHeight;
    int boardWidth;
    public:
        TextDisplay(int height, int width);
        void notify(Subject<Info> &whoNotified) override;
        void print(int i, bool isEffectBlind);
};

#endif




