#include "stylesSheetGlobal.h"

QString NameButton_Style(QString ButtonName)
{
    return "QPushButton#"+ButtonName+
           "{"
           "Text-align:left;"
           "font-family:century gothic;"
           "font-size:18px;"
           "background: transparent;"
           "color:orange;"
           "}"
           "QPushButton#"+ButtonName+":hover"
           "{"
           "font-size:22px;"
           "color:yellow;"
           "}";
}

QString GridLabel_Style()
{
    return
        "Text-align:left;"
        "font-family:century gothic;"
        "font-size:18px;"
        "background: transparent;"
        "color:black;";

}

QString pushButton_Style()
{
    return
        "Text-align:left;"
        "font-family:century gothic;"
        "font-size:18px;"
        "color:green;";
}


QString label_Style(QString field)
{
    return
    "<font color=black><u><phone></u></font>"
    +field+
    "<font color=black></font>";
}

QString dashboard_button_Style()
{
    return
        "QPushButton{"
        "font-size:22px;"
        "border-radius:10px;"
        "background-color:#ffffff;"
        "color:#010101;"
        "font-family:Segoe UI;"
        //"font-weight: bold;"
        "}"

        "QPushButton:hover{"
        "font-size:24px;"
        "border-radius:10px;"
        "background-color:#ffffff;"
        "border: 3px solid #fca72b;"
        "border-color:#fca72b;"
        "}"

        "QPushButton:pressed{"
        "border-radius:10px;"
        "background-color:#e0e0e0;"  // Light gray background when pressed
        "border: 3px solid #fca72b;"
        "border-color:#fca72b;"
        "box-shadow: inset 0 0 5px rgba(0, 0, 0, 0.3);"
        "}"
        ;
}

QString nonFilled_button_Style()
{
    return
        "QPushButton{"
        "font-size:15px;"
        "border-radius:10px;"
        "border: 3px solid #fca72b;"
        "border-color:#fca72b;"
        "background-color:#fff2e7;"
        "color:#010101;"
        "font-family:Segoe UI;"
        //"font-weight: bold;"
        "}"

        "QPushButton:hover{"
        "font-size:17px;"
        "background-color:#fca72b;"
        "}"

        // "QPushButton:pressed{"
        // "border-radius:10px;"
        // "border: 2px solid #90978E;"
        // "border-color:#90978E;"
        // "background-color:#1E3706;"
        // "color:#90978E;"
        // "}"
        ;
}

QString filled_button_Style()
{
    return
        "QPushButton{"
        "font-size:15px;"
        "border-radius:10px;"
        "border: 3px solid #fca72b;"
        "border-color:#fca72b;"
        "background-color:#fca72b;"
        "color:#010101;"
        "font-family:Segoe UI;"
       // "font-weight: bold;"
        "}"

        "QPushButton:hover{"
        "font-size:17px;"
        "border-radius:10px;"
        "border: 5px solid #ffcc87;"
        "border-color:#ffcc87;"
        "}"

        ;
}


QString scrollArea_Style()
{
    return
        "background: transparent;"
        "border: none;"
        "padding: 0;"
        "margin: 0;";
}

