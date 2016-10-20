#ifndef DLTASK_H
#define DLTASK_H

#include <QObject>

class DLTask : public QObject
{
    Q_OBJECT
public:
    explicit DLTask(QObject *parent = 0);
    ~DLTask();

signals:

public slots:

private:

};

#endif // DLTASK_H
