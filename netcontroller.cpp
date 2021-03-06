#include "netcontroller.h"
#include <QDir>
#include <QStandardPaths>
#include <QNetworkCookie>
#include <QSettings>
#include <QDebug>

netController::netController(QObject *parent) : QObject(parent)
{
	thumbManager = new QNetworkAccessManager(this);
	fileManager = new QNetworkAccessManager(this);
	jsonManager = new QNetworkAccessManager(this);
	captchaManager = new QNetworkAccessManager(this);

	cookies = new QNetworkCookieJar(this);
	//thumbManager->setCookieJar(cookies);
	//fileManager->setCookieJar(cookies);
	jsonManager->setCookieJar(cookies);

	diskCache = new QNetworkDiskCache(this);
	QDir().mkpath("cache");
	diskCache->setCacheDirectory("cache");
	//diskCache->setMaximumCacheSize(1073741824); //1GB cache
	jsonManager->setCache(diskCache);

	QDir().mkpath(QDir::homePath()+"/.config/qtchan");
	QString defaultCookies = QDir::homePath() + "/.config/qtchan/cookies";
	QSettings settings(QSettings::IniFormat,QSettings::UserScope,"qtchan","qtchan");
	QString cookiesFile = settings.value("cookiesFile",defaultCookies).toString();
	loadCookies(cookiesFile);

	if(settings.value("proxy/enable",false).toBool()==true){
		qDebug() << "PROXY HOST" << settings.value("proxy/host","127.0.0.1").toString();
		proxy.setType(QNetworkProxy::ProxyType(settings.value("proxy/type",1).toInt())); //QNetworkProxy::Socks5Proxy
		proxy.setHostName(settings.value("proxy/host","127.0.0.1").toString());
		proxy.setPort(settings.value("proxy/port",8080).toInt());
		if(!settings.value("proxy/user","").toString().isEmpty())
			proxy.setUser(settings.value("proxy/user","").toString());
		if(!settings.value("proxy/pass","").toString().isEmpty())
			proxy.setUser(settings.value("proxy/pass","").toString());
		captchaManager->setProxy(proxy);
	}
}

//cookies include 4chan pass
void netController::loadCookies(QString passFile){
	QFile file;
	file.setFileName(passFile);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
		QTextStream in(&file);
		QString line;
		QStringList info;
		while(!in.atEnd()){
			line = in.readLine();
			if(line.startsWith("#") || !line.contains(":")) continue;
			info = line.split(":");
			qDebug() << "adding cookie: " << info.at(0);
			QNetworkCookie temp(info.at(0).toStdString().c_str(),
								info.at(1).toStdString().c_str());
			temp.setDomain(".4chan.org");
			temp.setSecure(1);
			temp.setPath("/");
			//thumbManager->cookieJar()->insertCookie(temp);
			//fileManager->cookieJar()->insertCookie(temp);
			jsonManager->cookieJar()->insertCookie(temp);
		}
	}
}

void netController::removeCookies(){
	delete jsonManager->cookieJar();
	jsonManager->setCookieJar(new QNetworkCookieJar());
}

netController nc;

//std::vector<BoardTab*> bts;
//std::vector<Tab> tabs;
//std::vector<QWidget*> tabs;
