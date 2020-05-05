#include "Recognizer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = -1;

    Recognizer* rec = Recognizer::NewInstance();

    if( rec != NULL )
    {
        rec->show();

        ret = a.exec();

        delete rec;
    }

    return ret;
}
