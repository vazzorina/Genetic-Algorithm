#include <QObject>
#include <QChart>
#include <QXYSeries>
#include <bitset>
#include <random>

struct Individual {
    int i;
    double x;
    std::bitset<20> chromosome;
    double y_targ_func;
    double fitn_func;
};

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DataGenerator(QObject *parent = nullptr);
    ~DataGenerator();


    QList<Individual> *start_population = new QList<Individual>;

    double get_y(double x);
    double fitness_function(double x);

    Q_INVOKABLE void target_function(QXYSeries *series);
    Q_INVOKABLE void generate_population(QXYSeries *series);
    //Q_INVOKABLE void write_population(QList<Individual> *population);

private:
    std::mt19937 gen;

};
