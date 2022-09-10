#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.resize(900, 600);
    w.show();
    return a.exec();
}
