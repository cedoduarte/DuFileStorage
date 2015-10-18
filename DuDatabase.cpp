#include "DuDatabase.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QVariant>
#include <QFileInfo>

#define CREATE_TABLE \
    "CREATE TABLE IF NOT EXISTS DuData " \
    "(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" \
    ", filename TEXT UNIQUE NOT NULL" \
    ", data BLOB NOT NULL)"

DuDatabase::DuDatabase(QObject *parent)
    : QObject(parent)
{
    connect(this, &DuDatabase::databaseOpened, [&](bool ok, const QString &) {
        if (!ok) {
            return;
        }
        configureDatabase();
    });
}

void DuDatabase::startDatabase(const QString &dbName)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(dbName);
    emit databaseOpened(mDb.open(), mDb.lastError().text());
}

void DuDatabase::insertFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        emit anErrorHasOccurred(file.errorString());
        return;
    }
    auto arrayData = file.readAll();
    file.close();
    QSqlQuery q;
    q.prepare("INSERT INTO DuData (filename, data) VALUES (?,?)");
    q.addBindValue(QFileInfo(filename).fileName());
    q.addBindValue(arrayData);
    if (!q.exec()) {
        emit anErrorHasOccurred(q.lastError().text());
    }
}

QByteArray DuDatabase::extractFile(const QString &filename)
{
    QSqlQuery q;
    if (!q.exec(QString("SELECT data FROM DuData WHERE filename LIKE '%1'")
                .arg(filename))) {
        emit anErrorHasOccurred(q.lastError().text());
        return QByteArray();
    }
    q.next();
    return q.value(0).toByteArray();
}

void DuDatabase::configureDatabase()
{
    QSqlQuery q;
    if (!q.exec(CREATE_TABLE)) {
        emit anErrorHasOccurred(q.lastError().text());
    }
}

