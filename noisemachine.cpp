#include "noisemachine.h"
#include "ui_noisemachine.h"

noiseMachine::noiseMachine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::noiseMachine)
{
    ui->setupUi(this);
}

noiseMachine::~noiseMachine()
{
    delete ui;
}

bool isSoundFileByExtension(const QString& filePath) {
    QStringList soundExtensions = {"mp3", "wav"};
    QFileInfo fileInfo(filePath);
    return soundExtensions.contains(fileInfo.suffix().toLower());
}

void noiseMachine::on_actionAdd_file_for_morph_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sound File"), "", tr("Sound Files (*.wav);;All Files (*)"));
        if (fileName.isEmpty())
            return;
    QString fileName2 = QFileDialog::getOpenFileName(this, tr("Open Second File"), "", tr("Sound Files(*.wav);; All Files (*)"));
        if(fileName.isEmpty())
            return;
    currentFile = fileName;
    currentFile2 = fileName2;
}




void noiseMachine::on_morphButton_clicked()
{

    // It is important to covert files into SND after
    // you created or loaded them with QT




    // Converting QString file into SND file
    std::string currentFileStr = currentFile.toStdString();
    const char* currentFileSND = currentFileStr.c_str();

    std::string currentFile2Str = currentFile2.toStdString();
    const char* currentFile2SND = currentFile2Str.c_str();


    SF_INFO fileInfo;
    SNDFILE* inputFile = sf_open(currentFileSND, SFM_READ, &fileInfo);
    if (!inputFile)
    {
        qDebug() << "Error opening sound file: "<< sf_strerror(nullptr);
        return;
    }


    SF_INFO secFileInfo;
    SNDFILE* secInputFile = sf_open(currentFile2SND, SFM_READ, &secFileInfo);
    if (!secInputFile)
    {
        qDebug() << "Error opening sound file: "<< sf_strerror(nullptr);
        return;
    }


    // We need to add little delay, before seeding
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::srand(std::time(0));

    // Generate a random position to start cutting from
    sf_count_t startPosition = std::rand() % fileInfo.frames;

    // Set the position to the random start position
    sf_seek(inputFile, startPosition, SEEK_SET);
    sf_seek(secInputFile, startPosition, SEEK_SET);

    // Calculate the number of frames from the start position to the end of the file
    sf_count_t remainingFrames = fileInfo.frames - startPosition;


    // Create an output file with the same format as the input file
       SF_INFO outputFileInfo = fileInfo;
       outputFileInfo.frames = remainingFrames;

       QString outputFileName = QFileDialog::getSaveFileName(this, tr("Save Output File"), "", tr("WAV Files (*.wav)"));
       if (outputFileName.isEmpty())
       {
           sf_close(inputFile);
           sf_close(secInputFile);
           return;
       }

       // Convert outputFileName to std::string and then to const char*
       std::string outputFileNameStr = outputFileName.toStdString();
       const char* outputFileNameCStr = outputFileNameStr.c_str();

       SNDFILE* fullFile = sf_open(outputFileNameCStr, SFM_WRITE, &outputFileInfo);
       if (!fullFile)
       {
           sf_close(inputFile);
           sf_close(secInputFile);
           qDebug() << "Error creating output sound file:" << sf_strerror(nullptr);
           return;
       }
    // Read and write audio data
    std::vector<double> buffer(fileInfo.channels);
    while (sf_readf_double(inputFile, buffer.data(), 1) > 0) {
        sf_writef_double(fullFile, buffer.data(), 1);
        sf_writef_double(fullFile, buffer.data(), 1);

    }
    while (sf_readf_double(secInputFile, buffer.data(), 1) > 0){
        sf_writef_double(fullFile, buffer.data(), 1);
        sf_writef_double(fullFile, buffer.data(), 1);

    }

     // Close files
    sf_close(inputFile);
    sf_close(secInputFile);
    sf_close(fullFile);


    qDebug() << "Playing output file:" << outputFileName;

    QSound::play(outputFileName);
}

