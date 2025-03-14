#include "interface.h"

QString PATH = "C:/Users/tokar/Documents/777/files" ;

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Main window");
    setFixedSize(800,500);
    _review = new QPushButton("Review", this);
    _painter = new TPaint();
    _canvas = new TCanvas(_painter);
    _review->setGeometry(100,150,100,30);
    _fileName = new QLabel(this);
    _fileName->setGeometry(10,170,300,30);
    _loadFromFileBtn = new QPushButton("Load", this);
    _fileListWidget = new QListWidget(this);
    _fileListWidget->setViewMode(QListView::ListMode);
    _fileListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _fileListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _fileListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadFilesIntoListWidget();
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(_loadFromFileBtn);
    hlayout->addWidget(_review);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout-> addWidget(_fileListWidget);
    vlayout-> addWidget(_fileName);
    vlayout-> addLayout(hlayout);
    connect(_review, SIGNAL(clicked()),this,SLOT(onReviewBtnClicked()));
    connect(_loadFromFileBtn, SIGNAL(clicked()), this, SLOT(onloadFromFileBtnClicked()));
    this->setLayout(vlayout);
    _canvas->setAttribute( Qt::WA_QuitOnClose, false );
}
void TInterface::openFile(QString fname){
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QString lastOpenFile("Last file: ");
    lastOpenFile+=fname;
    _fileName->setText(lastOpenFile);
    GetMatrix matrix(fname);
    int result = matrix.checkMatrix();
    if(result == 0)
    {
        _painter->setGraph(matrix.getFullMatrix());
        _canvas->update();
        _canvas->show();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Неверный формат матрицы!");
        messageBox.setFixedSize(500,200);
    }
}

TInterface::~TInterface()
{
    delete _review;
    delete _fileName;
    delete _painter;
    delete _canvas;
}

void TInterface::onReviewBtnClicked()
{

    QString fname = QFileDialog::getOpenFileName(this, "Выберите файл", "C://");
    openFile(fname);
}

void TInterface::onloadFromFileBtnClicked()
{
    QString f = _fileListWidget->currentItem()->text();
    if (f.isEmpty()) {
        QMessageBox::information(this, tr("Информация"), tr("Пожалуйста, выберите файл."));
        return;
    }
    QString fname = PATH + "/" + f;
    openFile(fname);
}

void TInterface::loadFilesIntoListWidget() {
    QDir dir(PATH);
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot);

    foreach (const QString &file, files) {
        QListWidgetItem *item = new QListWidgetItem(file);
        _fileListWidget->addItem(item);
    }
}


