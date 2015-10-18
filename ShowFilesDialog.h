#ifndef SHOWFILESDIALOG_H
#define SHOWFILESDIALOG_H

#include <QDialog>

namespace Ui
{
class ShowFilesDialog;
}

class MainWidget;
class QSqlTableModel;

class ShowFilesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ShowFilesDialog(QWidget *parent = nullptr);
    ~ShowFilesDialog();
    MainWidget *getParent() const { return mParent; }
private slots:
    void on_actionInsert_a_file_triggered();
    void on_actionExtract_this_file_triggered();
    void on_actionDelete_this_file_triggered();

private:
    Ui::ShowFilesDialog *ui;
    MainWidget *mParent;
    QSqlTableModel *mModel;
};

#endif // SHOWFILESDIALOG_H
