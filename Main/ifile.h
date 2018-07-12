#ifndef IFILE_H
#define IFILE_H

#include <QString>
#include <QMainWindow>

class IFile{
public:
    virtual ~IFile(){}
    virtual QString description() = 0;
    virtual void Initilization(QMainWindow* window) = 0;
};
#define IFILE_IID "com.geolike.ifile"
Q_DECLARE_INTERFACE(IFile, IFILE_IID)

#endif // IFILE_H
