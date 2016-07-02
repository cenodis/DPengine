#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>



/// this macro facilitates size calculation for static arrays
#define countof(s) (sizeof(s) / sizeof(*(s)))

/// useful when including in parallel with ObjC headers
#ifndef NON_ENUM

/// non-integer precision, so #define instead of enum
#define NSVariableStatusItemLength (-1.0)
#define NSSquareStatusItemLength   (-2.0)

enum {
    NSUserDomainMask    = 0x0001,
    NSLocalDomainMask   = 0x0002,
    NSNetworkDomainMask = 0x0004,
    NSSystemDomainMask  = 0x0008,
    NSAllDomainsMask    = 0xFFFF,
};
enum {
    NSApplicationDirectory          =   1,
    NSDemoApplicationDirectory      =   2,
    NSDeveloperApplicationDirectory =   3,
    NSAdminApplicationDirectory     =   4,
    NSLibraryDirectory              =   5,
    NSDeveloperDirectory            =   6,
    NSUserDirectory                 =   7,
    NSDocumentationDirectory        =   8,
    NSDocumentDirectory             =   9,
    NSCoreServiceDirectory          =  10,
    NSAutosavedInformationDirectory =  11,
    NSDesktopDirectory              =  12,
    NSCachesDirectory               =  13,
    NSApplicationSupportDirectory   =  14,
    NSDownloadsDirectory            =  15,
    NSInputMethodsDirectory         =  16,
    NSMoviesDirectory               =  17,
    NSMusicDirectory                =  18,
    NSPicturesDirectory             =  19,
    NSPrinterDescriptionDirectory   =  20,
    NSSharedPublicDirectory         =  21,
    NSPreferencePanesDirectory      =  22,
    NSItemReplacementDirectory      =  99,
    NSAllApplicationsDirectory      = 100,
    NSAllLibrariesDirectory         = 101,
};
enum {
    NSBorderlessWindowMask         = (0     ),
    NSTitledWindowMask             = (1 << 0),
    NSClosableWindowMask           = (1 << 1),
    NSMiniaturizableWindowMask     = (1 << 2),
    NSResizableWindowMask          = (1 << 3),
    NSTexturedBackgroundWindowMask = (1 << 8),
};
enum {
    NSBackingStoreRetained    = 0,
    NSBackingStoreNonretained = 1,
    NSBackingStoreBuffered    = 2,
};
enum {
    NSApplicationActivationPolicyRegular    = 0,
    NSApplicationActivationPolicyAccessory  = 1,
    NSApplicationActivationPolicyProhibited = 2,
};
enum {
    NSMixedState = -1,
    NSOffState   =  0,
    NSOnState    =  1,
};
enum {
    NSNormalWindowLevel   =  0,
    NSFloatingWindowLevel =  3,
    NSDockWindowLevel     =  5,
    NSSubmenuWindowLevel  = 10,
    NSMainMenuWindowLevel = 20,
};
enum {
    NSDefaultControlTint  = 0,
    NSBlueControlTint     = 1,
    NSGraphiteControlTint = 6,
    NSClearControlTint    = 7,
};
enum {
    NSLeftTextAlignment      = 0,
    NSRightTextAlignment     = 1,
    NSCenterTextAlignment    = 2,
    NSJustifiedTextAlignment = 3,
    NSNaturalTextAlignment   = 4
};
enum {
    NSMomentaryLightButton        = 0,
    NSMomentaryPushButton         = 0,
    NSPushOnPushOffButton         = 1,
    NSToggleButton                = 2,
    NSSwitchButton                = 3,
    NSRadioButton                 = 4,
    NSMomentaryChangeButton       = 5,
    NSOnOffButton                 = 6,
    NSMomentaryLight              = 7,
    NSMomentaryPushInButton       = 7,
    NSAcceleratorButton           = 8,
    NSMultiLevelAcceleratorButton = 9,
};
enum {
    NSRoundedBezelStyle           =  1,
    NSRegularSquareBezelStyle     =  2,
    NSSmallIconButtonBezelStyle   =  2,
    NSThickSquareBezelStyle       =  3,
    NSThickerSquareBezelStyle     =  4,
    NSDisclosureBezelStyle        =  5,
    NSShadowlessSquareBezelStyle  =  6,
    NSCircularBezelStyle          =  7,
    NSTexturedSquareBezelStyle    =  8,
    NSHelpButtonBezelStyle        =  9,
    NSSmallSquareBezelStyle       = 10,
    NSTexturedRoundedBezelStyle   = 11,
    NSRoundRectBezelStyle         = 12,
    NSRecessedBezelStyle          = 13,
    NSRoundedDisclosureBezelStyle = 14,
    NSInlineBezelStyle            = 15,
};
enum {
    NSNoImage       = 0,
    NSImageOnly     = 1,
    NSImageLeft     = 2,
    NSImageRight    = 3,
    NSImageBelow    = 4,
    NSImageAbove    = 5,
    NSImageOverlaps = 6,
};
enum {
    NSTrackingMouseEnteredAndExited    = (1 << 0),
    NSTrackingMouseMoved               = (1 << 1),
    NSTrackingCursorUpdate             = (1 << 2),
    NSTrackingActiveWhenFirstResponder = (1 << 3),
    NSTrackingActiveInKeyWindow        = (1 << 4),
    NSTrackingActiveInActiveApp        = (1 << 5),
    NSTrackingActiveAlways             = (1 << 6),
    NSTrackingAssumeInside             = (1 << 7),
    NSTrackingInVisibleRect            = (1 << 8),
    NSTrackingEnabledDuringMouseDrag   = (1 << 9),
};
enum {
    NSLeftMouseDown      =  1,
    NSLeftMouseUp        =  2,
    NSRightMouseDown     =  3,
    NSRightMouseUp       =  4,
    NSMouseMoved         =  5,
    NSLeftMouseDragged   =  6,
    NSRightMouseDragged  =  7,
    NSMouseEntered       =  8,
    NSMouseExited        =  9,
    NSKeyDown            = 10,
    NSKeyUp              = 11,
    NSFlagsChanged       = 12,
    NSAppKitDefined      = 13,
    NSSystemDefined      = 14,
    NSApplicationDefined = 15,
    NSPeriodic           = 16,
    NSCursorUpdate       = 17,
    NSScrollWheel        = 22,
    NSTabletPoint        = 23,
    NSTabletProximity    = 24,
    NSOtherMouseDown     = 25,
    NSOtherMouseUp       = 26,
    NSOtherMouseDragged  = 27,
};
enum {
    NSOpenGLPFAAllRenderers          =   1,
    NSOpenGLPFATripleBuffer          =   3,
    NSOpenGLPFADoubleBuffer          =   5,
    NSOpenGLPFAStereo                =   6,
    NSOpenGLPFAAuxBuffers            =   7,
    NSOpenGLPFAColorSize             =   8,
    NSOpenGLPFAAlphaSize             =  11,
    NSOpenGLPFADepthSize             =  12,
    NSOpenGLPFAStencilSize           =  13,
    NSOpenGLPFAAccumSize             =  14,
    NSOpenGLPFAMinimumPolicy         =  51,
    NSOpenGLPFAMaximumPolicy         =  52,
    NSOpenGLPFAOffScreen             =  53,
    NSOpenGLPFAFullScreen            =  54,
    NSOpenGLPFASampleBuffers         =  55,
    NSOpenGLPFASamples               =  56,
    NSOpenGLPFAAuxDepthStencil       =  57,
    NSOpenGLPFAColorFloat            =  58,
    NSOpenGLPFAMultisample           =  59,
    NSOpenGLPFASupersample           =  60,
    NSOpenGLPFASampleAlpha           =  61,
    NSOpenGLPFARendererID            =  70,
    NSOpenGLPFASingleRenderer        =  71,
    NSOpenGLPFANoRecovery            =  72,
    NSOpenGLPFAAccelerated           =  73,
    NSOpenGLPFAClosestPolicy         =  74,
    NSOpenGLPFARobust                =  75,
    NSOpenGLPFABackingStore          =  76,
    NSOpenGLPFAMPSafe                =  78,
    NSOpenGLPFAWindow                =  80,
    NSOpenGLPFAMultiScreen           =  81,
    NSOpenGLPFACompliant             =  83,
    NSOpenGLPFAScreenMask            =  84,
    NSOpenGLPFAPixelBuffer           =  90,
    NSOpenGLPFARemotePixelBuffer     =  91,
    NSOpenGLPFAAllowOfflineRenderers =  96,
    NSOpenGLPFAAcceleratedCompute    =  97,
    NSOpenGLPFAOpenGLProfile         =  99,
    NSOpenGLPFAVirtualScreenCount    = 128,
};
enum {
    NSOpenGLCPSwapInterval           = 222,
    NSOpenGLCPSurfaceOrder           = 235,
    NSOpenGLCPSurfaceOpacity         = 236,
    NSOpenGLCPSurfaceBackingSize     = 304,
    NSOpenGLCPReclaimResources       = 308,
    NSOpenGLCPCurrentRendererID      = 309,
    NSOpenGLCPGPUVertexProcessing    = 310,
    NSOpenGLCPGPUFragmentProcessing  = 311,
    NSOpenGLCPHasDrawable            = 314,
    NSOpenGLCPMPSwapsInFlight        = 315,
};

