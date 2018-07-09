#ifndef SHAPEPLUGININTERFACE_H
#define SHAPEPLUGININTERFACE_H

#include <QObject>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QPainterPath>

class ShapePluginInterface{
public:
    virtual ~ShapePluginInterface(){}
    virtual QString description() = 0;
    virtual void initialization(QMainWindow* window) = 0;
};
#define SHAPEPLUGININTERFACE_IID "com.geolike.shapeplugininterface"
Q_DECLARE_INTERFACE(ShapePluginInterface, SHAPEPLUGININTERFACE_IID)

#endif // SHAPEPLUGININTERFACE_H
