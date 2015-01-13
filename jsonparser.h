#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>

class QDir;
class QFile;
struct QJsonParseError;
class QJsonObject;
class QString;
class QStandardItemModel;
class QStandardItem;

namespace Libs {

    // store all the pairs (subobj, err)
    typedef std::pair<QJsonObject, QJsonParseError> JsonObjErrPair;

    class JSonParser : public QObject
    {
        Q_OBJECT
    public:
        explicit JSonParser(QObject *parent, QString fileName);
        ~JSonParser();

        // read a JSon file
        void JSonRead();

        // return the model to the external world
        QStandardItemModel* getModel() const {

            return m_Model;
        }

    signals:
        void NotifyStatusMessage(QString message);

    public slots:
    private:
        QString m_fileName;
        QString m_configName;
        int m_numberOfSystems;
        int m_numberOfRooms;
        QStandardItemModel *m_Model;

        QString JSonReadFile();
        QString JSonReadFromRes();
        void SendErrorMessage(const QString& msg);
        JsonObjErrPair GetJsonObject(const QString &rawJson);
        void ShowJsonParseError(QJsonParseError jsonError);
        void SetupSystems(QJsonObject json_obj, QStandardItem *cfgItem);
        void SetupRooms(QJsonObject json_obj, QStandardItem *sysItem);
        void SetupATUs(QJsonObject json_obj);
    };
}


#endif // JSONPARSER_H
