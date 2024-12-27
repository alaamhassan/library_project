#ifndef SUBWINDOW_EDITMEMBER_H
#define SUBWINDOW_EDITMEMBER_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class subWindow_EditMember;
}

class subWindow_EditMember : public QDialog
{
    Q_OBJECT

public:
    explicit subWindow_EditMember(QWidget *parent = nullptr, int fieldID=0,int current_window=0);
    ~subWindow_EditMember();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_editMember_Button_clicked();


private:
    Ui::subWindow_EditMember *ui;
    int fieldID;
    int current_window;
    QMap<QString, QLineEdit*> lineEditMap;
};

#endif // SUBWINDOW_EDITMEMBER_H
