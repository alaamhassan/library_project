#include "global.h"
#include "QGridLayout"
#include "QScrollArea"
#include "qpushbutton.h"
#include "stylesSheetGlobal.h"

// Function: initialize_database
// Description: Sets the database path and adds a SQLite driver for the application.
void initialize_database()
{
    // Set the path to the database file relative to the application directory.
    QString database_path=QCoreApplication::applicationDirPath()+"/database/library.db";

    // Add an SQLite database driver to the application.
    library_db=QSqlDatabase::addDatabase("QSQLITE");

    library_db.setDatabaseName(database_path);
}

// Function: close_connection
// Description: Closes the connection to the database and logs a message.
void close_connection()
{
    library_db.close();
    qDebug()<<("close...");

}


// Function: open_connection
// Description: Opens a connection to the database. Returns true if successful, otherwise false.
bool open_connection()
{
    if(!library_db.open())
    {
        qDebug()<<("Failed to open the database!");
        return false;
    }
    else
    {
        qDebug()<<("Connected...");
        return true;
    }
}

// Function: populateDynamicGrid
// Description: Dynamically populates a grid layout within a QScrollArea based on database query results.
void populateDynamicGrid(QScrollArea* scrollArea,
                         const QString& tableName,
                         const int* start_DisplayNamesIndex,
                         const QStringList& DisplayNames,// {ID,Phone}
                         const QStringList& fields, //array of strings {member_name,member_id,member_phone}
                         const QString& queryCondition, // join
                         QWidget* parent,
                         bool displayVertically,
                         const QString& isUnique,//""
                         const QString& Id) {

//member_name,member_id,member_phone

    // Clear any existing layout in the parent widget.
    QLayout* currentLayout = parent->layout();
    if (currentLayout) {
        // Remove all items from the layout first
        QLayoutItem* item;
        while ((item = currentLayout->takeAt(0)) != nullptr) {
            delete item->widget();  // Delete the widget inside the layout
            delete item;  // Delete the layout item itself
        }
        // Optionally delete the layout itself
        delete currentLayout;

        //layout ->item->widgets
    }



    // Open database connection
    open_connection();

    // Dynamically create models and queries for the specified fields.
    QMap<QString, QSqlQueryModel*> models;
    QMap<QString, QSqlQuery*> queries;

    //for each field(iteam) in fields(qstringlist)

    for (const QString& field : fields) {
        models[field] = new QSqlQueryModel();
        //models[member_id]= new QSqlQueryModel();

        queries[field] = new QSqlQuery(library_db);


        // Dynamically build the query
        QString queryStr = QString("SELECT "+isUnique+" %1 FROM %2").arg(field, tableName);
        //select member_id FROM members

        if (!queryCondition.isEmpty()) {
            queryStr += queryCondition;
        }
        //queryStr =select member_id FROM members where member_id=3;
        //queryStr =select member_phone FROM members where member_id=3;

        // Prepare and execute the query.
        queries[field]->prepare(queryStr);
        //queries[member_id]
        queries[field]->exec();
        //
        models[field]->setQuery(*queries[field]);
    }


    // Create a new grid layout for the parent widget.
    QGridLayout* gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(0);


    // Store dynamically created buttons.
    QVector<QPushButton*> buttons;


    // Check the row count from the first field (assumes consistent row count across fields)
    int rowCount = models[fields.first()]->rowCount();

    //select member_id,member_phone from members
    //1,2,3
    //phone1
    for (int i = 0; i < rowCount; i++) {

        QStringList fieldValues; //{}

        //for each item in fields
        for (const QString& field : fields) {

            fieldValues << models[field]->record(i).value(0).toString();
        }

        //{1,phone1}

        // Create a separator line
        QFrame* line = new QFrame(parent);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setStyleSheet("background-color: gray; border: none; height: 0.1px; width: 0.5px;");


        if(!displayVertically)
        {
            // Create a button for the first field value (e.g., a name)
            QPushButton* button = new QPushButton(fieldValues[0], parent);
            button->setObjectName("btn_" + fieldValues[0]);//btn_1
            button->setProperty("id", fieldValues[1]); // Store the ID as a property //{member_name,member_id,member_phone}
            button->setStyleSheet(NameButton_Style("btn_" + fieldValues[0]));//btn_1
            buttons.append(button);

            //connect button to signal
            QAbstractAnimation::connect(button,SIGNAL(clicked()),parent,SLOT(On_MemberName_Clicked()));

            // Create a label with details for all fields
            QString labelDetails;
            int displayNamesIndex=0;

            for (int j = *start_DisplayNamesIndex; j < fields.size(); j++) {

                if(DisplayNames[displayNamesIndex]=="Returned") //1,0 returned=1,returned
                {
                    if(fieldValues[j]=="1")
                        fieldValues[j]="Yes";
                    else
                        fieldValues[j]="No";
                }

                labelDetails += QString("%1: %2").arg(DisplayNames[displayNamesIndex], fieldValues[j]);
                //ID: 1, PHONE: phone1

                if (j < fields.size() - 1) labelDetails += ", ";

                displayNamesIndex++;
            }

            //labelDetails= ID: 1, Role: Manager

            QLabel* label = new QLabel(labelDetails, parent);
            label->setStyleSheet(GridLabel_Style());

            // Add widgets to the grid layout
            gridLayout->addWidget(button); //name button
            gridLayout->addWidget(label); //labelDetails= ID: 1, Role: Manager
            gridLayout->addWidget(line); //

            // // Connect button click signal
            // QAbstractAnimation::connect(button, &QPushButton::clicked, [fieldValues]() {
            //     qDebug() << "Button clicked for: " << fieldValues;});

        }
        else
        {
            // Vertical Layout: Single member with all fields listed vertically
            for (int j = 0; j < fields.size(); j++) {

                QFrame* line = new QFrame(parent);
                line->setFrameShape(QFrame::HLine);
                line->setFrameShadow(QFrame::Sunken);
                line->setStyleSheet("background-color: gray; border: none; height: 1px; width: 0.5px;");

                if(DisplayNames[j]=="Returned")
                {
                    if(fieldValues[j]=="1")
                        fieldValues[j]="Yes";
                    else
                        fieldValues[j]="No";
                }

                QLabel* fieldLabel = new QLabel(QString("%1: %2").arg(DisplayNames[j], fieldValues[j]), parent);
                fieldLabel->setStyleSheet(GridLabel_Style());

                gridLayout->addWidget(fieldLabel, j * 2, 0);
                gridLayout->addWidget(line,j * 2+1,0);

            }

        }
    }

    // Set the layout into the scroll area
    scrollArea->viewport()->setStyleSheet("background: transparent;");


    QWidget* contentWidget = new QWidget(parent);
    contentWidget->setLayout(gridLayout);
    scrollArea->setWidget(contentWidget);

    //scroll area->widget->gridlayout


    scrollArea->setStyleSheet(scrollArea_Style());


    // Close the database connection
    close_connection();

}