#endif



#define STRING_OBJC_CLASSES    \
       "NSObject",             \
       "NSApplication",        \
       "NSAutoreleasePool",    \
       "NSBundle",             \
       "NSColor",              \
       "NSImage",              \
       "NSMenu",               \
       "NSMenuItem",           \
       "NSScreen",             \
       "NSStatusBar",          \
       "NSString",             \
       "NSWindow",             \
       "NSView",               \
       "NSOpenGLView",         \
       "NSOpenGLPixelFormat",  \
       "NSGraphicsContext",    \
       "NSCursor",             \
       "NSEvent",              \
       "NSTrackingArea",       \
       "NSFileManager",        \
       "NSFont",               \
       "NSTextField",          \
       "NSButton",             \
       "NSProgressIndicator",  \
       "NSStepper",            \
       "NSScrollView",         \
       "NSTableView",          \
       "NSTableColumn"

#define NSObject             (LoadedObjCClasses[ 0])
#define NSApplication        (LoadedObjCClasses[ 1])
#define NSAutoreleasePool    (LoadedObjCClasses[ 2])
#define NSBundle             (LoadedObjCClasses[ 3])
#define NSColor              (LoadedObjCClasses[ 4])
#define NSImage              (LoadedObjCClasses[ 5])
#define NSMenu               (LoadedObjCClasses[ 6])
#define NSMenuItem           (LoadedObjCClasses[ 7])
#define NSScreen             (LoadedObjCClasses[ 8])
#define NSStatusBar          (LoadedObjCClasses[ 9])
#define NSString             (LoadedObjCClasses[10])
#define NSWindow             (LoadedObjCClasses[11])
#define NSView               (LoadedObjCClasses[12])
#define NSOpenGLView         (LoadedObjCClasses[13])
#define NSOpenGLPixelFormat  (LoadedObjCClasses[14])
#define NSGraphicsContext    (LoadedObjCClasses[15])
#define NSCursor             (LoadedObjCClasses[16])
#define NSEvent              (LoadedObjCClasses[17])
#define NSTrackingArea       (LoadedObjCClasses[18])
#define NSFileManager        (LoadedObjCClasses[19])
#define NSFont               (LoadedObjCClasses[20])
#define NSTextField          (LoadedObjCClasses[21])
#define NSButton             (LoadedObjCClasses[22])
#define NSProgressIndicator  (LoadedObjCClasses[23])
#define NSStepper            (LoadedObjCClasses[24])
#define NSScrollView         (LoadedObjCClasses[25])
#define NSTableView          (LoadedObjCClasses[26])
#define NSTableColumn        (LoadedObjCClasses[27])



