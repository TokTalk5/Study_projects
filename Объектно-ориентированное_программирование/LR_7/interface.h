#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>

#include "getmatrix.h"
#include "paint.h"
#include "canvas.h"

class TInterface : public QWidget
{
    Q_OBJECT

    QPushButton* _review;
    QLabel* _fileName;
    QPushButton* _loadFromFileBtn;
    QListWidget* _fileListWidget;

    TPaint* _painter;
    TCanvas* _canvas;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
    void loadFilesIntoListWidget();

private:
    void openFile(QString);


public slots:
    void onReviewBtnClicked();
    void onloadFromFileBtnClicked();


};
#endif // TINTERFACE_H
