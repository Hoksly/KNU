
#include "antAlgorithms/basicAntAlgotiyhm.h"
#include "colonies/colony.h"
#include "maps/map.h"
#include "ants/basicAnt.h"
#include "chooseNextNodeStrategies/chooseStrategy.h"
#include "updateFeromoneStrategies/basicFeromoneDecayStrategy.h"
#include "chooseBestRootStrategies/chooseBestFeromoneRoot.h"
#include "antAlgorithms/antAlgorithmFactory.h"
#include <iostream>
#include <memory>
#include <chrono>

#include <QtWidgets>
#include <vector>
#include <set>

typedef boost::coroutines2::coroutine<vector<vector<double>>> Coroutine;


using std::pair;
using std::vector;


class GraphWidget : public QWidget {
Q_OBJECT


public:
    explicit GraphWidget(QWidget *parent = nullptr)
            : QWidget(parent) {
        setMinimumSize(800, 600);
        setWindowTitle("Ant Algorithm Visualization");

        canvas = new QWidget(this);
        canvas->setStyleSheet("background-color: white;");
        canvas->installEventFilter(this);

        QHBoxLayout *inputsLayout = new QHBoxLayout;
        iterationsLineEdit = new QLineEdit(this);
        iterationsLineEdit->setFixedWidth(100);

        antsLineEdit = new QLineEdit(this);
        antsLineEdit->setFixedWidth(100);

        pheromoneImpactLineEdit = new QLineEdit(this);
        pheromoneImpactLineEdit->setFixedWidth(100);

        distanceImpactLineEdit = new QLineEdit(this);
        distanceImpactLineEdit->setFixedWidth(100);

        decayCoefficientLineEdit = new QLineEdit(this);
        decayCoefficientLineEdit->setFixedWidth(100);

        clearButton = new QPushButton("Clear", this);

        inputsLayout->addWidget(new QLabel("Iterations:", this));
        inputsLayout->addWidget(iterationsLineEdit);
        inputsLayout->addWidget(new QLabel("Ants:", this));
        inputsLayout->addWidget(antsLineEdit);
        inputsLayout->addWidget(new QLabel("Pheromone impact:", this));
        inputsLayout->addWidget(pheromoneImpactLineEdit);
        inputsLayout->addWidget(new QLabel("Distance impact:", this));
        inputsLayout->addWidget(distanceImpactLineEdit);

        inputsLayout->addWidget(new QLabel("Decay:", this));
        inputsLayout->addWidget(decayCoefficientLineEdit);


        inputsLayout->addStretch();

        auto *drawingOptionsLayout = new QHBoxLayout;

        QCheckBox *drawBestPathCheckBox = new QCheckBox("Draw Best Path", this);
        QCheckBox *drawPheromoneCheckBox = new QCheckBox("Draw Pheromone", this);
        QCheckBox *useMultithreadingCheckBox = new QCheckBox("Use multithreading", this);

        drawingOptionsLayout->addWidget(drawBestPathCheckBox);
        drawingOptionsLayout->addWidget(drawPheromoneCheckBox);
        drawingOptionsLayout->addWidget(useMultithreadingCheckBox);
        drawingOptionsLayout->addWidget(clearButton);


        auto *resultsLayout = new QHBoxLayout;

        timeSpentLabel = new QLabel("", this);
        pathDistanceLabel = new QLabel("", this);

        timeSpentLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        pathDistanceLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        timeSpentLabel->setMinimumWidth(100);
        pathDistanceLabel->setMinimumWidth(100);


        resultsLayout->addWidget(new QLabel("Time spent:", this));
        resultsLayout->addWidget(timeSpentLabel);
        resultsLayout->addWidget( new QLabel("Path distance:", this));
        resultsLayout->addWidget(pathDistanceLabel);
        resultsLayout->addStretch();



        runButton = new QPushButton("Run", this);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(inputsLayout);
        mainLayout->addLayout(drawingOptionsLayout);
        mainLayout->addLayout(resultsLayout);
        mainLayout->addWidget(runButton);
        mainLayout->addWidget(canvas);
        mainLayout->setContentsMargins(10, 10, 10, 10);

        connect(clearButton, &QPushButton::clicked, this, &GraphWidget::clearCanvas);
        connect(runButton, &QPushButton::clicked, this, &GraphWidget::startAlgorithm);

        connect(drawBestPathCheckBox, &QCheckBox::stateChanged, this, &GraphWidget::drawBestPathStateChanged);
        connect(useMultithreadingCheckBox, &QCheckBox::stateChanged, this, &GraphWidget::useMultithreadingStateChanged);
        connect(drawPheromoneCheckBox, &QCheckBox::stateChanged, this, &GraphWidget::drawPheromoneStateChanged);

    }

protected:
    std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, int, Qt::GlobalColor>> pathLines;
    std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, double, Qt::GlobalColor>> pheromoneLines;

    QPushButton *runButton;
    QPushButton *clearButton;


    QLineEdit *iterationsLineEdit;
    QLineEdit *antsLineEdit;
    QLineEdit *pheromoneImpactLineEdit;
    QLineEdit *distanceImpactLineEdit;
    QLineEdit *decayCoefficientLineEdit;

    QLabel *timeSpentLabel;
    QLabel *pathDistanceLabel;



    QWidget *canvas;
    std::vector<QPair<int, int>> dots;

    bool useMultithreading = true;
    bool drawPheromone = true;
    bool drawBestPathState = true;




    void useMultithreadingStateChanged(int state)
    {
        if (state == Qt::Checked) {
            useMultithreading = true;

        } else {
            useMultithreading = false;

        }
    }

