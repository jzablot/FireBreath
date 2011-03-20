/**********************************************************\

  Auto-generated windowlessDrawerAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "windowlessDrawerAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn windowlessDrawerAPI::windowlessDrawerAPI(const windowlessDrawerPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
windowlessDrawerAPI::windowlessDrawerAPI(const windowlessDrawerPtr& plugin, const FB::BrowserHostPtr& host) : m_plugin(plugin), m_host(host)
{
    registerMethod("echo",      make_method(this, &windowlessDrawerAPI::echo));
    registerMethod("testEvent", make_method(this, &windowlessDrawerAPI::testEvent));

    // Read-write property
    registerProperty("testString",
                     make_property(this,
                        &windowlessDrawerAPI::get_testString,
                        &windowlessDrawerAPI::set_testString));

    // Read-only property
    registerProperty("version",
                     make_property(this,
                        &windowlessDrawerAPI::get_version));
    
    
    registerEvent("onfired");    
}

///////////////////////////////////////////////////////////////////////////////
/// @fn windowlessDrawerAPI::~windowlessDrawerAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
windowlessDrawerAPI::~windowlessDrawerAPI()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @fn windowlessDrawerPtr windowlessDrawerAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
windowlessDrawerPtr windowlessDrawerAPI::getPlugin()
{
    windowlessDrawerPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}



// Read/Write property testString
std::string windowlessDrawerAPI::get_testString()
{
    return m_testString;
}
void windowlessDrawerAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string windowlessDrawerAPI::get_version()
{
    return "CURRENT_VERSION";
}

// Method echo
FB::variant windowlessDrawerAPI::echo(const FB::variant& msg)
{
    return msg;
}

void windowlessDrawerAPI::testEvent(const FB::variant& var)
{
    FireEvent("onfired", FB::variant_list_of(var)(true)(1));
}

