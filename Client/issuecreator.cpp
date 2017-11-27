#include "issuecreator.h"
#include "ui_issuecreator.h"
#include <QProcess>
#include <iostream>

issuecreator::issuecreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::issuecreator)
{
    ui->setupUi(this);
    issuecreator::setWindowTitle("Issue creator");
}

issuecreator::~issuecreator()
{
    delete ui;
}

void issuecreator::on_Send_clicked()
{

    QString title = '\"'+ui->TitleEdit->text() + '\"';
    QString description = '\"' + ui->DescriptionEdit->toPlainText() + '\"';
    QString LogPass = ui->UsernameEdit->text() + ":" + ui->PassEdit->text();
    QString url = " https://api.github.com/repos/" + ui->UsernameEdit->text() +'/' + ui->RepoNameEdit->text() + "/issues";
    QString Request;
    Request = "curl -u " + LogPass + " -d '{\"title\":"  + title  + ", \"body\":" + description + " }' " + url ;
    QProcess* proc = new QProcess(this);
    proc->start("sh");
    proc->write(Request.toUtf8());
    proc->closeWriteChannel();
    proc->waitForFinished();

    issuecreator::close();

}


