#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

    // QWidget interface
protected:

    virtual void closeEvent(QCloseEvent *event) override;

    void reallyClose();

private slots:
    void on_btn_convert_clicked();

    void on_btn_copy_clicked();

    void on_checkBox_auto_pop_stateChanged(int arg1);

    void on_checkBox_backslash_stateChanged(int arg1);

    void onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason);

    void on_action_shutdown_triggered();

private:
    Ui::MainWindow *ui;
    bool is_backslash_;  //是否正斜杠
    bool is_auto_pop_;   //是否自动复制
    QSystemTrayIcon * system_tray_;
};

#endif // MAINWINDOW_H