    void drawPheromoneStateChanged(int state)
    {
        if (state == Qt::Checked) {
            drawPheromone = true;

        } else {
           drawPheromone = false;

        }
    }

    void drawBestPathStateChanged(int state)
    {
        if (state == Qt::Checked) {
            drawBestPathState = true;

        } else {
            drawBestPathState = false;

        }
    }


    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == canvas) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    // Add new point at mouse position
                    QPoint position = mouseEvent->pos();
                    dots.push_back(qMakePair(position.x(), position.y()));
                    updateCanvas();
                    return true; // Stop event propagation
                }
            } else if (event->type() == QEvent::Paint) {
                drawLines();
                drawDots();


                return true; // Stop event propagation
            }

        }
        return QWidget::eventFilter(obj, event);
    }

private slots:

    void drawBestPath(vector<std::size_t> route, const vector<std::pair<double, double>> dots)
    {
        size_t n = route.size();
        pathLines.clear();
        for(size_t i  = 1; i < route.size(); ++i)
        {
            drawPathLine(dots[route[i - 1]], dots[route[i]], Qt::black);
        }

    }



    void clearCanvas()
    {
        dots.clear();
        pathLines.clear();
        pheromoneLines.clear();
        canvas->update();
    }

    void clearLines()
    {
        pathLines.clear();
        pheromoneLines.clear();
        canvas->update();
    }


    void startAlgorithm()
    {
        // Get number of iterations and ants from line edits
        int32_t iterations = iterationsLineEdit->text().toInt();
        int32_t ants = antsLineEdit->text().toInt();

        // Export dots to vector of pairs

        clearLines();

        AntAlgorithmFactory<double, double> factory;
        std::shared_ptr<AntAlgorithm<double, double>> algMultPtr = factory.createAlgorithm("basic", ants, 0.6);

        vector<std::pair<double, double>> nodes = exportDots();
        algMultPtr->getMap()->fromCoordinates(nodes, 1.0);

        Coroutine::pull_type source([&](Coroutine::push_type &yield)
                                    { algMultPtr->run(0, iterations, yield);});


        for(auto &map: source)
        {



            exportPheromoneMap(map, nodes);

            canvas->update();
            QCoreApplication::processEvents();
        }



        vector<size_t> path = algMultPtr->getBestPath();

        drawBestPath(path, nodes);

        exportPheromoneMap(algMultPtr->getMap()->getFeromone(), nodes);

        canvas->update();

        qDebug() << iterations << ants;

    }


    void updateCanvas()
    {
        canvas->update();
    }

    void drawPathLine(std::pair<int, int> x, std::pair<int, int> y, Qt::GlobalColor color = Qt::black)
    {
        pathLines.emplace_back(x, y, 4, color);
    }

    void drawPheromoneLine(std::pair<int, int> x,  std::pair<int, int> y, double thickness, Qt::GlobalColor color = Qt::red)
    {

        pheromoneLines.emplace_back(x, y, thickness, color);
    }

    void exportPheromoneMap(const vector<vector<double>> &pheromoneMap, const vector<std::pair<double, double>> &nodes)
    {
        pheromoneLines.clear();
        double minPheromone = std::numeric_limits<double>::max();
        double maxPheromone = std::numeric_limits<double>::lowest();

        for (const auto& row : pheromoneMap) {
            for (const auto& value : row) {
                minPheromone = std::min(minPheromone, value);
                maxPheromone = std::max(maxPheromone, value);
            }
        }



        for (size_t i = 0; i < pheromoneMap.size(); ++i) {
            for (size_t j = 0; j < pheromoneMap[i].size(); ++j) {
                const double pheromone = pheromoneMap[i][j];
                const double normalizedValue = (pheromone - minPheromone) / (maxPheromone - minPheromone);


                const double thickness = normalizedValue * 2.5;
                if(thickness == 0)
                        continue;

                drawPheromoneLine(std::make_pair<int, int>(static_cast<int>(nodes[i].first), static_cast<int>(nodes[i].second)),

                                                           std::make_pair<int, int>(static_cast<int>(nodes[j].first), static_cast<int>(nodes[j].second)),
                                  thickness);

            }
        }
    }



    void drawLines()
    {
        QPainter painter(canvas);
        painter.eraseRect(rect());
        painter.setRenderHint(QPainter::Antialiasing, true);


        for (const auto &line : pheromoneLines) {
            std::pair<int, int> x = std::get<0>(line);
            std::pair<int, int> y = std::get<1>(line);
            double thickness = std::get<2>(line);
            Qt::GlobalColor color = std::get<3>(line);

            QPen pen(color, 1);
            pen.setCosmetic(true);
            pen.setWidthF(thickness);
            painter.setPen(pen);
            painter.drawLine(x.first, x.second, y.first, y.second);
        }


        for (const auto &line : pathLines) {
            std::pair<int, int> x = std::get<0>(line);
            std::pair<int, int> y = std::get<1>(line);
            int thickness = std::get<2>(line);
            Qt::GlobalColor color = std::get<3>(line);



            painter.setPen(QPen(color, thickness));
            painter.drawLine(x.first, x.second, y.first, y.second);
        }

    }

    void drawDots()
    {
        QPainter painter(canvas);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);

        for (const auto& dot : dots) {
            painter.drawEllipse(QPointF(dot.first, dot.second), 3, 3);
        }
    }

    std::vector<std::pair<double, double>> exportDots()
    {
        std::vector<std::pair<double, double>> ret;
        ret.reserve(dots.size());
        for (const auto& dot : dots) {

            ret.emplace_back(dot.first, dot.second);
        }
        return ret;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GraphWidget graphWidget;
    graphWidget.show();

    return app.exec();
}

#include "main.moc"