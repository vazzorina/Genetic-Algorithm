#include "datageneration.h"
#include <QChart>
#include <QXYSeries>
#include <cmath>
#include <random>

DataGenerator::DataGenerator(QObject *parent) : QObject(parent), gen(std::random_device{}()) { }

DataGenerator::~DataGenerator() {
    delete prev_population;
    delete population;
    delete parents;
    delete children;
    delete av_Fx_points;
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
    for (int i = 1; i <= 200; i++) {
        y = is_target ? get_y(x) : fitness_function(x);
        points.append(QPointF(x, y));
        x += 0.05;
    }

    series->replace(points);
}

void DataGenerator::generate_population(QXYSeries *series_start, QXYSeries *series_third,
                                        QXYSeries *series_last, QXYSeries *av_Fx) {
    if (!series_start && !series_last && !series_third) return;

    QList<QPointF> points_start;
    QList<QPointF> points_third;
    QList<QPointF> points_last;

    std::uniform_real_distribution<double> dis(-5.0, 5.0);

    for (int i = 1; i <= 50; i++) {
        double x = dis(gen);
        double y = get_y(x);
        double F = fitness_function(x);
        int X = (x + 5) * 100000; //переводим в целое число с сохранением дробной части до 5 знаков для записи хромомсомы
        std::bitset<20> chrom(X);
        Individual Individ({x, chrom, y, F});
        prev_population->append(Individ);
        points_start.append(QPointF(x, y));
    }


    int n = 50, i = 0;
    while (i <= n) {
        choice_parent();
        generate_children();
        turnir();
        average_Fx(i);
        if (i == 2) {
            for(const auto &ind : *population) {
                points_third.append(QPointF(ind.x, ind.y_targ_func));
            }
        }

        if (i == 50) {
            for(const auto &ind : *population) {
                points_last.append(QPointF(ind.x, ind.y_targ_func));
            }
        }

        i++;

        prev_population->clear();
        prev_population->append(*population);
        population->clear();
        parents->clear();
        children->clear();
    }

    prev_population->clear();

    series_start->replace(points_start);
    series_third->replace(points_third);
    series_last->replace(points_last);
    av_Fx->replace(*av_Fx_points);
    av_Fx_points->clear();
}

void DataGenerator::choice_parent() {
    QList<Individual> popup = *prev_population;

    std::shuffle(popup.begin(), popup.end(), gen);

    for (int i = 0; i < 50; i += 2) {
        Individual parent1 = popup[i];
        Individual parent2 = popup[i + 1];
        parents->append({parent1, parent2});
    }

}

void DataGenerator::generate_children() {
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    std::uniform_int_distribution<> k(1, 18); //место разлома хромомсомы
    std::uniform_int_distribution<> n(0, 19); //индекс гена для мутации

    for(const auto [p1, p2] : *parents) {
        double V = dis(gen);
        if (V < Pc) {
            int K = k(gen);
            std::bitset<20> chrom1 (p1.chromosome.to_string().substr(0, K) + p2.chromosome.to_string().substr(K, 20-K+1));
            std::bitset<20> chrom2 (p2.chromosome.to_string().substr(0, K) + p1.chromosome.to_string().substr(K, 20-K+1));

            int M1 = dis(gen), M2 = dis(gen);
            if (M1 < Pm) {
                int N = n(gen);
                chrom1[N].flip();
            }
            if (M2 < Pm) {
                int N = n(gen);
                chrom2[N].flip();
            }

            double x1 = static_cast<double>(chrom1.to_ulong()) / 100000 - 5;
            double x2 = static_cast<double>(chrom2.to_ulong()) / 100000 - 5;
            Individual child1 {x1, chrom1, get_y(x1), fitness_function(x1)};
            Individual child2 {x2, chrom2, get_y(x2), fitness_function(x2)};

            children->append(child1);
            children->append(child2);
        }
    }
}

void DataGenerator::turnir() {
    QList<Individual> popup;
    popup.append(*children);
    popup.append(*prev_population);
    std::shuffle(popup.begin(), popup.end(), gen);

    while(population->size() < 50) {
        QList<Individual> ppp;
        for(int i = 0; i + 1 < popup.size(); i += 2) {
            if(popup[i].fitn_func >= popup[i + 1].fitn_func) {
                population->append(popup[i]);
                popup[i].fitn_func = -1;
            } else {
                population->append(popup[i + 1]);
                popup[i + 1].fitn_func = -1;
            }
        }

        for (const auto &ind : popup){
            if(ind.fitn_func >= 0) {
                ppp.append(ind);
            }
        }

        popup.clear();
        popup = ppp;
    }
}

void DataGenerator::average_Fx(int i) {
    double sum = 0;
    for (const auto &ind : *population) {
        sum += ind.fitn_func;
    }
    double aFx = sum/population->size();
    av_Fx_points->append(QPointF(i, aFx));
}



