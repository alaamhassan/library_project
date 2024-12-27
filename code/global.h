#ifndef GLOBALS_H
#define GLOBALS_H


#include "admin_adminssectionwindow.h"
#include "mainwindow.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>


#include <QScrollArea>
// Declare pointers as extern to avoid multiple definitions
extern admin_AdminsSectionWindow* AdminSectionWindow;
extern MainWindow* mainWindow;

extern QSqlDatabase library_db;

void initialize_database();
void close_connection();
bool open_connection();


QMap<QString, QLineEdit*> createDynamicLineEdits(QWidget* parent, const QStringList& fieldNames,int LabelWidth=125);

void populateDynamicGrid(QScrollArea* scrollArea,
                        const QString& tableName,
                        const int* start_DisplayNamesIndex,
                        const QStringList& DisplayNames,
                        const QStringList& fields,
                        const QString& queryCondition,
                        QWidget* parent,
                        bool displayVertically=false,
                        const QString& isUnique="",
                        const QString& Id="member_id");


void deleteField(const QString& tableDisplayName,
                     const QString& tableName,
                     const QString& queryCondition,
                     QWidget* parent,
                     int current_ID=0);


void UpdateField(const QString& tableDisplayName,
                 const QString& tableName,
                 const QMap<QString, QVariant>& fieldValues,
                 const QString& conditionQuery,
                 QWidget* parent = nullptr);


void AddField(const QString& tableDisplayName,
              const QString& tableName,
              const QMap<QString, QVariant>& fieldValues,
              QWidget* parent = nullptr);


QStringList SelectField(const QString& tableName,
                        const QStringList& fields,
                        const QString& conditionQuery=" ;");

#endif // GLOBALS_H
