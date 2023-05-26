#include <QtWidgets>
#include <vector>

// Custom CanvasWidget class
class CanvasWidget : public QWidget {
public:
    CanvasWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(400, 400);
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
    }

    void setPoints(const std::vector<QPointF>& points) {
        this->points = points;
        update();
    }

    void setBestPath(const std::vector<int>& bestPath) {
        this->bestPath = bestPath;
        update();
    }

    void setPheromone(const std::vector<std::vector<double>>& pheromone) {
        this->pheromone = pheromone;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw points
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);
        for (const QPointF& point : points) {
            painter.drawEllipse(point, 5, 5);
        }

        // Draw best path
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::blue);
        for (size_t i = 0; i < bestPath.size() - 1; ++i) {
            const QPointF& startPoint = points[bestPath[i]];
            const QPointF& endPoint = points[bestPath[i + 1]];
            painter.drawLine(startPoint, endPoint);
        }

        // Draw pheromone
        for (size_t i = 0; i < pheromone.size(); ++i) {
            for (size_t j = 0; j < pheromone[i].size(); ++j) {
                const double intensity = pheromone[i][j];
                if (intensity > 0) {
                    const QPointF& startPoint = points[i];
                    const QPointF& endPoint = points[j];
                    QPen pen(QColor(148, 0, 211));  // Violet color
                    pen.setWidthF(1.0 + intensity * 5);  // Adjust line thickness based on intensity
                    painter.setPen(pen);
                    painter.drawLine(startPoint, endPoint);
                }
            }
        }
    }

private:
    std::vector<QPointF> points;
    std::vector<int> bestPath;
    std::vector<std::vector<double>> pheromone;
};

// Custom MainWindow class
class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Create the canvas widget
        canvasWidget = new CanvasWidget(this);
        setCentralWidget(canvasWidget);

        // Create the buttons
        runButton = new QPushButton("Run", this);
        drawPathButton = new QPushButton("Draw Best Path", this);
        saveImageButton = new QPushButton("Save Image", this);

        // Create the checkboxes
        showFeromoneCheckbox = new QCheckBox("Show Feromone", this);
        showNodesCheckbox = new QCheckBox("Show Nodes", this);
        useMultithreadingCheckbox = new QCheckBox("Use Multithreading", this);

        // Create the iteration and ant entry widgets
        iterationLabel = new QLabel("Iterations:", this);
        antLabel = new QLabel("Ants:", this);
        iterationSpinBox = new QSpinBox(this);
        antSpinBox = new QSpinBox(this);

        // Create the layout for the controls
        QVBoxLayout *controlsLayout = new QVBoxLayout();
        controlsLayout->addWidget(runButton);
        controlsLayout->addWidget(drawPathButton);
        controlsLayout->addWidget(saveImageButton);
        controlsLayout->addWidget(showFeromoneCheckbox);
        controlsLayout->addWidget(showNodesCheckbox);
        controlsLayout->addWidget(useMultithreadingCheckbox);
        controlsLayout->addWidget(iterationLabel);
        controlsLayout->addWidget(iterationSpinBox);
        controlsLayout->addWidget(antLabel);
        controlsLayout->addWidget(antSpinBox);
        controlsLayout->addStretch();

        // Create the main layout
        QHBoxLayout *mainLayout = new QHBoxLayout();
        mainLayout->addWidget(canvasWidget);
        mainLayout->addLayout(controlsLayout);

        // Create the central widget and set the main layout
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);

        // Connect the button signals to slots
        connect(runButton, &QPushButton::clicked, this, &MainWindow::runAlgorithm);
        connect(drawPathButton, &QPushButton::clicked, this, &MainWindow::drawBestPath);
        connect(saveImageButton, &QPushButton::clicked, this, &MainWindow::saveImage);

        // Set default values for the spin boxes
        iterationSpinBox->setValue(100);
        antSpinBox->setValue(10);
    }

private slots:
    void runAlgorithm() {
        // Get the number of iterations and ants from the spin boxes
        int iterations = iterationSpinBox->value();
        int ants = antSpinBox->value();

        // TODO: Run the algorithm with the given parameters

        // TODO: Update the canvas with the points, best path, and pheromone
        std::vector<QPointF> points;  // Replace with actual points data
        std::vector<int> bestPath;  // Replace with actual best path data
        std::vector<std::vector<double>> pheromone;  // Replace with actual pheromone data
        canvasWidget->setPoints(points);
        canvasWidget->setBestPath(bestPath);
        canvasWidget->setPheromone(pheromone);
    }

    void drawBestPath() {
        // TODO: Draw the best path on the canvas
    }

    void saveImage() {
        // TODO: Save the canvas as an image
    }

private:
    CanvasWidget *canvasWidget;
    QPushButton *runButton;
    QPushButton *drawPathButton;
    QPushButton *saveImageButton;
    QCheckBox *showFeromoneCheckbox;
    QCheckBox *showNodesCheckbox;
    QCheckBox *useMultithreadingCheckbox;
    QLabel *iterationLabel;
    QLabel *antLabel;
    QSpinBox *iterationSpinBox;
    QSpinBox *antSpinBox;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
