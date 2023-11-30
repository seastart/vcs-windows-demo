#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>

namespace Ui {
class FormLogin;
}

class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = nullptr);
    ~FormLogin();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void OnRoomEnter();
    void on_btnTest_clicked();

    void on_pushButton_3_clicked();

    void on_rbtn1_clicked();

    void on_rbtn2_clicked();

    void on_rbtn3_clicked();

    void on_btnRegiester_clicked();

    void on_btnDirShare_clicked();

    void on_btnStopDirShare_clicked();

    void OnDirectShareEvent(int,QString);
signals:
    void RoomEnter();
private:
    Ui::FormLogin *ui;
    bool showHide;
    bool isLogin;
    void SaveData();
    void LoadData();

    int widlen = 0;
};

#endif // FORMLOGIN_H
