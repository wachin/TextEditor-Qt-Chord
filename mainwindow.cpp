//#include <QtGui>

#include "mainwindow.h"
#include "finddialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QScrollBar>

MainWindow::MainWindow()
{
    textArea = new TextArea;
    //textArea->is
    windowTitle="Text Editor";
    setWindowIcon(QIcon(":/images/app.png"));
    setCentralWidget(textArea);
    documentModified=false;
    initMenus();
    initToolBars();
    setupScrollControls();
    setupTransposeButton();
    //initContext();
}
void MainWindow::initMenus()
{
/*Create Actions*/
    newFileAction=new QAction(tr("&New"), this);
    newFileAction->setToolTip("Create a new file");
    newFileAction->setStatusTip("New File");
    newFileAction->setIcon(QIcon(":/images/filenew.png"));
    newFileAction->setShortcut(QKeySequence("Ctrl+N"));
    newFileAction->showStatusText(this->statusBar());

   // newFileAction->setShortcutContext(Qt::ShortcutContext);
    openFileAction=new QAction(tr("O&pen"), this);
    openFileAction->setToolTip("Open an existing file");
    openFileAction->setStatusTip("Open File");
    openFileAction->setIcon(QIcon(":/images/fileopen.png"));
    openFileAction->setShortcut(QKeySequence("Ctrl+O"));

    saveFileAction=new QAction(tr("&Save"), this);
    saveFileAction->setToolTip("Save current file");
    saveFileAction->setStatusTip("Save File");
    saveFileAction->setIcon(QIcon(":/images/filesave.png"));

    printAction=new QAction(tr("Print"),this);
    printAction->setToolTip("Print the page");
    printAction->setStatusTip("Print File");
    printAction->setIcon(QIcon(":/images/print.png"));

    saveAsFileAction=new QAction(tr("Save &As"), this);
    openFileAction->setStatusTip("Open File");
    saveAsFileAction->setIcon(QIcon(":/images/filesaveas.png"));

    exitFileAction=new QAction(tr("E&xit"),this);
    exitFileAction->setToolTip("Exit the Application");
    exitFileAction->setStatusTip("Exit Editor");
    exitFileAction->setIcon(QIcon(":/images/fileexit.png"));

    copyEditAction=new QAction(tr("&Copy"), this);
    copyEditAction->setToolTip("Copy");
    copyEditAction->setStatusTip("Copy Text");
    copyEditAction->setIcon(QIcon(":/images/editcopy.png"));

    pasteEditAction=new QAction(tr("P&aste"), this);
    pasteEditAction->setToolTip("Paste");
    pasteEditAction->setStatusTip("Paste Text");
    pasteEditAction->setIcon(QIcon(":/images/editpaste.png"));

    fontEditAction=new QAction(tr("F&ont"), this);
    fontEditAction->setToolTip("Change Font");
    fontEditAction->setIcon(QIcon(":/images/editfont.png"));

    cutEditAction=new QAction(tr("C&ut"), this);
    cutEditAction->setToolTip("Cut");
    cutEditAction->setStatusTip("Cut Text");
    cutEditAction->setIcon(QIcon(":/images/editcut.png"));

    findEditAction=new QAction(tr("&Find"), this);
    findEditAction->setToolTip("Find text and/or replace");
    findEditAction->setStatusTip("Find text");
    findEditAction->setIcon(QIcon(":/images/editfind.png"));

    toolEditAction=new QAction(tr("Tool &Bar"),this);
    toolEditAction->setIcon(QIcon(":/images/edittool.png"));

    colorEditAction=new QAction(tr("Color"),this);
    colorEditAction->setIcon(QIcon(":/images/editcolor.png"));

    selectEditAction=new QAction(tr("Select All"),this);
    selectEditAction->setIcon(QIcon(":/images/editselect.png"));

    undoEditAction=new QAction(tr("Undo"),this);
    undoEditAction->setIcon(QIcon(":/images/editundo.png"));
    undoEditAction->setEnabled(false);

    redoEditAction=new QAction(tr("Redo"),this);
    redoEditAction->setIcon(QIcon(":/images/editredo.png"));
    redoEditAction->setEnabled(false);


    aboutHelpAction=new QAction(tr("&About"), this);
    aboutHelpAction->setToolTip("About this application");
    aboutHelpAction->setIcon(QIcon(":/images/helpabout.png"));
/*Connections*/
    connect(fontEditAction,SIGNAL(triggered()),this,SLOT(changeFont()));
    connect(exitFileAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(aboutHelpAction,SIGNAL(triggered()),this,SLOT(aboutMe()));
    connect(findEditAction,SIGNAL(triggered()),this,SLOT(findSlot()));
    connect(copyEditAction,SIGNAL(triggered()),textArea,SLOT(copy()));
    connect(cutEditAction,SIGNAL(triggered()),textArea,SLOT(cut()));
    connect(pasteEditAction,SIGNAL(triggered()),textArea,SLOT(paste()));
    connect(selectEditAction,SIGNAL(triggered()),textArea,SLOT(selectAll()));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    connect(saveFileAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    connect(newFileAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    connect(saveAsFileAction,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));
    connect(printAction,SIGNAL(triggered()),this,SLOT(printSlot()));

    connect(textArea,SIGNAL(textChanged()),this,SLOT(isModified()));
    connect(textArea,SIGNAL(undoAvailable(bool)),undoEditAction,SLOT(setEnabled(bool)));
    connect(textArea,SIGNAL(redoAvailable(bool)),redoEditAction,SLOT(setEnabled(bool)));
    connect(textArea,SIGNAL(pasteAvailable(bool)),pasteEditAction,SLOT(setEnabled(bool)));
    toolEditAction->setCheckable(true);
    toolEditAction->setChecked(true);

/*Menu Init*/
    fileMenu = menuBar()->addMenu(tr("&File"));
    //fileMenu->setStyle();
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);
    fileMenu->addAction(exitFileAction);
    fileMenu->addAction(printAction);
    /*---*/
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutEditAction);
    editMenu->addAction(copyEditAction);
    editMenu->addAction(pasteEditAction);
    editMenu->addAction(undoEditAction);
    editMenu->addAction(redoEditAction);
    editMenu->addAction(findEditAction);
    editMenu->addAction(selectEditAction);
    editMenu->addSeparator();
    editMenu->addAction(fontEditAction);
    editMenu->addAction(colorEditAction);
    editMenu->addAction(toolEditAction);
    /*---*/
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutHelpAction);

}
void MainWindow::initToolBars()
{
    //
    toolBar=addToolBar(tr("Main"));
    toolBar->addAction(newFileAction);
    toolBar->addAction(openFileAction);
    toolBar->addAction(saveFileAction);
    toolBar->addSeparator();
    toolBar->addAction(cutEditAction);
    toolBar->addAction(copyEditAction);
    toolBar->addAction(pasteEditAction);
    toolBar->addAction(findEditAction);
    toolBar->addSeparator();
    toolBar->addAction(aboutHelpAction);
    toolBar->addAction(printAction);
    toolBar->setVisible(true);
    connect(toolEditAction,SIGNAL(toggled(bool)),toolBar,SLOT(setVisible(bool)));
}

