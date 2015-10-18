#include "ExtractFileDialog.h"
#include "ui_ExtractFileDialog.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QCompleter>

ExtractFileDialog::ExtractFileDialog(int index, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExtractFileDialog)
{
    ui->setupUi(this);
    setWindowTitle("Extract file");
    QSqlQuery q;
    q.exec("SELECT filename FROM DuData");
    while (q.next()) {
        ui->filenameComboBox->addItem(q.value(0).toString());
    }
    ui->filenameComboBox->setCurrentIndex(index);
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    ui->destinationDirectoryLineEdit->setCompleter(new QCompleter
                                                   (fileSystemModel, this));
}

ExtractFileDialog::~ExtractFileDialog()
{
    delete ui;
}

QString ExtractFileDialog::getDestinationDirectory() const
{
    return ui->destinationDirectoryLineEdit->text();
}

QString ExtractFileDialog::getSelectedFilename() const
{
    return ui->filenameComboBox->currentText();
}

void ExtractFileDialog::on_toolButton_clicked()
{
    auto directory = QFileDialog::getExistingDirectory(this,
                                                       "Destination directory",
                                                       QDir::rootPath());
    ui->destinationDirectoryLineEdit->setText(directory);
}

void ExtractFileDialog::on_buttonBox_accepted()
{
    accept();
}

void ExtractFileDialog::on_buttonBox_rejected()
{
    reject();
}
