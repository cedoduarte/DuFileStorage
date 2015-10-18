#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui
{
class MainWidget;
}

class DuDatabase;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    enum Actions
    {
        CREATE_DATABASE,
        OPEN_DATABASE,
        SHOW_FILES
    };

    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    DuDatabase *database() const { return mDb; }
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
private:
    void createDatabase();
    void openDatabase();
    void showFiles();
    void makeConnections();

    Ui::MainWidget *ui;
    DuDatabase *mDb;
};

#endif // MAINWIDGET_H
