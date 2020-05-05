#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "RecognizerUI.h"
#include "RecognizerAlgorithm.h"

class Recognizer
{
protected:
    RecognizerUI* m_ui = nullptr;
    RecognizerAlgorithm m_algorithm;
protected:
    Recognizer();
    bool construct();
public:
    static Recognizer* NewInstance();
    void show();
    ~Recognizer();
};

#endif // RECOGNIZER_H
