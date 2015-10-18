#ifndef DUDATABASE_H
#define DUDATABASE_H

#include <QObject>
#include <QSqlDatabase>

class DuDatabase : public QObject
{
    Q_OBJECT
public:
    DuDatabase(QObject *parent = nullptr);
    void startDatabase(const QString &dbName);
    bool isOpen() const { return mDb.isOpen(); }
    void insertFile(const QString &filename);
    QByteArray extractFile(const QString &filename);
signals:
    void databaseOpened(bool, const QString &);
    void anErrorHasOccurred(const QString &);
private:
    void configureDatabase();

    QSqlDatabase mDb;
};

#endif // DUDATABASE_H
