#include "argumentparser.h"
#include <QDebug>




ArgumentParser::ArgumentParser()
{

}

void ArgumentParser::setArgs(Argument *a)
{
    args.append(a);
}

int ArgumentParser::ParseArguments(QStringList cmdlineArgs){

    for(int i = 0; i < cmdlineArgs.size();i++){
        QString cmd = cmdlineArgs.at(i);
        qDebug() << cmd;
        for(int a =0; a<args.size();a++){
            Argument *arg_ = args.at(a);
            for(int c=0; c < arg_->parseCmds.size(); c++){
                QString cmdarg = arg_->parseCmds.at(c);
                if(cmdarg == cmd){
                    if(i+1 >=cmdlineArgs.size()){
                        qDebug() << "no valid Argument found!";
                        return -1;
                    } else {
                        int val = cmdlineArgs.at(i+1).toInt();
                        qDebug() << "copy Argument in Value" << "found val" << val;
                        args[a]->Value = val;
                        //args[a]->parseCmds =
                        QString item = cmdlineArgs.at(i+1);
                        args[a]->payload = item;
                        args[a]->set = true;
                        //args[a].Value = cmdlineArgs.at(i+1).toInt();

                        continue;
                    }

                }
            }
        }
    }
    return 0;
}


void ArgumentParser::PrintArgumentDescription(){
    for(int i = 0; i < args.size();i++){
        qDebug() << args.at(i)->Description;
    }
}


Argument::Argument(){

}


Argument::Argument(QStringList cmd, QString Desc)
{
    this->parseCmds =cmd;
    this->Description = Desc;
    this->set = false;
}
