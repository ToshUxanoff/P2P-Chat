#include "issuecreator.h"
#include "ui_issuecreator.h"

issuecreator::issuecreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::issuecreator)
{
    ui->setupUi(this);
    issuecreator::setWindowTitle("Issue creator");
    Token = ReadTokenFromFile();
    if(isTokenWrited)
    {
        ui->label_2->hide();
        ui->PassEdit->hide();
    }
}
issuecreator::issuecreator(const QString &selectedText, QWidget* parent) :
    QDialog(parent),
    IssueDescription(selectedText),
    ui(new Ui::issuecreator)

{
    ui->setupUi(this);
    issuecreator::setWindowTitle("Issue creator");
    ui->DescriptionEdit->setText(IssueDescription);
    Token = ReadTokenFromFile();
    if(isTokenWrited)
    {
        ui->label_2->hide();
        ui->PassEdit->hide();
    }
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
QString issuecreator::ParseToken(QString Data)
{
     QJsonDocument document = QJsonDocument::fromJson(Data.toUtf8());
     QJsonObject root = document.object();
     QString token (root.value("token").toString());
     return token;
}
QString issuecreator::GetGithubToken(const QString &Login, const QString &Pass)
{

    QString Request = "curl -u" + Login + ':'+ Pass +" -d '{\"scopes\": [\"repo\"], \"note\": \"CoChat\" }' https://api.github.com/authorizations";
    QProcess* process = new QProcess(this);
    process->start("sh");
    process->write(Request.toUtf8());
    process->closeWriteChannel();
    process->waitForFinished();
    QString Answer = process->readAllStandardOutput();
    return ParseToken(Answer);
}
void issuecreator::WriteTokenToFile(const std::string& token)
{
    QFile configFile("config.txt");
    if(configFile.open(QIODevice::WriteOnly) && isTokenWrited == false)
    {
        configFile.write(token.c_str(), token.length());
        isTokenWrited = true;
        configFile.close();
    }
}
QString issuecreator::ReadTokenFromFile()
{
    QFile configFile("config.txt");
    QString Token;
    if(configFile.open(QIODevice::ReadOnly))
    {
        Token = configFile.readAll();
        if(!Token.isEmpty())
        {
            isTokenWrited = true;
        }
        configFile.close();
    }
    return Token;
}
void issuecreator::on_Send_clicked()
{

    if(Token.isEmpty())
    {
        Token = GetGithubToken(ui->UsernameEdit->text(), ui->PassEdit->text());
        WriteTokenToFile(Token.toStdString());
    }
    if(IsInternetConnected())
    {
        QString title = '\"'+ui->TitleEdit->text() + '\"';
        QString description = '\"' + ui->DescriptionEdit->toPlainText() + "\" }'";
        QString url = " https://api.github.com/repos/" + ui->UsernameEdit->text() +'/' + ui->RepoNameEdit->text() + "/issues";
        QString Request;
        Request = "curl -H \"Authorization: token " + Token  +"\" -d '{\"title\":"  + title  + ", \"body\":" + description  + url;
        QProcess* proc = new QProcess(this);
        proc->start("sh");
        proc->write(Request.toUtf8());
        proc->closeWriteChannel();
        proc->waitForFinished();
        issuecreator::close();
    }
}


