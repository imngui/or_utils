#ifndef OPENRAVE_PLUGIN_URDFRAVE_H
#define OPENRAVE_PLUGIN_URDFRAVE_H

#include <openrave/plugin.h>

struct URDFRavePlugin : public RavePlugin
{
    URDFRavePlugin();
    ~URDFRavePlugin() override;
    OpenRAVE::InterfaceBasePtr CreateInterface(OpenRAVE::InterfaceType type, const std::string& interfacename, std::istream& sinput, OpenRAVE::EnvironmentBasePtr penv) override;
    const InterfaceMap& GetInterfaces() const override;
    const std::string& GetPluginName() const override;
private:
    static const std::string _pluginname;
    InterfaceMap _interfaces;
};

#endif // OPENRAVE_PLUGIN_URDFRAVE_H