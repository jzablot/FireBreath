#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for windowlessDrawer
#
#\**********************************************************/

set(PLUGIN_NAME "windowlessDrawer")
set(PLUGIN_PREFIX "WDR")
set(COMPANY_NAME "firebreath")

# ActiveX constants:
set(FBTYPELIB_NAME windowlessDrawerLib)
set(FBTYPELIB_DESC "windowlessDrawer 1.0 Type Library")
set(IFBControl_DESC "windowlessDrawer Control Interface")
set(FBControl_DESC "windowlessDrawer Control Class")
set(IFBComJavascriptObject_DESC "windowlessDrawer IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "windowlessDrawer ComJavascriptObject Class")
set(IFBComEventSource_DESC "windowlessDrawer IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID fcaf3066-acae-5f3a-9012-32aa008189f0)
set(IFBControl_GUID 148d20ab-75e7-536a-8633-b112a4be05d9)
set(FBControl_GUID 0ed54bb8-6c0b-5644-b612-a764ca752f40)
set(IFBComJavascriptObject_GUID 27554ff9-826d-5aa8-b365-866e0673c26b)
set(FBComJavascriptObject_GUID 5c6402f4-254a-516c-a1db-45651ffe3885)
set(IFBComEventSource_GUID ae90a738-9a94-55ba-956b-1255bc70b55e)

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "firebreath.windowlessDrawer")
set(MOZILLA_PLUGINID "firebreath.com/windowlessDrawer")

# strings
set(FBSTRING_CompanyName "firebreath")
set(FBSTRING_FileDescription "windowless drawing for win32")
set(FBSTRING_PLUGIN_VERSION "1.0.0")
set(FBSTRING_LegalCopyright "Copyright 2011 firebreath")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "windowlessDrawer")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "windowlessDrawer")
set(FBSTRING_MIMEType "application/x-windowlessdrawer")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