// Functions deleteField, UpdateField, and AddField handle CRUD operations on database tables.
// For brevity, the comments for these functions would explain:
// - They dynamically build and execute SQL queries.
// - They use QMessageBox for user feedback on operation success/failure.
// - They use `QMap<QString, QVariant>` for key-value pairs of field data.

void deleteField(const QString& tableDisplayName,
                 const QString& tableName,
                 const QString& queryCondition,
                 QWidget* parent, //
                 int current_ID) { //book_id=3

    if(current_ID==0)
    {
        QMessageBox::critical(parent,"Delete "+tableDisplayName,"Error: Please, Choose a "+tableDisplayName+"!");
        //Delete Book
        //choose a book
    }
    else
    {

        open_connection();

        QSqlQuery* deleteMember_query =new QSqlQuery(library_db);


        deleteMember_query->prepare("DELETE FROM '"+tableName+"' "+queryCondition);


        if(!deleteMember_query->exec())
        {
            QMessageBox::critical(parent,"Delete "+tableDisplayName,"Error: Couldn't delete the "+tableDisplayName+"!");
        }
        else
        {
            QMessageBox::information(parent,"Delete "+tableDisplayName,"Success: "+tableDisplayName+" is Deleted!");
        }

        close_connection();
    }

}




void UpdateField(const QString& tableDisplayName,
                 const QString& tableName,
                const QMap<QString, QVariant>& fieldValues,
                const QString& conditionQuery, //where book_id=4
               QWidget* parent)
{
    open_connection();

    // Start constructing the SQL query
    QString queryStr = "UPDATE " + tableName + " SET ";
    //UPDATE book set

    QString updates="";
    for (auto it = fieldValues.cbegin(); it != fieldValues.cend(); ++it) {
        QString field = it.key();
        QString value = it.value().toString();

        updates+=QString("%1 = CASE WHEN '%2' != '' THEN '%2' ELSE %1 END").arg(field,value);

        //updates =book_id CASE WHEN 3 !='' THEN 3 ELSE book_id END,
        // book_author case when '' !='' THEN '' ELSE book_author END

        if (it != std::prev(fieldValues.cend())) {
            updates += ", "; // Add a comma between fields except after the last one
        }
    }


    queryStr += updates+conditionQuery;
    // UPDATE book set book_id CASE WHEN 3 !='' THEN 3 ELSE book_id END,
    // book_author case when '' !='' THEN '' ELSE book_author END where book_id=4



    QSqlQuery* Edit_query =new QSqlQuery(library_db);


    Edit_query->prepare(queryStr);


    if(!Edit_query->exec())
    {
        QMessageBox::critical(parent,"Edit "+tableDisplayName,"Error: Couldn't Update the "+tableDisplayName+" Info!");
    }
    else
    {
        QMessageBox::information(parent,"Edit "+tableDisplayName,"Success: "+tableDisplayName+" Info is Updated!");
    }

    close_connection();
}







