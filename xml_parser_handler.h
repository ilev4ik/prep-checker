#ifndef XML_PARSER_HANDLER_H
#define XML_PARSER_HANDLER_H

#include <map>
#include <vector>

#include <QXmlDefaultHandler>
#include <QDebug>

#include <QDir>
#include "prep.h"


// todo: invalidate state for each virtual parse call
class XmlParserHandler : public QXmlDefaultHandler
{
    typedef std::vector<Prep> SubjectType;
    typedef std::map<int, SubjectType> PrepsType;
public:
    XmlParserHandler(PrepsType& preps) : etalonPreps(preps) {}

    QString titleName() const
    {
        auto title = QString("%1.%2 by %3 (%4)")
                .arg(subject).arg(theme)
                .arg(author).arg(email);
        return title;
    }

    void setFileInfo(const QString& xmlPath)
    {
        xmlDir = QFileInfo(xmlPath).absoluteDir();
    }

    int loadedPreps() const
    {
        return prepId;
    }

protected:
    virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) override
    {
        if (localName == "test")
        {
            subject = atts.value("subject");
            theme = atts.value("theme");
        }
        if (inSources && localName == "object")
        {
            objectId++;
            objectName = atts.value("name");
        }
        else if (inSources && localName == "photo")
        {
            prepId++;
        }
        else if (localName == "author")
        {
            inSources = false;
            inAuthor = true;
        }
        else if (localName == "sources")
        {
            inAuthor = false;
            inSources = true;
        }

        currentTag = localName;
        return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
    }

    virtual bool characters(const QString& ch) override
    {
        const auto& rawString = ch.trimmed();
        if (!rawString.isEmpty())
        {
            if (inSources)
            {
                const auto& photoPath = xmlDir.absoluteFilePath(ch);
                etalonPreps[objectId].push_back({prepId, objectId, objectName, photoPath});
            }
            else if (inAuthor && currentTag == "name")
            {
                author = rawString;
            }
            else if (inAuthor && currentTag == "email")
            {
                email = rawString;
            }
            else if (currentTag == "description")
            {
                decription = rawString;
            }
        }
        return QXmlDefaultHandler::characters(ch);
    }

private:
    PrepsType& etalonPreps;
    QDir xmlDir;

    QString currentTag;
    QString objectName;
    int prepId = 0;
    int objectId = 0;

    bool inSources = false;
    bool inAuthor = false;

    QString author;
    QString email;
    QString subject;
    QString theme;
    QString decription;
};

#endif // XML_PARSER_HANDLER_H
