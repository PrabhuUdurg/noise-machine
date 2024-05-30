#ifndef NOISEMACHINE_H
#define NOISEMACHINE_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QSound>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <vector>
#include <sndfile.h>
#include <chrono>
#include <thread>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>



QT_BEGIN_NAMESPACE
namespace Ui { class noiseMachine; }
QT_END_NAMESPACE

class noiseMachine : public QMainWindow
{
    Q_OBJECT

public:
    noiseMachine(QWidget *parent = nullptr);
    ~noiseMachine();

private slots:
    void on_actionAdd_file_for_morph_triggered();

    void on_morphButton_clicked();

private:
    Ui::noiseMachine *ui;
    QString currentFile;
    QString currentFile2;
};
#endif // NOISEMACHINE_H
