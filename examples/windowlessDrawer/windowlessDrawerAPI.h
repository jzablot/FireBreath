/**********************************************************\

  Auto-generated windowlessDrawerAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "windowlessDrawer.h"

#ifndef H_windowlessDrawerAPI
#define H_windowlessDrawerAPI

class windowlessDrawerAPI : public FB::JSAPIAuto
{
public:
    windowlessDrawerAPI(const windowlessDrawerPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~windowlessDrawerAPI();

    windowlessDrawerPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Method test-event
    void testEvent(const FB::variant& s);

private:
    windowlessDrawerWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_windowlessDrawerAPI

