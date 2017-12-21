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
    if(!checker.isOnline())
    {
        return false;
        ui->statusLabel->setText("Can't connect to the internet!");
    }   
    return true;
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
    QJsonObject recordObject;
    QJsonArray ScopesArray;
    ScopesArray.push_back("repo");
    recordObject.insert("scopes", ScopesArray);
    recordObject.insert("note", QJsonValue::fromVariant("CoChat"));
    QJsonDocument doc(recordObject);
    QString LogData = Login + ':' + Pass;
    QNetworkReply* reply;
    QNetworkRequest request=QNetworkRequest(QUrl("https://api.github.com/authorizations"));
    request.setRawHeader("Authorization", "Basic " + LogData.toUtf8().toBase64());
    request.setRawHeader("Content-Type" , "application/x-www-form-urlencoded");
    QString JSON = doc.toJson();
    QNetworkAccessManager manager;
    reply = manager.post(request, JSON.toUtf8());
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString Answer = reply->readAll();
    delete reply;
    return ParseToken(Answer);
}
void issuecreator::WriteTokenToFile(const std::string& token)
{
    QFile configFile("config.ccf");

    if(configFile.open(QIODevice::WriteOnly) && isTokenWrited == false)
    {
        configFile.write(token.c_str(), token.length());
        isTokenWrited = true;
        configFile.close();
    }
}
QString issuecreator::ReadTokenFromFile()
{
    QFile configFile("config.ccf");
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
QNetworkRequest issuecreator::DoIssueRequest()
{
    QString UrlString("https://api.github.com/repos/"+ui->UsernameEdit->text() + '/'+ ui->RepoNameEdit->text() + "/issues");
    QNetworkRequest request=QNetworkRequest(QUrl(UrlString));
    request.setRawHeader("Authorization", "token " + Token.toUtf8());
    request.setRawHeader("Content-Type" , "application/x-www-form-urlencoded");
    return request;
}
QString issuecreator::DoIssueJSON()
{
    QJsonObject recordObject;
    recordObject.insert("title", QJsonValue::fromVariant(ui->TitleEdit->text()));
    recordObject.insert("body", QJsonValue::fromVariant(ui->DescriptionEdit->toPlainText()));
    QJsonDocument doc(recordObject);
    return doc.toJson();
}
void issuecreator::on_Send_clicked()
{
    if(Token.isEmpty())
    {
        Token = GetGithubToken(ui->UsernameEdit->text(), ui->PassEdit->text());
        WriteTokenToFile(Token.toStdString());
    }
    QNetworkAccessManager manager;
    QNetworkReply* reply;
    reply = manager.post(DoIssueRequest(), DoIssueJSON().toUtf8());
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    delete reply;
    issuecreator::destroy();
    issuecreator::close();
}