#define STRING_OBJC_SELECTORS                          \
       "init",                                         \
       "alloc",                                        \
       "release",                                      \
       "autorelease",                                  \
       "mainBundle",                                   \
       "bundlePath",                                   \
       "activateIgnoringOtherApps:",                   \
       "addItem:",                                     \
       "clearColor",                                   \
       "controlColor",                                 \
       "imageNamed:",                                  \
       "initWithCGImage:size:",                        \
       "initWithRect:options:owner:userInfo:",         \
       "initWithContentRect:styleMask:backing:defer:", \
       "initWithTitle:action:keyEquivalent:",          \
       "contentRectForFrameRect:",                     \
       "frameRectForContentRect:",                     \
       "frame",                                        \
       "setFrame:",                                    \
       "setFrame:display:animate:",                    \
       "setMinSize:",                                  \
       "setTitle:",                                    \
       "setStringValue:",                              \
       "makeMainWindow",                               \
       "makeKeyWindow",                                \
       "orderFront:",                                  \
       "orderOut:",                                    \
       "run",                                          \
       "separatorItem",                                \
       "setActivationPolicy:",                         \
       "setAutoenablesItems:",                         \
       "setBackgroundColor:",                          \
       "setDelegate:",                                 \
       "setEnabled:",                                  \
       "setHasShadow:",                                \
       "setHighlightMode:",                            \
       "setImage:",                                    \
       "setMenu:",                                     \
       "setOnStateImage:",                             \
       "setOpaque:",                                   \
       "setState:",                                    \
       "setSubmenu:",                                  \
       "setButtonType:",                               \
       "setBezelStyle:",                               \
       "setImagePosition:",                            \
       "setEditable:",                                 \
       "setSelectable:",                               \
       "setBezeled:",                                  \
       "setBordered:",                                 \
       "setDrawsBackground:",                          \
       "sharedApplication",                            \
       "statusItemWithLength:",                        \
       "UTF8String",                                   \
       "stringWithUTF8String:",                        \
       "systemStatusBar",                              \
       "thickness",                                    \
       "visibleFrame",                                 \
       "intrinsicContentSize",                         \
       "mainScreen",                                   \
       "stop:",                                        \
       "drain",                                        \
       "delegate",                                     \
       "setTag:",                                      \
       "tag",                                          \
       "setRepresentedObject:",                        \
       "representedObject",                            \
       "setTarget:",                                   \
       "target",                                       \
       "setIgnoresMouseEvents:",                       \
       "hide:",                                        \
       "unhide:",                                      \
       "retain",                                       \
       "retainCount",                                  \
       "initWithFrame:pixelFormat:",                   \
       "contentView",                                  \
       "setContentView:",                              \
       "setDocumentView:",                             \
       "addSubview:",                                  \
       "setHasVerticalScroller:",                      \
       "initWithAttributes:",                          \
       "currentContext",                               \
       "graphicsPort",                                 \
       "setLevel:",                                    \
       "pointingHandCursor",                           \
       "set",                                          \
       "setNeedsDisplay:",                             \
       "windowShouldClose:",                           \
       "windowDidResize:",                             \
       "isFlipped",                                    \
       "isOpaque",                                     \
       "drawRect:",                                    \
       "_M",                                           \
       "mouseLocationOutsideOfEventStream",            \
       "pressedMouseButtons",                          \
       "openGLContext",                                \
       "flushBuffer",                                  \
       "makeCurrentContext",                           \
       "setValues:forParameter:",                      \
       "popUpContextMenu:withEvent:forView:",          \
       "windowNumber",                                 \
       "objectAtIndex:",                               \
       "path",                                         \
       "defaultManager",                               \
       "systemFontOfSize:",                            \
       "ascender",                                     \
       "maximumAdvancement",                           \
       "URLsForDirectory:inDomains:",                  \
       "postEvent:atStart:",                           \
       "addTrackingArea:",                             \
       "enableCursorRects",                            \
       "resetCursorRects",                             \
       "addCursorRect:cursor:",                        \
       /** srsly, next line is just batshit insane **/ \
       "otherEventWithType:location:modifierFlags:timestamp:windowNumber:context:subtype:data1:data2:", \
       "setIndeterminate:",                            \
       "setMaxValue:",                                 \
       "setDoubleValue:",                              \
       "setWidth:",                                    \
       "setHidden:",                                   \
       "setAlignment:",                                \
       "addTableColumn:",                              \
       "headerCell",                                   \
       "class",                                        \
       "setWantsLayer:",                               \
       "drawInRect:withAttributes:"

