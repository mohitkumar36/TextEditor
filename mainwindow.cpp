#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui -> textEdit);
    this->setWindowTitle("");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionBold_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat formatBold, formatNormal;
    formatBold.setFontWeight(QFont::Bold);
    formatNormal.setFontWeight(QFont::Normal);


    if(cursor.hasSelection()){
        cursor.setPosition(cursor.selectionEnd());
        if(!cursor.charFormat().font().bold()){
            ui->textEdit->mergeCurrentCharFormat(formatBold);

        }
        else if (cursor.charFormat().font().bold()){
            ui->textEdit->mergeCurrentCharFormat(formatNormal);

        }
    }
}


void MainWindow::on_actionItalic_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat formatItalic, formatNormal;
    formatItalic.setFontItalic(true);
    formatNormal.setFontItalic(false);

    if(cursor.hasSelection()){
        cursor.setPosition(cursor.selectionEnd());
        if(!cursor.charFormat().font().italic()){
            ui->textEdit->mergeCurrentCharFormat(formatItalic);

        }
        else if (cursor.charFormat().font().italic()){
            ui->textEdit->mergeCurrentCharFormat(formatNormal);

        }
    }
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionSuperscript_triggered()
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);

    if(cursor.hasSelection()){
        cursor.setPosition(cursor.selectionEnd());
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->autoFormatting();
        cursor.insertText("");

    }
}


void MainWindow::on_actionSubscript_triggered()
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();
    format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    if(cursor.hasSelection()){
        cursor.setPosition(cursor.selectionEnd());
        ui->textEdit->mergeCurrentCharFormat(format);
        ui->textEdit->autoFormatting();
        cursor.insertText("");

    }
}


void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
    this->setWindowTitle("New File");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open the file");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text)){

            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();
            this->setWindowTitle(mFilename);
            ui->textEdit->setPlainText(text);
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    QFile sFile(mFilename);
    if(mFilename.isEmpty()){
        on_actionSave_AS_triggered();
    }
    if(sFile.open(QFile::WriteOnly | QFile::Text)){
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}


void MainWindow::on_actionSave_AS_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open the file");

    if(!file.isEmpty())
    {
        mFilename = file;
        this->setWindowTitle(mFilename);
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionAbout_triggered()
{
    Dialog resume;
    resume.setModal(true);
    resume.exec();
}

