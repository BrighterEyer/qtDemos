#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    audioRecorder = new QAudioRecorder;
    QStringList inputs = audioRecorder->audioInputs();
    ui->comboBox->addItems(inputs);
    /* 显示录制时间*/
    connect(audioRecorder,&QAudioRecorder::durationChanged,this,&MainWindow::updateProgress);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 开始按钮
void MainWindow::on_pushButton_clicked()
{
    audioRecorder->setAudioInput(ui->comboBox->currentText());
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(ui->lineEdit->text()));
    audioRecorder->record();
}
// 停止按钮
void MainWindow::on_pushButton_2_clicked()
{
    audioRecorder->stop();
}
// 选择按钮
void MainWindow::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getSaveFileName();
    ui->lineEdit->setText(filename);
}


//显示时间槽函数实现
void MainWindow::updateProgress(qint64 duration)
{
    if(audioRecorder->error() != QMediaRecorder::NoError || duration < 1000)
        return;
    setWindowTitle(tr("Recorded %1 sec").arg(duration / 1000));
}