void MainWindow::setupScrollControls()
{
    playButton = new QPushButton(QIcon(":/images/play.png"), "", this);
    pauseButton = new QPushButton(QIcon(":/images/pause.png"), "", this);
    stopButton = new QPushButton(QIcon(":/images/stop.png"), "", this);
    speedSlider = new QSlider(Qt::Horizontal, this);

    playButton->setToolTip("Play");
    pauseButton->setToolTip("Pause");
    stopButton->setToolTip("Stop");
    speedSlider->setToolTip("Adjust scroll speed");

    speedSlider->setRange(5, 18);  // 5 to 18 lines per 10 seconds
    speedSlider->setValue(10);  // Default speed
    speedSlider->setMinimumWidth(200);  // Make the slider longer

    connect(playButton, &QPushButton::clicked, this, &MainWindow::startScroll);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pauseScroll);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopScroll);
    connect(speedSlider, &QSlider::valueChanged, this, &MainWindow::updateScrollSpeed);

    QWidget* scrollWidget = new QWidget(this);
    QHBoxLayout* scrollLayout = new QHBoxLayout(scrollWidget);
    scrollLayout->addWidget(playButton);
    scrollLayout->addWidget(pauseButton);
    scrollLayout->addWidget(stopButton);
    scrollLayout->addWidget(speedSlider);
    scrollLayout->addStretch();

    toolBar->addWidget(scrollWidget);

    scrollTimer = new QTimer(this);
    connect(scrollTimer, &QTimer::timeout, this, &MainWindow::scrollText);
    scrollSpeed = 10;  // Default speed (10 lines per 10 seconds)
}

