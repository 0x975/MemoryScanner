#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QIcon binIcon(":/images/binary_lable.png");
    //QIcon binIcon(":/images/binary_lable_back.png");
    setWindowIcon(binIcon);

    QWidget *centralWidget = new QWidget;
    QHBoxLayout *main_layout = new QHBoxLayout;

    QGroupBox *matchesGroup = createMatchesPanel();
    QGroupBox *scannerGroup = createScannerPanel();

    //QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    //splitter->addWidget(matchesGroup);
    //splitter->addWidget(scannerGroup);

    //main_layout->addWidget(splitter);
    main_layout->addWidget(matchesGroup);
    main_layout->addWidget(scannerGroup);

    setupConnetions();
    memoryInteractionStratege = new LinuxMemoryInteraction();

    integerMemoryScanner    = new MemoryScannerEngine<int>(memoryInteractionStratege);
    characterMemoryScanner  = new MemoryScannerEngine<char>(memoryInteractionStratege);
    shortMemoryScanner      = new MemoryScannerEngine<short>(memoryInteractionStratege);
    doubleMemoryScanner     = new MemoryScannerEngine<double>(memoryInteractionStratege);
    longMemoryScanner       = new MemoryScannerEngine<long>(memoryInteractionStratege);
    floatMemoryScanner      = new MemoryScannerEngine<float>(memoryInteractionStratege);

    intValidator = new QIntValidator;
    doubleValidator = new QDoubleValidator;
    charValidator = new QRegExpValidator(QRegExp("^([a-z]|[A-Z])$"));

