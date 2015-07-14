#ifndef FORMAT_H
#define FORMAT_H

#include <QObject>

class FormatData {

private:
  QString type;
  unsigned long height;
  double duration;
  unsigned long width;

public:
    void setType(QString ts);
    QString getType();

    void setHeight(unsigned long h);
    unsigned long getHeight();

    void setDuration(double d);
    double getDuration();

    void setWidth(unsigned long w);
    unsigned long getWidth();

};

#endif // FORMAT_H
