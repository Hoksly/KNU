
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
        clearButton = new QPushButton("Clear", this);

        inputsLayout->addWidget(new QLabel("Iterations:", this));
        inputsLayout->addWidget(iterationsLineEdit);
        inputsLayout->addWidget(new QLabel("Ants:", this));
        inputsLayout->addWidget(antsLineEdit);
        inputsLayout->addWidget(clearButton);
        inputsLayout->addStretch();


        runButton = new QPushButton("Run", this);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(inputsLayout);
        mainLayout->addWidget(runButton);
        mainLayout->addWidget(canvas);
        mainLayout->setContentsMargins(10, 10, 10, 10);

        connect(clearButton, &QPushButton::clicked, this, &GraphWidget::clearCanvas);
        connect(runButton, &QPushButton::clicked, this, &GraphWidget::startAlgorithm);
    }

protected:
    std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, int, Qt::GlobalColor>> pathLines;
    std::vector<std::tuple<std::pair<int, int>, std::pair<int, int>, int, Qt::GlobalColor>> pheromoneLines;



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

    void drawBestPath(vector<size_t> route, const vector<std::pair<double, double>> dots)
    {
        size_t n = route.size();
        pathLines.clear();
        for(size_t i  = 1; i < route.size(); ++i)
        {
            drawPathLine(dots[route[i-1]], dots[route[i]], 2, Qt::black);
        }

    }
    void clearCanvas()
    {
        dots.clear();
        pathLines.clear();
        canvas->update();
    }


    void startAlgorithm()
    {
        // Get number of iterations and ants from line edits
        int32_t iterations = iterationsLineEdit->text().toInt();
        int32_t ants = antsLineEdit->text().toInt();

        // Export dots to vector of pairs


        AntAlgorithmFactory<double, double> factory;
        std::shared_ptr<AntAlgorithm<double, double>> algMultPtr = factory.createAlgorithm("basic", ants, 0.6);

        vector<std::pair<double, double>> nodes = exportDots();
        algMultPtr->getMap()->fromCoordinates(nodes, 1.0);
        algMultPtr->run(0, iterations);

        vector<size_t> path = algMultPtr->getBestPath();

        drawBestPath(path, nodes);


        canvas->update();

        qDebug() << iterations << ants;
        // Start the algorithm with the provided parameters
        // ...
    }

private:
    QPushButton *runButton;
    QPushButton *clearButton;


    QLineEdit *iterationsLineEdit;
    QLineEdit *antsLineEdit;
    QLineEdit *pheromoneImpactLineEdit;
    QLineEdit *distanceImpactLineEdit;


    QWidget *canvas;
    std::vector<QPair<int, int>> dots;

    void updateCanvas()
    {
        canvas->update();
    }

    void drawPathLine(std::pair<int, int> x,  std::pair<int, int> y, int thickness, Qt::GlobalColor color = Qt::black)
    {
        pathLines.emplace_back(x, y, thickness, color);
    }

    void drawPheromoneLine(std::pair<int, int> x,  std::pair<int, int> y, int thickness, Qt::GlobalColor color = Qt::red)
    {
        pheromoneLines.emplace_back(x, y, thickness, color);
    }


    void drawLines()
    {
        QPainter painter(canvas);
        painter.eraseRect(rect());
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw existing pathLines
        for (const auto &line : pathLines) {
            std::pair<int, int> x = std::get<0>(line);
            std::pair<int, int> y = std::get<1>(line);
            int thickness = std::get<2>(line);

            painter.setPen(QPen(Qt::black, thickness));
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