/* Onde Euro Filter vec3 node - for licensing and copyright see license.txt */

/* Entete commune */
#include "StdAfx.h"
#include "Filters/OneEuroFilter.h"

/* Entete Plugin */
#include <CPluginOneEuro.h>



class CFlowOneEuroFilterVec : public CFlowBaseNode<eNCT_Instanced>
{
        //OneEuroFilter *oef_w;
        OneEuroFilter* oef_x;
        OneEuroFilter* oef_y;
        OneEuroFilter* oef_z;

        enum EInputPorts
        {
            ACTIVE,
            IN_Value,
        };

        enum EOutputPorts
        {
            OUT_Value,
        };

    public:
        bool active;

        ////////////////////////////////////////////////////
        CFlowOneEuroFilterVec( SActivationInfo* pActInfo ) {}
        ////////////////////////////////////////////////////
        virtual ~CFlowOneEuroFilterVec( void ) {}
        ////////////////////////////////////////////////////
        virtual void Serialize( SActivationInfo* pActInfo, TSerialize ser ) {}

        ////////////////////////////////////////////////////
        virtual void GetConfiguration( SFlowNodeConfig& config )
        {
            // Define input ports here, in same order as EInputPorts
            static const SInputPortConfig inputs[] =
            {
                InputPortConfig<bool> ( "Active", _HELP( "Activation" ) ),
                InputPortConfig<Vec3> ( "Valeur", Vec3( 0, 0, 0 ), _HELP( "Valeur a filtrer" ) ),
                {0},
            };

            // Define output ports here, in same order as EOutputPorts
            static const SOutputPortConfig outputs[] =
            {
                OutputPortConfig<Vec3> ( "Valeur filtree", _HELP( "Fov courrant" ) ),
                {0},
            };

            // Fill in configuration
            config.pInputPorts = inputs;
            config.pOutputPorts = outputs;
            config.sDescription = _HELP( "FG node that sets up a CAVE environment" );
            config.SetCategory( EFLN_APPROVED );
        }




        ////////////////////////////////////////////////////
        virtual void ProcessEvent( EFlowEvent event, SActivationInfo* pActInfo )
        {
            switch ( event )
            {
                case eFE_Initialize:
                    {
                        oef_x = new OneEuroFilter ();
                        oef_y = new OneEuroFilter ();
                        oef_z = new OneEuroFilter ();
                    }
                    break;

                case eFE_Activate:
                    {
                        if ( IsPortActive( pActInfo, ACTIVE ) )
                        {
                            active = GetPortBool( pActInfo, ACTIVE );
                            pActInfo->pGraph->SetRegularlyUpdated( pActInfo->myID, true );
                        }
                    }
                    break;

                case eFE_Update:
                    {
                        if ( !active )
                        {
                            return;
                        }

                        oef_x->increaseTimeStamp( 1.0 / oef_x->getFrequence() );
                        oef_y->increaseTimeStamp( 1.0 / oef_y->getFrequence() );
                        oef_z->increaseTimeStamp( 1.0 / oef_z->getFrequence() );

                        Vec3 valeur =  GetPortVec3( pActInfo, IN_Value );
                        float filtered_x = ( float )oef_x->filter( valeur.x ) ;
                        float filtered_y = ( float )oef_y->filter( valeur.y ) ;
                        float filtered_z = ( float )oef_z->filter( valeur.z ) ;

                        Vec3 filtered = Vec3( filtered_x, filtered_y, filtered_z );
                        ActivateOutput( pActInfo, OUT_Value, filtered );
                    }
            }
        }

        virtual void GetMemoryStatistics( ICrySizer* s )
        {
            s->Add( *this );
        }
        virtual IFlowNodePtr Clone( SActivationInfo* pActInfo )
        {
            return new CFlowOneEuroFilterVec( pActInfo );
        }
        virtual void GetMemoryUsage( ICrySizer* s ) const
        {
            s->Add( *this );
        }

};


REGISTER_FLOW_NODE( "CryVR:Filters_Plugin:OneEuroFilterVec3", CFlowOneEuroFilterVec );
