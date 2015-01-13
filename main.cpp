#include <QApplication>

#include "jsonparser.h"
#include "dialog.h"

using namespace Libs;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JSonParser p(NULL, "config.json");
    p.JSonRead();

    Dialog *dial = new Dialog(NULL,  p.getModel());
    dial->show();
    dial->exec();

    delete dial;

    return a.exec();
}