/*
    uint8MemoryScanner  = new MemoryScannerEngine<uint8_t>(memoryInteractionStratege);
    uint16MemoryScanner = new MemoryScannerEngine<uint16_t>(memoryInteractionStratege);
    uint32MemoryScanner = new MemoryScannerEngine<uint32_t>(memoryInteractionStratege);
    uint64MemoryScanner = new MemoryScannerEngine<uint64_t>(memoryInteractionStratege);

    int8MemoryScanner  = new MemoryScannerEngine<int8_t>(memoryInteractionStratege);
    int16MemoryScanner = new MemoryScannerEngine<int16_t>(memoryInteractionStratege);
    int32MemoryScanner = new MemoryScannerEngine<int32_t>(memoryInteractionStratege);
    int64MemoryScanner = new MemoryScannerEngine<int64_t>(memoryInteractionStratege);
*/

    //setMinimumWidth(1000);
    //setMinimumHeight(400);

    centralWidget->setLayout(main_layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

QTableWidget* MainWindow::setupMathcesTable()
{
     QTableWidget *table = new QTableWidget(0, 4);

     table->setHorizontalHeaderItem(0, new QTableWidgetItem("Addres"));
     table->setHorizontalHeaderItem(1, new QTableWidgetItem("Offset"));
     table->setHorizontalHeaderItem(2, new QTableWidgetItem("Value"));
     table->setHorizontalHeaderItem(3, new QTableWidgetItem("Type"));

     table->setEditTriggers(QAbstractItemView::NoEditTriggers);
     table->setSelectionBehavior(QAbstractItemView::SelectRows);
     table->setSelectionMode(QAbstractItemView::SingleSelection);
     table->horizontalHeader()->setStretchLastSection(true);
     table->verticalHeader()->setVisible(false);

     return table;
}

QGroupBox* MainWindow::createMatchesPanel()
{
    QGroupBox *matchesBox = new QGroupBox("matches table");
    QVBoxLayout *boxLayout = new QVBoxLayout;

    QLabel *mathLabel = new QLabel("found: ");
    matchesCount = new QLabel("0");

    QHBoxLayout *lbLayout = new QHBoxLayout;
    lbLayout->addWidget(mathLabel);
    lbLayout->addWidget(matchesCount);
    lbLayout->addStretch(0);

    matchesTable = setupMathcesTable();
    boxLayout->addLayout(lbLayout);
    boxLayout->addWidget(matchesTable);

    matchesBox->setLayout(boxLayout);
    return matchesBox;
}

QGroupBox* MainWindow::createScannerPanel()
{
    QGroupBox *scannerBox = new QGroupBox;
    QVBoxLayout *boxLayout = new QVBoxLayout;

    processBtn = createProcessBtn();
    selectedProcessLabel= new QLabel("no process selected");

    QHBoxLayout *processSelectorLayout = new QHBoxLayout;
    processSelectorLayout->addWidget(processBtn);
    processSelectorLayout->addWidget(selectedProcessLabel);
    processSelectorLayout->addStretch(0);

    QLabel *scanCounterLabel = new QLabel("scanner counter: ");
    scannCount = new QLabel("0");

    QHBoxLayout *scannerCounterLayout = new QHBoxLayout;
    scannerCounterLayout->addWidget(scanCounterLabel);
    scannerCounterLayout->addWidget(scannCount);
    scannerCounterLayout->addStretch(0);

    scannProgress = new QProgressBar;
    scannProgress->setRange(0, 100);
    scannProgress->setValue(0);

    QLabel *valueLabel = new QLabel("value: ");
    valueTextField = new QLineEdit;
    valueTextField->setMinimumHeight(30);
    scannBtn = createScannerBtn();
    refreshBtn = createRefreshBtn();

    QHBoxLayout *scannerSetupLayout = new QHBoxLayout;
    scannerSetupLayout->addWidget(valueLabel);
    scannerSetupLayout->addWidget(valueTextField);
    scannerSetupLayout->addWidget(scannBtn);
    scannerSetupLayout->addWidget(refreshBtn);

    QLabel *dataTypeLabel = new QLabel("data type: ");
    dataTypeSelector = createDataTypeSelector();

    QLabel *compareTypeLabel = new QLabel("compare type: ");
    compareTypeSelector = new QComboBox;
    compareTypeSelector->addItem("Equal");
    compareTypeSelector->addItem("Less then");
    compareTypeSelector->addItem("Greater then");
    compareTypeSelector->insertSeparator(3);
    compareTypeSelector->addItem("Increased");
    compareTypeSelector->addItem("Decreased");
    compareTypeSelector->addItem("Unchanged");
    compareTypeSelector->addItem("Changed");

    QHBoxLayout *valueTypeLayout = new QHBoxLayout;
    valueTypeLayout->addWidget(dataTypeLabel);
    valueTypeLayout->addWidget(dataTypeSelector);
    valueTypeLayout->addWidget(compareTypeLabel);
    valueTypeLayout->addWidget(compareTypeSelector);
    valueTypeLayout->addStretch(0);

    boxLayout->addLayout(processSelectorLayout);
    boxLayout->addLayout(scannerCounterLayout);
    boxLayout->addWidget(scannProgress);
    boxLayout->addLayout(scannerSetupLayout);
    boxLayout->addLayout(valueTypeLayout);
    boxLayout->addStretch(0);

    scannerBox->setLayout(boxLayout);
    return scannerBox;
}

QComboBox* MainWindow::createDataTypeSelector()
{
    QComboBox *typeBox = new QComboBox;
    typeBox->addItem("Char");
    typeBox->addItem("Short");
    typeBox->addItem("Int");
    typeBox->addItem("Long");
    typeBox->addItem("Float");
    typeBox->addItem("Double");
    typeBox->addItem("LongDouble");
    return typeBox;
}

QPushButton* MainWindow::createProcessBtn()
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(":/images/monitor_icon.png"));
    button->setIconSize(QSize(25,25));
    button->setFixedSize(QSize(30,30));
    return button;
}

QPushButton* MainWindow::createScannerBtn()
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(":/images/lupa.png"));
    button->setIconSize(QSize(25,25));
    button->setFixedSize(QSize(30,30));
    return button;
}

QPushButton* MainWindow::createRefreshBtn()
{
    QPushButton *button = new QPushButton();
    button->setIcon(QIcon(":/images/refresh.png"));
    button->setIconSize(QSize(25,25));
    button->setFixedSize(QSize(30,30));
    return button;
}

