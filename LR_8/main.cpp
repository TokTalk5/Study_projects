#include <QApplication>
#include "canvas.h"
#include "stategraph.h"
#include "graph.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    graph g;
    StateGraph sample(g);
    TCanvas window(sample);
    window.show();

    return a.exec();
}
