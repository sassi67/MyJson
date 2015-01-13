#include "jsonparser.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValueRef>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStandardPaths>

namespace Libs {

    static QString RES_JSON_PREFIX = QStringLiteral(":/json");

    /**
     * @brief JSonParser::JSonParser
     * @param parent
     * @param fileName
     */
    JSonParser::JSonParser(QObject *parent, QString fileName):
        QObject(parent),
        m_fileName(fileName),
        m_configName(""),
        m_numberOfSystems(0),
        m_numberOfRooms(0),
        m_Model(new QStandardItemModel(this))
    {

    }

    /**
     * @brief JSonParser::~JSonParser
     */
    JSonParser::~JSonParser()
    {

    }

    /**
     * @brief JSonParser::JSonRead
     * @description Read and parse a configuration file
     */
    void JSonParser::JSonRead()
    {
        QString json_raw = JSonReadFile();
        if (json_raw.size() == 0) return;

        JsonObjErrPair json_result = GetJsonObject(json_raw);
        QJsonParseError json_err = json_result.second;
        if (json_err.error != QJsonParseError::NoError)
        {
            ShowJsonParseError(json_err);
            return;
        }

        // clean the standard item model
        m_Model->clear();
        // read the json file
        QJsonObject json_obj = json_result.first;
        // get the configuration data
        m_configName = json_obj["configName"].toString();
        m_numberOfSystems = json_obj["numberOfSystems"].toInt();
        m_numberOfRooms = json_obj["numberOfRooms"].toInt();

        // update the item model
        QStandardItem *cfgItem = m_Model->invisibleRootItem();
        // start to navigate the json file
        SetupSystems(json_obj, cfgItem);
    }

    /**
     * @brief JSonParser::JSonReadFile
     * @return
     */
    QString JSonParser::JSonReadFile()
    {
        QString config = JSonReadFromRes();
        QDir config_dir = QDir::currentPath();
        QString path = config_dir.filePath(m_fileName);
        QFile std_file(path);

        if (!std_file.open(QFile::ReadOnly | QFile::Text))
        {
            SendErrorMessage("Could not open " + path);
            return config;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }

    /**
     * @brief JSonParser::JSonReadFromRes
     * @return
     */
    QString JSonParser::JSonReadFromRes()
    {
        QDir res_dir(RES_JSON_PREFIX);

        if (!res_dir.exists())
        {
            SendErrorMessage("Resource path missing " + res_dir.canonicalPath());
            return "";
        }

        QString path = res_dir.filePath(m_fileName);
        QFile res_file(path);

        if (!res_file.open(QFile::ReadOnly| QFile::Text))
        {
            SendErrorMessage("Could not open resource " + path);
            return "";
        }
        QString settings = res_file.readAll();
        return settings;

    }

    /**
     * @brief JSonParser::SendErrorMessage
     * @param msg
     */
    void JSonParser::SendErrorMessage(const QString &msg)
    {
        emit NotifyStatusMessage(msg);
    }

    /**
     * @brief JSonParser::GetJsonObject
     * @param rawJson
     * @return
     */
    JsonObjErrPair JSonParser::GetJsonObject(const QString &rawJson)
    {
        QJsonParseError json_parse_error;
        QJsonDocument json_doc = QJsonDocument::fromJson(rawJson.toUtf8(),
                                                         &json_parse_error);
        QJsonObject json_obj = json_doc.object();
        return std::make_pair(json_obj, json_parse_error);
    }

    /**
     * @brief JSonParser::ShowJsonParseError
     * @param jsonError
     */
    void JSonParser::ShowJsonParseError(QJsonParseError jsonError)
    {
        QString msg = tr("Error parsing Json settings file.\n");
        msg.append(jsonError.errorString());
        qDebug() << msg;
    }

    /**
     * @brief JSonParser::SetupSystems
     * @param json_obj
     */
    void JSonParser::SetupSystems(QJsonObject json_obj, QStandardItem *cfgItem)
    {
        // get all the systems
        QJsonArray sys_array = json_obj["systems"].toArray();

        for (QJsonValueRef sys : sys_array)
        {
            // get the single system
            QJsonObject json_obj = sys.toObject();
            // update the model
            QStandardItem *item = new QStandardItem(QString("System: %0 - Type: %1").
                                                    arg(json_obj["systemName"].toString()).
                                                    arg(json_obj["type"].toString()));
            cfgItem->appendRow(item);

            // navigate the rooms of this system
            SetupRooms(json_obj, item);
        }
    }
    /**
     * @brief JSonParser::SetupRooms
     * @param json_obj
     */
    void JSonParser::SetupRooms(QJsonObject json_obj, QStandardItem *sysItem)
    {
        // get all the rooms
        QJsonArray rooms_array = json_obj["rooms"].toArray();

        for (QJsonValueRef room : rooms_array)
        {
            // get the single system
            QJsonObject json_obj = room.toObject();
            // update the model
            QStandardItem *item = new QStandardItem(QString("Room: %0 - Type: %1").
                                                    arg(json_obj["roomName"].toString()).
                                                    arg(json_obj["type"].toString()));
            sysItem->appendRow(item);
        }
    }
}
