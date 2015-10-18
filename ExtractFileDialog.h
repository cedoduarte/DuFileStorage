#ifndef EXTRACTFILEDIALOG_H
#define EXTRACTFILEDIALOG_H

#include <QDialog>

namespace Ui
{
class ExtractFileDialog;
}

class ExtractFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExtractFileDialog(int index, QWidget *parent = nullptr);
    ~ExtractFileDialog();
    QString getDestinationDirectory() const;
    QString getSelectedFilename() const;
private slots:
    void on_toolButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::ExtractFileDialog *ui;
};

#endif // EXTRACTFILEDIALOG_H
