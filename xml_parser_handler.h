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
        if (localName == "subject")
        {
            subjectId++;
            subjectName = atts.value("name");
        }
        else if (localName == "photo")
        {
            prepId++;
        }

        return QXmlDefaultHandler::startElement(namespaceURI, localName, qName, atts);
    }

    virtual bool characters(const QString& ch) override
    {
        const auto& rawString = ch.trimmed();
        if (!rawString.isEmpty())
        {
            const auto& photoPath = xmlDir.absoluteFilePath(ch);
            etalonPreps[subjectId].push_back({prepId, subjectId, subjectName, photoPath});
        }
        return QXmlDefaultHandler::characters(ch);
    }

private:
    PrepsType& etalonPreps;
    QDir xmlDir;

    QString subjectName;
    int prepId = 0;
    int subjectId = 0;
};

#endif // XML_PARSER_HANDLER_H
