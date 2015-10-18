#include "DuFileDialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QToolButton>
#include <QFileSystemModel>
#include <QCompleter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

DuFileDialog::DuFileDialog(const QString &title, const QString &labelText,
                           const QString &filter, const QString &dir,
                           bool saveOpen, QWidget *parent)
    : QDialog(parent)
{
    mFilenameLineEdit = new QLineEdit(this);
    mLabel = new QLabel(labelText, this);
    mDialogButtonBox = new QDialogButtonBox(this);
    mToolButton = new QToolButton(this);
    mTitle = title;
    mFilter = filter;
    mDir = dir;
    mSaveOpen = saveOpen;
    mLabel->setText(labelText);

    makeConfigurations();
    makeConnections();
}

QString DuFileDialog::getFilename() const
{
    return mFilenameLineEdit->text();
}

void DuFileDialog::makeConfigurations()
{
    setWindowTitle(mTitle);
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    mFilenameLineEdit->setCompleter(new QCompleter(fileSystemModel, this));
    mDialogButtonBox->setStandardButtons(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);
    mToolButton->setIcon(QIcon(":/browse"));

    auto hbox = new QHBoxLayout;
    hbox->addWidget(mLabel);
    hbox->addWidget(mFilenameLineEdit);
    hbox->addWidget(mToolButton);
    auto vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addWidget(mDialogButtonBox);
    setLayout(vbox);
    resize(width()*4, height());
}

void DuFileDialog::makeConnections()
{
    connect(mToolButton, &QToolButton::clicked, [&]() {
        QString filename;
        if (mSaveOpen) {
            filename = QFileDialog::getSaveFileName(this, mTitle, mDir,
                                                    mFilter);
        } else {
            filename = QFileDialog::getOpenFileName(this, mTitle, mDir,
                                                    mFilter);
        }
        mFilenameLineEdit->setText(filename);
    });

    connect(mDialogButtonBox, &QDialogButtonBox::accepted, this, accept);
    connect(mDialogButtonBox, &QDialogButtonBox::rejected, this, reject);
}
