#include "ConfigFactory.h"

IAhoAutomataConfig&AhoConfigFactory::Config()
{
    static EnglishAhoAutomataConfig conf;
    return conf;
}
