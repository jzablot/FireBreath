/**********************************************************\

  Auto-generated windowlessDrawer.cpp

  This file contains the auto-generated main plugin object
  implementation for the windowlessDrawer project

\**********************************************************/

#include "windowlessDrawerAPI.h"

#include "windowlessDrawer.h"



extern HINSTANCE gInstance;

///////////////////////////////////////////////////////////////////////////////
/// @fn windowlessDrawer::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void windowlessDrawer::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn windowlessDrawer::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void windowlessDrawer::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  windowlessDrawer constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
windowlessDrawer::windowlessDrawer() : mGrow(0), mFirstRefresh(true)
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  windowlessDrawer destructor.
///////////////////////////////////////////////////////////////////////////////
windowlessDrawer::~windowlessDrawer()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void windowlessDrawer::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<windowlessDrawer> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr windowlessDrawer::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<windowlessDrawerAPI>(FB::ptr_cast<windowlessDrawer>(shared_from_this()), m_host);
}

bool windowlessDrawer::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool windowlessDrawer::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool windowlessDrawer::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

void windowlessDrawer::refreshLoop()
{
   try
   {

      HDC hdc;
      PAINTSTRUCT ps;
      hdc = BeginPaint(mWindow, &ps);

      HBRUSH brush = CreateSolidBrush(RGB(100, 0, 25));
      SelectObject(hdc, brush);   
      Rectangle(hdc, 0, 0, 300, 300);
      DeleteObject(brush);

      EndPaint(mWindow, &ps);


      for (;;)
      {
         
         {
            boost::recursive_mutex::scoped_lock lock(mMutex);          

            static bool growing = true;

            if (growing)
            {
               if (mGrow < 300)
               {
                  mGrow++;
               }
               else
               {
                  growing = false;
                  mGrow--;
               }
            }
            else
            {
               if (mGrow > 0)
               {
                  mGrow--;
               }
               else
               {
                  growing = true;
                  mGrow++;
               }
            }
         }
         
         ::InvalidateRect(mWindow, NULL, TRUE);         
         boost::this_thread::sleep(boost::posix_time::milliseconds(50));
      }
   }
   catch (boost::thread_interrupted)
   {
   }
}

bool windowlessDrawer::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *w)
{
    FB::PluginWindowlessWin* windowless = dynamic_cast<FB::PluginWindowlessWin*>(w);
    if (windowless)
    {
       mPluginWindowlessWindow = windowless;

      WNDCLASSEX wc;

      wc.cbSize        = sizeof(WNDCLASSEX);
      wc.style         = 0;
      wc.lpfnWndProc   = &windowlessDrawer::WinProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hInstance     = gInstance;
      wc.lpszMenuName  = NULL;
      wc.lpszClassName = L"windowlessDrawerClass";
      wc.hIcon = NULL;
      wc.hCursor = NULL;
      wc.hIconSm = NULL;
      wc.hbrBackground = NULL;

      mAtom = ::RegisterClassExW(&wc);
      if (mAtom)
      {
         // ideally this would be off window -- not sure how to do that
         mWindow = ::CreateWindowExA(  0,
                                       "windowlessDrawerClass",
                                       "windowlessDrawerWindow",
                                       0,
                                       0,
                                       0,
                                       300,
                                       300,
                                       NULL,
                                       NULL,
                                       gInstance,
                                       NULL);

         if (mWindow)
         {            
            ::ShowWindow(mWindow, SW_SHOW);
            ::SetWindowLongA(mWindow, GWL_USERDATA, (LONG)this);
            mRefreshWindowThread.reset(new boost::thread(&windowlessDrawer::refreshLoop, this));  
         }
      }


       return true;
    }

    return false;
}

bool windowlessDrawer::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{   
   mRefreshWindowThread->interrupt();
   mRefreshWindowThread->join();

   ::DestroyWindow(mWindow);
   ::UnregisterClassA("windowlessDrawerClass", gInstance);   

    return true;    
}

bool windowlessDrawer::onRefreshEvent(FB::RefreshEvent *evt, FB::PluginWindow *w)
{
   FB::PluginWindowlessWin* windowless = dynamic_cast<FB::PluginWindowlessWin*>(w);
   if (windowless)
   {
      HDC realWindowHdc = ::GetDC(mWindow);

      if (mFirstRefresh)
      {
         mFirstRefresh = false;         
      }

      // there are issues with this blit; it doesn't seem to be getting the right
      // area from mWindow. 

      BOOL okay = ::BitBlt(windowless->getHDC(), 
                           windowless->getWindowPosition().left, 
                           windowless->getWindowPosition().top, 
                           windowless->getWindowWidth(), 
                           windowless->getWindowHeight(),
                           realWindowHdc, 
                           0, 
                           0, 
                           SRCCOPY);

      return true;
   }

   return false;
}

LRESULT CALLBACK 
windowlessDrawer::WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   if (uMsg == WM_PAINT)
   {
      windowlessDrawer* cpt = (windowlessDrawer*)::GetWindowLongA(hWnd, GWL_USERDATA);
      if (cpt)
      {
         HDC hdc;
         PAINTSTRUCT ps;
         hdc = BeginPaint(hWnd, &ps);

         int grow;
         {
            boost::recursive_mutex::scoped_lock lock(cpt->mMutex);
            grow = cpt->mGrow;
         }

         HBRUSH brush = CreateSolidBrush(RGB(100, 100, 25));
         SelectObject(hdc, brush);   
         Rectangle(hdc, 0, 0, grow, grow);
         DeleteObject(brush);

         EndPaint(hWnd, &ps);

         windowlessDrawer* cpt = (windowlessDrawer*)::GetWindowLongA(hWnd, GWL_USERDATA);
         if (cpt)
         {
            cpt->mPluginWindowlessWindow->InvalidateWindow();
         }

         return true;
      }
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}