/* OneEuro_Plugin - for licensing and copyright see license.txt */

#include <IPluginBase.h>

#pragma once

/**
* @brief OneEuro Plugin Namespace
*/
namespace OneEuroPlugin
{
    /**
    * @brief plugin OneEuro concrete interface
    */
    struct IPluginOneEuro
    {
        /**
        * @brief Get Plugin base interface
        */
        virtual PluginManager::IPluginBase* GetBase() = 0;

        // TODO: Add your concrete interface declaration here
    };
};