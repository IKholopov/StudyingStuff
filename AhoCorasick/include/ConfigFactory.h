#ifndef CONFIG_FACTORY_H
#define CONFIG_FACTORY_H

#include "EnglishAhoAutomataConfig.h"

class AhoConfigFactory{
    public:
        static IAhoAutomataConfig& Config();
};

#endif
