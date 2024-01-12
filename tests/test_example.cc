#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <framework/util/util.h>

#include <example/source/log.h>
#include <example/interface/example/nr_plugin_example.h>
#include <example/env/export.h>

/// mock NRSDK
static NRInterfaces s_interfaces;
static NRPluginLifecycleProvider s_lifecycle_provider;
static const NRPluginHandle s_handle = 1;
static NRExampleInterface s_example_interface;
static NRExampleProvider s_example_provider;

EXAMPLE_EXTERN_C_BEGIN
extern void NRPluginLoad_Example(NRInterfaces* interfaces);
EXAMPLE_EXTERN_C_END

NRPluginResult RegisterLifecycleProvider(
		const char *plugin_name, 
		const char *id, 
		const NRPluginLifecycleProvider *provider,
        uint32_t provider_size) 
{
    UNUSED(plugin_name);
    UNUSED(id);
    CHECK(provider_size == sizeof(NRPluginLifecycleProvider));
    s_lifecycle_provider = *provider;
    std::cout << __func__ << " success" << std::endl;
    return NR_PLUGIN_RESULT_SUCCESS;
}

NRPluginResult RegisterProvider(
		NRPluginHandle handle, 
		const NRExampleProvider *provider, 
		uint32_t provider_size) {
	CHECK(s_handle == handle);
    CHECK(provider_size == sizeof(NRExampleProvider));
    s_example_provider = *provider;
    std::cout << __func__ << " success" << std::endl;
    return NR_PLUGIN_RESULT_SUCCESS;
}

NRPluginResult SetVariable(NRPluginHandle handle, uint32_t variable) {
	CHECK(s_handle == handle);
    std::cout << __func__ << " = " << variable << std::endl;
    return NR_PLUGIN_RESULT_SUCCESS;
}

NRInterface *GetInterface(NRInterfaceGUID guid, unsigned long long* out_interface_size) {
    UNUSED(guid);
    std::cout << __func__ << " success" << std::endl;
	*out_interface_size = sizeof(s_example_interface);
    return &s_example_interface;
}

TEST_CASE("Example Test") {
    /// mock NRSDK
    s_interfaces.GetInterface = GetInterface;
    s_example_interface.RegisterLifecycleProvider = RegisterLifecycleProvider;
	s_example_interface.RegisterProvider = RegisterProvider;
    s_example_interface.SetVariable = SetVariable;

    /// call load function
    NRPluginLoad_Example(&s_interfaces);

    s_lifecycle_provider.Register(s_handle);
    s_lifecycle_provider.Initialize(s_handle);
    s_lifecycle_provider.Start(s_handle);
    s_lifecycle_provider.Pause(s_handle);
    s_lifecycle_provider.Resume(s_handle);
    s_lifecycle_provider.Stop(s_handle);
    s_lifecycle_provider.Release(s_handle);
    s_lifecycle_provider.Unregister(s_handle);
}
