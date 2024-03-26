#include <iostream>
#include "FixedWindowRollingPolicy.h"
#include "log4cxx/rolling/filerenameaction.h"
#include <log4cxx/file.h>
#include <sstream>
#include <string>

using namespace bvmf::risk::core;

FixedWindowRollingPolicy::FixedWindowRollingPolicy()
{
    maxFiles = 10;
}

FixedWindowRollingPolicy::~FixedWindowRollingPolicy()
{
}

void FixedWindowRollingPolicy::activeOptions( log4cxx::helpers::Pool& p )
{
    std::cout << "*****************PASSOUUU AQUIIII *****************" << std::endl;

    if( maxFiles < 5 )
    {
        std::stringstream ss;
        ss << "MaxFiles (" << maxFiles << ") cannot be smaller than 5.";
        std::cout << "FixedWindowRollingPolicy::activeOptions() - ERRO: " << ss.str();
        //warn( ss.str() );
        //warn("Setting maxFiles to 5.");
        maxFiles = 5;
    }
}

log4cxx::rolling::RolloverDescriptionPtr FixedWindowRollingPolicy::initialize( const std::string file, const bool append )
{
    log4cxx::rolling::ActionPtr synchronous;
    log4cxx::rolling::ActionPtr asynchronous;
    log4cxx::rolling::RolloverDescriptionPtr rd; // (file, append, synchronous, asynchronous);
    rd->activeFileName = file;
    rd->append = append;
    return rd;
}

log4cxx::rolling::RolloverDescriptionPtr FixedWindowRollingPolicy::rollover( log4cxx::LogString currentFileName )
{
    log4cxx::rolling::RolloverDescriptionPtr rd;
    return rd;
}

void FixedWindowRollingPolicy::excluiAntigos( std::string currentFileName )
{
}

void FixedWindowRollingPolicy::listaArquivos( std::string currentFileName )
{
    log4cxx::File currentFile( currentFileName );
}

std::string FixedWindowRollingPolicy::proximoArquivo( std::string currentFileName )
{
}
