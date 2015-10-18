#ifndef DUFILEDIALOG_H
#define DUFILEDIALOG_H

#include <QDialog>
#include <QDir>

class QLineEdit;
class QLabel;
class QDialogButtonBox;
class QToolButton;

class DuFileDialog : public QDialog
{
public:
    explicit DuFileDialog(const QString &title, const QString &labelText,
                          const QString &filter,
                          const QString &dir = QDir::rootPath(),
                          bool saveOpen = true, QWidget *parent = nullptr);
    QString getFilename() const;
private:
    void makeConfigurations();
    void makeConnections();

    QLineEdit *mFilenameLineEdit;
    QLabel *mLabel;
    QDialogButtonBox *mDialogButtonBox;
    QToolButton *mToolButton;
    QString mTitle;
    QString mFilter;
    QString mDir;
    bool mSaveOpen;
};

#endif // DUFILEDIALOG_H