void MainWindow::setupTransposeButton()
{
    transposeButton = new QPushButton("Transpose", this);
    connect(transposeButton, &QPushButton::clicked, this, &MainWindow::transposeChords);
    toolBar->addWidget(transposeButton);
}

void MainWindow::startScroll()
{
    scrollTimer->start(1000);  // Update every second
}

void MainWindow::pauseScroll()
{
    scrollTimer->stop();
}

void MainWindow::stopScroll()
{
    scrollTimer->stop();
    textArea->verticalScrollBar()->setValue(0);
}

void MainWindow::updateScrollSpeed(int value)
{
    scrollSpeed = value;
}

void MainWindow::scrollText()
{
    QScrollBar* vScrollBar = textArea->verticalScrollBar();
    int newValue = vScrollBar->value() + scrollSpeed / 10;
    if (newValue <= vScrollBar->maximum()) {
        vScrollBar->setValue(newValue);
    } else {
        stopScroll();
    }
}

void MainWindow::transposeChords()
{
    QStringList options;
    for (int i = -7; i <= 7; ++i) {
        if (i == 0) continue;
        options << QString("%1%2").arg(i > 0 ? "+" : "").arg(i);
    }

    bool ok;
    QString selection = QInputDialog::getItem(this, "Transpose Chords",
                                              "Select semitones to transpose:",
                                              options, 0, false, &ok);
    if (ok && !selection.isEmpty()) {
        int semitones = selection.toInt();
        QString text = textArea->toPlainText();
        QStringList lines = text.split("\n");
        for (int i = 0; i < lines.size(); ++i) {
            QStringList words = lines[i].split(" ");
            for (int j = 0; j < words.size(); ++j) {
                words[j] = transposeChord(words[j], semitones);
            }
            lines[i] = words.join(" ");
        }
        textArea->setPlainText(lines.join("\n"));
    }
}

QString MainWindow::transposeChord(const QString &chord, int semitones)
{
    QStringList notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    QString base = chord.left(1);
    QString remainder = chord.mid(1);
    int index = notes.indexOf(base);
    if (index != -1) {
        index = (index + semitones + 12) % 12;
        return notes[index] + remainder;
    }
    return chord;
}

