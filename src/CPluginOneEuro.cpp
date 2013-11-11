/* OneEuro_Plugin - for licensing and copyright see license.txt */

#include <StdAfx.h>
#include <CPluginOneEuro.h>
#include <IPluginOneEuro.h>

namespace OneEuroPlugin
{
    CPluginOneEuro* gPlugin = NULL;

    CPluginOneEuro::CPluginOneEuro()
    {
        gPlugin = this;
    }

    CPluginOneEuro::~CPluginOneEuro()
    {
        Release( true );

        gPlugin = NULL;
    }

    bool CPluginOneEuro::Release( bool bForce )
    {
        bool bRet = true;
        bool bWasInitialized = m_bIsFullyInitialized; // Will be reset by base class so backup

        if ( !m_bCanUnload )
        {
            // Note: Type Unregistration will be automatically done by the Base class (Through RegisterTypes)
            // Should be called while Game is still active otherwise there might be leaks/problems
            bRet = CPluginBase::Release( bForce );

            if ( bRet )
            {
                if ( bWasInitialized )
                {
                    // TODO: Cleanup stuff that can only be cleaned up if the plugin was initialized
                }

                // Cleanup like this always (since the class is static its cleaned up when the dll is unloaded)
                gPluginManager->UnloadPlugin( GetName() );

                // Allow Plugin Manager garbage collector to unload this plugin
                AllowDllUnload();
            }
        }

        return bRet;
    };

    bool CPluginOneEuro::Init( SSystemGlobalEnvironment& env, SSystemInitParams& startupParams, IPluginBase* pPluginManager, const char* sPluginDirectory )
    {
        gPluginManager = ( PluginManager::IPluginManager* )pPluginManager->GetConcreteInterface( NULL );
        CPluginBase::Init( env, startupParams, pPluginManager, sPluginDirectory );

        return true;
    }

    bool CPluginOneEuro::RegisterTypes( int nFactoryType, bool bUnregister )
    {
        // Note: Autoregister Flownodes will be automatically registered by the Base class
        bool bRet = CPluginBase::RegisterTypes( nFactoryType, bUnregister );

        using namespace PluginManager;
        eFactoryType enFactoryType = eFactoryType( nFactoryType );

        if ( bRet )
        {
            if ( gEnv && gEnv->pSystem && !gEnv->pSystem->IsQuitting() )
            {
                // UIEvents
                if ( gEnv->pConsole && ( enFactoryType == FT_All || enFactoryType == FT_UIEvent ) )
                {
                    if ( !bUnregister )
                    {


                    }

                    else
                    {



                    }
                }

                // CVars
                if ( gEnv->pConsole && ( enFactoryType == FT_All || enFactoryType == FT_CVar ) )
                {
                    if ( !bUnregister )
                    {
                        gEnv->pConsole->RegisterFloat( "CryVR_filters_enable", 1, 0, "Use Online Lobby Service (rather than LAN)" );
                        gEnv->pConsole->RegisterFloat( "CryVR_filters_euro_enable", 1, 0, "Use Online Lobby Service (rather than LAN)" );
                        gEnv->pConsole->RegisterInt( "CryVR_filters_euro_frequence", 120, 0, "Use Online Lobby Service (rather than LAN)" );
                        gEnv->pConsole->RegisterFloat( "CryVR_filters_euro_beta", 0.007, 0, "Use Online Lobby Service (rather than LAN)" );
                        gEnv->pConsole->RegisterFloat( "CryVR_filters_euro_mincutoff", 1, 0, "Use Online Lobby Service (rather than LAN)" );

                    }

                    else
                    {
                        gEnv->pConsole->UnregisterVariable( "CryVR_filters_enable", true );
                        gEnv->pConsole->UnregisterVariable( "CryVR_filters_euro_enable", true );
                        gEnv->pConsole->UnregisterVariable( "CryVR_filters_euro_frequence", true );
                        gEnv->pConsole->UnregisterVariable( "CryVR_filters_euro_beta", true );
                        gEnv->pConsole->UnregisterVariable( "CryVR_filters_euro_mincutoff", true );

                    }
                }

                // CVars Commands
                if ( gEnv->pConsole && ( enFactoryType == FT_All || enFactoryType == FT_CVarCommand ) )
                {
                    if ( !bUnregister )
                    {
                        // TODO: Register CVar Commands here if you have some
                        // ...
                    }

                    else
                    {
                        // TODO: Unregister CVar Commands here if you have some
                        // ...
                    }
                }

                // Game Objects
                if ( gEnv->pGame && gEnv->pGame->GetIGameFramework() && ( enFactoryType == FT_All || enFactoryType == FT_GameObjectExtension ) )
                {
                    if ( !bUnregister )
                    {
                        // TODO: Register Game Object Extensions here if you have some
                        // ...
                    }
                }
            }
        }

        return bRet;
    }

    const char* CPluginOneEuro::ListCVars() const
    {
        return "CryVR_filters_euro_frequence, CryVR_filters_euro_beta, CryVR_filters_euro_mincutoff, CryVR_filters_enable, CryVR_filters_euro_enable";
    }

    const char* CPluginOneEuro::GetStatus() const
    {
        return "OK";
    }

    // TODO: Add your plugin concrete interface implementation
}