#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QTextEdit>
#include <QToolBar>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QFile>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QSlider>
#include <QPushButton>
#include <QTimer>
#include <QScrollBar>

class QAction;
class QMenu;
class QTextEdit;
class QFile;
class QFileDialog;
class QFontDialog;
class QStatusBar;
class QToolBar;
class QMenuBar;
class QMessageBox;
class QSlider;
class QPushButton;
class QTimer;

class TextArea : public QTextEdit {
    Q_OBJECT

public:
    TextArea(QWidget *parent = 0);

signals:

private slots:

private:
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    void initMenus();
    void initToolBars();
    void initContext();

private slots:
    void openFileSlot();
    void saveFileSlot();
    void newFileSlot();
    void saveAsFileSlot();
    void changeFont();
    void aboutMe();
    void isModified();
    void updateTitle();
    void findSlot();
    void printSlot();
    void printPreview(QPrinter *printer);
    void startScroll();
    void pauseScroll();
    void stopScroll();
    void updateScrollSpeed(int value);
    void scrollText();
    void transposeChords();

private:
    enum { saveFile, openFile };
    QAction *newFileAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *exitFileAction;
    QAction *saveAsFileAction;
    QAction *copyEditAction;
    QAction *pasteEditAction;
    QAction *fontEditAction;
    QAction *cutEditAction;
    QAction *toolEditAction;
    QAction *findEditAction;
    QAction *colorEditAction;
    QAction *selectEditAction;
    QAction *undoEditAction;
    QAction *redoEditAction;
    QAction *aboutHelpAction;
    QAction *printAction;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *toolBar;
    QToolBar *editToolBar;
    TextArea *textArea;
    bool documentModified;
    QString windowTitle;
    QString curFilename;
    QTextDocument *mDoc2Print;
    QTextCursor mDocCursor;
    void prepareDocument();
    bool fileOperate(QString &flname, int mode);

    // Nuevos componentes para el desplazamiento automático
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QSlider *speedSlider;
    QTimer *scrollTimer;
    int scrollSpeed;

    // Nuevo botón para transposición
    QPushButton *transposeButton;

    void setupScrollControls();
    void setupTransposeButton();
    QString transposeChord(const QString &chord, int semitones);
};

#endif // MAINWINDOW_H
