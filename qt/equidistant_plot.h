#ifndef EQUIDISTANT_PLOT_H
#define EQUIDISTANT_PLOT_H
#include <qcustomplot.h>
#include <complex>


struct equidistant_plot : public QCustomPlot
{
    equidistant_plot(QWidget* parent) : QCustomPlot(parent){
        auto g = this->addGraph();
        g->keyAxis()->setLabel("X");
        g->valueAxis()->setLabel("Y");

        setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

        legend->setVisible(true);
    }

    void set_labels(std::string y = "Y", std::string x = "X")
    {
        graph(0)->keyAxis()->setLabel(QString::fromStdString(x));
        graph(0)->valueAxis()->setLabel(QString::fromStdString(y));
    }

    void set_graphs_amount(int n = 1)
    {
        while (graphCount() < n)
        {
            int i = graphCount();
            auto g = addGraph();

            switch (i)
            {
            case 0: g->setPen(QPen(Qt::blue)); break;
            case 1: g->setPen(QPen(Qt::green));break;
            case 2: g->setPen(QPen(Qt::red));break;
            case 3: g->setPen(QPen(Qt::darkYellow));break;
            case 4: g->setPen(QPen(Qt::darkBlue));break;
            case 5: g->setPen(QPen(Qt::darkGray));break;
            }
        }
    }


    template <typename Container>
    void set_data(Container c, double left_border, double right_border, std::vector<std::string> labels = {})
    {
        set_data({c},left_border,right_border,labels);
    }


    template <typename Container>
    void set_data(std::initializer_list<Container> cl, double left_border, double right_border, std::vector<std::string> labels = {})
    {
        QVector<double> x(std::size(*cl.begin()),0.0);

        for (auto i = 0; i < x.size(); ++i)
        {
            x[i] = left_border + (double)i/x.size() * right_border;
        }

        std::vector<QVector<double>> y(cl.size());

        int j = 0;
        for (auto i = cl.begin(); i != cl.end(); ++i,++j)
        {
            y[j] = QVector<double>(std::begin(*i),std::end(*i));
        }

        set_graphs_amount(y.size());

        for (int i = 0; i < y.size(); ++i) {
            graph(i)->setData(x,y[i],true);
        }

        for (auto i = 0; i < labels.size();++i)
        {
            graph(i)->setName(labels[i].c_str());
        }

        rescaleAxes();
        replot();
    }

    void set_data(std::vector<std::complex<double>>& c, double left_border, double right_border, std::array<std::string,2> labels = {})
    {
        std::vector<double> re(c.size());
        std::vector<double> im(c.size());

        for (auto i = 0; i < c.size(); ++i)
        {
            re[i] = c[i].real();
            im[i] = c[i].imag();
        }

        set_data({re, im},left_border,right_border, {labels[0],labels[1]});
    }

    template <typename Container>
    void set_data(Container c, int index = 0)
    {
        set_data({c},0,c.size(),index);
    }
};

#endif // EQUIDISTANT_PLOT_H
