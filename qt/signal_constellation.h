#ifndef SIGNAL_CONSTELLATION_H
#define SIGNAL_CONSTELLATION_H

#include "qcustomplot.h"

class signal_constellation : public QCustomPlot
{
public:
    signal_constellation(QWidget* parent) : QCustomPlot(parent){
        auto g = this->addGraph();
        g->keyAxis()->setLabel("I компонента");
        g->valueAxis()->setLabel("Q компонента");
        g->setLineStyle(QCPGraph::lsNone);
        g->setScatterStyle(QCPScatterStyle::ssPlus);
    }

    void preprocess()
    {
        auto g = this->graph(0);

        g->rescaleAxes();
        auto half_w = std::max(g->keyAxis()->range().lower,g->keyAxis()->range().upper);
        auto half_h = std::max(g->valueAxis()->range().lower,g->valueAxis()->range().upper);

        auto l = std::max(half_w,half_h);
        l *= 1.1;
        g->keyAxis()->setRange(-l,l);
        g->valueAxis()->setRange(-l,l);
    }

    template <typename Container>
    void set_data(Container c){
        QVector<double> x(std::size(c));
        QVector<double> y(std::size(c));

        for (auto i = 0; i < std::size(c); ++i)
        {
            x[i] = c[i][0];
            y[i] = c[i][1];
        }

        this->graph(0)->setData(x,y);
        preprocess();
        replot();
    };

    template <typename Container>
    void set_data(Container I, Container Q){
        QVector<double> x(std::begin(I),std::end(I));
        QVector<double> y(std::begin(Q),std::end(Q));
        this->graph(0)->setData(x,y);
        preprocess();
        replot();
    };
};

#endif // SIGNAL_CONSTELLATION_H
