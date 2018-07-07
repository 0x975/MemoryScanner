#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>

#include <iostream>
#include "memoryscannerengine.h"
#include "taskselectiondialog.h"
#include "memoryscannerengine.h"
#include "memoryinteractionstratege.h"

#include "linuxmemoryinteraction.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTableWidget* setupMathcesTable();
    QGroupBox* createMatchesPanel();
    QGroupBox* createScannerPanel();
    QPushButton* createProcessBtn();
    QPushButton* createScannerBtn();
    QPushButton* createRefreshBtn();
    QComboBox* createDataTypeSelector();

    void setupConnetions();
    void onScannBtnHandler();
    void onRefreshBtnHandler();
    void onProcessBtnHandler();

    void updateSelectedProcess();
    void showNoProcessMessage();
    void showBadScannMessage(std::string message);
    void showWarningMessage(std::string message);
    void showOpenProcessErrorMessage();

    void makeScann();
    void makeWrite(QString value);

    void updateIntegerMathesTable(std::vector<memoryMatch<int>> matches);
    void updateCharacterMathesTable(std::vector<memoryMatch<char>> matches);
    void updateShortMathesTable(std::vector<memoryMatch<short>> matches);
    void updateLongMathesTable(std::vector<memoryMatch<long>> matches);
    void updateFloatMathesTable(std::vector<memoryMatch<float>> matches);
    void updateDoubleMathesTable(std::vector<memoryMatch<double>> matches);

    QString pointerToQString(uint8_t *ptr, int length);
    CompareType getSelectedCompareType();
    DataType getSelectedValueType();
    void refreshAllScanner();

private slots:
    void dataTypeSelectorChanged(int index);
    void compareTypeSelectorChanged(int index);
    void matchesTableDoubleClick(int row, int col);

private:
    ProcessDescriptor selectedProcess;
    MemoryInteractionStratege  *memoryInteractionStratege;

    MemoryScannerEngine<int>    *integerMemoryScanner;
    MemoryScannerEngine<char>   *characterMemoryScanner;
    MemoryScannerEngine<short>  *shortMemoryScanner;
    MemoryScannerEngine<long>   *longMemoryScanner;
    MemoryScannerEngine<float>  *floatMemoryScanner;
    MemoryScannerEngine<double> *doubleMemoryScanner;
/*
    MemoryScannerEngine<uint8_t> *uint8MemoryScanner;
    MemoryScannerEngine<uint16_t> *uint16MemoryScanner;
    MemoryScannerEngine<uint32_t> *uint32MemoryScanner;
    MemoryScannerEngine<uint64_t> *uint64MemoryScanner;

    MemoryScannerEngine<int8_t> *int8MemoryScanner;
    MemoryScannerEngine<int16_t> *int16MemoryScanner;
    MemoryScannerEngine<int32_t> *int32MemoryScanner;
    MemoryScannerEngine<int64_t> *int64MemoryScanner;
*/
    std::vector<uint8_t*> matchesAdresses;
    QTableWidget *matchesTable;
    QLabel *matchesCount;

    QPushButton *processBtn;
    QLabel *selectedProcessLabel;

    QLineEdit *valueTextField;
    QComboBox *dataTypeSelector;
    QComboBox *compareTypeSelector;
    QProgressBar *scannProgress;
    QLabel *scannCount;
    QPushButton *refreshBtn;
    QPushButton *scannBtn;
};

#endif // MAINWINDOW_H
