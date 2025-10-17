#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1400, 800);
    setWindowTitle("ImagePro - Dark Edition");
    QFile styleFile(":/styles.qss");  // لو ضفته كـ resource
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        this->setStyleSheet(style);
    }
    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    setCentralWidget(central);

    setupToolbar();

    statusLabel = new QLabel("Ready");
    statusBar()->addWidget(statusLabel);

    // Left Filters Panel
    QFrame *filtersFrame = new QFrame;
    filtersFrame->setObjectName("frameFilters");
    filtersFrame->setMinimumWidth(220);
    QVBoxLayout *filtersLayout = new QVBoxLayout(filtersFrame);

    QLabel *filtersTitle = new QLabel("Filters");
    filtersTitle->setObjectName("panelTitle");
    filtersLayout->addWidget(filtersTitle);

    QScrollArea *filtersScroll = new QScrollArea;
    filtersScroll->setWidgetResizable(true);
    QWidget *scrollContent = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);

    QStringList filters = {
        "Blur", "Sharpen", "Brightness", "Contrast", "Saturation",
        "Grayscale", "Sepia", "Invert", "Edge Detect", "Emboss",
        "Gamma", "Hue", "Exposure", "Highlights", "Shadows",
        "Temperature", "Tint", "Vibrance", "Noise Reduction", "Clarity",
        "Vignette", "Pixelate", "Posterize", "Solarize", "Threshold", "Cartoon"
    };

    for (const QString &name : filters) {
        QPushButton *btn = new QPushButton(name);
        btn->setMinimumHeight(34);
        scrollLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [=]() {
            statusLabel->setText(QString("Filter selected: %1").arg(name));
        });
    }

    scrollLayout->addStretch();
    scrollContent->setLayout(scrollLayout);
    filtersScroll->setWidget(scrollContent);
    filtersLayout->addWidget(filtersScroll);

    // Center Canvas
    QFrame *canvasFrame = new QFrame;
    canvasFrame->setObjectName("frameCanvas");
    QVBoxLayout *canvasLayout = new QVBoxLayout(canvasFrame);

    QLabel *dropZone = new QLabel("Drop an image here or click below to browse");
    dropZone->setAlignment(Qt::AlignCenter);
    dropZone->setObjectName("dropZone");
    dropZone->setMinimumHeight(380);
    canvasLayout->addWidget(dropZone);

    QPushButton *selectImage = new QPushButton("Select Image");
    selectImage->setFixedWidth(160);
    connect(selectImage, &QPushButton::clicked, this, [=]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg)");
        if (!fileName.isEmpty())
            statusLabel->setText("Loaded: " + fileName);
    });
    canvasLayout->addWidget(selectImage, 0, Qt::AlignHCenter);
    canvasLayout->addStretch();

    // Right Properties Panel
    QFrame *propsFrame = new QFrame;
    propsFrame->setObjectName("frameProperties");
    propsFrame->setMinimumWidth(280);
    QVBoxLayout *propsLayout = new QVBoxLayout(propsFrame);

    QLabel *propsTitle = new QLabel("Properties");
    propsTitle->setObjectName("panelTitle");
    propsLayout->addWidget(propsTitle);

    auto addSlider = [&](QString text) {
        QLabel *label = new QLabel(text);
        QSlider *slider = new QSlider(Qt::Horizontal);
        propsLayout->addWidget(label);
        propsLayout->addWidget(slider);
    };

    addSlider("Brightness");
    addSlider("Contrast");
    addSlider("Intensity");
    addSlider("Radius");

    QPushButton *applyBtn = new QPushButton("Apply Filter");
    QPushButton *resetBtn = new QPushButton("Reset");
    propsLayout->addWidget(applyBtn);
    propsLayout->addWidget(resetBtn);
    propsLayout->addStretch();

    // Combine everything
    mainLayout->addWidget(filtersFrame);
    mainLayout->addWidget(canvasFrame, 1);
    mainLayout->addWidget(propsFrame);
}

void MainWindow::setupToolbar()
{
    QToolBar *toolbar = new QToolBar("Toolbar");
    toolbar->setObjectName("mainToolbar");
    toolbar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, toolbar);

    QAction *openAct = toolbar->addAction("Open");
    QAction *saveAct = toolbar->addAction("Save");
    QAction *exportAct = toolbar->addAction("Export");

    QWidget *spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacer);

    QLabel *appTitle = new QLabel("ImagePro");
    appTitle->setObjectName("appTitle");
    toolbar->addWidget(appTitle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