#define init(inst)                                                     objc_msgSend(inst, LoadedObjCSelectors[  0])
#define alloc(inst)                                                    objc_msgSend(inst, LoadedObjCSelectors[  1])
#define release(inst)                                                  objc_msgSend(inst, LoadedObjCSelectors[  2])
#define autorelease(inst)                                              objc_msgSend(inst, LoadedObjCSelectors[  3])
#define mainBundle(inst)                                               objc_msgSend(inst, LoadedObjCSelectors[  4])
#define bundlePath(inst)                                               objc_msgSend(inst, LoadedObjCSelectors[  5])
#define activateIgnoringOtherApps_(inst, b)                            objc_msgSend(inst, LoadedObjCSelectors[  6], (bool)(b))
#define addItem_(inst, i)                                              objc_msgSend(inst, LoadedObjCSelectors[  7], i)
#define clearColor(inst)                                               objc_msgSend(inst, LoadedObjCSelectors[  8])
#define controlColor(inst)                                             objc_msgSend(inst, LoadedObjCSelectors[  9])
#define imageNamed_(inst, s)                                           objc_msgSend(inst, LoadedObjCSelectors[ 10], s)
#define initWithCGImage_size_(inst, i, s)                              objc_msgSend(inst, LoadedObjCSelectors[ 11], i, s)
#define initWithRect_options_owner_userInfo_(inst, r, o, w, i)         objc_msgSend(inst, LoadedObjCSelectors[ 12], (CGRect)(r), o, w, i)
#define initWithContentRect_styleMask_backing_defer_(inst, r, m, b, d) objc_msgSend(inst, LoadedObjCSelectors[ 13], r, (unsigned)(m), (unsigned)(b), (bool)(d))
#define initWithTitle_action_keyEquivalent_(inst, t, a, k)             objc_msgSend(inst, LoadedObjCSelectors[ 14], t, a, k)
#define ContentRectForFrameRect_                                                          LoadedObjCSelectors[ 15]
#define FrameRectForContentRect_                                                          LoadedObjCSelectors[ 16]
#define Frame                                                                             LoadedObjCSelectors[ 17]
#define setFrame_(inst, f)                                             objc_msgSend(inst, LoadedObjCSelectors[ 18], f)
#define setFrame_display_animate_(inst, f, d, a)                       objc_msgSend(inst, LoadedObjCSelectors[ 19], f, d, a)
#define setMinSize_(inst, s)                                           objc_msgSend(inst, LoadedObjCSelectors[ 20], s)
#define setTitle_(inst, t)                                             objc_msgSend(inst, LoadedObjCSelectors[ 21], t)
#define setStringValue_(inst, s)                                       objc_msgSend(inst, LoadedObjCSelectors[ 22], s)
#define makeMainWindow(inst)                                           objc_msgSend(inst, LoadedObjCSelectors[ 23])
#define makeKeyWindow(inst)                                            objc_msgSend(inst, LoadedObjCSelectors[ 24])
#define orderFront_(inst, w)                                           objc_msgSend(inst, LoadedObjCSelectors[ 25], w)
#define orderOut_(inst, w)                                             objc_msgSend(inst, LoadedObjCSelectors[ 26], w)
#define run(inst)                                                      objc_msgSend(inst, LoadedObjCSelectors[ 27])
#define separatorItem(inst)                                            objc_msgSend(inst, LoadedObjCSelectors[ 28])
#define setActivationPolicy_(inst, p)                                  objc_msgSend(inst, LoadedObjCSelectors[ 29], (unsigned)(p))
#define setAutoenablesItems_(inst, b)                                  objc_msgSend(inst, LoadedObjCSelectors[ 30], (bool)(b))
#define setBackgroundColor_(inst, c)                                   objc_msgSend(inst, LoadedObjCSelectors[ 31], c)
#define setDelegate_(inst, d)                                          objc_msgSend(inst, LoadedObjCSelectors[ 32], d)
#define setEnabled_(inst, b)                                           objc_msgSend(inst, LoadedObjCSelectors[ 33], (bool)(b))
#define setHasShadow_(inst, b)                                         objc_msgSend(inst, LoadedObjCSelectors[ 34], (bool)(b))
#define setHighlightMode_(inst, b)                                     objc_msgSend(inst, LoadedObjCSelectors[ 35], (bool)(b))
#define setImage_(inst, i)                                             objc_msgSend(inst, LoadedObjCSelectors[ 36], i)
#define setMenu_(inst, m)                                              objc_msgSend(inst, LoadedObjCSelectors[ 37], m)
#define setOnStateImage_(inst, i)                                      objc_msgSend(inst, LoadedObjCSelectors[ 38], i)
#define setOpaque_(inst, b)                                            objc_msgSend(inst, LoadedObjCSelectors[ 39], (bool)(b))
#define setState_(inst, s)                                             objc_msgSend(inst, LoadedObjCSelectors[ 40], (unsigned)(s))
#define setSubmenu_(inst, m)                                           objc_msgSend(inst, LoadedObjCSelectors[ 41], m)
#define setButtonType_(inst, t)                                        objc_msgSend(inst, LoadedObjCSelectors[ 42], t)
#define setBezelStyle_(inst, s)                                        objc_msgSend(inst, LoadedObjCSelectors[ 43], s)
#define setImagePosition_(inst, p)                                     objc_msgSend(inst, LoadedObjCSelectors[ 44], p)
#define setEditable_(inst, e)                                          objc_msgSend(inst, LoadedObjCSelectors[ 45], e)
#define setSelectable_(inst, s)                                        objc_msgSend(inst, LoadedObjCSelectors[ 46], s)
#define setBezeled_(inst, b)                                           objc_msgSend(inst, LoadedObjCSelectors[ 47], b)
#define setBordered_(inst, b)                                          objc_msgSend(inst, LoadedObjCSelectors[ 48], b)
#define setDrawsBackground_(inst, d)                                   objc_msgSend(inst, LoadedObjCSelectors[ 49], d)
#define sharedApplication(inst)                                        objc_msgSend(inst, LoadedObjCSelectors[ 50])
#define statusItemWithLength_(inst, l)                                 objc_msgSend(inst, LoadedObjCSelectors[ 51], (double)(l))
#define UTF8String(inst)                                        (char*)objc_msgSend(inst, LoadedObjCSelectors[ 52])
#define stringWithUTF8String_(inst, s)                                 objc_msgSend(inst, LoadedObjCSelectors[ 53], (char*)(s))
#define systemStatusBar(inst)                                          objc_msgSend(inst, LoadedObjCSelectors[ 54])
#define Thickness                                                                         LoadedObjCSelectors[ 55]
#define VisibleFrame                                                                      LoadedObjCSelectors[ 56]
#define IntrinsicContentSize                                                              LoadedObjCSelectors[ 57]
#define mainScreen(inst)                                               objc_msgSend(inst, LoadedObjCSelectors[ 58])
#define stop_(inst, s)                                                 objc_msgSend(inst, LoadedObjCSelectors[ 59], s)
#define drain(inst)                                                    objc_msgSend(inst, LoadedObjCSelectors[ 60])
#define delegate(inst)                                                 objc_msgSend(inst, LoadedObjCSelectors[ 61])
#define setTag_(inst, t)                                               objc_msgSend(inst, LoadedObjCSelectors[ 62], t)
#define tag(inst)                                                      objc_msgSend(inst, LoadedObjCSelectors[ 63])
#define setRepresentedObject_(inst, o)                                 objc_msgSend(inst, LoadedObjCSelectors[ 64], o)
#define representedObject(inst)                                        objc_msgSend(inst, LoadedObjCSelectors[ 65])
#define setTarget_(inst, t)                                            objc_msgSend(inst, LoadedObjCSelectors[ 66], t)
#define target(inst)                                                   objc_msgSend(inst, LoadedObjCSelectors[ 67])
#define setIgnoresMouseEvents_(inst, i)                                objc_msgSend(inst, LoadedObjCSelectors[ 68], (bool)(i))
#define hide_(inst, e)                                                 objc_msgSend(inst, LoadedObjCSelectors[ 69], e)
#define unhide_(inst, e)                                               objc_msgSend(inst, LoadedObjCSelectors[ 70], e)
#define retain(inst)                                                   objc_msgSend(inst, LoadedObjCSelectors[ 71])
#define retainCount(inst)                                              objc_msgSend(inst, LoadedObjCSelectors[ 72])
#define initWithFrame_pixelFormat_(inst, f, p)                         objc_msgSend(inst, LoadedObjCSelectors[ 73], f, p)
#define contentView(inst)                                              objc_msgSend(inst, LoadedObjCSelectors[ 74])
#define setContentView_(inst, v)                                       objc_msgSend(inst, LoadedObjCSelectors[ 75], v)
#define setDocumentView_(inst, v)                                      objc_msgSend(inst, LoadedObjCSelectors[ 76], v)
#define addSubview_(inst, v)                                           objc_msgSend(inst, LoadedObjCSelectors[ 77], v)
#define setHasVerticalScroller_(inst, s)                               objc_msgSend(inst, LoadedObjCSelectors[ 78], s)
#define initWithAttributes_(inst, a)                                   objc_msgSend(inst, LoadedObjCSelectors[ 79], (uint32_t*)(a))
#define currentContext(inst)                                           objc_msgSend(inst, LoadedObjCSelectors[ 80])
#define graphicsPort(inst)                                             objc_msgSend(inst, LoadedObjCSelectors[ 81])
#define setLevel_(inst, l)                                             objc_msgSend(inst, LoadedObjCSelectors[ 82], (long)(l))
#define pointingHandCursor(inst)                                       objc_msgSend(inst, LoadedObjCSelectors[ 83])
#define set(inst)                                                      objc_msgSend(inst, LoadedObjCSelectors[ 84])
#define setNeedsDisplay_(inst, d)                                      objc_msgSend(inst, LoadedObjCSelectors[ 85], (bool)(d))
#define WindowShouldClose_                                                                LoadedObjCSelectors[ 86]
#define WindowDidResize_                                                                  LoadedObjCSelectors[ 87]
#define IsFlipped                                                                         LoadedObjCSelectors[ 88]
#define IsOpaque                                                                          LoadedObjCSelectors[ 89]
#define DrawRect_                                                                         LoadedObjCSelectors[ 90]
#define MenuSelector                                                                      LoadedObjCSelectors[ 91]
#define MouseLocationOutsideOfEventStream                                                 LoadedObjCSelectors[ 92]
#define pressedMouseButtons(inst)                                (long)objc_msgSend(inst, LoadedObjCSelectors[ 93])
#define openGLContext(inst)                                            objc_msgSend(inst, LoadedObjCSelectors[ 94])
#define flushBuffer(inst)                                              objc_msgSend(inst, LoadedObjCSelectors[ 95])
#define makeCurrentContext(inst)                                       objc_msgSend(inst, LoadedObjCSelectors[ 96])
#define setValues_forParameter_(inst, v, p)                            objc_msgSend(inst, LoadedObjCSelectors[ 97], (int*)(v), (int)(p))
#define popUpContextMenu_withEvent_forView_(inst, m, e, v)             objc_msgSend(inst, LoadedObjCSelectors[ 98], m, e, v)
#define windowNumber(inst)                                             objc_msgSend(inst, LoadedObjCSelectors[ 99])
#define objectAtIndex_(inst, i)                                        objc_msgSend(inst, LoadedObjCSelectors[100], i)
#define path(inst)                                                     objc_msgSend(inst, LoadedObjCSelectors[101])
#define defaultManager(inst)                                           objc_msgSend(inst, LoadedObjCSelectors[102])
#define systemFontOfSize_(inst, s)                                     objc_msgSend(inst, LoadedObjCSelectors[103], s)
#define Ascender                                                                          LoadedObjCSelectors[104]
#define MaximumAdvancement                                                                LoadedObjCSelectors[105]
#define URLsForDirectory_inDomains_(inst, u, d)                        objc_msgSend(inst, LoadedObjCSelectors[106], u, d)
#define postEvent_atStart_(inst, e, s)                                 objc_msgSend(inst, LoadedObjCSelectors[107], e, (bool)(s))
#define addTrackingArea_(inst, a)                                      objc_msgSend(inst, LoadedObjCSelectors[108], a)
#define enableCursorRects(inst)                                        objc_msgSend(inst, LoadedObjCSelectors[109])
#define ResetCursorRects                                                                  LoadedObjCSelectors[110]
#define addCursorRect_cursor_(inst, r, c)                              objc_msgSend(inst, LoadedObjCSelectors[111], r, c)
#define MakeEvent(t, l, m, s, w, c)                                 objc_msgSend(NSEvent, LoadedObjCSelectors[112], t, l, m, (CGFloat)(s), w, c, 0, 0, 0)
#define setIndeterminate_(inst, i)                                     objc_msgSend(inst, LoadedObjCSelectors[113], i)
#define setMaxValue_(inst, v)                                          objc_msgSend(inst, LoadedObjCSelectors[114], (double)(v))
#define setDoubleValue_(inst, v)                                       objc_msgSend(inst, LoadedObjCSelectors[115], (double)(v))
#define setWidth_(inst, w)                                             objc_msgSend(inst, LoadedObjCSelectors[116], (int)(w))
#define setHidden_(inst, h)                                            objc_msgSend(inst, LoadedObjCSelectors[117], h)
#define setAlignment_(inst, a)                                         objc_msgSend(inst, LoadedObjCSelectors[118], a)
#define addTableColumn_(inst, c)                                       objc_msgSend(inst, LoadedObjCSelectors[119], c)
#define headerCell(inst)                                               objc_msgSend(inst, LoadedObjCSelectors[120])
#define class(inst)                                             (Class)objc_msgSend(inst, LoadedObjCSelectors[121])
#define setWantsLayer_(inst, w)                                        objc_msgSend(inst, LoadedObjCSelectors[122], w)
#define drawInRect_withAttributes_(inst, r, a)                         objc_msgSend(inst, LoadedObjCSelectors[123], (CGRect)(r), a)



