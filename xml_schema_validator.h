#ifndef XML_SCHEMA_VALIDATOR_H
#define XML_SCHEMA_VALIDATOR_H

#include <QXmlSchema>
#include <QAbstractMessageHandler>
#include <QXmlSchemaValidator>
#include <QXmlInputSource>
#include <QFile>
#include <QMessageBox>
#include <QUrl>
#include <QDir>

class MessageHandler : public QAbstractMessageHandler
{
public:
    MessageHandler() : QAbstractMessageHandler(0) {}

    QString fullErrorMsg() const
    {
        auto msg = QString("%1 at %2:%3")
                .arg(statusMessage())
                .arg(line())
                .arg(column());;
        return msg;
    }

    QString statusMessage() const
    {
        return m_description;
    }

    int line() const
    {
        return m_sourceLocation.line();
    }

    int column() const
    {
        return m_sourceLocation.column();
    }

protected:
    virtual void handleMessage(QtMsgType type, const QString &description,
                               const QUrl &identifier, const QSourceLocation &sourceLocation)
    {
        Q_UNUSED(type);
        Q_UNUSED(identifier);

        m_description = description;
        m_sourceLocation = sourceLocation;
    }

private:
    QString m_description;
    QSourceLocation m_sourceLocation;
};

class XmlSchemaValidator
{
public:
    static bool validate(QFile& xmlFile, QString& errorMsg)
    {
        static const QString xsdPath = R"(C:\Users\Levon\Documents\pic_checker\resources.xsd)";
        QFile xsdFile(QDir::fromNativeSeparators(xsdPath));
        if (!xsdFile.open(QIODevice::ReadOnly))
        {
            errorMsg = QObject::tr("Не открылся файл");
            return false;
        }

        MessageHandler messageHandler;
        QXmlSchema schema;
        schema.setMessageHandler(&messageHandler);
        if (!schema.load(&xsdFile, QUrl::fromLocalFile(xsdFile.fileName())))
        {   // schema is invalid
            errorMsg = QObject::tr("Ошибка загрузки схемы");
            return false;
        }

        bool errorOccurred = false;
        if (!schema.isValid()) {
            errorOccurred = true;
        } else {
            QXmlSchemaValidator validator(schema);
            if (!validator.validate(&xmlFile,  QUrl::fromLocalFile(xmlFile.fileName()))) {
                errorOccurred = true;
                errorMsg = messageHandler.fullErrorMsg();
            }
        }
        return !errorOccurred;
    }
};

#endif // XML_SCHEMA_VALIDATOR_H
