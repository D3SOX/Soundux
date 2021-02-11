#pragma once
#include <QQmlApplicationEngine>
#include <vector>

#include "../config/config.h"
#include "../bindings/bindings.h"

#ifdef _WIN32
#include "../hotkeys/windows.h"
#include "../playback/windows.h"
#else
#ifdef __linux__
#include "../hotkeys/linux.h"
#include "../playback/linux.h"
// #else
// #include "../hotkeys/mac.h"
#endif
#endif

class Core : public QObject
{
    Q_OBJECT
  public:
    explicit Core(QObject * = nullptr);

  public slots:
    void setEngine(QQmlApplicationEngine *);
    void loadSettings();
    void refresh();

    void onSizeChanged(int, int);

    void removeTab();
    QTab getCurrentTab();
    std::vector<QTab> getTabs();

    void addFolderTab(const QUrl &);
    void updateFolderSounds(const QTab &);
    void updateFolderSounds(Soundux::Config::Tab &);

    void changeLocalVolume(int);
    void changeRemoteVolume(int);

    std::vector<QSound> getAllSounds();
    std::vector<QSound> getSounds();

    void playSound(const Soundux::Config::Sound &);
    void playSoundByPath(const QString &);
    void playSound(int);
    void stopPlayback();

    void currentTabChanged(int);

    void setStopHotkey();
    void setHotkey(const QString &);
    void hotkeyDialogFocusChanged(int);

    int getDarkMode();
    void onDarkModeChanged(int);

    int getAllowOverlapping();
    void onAllowOverlappingChanged(int);

    void onTabHotkeyOnlyChanged(int);
    int getTabHotkeysOnly();

    int isWindows();
    QList<QString> getStopHotKey();
    QList<QString> getCurrentHotKey(const QString &);

    // Can't use preprocessor here because qt doesnt like that.

    /* Linux */
    void setLinuxSink(const ma_device_info &);
    void currentOutputApplicationChanged(int);
    std::vector<QPulseAudioRecordingStream> getOutputApplications();
    /* */

    /* Windows */
    QList<QString> getPlaybackDevices();
    /* */

  signals:
    void keyPress(QList<QString>);
    void keyCleared();

    void foldersChanged();
    void setSize(int, int);
    void updateCurrentTab();
    void invalidApplication();
    void setLocalVolume(float);
    void setRemoteVolume(float);
    void setOutputApplication(int);
    void playbackChanged(int);

  private:
    QQmlApplicationEngine *engine{};
    ma_device_info sink;
};

inline Core gCore;