void AddField(const QString& tableDisplayName,
                 const QString& tableName,
              const QMap<QString, QVariant>& fieldInfo, //{"book_id":3,"book_author":alex,...
                 QWidget* parent)
{
    open_connection();

    // Start constructing the SQL query
    QString queryStr = "INSERT INTO " + tableName + " ( ";
    //INSERT INTO books (

    QString fieldNames="";
    QString fieldValues="";

    for (auto it = fieldInfo.cbegin(); it != fieldInfo.cend(); ++it) {
        QString field = it.key();
        QString value = it.value().toString();
        fieldNames+=QString("%1").arg(field);
        //book_id
        fieldValues+=QString("'%1'").arg(value);
        //3


        if (it != std::prev(fieldInfo.cend())) {
            fieldNames += ", "; // Add a comma between fields except after the last one
            //book_id,
            fieldValues += ", ";
            //3,
        }
    }
    //fieldNames= book_id, book_author
    //fieldValues=3, alex
    queryStr += fieldNames+" ) VALUES ("+fieldValues +");";

 //INSERT INTO books (book_id, book_author ) VALUES (3, alex);


    QSqlQuery* Add_query =new QSqlQuery(library_db);


    Add_query->prepare(queryStr);


    if(!Add_query->exec())
    {
        QMessageBox::critical(parent,"Add "+tableDisplayName,"Error: Couldn't add the "+tableDisplayName+" Info!");

        QString error = Add_query->lastError().text();
        QMessageBox::critical(parent, "Error", "SQL Error: " + error);

    }
    else
    {
        QMessageBox::information(parent,"Add "+tableDisplayName,"Success: "+tableDisplayName+" was added!");
    }

    close_connection();
}



QStringList SelectField(const QString& tableName,
                        const QStringList& fields,
                        const QString& conditionQuery)
{

    QStringList fieldvalues={};

    open_connection();

    // Start constructing the SQL query
    QString queryStr = "SELECT ";


    for (int j=0; j<fields.size();j++) {
        queryStr +=fields[j];
        //select book_id, book_author

        if(j<fields.size()-1)
        {
            queryStr +=", ";
        }
    }

    queryStr += " FROM "+tableName +conditionQuery;
    //select book_id, book_author FROM books where book_genra=history;
    //(1,alex),(5,alaa)




    QSqlQuery* select_query =new QSqlQuery(library_db);


    select_query->prepare(queryStr);


    if(select_query->exec())
    {
        while (select_query->next())
        {
            for (int i = 0; i < select_query->record().count(); i++) {
                fieldvalues.append(select_query->value(i).toString());
            }
        }
    }


    close_connection();

    return fieldvalues;
}




// Function: createDynamicLineEdits
// Description: Dynamically creates QLineEdit widgets for a given list of field names.
// The positions and dimensions of the widgets are calculated based on the input field count and spacing.

QMap<QString, QLineEdit*> createDynamicLineEdits(QWidget* parent, const QStringList& fieldNames,int LabelWidth) {
    // Starting position and dimensions for the widgets
    int startX = 76;             // X-coordinate for labels and line edits
    int startY = 245;             // Y-coordinate for the first widget
    int labelWidth = LabelWidth;        // Width of QLabel
    int lineEditWidth = 150;     // Width of QLineEdit
    int widgetHeight = 30;       // Height of both QLabel and QLineEdit
    int verticalSpacing = (240-(fieldNames.size()*widgetHeight))/fieldNames.size();    // Spacing between rows

    // Store references to the dynamically created QLineEdit widgets
    QMap<QString, QLineEdit*> lineEditMap;

    // Iterate over the field names
    for (int i = 0; i < fieldNames.size(); ++i) {
        const QString& fieldName = fieldNames[i];

        // Create a QLabel for the field
        QLabel* label = new QLabel(fieldName + ":", parent);
        label->setGeometry(startX, startY + i * (widgetHeight + verticalSpacing), labelWidth, widgetHeight);
        label->show();


        // Create a QLineEdit for the field
        QLineEdit* lineEdit = new QLineEdit(parent);
        lineEdit->setGeometry(startX + labelWidth + 10, startY + i * (widgetHeight + verticalSpacing), lineEditWidth, widgetHeight);
        lineEdit->show();

        // Store the lineEdit in the map
        lineEditMap[fieldName] = lineEdit;
    }

    return lineEditMap;

    // Now you can use lineEditMap to access specific QLineEdit widgets by field name
}





