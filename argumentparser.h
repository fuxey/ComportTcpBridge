#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <QStringList>
#include <QVariant>
#include <QList>

class Argument {
public:
    Argument();
    Argument(QStringList cmd, QString Desc);
    QStringList parseCmds;
    int Value;
    QString Description;
    QString payload;
    bool set;
};


class ArgumentParser
{
public:
    ArgumentParser();
    void setArgs(Argument *a);

    int ParseArguments(QStringList cmdlineArgs);
    void PrintArgumentDescription();
private:
    QList<Argument *> args;
};





#endif // ARGUMENTPARSER_H
