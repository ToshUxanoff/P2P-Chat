#include "issuecreator.h"
#include "ui_issuecreator.h"
#include <QProcess>
#include <iostream>
#include <QNetworkConfigurationManager>
issuecreator::issuecreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::issuecreator)
{
    ui->setupUi(this);
    issuecreator::setWindowTitle("Issue creator");
}
issuecreator::issuecreator(const QString &selectedText, QWidget* parent) :
    QDialog(parent),
    IssueDescription(selectedText),
    ui(new Ui::issuecreator)

{
    ui->setupUi(this);
    issuecreator::setWindowTitle("Issue creator");
    ui->DescriptionEdit->setText(IssueDescription);
}
issuecreator::~issuecreator()
{
    delete ui;
}
bool issuecreator::IsInternetConnected()
{
    QNetworkConfigurationManager checker;
    if(checker.isOnline())
    {
        return true;
    }
    else
    {
        ui->statusLabel->setText("Can't connect to the internet!");
        return false;
    }

}
void issuecreator::on_Send_clicked()
{
    if(IsInternetConnected())
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
}