void MainWindow::setupConnetions()
{
    connect(scannBtn, &QPushButton::pressed, this, &MainWindow::onScannBtnHandler);
    connect(refreshBtn, &QPushButton::pressed, this, &MainWindow::onRefreshBtnHandler);
    connect(processBtn, &QPushButton::pressed, this, &MainWindow::onProcessBtnHandler);

    connect(dataTypeSelector,
            static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::dataTypeSelectorChanged);

    connect(compareTypeSelector,
            static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::compareTypeSelectorChanged);

    connect(matchesTable,
            static_cast<void(QTableWidget::*)(int, int)>(&QTableWidget::cellDoubleClicked),
            this,
            &MainWindow::matchesTableDoubleClick);
}

void MainWindow::onScannBtnHandler()
{
    if(!selectedProcess.is_valid()) {
         showNoProcessMessage();
         return;
    }
    if(memoryInteractionStratege->openProcessForInteraction(selectedProcess.pid()) == -1) {
        showOpenProcessErrorMessage();
        return;
    }

   if(!valueTextField->hasAcceptableInput()) {
        showWarningMessage("no acceptable input");
        return;
   }

    dataTypeSelector->setDisabled(true);
    try {
        makeScann();     
    }
    catch(MemoryScannerEngineException &e) {
        showBadScannMessage(e.what());
    }
}

void MainWindow::onRefreshBtnHandler()
{
    dataTypeSelector->setEnabled(true);
    matchesCount->setText(QString::number(0));
    scannCount->setText(QString::number(0));
    matchesTable->setRowCount(0);

    valueTextField->clear();
    refreshAllScanner();
}

void MainWindow::onProcessBtnHandler()
{
    TaskSelectionDialog taskDialog;
    if(taskDialog.exec() != QDialog::Rejected) {
        selectedProcess = taskDialog.getSelectedProcess();
        updateSelectedProcess();
    }
}

void MainWindow::makeScann()
{
    DataType type = getSelectedValueType();

    if(type == Char) {
        char val;
        showWarningMessage("unsupported data type");
        onRefreshBtnHandler();
    }

    if(type == Short) {
        short val = valueTextField->text().toShort();
        std::vector<memoryMatch<short>> matches;

        if(valueTextField->isEnabled()) {
            matches = shortMemoryScanner->executeScanning(selectedProcess.pid(), val, getSelectedCompareType());
        }
        else {
            matches = shortMemoryScanner->executeScanning(selectedProcess.pid(), getSelectedCompareType());
        }

        updateShortMathesTable(matches);
    }

    if(type == Int) {
        int val = valueTextField->text().toInt();
        std::vector<memoryMatch<int>> matches;

        if(valueTextField->isEnabled()) {
            matches = integerMemoryScanner->executeScanning(selectedProcess.pid(), val, getSelectedCompareType());
        }
        else {
            matches = integerMemoryScanner->executeScanning(selectedProcess.pid(), getSelectedCompareType());
        }
        updateIntegerMathesTable(matches);
    }

    if(type == Long) {
        long val = valueTextField->text().toLong();
        std::vector<memoryMatch<long>> matches;

        if(valueTextField->isEnabled()) {
            matches = longMemoryScanner->executeScanning(selectedProcess.pid(), val, getSelectedCompareType());
        }
        else {
            matches = longMemoryScanner->executeScanning(selectedProcess.pid(), getSelectedCompareType());
        }
        updateLongMathesTable(matches);
    }

    if(type == Float) {
        float val = valueTextField->text().toFloat();
        std::vector<memoryMatch<float>> matches;

        if(valueTextField->isEnabled()) {
            matches = floatMemoryScanner->executeScanning(selectedProcess.pid(), val, getSelectedCompareType());
        }
        else {
            matches = floatMemoryScanner->executeScanning(selectedProcess.pid(), getSelectedCompareType());
        }
        updateFloatMathesTable(matches);
    }

    if(type == Dobule) {
        double val = valueTextField->text().toDouble();
        std::vector<memoryMatch<double>> matches;

        if(valueTextField->isEnabled()) {
            matches = doubleMemoryScanner->executeScanning(selectedProcess.pid(), val, getSelectedCompareType());
        }
        else {
            matches = doubleMemoryScanner->executeScanning(selectedProcess.pid(), getSelectedCompareType());
        }
        updateDoubleMathesTable(matches);
    }

    if(type == LongDouble) {
        showWarningMessage("unsupported data type");
        onRefreshBtnHandler();
    }
}

