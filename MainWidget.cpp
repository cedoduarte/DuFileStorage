#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "DuFileDialog.h"
#include "DuDatabase.h"
#include "ShowFilesDialog.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("DuFileStorage");
    mDb = new DuDatabase(this);
    ui->label->setText("<b>The database is not open</b>");
    ui->listWidget->setViewMode(QListView::IconMode);
    makeConnections();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_listWidget_clicked(const QModelIndex &index)
{
    const int row = index.row();
    switch (row) {
    case CREATE_DATABASE:
        createDatabase();
        return;
    case OPEN_DATABASE:
        openDatabase();
        return;
    }
    if (!mDb->isOpen()) {
        QMessageBox::critical(this, "Error", "The database is not open");
        return;
    }
    switch (row) {
    case SHOW_FILES:
        showFiles();
        return;
    }
}

void MainWidget::createDatabase()
{
    DuFileDialog d("New database", "Database filename",
                 "DuData (*.ddata);;Any file (*.*)", QDir::rootPath(), true,
                 this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    auto dbFilename = d.getFilename();
    if (dbFilename.isEmpty()) {
        ui->label->setText("<b>The database is not open</b>");
        return;
    }
    ui->label->setText("<b>Opened database: " + dbFilename + "</b>");
    mDb->startDatabase(dbFilename);
}

void MainWidget::openDatabase()
{
    DuFileDialog d("Open database", "Database filename",
                 "DuData (*.ddata);;Any file (*.*)", QDir::rootPath(), false,
                 this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    auto dbFilename = d.getFilename();
    if (dbFilename.isEmpty()) {
        ui->label->setText("<b>The database is not open</b>");
        return;
    }
    ui->label->setText("<b>Opened database: " + dbFilename + "</b>");
    mDb->startDatabase(dbFilename);
}

void MainWidget::showFiles()
{
    ShowFilesDialog d(this);
    d.exec();
}

void MainWidget::makeConnections()
{
    connect(mDb, &DuDatabase::databaseOpened, [&](bool ok, const QString &error)
    {
        if (!ok) {
            ui->label->setText("<b>" + error + "</b>");
        }
    });

    connect(mDb, &DuDatabase::anErrorHasOccurred, [&](const QString &error) {
        ui->label->setText("<b>" + error + "</b>");
    });
}