#define GET_IVAR(inst, name, data) object_getInstanceVariable(inst, name, (void**)(data))
#define SET_IVAR(inst, name, data) object_setInstanceVariable(inst, name, (void*)(data))



/// a horrible abomination coming up (but this is generally the way OS X works)
#ifdef __i386__
    /// never tried these, not sure if they are correct
    #define GetT1DV(r, i, s) { void *f = objc_msgSend_fpret;  r = ((typeof(r) (*)(id, SEL))f)(i, s); }
    #define GetT2DV(r, i, s) { void *f = objc_msgSend_stret;      ((void (*)(typeof(r)*, id, SEL))f)(&r, i, s); }
    #define GetT4DV(r, i, s) { void *f = objc_msgSend_stret;      ((void (*)(typeof(r)*, id, SEL))f)(&r, i, s); }
    #define GetT4DV2(r, i, s, p) { void *f = objc_msgSend_stret;  ((void (*)(typeof(r)*, id, SEL, typeof(p)))f)(&r, i, s, p); }
#else
    #define GetT1DV(r, i, s) { void *f = objc_msgSend;        r = ((typeof(r) (*)(id, SEL))f)(i, s); }
    #define GetT2DV(r, i, s) { void *f = objc_msgSend;        r = ((typeof(r) (*)(id, SEL))f)(i, s); }
    #define GetT4DV(r, i, s) { void *f = objc_msgSend_stret;      ((void (*)(typeof(r)*, id, SEL))f)(&r, i, s); }
    #define GetT4DV2(r, i, s, p) { void *f = objc_msgSend_stret;  ((void (*)(typeof(r)*, id, SEL, typeof(p)))f)(&r, i, s, p); }
