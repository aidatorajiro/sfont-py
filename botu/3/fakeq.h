#ifndef FAKEQ_H
#define FAKEQ_H

using namespace std;
#include <iostream>
#include <vector>
#include <string>

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef long long int qint64;

namespace QIODevice {
    enum OpenMode{
        ReadOnly
    };
}

namespace QSysInfo {
  enum Endian {
    BigEndian,
    LittleEndian
  };
  Endian ByteOrder = LittleEndian;
}

template <typename T> class QList {
public:
    QList();
    ~QList();
    void append(const T &t);
    T& back();
    T takeLast();
    int size();
private:
    vector<T> vec;
};

int qMin(int, int);

class QString {
public:
    QString(const char *);
    ~QString();
    QString arg(QString);
    QList<QString> split(char);
    bool contains(const char *);
private:
    string str;
};

class QByteArrayData {
public:
    QByteArrayData();
    QByteArrayData(const char *, qint64);
    ~QByteArrayData();
private:
    string str;
};

class QByteArray {
public:
    QByteArray();
    QByteArray(const char *, qint64);
    ~QByteArray();
    QByteArrayData data;
};

typedef QList<QString> QStringList;

class QFile {
public:
    QFile();
    QFile(const QString &name);
    ~QFile();
    bool seek(qint64);
    qint64 read(char *, qint64);
    qint64 write(const char *, qint64);
    qint64 pos();
    QString fileName();
    bool open(QIODevice::OpenMode flags);
    bool close();
private:
    QFile(QFile&);
    void operator= (QFile&);
    
    ifstream ifs;
    ofstream ofs;
};

char * qPrintable (QString);

#endif

