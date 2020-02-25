#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QClipboard>
#include <QSettings>
#include <QDir>
#include <QCloseEvent>
#include <QThread>
#include <QMenu>
#include <QAction>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //interface
    QSettings * config = new QSettings("format.ini", QSettings::IniFormat,this);
    if( config->value("/Setting/backslash").toBool() )
    {
        ui->checkBox_backslash->setChecked(true);
    }
    if( config->value("/Settting/autoPop").toBool())
    {
        ui->checkBox_auto_pop->setChecked(true);
    }

    //SystemTrayIcon
    system_tray_ = new QSystemTrayIcon(this);
    system_tray_->setIcon(QIcon(":/icon/convert.png"));
    system_tray_->setToolTip("路径转换工具");
    system_tray_->show();

    QMenu * menu = new QMenu(this);
    menu->addAction(ui->action_shutdown);
    system_tray_->setContextMenu(menu);
    connect(system_tray_,&QSystemTrayIcon::activated,this,
            &MainWindow::onSystemTrayActivated);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

void MainWindow::reallyClose()
{
    QApplication::exit();
}

void MainWindow::on_btn_convert_clicked()
{
    QString original = ui->line_original->text();
    if(ui->checkBox_backslash->isChecked())
    {
        //正斜杠  /
        original = QDir::fromNativeSeparators(original);
    }
    else
    {
        original = original.replace("\\", "\\\\");
    }
    ui->lineEdit_convert->setText(original);
    if(ui->checkBox_auto_pop)
    {

        QClipboard * clipboard = QApplication::clipboard();//获取系统剪贴板指针
        clipboard->setText(original);
    }
    return;
}

void MainWindow::on_btn_copy_clicked()
{
    QString text = ui->lineEdit_convert->text();
    QClipboard * clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    clipboard->setText(text);                             //设置剪贴板内容
}

void MainWindow::on_checkBox_auto_pop_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    QSettings * config = new QSettings("format.ini", QSettings::IniFormat,this);
    if(ui->checkBox_auto_pop->isChecked())
    {
        config->setValue("/Settting/autoPop",true);
    }
    else
    {
        config->setValue("/Settting/autoPop",false);
    }
}

void MainWindow::on_checkBox_backslash_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    QSettings * config = new QSettings("format.ini", QSettings::IniFormat,this);
    if(ui->checkBox_backslash->isChecked())
    {
        config->setValue("/Setting/backslash",true);
    } else {
        config->setValue("/Setting/backslash",false);
    }
}

void MainWindow::onSystemTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::ActivationReason::Trigger:
    case QSystemTrayIcon::ActivationReason::DoubleClick:
        this->show();
        break;
    default:
        break;
    }
}

void MainWindow::on_action_shutdown_triggered()
{
    QApplication::exit();
}
