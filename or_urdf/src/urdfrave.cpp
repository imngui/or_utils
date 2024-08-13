#include "urdfrave.h"
#include "urdf_loader.h"

const std::string URDFRavePlugin::_pluginname = "URDFRavePlugin";

URDFRavePlugin::URDFRavePlugin()
{
    _interfaces[OpenRAVE::PT_Module].push_back("urdf_");
}

URDFRavePlugin::~URDFRavePlugin() {}

OpenRAVE::InterfaceBasePtr URDFRavePlugin::CreateInterface(OpenRAVE::InterfaceType type, const std::string& interfacename, std::istream& sinput, OpenRAVE::EnvironmentBasePtr penv)
{
    if( type == OpenRAVE::PT_Module && interfacename == "urdf_" ) {
        return boost::make_shared<or_urdf::URDFLoader>(penv);
    }
    return OpenRAVE::InterfaceBasePtr();
}

const URDFRavePlugin::InterfaceMap& URDFRavePlugin::GetInterfaces() const
{
    return _interfaces;
}

const std::string& URDFRavePlugin::GetPluginName() const
{
    return _pluginname;
}

OPENRAVE_PLUGIN_API RavePlugin* CreatePlugin() {
    return new URDFRavePlugin();
}
