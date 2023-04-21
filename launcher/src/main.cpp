#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("BladeBattles Launcher");

    QPushButton *playButton = new QPushButton("Play");

    QComboBox *resolutionComboBox = new QComboBox;
    resolutionComboBox->addItem("640x480");
    resolutionComboBox->addItem("800x600");
    resolutionComboBox->addItem("1024x768");
    resolutionComboBox->addItem("1280x720");
    resolutionComboBox->addItem("1366x768");
    resolutionComboBox->addItem("1920x1080");

    QLabel *resolutionLabel = new QLabel("Selected resolution: ");

    QCheckBox *fullscreenCheckBox = new QCheckBox("Fullscreen mode");

    QCheckBox *vsyncCheckBox = new QCheckBox("VSync");

    QLabel *audioLabel = new QLabel("Volume audio: ");
    QSlider *audioSlider = new QSlider(Qt::Horizontal);
    audioSlider->setMinimum(0);
    audioSlider->setMaximum(100);

    QFile configFile("config.txt");
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&configFile);
        QString line = in.readLine();
        while (!line.isNull())
        {
            QStringList parts = line.split(":");
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            if (key == "resolution")
            {
                resolutionLabel->setText("Selected resolution: " + value);
                resolutionComboBox->setCurrentText(value);
            }
            else if (key == "fullscreen")
            {
                fullscreenCheckBox->setChecked(value == "true");
            }
            else if (key == "vsync")
            {
                vsyncCheckBox->setChecked(value == "true");
            }
            else if (key == "audio")
            {
                audioSlider->setValue(value.toInt());
            }
            line = in.readLine();
        }
        configFile.close();
    }

    QObject::connect(playButton, &QPushButton::clicked, [&]()
                     {
                     QString selectedResolution = resolutionComboBox->currentText();
                     QString fullscreen = fullscreenCheckBox->isChecked() ? "true" : "false";
                     QString vsync = vsyncCheckBox->isChecked() ? "true" : "false";
                     int audio = audioSlider->value();

                     QFile configFile("config.txt");
                     if (configFile.open(QIODevice::WriteOnly | QIODevice::Text))
                     {
                         QTextStream out(&configFile);
                         out << "resolution: " << selectedResolution << "\n";
                         out << "fullscreen: " << fullscreen << "\n";
                         out << "vsync: " << vsync << "\n";
                         out << "audio: " << audio << "\n";
                         configFile.close();
                     }

                     QString executablePath = "./_game";

                     QProcess *process = new QProcess;
                     process->start(executablePath); 
                     QApplication::quit(); });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(playButton);
    layout->addWidget(resolutionComboBox);
    layout->addWidget(resolutionLabel);
    layout->addWidget(fullscreenCheckBox);
    layout->addWidget(vsyncCheckBox);
    layout->addWidget(audioLabel);
    layout->addWidget(audioSlider);

    window->setLayout(layout);

    window->show();

    return app.exec();
}