#endif

/// NSString creation macro
#define UTF8(s) stringWithUTF8String_(NSString, s)



static const char *StringObjCClasses[] = {STRING_OBJC_CLASSES, 0};
static id LoadedObjCClasses[countof(StringObjCClasses)] = {};

static const char *StringObjCSelectors[] = {STRING_OBJC_SELECTORS, 0};
static SEL LoadedObjCSelectors[countof(StringObjCSelectors)] = {};



/// overloaded method for a subclass
typedef struct _OMSC {
    SEL name;
    void *func;
} OMSC;



static id Subclass(id base, char *name, char *flds[], OMSC *mths) {
    Class retn = objc_allocateClassPair((Class)base, name, 0);
    long iter;

    iter = -1;
    /// adding fields
    while (flds[++iter])
        class_addIvar(retn, flds[iter],
                      sizeof(id), (sizeof(id) >= 8)? 3 : 2, 0);
    iter = -1;
    /// overloading methods
    while (mths[++iter].func)
        class_addMethod(retn, mths[iter].name, mths[iter].func, 0);

    objc_registerClassPair(retn);
    return (id)retn;
}



static void LoadObjC() {
    long iter;

    if (!*LoadedObjCClasses) {
        iter = -1;
        while (StringObjCClasses[++iter])
            LoadedObjCClasses[iter] =
                objc_getClass(StringObjCClasses[iter]);
        iter = -1;
        while (StringObjCSelectors[++iter])
            LoadedObjCSelectors[iter] =
                sel_registerName(StringObjCSelectors[iter]);
    }
}
