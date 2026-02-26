#include "datageneration.h"
#include <QChart>
#include <QXYSeries>
#include <cmath>
#include <random>

DataGenerator::DataGenerator(QObject *parent) : QObject(parent), gen(std::random_device{}()) {

}

DataGenerator::~DataGenerator() {
    delete start_population;
}

double DataGenerator::get_y(double x) {
    return 2 * x - 3.3 * x * cos(9.3 * x) - 2.3 * sin(1.7 * x);
}

double DataGenerator::fitness_function(double x) {
    return 25 - get_y(x);
}

void DataGenerator::get_function(QXYSeries *series, bool is_target) {
    if (!series) return;
    double x = -5, y = 0;
    QList<QPointF> points;
    for (int i = 1; i <= 50; i++) {
        y = is_target ? get_y(x) : fitness_function(x);
        points.append(QPointF(x, y));
        x += 0.2;
    }

    series->replace(points);
}

void DataGenerator::generate_population(QXYSeries *series) {
    if (!series) return;
    double x = -5, y = 0;
    QList<QPointF> points;
    for (int i = 1; i <= 50; i++) {
        y = get_y(x);
        points.append(QPointF(x, y));
        x += 0.2;
    }

    series->replace(points);
}

// void write_population(QList<Individual> *population) {

// }

