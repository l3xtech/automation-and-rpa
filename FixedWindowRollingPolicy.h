#ifndef FIXEDWINDOWROLLINGPOLICY_H_
#define FIXEDWINDOWROLLINGPOLICY_H_

#include <log4cxx/rolling/rollingpolicybase.h>
#include <log4cxx/rolling/rolloverdescription.h>
#include <log4cxx/helpers/pool.h>

namespace bvmf {
namespace risk {
namespace core {
class FixedWindowRollingPolicy : public log4cxx::rollingPolicyBase
{
private:
    int maxFiles;

public:
    FixedWindowRollingPolicy();
    virtual ~FixedWindowRollingPolicy();

    void activeOptions( log4cxx::helpers::Pool& p );
    log4cxx::rolling::RolloverDescriptionPtr initialize( const std::string file, const bool append );
    log4cxx::rolling::RolloverDescriptionPtr rollover( log4cxx::LogString currentFileName );
    void excluiAntigos( std::string currentFileName );
    void listaArquivos( std::string currentFileName );
    std::string proximoArquivo( std::string currentFileName );

    int getMaxFiles(){
        return maxFiles;
    }

    void setMaxfiles( int maxFiles ){
        this->maxFiles = maxFiles;
    }

};
}}}

#endif /* FIXEDWINDOWROLLINGPOLICY_H_ */
