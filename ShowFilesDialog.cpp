#include "ShowFilesDialog.h"
#include "ui_ShowFilesDialog.h"
#include "MainWidget.h"
#include "DuDatabase.h"
#include "DuFileDialog.h"
#include "ExtractFileDialog.h"
#include <QSqlTableModel>
#include <QFile>
#include <QMessageBox>

ShowFilesDialog::ShowFilesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowFilesDialog)
{
    ui->setupUi(this);
    setWindowTitle("File viewer");
    mParent = static_cast<MainWidget *>(parent);
    mModel = new QSqlTableModel(this);
    mModel->setTable("DuData");
    mModel->select();
    ui->tableView->setModel(mModel);
    ui->tableView->hideColumn(0);
    mModel->setHeaderData(1, Qt::Horizontal, "Filename");
    ui->tableView->hideColumn(2);
    ui->tableView->addAction(ui->actionInsert_a_file);
    ui->tableView->addAction(ui->actionExtract_this_file);
    ui->tableView->addAction(ui->actionDelete_this_file);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

ShowFilesDialog::~ShowFilesDialog()
{
    delete ui;
}

void ShowFilesDialog::on_actionInsert_a_file_triggered()
{
    DuFileDialog d("Open file", "Filename", "Any file (*.*)", QDir::rootPath(),
                 false, this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    auto filename = d.getFilename();
    if (filename.isEmpty()) {
        QMessageBox::critical(this, "Error", "The filename is empty");
        return;
    }
    mParent->database()->insertFile(filename);
    mModel->select();
}

void ShowFilesDialog::on_actionExtract_this_file_triggered()
{
    ExtractFileDialog d(ui->tableView->currentIndex().row(), this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    QFile file(d.getDestinationDirectory() + "/" + d.getSelectedFilename());
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    file.write(mParent->database()->extractFile(ui->tableView->currentIndex()
                                                .data().toString()));
    file.flush();
    file.close();
}

void ShowFilesDialog::on_actionDelete_this_file_triggered()
{
    mModel->removeRow(ui->tableView->currentIndex().row());
    mModel->select();
}