void MainWindow::initContext(){
    this->addAction(cutEditAction);
    this->addAction(copyEditAction);
    this->addAction(pasteEditAction);
    this->addAction(selectEditAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}
void MainWindow::printSlot(){

    prepareDocument();

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
    printer.setPageOrientation(QPageLayout::Portrait);

    QPrintPreviewDialog preview(&printer,this,Qt::WindowCloseButtonHint|Qt::WindowMaximizeButtonHint);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    preview.showMaximized();
    preview.exec();
    delete mDoc2Print;
//    textArea->print(&printer);
//#endif
}
void MainWindow::printPreview(QPrinter *printer){
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    mDoc2Print->print(printer);
#endif
}

void MainWindow::prepareDocument(){
    mDoc2Print=new QTextDocument();
    mDocCursor=QTextCursor(mDoc2Print);

    mDocCursor.insertText(textArea->document()->toPlainText());

}

void MainWindow::isModified()
{
    if(!documentModified){
       documentModified=true;
       updateTitle();
   }
}
void MainWindow::updateTitle()
{
    if(documentModified){
    windowTitle=QString("%1 %2 %3").arg("Text Editor").arg(curFilename).arg("*");
    this->setWindowTitle(windowTitle);
}else{
    windowTitle=QString("%1 %2").arg("Text Editor").arg(curFilename);
    this->setWindowTitle(windowTitle);
}
}

void MainWindow::aboutMe(){
    QMessageBox::about(this,"About Me",
                       "A Prototype TextEditor Application For Studying QT."
                       "\nAll copyrights belong to Prasanth Ravi");
}
void MainWindow::openFileSlot(){
    QString userFile=QFileDialog::getOpenFileName(this,"Open Document"
                                 ,".","Text Files(*.txt *.rtf *.doc);;All Files(*.*)");
    bool res=fileOperate(userFile,openFile);
    if(res){
        statusBar()->showMessage("Open Successful",2000);
        curFilename=userFile;
        documentModified=false;
        }
    else{
        statusBar()->showMessage("Problem loading file !!",2000);
    }
    updateTitle();
}
void MainWindow::saveFileSlot(){
    bool res;
    if(curFilename==""){
    QString userFile=QFileDialog::getSaveFileName(this,"Save Document",".",
                                    "Text File(*.txt);;Rich Text Document(*.rtf)");
    res=fileOperate(userFile,saveFile);
    }
    else{
    res=fileOperate(curFilename,saveFile);
    }
    if(res){
        statusBar()->showMessage("Save Successful",2000);
        documentModified=false;
        }
    else{
        statusBar()->showMessage("Problem saving file !!",2000);
    }
    updateTitle();
}
void MainWindow::saveAsFileSlot(){
    bool res;
    QString userFile=QFileDialog::getSaveFileName(this,"Save Document",".",
                                    "Text File(*.txt);;Rich Text Document(*.rtf)");
    res=fileOperate(userFile,saveFile);
    if(res){
        statusBar()->showMessage("Save Successful",2000);
        documentModified=false;
        }
    else{
        statusBar()->showMessage("Problem saving file !!",2000);
    }
}

void MainWindow::newFileSlot(){
    if(documentModified){
        int res=QMessageBox::warning(this,"File Modified!!",
                             "File has been modified.\nDo you want to create new?",
                             QMessageBox::Ok|QMessageBox::Cancel);
        if(res==QMessageBox::Ok){
            textArea->clear();
            textArea->setFocus();
            documentModified=false;
            curFilename="";
        }
    }
    else{
        textArea->clear();
        textArea->setFocus();
        documentModified=false;
        curFilename="";
    }
    updateTitle();
}

bool MainWindow::fileOperate(QString &flname, int mode){
    switch(mode){
    case openFile:{

        QFile textFile(flname);
        if(textFile.open(QIODevice::ReadOnly)){
            QByteArray content=textFile.readAll();
            QString stringContent(content);
            textArea->setText(stringContent);
            textFile.close();
            return true;
        }
        break;
    }
    case saveFile:{

        QFile textFile(flname);

        if(textFile.open(QIODevice::WriteOnly)){
            QString stringContent=textArea->toPlainText();
            QByteArray content=stringContent.toUtf8();
            textFile.write(content);
            textFile.close();
            return true;
        }

    }
    };
return false;
}
void MainWindow::findSlot(){
    /*
    FindDialog *findDlg=new FindDialog(this);
    findDlg->raise();
    findDlg->show();
    findDlg->activateWindow();
    findDlg->setModal(true);
    */
    FindDialog findDlg(this);
    findDlg.exec();
}

void MainWindow::changeFont(){
    textArea->setFont(QFontDialog::getFont(0,this));
}


TextArea::TextArea(QWidget *parent): QTextEdit(parent){

}