void MainWindow::updateSelectedProcess()
{
    QString processString;
    if(selectedProcess.is_valid()) {
        processString += QString::number(selectedProcess.pid());
        processString += " - ";
        processString += QString::fromStdString(selectedProcess.name());
        selectedProcessLabel->setText(processString);
    }
}

void MainWindow::showNoProcessMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("warning msg");
    msgBox.setText("There is no selected process");
    msgBox.exec();
}

void MainWindow::showOpenProcessErrorMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("warning msg");
    msgBox.setText("Can not scan this process");
    msgBox.exec();
}

void MainWindow::showBadScannMessage(std::string message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("warning message");
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
}

void MainWindow::showWarningMessage(std::string message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("warning message");
    msgBox.setText(QString::fromStdString(message));
    msgBox.exec();
}

void MainWindow::updateIntegerMathesTable(std::vector<memoryMatch<int>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(integerMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(QString::number(matches[i].value)));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

void MainWindow::updateCharacterMathesTable(std::vector<memoryMatch<char>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(characterMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(matches[i].value));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

void MainWindow::updateShortMathesTable(std::vector<memoryMatch<short>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(shortMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(QString::number(matches[i].value)));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

void MainWindow::updateLongMathesTable(std::vector<memoryMatch<long>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(longMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(QString::number(matches[i].value)));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

void MainWindow::updateFloatMathesTable(std::vector<memoryMatch<float>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(floatMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(QString::number(matches[i].value)));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

void MainWindow::updateDoubleMathesTable(std::vector<memoryMatch<double>> matches)
{
    matchesCount->setText(QString::number(matches.size()));
    scannCount->setText(QString::number(doubleMemoryScanner->getScanningCount()));

    matchesAdresses.clear();
    matchesTable->setRowCount(0);
    for(int i = 0; i < matches.size(); i++) {
        matchesTable->setRowCount(i + 1);

        matchesTable->setItem(i, 0, new QTableWidgetItem(pointerToQString(matches[i].addres,12)));
        matchesTable->setItem(i, 1, new QTableWidgetItem(pointerToQString(matches[i].offset, 4)));
        matchesTable->setItem(i, 2, new QTableWidgetItem(QString::number(matches[i].value)));

        if(matches[i].type == heap) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("Heap"));
        }
        else if(matches[i].type == stack) {
            matchesTable->setItem(i, 3, new QTableWidgetItem("stack"));
        }
        else {
            matchesTable->setItem(i, 3, new QTableWidgetItem(""));
        }

        matchesAdresses.push_back(matches[i].addres);
    }
}

QString MainWindow::pointerToQString(uint8_t *ptr, int length)
{
    return QString("0x%1").arg((quintptr)ptr, length, 16, QChar('0'));
}

CompareType MainWindow::getSelectedCompareType()
 {
     int dataIndex = compareTypeSelector->currentIndex();
     if(dataIndex == 0) return Equal;
     if(dataIndex == 1) return Less;
     if(dataIndex == 2) return Greater;  
     /* separator */
     if(dataIndex == 4) return Increased;
     if(dataIndex == 5) return Decreased;
     if(dataIndex == 6) return Unchanged;
     if(dataIndex == 7) return Changed;
     return Unknown;
 }

DataType MainWindow::getSelectedValueType()
{
    int dataIndex = dataTypeSelector->currentIndex();

    if(dataIndex == 0) return Char;
    if(dataIndex == 1) return Short;
    if(dataIndex == 2) return Int;
    if(dataIndex == 3) return Long;
    if(dataIndex == 4) return Float;
    if(dataIndex == 5) return Dobule;
    if(dataIndex == 6) return LongDouble;
    return NoType;
}

void MainWindow::refreshAllScanner()
{
    characterMemoryScanner->refreshScanner();
    shortMemoryScanner->refreshScanner();
    integerMemoryScanner->refreshScanner();
    doubleMemoryScanner->refreshScanner();
    longMemoryScanner->refreshScanner();
    floatMemoryScanner->refreshScanner();

    matchesAdresses.clear();
}

void MainWindow::dataTypeSelectorChanged(int index)
{
    Q_UNUSED(index);
    valueTextField->clear();

    int dataIndex = dataTypeSelector->currentIndex();
    if(dataIndex == 0) {
        valueTextField->setValidator(charValidator);
    }
    if(dataIndex == 1) {
        valueTextField->setValidator(intValidator);
    }
    if(dataIndex == 2) {
        valueTextField->setValidator(intValidator);
    }
    if(dataIndex == 3) {
        valueTextField->setValidator(intValidator);
    }
    if(dataIndex == 4) {
        valueTextField->setValidator(doubleValidator);
    }
    if(dataIndex == 5) {
        valueTextField->setValidator(doubleValidator);
    }
    if(dataIndex == 6) {
        valueTextField->setValidator(doubleValidator);
    }

    //std::cout << "index: " << index << std::endl;
}

void MainWindow::compareTypeSelectorChanged(int index)
{
    if(index > 3) {
        valueTextField->setEnabled(false);
    }
    else {
        valueTextField->setEnabled(true);
    }
}

void MainWindow::makeWrite(QString value)
{
    Q_UNUSED(value);
}

void MainWindow::matchesTableDoubleClick(int row, int col)
{
    Q_UNUSED(col);
    bool ok_btn;
    QString content = QInputDialog::getText(this, tr("get value dialog"),
                                            tr("value:"), QLineEdit::Normal,
                                            "", &ok_btn);

    if(ok_btn && !content.isEmpty()) {

        try {
            DataType selectedType = getSelectedValueType();
            if(selectedType == Char) {
                showWarningMessage("can not write value for this data type");
            }
            if(selectedType == Short) {
                short val = content.toShort();
                shortMemoryScanner->changeMemoryValue(selectedProcess.pid(), val, matchesAdresses[row]);
                updateShortMathesTable(shortMemoryScanner->makeNextScan(selectedProcess.pid(), Changed));
            }
            if(selectedType == Int) {
                int val = content.toInt();
                integerMemoryScanner->changeMemoryValue(selectedProcess.pid(), val, matchesAdresses[row]);
                updateIntegerMathesTable(integerMemoryScanner->makeNextScan(selectedProcess.pid(), Changed));
            }
            if(selectedType == Long) {
                long val = content.toLong();
                longMemoryScanner->changeMemoryValue(selectedProcess.pid(), val, matchesAdresses[row]);
                updateLongMathesTable(longMemoryScanner->makeNextScan(selectedProcess.pid(), Changed));
            }
            if(selectedType == Float) {
                float val = content.toFloat();
                floatMemoryScanner->changeMemoryValue(selectedProcess.pid(), val, matchesAdresses[row]);
                updateFloatMathesTable(floatMemoryScanner->makeNextScan(selectedProcess.pid(), Changed));
            }
            if(selectedType == Dobule) {
                double val = content.toDouble();
                doubleMemoryScanner->changeMemoryValue(selectedProcess.pid(), val, matchesAdresses[row]);
                updateDoubleMathesTable(doubleMemoryScanner->makeNextScan(selectedProcess.pid(), Changed));
            }
        }
        catch(MemoryScannerEngineException &e) {
            showBadScannMessage(e.what());
        }
    }
}

