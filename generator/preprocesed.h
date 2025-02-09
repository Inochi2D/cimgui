
// dear imgui, v1.91.8
// (headers)

// Help:
// - See links below.
// - Call and read ImGui::ShowDemoWindow() in imgui_demo.cpp. All applications in examples/ are doing that.
// - Read top of imgui.cpp for more details, links and comments.
// - Add '#define IMGUI_DEFINE_MATH_OPERATORS' before including this file (or in imconfig.h) to access courtesy maths operators for ImVec2 and ImVec4.

// Resources:
// - FAQ ........................ https://dearimgui.com/faq (in repository as docs/FAQ.md)
// - Homepage ................... https://github.com/ocornut/imgui
// - Releases & changelog ....... https://github.com/ocornut/imgui/releases
// - Gallery .................... https://github.com/ocornut/imgui/issues?q=label%3Agallery (please post your screenshots/video there!)
// - Wiki ....................... https://github.com/ocornut/imgui/wiki (lots of good stuff there)
//   - Getting Started            https://github.com/ocornut/imgui/wiki/Getting-Started (how to integrate in an existing app by adding ~25 lines of code)
//   - Third-party Extensions     https://github.com/ocornut/imgui/wiki/Useful-Extensions (ImPlot & many more)
//   - Bindings/Backends          https://github.com/ocornut/imgui/wiki/Bindings (language bindings, backends for various tech/engines)
//   - Glossary                   https://github.com/ocornut/imgui/wiki/Glossary
//   - Debug Tools                https://github.com/ocornut/imgui/wiki/Debug-Tools
//   - Software using Dear ImGui  https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui
// - Issues & support ........... https://github.com/ocornut/imgui/issues
// - Test Engine & Automation ... https://github.com/ocornut/imgui_test_engine (test suite, test engine to automate your apps)

// For first-time users having issues compiling/linking/running/loading fonts:
// please post in https://github.com/ocornut/imgui/discussions if you cannot find a solution in resources above.
// Everything else should be asked in 'Issues'! We are building a database of cross-linked knowledge there.

// Library Version
// (Integer encoded as XYYZZ for use in #if preprocessor conditionals, e.g. '#if IMGUI_VERSION_NUM >= 12345')






/*

Index of this file:
// [SECTION] Header mess
// [SECTION] Forward declarations and basic types
// [SECTION] Dear ImGui end-user API functions
// [SECTION] Flags & Enumerations
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
// [SECTION] Helpers: Debug log, Memory allocations macros, ImVector<>
// [SECTION] ImGuiStyle
// [SECTION] ImGuiIO
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiWindowClass, ImGuiPayload)
// [SECTION] Helpers (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, Math Operators, ImColor)
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiMultiSelectIO, ImGuiSelectionRequest, ImGuiSelectionBasicStorage, ImGuiSelectionExternalStorage)
// [SECTION] Drawing API (ImDrawCallback, ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawFlags, ImDrawListFlags, ImDrawList, ImDrawData)
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontGlyphRangesBuilder, ImFontAtlasFlags, ImFontAtlas, ImFont)
// [SECTION] Viewports (ImGuiViewportFlags, ImGuiViewport)
// [SECTION] ImGuiPlatformIO + other Platform Dependent Interfaces (ImGuiPlatformMonitor, ImGuiPlatformImeData)
// [SECTION] Obsolete functions and types

*/


// Configuration file with compile-time options
// (edit imconfig.h or '#define IMGUI_USER_CONFIG "myfilename.h" from your build system)






//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

// Includes

// Define attributes of all API symbols declarations (e.g. for DLL under Windows)
// IMGUI_API is used for core imgui functions, IMGUI_IMPL_API is used for the default backends files (imgui_impl_xxx.h)
// Using dear imgui via a shared library is not recommended: we don't guarantee backward nor forward ABI compatibility + this is a call-heavy library and function call overhead adds up.







// Helper Macros





// Check that version and structures layouts are matching between compiled imgui code and caller. Read comments above DebugCheckVersionAndDataLayout() for details.


// Helper Macros - IM_FMTARGS, IM_FMTLIST: Apply printf-style warnings to our formatting functions.
// (MSVC provides an equivalent mechanism via SAL Annotations but it would require the macros in a different
//  location. e.g. #include <sal.h> + void myprintf(_Printf_format_string_ const char* format, ...))








// Disable some of MSVC most aggressive Debug runtime checks in function header/footer (used in some simple/low-level functions)






// Warnings


















//-----------------------------------------------------------------------------
// [SECTION] Forward declarations and basic types
//-----------------------------------------------------------------------------

// Scalar data types
typedef unsigned int        ImGuiID;// A unique ID used by widgets (typically the result of hashing a stack of string)
typedef signed char         ImS8;   // 8-bit signed integer
typedef unsigned char       ImU8;   // 8-bit unsigned integer
typedef signed short        ImS16;  // 16-bit signed integer
typedef unsigned short      ImU16;  // 16-bit unsigned integer
typedef signed int          ImS32;  // 32-bit signed integer == int
typedef unsigned int        ImU32;  // 32-bit unsigned integer (often used to store packed colors)
typedef signed   long long  ImS64;  // 64-bit signed integer
typedef unsigned long long  ImU64;  // 64-bit unsigned integer

// Forward declarations: ImDrawList, ImFontAtlas layer
struct ImDrawChannel;               // Temporary storage to output draw commands out of order, used by ImDrawListSplitter and ImDrawList::ChannelsSplit()
struct ImDrawCmd;                   // A single draw command within a parent ImDrawList (generally maps to 1 GPU draw call, unless it is a callback)
struct ImDrawData;                  // All draw command lists required to render the frame + pos/size coordinates to use for the projection matrix.
struct ImDrawList;                  // A single draw command list (generally one per window, conceptually you may see this as a dynamic "mesh" builder)
struct ImDrawListSharedData;        // Data shared among multiple draw lists (typically owned by parent ImGui context, but you may create one yourself)
struct ImDrawListSplitter;          // Helper to split a draw list into different layers which can be drawn into out of order, then flattened back.
struct ImDrawVert;                  // A single vertex (pos + uv + col = 20 bytes by default. Override layout with IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT)
struct ImFont;                      // Runtime data for a single font within a parent ImFontAtlas
struct ImFontAtlas;                 // Runtime data for multiple fonts, bake multiple fonts into a single texture, TTF/OTF font loader
struct ImFontBuilderIO;             // Opaque interface to a font builder (stb_truetype or FreeType).
struct ImFontConfig;                // Configuration data when adding a font or merging fonts
struct ImFontGlyph;                 // A single font glyph (code point + coordinates within in ImFontAtlas + offset)
struct ImFontGlyphRangesBuilder;    // Helper to build glyph ranges from text/string data
struct ImColor;                     // Helper functions to create a color that can be converted to either u32 or float4 (*OBSOLETE* please avoid using)

// Forward declarations: ImGui layer
struct ImGuiContext;                // Dear ImGui context (opaque structure, unless including imgui_internal.h)
struct ImGuiIO;                     // Main configuration and I/O between your application and ImGui (also see: ImGuiPlatformIO)
struct ImGuiInputTextCallbackData;  // Shared state of InputText() when using custom ImGuiInputTextCallback (rare/advanced use)
struct ImGuiKeyData;                // Storage for ImGuiIO and IsKeyDown(), IsKeyPressed() etc functions.
struct ImGuiListClipper;            // Helper to manually clip large list of items
struct ImGuiMultiSelectIO;          // Structure to interact with a BeginMultiSelect()/EndMultiSelect() block
struct ImGuiOnceUponAFrame;         // Helper for running a block of code not more than once a frame
struct ImGuiPayload;                // User data payload for drag and drop operations
struct ImGuiPlatformIO;             // Interface between platform/renderer backends and ImGui (e.g. Clipboard, IME, Multi-Viewport support). Extends ImGuiIO.
struct ImGuiPlatformImeData;        // Platform IME data for io.PlatformSetImeDataFn() function.
struct ImGuiPlatformMonitor;        // Multi-viewport support: user-provided bounds for each connected monitor/display. Used when positioning popups and tooltips to avoid them straddling monitors
struct ImGuiSelectionBasicStorage;  // Optional helper to store multi-selection state + apply multi-selection requests.
struct ImGuiSelectionExternalStorage;//Optional helper to apply multi-selection requests to existing randomly accessible storage.
struct ImGuiSelectionRequest;       // A selection request (stored in ImGuiMultiSelectIO)
struct ImGuiSizeCallbackData;       // Callback data when using SetNextWindowSizeConstraints() (rare/advanced use)
struct ImGuiStorage;                // Helper for key->value storage (container sorted by key)
struct ImGuiStoragePair;            // Helper for key->value storage (pair)
struct ImGuiStyle;                  // Runtime data for styling/colors
struct ImGuiTableSortSpecs;         // Sorting specifications for a table (often handling sort specs for a single column, occasionally more)
struct ImGuiTableColumnSortSpecs;   // Sorting specification for one column of a table
struct ImGuiTextBuffer;             // Helper to hold and append into a text buffer (~string builder)
struct ImGuiTextFilter;             // Helper to parse and apply text filters (e.g. "aaaaa[,bbbbb][,ccccc]")
struct ImGuiViewport;               // A Platform Window (always 1 unless multi-viewport are enabled. One per platform window to output to). In the future may represent Platform Monitor
struct ImGuiWindowClass;            // Window class (rare/advanced uses: provide hints to the platform backend via altered viewport flags and parent/child info)

// Enumerations
// - We don't use strongly typed enums much because they add constraints (can't extend in private code, can't store typed in bit fields, extra casting on iteration)
// - Tip: Use your programming IDE navigation facilities on the names in the _central column_ below to find the actual flags/enum lists!
//   - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
//   - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
//   - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
enum ImGuiDir : int;                // -> enum ImGuiDir              // Enum: A cardinal direction (Left, Right, Up, Down)
enum ImGuiKey : int;                // -> enum ImGuiKey              // Enum: A key identifier (ImGuiKey_XXX or ImGuiMod_XXX value)
enum ImGuiMouseSource : int;        // -> enum ImGuiMouseSource      // Enum; A mouse input source identifier (Mouse, TouchScreen, Pen)
enum ImGuiSortDirection : ImU8;     // -> enum ImGuiSortDirection    // Enum: A sorting direction (ascending or descending)
typedef int ImGuiCol;               // -> enum ImGuiCol_             // Enum: A color identifier for styling
typedef int ImGuiCond;              // -> enum ImGuiCond_            // Enum: A condition for many Set*() functions
typedef int ImGuiDataType;          // -> enum ImGuiDataType_        // Enum: A primary data type
typedef int ImGuiMouseButton;       // -> enum ImGuiMouseButton_     // Enum: A mouse button identifier (0=left, 1=right, 2=middle)
typedef int ImGuiMouseCursor;       // -> enum ImGuiMouseCursor_     // Enum: A mouse cursor shape
typedef int ImGuiStyleVar;          // -> enum ImGuiStyleVar_        // Enum: A variable identifier for styling
typedef int ImGuiTableBgTarget;     // -> enum ImGuiTableBgTarget_   // Enum: A color target for TableSetBgColor()

// Flags (declared as int to allow using as flags without overhead, and to not pollute the top of this file)
// - Tip: Use your programming IDE navigation facilities on the names in the _central column_ below to find the actual flags/enum lists!
//   - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
//   - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
//   - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
typedef int ImDrawFlags;            // -> enum ImDrawFlags_          // Flags: for ImDrawList functions
typedef int ImDrawListFlags;        // -> enum ImDrawListFlags_      // Flags: for ImDrawList instance
typedef int ImFontAtlasFlags;       // -> enum ImFontAtlasFlags_     // Flags: for ImFontAtlas build
typedef int ImGuiBackendFlags;      // -> enum ImGuiBackendFlags_    // Flags: for io.BackendFlags
typedef int ImGuiButtonFlags;       // -> enum ImGuiButtonFlags_     // Flags: for InvisibleButton()
typedef int ImGuiChildFlags;        // -> enum ImGuiChildFlags_      // Flags: for BeginChild()
typedef int ImGuiColorEditFlags;    // -> enum ImGuiColorEditFlags_  // Flags: for ColorEdit4(), ColorPicker4() etc.
typedef int ImGuiConfigFlags;       // -> enum ImGuiConfigFlags_     // Flags: for io.ConfigFlags
typedef int ImGuiComboFlags;        // -> enum ImGuiComboFlags_      // Flags: for BeginCombo()
typedef int ImGuiDockNodeFlags;     // -> enum ImGuiDockNodeFlags_   // Flags: for DockSpace()
typedef int ImGuiDragDropFlags;     // -> enum ImGuiDragDropFlags_   // Flags: for BeginDragDropSource(), AcceptDragDropPayload()
typedef int ImGuiFocusedFlags;      // -> enum ImGuiFocusedFlags_    // Flags: for IsWindowFocused()
typedef int ImGuiHoveredFlags;      // -> enum ImGuiHoveredFlags_    // Flags: for IsItemHovered(), IsWindowHovered() etc.
typedef int ImGuiInputFlags;        // -> enum ImGuiInputFlags_      // Flags: for Shortcut(), SetNextItemShortcut()
typedef int ImGuiInputTextFlags;    // -> enum ImGuiInputTextFlags_  // Flags: for InputText(), InputTextMultiline()
typedef int ImGuiItemFlags;         // -> enum ImGuiItemFlags_       // Flags: for PushItemFlag(), shared by all items
typedef int ImGuiKeyChord;          // -> ImGuiKey | ImGuiMod_XXX    // Flags: for IsKeyChordPressed(), Shortcut() etc. an ImGuiKey optionally OR-ed with one or more ImGuiMod_XXX values.
typedef int ImGuiPopupFlags;        // -> enum ImGuiPopupFlags_      // Flags: for OpenPopup*(), BeginPopupContext*(), IsPopupOpen()
typedef int ImGuiMultiSelectFlags;  // -> enum ImGuiMultiSelectFlags_// Flags: for BeginMultiSelect()
typedef int ImGuiSelectableFlags;   // -> enum ImGuiSelectableFlags_ // Flags: for Selectable()
typedef int ImGuiSliderFlags;       // -> enum ImGuiSliderFlags_     // Flags: for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
typedef int ImGuiTabBarFlags;       // -> enum ImGuiTabBarFlags_     // Flags: for BeginTabBar()
typedef int ImGuiTabItemFlags;      // -> enum ImGuiTabItemFlags_    // Flags: for BeginTabItem()
typedef int ImGuiTableFlags;        // -> enum ImGuiTableFlags_      // Flags: For BeginTable()
typedef int ImGuiTableColumnFlags;  // -> enum ImGuiTableColumnFlags_// Flags: For TableSetupColumn()
typedef int ImGuiTableRowFlags;     // -> enum ImGuiTableRowFlags_   // Flags: For TableNextRow()
typedef int ImGuiTreeNodeFlags;     // -> enum ImGuiTreeNodeFlags_   // Flags: for TreeNode(), TreeNodeEx(), CollapsingHeader()
typedef int ImGuiViewportFlags;     // -> enum ImGuiViewportFlags_   // Flags: for ImGuiViewport
typedef int ImGuiWindowFlags;       // -> enum ImGuiWindowFlags_     // Flags: for Begin(), BeginChild()

// ImTexture: user data for renderer backend to identify a texture [Compile-time configurable type]
// - To use something else than an opaque void* pointer: override with e.g. '#define ImTextureID MyTextureType*' in your imconfig.h file.
// - This can be whatever to you want it to be! read the FAQ about ImTextureID for details.
// - You can make this a structure with various constructors if you need. You will have to implement ==/!= operators.
// - (note: before v1.91.4 (2024/10/08) the default type for ImTextureID was void*. Use intermediary intptr_t cast and read FAQ if you have casting warnings)

typedef ImU64 ImTextureID;          // Default: store a pointer or an integer fitting in a pointer (most renderer backends are ok with that)

// ImDrawIdx: vertex index. [Compile-time configurable type]
// - To use 16-bit indices + allow large meshes: backend need to set 'io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset' and handle ImDrawCmd::VtxOffset (recommended).
// - To use 32-bit indices: override with '#define ImDrawIdx unsigned int' in your imconfig.h file.

typedef unsigned short ImDrawIdx;   // Default: 16-bit (for maximum compatibility with renderer backends)

// Character types
// (we generally use UTF-8 encoded string in the API. This is storage specifically for a decoded character used for keyboard input and display)
typedef unsigned int ImWchar32;     // A single decoded U32 character/code point. We encode them as multi bytes UTF-8 when used in strings.
typedef unsigned short ImWchar16;   // A single decoded U16 character/code point. We encode them as multi bytes UTF-8 when used in strings.



typedef ImWchar16 ImWchar;

// Multi-Selection item index or identifier when using BeginMultiSelect()
// - Used by SetNextItemSelectionUserData() + and inside ImGuiMultiSelectIO structure.
// - Most users are likely to use this store an item INDEX but this may be used to store a POINTER/ID as well. Read comments near ImGuiMultiSelectIO for details.
typedef ImS64 ImGuiSelectionUserData;

// Callback and functions types
typedef int     (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData* data);    // Callback function for ImGui::InputText()
typedef void    (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);              // Callback function for ImGui::SetNextWindowSizeConstraints()
typedef void*   (*ImGuiMemAllocFunc)(size_t sz, void* user_data);               // Function signature for ImGui::SetAllocatorFunctions()
typedef void    (*ImGuiMemFreeFunc)(void* ptr, void* user_data);                // Function signature for ImGui::SetAllocatorFunctions()

// ImVec2: 2D vector used to store positions, sizes etc. [Compile-time configurable type]
// - This is a frequently used type in the API. Consider using IM_VEC2_CLASS_EXTRA to create implicit cast from/to our preferred type.
// - Add '#define IMGUI_DEFINE_MATH_OPERATORS' before including this file (or in imconfig.h) to access courtesy maths operators for ImVec2 and ImVec4.

struct ImVec2
{
    float                                   x, y;
    constexpr ImVec2()                      : x(0.0f), y(0.0f) { }
    constexpr ImVec2(float _x, float _y)    : x(_x), y(_y) { }
    float& operator[] (size_t idx)          { (void)( (!!(idx == 0 || idx == 1)) || (_wassert(L"idx == 0 || idx == 1", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(304)), 0) ); return ((float*)(void*)(char*)this)[idx]; } // We very rarely use this [] operator, so the assert overhead is fine.
    float  operator[] (size_t idx) const    { (void)( (!!(idx == 0 || idx == 1)) || (_wassert(L"idx == 0 || idx == 1", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(305)), 0) ); return ((const float*)(const void*)(const char*)this)[idx]; }



};

// ImVec4: 4D vector used to store clipping rectangles, colors etc. [Compile-time configurable type]
struct ImVec4
{
    float                                                     x, y, z, w;
    constexpr ImVec4()                                        : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    constexpr ImVec4(float _x, float _y, float _z, float _w)  : x(_x), y(_y), z(_z), w(_w) { }



};


//-----------------------------------------------------------------------------
// [SECTION] Dear ImGui end-user API functions
// (Note that ImGui:: being a namespace, you can add extra ImGui:: functions in your own separate file. Please don't modify imgui source files!)
//-----------------------------------------------------------------------------

namespace ImGui
{
    // Context creation and access
    // - Each context create its own ImFontAtlas by default. You may instance one yourself and pass it to CreateContext() to share a font atlas between contexts.
    // - DLL users: heaps and globals are not shared across DLL boundaries! You will need to call SetCurrentContext() + SetAllocatorFunctions()
    //   for each static/DLL boundary you are calling from. Read "Context and Memory Allocators" section of imgui.cpp for details.
     ImGuiContext* CreateContext(ImFontAtlas* shared_font_atlas = ((void *)0));
     void          DestroyContext(ImGuiContext* ctx = ((void *)0));   // NULL = destroy current context
     ImGuiContext* GetCurrentContext();
     void          SetCurrentContext(ImGuiContext* ctx);

    // Main
     ImGuiIO&      GetIO();                                    // access the ImGuiIO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)
     ImGuiPlatformIO& GetPlatformIO();                         // access the ImGuiPlatformIO structure (mostly hooks/functions to connect to platform/renderer and OS Clipboard, IME etc.)
     ImGuiStyle&   GetStyle();                                 // access the Style structure (colors, sizes). Always use PushStyleColor(), PushStyleVar() to modify style mid-frame!
     void          NewFrame();                                 // start a new Dear ImGui frame, you can submit any command from this point until Render()/EndFrame().
     void          EndFrame();                                 // ends the Dear ImGui frame. automatically called by Render(). If you don't need to render data (skipping rendering) you may call EndFrame() without Render()... but you'll have wasted CPU already! If you don't need to render, better to not create any windows and not call NewFrame() at all!
     void          Render();                                   // ends the Dear ImGui frame, finalize the draw data. You can then get call GetDrawData().
     ImDrawData*   GetDrawData();                              // valid after Render() and until the next call to NewFrame(). this is what you have to render.

    // Demo, Debug, Information
     void          ShowDemoWindow(bool* p_open = ((void *)0));        // create Demo window. demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!
     void          ShowMetricsWindow(bool* p_open = ((void *)0));     // create Metrics/Debugger window. display Dear ImGui internals: windows, draw commands, various internal state, etc.
     void          ShowDebugLogWindow(bool* p_open = ((void *)0));    // create Debug Log window. display a simplified log of important dear imgui events.
     void          ShowIDStackToolWindow(bool* p_open = ((void *)0)); // create Stack Tool window. hover items with mouse to query information about the source of their unique ID.
     void          ShowAboutWindow(bool* p_open = ((void *)0));       // create About window. display Dear ImGui version, credits and build/system information.
     void          ShowStyleEditor(ImGuiStyle* ref = ((void *)0));    // add style editor block (not a window). you can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it uses the default style)
     bool          ShowStyleSelector(const char* label);       // add style selector block (not a window), essentially a combo listing the default styles.
     void          ShowFontSelector(const char* label);        // add font selector block (not a window), essentially a combo listing the loaded fonts.
     void          ShowUserGuide();                            // add basic help/info block (not a window): how to manipulate ImGui as an end-user (mouse/keyboard controls).
     const char*   GetVersion();                               // get the compiled version string e.g. "1.80 WIP" (essentially the value for IMGUI_VERSION from the compiled version of imgui.cpp)

    // Styles
     void          StyleColorsDark(ImGuiStyle* dst = ((void *)0));    // new, recommended style (default)
     void          StyleColorsLight(ImGuiStyle* dst = ((void *)0));   // best used with borders and a custom, thicker font
     void          StyleColorsClassic(ImGuiStyle* dst = ((void *)0)); // classic imgui style

    // Windows
    // - Begin() = push window to the stack and start appending to it. End() = pop window from the stack.
    // - Passing 'bool* p_open != NULL' shows a window-closing widget in the upper-right corner of the window,
    //   which clicking will set the boolean to false when clicked.
    // - You may append multiple times to the same window during the same frame by calling Begin()/End() pairs multiple times.
    //   Some information such as 'flags' or 'p_open' will only be considered by the first call to Begin().
    // - Begin() return false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
    //   anything to the window. Always call a matching End() for each Begin() call, regardless of its return value!
    //   [Important: due to legacy reason, Begin/End and BeginChild/EndChild are inconsistent with all other functions
    //    such as BeginMenu/EndMenu, BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding
    //    BeginXXX function returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
    // - Note that the bottom of window stack always contains a window called "Debug".
     bool          Begin(const char* name, bool* p_open = ((void *)0), ImGuiWindowFlags flags = 0);
     void          End();

    // Child Windows
    // - Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window. Child windows can embed their own child.
    // - Before 1.90 (November 2023), the "ImGuiChildFlags child_flags = 0" parameter was "bool border = false".
    //   This API is backward compatible with old code, as we guarantee that ImGuiChildFlags_Borders == true.
    //   Consider updating your old code:
    //      BeginChild("Name", size, false)   -> Begin("Name", size, 0); or Begin("Name", size, ImGuiChildFlags_None);
    //      BeginChild("Name", size, true)    -> Begin("Name", size, ImGuiChildFlags_Borders);
    // - Manual sizing (each axis can use a different setting e.g. ImVec2(0.0f, 400.0f)):
    //     == 0.0f: use remaining parent window size for this axis.
    //      > 0.0f: use specified size for this axis.
    //      < 0.0f: right/bottom-align to specified distance from available content boundaries.
    // - Specifying ImGuiChildFlags_AutoResizeX or ImGuiChildFlags_AutoResizeY makes the sizing automatic based on child contents.
    //   Combining both ImGuiChildFlags_AutoResizeX _and_ ImGuiChildFlags_AutoResizeY defeats purpose of a scrolling region and is NOT recommended.
    // - BeginChild() returns false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
    //   anything to the window. Always call a matching EndChild() for each BeginChild() call, regardless of its return value.
    //   [Important: due to legacy reason, Begin/End and BeginChild/EndChild are inconsistent with all other functions
    //    such as BeginMenu/EndMenu, BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding
    //    BeginXXX function returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
     bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
     bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
     void          EndChild();

    // Windows Utilities
    // - 'current window' = the window we are appending into while inside a Begin()/End() block. 'next window' = next window we will Begin() into.
     bool          IsWindowAppearing();
     bool          IsWindowCollapsed();
     bool          IsWindowFocused(ImGuiFocusedFlags flags=0); // is current window focused? or its root/child, depending on flags. see flags for options.
     bool          IsWindowHovered(ImGuiHoveredFlags flags=0); // is current window hovered and hoverable (e.g. not blocked by a popup/modal)? See ImGuiHoveredFlags_ for options. IMPORTANT: If you are trying to check whether your mouse should be dispatched to Dear ImGui or to your underlying app, you should not use this function! Use the 'io.WantCaptureMouse' boolean for that! Refer to FAQ entry "How can I tell whether to dispatch mouse/keyboard to Dear ImGui or my application?" for details.
     ImDrawList*   GetWindowDrawList();                        // get draw list associated to the current window, to append your own drawing primitives
     float         GetWindowDpiScale();                        // get DPI scale currently associated to the current window's viewport.
     ImVec2        GetWindowPos();                             // get current window position in screen space (IT IS UNLIKELY YOU EVER NEED TO USE THIS. Consider always using GetCursorScreenPos() and GetContentRegionAvail() instead)
     ImVec2        GetWindowSize();                            // get current window size (IT IS UNLIKELY YOU EVER NEED TO USE THIS. Consider always using GetCursorScreenPos() and GetContentRegionAvail() instead)
     float         GetWindowWidth();                           // get current window width (IT IS UNLIKELY YOU EVER NEED TO USE THIS). Shortcut for GetWindowSize().x.
     float         GetWindowHeight();                          // get current window height (IT IS UNLIKELY YOU EVER NEED TO USE THIS). Shortcut for GetWindowSize().y.
     ImGuiViewport*GetWindowViewport();                        // get viewport currently associated to the current window.

    // Window manipulation
    // - Prefer using SetNextXXX functions (before Begin) rather that SetXXX functions (after Begin).
     void          SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0)); // set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.
     void          SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);                  // set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()
     void          SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback = ((void *)0), void* custom_callback_data = ((void *)0)); // set next window size limits. use 0.0f or FLT_MAX if you don't want limits. Use -1 for both min and max of same axis to preserve current size (which itself is a constraint). Use callback to apply non-trivial programmatic constraints.
     void          SetNextWindowContentSize(const ImVec2& size);                               // set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to 0.0f to leave it automatic. call before Begin()
     void          SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);                 // set next window collapsed state. call before Begin()
     void          SetNextWindowFocus();                                                       // set next window to be focused / top-most. call before Begin()
     void          SetNextWindowScroll(const ImVec2& scroll);                                  // set next window scrolling value (use < 0.0f to not affect a given axis).
     void          SetNextWindowBgAlpha(float alpha);                                          // set next window background color alpha. helper to easily override the Alpha component of ImGuiCol_WindowBg/ChildBg/PopupBg. you may also use ImGuiWindowFlags_NoBackground.
     void          SetNextWindowViewport(ImGuiID viewport_id);                                 // set next window viewport
     void          SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);                        // (not recommended) set current window position - call within Begin()/End(). prefer using SetNextWindowPos(), as this may incur tearing and side-effects.
     void          SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);                      // (not recommended) set current window size - call within Begin()/End(). set to ImVec2(0, 0) to force an auto-fit. prefer using SetNextWindowSize(), as this may incur tearing and minor side-effects.
     void          SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);                     // (not recommended) set current window collapsed state. prefer using SetNextWindowCollapsed().
     void          SetWindowFocus();                                                           // (not recommended) set current window to be focused / top-most. prefer using SetNextWindowFocus().
     void          SetWindowFontScale(float scale);                                            // [OBSOLETE] set font scale. Adjust IO.FontGlobalScale if you want to scale all windows. This is an old API! For correct scaling, prefer to reload font + rebuild ImFontAtlas + call style.ScaleAllSizes().
     void          SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond = 0);      // set named window position.
     void          SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond = 0);    // set named window size. set axis to 0.0f to force an auto-fit on this axis.
     void          SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond = 0);   // set named window collapsed state
     void          SetWindowFocus(const char* name);                                           // set named window to be focused / top-most. use NULL to remove focus.

    // Windows Scrolling
    // - Any change of Scroll will be applied at the beginning of next frame in the first call to Begin().
    // - You may instead use SetNextWindowScroll() prior to calling Begin() to avoid this delay, as an alternative to using SetScrollX()/SetScrollY().
     float         GetScrollX();                                                   // get scrolling amount [0 .. GetScrollMaxX()]
     float         GetScrollY();                                                   // get scrolling amount [0 .. GetScrollMaxY()]
     void          SetScrollX(float scroll_x);                                     // set scrolling amount [0 .. GetScrollMaxX()]
     void          SetScrollY(float scroll_y);                                     // set scrolling amount [0 .. GetScrollMaxY()]
     float         GetScrollMaxX();                                                // get maximum scrolling amount ~~ ContentSize.x - WindowSize.x - DecorationsSize.x
     float         GetScrollMaxY();                                                // get maximum scrolling amount ~~ ContentSize.y - WindowSize.y - DecorationsSize.y
     void          SetScrollHereX(float center_x_ratio = 0.5f);                    // adjust scrolling amount to make current cursor position visible. center_x_ratio=0.0: left, 0.5: center, 1.0: right. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
     void          SetScrollHereY(float center_y_ratio = 0.5f);                    // adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
     void          SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);  // adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.
     void          SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);  // adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.

    // Parameters stacks (shared)
     void          PushFont(ImFont* font);                                         // use NULL as a shortcut to push default font
     void          PopFont();
     void          PushStyleColor(ImGuiCol idx, ImU32 col);                        // modify a style color. always use this if you modify the style after NewFrame().
     void          PushStyleColor(ImGuiCol idx, const ImVec4& col);
     void          PopStyleColor(int count = 1);
     void          PushStyleVar(ImGuiStyleVar idx, float val);                     // modify a style float variable. always use this if you modify the style after NewFrame()!
     void          PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);             // modify a style ImVec2 variable. "
     void          PushStyleVarX(ImGuiStyleVar idx, float val_x);                  // modify X component of a style ImVec2 variable. "
     void          PushStyleVarY(ImGuiStyleVar idx, float val_y);                  // modify Y component of a style ImVec2 variable. "
     void          PopStyleVar(int count = 1);
     void          PushItemFlag(ImGuiItemFlags option, bool enabled);              // modify specified shared item flag, e.g. PushItemFlag(ImGuiItemFlags_NoTabStop, true)
     void          PopItemFlag();

    // Parameters stacks (current window)
     void          PushItemWidth(float item_width);                                // push width of items for common large "item+label" widgets. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side).
     void          PopItemWidth();
     void          SetNextItemWidth(float item_width);                             // set width of the _next_ common large "item+label" widget. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)
     float         CalcItemWidth();                                                // width of item given pushed settings and current cursor position. NOT necessarily the width of last item unlike most 'Item' functions.
     void          PushTextWrapPos(float wrap_local_pos_x = 0.0f);                 // push word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space
     void          PopTextWrapPos();

    // Style read access
    // - Use the ShowStyleEditor() function to interactively see/edit the colors.
     ImFont*       GetFont();                                                      // get current font
     float         GetFontSize();                                                  // get current font size (= height in pixels) of current font with current scale applied
     ImVec2        GetFontTexUvWhitePixel();                                       // get UV coordinate for a white pixel, useful to draw custom shapes via the ImDrawList API
     ImU32         GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);              // retrieve given style color with style alpha applied and optional extra alpha multiplier, packed as a 32-bit value suitable for ImDrawList
     ImU32         GetColorU32(const ImVec4& col);                                 // retrieve given color with style alpha applied, packed as a 32-bit value suitable for ImDrawList
     ImU32         GetColorU32(ImU32 col, float alpha_mul = 1.0f);                 // retrieve given color with style alpha applied, packed as a 32-bit value suitable for ImDrawList
     const ImVec4& GetStyleColorVec4(ImGuiCol idx);                                // retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in.

    // Layout cursor positioning
    // - By "cursor" we mean the current output position.
    // - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
    // - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceding widget.
    // - YOU CAN DO 99% OF WHAT YOU NEED WITH ONLY GetCursorScreenPos() and GetContentRegionAvail().
    // - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
    //    - Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions. -> this is the preferred way forward.
    //    - Window-local coordinates:   SameLine(offset), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), PushTextWrapPos()
    //    - Window-local coordinates:   GetContentRegionMax(), GetWindowContentRegionMin(), GetWindowContentRegionMax() --> all obsoleted. YOU DON'T NEED THEM.
    // - GetCursorScreenPos() = GetCursorPos() + GetWindowPos(). GetWindowPos() is almost only ever useful to convert from window-local to absolute coordinates. Try not to use it.
     ImVec2        GetCursorScreenPos();                                           // cursor position, absolute coordinates. THIS IS YOUR BEST FRIEND (prefer using this rather than GetCursorPos(), also more useful to work with ImDrawList API).
     void          SetCursorScreenPos(const ImVec2& pos);                          // cursor position, absolute coordinates. THIS IS YOUR BEST FRIEND.
     ImVec2        GetContentRegionAvail();                                        // available space from current position. THIS IS YOUR BEST FRIEND.
     ImVec2        GetCursorPos();                                                 // [window-local] cursor position in window-local coordinates. This is not your best friend.
     float         GetCursorPosX();                                                // [window-local] "
     float         GetCursorPosY();                                                // [window-local] "
     void          SetCursorPos(const ImVec2& local_pos);                          // [window-local] "
     void          SetCursorPosX(float local_x);                                   // [window-local] "
     void          SetCursorPosY(float local_y);                                   // [window-local] "
     ImVec2        GetCursorStartPos();                                            // [window-local] initial cursor position, in window-local coordinates. Call GetCursorScreenPos() after Begin() to get the absolute coordinates version.

    // Other layout functions
     void          Separator();                                                    // separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
     void          SameLine(float offset_from_start_x=0.0f, float spacing=-1.0f);  // call between widgets or groups to layout them horizontally. X position given in window coordinates.
     void          NewLine();                                                      // undo a SameLine() or force a new line when in a horizontal-layout context.
     void          Spacing();                                                      // add vertical spacing.
     void          Dummy(const ImVec2& size);                                      // add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into.
     void          Indent(float indent_w = 0.0f);                                  // move content position toward the right, by indent_w, or style.IndentSpacing if indent_w <= 0
     void          Unindent(float indent_w = 0.0f);                                // move content position back to the left, by indent_w, or style.IndentSpacing if indent_w <= 0
     void          BeginGroup();                                                   // lock horizontal starting position
     void          EndGroup();                                                     // unlock horizontal starting position + capture the whole group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
     void          AlignTextToFramePadding();                                      // vertically align upcoming text baseline to FramePadding.y so that it will align properly to regularly framed items (call if you have text on a line before a framed item)
     float         GetTextLineHeight();                                            // ~ FontSize
     float         GetTextLineHeightWithSpacing();                                 // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
     float         GetFrameHeight();                                               // ~ FontSize + style.FramePadding.y * 2
     float         GetFrameHeightWithSpacing();                                    // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)

    // ID stack/scopes
    // Read the FAQ (docs/FAQ.md or http://dearimgui.com/faq) for more details about how ID are handled in dear imgui.
    // - Those questions are answered and impacted by understanding of the ID stack system:
    //   - "Q: Why is my widget not reacting when I click on it?"
    //   - "Q: How can I have widgets with an empty label?"
    //   - "Q: How can I have multiple widgets with the same label?"
    // - Short version: ID are hashes of the entire ID stack. If you are creating widgets in a loop you most likely
    //   want to push a unique identifier (e.g. object pointer, loop index) to uniquely differentiate them.
    // - You can also use the "Label##foobar" syntax within widget label to distinguish them from each others.
    // - In this header file we use the "label"/"name" terminology to denote a string that will be displayed + used as an ID,
    //   whereas "str_id" denote a string that is only used as an ID and not normally displayed.
     void          PushID(const char* str_id);                                     // push string into the ID stack (will hash string).
     void          PushID(const char* str_id_begin, const char* str_id_end);       // push string into the ID stack (will hash string).
     void          PushID(const void* ptr_id);                                     // push pointer into the ID stack (will hash pointer).
     void          PushID(int int_id);                                             // push integer into the ID stack (will hash integer).
     void          PopID();                                                        // pop from the ID stack.
     ImGuiID       GetID(const char* str_id);                                      // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into ImGuiStorage yourself
     ImGuiID       GetID(const char* str_id_begin, const char* str_id_end);
     ImGuiID       GetID(const void* ptr_id);
     ImGuiID       GetID(int int_id);

    // Widgets: Text
     void          TextUnformatted(const char* text, const char* text_end = ((void *)0)); // raw text without formatting. Roughly equivalent to Text("%s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
     void          Text(const char* fmt, ...)                                      ; // formatted text
     void          TextV(const char* fmt, va_list args)                            ;
     void          TextColored(const ImVec4& col, const char* fmt, ...)            ; // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
     void          TextColoredV(const ImVec4& col, const char* fmt, va_list args)  ;
     void          TextDisabled(const char* fmt, ...)                              ; // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
     void          TextDisabledV(const char* fmt, va_list args)                    ;
     void          TextWrapped(const char* fmt, ...)                               ; // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
     void          TextWrappedV(const char* fmt, va_list args)                     ;
     void          LabelText(const char* label, const char* fmt, ...)              ; // display text+label aligned the same way as value+label widgets
     void          LabelTextV(const char* label, const char* fmt, va_list args)    ;
     void          BulletText(const char* fmt, ...)                                ; // shortcut for Bullet()+Text()
     void          BulletTextV(const char* fmt, va_list args)                      ;
     void          SeparatorText(const char* label);                               // currently: formatted text with an horizontal line

    // Widgets: Main
    // - Most widgets return true when the value has been changed or when pressed/selected
    // - You may also use one of the many IsItemXXX functions (e.g. IsItemActive, IsItemHovered, etc.) to query widget state.
     bool          Button(const char* label, const ImVec2& size = ImVec2(0, 0));   // button
     bool          SmallButton(const char* label);                                 // button with (FramePadding.y == 0) to easily embed within text
     bool          InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0); // flexible button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
     bool          ArrowButton(const char* str_id, ImGuiDir dir);                  // square button with an arrow shape
     bool          Checkbox(const char* label, bool* v);
     bool          CheckboxFlags(const char* label, int* flags, int flags_value);
     bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
     bool          RadioButton(const char* label, bool active);                    // use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }
     bool          RadioButton(const char* label, int* v, int v_button);           // shortcut to handle the above pattern when value is an integer
     void          ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-1.175494351e-38F, 0), const char* overlay = ((void *)0));
     void          Bullet();                                                       // draw a small circle + keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses
     bool          TextLink(const char* label);                                    // hyperlink text button, return true when clicked
     void          TextLinkOpenURL(const char* label, const char* url = ((void *)0));     // hyperlink text button, automatically open file/url when clicked

    // Widgets: Images
    // - Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
    // - 'uv0' and 'uv1' are texture coordinates. Read about them from the same link above.
    // - Note that Image() may add +2.0f to provided size if a border is visible, ImageButton() adds style.FramePadding*2.0f to provided size.
    // - ImageButton() draws a background based on regular Button() color + optionally an inner background if specified.
     void          Image(ImTextureID user_texture_id, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
     bool          ImageButton(const char* str_id, ImTextureID user_texture_id, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));

    // Widgets: Combo Box (Dropdown)
    // - The BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.
    // - The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose. This is analogous to how ListBox are created.
     bool          BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
     void          EndCombo(); // only call EndCombo() if BeginCombo() returns true!
     bool          Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
     bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
     bool          Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items = -1);

    // Widgets: Drag Sliders
    // - CTRL+Click on any drag box to turn them into an input box. Manually input values aren't clamped by default and can go off-bounds. Use ImGuiSliderFlags_AlwaysClamp to always clamp.
    // - For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every function, note that a 'float v[X]' function argument is the same as 'float* v',
    //   the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
    // - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
    // - Format string may also be set to NULL or use the default format ("%f" or "%d").
    // - Speed are per-pixel of mouse movement (v_speed=0.2f: mouse needs to move by 5 pixels to increase value by 1). For keyboard/gamepad navigation, minimum speed is Max(v_speed, minimum_step_at_given_precision).
    // - Use v_min < v_max to clamp edits to given limits. Note that CTRL+Click manual input can override those limits if ImGuiSliderFlags_AlwaysClamp is not used.
    // - Use v_max = FLT_MAX / INT_MAX etc to avoid clamping to a maximum, same with v_min = -FLT_MAX / INT_MIN to avoid clamping to a minimum.
    // - We use the same sets of flags for DragXXX() and SliderXXX() functions as the features are the same and it makes it easier to swap them.
    // - Legacy: Pre-1.78 there are DragXXX() function signatures that take a final `float power=1.0f' argument instead of the `ImGuiSliderFlags flags=0' argument.
    //   If you get a warning converting a float to ImGuiSliderFlags, read https://github.com/ocornut/imgui/issues/3361
     bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);     // If v_min >= v_max we have no bound
     bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = ((void *)0), ImGuiSliderFlags flags = 0);
     bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);  // If v_min >= v_max we have no bound
     bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = ((void *)0), ImGuiSliderFlags flags = 0);
     bool          DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min = ((void *)0), const void* p_max = ((void *)0), const char* format = ((void *)0), ImGuiSliderFlags flags = 0);
     bool          DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min = ((void *)0), const void* p_max = ((void *)0), const char* format = ((void *)0), ImGuiSliderFlags flags = 0);

    // Widgets: Regular Sliders
    // - CTRL+Click on any slider to turn them into an input box. Manually input values aren't clamped by default and can go off-bounds. Use ImGuiSliderFlags_AlwaysClamp to always clamp.
    // - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
    // - Format string may also be set to NULL or use the default format ("%f" or "%d").
    // - Legacy: Pre-1.78 there are SliderXXX() function signatures that take a final `float power=1.0f' argument instead of the `ImGuiSliderFlags flags=0' argument.
    //   If you get a warning converting a float to ImGuiSliderFlags, read https://github.com/ocornut/imgui/issues/3361
     bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display.
     bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
     bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = ((void *)0), ImGuiSliderFlags flags = 0);
     bool          SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = ((void *)0), ImGuiSliderFlags flags = 0);
     bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
     bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
     bool          VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = ((void *)0), ImGuiSliderFlags flags = 0);

    // Widgets: Input with Keyboard
    // - If you want to use InputText() with std::string or any custom dynamic string type, see misc/cpp/imgui_stdlib.h and comments in imgui_demo.cpp.
    // - Most of the ImGuiInputTextFlags flags are only useful for InputText() and not for InputFloatX, InputIntX, InputDouble etc.
     bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = ((void *)0), void* user_data = ((void *)0));
     bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = ((void *)0), void* user_data = ((void *)0));
     bool          InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = ((void *)0), void* user_data = ((void *)0));
     bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
     bool          InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
     bool          InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
     bool          InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
     bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
     bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
     bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
     bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
     bool          InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
     bool          InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = ((void *)0), const void* p_step_fast = ((void *)0), const char* format = ((void *)0), ImGuiInputTextFlags flags = 0);
     bool          InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = ((void *)0), const void* p_step_fast = ((void *)0), const char* format = ((void *)0), ImGuiInputTextFlags flags = 0);

    // Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
    // - Note that in C++ a 'float v[X]' function argument is the _same_ as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible.
    // - You can pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
     bool          ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
     bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
     bool          ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
     bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = ((void *)0));
     bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // display a color square/button, hover for details, return true when pressed.
     void          SetColorEditOptions(ImGuiColorEditFlags flags);                     // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.

    // Widgets: Trees
    // - TreeNode functions return true when the node is open, in which case you need to also call TreePop() when you are finished displaying the tree node contents.
     bool          TreeNode(const char* label);
     bool          TreeNode(const char* str_id, const char* fmt, ...) ;   // helper variation to easily decorelate the id from the displayed string. Read the FAQ about why and how to use ID. to align arbitrary text at the same level as a TreeNode() you can use Bullet().
     bool          TreeNode(const void* ptr_id, const char* fmt, ...) ;   // "
     bool          TreeNodeV(const char* str_id, const char* fmt, va_list args) ;
     bool          TreeNodeV(const void* ptr_id, const char* fmt, va_list args) ;
     bool          TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
     bool          TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) ;
     bool          TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) ;
     bool          TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) ;
     bool          TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) ;
     void          TreePush(const char* str_id);                                       // ~ Indent()+PushID(). Already called by TreeNode() when returning true, but you can call TreePush/TreePop yourself if desired.
     void          TreePush(const void* ptr_id);                                       // "
     void          TreePop();                                                          // ~ Unindent()+PopID()
     float         GetTreeNodeToLabelSpacing();                                        // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
     bool          CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);  // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
     bool          CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0); // when 'p_visible != NULL': if '*p_visible==true' display an additional small close button on upper right of the header which will set the bool to false when clicked, if '*p_visible==false' don't display the header.
     void          SetNextItemOpen(bool is_open, ImGuiCond cond = 0);                  // set next TreeNode/CollapsingHeader open state.
     void          SetNextItemStorageID(ImGuiID storage_id);                           // set id to use for open/close storage (default to same as item id).

    // Widgets: Selectables
    // - A selectable highlights when hovered, and can display another color when selected.
    // - Neighbors selectable extend their highlight bounds in order to leave no gap between them. This is so a series of selected Selectable appear contiguous.
     bool          Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
     bool          Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));      // "bool* p_selected" point to the selection state (read-write), as a convenient helper.

    // Multi-selection system for Selectable(), Checkbox(), TreeNode() functions [BETA]
    // - This enables standard multi-selection/range-selection idioms (CTRL+Mouse/Keyboard, SHIFT+Mouse/Keyboard, etc.) in a way that also allow a clipper to be used.
    // - ImGuiSelectionUserData is often used to store your item index within the current view (but may store something else).
    // - Read comments near ImGuiMultiSelectIO for instructions/details and see 'Demo->Widgets->Selection State & Multi-Select' for demo.
    // - TreeNode() is technically supported but... using this correctly is more complicated. You need some sort of linear/random access to your tree,
    //   which is suited to advanced trees setups already implementing filters and clipper. We will work simplifying the current demo.
    // - 'selection_size' and 'items_count' parameters are optional and used by a few features. If they are costly for you to compute, you may avoid them.
     ImGuiMultiSelectIO*   BeginMultiSelect(ImGuiMultiSelectFlags flags, int selection_size = -1, int items_count = -1);
     ImGuiMultiSelectIO*   EndMultiSelect();
     void                  SetNextItemSelectionUserData(ImGuiSelectionUserData selection_user_data);
     bool                  IsItemToggledSelection();                                   // Was the last item selection state toggled? Useful if you need the per-item information _before_ reaching EndMultiSelect(). We only returns toggle _event_ in order to handle clipping correctly.

    // Widgets: List Boxes
    // - This is essentially a thin wrapper to using BeginChild/EndChild with the ImGuiChildFlags_FrameStyle flag for stylistic changes + displaying a label.
    // - If you don't need a label you can probably simply use BeginChild() with the ImGuiChildFlags_FrameStyle flag for the same result.
    // - You can submit contents and manage your selection state however you want it, by creating e.g. Selectable() or any other items.
    // - The simplified/old ListBox() api are helpers over BeginListBox()/EndListBox() which are kept available for convenience purpose. This is analoguous to how Combos are created.
    // - Choose frame width:   size.x > 0.0f: custom  /  size.x < 0.0f or -FLT_MIN: right-align   /  size.x = 0.0f (default): use current ItemWidth
    // - Choose frame height:  size.y > 0.0f: custom  /  size.y < 0.0f or -FLT_MIN: bottom-align  /  size.y = 0.0f (default): arbitrary default height which can fit ~7 items
     bool          BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0)); // open a framed scrolling region
     void          EndListBox();                                                       // only call EndListBox() if BeginListBox() returned true!
     bool          ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
     bool          ListBox(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int height_in_items = -1);

    // Widgets: Data Plotting
    // - Consider using ImPlot (https://github.com/epezent/implot) which is much better!
     void          PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = ((void *)0), float scale_min = 3.402823466e+38F, float scale_max = 3.402823466e+38F, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
     void          PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = ((void *)0), float scale_min = 3.402823466e+38F, float scale_max = 3.402823466e+38F, ImVec2 graph_size = ImVec2(0, 0));
     void          PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = ((void *)0), float scale_min = 3.402823466e+38F, float scale_max = 3.402823466e+38F, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float));
     void          PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = ((void *)0), float scale_min = 3.402823466e+38F, float scale_max = 3.402823466e+38F, ImVec2 graph_size = ImVec2(0, 0));

    // Widgets: Value() Helpers.
    // - Those are merely shortcut to calling Text() with a format string. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
     void          Value(const char* prefix, bool b);
     void          Value(const char* prefix, int v);
     void          Value(const char* prefix, unsigned int v);
     void          Value(const char* prefix, float v, const char* float_format = ((void *)0));

    // Widgets: Menus
    // - Use BeginMenuBar() on a window ImGuiWindowFlags_MenuBar to append to its menu bar.
    // - Use BeginMainMenuBar() to create a menu bar at the top of the screen and append to it.
    // - Use BeginMenu() to create a menu. You can call BeginMenu() multiple time with the same identifier to append more items to it.
    // - Not that MenuItem() keyboardshortcuts are displayed as a convenience but _not processed_ by Dear ImGui at the moment.
     bool          BeginMenuBar();                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
     void          EndMenuBar();                                                       // only call EndMenuBar() if BeginMenuBar() returns true!
     bool          BeginMainMenuBar();                                                 // create and append to a full screen menu-bar.
     void          EndMainMenuBar();                                                   // only call EndMainMenuBar() if BeginMainMenuBar() returns true!
     bool          BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
     void          EndMenu();                                                          // only call EndMenu() if BeginMenu() returns true!
     bool          MenuItem(const char* label, const char* shortcut = ((void *)0), bool selected = false, bool enabled = true);  // return true when activated.
     bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // return true when activated + toggle (*p_selected) if p_selected != NULL

    // Tooltips
    // - Tooltips are windows following the mouse. They do not take focus away.
    // - A tooltip window can contain items of any types.
    // - SetTooltip() is more or less a shortcut for the 'if (BeginTooltip()) { Text(...); EndTooltip(); }' idiom (with a subtlety that it discard any previously submitted tooltip)
     bool          BeginTooltip();                                                     // begin/append a tooltip window.
     void          EndTooltip();                                                       // only call EndTooltip() if BeginTooltip()/BeginItemTooltip() returns true!
     void          SetTooltip(const char* fmt, ...) ;                     // set a text-only tooltip. Often used after a ImGui::IsItemHovered() check. Override any previous call to SetTooltip().
     void          SetTooltipV(const char* fmt, va_list args) ;

    // Tooltips: helpers for showing a tooltip when hovering an item
    // - BeginItemTooltip() is a shortcut for the 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip) && BeginTooltip())' idiom.
    // - SetItemTooltip() is a shortcut for the 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip)) { SetTooltip(...); }' idiom.
    // - Where 'ImGuiHoveredFlags_ForTooltip' itself is a shortcut to use 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' depending on active input type. For mouse it defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'.
     bool          BeginItemTooltip();                                                 // begin/append a tooltip window if preceding item was hovered.
     void          SetItemTooltip(const char* fmt, ...) ;                 // set a text-only tooltip if preceding item was hovered. override any previous call to SetTooltip().
     void          SetItemTooltipV(const char* fmt, va_list args) ;

    // Popups, Modals
    //  - They block normal mouse hovering detection (and therefore most mouse interactions) behind them.
    //  - If not modal: they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
    //  - Their visibility state (~bool) is held internally instead of being held by the programmer as we are used to with regular Begin*() calls.
    //  - The 3 properties above are related: we need to retain popup visibility state in the library because popups may be closed as any time.
    //  - You can bypass the hovering restriction by using ImGuiHoveredFlags_AllowWhenBlockedByPopup when calling IsItemHovered() or IsWindowHovered().
    //  - IMPORTANT: Popup identifiers are relative to the current ID stack, so OpenPopup and BeginPopup generally needs to be at the same level of the stack.
    //    This is sometimes leading to confusing mistakes. May rework this in the future.
    //  - BeginPopup(): query popup state, if open start appending into the window. Call EndPopup() afterwards if returned true. ImGuiWindowFlags are forwarded to the window.
    //  - BeginPopupModal(): block every interaction behind the window, cannot be closed by user, add a dimming background, has a title bar.
     bool          BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);                         // return true if the popup is open, and you can start outputting to it.
     bool          BeginPopupModal(const char* name, bool* p_open = ((void *)0), ImGuiWindowFlags flags = 0); // return true if the modal is open, and you can start outputting to it.
     void          EndPopup();                                                                         // only call EndPopup() if BeginPopupXXX() returns true!

    // Popups: open/close functions
    //  - OpenPopup(): set popup state to open. ImGuiPopupFlags are available for opening options.
    //  - If not modal: they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
    //  - CloseCurrentPopup(): use inside the BeginPopup()/EndPopup() scope to close manually.
    //  - CloseCurrentPopup() is called by default by Selectable()/MenuItem() when activated (FIXME: need some options).
    //  - Use ImGuiPopupFlags_NoOpenOverExistingPopup to avoid opening a popup if there's already one at the same level. This is equivalent to e.g. testing for !IsAnyPopupOpen() prior to OpenPopup().
    //  - Use IsWindowAppearing() after BeginPopup() to tell if a window just opened.
    //  - IMPORTANT: Notice that for OpenPopupOnItemClick() we exceptionally default flags to 1 (== ImGuiPopupFlags_MouseButtonRight) for backward compatibility with older API taking 'int mouse_button = 1' parameter
     void          OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0);                     // call to mark popup as open (don't call every frame!).
     void          OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0);                             // id overload to facilitate calling from nested stacks
     void          OpenPopupOnItemClick(const char* str_id = ((void *)0), ImGuiPopupFlags popup_flags = 1);   // helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1. (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)
     void          CloseCurrentPopup();                                                                // manually close the popup we have begin-ed into.

    // Popups: open+begin combined functions helpers
    //  - Helpers to do OpenPopup+BeginPopup where the Open action is triggered by e.g. hovering an item and right-clicking.
    //  - They are convenient to easily create context menus, hence the name.
    //  - IMPORTANT: Notice that BeginPopupContextXXX takes ImGuiPopupFlags just like OpenPopup() and unlike BeginPopup(). For full consistency, we may add ImGuiWindowFlags to the BeginPopupContextXXX functions in the future.
    //  - IMPORTANT: Notice that we exceptionally default their flags to 1 (== ImGuiPopupFlags_MouseButtonRight) for backward compatibility with older API taking 'int mouse_button = 1' parameter, so if you add other flags remember to re-add the ImGuiPopupFlags_MouseButtonRight.
     bool          BeginPopupContextItem(const char* str_id = ((void *)0), ImGuiPopupFlags popup_flags = 1);  // open+begin popup when clicked on last item. Use str_id==NULL to associate the popup to previous item. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!
     bool          BeginPopupContextWindow(const char* str_id = ((void *)0), ImGuiPopupFlags popup_flags = 1);// open+begin popup when clicked on current window.
     bool          BeginPopupContextVoid(const char* str_id = ((void *)0), ImGuiPopupFlags popup_flags = 1);  // open+begin popup when clicked in void (where there are no windows).

    // Popups: query functions
    //  - IsPopupOpen(): return true if the popup is open at the current BeginPopup() level of the popup stack.
    //  - IsPopupOpen() with ImGuiPopupFlags_AnyPopupId: return true if any popup is open at the current BeginPopup() level of the popup stack.
    //  - IsPopupOpen() with ImGuiPopupFlags_AnyPopupId + ImGuiPopupFlags_AnyPopupLevel: return true if any popup is open.
     bool          IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0);                         // return true if the popup is open.

    // Tables
    // - Full-featured replacement for old Columns API.
    // - See Demo->Tables for demo code. See top of imgui_tables.cpp for general commentary.
    // - See ImGuiTableFlags_ and ImGuiTableColumnFlags_ enums for a description of available flags.
    // The typical call flow is:
    // - 1. Call BeginTable(), early out if returning false.
    // - 2. Optionally call TableSetupColumn() to submit column name/flags/defaults.
    // - 3. Optionally call TableSetupScrollFreeze() to request scroll freezing of columns/rows.
    // - 4. Optionally call TableHeadersRow() to submit a header row. Names are pulled from TableSetupColumn() data.
    // - 5. Populate contents:
    //    - In most situations you can use TableNextRow() + TableSetColumnIndex(N) to start appending into a column.
    //    - If you are using tables as a sort of grid, where every column is holding the same type of contents,
    //      you may prefer using TableNextColumn() instead of TableNextRow() + TableSetColumnIndex().
    //      TableNextColumn() will automatically wrap-around into the next row if needed.
    //    - IMPORTANT: Comparatively to the old Columns() API, we need to call TableNextColumn() for the first column!
    //    - Summary of possible call flow:
    //        - TableNextRow() -> TableSetColumnIndex(0) -> Text("Hello 0") -> TableSetColumnIndex(1) -> Text("Hello 1")  // OK
    //        - TableNextRow() -> TableNextColumn()      -> Text("Hello 0") -> TableNextColumn()      -> Text("Hello 1")  // OK
    //        -                   TableNextColumn()      -> Text("Hello 0") -> TableNextColumn()      -> Text("Hello 1")  // OK: TableNextColumn() automatically gets to next row!
    //        - TableNextRow()                           -> Text("Hello 0")                                               // Not OK! Missing TableSetColumnIndex() or TableNextColumn()! Text will not appear!
    // - 5. Call EndTable()
     bool          BeginTable(const char* str_id, int columns, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f);
     void          EndTable();                                         // only call EndTable() if BeginTable() returns true!
     void          TableNextRow(ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f); // append into the first cell of a new row.
     bool          TableNextColumn();                                  // append into the next column (or first column of next row if currently in last column). Return true when column is visible.
     bool          TableSetColumnIndex(int column_n);                  // append into the specified column. Return true when column is visible.

    // Tables: Headers & Columns declaration
    // - Use TableSetupColumn() to specify label, resizing policy, default width/weight, id, various other flags etc.
    // - Use TableHeadersRow() to create a header row and automatically submit a TableHeader() for each column.
    //   Headers are required to perform: reordering, sorting, and opening the context menu.
    //   The context menu can also be made available in columns body using ImGuiTableFlags_ContextMenuInBody.
    // - You may manually submit headers using TableNextRow() + TableHeader() calls, but this is only useful in
    //   some advanced use cases (e.g. adding custom widgets in header row).
    // - Use TableSetupScrollFreeze() to lock columns/rows so they stay visible when scrolled.
     void          TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
     void          TableSetupScrollFreeze(int cols, int rows);         // lock columns/rows so they stay visible when scrolled.
     void          TableHeader(const char* label);                     // submit one header cell manually (rarely used)
     void          TableHeadersRow();                                  // submit a row with headers cells based on data provided to TableSetupColumn() + submit context menu
     void          TableAngledHeadersRow();                            // submit a row with angled headers for every column with the ImGuiTableColumnFlags_AngledHeader flag. MUST BE FIRST ROW.

    // Tables: Sorting & Miscellaneous functions
    // - Sorting: call TableGetSortSpecs() to retrieve latest sort specs for the table. NULL when not sorting.
    //   When 'sort_specs->SpecsDirty == true' you should sort your data. It will be true when sorting specs have
    //   changed since last call, or the first time. Make sure to set 'SpecsDirty = false' after sorting,
    //   else you may wastefully sort your data every frame!
    // - Functions args 'int column_n' treat the default value of -1 as the same as passing the current column index.
     ImGuiTableSortSpecs*  TableGetSortSpecs();                        // get latest sort specs for the table (NULL if not sorting).  Lifetime: don't hold on this pointer over multiple frames or past any subsequent call to BeginTable().
     int                   TableGetColumnCount();                      // return number of columns (value passed to BeginTable)
     int                   TableGetColumnIndex();                      // return current column index.
     int                   TableGetRowIndex();                         // return current row index.
     const char*           TableGetColumnName(int column_n = -1);      // return "" if column didn't have a name declared by TableSetupColumn(). Pass -1 to use current column.
     ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1);     // return column flags so you can query their Enabled/Visible/Sorted/Hovered status flags. Pass -1 to use current column.
     void                  TableSetColumnEnabled(int column_n, bool v);// change user accessible enabled/disabled state of a column. Set to false to hide the column. User can use the context menu to change this themselves (right-click in headers, or right-click in columns body with ImGuiTableFlags_ContextMenuInBody)
     int                   TableGetHoveredColumn();                    // return hovered column. return -1 when table is not hovered. return columns_count if the unused space at the right of visible columns is hovered. Can also use (TableGetColumnFlags() & ImGuiTableColumnFlags_IsHovered) instead.
     void                  TableSetBgColor(ImGuiTableBgTarget target, ImU32 color, int column_n = -1);  // change the color of a cell, row, or column. See ImGuiTableBgTarget_ flags for details.

    // Legacy Columns API (prefer using Tables!)
    // - You can also use SameLine(pos_x) to mimic simplified columns.
     void          Columns(int count = 1, const char* id = ((void *)0), bool borders = true);
     void          NextColumn();                                                       // next column, defaults to current row or next row if the current row is finished
     int           GetColumnIndex();                                                   // get current column index
     float         GetColumnWidth(int column_index = -1);                              // get column width (in pixels). pass -1 to use current column
     void          SetColumnWidth(int column_index, float width);                      // set column width (in pixels). pass -1 to use current column
     float         GetColumnOffset(int column_index = -1);                             // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetColumnsCount() inclusive. column 0 is typically 0.0f
     void          SetColumnOffset(int column_index, float offset_x);                  // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
     int           GetColumnsCount();

    // Tab Bars, Tabs
    // - Note: Tabs are automatically created by the docking system (when in 'docking' branch). Use this to create tab bars/tabs yourself.
     bool          BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0);        // create and append into a TabBar
     void          EndTabBar();                                                        // only call EndTabBar() if BeginTabBar() returns true!
     bool          BeginTabItem(const char* label, bool* p_open = ((void *)0), ImGuiTabItemFlags flags = 0); // create a Tab. Returns true if the Tab is selected.
     void          EndTabItem();                                                       // only call EndTabItem() if BeginTabItem() returns true!
     bool          TabItemButton(const char* label, ImGuiTabItemFlags flags = 0);      // create a Tab behaving like a button. return true when clicked. cannot be selected in the tab bar.
     void          SetTabItemClosed(const char* tab_or_docked_window_label);           // notify TabBar or Docking system of a closed tab/window ahead (useful to reduce visual flicker on reorderable tab bars). For tab-bar: call after BeginTabBar() and before Tab submissions. Otherwise call with a window name.

    // Docking
    // [BETA API] Enable with io.ConfigFlags |= ImGuiConfigFlags_DockingEnable.
    // Note: You can use most Docking facilities without calling any API. You DO NOT need to call DockSpace() to use Docking!
    // - Drag from window title bar or their tab to dock/undock. Hold SHIFT to disable docking.
    // - Drag from window menu button (upper-left button) to undock an entire node (all windows).
    // - When io.ConfigDockingWithShift == true, you instead need to hold SHIFT to enable docking.
    // About dockspaces:
    // - Use DockSpaceOverViewport() to create a window covering the screen or a specific viewport + a dockspace inside it.
    //   This is often used with ImGuiDockNodeFlags_PassthruCentralNode to make it transparent.
    // - Use DockSpace() to create an explicit dock node _within_ an existing window. See Docking demo for details.
    // - Important: Dockspaces need to be submitted _before_ any window they can host. Submit it early in your frame!
    // - Important: Dockspaces need to be kept alive if hidden, otherwise windows docked into it will be undocked.
    //   e.g. if you have multiple tabs with a dockspace inside each tab: submit the non-visible dockspaces with ImGuiDockNodeFlags_KeepAliveOnly.
     ImGuiID       DockSpace(ImGuiID dockspace_id, const ImVec2& size = ImVec2(0, 0), ImGuiDockNodeFlags flags = 0, const ImGuiWindowClass* window_class = ((void *)0));
     ImGuiID       DockSpaceOverViewport(ImGuiID dockspace_id = 0, const ImGuiViewport* viewport = ((void *)0), ImGuiDockNodeFlags flags = 0, const ImGuiWindowClass* window_class = ((void *)0));
     void          SetNextWindowDockID(ImGuiID dock_id, ImGuiCond cond = 0);           // set next window dock id
     void          SetNextWindowClass(const ImGuiWindowClass* window_class);           // set next window class (control docking compatibility + provide hints to platform backend via custom viewport flags and platform parent/child relationship)
     ImGuiID       GetWindowDockID();
     bool          IsWindowDocked();                                                   // is current window docked into another window?

    // Logging/Capture
    // - All text output from the interface can be captured into tty/file/clipboard. By default, tree nodes are automatically opened during logging.
     void          LogToTTY(int auto_open_depth = -1);                                 // start logging to tty (stdout)
     void          LogToFile(int auto_open_depth = -1, const char* filename = ((void *)0));   // start logging to file
     void          LogToClipboard(int auto_open_depth = -1);                           // start logging to OS clipboard
     void          LogFinish();                                                        // stop logging (close file, etc.)
     void          LogButtons();                                                       // helper to display buttons for logging to tty/file/clipboard
     void          LogText(const char* fmt, ...) ;                        // pass text data straight to log (without being displayed)
     void          LogTextV(const char* fmt, va_list args) ;

    // Drag and Drop
    // - On source items, call BeginDragDropSource(), if it returns true also call SetDragDropPayload() + EndDragDropSource().
    // - On target candidates, call BeginDragDropTarget(), if it returns true also call AcceptDragDropPayload() + EndDragDropTarget().
    // - If you stop calling BeginDragDropSource() the payload is preserved however it won't have a preview tooltip (we currently display a fallback "..." tooltip, see #1725)
    // - An item can be both drag source and drop target.
     bool          BeginDragDropSource(ImGuiDragDropFlags flags = 0);                                      // call after submitting an item which may be dragged. when this return true, you can call SetDragDropPayload() + EndDragDropSource()
     bool          SetDragDropPayload(const char* type, const void* data, size_t sz, ImGuiCond cond = 0);  // type is a user defined string of maximum 32 characters. Strings starting with '_' are reserved for dear imgui internal types. Data is copied and held by imgui. Return true when payload has been accepted.
     void          EndDragDropSource();                                                                    // only call EndDragDropSource() if BeginDragDropSource() returns true!
     bool                  BeginDragDropTarget();                                                          // call after submitting an item that may receive a payload. If this returns true, you can call AcceptDragDropPayload() + EndDragDropTarget()
     const ImGuiPayload*   AcceptDragDropPayload(const char* type, ImGuiDragDropFlags flags = 0);          // accept contents of a given type. If ImGuiDragDropFlags_AcceptBeforeDelivery is set you can peek into the payload before the mouse button is released.
     void                  EndDragDropTarget();                                                            // only call EndDragDropTarget() if BeginDragDropTarget() returns true!
     const ImGuiPayload*   GetDragDropPayload();                                                           // peek directly into the current payload from anywhere. returns NULL when drag and drop is finished or inactive. use ImGuiPayload::IsDataType() to test for the payload type.

    // Disabling [BETA API]
    // - Disable all user interactions and dim items visuals (applying style.DisabledAlpha over current colors)
    // - Those can be nested but it cannot be used to enable an already disabled section (a single BeginDisabled(true) in the stack is enough to keep everything disabled)
    // - Tooltips windows by exception are opted out of disabling.
    // - BeginDisabled(false)/EndDisabled() essentially does nothing but is provided to facilitate use of boolean expressions (as a micro-optimization: if you have tens of thousands of BeginDisabled(false)/EndDisabled() pairs, you might want to reformulate your code to avoid making those calls)
     void          BeginDisabled(bool disabled = true);
     void          EndDisabled();

    // Clipping
    // - Mouse hovering is affected by ImGui::PushClipRect() calls, unlike direct calls to ImDrawList::PushClipRect() which are render only.
     void          PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect);
     void          PopClipRect();

    // Focus, Activation
     void          SetItemDefaultFocus();                                              // make last item the default focused item of of a newly appearing window.
     void          SetKeyboardFocusHere(int offset = 0);                               // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.

    // Keyboard/Gamepad Navigation
     void          SetNavCursorVisible(bool visible);                                  // alter visibility of keyboard/gamepad cursor. by default: show when using an arrow key, hide when clicking with mouse.

    // Overlapping mode
     void          SetNextItemAllowOverlap();                                          // allow next item to be overlapped by a subsequent item. Useful with invisible buttons, selectable, treenode covering an area where subsequent items may need to be added. Note that both Selectable() and TreeNode() have dedicated flags doing this.

    // Item/Widgets Utilities and Query Functions
    // - Most of the functions are referring to the previous Item that has been submitted.
    // - See Demo Window under "Widgets->Querying Status" for an interactive visualization of most of those functions.
     bool          IsItemHovered(ImGuiHoveredFlags flags = 0);                         // is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.
     bool          IsItemActive();                                                     // is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)
     bool          IsItemFocused();                                                    // is the last item focused for keyboard/gamepad navigation?
     bool          IsItemClicked(ImGuiMouseButton mouse_button = 0);                   // is the last item hovered and mouse clicked on? (**)  == IsMouseClicked(mouse_button) && IsItemHovered()Important. (**) this is NOT equivalent to the behavior of e.g. Button(). Read comments in function definition.
     bool          IsItemVisible();                                                    // is the last item visible? (items may be out of sight because of clipping/scrolling)
     bool          IsItemEdited();                                                     // did the last item modify its underlying value this frame? or was pressed? This is generally the same as the "bool" return value of many widgets.
     bool          IsItemActivated();                                                  // was the last item just made active (item was previously inactive).
     bool          IsItemDeactivated();                                                // was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that require continuous editing.
     bool          IsItemDeactivatedAfterEdit();                                       // was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that require continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).
     bool          IsItemToggledOpen();                                                // was the last item open state toggled? set by TreeNode().
     bool          IsAnyItemHovered();                                                 // is any item hovered?
     bool          IsAnyItemActive();                                                  // is any item active?
     bool          IsAnyItemFocused();                                                 // is any item focused?
     ImGuiID       GetItemID();                                                        // get ID of last item (~~ often same ImGui::GetID(label) beforehand)
     ImVec2        GetItemRectMin();                                                   // get upper-left bounding rectangle of the last item (screen space)
     ImVec2        GetItemRectMax();                                                   // get lower-right bounding rectangle of the last item (screen space)
     ImVec2        GetItemRectSize();                                                  // get size of last item

    // Viewports
    // - Currently represents the Platform Window created by the application which is hosting our Dear ImGui windows.
    // - In 'docking' branch with multi-viewport enabled, we extend this concept to have multiple active viewports.
    // - In the future we will extend this concept further to also represent Platform Monitor and support a "no main platform window" operation mode.
     ImGuiViewport* GetMainViewport();                                                 // return primary/default viewport. This can never be NULL.

    // Background/Foreground Draw Lists
     ImDrawList*   GetBackgroundDrawList(ImGuiViewport* viewport = ((void *)0));              // get background draw list for the given viewport or viewport associated to the current window. this draw list will be the first rendering one. Useful to quickly draw shapes/text behind dear imgui contents.
     ImDrawList*   GetForegroundDrawList(ImGuiViewport* viewport = ((void *)0));              // get foreground draw list for the given viewport or viewport associated to the current window. this draw list will be the top-most rendered one. Useful to quickly draw shapes/text over dear imgui contents.

    // Miscellaneous Utilities
     bool          IsRectVisible(const ImVec2& size);                                  // test if rectangle (of given size, starting from cursor position) is visible / not clipped.
     bool          IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);      // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
     double        GetTime();                                                          // get global imgui time. incremented by io.DeltaTime every frame.
     int           GetFrameCount();                                                    // get global imgui frame count. incremented by 1 every frame.
     ImDrawListSharedData* GetDrawListSharedData();                                    // you may use this when creating your own ImDrawList instances.
     const char*   GetStyleColorName(ImGuiCol idx);                                    // get a string corresponding to the enum value (for display, saving, etc.).
     void          SetStateStorage(ImGuiStorage* storage);                             // replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
     ImGuiStorage* GetStateStorage();

    // Text Utilities
     ImVec2        CalcTextSize(const char* text, const char* text_end = ((void *)0), bool hide_text_after_double_hash = false, float wrap_width = -1.0f);

    // Color Utilities
     ImVec4        ColorConvertU32ToFloat4(ImU32 in);
     ImU32         ColorConvertFloat4ToU32(const ImVec4& in);
     void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
     void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

    // Inputs Utilities: Keyboard/Mouse/Gamepad
    // - the ImGuiKey enum contains all possible keyboard, mouse and gamepad inputs (e.g. ImGuiKey_A, ImGuiKey_MouseLeft, ImGuiKey_GamepadDpadUp...).
    // - (legacy: before v1.87, we used ImGuiKey to carry native/user indices as defined by each backends. This was obsoleted in 1.87 (2022-02) and completely removed in 1.91.5 (2024-11). See https://github.com/ocornut/imgui/issues/4921)
    // - (legacy: any use of ImGuiKey will assert when key < 512 to detect passing legacy native/user indices)
     bool          IsKeyDown(ImGuiKey key);                                            // is key being held.
     bool          IsKeyPressed(ImGuiKey key, bool repeat = true);                     // was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
     bool          IsKeyReleased(ImGuiKey key);                                        // was key released (went from Down to !Down)?
     bool          IsKeyChordPressed(ImGuiKeyChord key_chord);                         // was key chord (mods + key) pressed, e.g. you can pass 'ImGuiMod_Ctrl | ImGuiKey_S' as a key-chord. This doesn't do any routing or focus check, please consider using Shortcut() function instead.
     int           GetKeyPressedAmount(ImGuiKey key, float repeat_delay, float rate);  // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
     const char*   GetKeyName(ImGuiKey key);                                           // [DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared.
     void          SetNextFrameWantCaptureKeyboard(bool want_capture_keyboard);        // Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard"; after the next NewFrame() call.

    // Inputs Utilities: Shortcut Testing & Routing [BETA]
    // - ImGuiKeyChord = a ImGuiKey + optional ImGuiMod_Alt/ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Super.
    //       ImGuiKey_C                          // Accepted by functions taking ImGuiKey or ImGuiKeyChord arguments)
    //       ImGuiMod_Ctrl | ImGuiKey_C          // Accepted by functions taking ImGuiKeyChord arguments)
    //   only ImGuiMod_XXX values are legal to combine with an ImGuiKey. You CANNOT combine two ImGuiKey values.
    // - The general idea is that several callers may register interest in a shortcut, and only one owner gets it.
    //      Parent   -> call Shortcut(Ctrl+S)    // When Parent is focused, Parent gets the shortcut.
    //        Child1 -> call Shortcut(Ctrl+S)    // When Child1 is focused, Child1 gets the shortcut (Child1 overrides Parent shortcuts)
    //        Child2 -> no call                  // When Child2 is focused, Parent gets the shortcut.
    //   The whole system is order independent, so if Child1 makes its calls before Parent, results will be identical.
    //   This is an important property as it facilitate working with foreign code or larger codebase.
    // - To understand the difference:
    //   - IsKeyChordPressed() compares mods and call IsKeyPressed() -> function has no side-effect.
    //   - Shortcut() submits a route, routes are resolved, if it currently can be routed it calls IsKeyChordPressed() -> function has (desirable) side-effects as it can prevents another call from getting the route.
    // - Visualize registered routes in 'Metrics/Debugger->Inputs'.
     bool          Shortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);
     void          SetNextItemShortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags = 0);

    // Inputs Utilities: Key/Input Ownership [BETA]
    // - One common use case would be to allow your items to disable standard inputs behaviors such
    //   as Tab or Alt key handling, Mouse Wheel scrolling, etc.
    //   e.g. Button(...); SetItemKeyOwner(ImGuiKey_MouseWheelY); to make hovering/activating a button disable wheel for scrolling.
    // - Reminder ImGuiKey enum include access to mouse buttons and gamepad, so key ownership can apply to them.
    // - Many related features are still in imgui_internal.h. For instance, most IsKeyXXX()/IsMouseXXX() functions have an owner-id-aware version.
     void          SetItemKeyOwner(ImGuiKey key);                                      // Set key owner to last item ID if it is hovered or active. Equivalent to 'if (IsItemHovered() || IsItemActive()) { SetKeyOwner(key, GetItemID());'.

    // Inputs Utilities: Mouse
    // - To refer to a mouse button, you may use named enums in your code e.g. ImGuiMouseButton_Left, ImGuiMouseButton_Right.
    // - You can also use regular integer: it is forever guaranteed that 0=Left, 1=Right, 2=Middle.
    // - Dragging operations are only reported after mouse has moved a certain distance away from the initial clicking position (see 'lock_threshold' and 'io.MouseDraggingThreshold')
     bool          IsMouseDown(ImGuiMouseButton button);                               // is mouse button held?
     bool          IsMouseClicked(ImGuiMouseButton button, bool repeat = false);       // did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1.
     bool          IsMouseReleased(ImGuiMouseButton button);                           // did mouse button released? (went from Down to !Down)
     bool          IsMouseDoubleClicked(ImGuiMouseButton button);                      // did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)
     bool          IsMouseReleasedWithDelay(ImGuiMouseButton button, float delay);     // delayed mouse release (use very sparingly!). Generally used with 'delay >= io.MouseDoubleClickTime' + combined with a 'io.MouseClickedLastCount==1' test. This is a very rarely used UI idiom, but some apps use this: e.g. MS Explorer single click on an icon to rename.
     int           GetMouseClickedCount(ImGuiMouseButton button);                      // return the number of successive mouse-clicks at the time where a click happen (otherwise 0).
     bool          IsMouseHoveringRect(const ImVec2& r_min, const ImVec2& r_max, bool clip = true);// is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.
     bool          IsMousePosValid(const ImVec2* mouse_pos = ((void *)0));                    // by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available
     bool          IsAnyMouseDown();                                                   // [WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid.
     ImVec2        GetMousePos();                                                      // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
     ImVec2        GetMousePosOnOpeningCurrentPopup();                                 // retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)
     bool          IsMouseDragging(ImGuiMouseButton button, float lock_threshold = -1.0f);         // is mouse dragging? (uses io.MouseDraggingThreshold if lock_threshold < 0.0f)
     ImVec2        GetMouseDragDelta(ImGuiMouseButton button = 0, float lock_threshold = -1.0f);   // return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (uses io.MouseDraggingThreshold if lock_threshold < 0.0f)
     void          ResetMouseDragDelta(ImGuiMouseButton button = 0);                   //
     ImGuiMouseCursor GetMouseCursor();                                                // get desired mouse cursor shape. Important: reset in ImGui::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
     void          SetMouseCursor(ImGuiMouseCursor cursor_type);                       // set desired mouse cursor shape
     void          SetNextFrameWantCaptureMouse(bool want_capture_mouse);              // Override io.WantCaptureMouse flag next frame (said flag is left for your application to handle, typical when true it instucts your app to ignore inputs). This is equivalent to setting "io.WantCaptureMouse = want_capture_mouse;" after the next NewFrame() call.

    // Clipboard Utilities
    // - Also see the LogToClipboard() function to capture GUI into clipboard, or easily output text data to the clipboard.
     const char*   GetClipboardText();
     void          SetClipboardText(const char* text);

    // Settings/.Ini Utilities
    // - The disk functions are automatically called if io.IniFilename != NULL (default is "imgui.ini").
    // - Set io.IniFilename to NULL to load/save manually. Read io.WantSaveIniSettings description about handling .ini saving manually.
    // - Important: default value "imgui.ini" is relative to current working dir! Most apps will want to lock this to an absolute path (e.g. same path as executables).
     void          LoadIniSettingsFromDisk(const char* ini_filename);                  // call after CreateContext() and before the first call to NewFrame(). NewFrame() automatically calls LoadIniSettingsFromDisk(io.IniFilename).
     void          LoadIniSettingsFromMemory(const char* ini_data, size_t ini_size=0); // call after CreateContext() and before the first call to NewFrame() to provide .ini data from your own data source.
     void          SaveIniSettingsToDisk(const char* ini_filename);                    // this is automatically called (if io.IniFilename is not empty) a few seconds after any modification that should be reflected in the .ini file (and also by DestroyContext).
     const char*   SaveIniSettingsToMemory(size_t* out_ini_size = ((void *)0));               // return a zero-terminated string with the .ini data which you can save by your own mean. call when io.WantSaveIniSettings is set, then save data by your own mean and clear io.WantSaveIniSettings.

    // Debug Utilities
    // - Your main debugging friend is the ShowMetricsWindow() function, which is also accessible from Demo->Tools->Metrics Debugger
     void          DebugTextEncoding(const char* text);
     void          DebugFlashStyleColor(ImGuiCol idx);
     void          DebugStartItemPicker();
     bool          DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert, size_t sz_drawidx); // This is called by IMGUI_CHECKVERSION() macro.

     void          DebugLog(const char* fmt, ...)           ; // Call via IMGUI_DEBUG_LOG() for maximum stripping in caller code!
     void          DebugLogV(const char* fmt, va_list args) ;

    // Memory Allocators
    // - Those functions are not reliant on the current context.
    // - DLL users: heaps and globals are not shared across DLL boundaries! You will need to call SetCurrentContext() + SetAllocatorFunctions()
    //   for each static/DLL boundary you are calling from. Read "Context and Memory Allocators" section of imgui.cpp for more details.
     void          SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func, ImGuiMemFreeFunc free_func, void* user_data = ((void *)0));
     void          GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data);
     void*         MemAlloc(size_t size);
     void          MemFree(void* ptr);

    // (Optional) Platform/OS interface for multi-viewport support
    // Read comments around the ImGuiPlatformIO structure for more details.
    // Note: You may use GetWindowViewport() to get the current viewport of the current window.
     void              UpdatePlatformWindows();                                        // call in main loop. will call CreateWindow/ResizeWindow/etc. platform functions for each secondary viewport, and DestroyWindow for each inactive viewport.
     void              RenderPlatformWindowsDefault(void* platform_render_arg = ((void *)0), void* renderer_render_arg = ((void *)0)); // call in main loop. will call RenderWindow/SwapBuffers platform functions for each secondary viewport which doesn't have the ImGuiViewportFlags_Minimized flag set. May be reimplemented by user for custom rendering needs.
     void              DestroyPlatformWindows();                                       // call DestroyWindow platform functions for all viewports. call from backend Shutdown() if you need to close platform windows before imgui shutdown. otherwise will be called by DestroyContext().
     ImGuiViewport*    FindViewportByID(ImGuiID id);                                   // this is a helper for backends.
     ImGuiViewport*    FindViewportByPlatformHandle(void* platform_handle);            // this is a helper for backends. the type platform_handle is decided by the backend (e.g. HWND, MyWindow*, GLFWwindow* etc.)

} // namespace ImGui

//-----------------------------------------------------------------------------
// [SECTION] Flags & Enumerations
//-----------------------------------------------------------------------------

// Flags for ImGui::Begin()
// (Those are per-window flags. There are shared flags in ImGuiIO: io.ConfigWindowsResizeFromEdges and io.ConfigWindowsMoveFromTitleBarOnly)
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None                   = 0,
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    ImGuiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    ImGuiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    ImGuiWindowFlags_NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    ImGuiWindowFlags_NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    ImGuiWindowFlags_MenuBar                = 1 << 10,  // Has a menu-bar
    ImGuiWindowFlags_HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    ImGuiWindowFlags_NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    ImGuiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    ImGuiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    ImGuiWindowFlags_AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    ImGuiWindowFlags_NoNavInputs            = 1 << 16,  // No keyboard/gamepad navigation within the window
    ImGuiWindowFlags_NoNavFocus             = 1 << 17,  // No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by CTRL+TAB)
    ImGuiWindowFlags_UnsavedDocument        = 1 << 18,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    ImGuiWindowFlags_NoDocking              = 1 << 19,  // Disable docking of this window
    ImGuiWindowFlags_NoNav                  = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    ImGuiWindowFlags_NoDecoration           = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
    ImGuiWindowFlags_NoInputs               = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,

    // [Internal]
    ImGuiWindowFlags_DockNodeHost           = 1 << 23,  // Don't use! For internal use by Begin()/NewFrame()
    ImGuiWindowFlags_ChildWindow            = 1 << 24,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_Tooltip                = 1 << 25,  // Don't use! For internal use by BeginTooltip()
    ImGuiWindowFlags_Popup                  = 1 << 26,  // Don't use! For internal use by BeginPopup()
    ImGuiWindowFlags_Modal                  = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
    ImGuiWindowFlags_ChildMenu              = 1 << 28,  // Don't use! For internal use by BeginMenu()

    // Obsolete names




};

// Flags for ImGui::BeginChild()
// (Legacy: bit 0 must always correspond to ImGuiChildFlags_Borders to be backward compatible with old API using 'bool border = false'.
// About using AutoResizeX/AutoResizeY flags:
// - May be combined with SetNextWindowSizeConstraints() to set a min/max size for each axis (see "Demo->Child->Auto-resize with Constraints").
// - Size measurement for a given axis is only performed when the child window is within visible boundaries, or is just appearing.
//   - This allows BeginChild() to return false when not within boundaries (e.g. when scrolling), which is more optimal. BUT it won't update its auto-size while clipped.
//     While not perfect, it is a better default behavior as the always-on performance gain is more valuable than the occasional "resizing after becoming visible again" glitch.
//   - You may also use ImGuiChildFlags_AlwaysAutoResize to force an update even when child window is not in view.
//     HOWEVER PLEASE UNDERSTAND THAT DOING SO WILL PREVENT BeginChild() FROM EVER RETURNING FALSE, disabling benefits of coarse clipping.
enum ImGuiChildFlags_
{
    ImGuiChildFlags_None                    = 0,
    ImGuiChildFlags_Borders                 = 1 << 0,   // Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
    ImGuiChildFlags_AlwaysUseWindowPadding  = 1 << 1,   // Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
    ImGuiChildFlags_ResizeX                 = 1 << 2,   // Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
    ImGuiChildFlags_ResizeY                 = 1 << 3,   // Allow resize from bottom border (layout direction). "
    ImGuiChildFlags_AutoResizeX             = 1 << 4,   // Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AutoResizeY             = 1 << 5,   // Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
    ImGuiChildFlags_AlwaysAutoResize        = 1 << 6,   // Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
    ImGuiChildFlags_FrameStyle              = 1 << 7,   // Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
    ImGuiChildFlags_NavFlattened            = 1 << 8,   // [BETA] Share focus scope, allow keyboard/gamepad navigation to cross over parent border to this child or between sibling child windows.

    // Obsolete names



};

// Flags for ImGui::PushItemFlag()
// (Those are shared by all items)
enum ImGuiItemFlags_
{
    ImGuiItemFlags_None                     = 0,        // (Default)
    ImGuiItemFlags_NoTabStop                = 1 << 0,   // false    // Disable keyboard tabbing. This is a "lighter" version of ImGuiItemFlags_NoNav.
    ImGuiItemFlags_NoNav                    = 1 << 1,   // false    // Disable any form of focusing (keyboard/gamepad directional navigation and SetKeyboardFocusHere() calls).
    ImGuiItemFlags_NoNavDefaultFocus        = 1 << 2,   // false    // Disable item being a candidate for default focus (e.g. used by title bar items).
    ImGuiItemFlags_ButtonRepeat             = 1 << 3,   // false    // Any button-like behavior will have repeat mode enabled (based on io.KeyRepeatDelay and io.KeyRepeatRate values). Note that you can also call IsItemActive() after any button to tell if it is being held.
    ImGuiItemFlags_AutoClosePopups          = 1 << 4,   // true     // MenuItem()/Selectable() automatically close their parent popup window.
    ImGuiItemFlags_AllowDuplicateId         = 1 << 5,   // false    // Allow submitting an item with the same identifier as an item already submitted this frame without triggering a warning tooltip if io.ConfigDebugHighlightIdConflicts is set.
};

// Flags for ImGui::InputText()
// (Those are per-item flags. There are shared flags in ImGuiIO: io.ConfigInputTextCursorBlink and io.ConfigInputTextEnterKeepActive)
enum ImGuiInputTextFlags_
{
    // Basic filters (also see ImGuiInputTextFlags_CallbackCharFilter)
    ImGuiInputTextFlags_None                = 0,
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsScientific     = 1 << 2,   // Allow 0123456789.+-*/eE (Scientific notation input)
    ImGuiInputTextFlags_CharsUppercase      = 1 << 3,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 4,   // Filter out spaces, tabs

    // Inputs
    ImGuiInputTextFlags_AllowTabInput       = 1 << 5,   // Pressing TAB input a '\t' character into the text field
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 6,   // Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider using IsItemDeactivatedAfterEdit() instead!
    ImGuiInputTextFlags_EscapeClearsAll     = 1 << 7,   // Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 8,   // In multi-line mode, validate with Enter, add new line with Ctrl+Enter (default is opposite: validate with Ctrl+Enter, add line with Enter).

    // Other options
    ImGuiInputTextFlags_ReadOnly            = 1 << 9,   // Read-only mode
    ImGuiInputTextFlags_Password            = 1 << 10,  // Password mode, display all characters as '*', disable copy
    ImGuiInputTextFlags_AlwaysOverwrite     = 1 << 11,  // Overwrite mode
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 12,  // Select entire text when first taking mouse focus
    ImGuiInputTextFlags_ParseEmptyRefVal    = 1 << 13,  // InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value.
    ImGuiInputTextFlags_DisplayEmptyRefVal  = 1 << 14,  // InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it. Generally used with ImGuiInputTextFlags_ParseEmptyRefVal.
    ImGuiInputTextFlags_NoHorizontalScroll  = 1 << 15,  // Disable following the cursor horizontally
    ImGuiInputTextFlags_NoUndoRedo          = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().

    // Elide display / Alignment
    ImGuiInputTextFlags_ElideLeft			= 1 << 17,	// When text doesn't fit, elide left side to ensure right side stays visible. Useful for path/filenames. Single-line only!

    // Callback features
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 18,  // Callback on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory     = 1 << 19,  // Callback on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways      = 1 << 20,  // Callback on each iteration. User code may query cursor position, modify text buffer.
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 21,  // Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
    ImGuiInputTextFlags_CallbackResize      = 1 << 22,  // Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
    ImGuiInputTextFlags_CallbackEdit        = 1 << 23,  // Callback on any edit. Note that InputText() already returns true on edit + you can always use IsItemEdited(). The callback is useful to manipulate the underlying buffer while focus is active.

    // Obsolete names
    //ImGuiInputTextFlags_AlwaysInsertMode  = ImGuiInputTextFlags_AlwaysOverwrite   // [renamed in 1.82] name was not matching behavior
};

// Flags for ImGui::TreeNodeEx(), ImGui::CollapsingHeader*()
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None                 = 0,
    ImGuiTreeNodeFlags_Selected             = 1 << 0,   // Draw as selected
    ImGuiTreeNodeFlags_Framed               = 1 << 1,   // Draw frame with background (e.g. for CollapsingHeader)
    ImGuiTreeNodeFlags_AllowOverlap         = 1 << 2,   // Hit testing to allow subsequent widgets to overlap this one
    ImGuiTreeNodeFlags_NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    ImGuiTreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
    ImGuiTreeNodeFlags_DefaultOpen          = 1 << 5,   // Default node to be open
    ImGuiTreeNodeFlags_OpenOnDoubleClick    = 1 << 6,   // Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_OpenOnArrow          = 1 << 7,   // Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
    ImGuiTreeNodeFlags_Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes).
    ImGuiTreeNodeFlags_Bullet               = 1 << 9,   // Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
    ImGuiTreeNodeFlags_FramePadding         = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
    ImGuiTreeNodeFlags_SpanAvailWidth       = 1 << 11,  // Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line without using AllowOverlap mode.
    ImGuiTreeNodeFlags_SpanFullWidth        = 1 << 12,  // Extend hit box to the left-most and right-most edges (cover the indent area).
    ImGuiTreeNodeFlags_SpanLabelWidth       = 1 << 13,  // Narrow hit box + narrow hovering highlight, will only cover the label text.
    ImGuiTreeNodeFlags_SpanAllColumns       = 1 << 14,  // Frame will span all columns of its container table (label will still fit in current column)
    ImGuiTreeNodeFlags_LabelSpanAllColumns  = 1 << 15,  // Label will span all columns of its container table
    //ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 16,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 17,  // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
    ImGuiTreeNodeFlags_CollapsingHeader     = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog,





};

// Flags for OpenPopup*(), BeginPopupContext*(), IsPopupOpen() functions.
// - To be backward compatible with older API which took an 'int mouse_button = 1' argument instead of 'ImGuiPopupFlags flags',
//   we need to treat small flags values as a mouse button index, so we encode the mouse button in the first few bits of the flags.
//   It is therefore guaranteed to be legal to pass a mouse button index in ImGuiPopupFlags.
// - For the same reason, we exceptionally default the ImGuiPopupFlags argument of BeginPopupContextXXX functions to 1 instead of 0.
//   IMPORTANT: because the default parameter is 1 (==ImGuiPopupFlags_MouseButtonRight), if you rely on the default parameter
//   and want to use another flag, you need to pass in the ImGuiPopupFlags_MouseButtonRight flag explicitly.
// - Multiple buttons currently cannot be combined/or-ed in those functions (we could allow it later).
enum ImGuiPopupFlags_
{
    ImGuiPopupFlags_None                    = 0,
    ImGuiPopupFlags_MouseButtonLeft         = 0,        // For BeginPopupContext*(): open on Left Mouse release. Guaranteed to always be == 0 (same as ImGuiMouseButton_Left)
    ImGuiPopupFlags_MouseButtonRight        = 1,        // For BeginPopupContext*(): open on Right Mouse release. Guaranteed to always be == 1 (same as ImGuiMouseButton_Right)
    ImGuiPopupFlags_MouseButtonMiddle       = 2,        // For BeginPopupContext*(): open on Middle Mouse release. Guaranteed to always be == 2 (same as ImGuiMouseButton_Middle)
    ImGuiPopupFlags_MouseButtonMask_        = 0x1F,
    ImGuiPopupFlags_MouseButtonDefault_     = 1,
    ImGuiPopupFlags_NoReopen                = 1 << 5,   // For OpenPopup*(), BeginPopupContext*(): don't reopen same popup if already open (won't reposition, won't reinitialize navigation)
    //ImGuiPopupFlags_NoReopenAlwaysNavInit = 1 << 6,   // For OpenPopup*(), BeginPopupContext*(): focus and initialize navigation even when not reopening.
    ImGuiPopupFlags_NoOpenOverExistingPopup = 1 << 7,   // For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
    ImGuiPopupFlags_NoOpenOverItems         = 1 << 8,   // For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
    ImGuiPopupFlags_AnyPopupId              = 1 << 10,  // For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
    ImGuiPopupFlags_AnyPopupLevel           = 1 << 11,  // For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
    ImGuiPopupFlags_AnyPopup                = ImGuiPopupFlags_AnyPopupId | ImGuiPopupFlags_AnyPopupLevel,
};

// Flags for ImGui::Selectable()
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None               = 0,
    ImGuiSelectableFlags_NoAutoClosePopups  = 1 << 0,   // Clicking this doesn't close parent popup window (overrides ImGuiItemFlags_AutoClosePopups)
    ImGuiSelectableFlags_SpanAllColumns     = 1 << 1,   // Frame will span all columns of its container table (text will still fit in current column)
    ImGuiSelectableFlags_AllowDoubleClick   = 1 << 2,   // Generate press events on double clicks too
    ImGuiSelectableFlags_Disabled           = 1 << 3,   // Cannot be selected, display grayed out text
    ImGuiSelectableFlags_AllowOverlap       = 1 << 4,   // (WIP) Hit testing to allow subsequent widgets to overlap this one
    ImGuiSelectableFlags_Highlight          = 1 << 5,   // Make the item be displayed as if it is hovered





};

// Flags for ImGui::BeginCombo()
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None                    = 0,
    ImGuiComboFlags_PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
    ImGuiComboFlags_HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    ImGuiComboFlags_HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
    ImGuiComboFlags_HeightLarge             = 1 << 3,   // Max ~20 items visible
    ImGuiComboFlags_HeightLargest           = 1 << 4,   // As many fitting items as possible
    ImGuiComboFlags_NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
    ImGuiComboFlags_NoPreview               = 1 << 6,   // Display only a square arrow button
    ImGuiComboFlags_WidthFitPreview         = 1 << 7,   // Width dynamically calculated from preview contents
    ImGuiComboFlags_HeightMask_             = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest,
};

// Flags for ImGui::BeginTabBar()
enum ImGuiTabBarFlags_
{
    ImGuiTabBarFlags_None                           = 0,
    ImGuiTabBarFlags_Reorderable                    = 1 << 0,   // Allow manually dragging tabs to re-order them + New tabs are appended at the end of list
    ImGuiTabBarFlags_AutoSelectNewTabs              = 1 << 1,   // Automatically select new tabs when they appear
    ImGuiTabBarFlags_TabListPopupButton             = 1 << 2,   // Disable buttons to open the tab list popup
    ImGuiTabBarFlags_NoCloseWithMiddleMouseButton   = 1 << 3,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabBarFlags_NoTabListScrollingButtons      = 1 << 4,   // Disable scrolling buttons (apply when fitting policy is ImGuiTabBarFlags_FittingPolicyScroll)
    ImGuiTabBarFlags_NoTooltip                      = 1 << 5,   // Disable tooltips when hovering a tab
    ImGuiTabBarFlags_DrawSelectedOverline           = 1 << 6,   // Draw selected overline markers over selected tab
    ImGuiTabBarFlags_FittingPolicyResizeDown        = 1 << 7,   // Resize tabs when they don't fit
    ImGuiTabBarFlags_FittingPolicyScroll            = 1 << 8,   // Add scroll buttons when tabs don't fit
    ImGuiTabBarFlags_FittingPolicyMask_             = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
    ImGuiTabBarFlags_FittingPolicyDefault_          = ImGuiTabBarFlags_FittingPolicyResizeDown,
};

// Flags for ImGui::BeginTabItem()
enum ImGuiTabItemFlags_
{
    ImGuiTabItemFlags_None                          = 0,
    ImGuiTabItemFlags_UnsavedDocument               = 1 << 0,   // Display a dot next to the title + set ImGuiTabItemFlags_NoAssumedClosure.
    ImGuiTabItemFlags_SetSelected                   = 1 << 1,   // Trigger flag to programmatically make the tab selected when calling BeginTabItem()
    ImGuiTabItemFlags_NoCloseWithMiddleMouseButton  = 1 << 2,   // Disable behavior of closing tabs (that are submitted with p_open != NULL) with middle mouse button. You may handle this behavior manually on user's side with if (IsItemHovered() && IsMouseClicked(2)) *p_open = false.
    ImGuiTabItemFlags_NoPushId                      = 1 << 3,   // Don't call PushID()/PopID() on BeginTabItem()/EndTabItem()
    ImGuiTabItemFlags_NoTooltip                     = 1 << 4,   // Disable tooltip for the given tab
    ImGuiTabItemFlags_NoReorder                     = 1 << 5,   // Disable reordering this tab or having another tab cross over this tab
    ImGuiTabItemFlags_Leading                       = 1 << 6,   // Enforce the tab position to the left of the tab bar (after the tab list popup button)
    ImGuiTabItemFlags_Trailing                      = 1 << 7,   // Enforce the tab position to the right of the tab bar (before the scrolling buttons)
    ImGuiTabItemFlags_NoAssumedClosure              = 1 << 8,   // Tab is selected when trying to close + closure is not immediately assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
};

// Flags for ImGui::IsWindowFocused()
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None                          = 0,
    ImGuiFocusedFlags_ChildWindows                  = 1 << 0,   // Return true if any children of the window is focused
    ImGuiFocusedFlags_RootWindow                    = 1 << 1,   // Test from root window (top most parent of the current hierarchy)
    ImGuiFocusedFlags_AnyWindow                     = 1 << 2,   // Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
    ImGuiFocusedFlags_NoPopupHierarchy              = 1 << 3,   // Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    ImGuiFocusedFlags_DockHierarchy                 = 1 << 4,   // Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiFocusedFlags_RootAndChildWindows           = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows,
};

// Flags for ImGui::IsItemHovered(), ImGui::IsWindowHovered()
// Note: if you are trying to check whether your mouse should be dispatched to Dear ImGui or to your app, you should use 'io.WantCaptureMouse' instead! Please read the FAQ!
// Note: windows with the ImGuiWindowFlags_NoInputs flag are ignored by IsWindowHovered() calls.
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    ImGuiHoveredFlags_ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    ImGuiHoveredFlags_RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    ImGuiHoveredFlags_AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    ImGuiHoveredFlags_NoPopupHierarchy              = 1 << 3,   // IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
    ImGuiHoveredFlags_DockHierarchy                 = 1 << 4,   // IsWindowHovered() only: Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
    ImGuiHoveredFlags_AllowWhenBlockedByPopup       = 1 << 5,   // Return true even if a popup window is normally blocking access to this item/window
    //ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 6,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem  = 1 << 7,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    ImGuiHoveredFlags_AllowWhenOverlappedByItem     = 1 << 8,   // IsItemHovered() only: Return true even if the item uses AllowOverlap mode and is overlapped by another hoverable item.
    ImGuiHoveredFlags_AllowWhenOverlappedByWindow   = 1 << 9,   // IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window.
    ImGuiHoveredFlags_AllowWhenDisabled             = 1 << 10,  // IsItemHovered() only: Return true even if the item is disabled
    ImGuiHoveredFlags_NoNavOverride                 = 1 << 11,  // IsItemHovered() only: Disable using keyboard/gamepad navigation state when active, always query mouse
    ImGuiHoveredFlags_AllowWhenOverlapped           = ImGuiHoveredFlags_AllowWhenOverlappedByItem | ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
    ImGuiHoveredFlags_RectOnly                      = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows           = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows,

    // Tooltips mode
    // - typically used in IsItemHovered() + SetTooltip() sequence.
    // - this is a shortcut to pull flags from 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' where you can reconfigure desired behavior.
    //   e.g. 'TooltipHoveredFlagsForMouse' defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'.
    // - for frequently actioned or hovered items providing a tooltip, you want may to use ImGuiHoveredFlags_ForTooltip (stationary + delay) so the tooltip doesn't show too often.
    // - for items which main purpose is to be hovered, or items with low affordance, or in less consistent apps, prefer no delay or shorter delay.
    ImGuiHoveredFlags_ForTooltip                    = 1 << 12,  // Shortcut for standard flags when using IsItemHovered() + SetTooltip() sequence.

    // (Advanced) Mouse Hovering delays.
    // - generally you can use ImGuiHoveredFlags_ForTooltip to use application-standardized flags.
    // - use those if you need specific overrides.
    ImGuiHoveredFlags_Stationary                    = 1 << 13,  // Require mouse to be stationary for style.HoverStationaryDelay (~0.15 sec) _at least one time_. After this, can move on same item/window. Using the stationary test tends to reduces the need for a long delay.
    ImGuiHoveredFlags_DelayNone                     = 1 << 14,  // IsItemHovered() only: Return true immediately (default). As this is the default you generally ignore this.
    ImGuiHoveredFlags_DelayShort                    = 1 << 15,  // IsItemHovered() only: Return true after style.HoverDelayShort elapsed (~0.15 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_DelayNormal                   = 1 << 16,  // IsItemHovered() only: Return true after style.HoverDelayNormal elapsed (~0.40 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
    ImGuiHoveredFlags_NoSharedDelay                 = 1 << 17,  // IsItemHovered() only: Disable shared delay system where moving from one item to the next keeps the previous timer for a short time (standard for tooltips with long delays)
};

// Flags for ImGui::DockSpace(), shared/inherited by child nodes.
// (Some flags can be applied to individual nodes directly)
// FIXME-DOCK: Also see ImGuiDockNodeFlagsPrivate_ which may involve using the WIP and internal DockBuilder api.
enum ImGuiDockNodeFlags_
{
    ImGuiDockNodeFlags_None                         = 0,
    ImGuiDockNodeFlags_KeepAliveOnly                = 1 << 0,   //       // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
    //ImGuiDockNodeFlags_NoCentralNode              = 1 << 1,   //       // Disable Central Node (the node which can stay empty)
    ImGuiDockNodeFlags_NoDockingOverCentralNode     = 1 << 2,   //       // Disable docking over the Central Node, which will be always kept empty.
    ImGuiDockNodeFlags_PassthruCentralNode          = 1 << 3,   //       // Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
    ImGuiDockNodeFlags_NoDockingSplit               = 1 << 4,   //       // Disable other windows/nodes from splitting this node.
    ImGuiDockNodeFlags_NoResize                     = 1 << 5,   // Saved // Disable resizing node using the splitter/separators. Useful with programmatically setup dockspaces.
    ImGuiDockNodeFlags_AutoHideTabBar               = 1 << 6,   //       // Tab bar will automatically hide when there is a single window in the dock node.
    ImGuiDockNodeFlags_NoUndocking                  = 1 << 7,   //       // Disable undocking this node.





};

// Flags for ImGui::BeginDragDropSource(), ImGui::AcceptDragDropPayload()
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None                         = 0,
    // BeginDragDropSource() flags
    ImGuiDragDropFlags_SourceNoPreviewTooltip       = 1 << 0,   // Disable preview tooltip. By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disables this behavior.
    ImGuiDragDropFlags_SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disables this behavior so you can still call IsItemHovered() on the source item.
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    ImGuiDragDropFlags_SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
    ImGuiDragDropFlags_SourceExtern                 = 1 << 4,   // External source (from outside of dear imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    ImGuiDragDropFlags_PayloadAutoExpire            = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
    ImGuiDragDropFlags_PayloadNoCrossContext        = 1 << 6,   // Hint to specify that the payload may not be copied outside current dear imgui context.
    ImGuiDragDropFlags_PayloadNoCrossProcess        = 1 << 7,   // Hint to specify that the payload may not be copied outside current process.
    // AcceptDragDropPayload() flags
    ImGuiDragDropFlags_AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
    ImGuiDragDropFlags_AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    ImGuiDragDropFlags_AcceptPeekOnly               = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect, // For peeking ahead and inspecting the payload before delivery.




};

// Standard Drag and Drop payload types. You can define you own payload types using short strings. Types starting with '_' are defined by Dear ImGui.



// A primary data type
enum ImGuiDataType_
{
    ImGuiDataType_S8,       // signed char / char (with sensible compilers)
    ImGuiDataType_U8,       // unsigned char
    ImGuiDataType_S16,      // short
    ImGuiDataType_U16,      // unsigned short
    ImGuiDataType_S32,      // int
    ImGuiDataType_U32,      // unsigned int
    ImGuiDataType_S64,      // long long / __int64
    ImGuiDataType_U64,      // unsigned long long / unsigned __int64
    ImGuiDataType_Float,    // float
    ImGuiDataType_Double,   // double
    ImGuiDataType_Bool,     // bool (provided for user convenience, not supported by scalar widgets)
    ImGuiDataType_String,   // char* (provided for user convenience, not supported by scalar widgets)
    ImGuiDataType_COUNT
};

// A cardinal direction
enum ImGuiDir : int
{
    ImGuiDir_None    = -1,
    ImGuiDir_Left    = 0,
    ImGuiDir_Right   = 1,
    ImGuiDir_Up      = 2,
    ImGuiDir_Down    = 3,
    ImGuiDir_COUNT
};

// A sorting direction
enum ImGuiSortDirection : ImU8
{
    ImGuiSortDirection_None         = 0,
    ImGuiSortDirection_Ascending    = 1,    // Ascending = 0->9, A->Z etc.
    ImGuiSortDirection_Descending   = 2     // Descending = 9->0, Z->A etc.
};

// A key identifier (ImGuiKey_XXX or ImGuiMod_XXX value): can represent Keyboard, Mouse and Gamepad values.
// All our named keys are >= 512. Keys value 0 to 511 are left unused and were legacy native/opaque key values (< 1.87).
// Support for legacy keys was completely removed in 1.91.5.
// Read details about the 1.87+ transition : https://github.com/ocornut/imgui/issues/4921
// Note that "Keys" related to physical keys and are not the same concept as input "Characters", the later are submitted via io.AddInputCharacter().
// The keyboard key enum values are named after the keys on a standard US keyboard, and on other keyboard types the keys reported may not match the keycaps.
enum ImGuiKey : int
{
    // Keyboard
    ImGuiKey_None = 0,
    ImGuiKey_NamedKey_BEGIN = 512,  // First valid key value (other than 0)

    ImGuiKey_Tab = 512,             // == ImGuiKey_NamedKey_BEGIN
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_LeftCtrl, ImGuiKey_LeftShift, ImGuiKey_LeftAlt, ImGuiKey_LeftSuper,
    ImGuiKey_RightCtrl, ImGuiKey_RightShift, ImGuiKey_RightAlt, ImGuiKey_RightSuper,
    ImGuiKey_Menu,
    ImGuiKey_0, ImGuiKey_1, ImGuiKey_2, ImGuiKey_3, ImGuiKey_4, ImGuiKey_5, ImGuiKey_6, ImGuiKey_7, ImGuiKey_8, ImGuiKey_9,
    ImGuiKey_A, ImGuiKey_B, ImGuiKey_C, ImGuiKey_D, ImGuiKey_E, ImGuiKey_F, ImGuiKey_G, ImGuiKey_H, ImGuiKey_I, ImGuiKey_J,
    ImGuiKey_K, ImGuiKey_L, ImGuiKey_M, ImGuiKey_N, ImGuiKey_O, ImGuiKey_P, ImGuiKey_Q, ImGuiKey_R, ImGuiKey_S, ImGuiKey_T,
    ImGuiKey_U, ImGuiKey_V, ImGuiKey_W, ImGuiKey_X, ImGuiKey_Y, ImGuiKey_Z,
    ImGuiKey_F1, ImGuiKey_F2, ImGuiKey_F3, ImGuiKey_F4, ImGuiKey_F5, ImGuiKey_F6,
    ImGuiKey_F7, ImGuiKey_F8, ImGuiKey_F9, ImGuiKey_F10, ImGuiKey_F11, ImGuiKey_F12,
    ImGuiKey_F13, ImGuiKey_F14, ImGuiKey_F15, ImGuiKey_F16, ImGuiKey_F17, ImGuiKey_F18,
    ImGuiKey_F19, ImGuiKey_F20, ImGuiKey_F21, ImGuiKey_F22, ImGuiKey_F23, ImGuiKey_F24,
    ImGuiKey_Apostrophe,        // '
    ImGuiKey_Comma,             // ,
    ImGuiKey_Minus,             // -
    ImGuiKey_Period,            // .
    ImGuiKey_Slash,             // /
    ImGuiKey_Semicolon,         // ;
    ImGuiKey_Equal,             // =
    ImGuiKey_LeftBracket,       // [
    ImGuiKey_Backslash,         // \ (this text inhibit multiline comment caused by backslash)
    ImGuiKey_RightBracket,      // ]
    ImGuiKey_GraveAccent,       // `
    ImGuiKey_CapsLock,
    ImGuiKey_ScrollLock,
    ImGuiKey_NumLock,
    ImGuiKey_PrintScreen,
    ImGuiKey_Pause,
    ImGuiKey_Keypad0, ImGuiKey_Keypad1, ImGuiKey_Keypad2, ImGuiKey_Keypad3, ImGuiKey_Keypad4,
    ImGuiKey_Keypad5, ImGuiKey_Keypad6, ImGuiKey_Keypad7, ImGuiKey_Keypad8, ImGuiKey_Keypad9,
    ImGuiKey_KeypadDecimal,
    ImGuiKey_KeypadDivide,
    ImGuiKey_KeypadMultiply,
    ImGuiKey_KeypadSubtract,
    ImGuiKey_KeypadAdd,
    ImGuiKey_KeypadEnter,
    ImGuiKey_KeypadEqual,
    ImGuiKey_AppBack,               // Available on some keyboard/mouses. Often referred as "Browser Back"
    ImGuiKey_AppForward,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    ImGuiKey_GamepadStart,          // Menu (Xbox)      + (Switch)   Start/Options (PS)
    ImGuiKey_GamepadBack,           // View (Xbox)      - (Switch)   Share (PS)
    ImGuiKey_GamepadFaceLeft,       // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    ImGuiKey_GamepadFaceRight,      // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    ImGuiKey_GamepadFaceUp,         // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    ImGuiKey_GamepadFaceDown,       // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    ImGuiKey_GamepadDpadLeft,       // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadRight,      // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadUp,         // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadDpadDown,       // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    ImGuiKey_GamepadL1,             // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    ImGuiKey_GamepadR1,             // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    ImGuiKey_GamepadL2,             // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    ImGuiKey_GamepadR2,             // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    ImGuiKey_GamepadL3,             // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    ImGuiKey_GamepadR3,             // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    ImGuiKey_GamepadLStickLeft,     // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickRight,    // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickUp,       // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadLStickDown,     // [Analog]                                         // Move Window (in Windowing mode)
    ImGuiKey_GamepadRStickLeft,     // [Analog]
    ImGuiKey_GamepadRStickRight,    // [Analog]
    ImGuiKey_GamepadRStickUp,       // [Analog]
    ImGuiKey_GamepadRStickDown,     // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    ImGuiKey_MouseLeft, ImGuiKey_MouseRight, ImGuiKey_MouseMiddle, ImGuiKey_MouseX1, ImGuiKey_MouseX2, ImGuiKey_MouseWheelX, ImGuiKey_MouseWheelY,

    // [Internal] Reserved for mod storage
    ImGuiKey_ReservedForModCtrl, ImGuiKey_ReservedForModShift, ImGuiKey_ReservedForModAlt, ImGuiKey_ReservedForModSuper,
    ImGuiKey_NamedKey_END,

    // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
    // - This is mirroring the data also written to io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper, in a format allowing
    //   them to be accessed via standard key API, allowing calls such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
    // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
    //   and prefer using the real keys (e.g. ImGuiKey_LeftCtrl, ImGuiKey_RightCtrl instead of ImGuiMod_Ctrl).
    // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
    //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
    //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
    // - On macOS, we swap Cmd(Super) and Ctrl keys at the time of the io.AddKeyEvent() call.
    ImGuiMod_None                   = 0,
    ImGuiMod_Ctrl                   = 1 << 12, // Ctrl (non-macOS), Cmd (macOS)
    ImGuiMod_Shift                  = 1 << 13, // Shift
    ImGuiMod_Alt                    = 1 << 14, // Option/Menu
    ImGuiMod_Super                  = 1 << 15, // Windows/Super (non-macOS), Ctrl (macOS)
    ImGuiMod_Mask_                  = 0xF000,  // 4-bits

    // [Internal] If you need to iterate all keys (for e.g. an input mapper) you may use ImGuiKey_NamedKey_BEGIN..ImGuiKey_NamedKey_END.
    ImGuiKey_NamedKey_COUNT         = ImGuiKey_NamedKey_END - ImGuiKey_NamedKey_BEGIN,
    //ImGuiKey_KeysData_SIZE        = ImGuiKey_NamedKey_COUNT,  // Size of KeysData[]: only hold named keys
    //ImGuiKey_KeysData_OFFSET      = ImGuiKey_NamedKey_BEGIN,  // Accesses to io.KeysData[] must use (key - ImGuiKey_NamedKey_BEGIN) index.







};

// Flags for Shortcut(), SetNextItemShortcut(),
// (and for upcoming extended versions of IsKeyPressed(), IsMouseClicked(), Shortcut(), SetKeyOwner(), SetItemKeyOwner() that are still in imgui_internal.h)
// Don't mistake with ImGuiInputTextFlags! (which is for ImGui::InputText() function)
enum ImGuiInputFlags_
{
    ImGuiInputFlags_None                    = 0,
    ImGuiInputFlags_Repeat                  = 1 << 0,   // Enable repeat. Return true on successive repeats. Default for legacy IsKeyPressed(). NOT Default for legacy IsMouseClicked(). MUST BE == 1.

    // Flags for Shortcut(), SetNextItemShortcut()
    // - Routing policies: RouteGlobal+OverActive >> RouteActive or RouteFocused (if owner is active item) >> RouteGlobal+OverFocused >> RouteFocused (if in focused window stack) >> RouteGlobal.
    // - Default policy is RouteFocused. Can select only 1 policy among all available.
    ImGuiInputFlags_RouteActive             = 1 << 10,  // Route to active item only.
    ImGuiInputFlags_RouteFocused            = 1 << 11,  // Route to windows in the focus stack (DEFAULT). Deep-most focused window takes inputs. Active item takes inputs over deep-most focused window.
    ImGuiInputFlags_RouteGlobal             = 1 << 12,  // Global route (unless a focused window or active item registered the route).
    ImGuiInputFlags_RouteAlways             = 1 << 13,  // Do not register route, poll keys directly.
    // - Routing options
    ImGuiInputFlags_RouteOverFocused        = 1 << 14,  // Option: global route: higher priority than focused route (unless active item in focused route).
    ImGuiInputFlags_RouteOverActive         = 1 << 15,  // Option: global route: higher priority than active item. Unlikely you need to use that: will interfere with every active items, e.g. CTRL+A registered by InputText will be overridden by this. May not be fully honored as user/internal code is likely to always assume they can access keys when active.
    ImGuiInputFlags_RouteUnlessBgFocused    = 1 << 16,  // Option: global route: will not be applied if underlying background/void is focused (== no Dear ImGui windows are focused). Useful for overlay applications.
    ImGuiInputFlags_RouteFromRootWindow     = 1 << 17,  // Option: route evaluated from the point of view of root window rather than current window.

    // Flags for SetNextItemShortcut()
    ImGuiInputFlags_Tooltip                 = 1 << 18,  // Automatically display a tooltip when hovering item [BETA] Unsure of right api (opt-in/opt-out)
};

// Configuration flags stored in io.ConfigFlags. Set by user/application.
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_None                   = 0,
    ImGuiConfigFlags_NavEnableKeyboard      = 1 << 0,   // Master keyboard navigation enable flag. Enable full Tabbing + directional arrows + space/enter to activate.
    ImGuiConfigFlags_NavEnableGamepad       = 1 << 1,   // Master gamepad navigation enable flag. Backend also needs to set ImGuiBackendFlags_HasGamepad.
    ImGuiConfigFlags_NoMouse                = 1 << 4,   // Instruct dear imgui to disable mouse inputs and interactions.
    ImGuiConfigFlags_NoMouseCursorChange    = 1 << 5,   // Instruct backend to not alter mouse cursor shape and visibility. Use if the backend cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.
    ImGuiConfigFlags_NoKeyboard             = 1 << 6,   // Instruct dear imgui to disable keyboard inputs and interactions. This is done by ignoring keyboard events and clearing existing states.

    // [BETA] Docking
    ImGuiConfigFlags_DockingEnable          = 1 << 7,   // Docking enable flags.

    // [BETA] Viewports
    // When using viewports it is recommended that your default value for ImGuiCol_WindowBg is opaque (Alpha=1.0) so transition to a viewport won't be noticeable.
    ImGuiConfigFlags_ViewportsEnable        = 1 << 10,  // Viewport enable flags (require both ImGuiBackendFlags_PlatformHasViewports + ImGuiBackendFlags_RendererHasViewports set by the respective backends)
    ImGuiConfigFlags_DpiEnableScaleViewports= 1 << 14,  // [BETA: Don't use] FIXME-DPI: Reposition and resize imgui windows when the DpiScale of a viewport changed (mostly useful for the main viewport hosting other window). Note that resizing the main window itself is up to your application.
    ImGuiConfigFlags_DpiEnableScaleFonts    = 1 << 15,  // [BETA: Don't use] FIXME-DPI: Request bitmap-scaled fonts to match DpiScale. This is a very low-quality workaround. The correct way to handle DPI is _currently_ to replace the atlas and/or fonts in the Platform_OnChangedViewport callback, but this is all early work in progress.

    // User storage (to allow your backend/engine to communicate to code that may be shared between multiple projects. Those flags are NOT used by core Dear ImGui)
    ImGuiConfigFlags_IsSRGB                 = 1 << 20,  // Application is SRGB-aware.
    ImGuiConfigFlags_IsTouchScreen          = 1 << 21,  // Application is using a touch screen instead of a mouse.





};

// Backend capabilities flags stored in io.BackendFlags. Set by imgui_impl_xxx or custom backend.
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_None                  = 0,
    ImGuiBackendFlags_HasGamepad            = 1 << 0,   // Backend Platform supports gamepad and currently has one connected.
    ImGuiBackendFlags_HasMouseCursors       = 1 << 1,   // Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
    ImGuiBackendFlags_HasSetMousePos        = 1 << 2,   // Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if io.ConfigNavMoveSetMousePos is set).
    ImGuiBackendFlags_RendererHasVtxOffset  = 1 << 3,   // Backend Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.

    // [BETA] Viewports
    ImGuiBackendFlags_PlatformHasViewports  = 1 << 10,  // Backend Platform supports multiple viewports.
    ImGuiBackendFlags_HasMouseHoveredViewport=1 << 11,  // Backend Platform supports calling io.AddMouseViewportEvent() with the viewport under the mouse. IF POSSIBLE, ignore viewports with the ImGuiViewportFlags_NoInputs flag (Win32 backend, GLFW 3.30+ backend can do this, SDL backend cannot). If this cannot be done, Dear ImGui needs to use a flawed heuristic to find the viewport under.
    ImGuiBackendFlags_RendererHasViewports  = 1 << 12,  // Backend Renderer supports multiple viewports.
};

// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,              // Background of normal windows
    ImGuiCol_ChildBg,               // Background of child windows
    ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,               // Title bar
    ImGuiCol_TitleBgActive,         // Title bar when focused
    ImGuiCol_TitleBgCollapsed,      // Title bar when collapsed
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark,             // Checkbox tick and RadioButton circle
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
    ImGuiCol_ResizeGrip,            // Resize grip in lower-right and lower-left corners of windows.
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_TabHovered,            // Tab background, when hovered
    ImGuiCol_Tab,                   // Tab background, when tab-bar is focused & tab is unselected
    ImGuiCol_TabSelected,           // Tab background, when tab-bar is focused & tab is selected
    ImGuiCol_TabSelectedOverline,   // Tab horizontal overline, when tab-bar is focused & tab is selected
    ImGuiCol_TabDimmed,             // Tab background, when tab-bar is unfocused & tab is unselected
    ImGuiCol_TabDimmedSelected,     // Tab background, when tab-bar is unfocused & tab is selected
    ImGuiCol_TabDimmedSelectedOverline,//..horizontal overline, when tab-bar is unfocused & tab is selected
    ImGuiCol_DockingPreview,        // Preview overlay color when about to docking something
    ImGuiCol_DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TableHeaderBg,         // Table header background
    ImGuiCol_TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
    ImGuiCol_TableRowBg,            // Table row background (even rows)
    ImGuiCol_TableRowBgAlt,         // Table row background (odd rows)
    ImGuiCol_TextLink,              // Hyperlink color
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,        // Rectangle highlighting a drop target
    ImGuiCol_NavCursor,             // Color of keyboard/gamepad navigation cursor/rectangle, when visible
    ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
    ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    ImGuiCol_COUNT,







};

// Enumeration for PushStyleVar() / PopStyleVar() to temporarily modify the ImGuiStyle structure.
// - The enum only refers to fields of ImGuiStyle which makes sense to be pushed/popped inside UI code.
//   During initialization or between frames, feel free to just poke into ImGuiStyle directly.
// - Tip: Use your programming IDE navigation facilities on the names in the _second column_ below to find the actual members and their description.
//   - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
//   - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
//   - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
// - When changing this enum, you need to update the associated internal table GStyleVarInfo[] accordingly. This is where we link enum values to members offset/type.
enum ImGuiStyleVar_
{
    // Enum name -------------------------- // Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    ImGuiStyleVar_Alpha,                    // float     Alpha
    ImGuiStyleVar_DisabledAlpha,            // float     DisabledAlpha
    ImGuiStyleVar_WindowPadding,            // ImVec2    WindowPadding
    ImGuiStyleVar_WindowRounding,           // float     WindowRounding
    ImGuiStyleVar_WindowBorderSize,         // float     WindowBorderSize
    ImGuiStyleVar_WindowMinSize,            // ImVec2    WindowMinSize
    ImGuiStyleVar_WindowTitleAlign,         // ImVec2    WindowTitleAlign
    ImGuiStyleVar_ChildRounding,            // float     ChildRounding
    ImGuiStyleVar_ChildBorderSize,          // float     ChildBorderSize
    ImGuiStyleVar_PopupRounding,            // float     PopupRounding
    ImGuiStyleVar_PopupBorderSize,          // float     PopupBorderSize
    ImGuiStyleVar_FramePadding,             // ImVec2    FramePadding
    ImGuiStyleVar_FrameRounding,            // float     FrameRounding
    ImGuiStyleVar_FrameBorderSize,          // float     FrameBorderSize
    ImGuiStyleVar_ItemSpacing,              // ImVec2    ItemSpacing
    ImGuiStyleVar_ItemInnerSpacing,         // ImVec2    ItemInnerSpacing
    ImGuiStyleVar_IndentSpacing,            // float     IndentSpacing
    ImGuiStyleVar_CellPadding,              // ImVec2    CellPadding
    ImGuiStyleVar_ScrollbarSize,            // float     ScrollbarSize
    ImGuiStyleVar_ScrollbarRounding,        // float     ScrollbarRounding
    ImGuiStyleVar_GrabMinSize,              // float     GrabMinSize
    ImGuiStyleVar_GrabRounding,             // float     GrabRounding
    ImGuiStyleVar_TabRounding,              // float     TabRounding
    ImGuiStyleVar_TabBorderSize,            // float     TabBorderSize
    ImGuiStyleVar_TabBarBorderSize,         // float     TabBarBorderSize
    ImGuiStyleVar_TabBarOverlineSize,       // float     TabBarOverlineSize
    ImGuiStyleVar_TableAngledHeadersAngle,  // float     TableAngledHeadersAngle
    ImGuiStyleVar_TableAngledHeadersTextAlign,// ImVec2  TableAngledHeadersTextAlign
    ImGuiStyleVar_ButtonTextAlign,          // ImVec2    ButtonTextAlign
    ImGuiStyleVar_SelectableTextAlign,      // ImVec2    SelectableTextAlign
    ImGuiStyleVar_SeparatorTextBorderSize,  // float     SeparatorTextBorderSize
    ImGuiStyleVar_SeparatorTextAlign,       // ImVec2    SeparatorTextAlign
    ImGuiStyleVar_SeparatorTextPadding,     // ImVec2    SeparatorTextPadding
    ImGuiStyleVar_DockingSeparatorSize,     // float     DockingSeparatorSize
    ImGuiStyleVar_COUNT
};

// Flags for InvisibleButton() [extended in imgui_internal.h]
enum ImGuiButtonFlags_
{
    ImGuiButtonFlags_None                   = 0,
    ImGuiButtonFlags_MouseButtonLeft        = 1 << 0,   // React on left mouse button (default)
    ImGuiButtonFlags_MouseButtonRight       = 1 << 1,   // React on right mouse button
    ImGuiButtonFlags_MouseButtonMiddle      = 1 << 2,   // React on center mouse button
    ImGuiButtonFlags_MouseButtonMask_       = ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight | ImGuiButtonFlags_MouseButtonMiddle, // [Internal]
    ImGuiButtonFlags_EnableNav              = 1 << 3,   // InvisibleButton(): do not disable navigation/tabbing. Otherwise disabled by default.
};

// Flags for ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton()
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None            = 0,
    ImGuiColorEditFlags_NoAlpha         = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (will only read 3 components from the input pointer).
    ImGuiColorEditFlags_NoPicker        = 1 << 2,   //              // ColorEdit: disable picker when clicking on color square.
    ImGuiColorEditFlags_NoOptions       = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    ImGuiColorEditFlags_NoSmallPreview  = 1 << 4,   //              // ColorEdit, ColorPicker: disable color square preview next to the inputs. (e.g. to show only the inputs)
    ImGuiColorEditFlags_NoInputs        = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview color square).
    ImGuiColorEditFlags_NoTooltip       = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    ImGuiColorEditFlags_NoLabel         = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    ImGuiColorEditFlags_NoSidePreview   = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, use small color square preview instead.
    ImGuiColorEditFlags_NoDragDrop      = 1 << 9,   //              // ColorEdit: disable drag and drop target. ColorButton: disable drag and drop source.
    ImGuiColorEditFlags_NoBorder        = 1 << 10,  //              // ColorButton: disable border (which is enforced by default)

    // Alpha preview
    // - Prior to 1.91.8 (2025/01/21): alpha was made opaque in the preview by default using old name ImGuiColorEditFlags_AlphaPreview.
    // - We now display the preview as transparent by default. You can use ImGuiColorEditFlags_AlphaOpaque to use old behavior.
    // - The new flags may be combined better and allow finer controls.
    ImGuiColorEditFlags_AlphaOpaque     = 1 << 11,  //              // ColorEdit, ColorPicker, ColorButton: disable alpha in the preview,. Contrary to _NoAlpha it may still be edited when calling ColorEdit4()/ColorPicker4(). For ColorButton() this does the same as _NoAlpha.
    ImGuiColorEditFlags_AlphaNoBg       = 1 << 12,  //              // ColorEdit, ColorPicker, ColorButton: disable rendering a checkerboard background behind transparent color.
    ImGuiColorEditFlags_AlphaPreviewHalf= 1 << 13,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half transparent preview.

    // User Options (right-click on widget to change some of them).
    ImGuiColorEditFlags_AlphaBar        = 1 << 16,  //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    ImGuiColorEditFlags_HDR             = 1 << 19,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
    ImGuiColorEditFlags_DisplayRGB      = 1 << 20,  // [Display]    // ColorEdit: override _display_ type among RGB/HSV/Hex. ColorPicker: select any combination using one or more of RGB/HSV/Hex.
    ImGuiColorEditFlags_DisplayHSV      = 1 << 21,  // [Display]    // "
    ImGuiColorEditFlags_DisplayHex      = 1 << 22,  // [Display]    // "
    ImGuiColorEditFlags_Uint8           = 1 << 23,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    ImGuiColorEditFlags_Float           = 1 << 24,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    ImGuiColorEditFlags_PickerHueBar    = 1 << 25,  // [Picker]     // ColorPicker: bar for Hue, rectangle for Sat/Value.
    ImGuiColorEditFlags_PickerHueWheel  = 1 << 26,  // [Picker]     // ColorPicker: wheel for Hue, triangle for Sat/Value.
    ImGuiColorEditFlags_InputRGB        = 1 << 27,  // [Input]      // ColorEdit, ColorPicker: input and output data in RGB format.
    ImGuiColorEditFlags_InputHSV        = 1 << 28,  // [Input]      // ColorEdit, ColorPicker: input and output data in HSV format.

    // Defaults Options. You can set application defaults using SetColorEditOptions(). The intent is that you probably don't want to
    // override them in most of your calls. Let the user choose via the option menu and/or call SetColorEditOptions() once during startup.
    ImGuiColorEditFlags_DefaultOptions_ = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,

    // [Internal] Masks
    ImGuiColorEditFlags_AlphaMask_      = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaOpaque | ImGuiColorEditFlags_AlphaNoBg | ImGuiColorEditFlags_AlphaPreviewHalf,
    ImGuiColorEditFlags_DisplayMask_    = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex,
    ImGuiColorEditFlags_DataTypeMask_   = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags_PickerMask_     = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags_InputMask_      = ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_InputHSV,

    // Obsolete names



    //ImGuiColorEditFlags_RGB = ImGuiColorEditFlags_DisplayRGB, ImGuiColorEditFlags_HSV = ImGuiColorEditFlags_DisplayHSV, ImGuiColorEditFlags_HEX = ImGuiColorEditFlags_DisplayHex  // [renamed in 1.69]
};

// Flags for DragFloat(), DragInt(), SliderFloat(), SliderInt() etc.
// We use the same sets of flags for DragXXX() and SliderXXX() functions as the features are the same and it makes it easier to swap them.
// (Those are per-item flags. There is shared behavior flag too: ImGuiIO: io.ConfigDragClickToInputText)
enum ImGuiSliderFlags_
{
    ImGuiSliderFlags_None               = 0,
    ImGuiSliderFlags_Logarithmic        = 1 << 5,       // Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
    ImGuiSliderFlags_NoRoundToFormat    = 1 << 6,       // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits).
    ImGuiSliderFlags_NoInput            = 1 << 7,       // Disable CTRL+Click or Enter key allowing to input text directly into the widget.
    ImGuiSliderFlags_WrapAround         = 1 << 8,       // Enable wrapping around from max to min and from min to max. Only supported by DragXXX() functions for now.
    ImGuiSliderFlags_ClampOnInput       = 1 << 9,       // Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.
    ImGuiSliderFlags_ClampZeroRange     = 1 << 10,      // Clamp even if min==max==0.0f. Otherwise due to legacy reason DragXXX functions don't clamp with those values. When your clamping limits are dynamic you almost always want to use it.
    ImGuiSliderFlags_NoSpeedTweaks      = 1 << 11,      // Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic.
    ImGuiSliderFlags_AlwaysClamp        = ImGuiSliderFlags_ClampOnInput | ImGuiSliderFlags_ClampZeroRange,
    ImGuiSliderFlags_InvalidMask_       = 0x7000000F,   // [Internal] We treat using those bits as being potentially a 'float power' argument from the previous API that has got miscast to this enum, and will trigger an assert if needed.
};

// Identify a mouse button.
// Those values are guaranteed to be stable and we frequently use 0/1 directly. Named enums provided for convenience.
enum ImGuiMouseButton_
{
    ImGuiMouseButton_Left = 0,
    ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2,
    ImGuiMouseButton_COUNT = 5
};

// Enumeration for GetMouseCursor()
// User code may request backend to display given cursor by calling SetMouseCursor(), which is why we have some cursors that are marked unused here
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    ImGuiMouseCursor_ResizeAll,         // (Unused by Dear ImGui functions)
    ImGuiMouseCursor_ResizeNS,          // When hovering over a horizontal border
    ImGuiMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    ImGuiMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    ImGuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Hand,              // (Unused by Dear ImGui functions. Use for e.g. hyperlinks)
    ImGuiMouseCursor_NotAllowed,        // When hovering something with disallowed interaction. Usually a crossed circle.
    ImGuiMouseCursor_COUNT
};

// Enumeration for AddMouseSourceEvent() actual source of Mouse Input data.
// Historically we use "Mouse" terminology everywhere to indicate pointer data, e.g. MousePos, IsMousePressed(), io.AddMousePosEvent()
// But that "Mouse" data can come from different source which occasionally may be useful for application to know about.
// You can submit a change of pointer type using io.AddMouseSourceEvent().
enum ImGuiMouseSource : int
{
    ImGuiMouseSource_Mouse = 0,         // Input is coming from an actual mouse.
    ImGuiMouseSource_TouchScreen,       // Input is coming from a touch screen (no hovering prior to initial press, less precise initial press aiming, dual-axis wheeling possible).
    ImGuiMouseSource_Pen,               // Input is coming from a pressure/magnetic pen (often used in conjunction with high-sampling rates).
    ImGuiMouseSource_COUNT
};

// Enumeration for ImGui::SetNextWindow***(), SetWindow***(), SetNextItem***() functions
// Represent a condition.
// Important: Treat as a regular enum! Do NOT combine multiple values using binary operators! All the functions above treat 0 as a shortcut to ImGuiCond_Always.
enum ImGuiCond_
{
    ImGuiCond_None          = 0,        // No condition (always set the variable), same as _Always
    ImGuiCond_Always        = 1 << 0,   // No condition (always set the variable), same as _None
    ImGuiCond_Once          = 1 << 1,   // Set the variable once per runtime session (only the first call will succeed)
    ImGuiCond_FirstUseEver  = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
    ImGuiCond_Appearing     = 1 << 3,   // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
};

//-----------------------------------------------------------------------------
// [SECTION] Tables API flags and structures (ImGuiTableFlags, ImGuiTableColumnFlags, ImGuiTableRowFlags, ImGuiTableBgTarget, ImGuiTableSortSpecs, ImGuiTableColumnSortSpecs)
//-----------------------------------------------------------------------------

// Flags for ImGui::BeginTable()
// - Important! Sizing policies have complex and subtle side effects, much more so than you would expect.
//   Read comments/demos carefully + experiment with live demos to get acquainted with them.
// - The DEFAULT sizing policies are:
//    - Default to ImGuiTableFlags_SizingFixedFit    if ScrollX is on, or if host window has ImGuiWindowFlags_AlwaysAutoResize.
//    - Default to ImGuiTableFlags_SizingStretchSame if ScrollX is off.
// - When ScrollX is off:
//    - Table defaults to ImGuiTableFlags_SizingStretchSame -> all Columns defaults to ImGuiTableColumnFlags_WidthStretch with same weight.
//    - Columns sizing policy allowed: Stretch (default), Fixed/Auto.
//    - Fixed Columns (if any) will generally obtain their requested width (unless the table cannot fit them all).
//    - Stretch Columns will share the remaining width according to their respective weight.
//    - Mixed Fixed/Stretch columns is possible but has various side-effects on resizing behaviors.
//      The typical use of mixing sizing policies is: any number of LEADING Fixed columns, followed by one or two TRAILING Stretch columns.
//      (this is because the visible order of columns have subtle but necessary effects on how they react to manual resizing).
// - When ScrollX is on:
//    - Table defaults to ImGuiTableFlags_SizingFixedFit -> all Columns defaults to ImGuiTableColumnFlags_WidthFixed
//    - Columns sizing policy allowed: Fixed/Auto mostly.
//    - Fixed Columns can be enlarged as needed. Table will show a horizontal scrollbar if needed.
//    - When using auto-resizing (non-resizable) fixed columns, querying the content width to use item right-alignment e.g. SetNextItemWidth(-FLT_MIN) doesn't make sense, would create a feedback loop.
//    - Using Stretch columns OFTEN DOES NOT MAKE SENSE if ScrollX is on, UNLESS you have specified a value for 'inner_width' in BeginTable().
//      If you specify a value for 'inner_width' then effectively the scrolling space is known and Stretch or mixed Fixed/Stretch columns become meaningful again.
// - Read on documentation at the top of imgui_tables.cpp for details.
enum ImGuiTableFlags_
{
    // Features
    ImGuiTableFlags_None                       = 0,
    ImGuiTableFlags_Resizable                  = 1 << 0,   // Enable resizing columns.
    ImGuiTableFlags_Reorderable                = 1 << 1,   // Enable reordering columns in header row (need calling TableSetupColumn() + TableHeadersRow() to display headers)
    ImGuiTableFlags_Hideable                   = 1 << 2,   // Enable hiding/disabling columns in context menu.
    ImGuiTableFlags_Sortable                   = 1 << 3,   // Enable sorting. Call TableGetSortSpecs() to obtain sort specs. Also see ImGuiTableFlags_SortMulti and ImGuiTableFlags_SortTristate.
    ImGuiTableFlags_NoSavedSettings            = 1 << 4,   // Disable persisting columns order, width and sort settings in the .ini file.
    ImGuiTableFlags_ContextMenuInBody          = 1 << 5,   // Right-click on columns body/contents will display table context menu. By default it is available in TableHeadersRow().
    // Decorations
    ImGuiTableFlags_RowBg                      = 1 << 6,   // Set each RowBg color with ImGuiCol_TableRowBg or ImGuiCol_TableRowBgAlt (equivalent of calling TableSetBgColor with ImGuiTableBgFlags_RowBg0 on each row manually)
    ImGuiTableFlags_BordersInnerH              = 1 << 7,   // Draw horizontal borders between rows.
    ImGuiTableFlags_BordersOuterH              = 1 << 8,   // Draw horizontal borders at the top and bottom.
    ImGuiTableFlags_BordersInnerV              = 1 << 9,   // Draw vertical borders between columns.
    ImGuiTableFlags_BordersOuterV              = 1 << 10,  // Draw vertical borders on the left and right sides.
    ImGuiTableFlags_BordersH                   = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH, // Draw horizontal borders.
    ImGuiTableFlags_BordersV                   = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV, // Draw vertical borders.
    ImGuiTableFlags_BordersInner               = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH, // Draw inner borders.
    ImGuiTableFlags_BordersOuter               = ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersOuterH, // Draw outer borders.
    ImGuiTableFlags_Borders                    = ImGuiTableFlags_BordersInner | ImGuiTableFlags_BordersOuter,   // Draw all borders.
    ImGuiTableFlags_NoBordersInBody            = 1 << 11,  // [ALPHA] Disable vertical borders in columns Body (borders will always appear in Headers). -> May move to style
    ImGuiTableFlags_NoBordersInBodyUntilResize = 1 << 12,  // [ALPHA] Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers). -> May move to style
    // Sizing Policy (read above for defaults)
    ImGuiTableFlags_SizingFixedFit             = 1 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching contents width.
    ImGuiTableFlags_SizingFixedSame            = 2 << 13,  // Columns default to _WidthFixed or _WidthAuto (if resizable or not resizable), matching the maximum contents width of all columns. Implicitly enable ImGuiTableFlags_NoKeepColumnsVisible.
    ImGuiTableFlags_SizingStretchProp          = 3 << 13,  // Columns default to _WidthStretch with default weights proportional to each columns contents widths.
    ImGuiTableFlags_SizingStretchSame          = 4 << 13,  // Columns default to _WidthStretch with default weights all equal, unless overridden by TableSetupColumn().
    // Sizing Extra Options
    ImGuiTableFlags_NoHostExtendX              = 1 << 16,  // Make outer width auto-fit to columns, overriding outer_size.x value. Only available when ScrollX/ScrollY are disabled and Stretch columns are not used.
    ImGuiTableFlags_NoHostExtendY              = 1 << 17,  // Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit). Only available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.
    ImGuiTableFlags_NoKeepColumnsVisible       = 1 << 18,  // Disable keeping column always minimally visible when ScrollX is off and table gets too small. Not recommended if columns are resizable.
    ImGuiTableFlags_PreciseWidths              = 1 << 19,  // Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.
    // Clipping
    ImGuiTableFlags_NoClip                     = 1 << 20,  // Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with TableSetupScrollFreeze().
    // Padding
    ImGuiTableFlags_PadOuterX                  = 1 << 21,  // Default if BordersOuterV is on. Enable outermost padding. Generally desirable if you have headers.
    ImGuiTableFlags_NoPadOuterX                = 1 << 22,  // Default if BordersOuterV is off. Disable outermost padding.
    ImGuiTableFlags_NoPadInnerX                = 1 << 23,  // Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off).
    // Scrolling
    ImGuiTableFlags_ScrollX                    = 1 << 24,  // Enable horizontal scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size. Changes default sizing policy. Because this creates a child window, ScrollY is currently generally recommended when using ScrollX.
    ImGuiTableFlags_ScrollY                    = 1 << 25,  // Enable vertical scrolling. Require 'outer_size' parameter of BeginTable() to specify the container size.
    // Sorting
    ImGuiTableFlags_SortMulti                  = 1 << 26,  // Hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).
    ImGuiTableFlags_SortTristate               = 1 << 27,  // Allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).
    // Miscellaneous
    ImGuiTableFlags_HighlightHoveredColumn     = 1 << 28,  // Highlight column headers when hovered (may evolve into a fuller highlight)

    // [Internal] Combinations and masks
    ImGuiTableFlags_SizingMask_                = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_SizingStretchSame,
};

// Flags for ImGui::TableSetupColumn()
enum ImGuiTableColumnFlags_
{
    // Input configuration flags
    ImGuiTableColumnFlags_None                  = 0,
    ImGuiTableColumnFlags_Disabled              = 1 << 0,   // Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
    ImGuiTableColumnFlags_DefaultHide           = 1 << 1,   // Default as a hidden/disabled column.
    ImGuiTableColumnFlags_DefaultSort           = 1 << 2,   // Default as a sorting column.
    ImGuiTableColumnFlags_WidthStretch          = 1 << 3,   // Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
    ImGuiTableColumnFlags_WidthFixed            = 1 << 4,   // Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
    ImGuiTableColumnFlags_NoResize              = 1 << 5,   // Disable manual resizing.
    ImGuiTableColumnFlags_NoReorder             = 1 << 6,   // Disable manual reordering this column, this will also prevent other columns from crossing over this column.
    ImGuiTableColumnFlags_NoHide                = 1 << 7,   // Disable ability to hide/disable this column.
    ImGuiTableColumnFlags_NoClip                = 1 << 8,   // Disable clipping for this column (all NoClip columns will render in a same draw command).
    ImGuiTableColumnFlags_NoSort                = 1 << 9,   // Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
    ImGuiTableColumnFlags_NoSortAscending       = 1 << 10,  // Disable ability to sort in the ascending direction.
    ImGuiTableColumnFlags_NoSortDescending      = 1 << 11,  // Disable ability to sort in the descending direction.
    ImGuiTableColumnFlags_NoHeaderLabel         = 1 << 12,  // TableHeadersRow() will submit an empty label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers. You may append into this cell by calling TableSetColumnIndex() right after the TableHeadersRow() call.
    ImGuiTableColumnFlags_NoHeaderWidth         = 1 << 13,  // Disable header text width contribution to automatic column width.
    ImGuiTableColumnFlags_PreferSortAscending   = 1 << 14,  // Make the initial sort direction Ascending when first sorting on this column (default).
    ImGuiTableColumnFlags_PreferSortDescending  = 1 << 15,  // Make the initial sort direction Descending when first sorting on this column.
    ImGuiTableColumnFlags_IndentEnable          = 1 << 16,  // Use current Indent value when entering cell (default for column 0).
    ImGuiTableColumnFlags_IndentDisable         = 1 << 17,  // Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
    ImGuiTableColumnFlags_AngledHeader          = 1 << 18,  // TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.

    // Output status flags, read-only via TableGetColumnFlags()
    ImGuiTableColumnFlags_IsEnabled             = 1 << 24,  // Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
    ImGuiTableColumnFlags_IsVisible             = 1 << 25,  // Status: is visible == is enabled AND not clipped by scrolling.
    ImGuiTableColumnFlags_IsSorted              = 1 << 26,  // Status: is currently part of the sort specs
    ImGuiTableColumnFlags_IsHovered             = 1 << 27,  // Status: is hovered by mouse

    // [Internal] Combinations and masks
    ImGuiTableColumnFlags_WidthMask_            = ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_WidthFixed,
    ImGuiTableColumnFlags_IndentMask_           = ImGuiTableColumnFlags_IndentEnable | ImGuiTableColumnFlags_IndentDisable,
    ImGuiTableColumnFlags_StatusMask_           = ImGuiTableColumnFlags_IsEnabled | ImGuiTableColumnFlags_IsVisible | ImGuiTableColumnFlags_IsSorted | ImGuiTableColumnFlags_IsHovered,
    ImGuiTableColumnFlags_NoDirectResize_       = 1 << 30,  // [Internal] Disable user resizing this column directly (it may however we resized indirectly from its left edge)
};

// Flags for ImGui::TableNextRow()
enum ImGuiTableRowFlags_
{
    ImGuiTableRowFlags_None                     = 0,
    ImGuiTableRowFlags_Headers                  = 1 << 0,   // Identify header row (set default background color + width of its contents accounted differently for auto column width)
};

// Enum for ImGui::TableSetBgColor()
// Background colors are rendering in 3 layers:
//  - Layer 0: draw with RowBg0 color if set, otherwise draw with ColumnBg0 if set.
//  - Layer 1: draw with RowBg1 color if set, otherwise draw with ColumnBg1 if set.
//  - Layer 2: draw with CellBg color if set.
// The purpose of the two row/columns layers is to let you decide if a background color change should override or blend with the existing color.
// When using ImGuiTableFlags_RowBg on the table, each row has the RowBg0 color automatically set for odd/even rows.
// If you set the color of RowBg0 target, your color will override the existing RowBg0 color.
// If you set the color of RowBg1 or ColumnBg1 target, your color will blend over the RowBg0 color.
enum ImGuiTableBgTarget_
{
    ImGuiTableBgTarget_None                     = 0,
    ImGuiTableBgTarget_RowBg0                   = 1,        // Set row background color 0 (generally used for background, automatically set when ImGuiTableFlags_RowBg is used)
    ImGuiTableBgTarget_RowBg1                   = 2,        // Set row background color 1 (generally used for selection marking)
    ImGuiTableBgTarget_CellBg                   = 3,        // Set cell background color (top-most color)
};

// Sorting specifications for a table (often handling sort specs for a single column, occasionally more)
// Obtained by calling TableGetSortSpecs().
// When 'SpecsDirty == true' you can sort your data. It will be true with sorting specs have changed since last call, or the first time.
// Make sure to set 'SpecsDirty = false' after sorting, else you may wastefully sort your data every frame!
struct ImGuiTableSortSpecs
{
    const ImGuiTableColumnSortSpecs* Specs;     // Pointer to sort spec array.
    int                         SpecsCount;     // Sort spec count. Most often 1. May be > 1 when ImGuiTableFlags_SortMulti is enabled. May be == 0 when ImGuiTableFlags_SortTristate is enabled.
    bool                        SpecsDirty;     // Set to true when specs have changed since last time! Use this to sort again, then clear the flag.

    ImGuiTableSortSpecs()       { memset(this, 0, sizeof(*this)); }
};

// Sorting specification for one column of a table (sizeof == 12 bytes)
struct ImGuiTableColumnSortSpecs
{
    ImGuiID                     ColumnUserID;       // User id of the column (if specified by a TableSetupColumn() call)
    ImS16                       ColumnIndex;        // Index of the column
    ImS16                       SortOrder;          // Index within parent ImGuiTableSortSpecs (always stored in order starting from 0, tables sorted on a single criteria will always have a 0 here)
    ImGuiSortDirection          SortDirection;      // ImGuiSortDirection_Ascending or ImGuiSortDirection_Descending

    ImGuiTableColumnSortSpecs() { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Helpers: Debug log, memory allocations macros, ImVector<>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Debug Logging into ShowDebugLogWindow(), tty and more.
//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------
// IM_MALLOC(), IM_FREE(), IM_NEW(), IM_PLACEMENT_NEW(), IM_DELETE()
// We call C++ constructor on own allocated memory via the placement "new(ptr) Type()" syntax.
// Defining a custom placement new() with a custom parameter allows us to bypass including <new> which on some platforms complains when user has disabled exceptions.
//-----------------------------------------------------------------------------

struct ImNewWrapper {};
inline void* operator new(size_t, ImNewWrapper, void* ptr) { return ptr; }
inline void  operator delete(void*, ImNewWrapper, void*)   {} // This is only required so we can use the symmetrical new()




template<typename T> void IM_DELETE(T* p)   { if (p) { p->~T(); ImGui::MemFree(p); } }

//-----------------------------------------------------------------------------
// ImVector<>
// Lightweight std::vector<>-like class to avoid dragging dependencies (also, some implementations of STL with debug enabled are absurdly slow, we bypass it so our code runs fast in debug).
//-----------------------------------------------------------------------------
// - You generally do NOT need to care or use this ever. But we need to make it available in imgui.h because some of our public structures are relying on it.
// - We use std-like naming convention here, which is a little unusual for this codebase.
// - Important: clear() frees memory, resize(0) keep the allocated buffer. We use resize(0) a lot to intentionally recycle allocated buffers across frames and amortize our costs.
// - Important: our implementation does NOT call C++ constructors/destructors, we treat everything as raw data! This is intentional but be extra mindful of that,
//   Do NOT use this class as a std::vector replacement in your own code! Many of the structures used by dear imgui can be safely initialized by a zero-memset.
//-----------------------------------------------------------------------------


template<typename T>
struct ImVector
{
    int                 Size;
    int                 Capacity;
    T*                  Data;

    // Provide standard typedefs but we don't use them ourselves.
    typedef T                   value_type;
    typedef value_type*         iterator;
    typedef const value_type*   const_iterator;

    // Constructors, destructor
    inline ImVector()                                       { Size = Capacity = 0; Data = ((void *)0); }
    inline ImVector(const ImVector<T>& src)                 { Size = Capacity = 0; Data = ((void *)0); operator=(src); }
    inline ImVector<T>& operator=(const ImVector<T>& src)   { clear(); resize(src.Size); if (src.Data) memcpy(Data, src.Data, (size_t)Size * sizeof(T)); return *this; }
    inline ~ImVector()                                      { if (Data) ImGui::MemFree(Data); } // Important: does not destruct anything

    inline void         clear()                             { if (Data) { Size = Capacity = 0; ImGui::MemFree(Data); Data = ((void *)0); } }  // Important: does not destruct anything
    inline void         clear_delete()                      { for (int n = 0; n < Size; n++) IM_DELETE(Data[n]); clear(); }     // Important: never called automatically! always explicit.
    inline void         clear_destruct()                    { for (int n = 0; n < Size; n++) Data[n].~T(); clear(); }           // Important: never called automatically! always explicit.

    inline bool         empty() const                       { return Size == 0; }
    inline int          size() const                        { return Size; }
    inline int          size_in_bytes() const               { return Size * (int)sizeof(T); }
    inline int          max_size() const                    { return 0x7FFFFFFF / (int)sizeof(T); }
    inline int          capacity() const                    { return Capacity; }
    inline T&           operator[](int i)                   { (void)( (!!(i >= 0 && i < Size)) || (_wassert(L"i >= 0 && i < Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2173)), 0) ); return Data[i]; }
    inline const T&     operator[](int i) const             { (void)( (!!(i >= 0 && i < Size)) || (_wassert(L"i >= 0 && i < Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2174)), 0) ); return Data[i]; }

    inline T*           begin()                             { return Data; }
    inline const T*     begin() const                       { return Data; }
    inline T*           end()                               { return Data + Size; }
    inline const T*     end() const                         { return Data + Size; }
    inline T&           front()                             { (void)( (!!(Size > 0)) || (_wassert(L"Size > 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2180)), 0) ); return Data[0]; }
    inline const T&     front() const                       { (void)( (!!(Size > 0)) || (_wassert(L"Size > 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2181)), 0) ); return Data[0]; }
    inline T&           back()                              { (void)( (!!(Size > 0)) || (_wassert(L"Size > 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2182)), 0) ); return Data[Size - 1]; }
    inline const T&     back() const                        { (void)( (!!(Size > 0)) || (_wassert(L"Size > 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2183)), 0) ); return Data[Size - 1]; }
    inline void         swap(ImVector<T>& rhs)              { int rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; int rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; T* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }

    inline int          _grow_capacity(int sz) const        { int new_capacity = Capacity ? (Capacity + Capacity / 2) : 8; return new_capacity > sz ? new_capacity : sz; }
    inline void         resize(int new_size)                { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void         resize(int new_size, const T& v)    { if (new_size > Capacity) reserve(_grow_capacity(new_size)); if (new_size > Size) for (int n = Size; n < new_size; n++) memcpy(&Data[n], &v, sizeof(v)); Size = new_size; }
    inline void         shrink(int new_size)                { (void)( (!!(new_size <= Size)) || (_wassert(L"new_size <= Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2189)), 0) ); Size = new_size; } // Resize a vector to a smaller size, guaranteed not to cause a reallocation
    inline void         reserve(int new_capacity)           { if (new_capacity <= Capacity) return; T* new_data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T)); if (Data) { memcpy(new_data, Data, (size_t)Size * sizeof(T)); ImGui::MemFree(Data); } Data = new_data; Capacity = new_capacity; }
    inline void         reserve_discard(int new_capacity)   { if (new_capacity <= Capacity) return; if (Data) ImGui::MemFree(Data); Data = (T*)ImGui::MemAlloc((size_t)new_capacity * sizeof(T)); Capacity = new_capacity; }

    // NB: It is illegal to call push_back/push_front/insert with a reference pointing inside the ImVector data itself! e.g. v.push_back(v[10]) is forbidden.
    inline void         push_back(const T& v)               { if (Size == Capacity) reserve(_grow_capacity(Size + 1)); memcpy(&Data[Size], &v, sizeof(v)); Size++; }
    inline void         pop_back()                          { (void)( (!!(Size > 0)) || (_wassert(L"Size > 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2195)), 0) ); Size--; }
    inline void         push_front(const T& v)              { if (Size == 0) push_back(v); else insert(Data, v); }
    inline T*           erase(const T* it)                  { (void)( (!!(it >= Data && it < Data + Size)) || (_wassert(L"it >= Data && it < Data + Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2197)), 0) ); const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + 1, ((size_t)Size - (size_t)off - 1) * sizeof(T)); Size--; return Data + off; }
    inline T*           erase(const T* it, const T* it_last){ (void)( (!!(it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size)) || (_wassert(L"it >= Data && it < Data + Size && it_last >= it && it_last <= Data + Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2198)), 0) ); const ptrdiff_t count = it_last - it; const ptrdiff_t off = it - Data; memmove(Data + off, Data + off + count, ((size_t)Size - (size_t)off - (size_t)count) * sizeof(T)); Size -= (int)count; return Data + off; }
    inline T*           erase_unsorted(const T* it)         { (void)( (!!(it >= Data && it < Data + Size)) || (_wassert(L"it >= Data && it < Data + Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2199)), 0) );  const ptrdiff_t off = it - Data; if (it < Data + Size - 1) memcpy(Data + off, Data + Size - 1, sizeof(T)); Size--; return Data + off; }
    inline T*           insert(const T* it, const T& v)     { (void)( (!!(it >= Data && it <= Data + Size)) || (_wassert(L"it >= Data && it <= Data + Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2200)), 0) ); const ptrdiff_t off = it - Data; if (Size == Capacity) reserve(_grow_capacity(Size + 1)); if (off < (int)Size) memmove(Data + off + 1, Data + off, ((size_t)Size - (size_t)off) * sizeof(T)); memcpy(&Data[off], &v, sizeof(v)); Size++; return Data + off; }
    inline bool         contains(const T& v) const          { const T* data = Data;  const T* data_end = Data + Size; while (data < data_end) if (*data++ == v) return true; return false; }
    inline T*           find(const T& v)                    { T* data = Data;  const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline const T*     find(const T& v) const              { const T* data = Data;  const T* data_end = Data + Size; while (data < data_end) if (*data == v) break; else ++data; return data; }
    inline int          find_index(const T& v) const        { const T* data_end = Data + Size; const T* it = find(v); if (it == data_end) return -1; const ptrdiff_t off = it - Data; return (int)off; }
    inline bool         find_erase(const T& v)              { const T* it = find(v); if (it < Data + Size) { erase(it); return true; } return false; }
    inline bool         find_erase_unsorted(const T& v)     { const T* it = find(v); if (it < Data + Size) { erase_unsorted(it); return true; } return false; }
    inline int          index_from_ptr(const T* it) const   { (void)( (!!(it >= Data && it < Data + Size)) || (_wassert(L"it >= Data && it < Data + Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2207)), 0) ); const ptrdiff_t off = it - Data; return (int)off; }
};


//-----------------------------------------------------------------------------
// [SECTION] ImGuiStyle
//-----------------------------------------------------------------------------
// You may modify the ImGui::GetStyle() main instance during initialization and before NewFrame().
// During the frame, use ImGui::PushStyleVar(ImGuiStyleVar_XXXX)/PopStyleVar() to alter the main style values,
// and ImGui::PushStyleColor(ImGuiCol_XXX)/PopStyleColor() for colors.
//-----------------------------------------------------------------------------

struct ImGuiStyle
{
    float       Alpha;                      // Global alpha applies to everything in Dear ImGui.
    float       DisabledAlpha;              // Additional alpha multiplier applied by BeginDisabled(). Multiply over current value of Alpha.
    ImVec2      WindowPadding;              // Padding within a window.
    float       WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
    float       WindowBorderSize;           // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      WindowMinSize;              // Minimum window size. This is a global setting. If you want to constrain individual windows, use SetNextWindowSizeConstraints().
    ImVec2      WindowTitleAlign;           // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    ImGuiDir    WindowMenuButtonPosition;   // Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
    float       ChildRounding;              // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
    float       ChildBorderSize;            // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    float       PopupRounding;              // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
    float       PopupBorderSize;            // Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      FramePadding;               // Padding within a framed rectangle (used by most widgets).
    float       FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    float       FrameBorderSize;            // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      ItemSpacing;                // Horizontal and vertical spacing between widgets/lines.
    ImVec2      ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
    ImVec2      CellPadding;                // Padding within a table cell. Cellpadding.x is locked for entire table. CellPadding.y may be altered between different rows.
    ImVec2      TouchExtraPadding;          // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    float       IndentSpacing;              // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    float       ColumnsMinSpacing;          // Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
    float       ScrollbarSize;              // Width of the vertical scrollbar, Height of the horizontal scrollbar.
    float       ScrollbarRounding;          // Radius of grab corners for scrollbar.
    float       GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar.
    float       GrabRounding;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    float       LogSliderDeadzone;          // The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
    float       TabRounding;                // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
    float       TabBorderSize;              // Thickness of border around tabs.
    float       TabMinWidthForCloseButton;  // Minimum width for close button to appear on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
    float       TabBarBorderSize;           // Thickness of tab-bar separator, which takes on the tab active color to denote focus.
    float       TabBarOverlineSize;         // Thickness of tab-bar overline, which highlights the selected tab-bar.
    float       TableAngledHeadersAngle;    // Angle of angled headers (supported values range from -50.0f degrees to +50.0f degrees).
    ImVec2      TableAngledHeadersTextAlign;// Alignment of angled headers within the cell
    ImGuiDir    ColorButtonPosition;        // Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
    ImVec2      ButtonTextAlign;            // Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
    ImVec2      SelectableTextAlign;        // Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
    float       SeparatorTextBorderSize;    // Thickness of border in SeparatorText()
    ImVec2      SeparatorTextAlign;         // Alignment of text within the separator. Defaults to (0.0f, 0.5f) (left aligned, center).
    ImVec2      SeparatorTextPadding;       // Horizontal offset of text from each edge of the separator + spacing on other axis. Generally small values. .y is recommended to be == FramePadding.y.
    ImVec2      DisplayWindowPadding;       // Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen.
    ImVec2      DisplaySafeAreaPadding;     // Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents. Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).
    float       DockingSeparatorSize;       // Thickness of resizing border between docked windows
    float       MouseCursorScale;           // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). We apply per-monitor DPI scaling over this scale. May be removed later.
    bool        AntiAliasedLines;           // Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    bool        AntiAliasedLinesUseTex;     // Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering (NOT point/nearest filtering). Latched at the beginning of the frame (copied to ImDrawList).
    bool        AntiAliasedFill;            // Enable anti-aliased edges around filled shapes (rounded rectangles, circles, etc.). Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
    float       CurveTessellationTol;       // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    float       CircleTessellationMaxError; // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
    ImVec4      Colors[ImGuiCol_COUNT];

    // Behaviors
    // (It is possible to modify those fields mid-frame if specific behavior need it, unlike e.g. configuration fields in ImGuiIO)
    float             HoverStationaryDelay;     // Delay for IsItemHovered(ImGuiHoveredFlags_Stationary). Time required to consider mouse stationary.
    float             HoverDelayShort;          // Delay for IsItemHovered(ImGuiHoveredFlags_DelayShort). Usually used along with HoverStationaryDelay.
    float             HoverDelayNormal;         // Delay for IsItemHovered(ImGuiHoveredFlags_DelayNormal). "
    ImGuiHoveredFlags HoverFlagsForTooltipMouse;// Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using mouse.
    ImGuiHoveredFlags HoverFlagsForTooltipNav;  // Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) or BeginItemTooltip()/SetItemTooltip() while using keyboard/gamepad.

     ImGuiStyle();
     void ScaleAllSizes(float scale_factor);
};

//-----------------------------------------------------------------------------
// [SECTION] ImGuiIO
//-----------------------------------------------------------------------------
// Communicate most settings and inputs/outputs to Dear ImGui using this structure.
// Access via ImGui::GetIO(). Read 'Programmer guide' section in .cpp file for general usage.
// It is generally expected that:
// - initialization: backends and user code writes to ImGuiIO.
// - main loop: backends writes to ImGuiIO, user code and imgui code reads from ImGuiIO.
//-----------------------------------------------------------------------------
// Also see ImGui::GetPlatformIO() and ImGuiPlatformIO struct for OS/platform related functions: clipboard, IME etc.
//-----------------------------------------------------------------------------

// [Internal] Storage used by IsKeyDown(), IsKeyPressed() etc functions.
// If prior to 1.87 you used io.KeysDownDuration[] (which was marked as internal), you should use GetKeyData(key)->DownDuration and *NOT* io.KeysData[key]->DownDuration.
struct ImGuiKeyData
{
    bool        Down;               // True for if key is down
    float       DownDuration;       // Duration the key has been down (<0.0f: not pressed, 0.0f: just pressed, >0.0f: time held)
    float       DownDurationPrev;   // Last frame duration the key has been down
    float       AnalogValue;        // 0.0f..1.0f for gamepad values
};

struct ImGuiIO
{
    //------------------------------------------------------------------
    // Configuration                            // Default value
    //------------------------------------------------------------------

    ImGuiConfigFlags   ConfigFlags;             // = 0              // See ImGuiConfigFlags_ enum. Set by user/application. Keyboard/Gamepad navigation options, etc.
    ImGuiBackendFlags  BackendFlags;            // = 0              // See ImGuiBackendFlags_ enum. Set by backend (imgui_impl_xxx files or custom backend) to communicate features supported by the backend.
    ImVec2      DisplaySize;                    // <unset>          // Main display size, in pixels (generally == GetMainViewport()->Size). May change every frame.
    float       DeltaTime;                      // = 1.0f/60.0f     // Time elapsed since last frame, in seconds. May change every frame.
    float       IniSavingRate;                  // = 5.0f           // Minimum time between saving positions/sizes to .ini file, in seconds.
    const char* IniFilename;                    // = "imgui.ini"    // Path to .ini file (important: default "imgui.ini" is relative to current working dir!). Set NULL to disable automatic .ini loading/saving or if you want to manually call LoadIniSettingsXXX() / SaveIniSettingsXXX() functions.
    const char* LogFilename;                    // = "imgui_log.txt"// Path to .log file (default parameter to ImGui::LogToFile when no file is specified).
    void*       UserData;                       // = NULL           // Store your own data.

    // Font system
    ImFontAtlas*Fonts;                          // <auto>           // Font atlas: load, rasterize and pack one or more fonts into a single texture.
    float       FontGlobalScale;                // = 1.0f           // Global scale all fonts
    bool        FontAllowUserScaling;           // = false          // [OBSOLETE] Allow user scaling text of individual window with CTRL+Wheel.
    ImFont*     FontDefault;                    // = NULL           // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
    ImVec2      DisplayFramebufferScale;        // = (1, 1)         // For retina display or other situations where window coordinates are different from framebuffer coordinates. This generally ends up in ImDrawData::FramebufferScale.

    // Keyboard/Gamepad Navigation options
    bool        ConfigNavSwapGamepadButtons;    // = false          // Swap Activate<>Cancel (A<>B) buttons, matching typical "Nintendo/Japanese style" gamepad layout.
    bool        ConfigNavMoveSetMousePos;       // = false          // Directional/tabbing navigation teleports the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is difficult. Will update io.MousePos and set io.WantSetMousePos=true.
    bool        ConfigNavCaptureKeyboard;       // = true           // Sets io.WantCaptureKeyboard when io.NavActive is set.
    bool        ConfigNavEscapeClearFocusItem;  // = true           // Pressing Escape can clear focused item + navigation id/highlight. Set to false if you want to always keep highlight on.
    bool        ConfigNavEscapeClearFocusWindow;// = false          // Pressing Escape can clear focused window as well (super set of io.ConfigNavEscapeClearFocusItem).
    bool        ConfigNavCursorVisibleAuto;     // = true           // Using directional navigation key makes the cursor visible. Mouse click hides the cursor.
    bool        ConfigNavCursorVisibleAlways;   // = false          // Navigation cursor is always visible.

    // Docking options (when ImGuiConfigFlags_DockingEnable is set)
    bool        ConfigDockingNoSplit;           // = false          // Simplified docking mode: disable window splitting, so docking is limited to merging multiple windows together into tab-bars.
    bool        ConfigDockingWithShift;         // = false          // Enable docking with holding Shift key (reduce visual noise, allows dropping in wider space)
    bool        ConfigDockingAlwaysTabBar;      // = false          // [BETA] [FIXME: This currently creates regression with auto-sizing and general overhead] Make every single floating window display within a docking node.
    bool        ConfigDockingTransparentPayload;// = false          // [BETA] Make window or viewport transparent when docking and only display docking boxes on the target viewport. Useful if rendering of multiple viewport cannot be synced. Best used with ConfigViewportsNoAutoMerge.

    // Viewport options (when ImGuiConfigFlags_ViewportsEnable is set)
    bool        ConfigViewportsNoAutoMerge;     // = false;         // Set to make all floating imgui windows always create their own viewport. Otherwise, they are merged into the main host viewports when overlapping it. May also set ImGuiViewportFlags_NoAutoMerge on individual viewport.
    bool        ConfigViewportsNoTaskBarIcon;   // = false          // Disable default OS task bar icon flag for secondary viewports. When a viewport doesn't want a task bar icon, ImGuiViewportFlags_NoTaskBarIcon will be set on it.
    bool        ConfigViewportsNoDecoration;    // = true           // Disable default OS window decoration flag for secondary viewports. When a viewport doesn't want window decorations, ImGuiViewportFlags_NoDecoration will be set on it. Enabling decoration can create subsequent issues at OS levels (e.g. minimum window size).
    bool        ConfigViewportsNoDefaultParent; // = false          // Disable default OS parenting to main viewport for secondary viewports. By default, viewports are marked with ParentViewportId = <main_viewport>, expecting the platform backend to setup a parent/child relationship between the OS windows (some backend may ignore this). Set to true if you want the default to be 0, then all viewports will be top-level OS windows.

    // Miscellaneous options
    // (you can visualize and interact with all options in 'Demo->Configuration')
    bool        MouseDrawCursor;                // = false          // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor). Cannot be easily renamed to 'io.ConfigXXX' because this is frequently used by backend implementations.
    bool        ConfigMacOSXBehaviors;          // = defined(__APPLE__) // Swap Cmd<>Ctrl keys + OS X style text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl.
    bool        ConfigInputTrickleEventQueue;   // = true           // Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.
    bool        ConfigInputTextCursorBlink;     // = true           // Enable blinking cursor (optional as some users consider it to be distracting).
    bool        ConfigInputTextEnterKeepActive; // = false          // [BETA] Pressing Enter will keep item active and select contents (single-line only).
    bool        ConfigDragClickToInputText;     // = false          // [BETA] Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving). Not desirable on devices without a keyboard.
    bool        ConfigWindowsResizeFromEdges;   // = true           // Enable resizing of windows from their edges and from the lower-left corner. This requires ImGuiBackendFlags_HasMouseCursors for better mouse cursor feedback. (This used to be a per-window ImGuiWindowFlags_ResizeFromAnySide flag)
    bool        ConfigWindowsMoveFromTitleBarOnly;  // = false      // Enable allowing to move windows only when clicking on their title bar. Does not apply to windows without a title bar.
    bool        ConfigWindowsCopyContentsWithCtrlC; // = false      // [EXPERIMENTAL] CTRL+C copy the contents of focused window into the clipboard. Experimental because: (1) has known issues with nested Begin/End pairs (2) text output quality varies (3) text output is in submission order rather than spatial order.
    bool        ConfigScrollbarScrollByPage;    // = true           // Enable scrolling page by page when clicking outside the scrollbar grab. When disabled, always scroll to clicked location. When enabled, Shift+Click scrolls to clicked location.
    float       ConfigMemoryCompactTimer;       // = 60.0f          // Timer (in seconds) to free transient windows/tables memory buffers when unused. Set to -1.0f to disable.

    // Inputs Behaviors
    // (other variables, ones which are expected to be tweaked within UI code, are exposed in ImGuiStyle)
    float       MouseDoubleClickTime;           // = 0.30f          // Time for a double-click, in seconds.
    float       MouseDoubleClickMaxDist;        // = 6.0f           // Distance threshold to stay in to validate a double-click, in pixels.
    float       MouseDragThreshold;             // = 6.0f           // Distance threshold before considering we are dragging.
    float       KeyRepeatDelay;                 // = 0.275f         // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
    float       KeyRepeatRate;                  // = 0.050f         // When holding a key/button, rate at which it repeats, in seconds.

    //------------------------------------------------------------------
    // Debug options
    //------------------------------------------------------------------

    // Options to configure Error Handling and how we handle recoverable errors [EXPERIMENTAL]
    // - Error recovery is provided as a way to facilitate:
    //    - Recovery after a programming error (native code or scripting language - the later tends to facilitate iterating on code while running).
    //    - Recovery after running an exception handler or any error processing which may skip code after an error has been detected.
    // - Error recovery is not perfect nor guaranteed! It is a feature to ease development.
    //   You not are not supposed to rely on it in the course of a normal application run.
    // - Functions that support error recovery are using IM_ASSERT_USER_ERROR() instead of IM_ASSERT().
    // - By design, we do NOT allow error recovery to be 100% silent. One of the three options needs to be checked!
    // - Always ensure that on programmers seats you have at minimum Asserts or Tooltips enabled when making direct imgui API calls!
    //   Otherwise it would severely hinder your ability to catch and correct mistakes!
    // Read https://github.com/ocornut/imgui/wiki/Error-Handling for details.
    // - Programmer seats: keep asserts (default), or disable asserts and keep error tooltips (new and nice!)
    // - Non-programmer seats: maybe disable asserts, but make sure errors are resurfaced (tooltips, visible log entries, use callback etc.)
    // - Recovery after error/exception: record stack sizes with ErrorRecoveryStoreState(), disable assert, set log callback (to e.g. trigger high-level breakpoint), recover with ErrorRecoveryTryToRecoverState(), restore settings.
    bool        ConfigErrorRecovery;                // = true       // Enable error recovery support. Some errors won't be detected and lead to direct crashes if recovery is disabled.
    bool        ConfigErrorRecoveryEnableAssert;    // = true       // Enable asserts on recoverable error. By default call IM_ASSERT() when returning from a failing IM_ASSERT_USER_ERROR()
    bool        ConfigErrorRecoveryEnableDebugLog;  // = true       // Enable debug log output on recoverable errors.
    bool        ConfigErrorRecoveryEnableTooltip;   // = true       // Enable tooltip on recoverable errors. The tooltip include a way to enable asserts if they were disabled.

    // Option to enable various debug tools showing buttons that will call the IM_DEBUG_BREAK() macro.
    // - The Item Picker tool will be available regardless of this being enabled, in order to maximize its discoverability.
    // - Requires a debugger being attached, otherwise IM_DEBUG_BREAK() options will appear to crash your application.
    //   e.g. io.ConfigDebugIsDebuggerPresent = ::IsDebuggerPresent() on Win32, or refer to ImOsIsDebuggerPresent() imgui_test_engine/imgui_te_utils.cpp for a Unix compatible version).
    bool        ConfigDebugIsDebuggerPresent;   // = false          // Enable various tools calling IM_DEBUG_BREAK().

    // Tools to detect code submitting items with conflicting/duplicate IDs
    // - Code should use PushID()/PopID() in loops, or append "##xx" to same-label identifiers.
    // - Empty label e.g. Button("") == same ID as parent widget/node. Use Button("##xx") instead!
    // - See FAQ https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-about-the-id-stack-system
    bool        ConfigDebugHighlightIdConflicts;// = true           // Highlight and show an error message when multiple items have conflicting identifiers.

    // Tools to test correct Begin/End and BeginChild/EndChild behaviors.
    // - Presently Begin()/End() and BeginChild()/EndChild() needs to ALWAYS be called in tandem, regardless of return value of BeginXXX()
    // - This is inconsistent with other BeginXXX functions and create confusion for many users.
    // - We expect to update the API eventually. In the meanwhile we provide tools to facilitate checking user-code behavior.
    bool        ConfigDebugBeginReturnValueOnce;// = false          // First-time calls to Begin()/BeginChild() will return false. NEEDS TO BE SET AT APPLICATION BOOT TIME if you don't want to miss windows.
    bool        ConfigDebugBeginReturnValueLoop;// = false          // Some calls to Begin()/BeginChild() will return false. Will cycle through window depths then repeat. Suggested use: add "io.ConfigDebugBeginReturnValue = io.KeyShift" in your main loop then occasionally press SHIFT. Windows should be flickering while running.

    // Option to deactivate io.AddFocusEvent(false) handling.
    // - May facilitate interactions with a debugger when focus loss leads to clearing inputs data.
    // - Backends may have other side-effects on focus loss, so this will reduce side-effects but not necessary remove all of them.
    bool        ConfigDebugIgnoreFocusLoss;     // = false          // Ignore io.AddFocusEvent(false), consequently not calling io.ClearInputKeys()/io.ClearInputMouse() in input processing.

    // Option to audit .ini data
    bool        ConfigDebugIniSettings;         // = false          // Save .ini data with extra comments (particularly helpful for Docking, but makes saving slower)

    //------------------------------------------------------------------
    // Platform Identifiers
    // (the imgui_impl_xxxx backend files are setting those up for you)
    //------------------------------------------------------------------

    // Nowadays those would be stored in ImGuiPlatformIO but we are leaving them here for legacy reasons.
    // Optional: Platform/Renderer backend name (informational only! will be displayed in About Window) + User data for backend/wrappers to store their own stuff.
    const char* BackendPlatformName;            // = NULL
    const char* BackendRendererName;            // = NULL
    void*       BackendPlatformUserData;        // = NULL           // User data for platform backend
    void*       BackendRendererUserData;        // = NULL           // User data for renderer backend
    void*       BackendLanguageUserData;        // = NULL           // User data for non C++ programming language backend

    //------------------------------------------------------------------
    // Input - Call before calling NewFrame()
    //------------------------------------------------------------------

    // Input Functions
     void  AddKeyEvent(ImGuiKey key, bool down);                   // Queue a new key down/up event. Key should be "translated" (as in, generally ImGuiKey_A matches the key end-user would use to emit an 'A' character)
     void  AddKeyAnalogEvent(ImGuiKey key, bool down, float v);    // Queue a new key down/up event for analog values (e.g. ImGuiKey_Gamepad_ values). Dead-zones should be handled by the backend.
     void  AddMousePosEvent(float x, float y);                     // Queue a mouse position update. Use -FLT_MAX,-FLT_MAX to signify no mouse (e.g. app not focused and not hovered)
     void  AddMouseButtonEvent(int button, bool down);             // Queue a mouse button change
     void  AddMouseWheelEvent(float wheel_x, float wheel_y);       // Queue a mouse wheel update. wheel_y<0: scroll down, wheel_y>0: scroll up, wheel_x<0: scroll right, wheel_x>0: scroll left.
     void  AddMouseSourceEvent(ImGuiMouseSource source);           // Queue a mouse source change (Mouse/TouchScreen/Pen)
     void  AddMouseViewportEvent(ImGuiID id);                      // Queue a mouse hovered viewport. Requires backend to set ImGuiBackendFlags_HasMouseHoveredViewport to call this (for multi-viewport support).
     void  AddFocusEvent(bool focused);                            // Queue a gain/loss of focus for the application (generally based on OS/platform focus of your window)
     void  AddInputCharacter(unsigned int c);                      // Queue a new character input
     void  AddInputCharacterUTF16(ImWchar16 c);                    // Queue a new character input from a UTF-16 character, it can be a surrogate
     void  AddInputCharactersUTF8(const char* str);                // Queue a new characters input from a UTF-8 string

     void  SetKeyEventNativeData(ImGuiKey key, int native_keycode, int native_scancode, int native_legacy_index = -1); // [Optional] Specify index for legacy <1.87 IsKeyXXX() functions with native indices + specify native keycode, scancode.
     void  SetAppAcceptingEvents(bool accepting_events);           // Set master flag for accepting key/mouse/text events (default to true). Useful if you have native dialog boxes that are interrupting your application loop/refresh, and you want to disable events being queued while your app is frozen.
     void  ClearEventsQueue();                                     // Clear all incoming events.
     void  ClearInputKeys();                                       // Clear current keyboard/gamepad state + current frame text input buffer. Equivalent to releasing all keys/buttons.
     void  ClearInputMouse();                                      // Clear current mouse state.




    //------------------------------------------------------------------
    // Output - Updated by NewFrame() or EndFrame()/Render()
    // (when reading from the io.WantCaptureMouse, io.WantCaptureKeyboard flags to dispatch your inputs, it is
    //  generally easier and more correct to use their state BEFORE calling NewFrame(). See FAQ for details!)
    //------------------------------------------------------------------

    bool        WantCaptureMouse;                   // Set when Dear ImGui will use mouse inputs, in this case do not dispatch them to your main game/application (either way, always pass on mouse inputs to imgui). (e.g. unclicked mouse is hovering over an imgui window, widget is active, mouse was clicked over an imgui window, etc.).
    bool        WantCaptureKeyboard;                // Set when Dear ImGui will use keyboard inputs, in this case do not dispatch them to your main game/application (either way, always pass keyboard inputs to imgui). (e.g. InputText active, or an imgui window is focused and navigation is enabled, etc.).
    bool        WantTextInput;                      // Mobile/console: when set, you may display an on-screen keyboard. This is set by Dear ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
    bool        WantSetMousePos;                    // MousePos has been altered, backend should reposition mouse on next frame. Rarely used! Set only when io.ConfigNavMoveSetMousePos is enabled.
    bool        WantSaveIniSettings;                // When manual .ini load/save is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. Important: clear io.WantSaveIniSettings yourself after saving!
    bool        NavActive;                          // Keyboard/Gamepad navigation is currently allowed (will handle ImGuiKey_NavXXX events) = a window is focused and it doesn't use the ImGuiWindowFlags_NoNavInputs flag.
    bool        NavVisible;                         // Keyboard/Gamepad navigation highlight is visible and allowed (will handle ImGuiKey_NavXXX events).
    float       Framerate;                          // Estimate of application framerate (rolling average over 60 frames, based on io.DeltaTime), in frame per second. Solely for convenience. Slow applications may not want to use a moving average or may want to reset underlying buffers occasionally.
    int         MetricsRenderVertices;              // Vertices output during last call to Render()
    int         MetricsRenderIndices;               // Indices output during last call to Render() = number of triangles * 3
    int         MetricsRenderWindows;               // Number of visible windows
    int         MetricsActiveWindows;               // Number of active windows
    ImVec2      MouseDelta;                         // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.

    //------------------------------------------------------------------
    // [Internal] Dear ImGui will maintain those fields. Forward compatibility not guaranteed!
    //------------------------------------------------------------------

    ImGuiContext* Ctx;                              // Parent UI context (needs to be set explicitly by parent).

    // Main Input State
    // (this block used to be written by backend, since 1.87 it is best to NOT write to those directly, call the AddXXX functions above instead)
    // (reading from those variables is fair game, as they are extremely unlikely to be moving anywhere)
    ImVec2      MousePos;                           // Mouse position, in pixels. Set to ImVec2(-FLT_MAX, -FLT_MAX) if mouse is unavailable (on another screen, etc.)
    bool        MouseDown[5];                       // Mouse buttons: 0=left, 1=right, 2=middle + extras (ImGuiMouseButton_COUNT == 5). Dear ImGui mostly uses left and right buttons. Other buttons allow us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
    float       MouseWheel;                         // Mouse wheel Vertical: 1 unit scrolls about 5 lines text. >0 scrolls Up, <0 scrolls Down. Hold SHIFT to turn vertical scroll into horizontal scroll.
    float       MouseWheelH;                        // Mouse wheel Horizontal. >0 scrolls Left, <0 scrolls Right. Most users don't have a mouse with a horizontal wheel, may not be filled by all backends.
    ImGuiMouseSource MouseSource;                   // Mouse actual input peripheral (Mouse/TouchScreen/Pen).
    ImGuiID     MouseHoveredViewport;               // (Optional) Modify using io.AddMouseViewportEvent(). With multi-viewports: viewport the OS mouse is hovering. If possible _IGNORING_ viewports with the ImGuiViewportFlags_NoInputs flag is much better (few backends can handle that). Set io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport if you can provide this info. If you don't imgui will infer the value using the rectangles and last focused time of the viewports it knows about (ignoring other OS windows).
    bool        KeyCtrl;                            // Keyboard modifier down: Control
    bool        KeyShift;                           // Keyboard modifier down: Shift
    bool        KeyAlt;                             // Keyboard modifier down: Alt
    bool        KeySuper;                           // Keyboard modifier down: Cmd/Super/Windows

    // Other state maintained from data above + IO function calls
    ImGuiKeyChord KeyMods;                          // Key mods flags (any of ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Alt/ImGuiMod_Super flags, same as io.KeyCtrl/KeyShift/KeyAlt/KeySuper but merged into flags. Read-only, updated by NewFrame()
    ImGuiKeyData  KeysData[ImGuiKey_NamedKey_COUNT];// Key state for all known keys. Use IsKeyXXX() functions to access this.
    bool        WantCaptureMouseUnlessPopupClose;   // Alternative to WantCaptureMouse: (WantCaptureMouse == true && WantCaptureMouseUnlessPopupClose == false) when a click over void is expected to close a popup.
    ImVec2      MousePosPrev;                       // Previous mouse position (note that MouseDelta is not necessary == MousePos-MousePosPrev, in case either position is invalid)
    ImVec2      MouseClickedPos[5];                 // Position at time of clicking
    double      MouseClickedTime[5];                // Time of last click (used to figure out double-click)
    bool        MouseClicked[5];                    // Mouse button went from !Down to Down (same as MouseClickedCount[x] != 0)
    bool        MouseDoubleClicked[5];              // Has mouse button been double-clicked? (same as MouseClickedCount[x] == 2)
    ImU16       MouseClickedCount[5];               // == 0 (not clicked), == 1 (same as MouseClicked[]), == 2 (double-clicked), == 3 (triple-clicked) etc. when going from !Down to Down
    ImU16       MouseClickedLastCount[5];           // Count successive number of clicks. Stays valid after mouse release. Reset after another click is done.
    bool        MouseReleased[5];                   // Mouse button went from Down to !Down
    double      MouseReleasedTime[5];               // Time of last released (rarely used! but useful to handle delayed single-click when trying to disambiguate them from double-click).
    bool        MouseDownOwned[5];                  // Track if button was clicked inside a dear imgui window or over void blocked by a popup. We don't request mouse capture from the application if click started outside ImGui bounds.
    bool        MouseDownOwnedUnlessPopupClose[5];  // Track if button was clicked inside a dear imgui window.
    bool        MouseWheelRequestAxisSwap;          // On a non-Mac system, holding SHIFT requests WheelY to perform the equivalent of a WheelX event. On a Mac system this is already enforced by the system.
    bool        MouseCtrlLeftAsRightClick;          // (OSX) Set to true when the current click was a ctrl-click that spawned a simulated right click
    float       MouseDownDuration[5];               // Duration the mouse button has been down (0.0f == just clicked)
    float       MouseDownDurationPrev[5];           // Previous time the mouse button has been down
    ImVec2      MouseDragMaxDistanceAbs[5];         // Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
    float       MouseDragMaxDistanceSqr[5];         // Squared maximum distance of how much mouse has traveled from the clicking point (used for moving thresholds)
    float       PenPressure;                        // Touch/Pen pressure (0.0f to 1.0f, should be >0.0f only when MouseDown[0] == true). Helper storage currently unused by Dear ImGui.
    bool        AppFocusLost;                       // Only modify via AddFocusEvent()
    bool        AppAcceptingEvents;                 // Only modify via SetAppAcceptingEvents()
    ImWchar16   InputQueueSurrogate;                // For AddInputCharacterUTF16()
    ImVector<ImWchar> InputQueueCharacters;         // Queue of _characters_ input (obtained by platform backend). Fill using AddInputCharacter() helper.

    // Legacy: before 1.87, we required backend to fill io.KeyMap[] (imgui->native map) during initialization and io.KeysDown[] (native indices) every frame.
    // This is still temporarily supported as a legacy feature. However the new preferred scheme is for backend to call io.AddKeyEvent().
    //   Old (<1.87):  ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Space]) --> New (1.87+) ImGui::IsKeyPressed(ImGuiKey_Space)
    //   Old (<1.87):  ImGui::IsKeyPressed(MYPLATFORM_KEY_SPACE)                  --> New (1.87+) ImGui::IsKeyPressed(ImGuiKey_Space)
    // Read https://github.com/ocornut/imgui/issues/4921 for details.
    //int       KeyMap[ImGuiKey_COUNT];             // [LEGACY] Input: map of indices into the KeysDown[512] entries array which represent your "native" keyboard state. The first 512 are now unused and should be kept zero. Legacy backend will write into KeyMap[] using ImGuiKey_ indices which are always >512.
    //bool      KeysDown[ImGuiKey_COUNT];           // [LEGACY] Input: Keyboard keys that are pressed (ideally left in the "native" order your engine has access to keyboard keys, so you can use your own defines/enums for keys). This used to be [512] sized. It is now ImGuiKey_COUNT to allow legacy io.KeysDown[GetKeyIndex(...)] to work without an overflow.
    //float     NavInputs[ImGuiNavInput_COUNT];     // [LEGACY] Since 1.88, NavInputs[] was removed. Backends from 1.60 to 1.86 won't build. Feed gamepad inputs via io.AddKeyEvent() and ImGuiKey_GamepadXXX enums.
    //void*     ImeWindowHandle;                    // [Obsoleted in 1.87] Set ImGuiViewport::PlatformHandleRaw instead. Set this to your HWND to get automatic IME cursor positioning.

    // Legacy: before 1.91.1, clipboard functions were stored in ImGuiIO instead of ImGuiPlatformIO.
    // As this is will affect all users of custom engines/backends, we are providing proper legacy redirection (will obsolete).






       ImGuiIO();
};

//-----------------------------------------------------------------------------
// [SECTION] Misc data structures (ImGuiInputTextCallbackData, ImGuiSizeCallbackData, ImGuiPayload)
//-----------------------------------------------------------------------------

// Shared state of InputText(), passed as an argument to your callback when a ImGuiInputTextFlags_Callback* flag is used.
// The callback function should return 0 by default.
// Callbacks (follow a flag name and see comments in ImGuiInputTextFlags_ declarations for more details)
// - ImGuiInputTextFlags_CallbackEdit:        Callback on buffer edit. Note that InputText() already returns true on edit + you can always use IsItemEdited(). The callback is useful to manipulate the underlying buffer while focus is active.
// - ImGuiInputTextFlags_CallbackAlways:      Callback on each iteration
// - ImGuiInputTextFlags_CallbackCompletion:  Callback on pressing TAB
// - ImGuiInputTextFlags_CallbackHistory:     Callback on pressing Up/Down arrows
// - ImGuiInputTextFlags_CallbackCharFilter:  Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
// - ImGuiInputTextFlags_CallbackResize:      Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow.
struct ImGuiInputTextCallbackData
{
    ImGuiContext*       Ctx;            // Parent UI context
    ImGuiInputTextFlags EventFlag;      // One ImGuiInputTextFlags_Callback*    // Read-only
    ImGuiInputTextFlags Flags;          // What user passed to InputText()      // Read-only
    void*               UserData;       // What user passed to InputText()      // Read-only

    // Arguments for the different callback events
    // - During Resize callback, Buf will be same as your input buffer.
    // - However, during Completion/History/Always callback, Buf always points to our own internal data (it is not the same as your buffer)! Changes to it will be reflected into your own buffer shortly after the callback.
    // - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
    // - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
    ImWchar             EventChar;      // Character input                      // Read-write   // [CharFilter] Replace character with another one, or set to zero to drop. return 1 is equivalent to setting EventChar=0;
    ImGuiKey            EventKey;       // Key pressed (Up/Down/TAB)            // Read-only    // [Completion,History]
    char*               Buf;            // Text buffer                          // Read-write   // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
    int                 BufTextLen;     // Text length (in bytes)               // Read-write   // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
    int                 BufSize;        // Buffer size (in bytes) = capacity+1  // Read-only    // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
    bool                BufDirty;       // Set if you modify Buf/BufTextLen!    // Write        // [Completion,History,Always]
    int                 CursorPos;      //                                      // Read-write   // [Completion,History,Always]
    int                 SelectionStart; //                                      // Read-write   // [Completion,History,Always] == to SelectionEnd when no selection)
    int                 SelectionEnd;   //                                      // Read-write   // [Completion,History,Always]

    // Helper functions for text manipulation.
    // Use those function to benefit from the CallbackResize behaviors. Calling those function reset the selection.
     ImGuiInputTextCallbackData();
     void      DeleteChars(int pos, int bytes_count);
     void      InsertChars(int pos, const char* text, const char* text_end = ((void *)0));
    void                SelectAll()             { SelectionStart = 0; SelectionEnd = BufTextLen; }
    void                ClearSelection()        { SelectionStart = SelectionEnd = BufTextLen; }
    bool                HasSelection() const    { return SelectionStart != SelectionEnd; }
};

// Resizing callback data to apply custom constraint. As enabled by SetNextWindowSizeConstraints(). Callback is called during the next Begin().
// NB: For basic min/max size constraint on each axis you don't need to use the callback! The SetNextWindowSizeConstraints() parameters are enough.
struct ImGuiSizeCallbackData
{
    void*   UserData;       // Read-only.   What user passed to SetNextWindowSizeConstraints(). Generally store an integer or float in here (need reinterpret_cast<>).
    ImVec2  Pos;            // Read-only.   Window position, for reference.
    ImVec2  CurrentSize;    // Read-only.   Current window size.
    ImVec2  DesiredSize;    // Read-write.  Desired size, based on user's mouse position. Write to this field to restrain resizing.
};

// [ALPHA] Rarely used / very advanced uses only. Use with SetNextWindowClass() and DockSpace() functions.
// Important: the content of this class is still highly WIP and likely to change and be refactored
// before we stabilize Docking features. Please be mindful if using this.
// Provide hints:
// - To the platform backend via altered viewport flags (enable/disable OS decoration, OS task bar icons, etc.)
// - To the platform backend for OS level parent/child relationships of viewport.
// - To the docking system for various options and filtering.
struct ImGuiWindowClass
{
    ImGuiID             ClassId;                    // User data. 0 = Default class (unclassed). Windows of different classes cannot be docked with each others.
    ImGuiID             ParentViewportId;           // Hint for the platform backend. -1: use default. 0: request platform backend to not parent the platform. != 0: request platform backend to create a parent<>child relationship between the platform windows. Not conforming backends are free to e.g. parent every viewport to the main viewport or not.
    ImGuiID             FocusRouteParentWindowId;   // ID of parent window for shortcut focus route evaluation, e.g. Shortcut() call from Parent Window will succeed when this window is focused.
    ImGuiViewportFlags  ViewportFlagsOverrideSet;   // Viewport flags to set when a window of this class owns a viewport. This allows you to enforce OS decoration or task bar icon, override the defaults on a per-window basis.
    ImGuiViewportFlags  ViewportFlagsOverrideClear; // Viewport flags to clear when a window of this class owns a viewport. This allows you to enforce OS decoration or task bar icon, override the defaults on a per-window basis.
    ImGuiTabItemFlags   TabItemFlagsOverrideSet;    // [EXPERIMENTAL] TabItem flags to set when a window of this class gets submitted into a dock node tab bar. May use with ImGuiTabItemFlags_Leading or ImGuiTabItemFlags_Trailing.
    ImGuiDockNodeFlags  DockNodeFlagsOverrideSet;   // [EXPERIMENTAL] Dock node flags to set when a window of this class is hosted by a dock node (it doesn't have to be selected!)
    bool                DockingAlwaysTabBar;        // Set to true to enforce single floating windows of this class always having their own docking node (equivalent of setting the global io.ConfigDockingAlwaysTabBar)
    bool                DockingAllowUnclassed;      // Set to true to allow windows of this class to be docked/merged with an unclassed window. // FIXME-DOCK: Move to DockNodeFlags override?

    ImGuiWindowClass() { memset(this, 0, sizeof(*this)); ParentViewportId = (ImGuiID)-1; DockingAllowUnclassed = true; }
};

// Data payload for Drag and Drop operations: AcceptDragDropPayload(), GetDragDropPayload()
struct ImGuiPayload
{
    // Members
    void*           Data;               // Data (copied and owned by dear imgui)
    int             DataSize;           // Data size

    // [Internal]
    ImGuiID         SourceId;           // Source item id
    ImGuiID         SourceParentId;     // Source parent id (if available)
    int             DataFrameCount;     // Data timestamp
    char            DataType[32 + 1];   // Data type tag (short user-supplied string, 32 characters max)
    bool            Preview;            // Set when AcceptDragDropPayload() was called and mouse has been hovering the target item (nb: handle overlapping drag targets)
    bool            Delivery;           // Set when AcceptDragDropPayload() was called and mouse button is released over the target item.

    ImGuiPayload()  { Clear(); }
    void Clear()    { SourceId = SourceParentId = 0; Data = ((void *)0); DataSize = 0; memset(DataType, 0, sizeof(DataType)); DataFrameCount = -1; Preview = Delivery = false; }
    bool IsDataType(const char* type) const { return DataFrameCount != -1 && strcmp(type, DataType) == 0; }
    bool IsPreview() const                  { return Preview; }
    bool IsDelivery() const                 { return Delivery; }
};

//-----------------------------------------------------------------------------
// [SECTION] Helpers (ImGuiOnceUponAFrame, ImGuiTextFilter, ImGuiTextBuffer, ImGuiStorage, ImGuiListClipper, Math Operators, ImColor)
//-----------------------------------------------------------------------------

// Helper: Unicode defines






// Helper: Execute a block of code at maximum once a frame. Convenient if you want to quickly create a UI within deep-nested code that runs multiple times every frame.
// Usage: static ImGuiOnceUponAFrame oaf; if (oaf) ImGui::Text("This will be called only once per frame");
struct ImGuiOnceUponAFrame
{
    ImGuiOnceUponAFrame() { RefFrame = -1; }
    mutable int RefFrame;
    operator bool() const { int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};

// Helper: Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
struct ImGuiTextFilter
{
               ImGuiTextFilter(const char* default_filter = "");
     bool      Draw(const char* label = "Filter (inc,-exc)", float width = 0.0f);  // Helper calling InputText+Build
     bool      PassFilter(const char* text, const char* text_end = ((void *)0)) const;
     void      Build();
    void                Clear()          { InputBuf[0] = 0; Build(); }
    bool                IsActive() const { return !Filters.empty(); }

    // [Internal]
    struct ImGuiTextRange
    {
        const char*     b;
        const char*     e;

        ImGuiTextRange()                                { b = e = ((void *)0); }
        ImGuiTextRange(const char* _b, const char* _e)  { b = _b; e = _e; }
        bool            empty() const                   { return b == e; }
         void  split(char separator, ImVector<ImGuiTextRange>* out) const;
    };
    char                    InputBuf[256];
    ImVector<ImGuiTextRange>Filters;
    int                     CountGrep;
};

// Helper: Growable text buffer for logging/accumulating text
// (this could be called 'ImGuiTextBuilder' / 'ImGuiStringBuilder')
struct ImGuiTextBuffer
{
    ImVector<char>      Buf;
     static char EmptyString[1];

    ImGuiTextBuffer()   { }
    inline char         operator[](int i) const { (void)( (!!(Buf.Data != ((void *)0))) || (_wassert(L"Buf.Data != ((void *)0)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(2701)), 0) ); return Buf.Data[i]; }
    const char*         begin() const           { return Buf.Data ? &Buf.front() : EmptyString; }
    const char*         end() const             { return Buf.Data ? &Buf.back() : EmptyString; }   // Buf is zero-terminated, so end() will point on the zero-terminator
    int                 size() const            { return Buf.Size ? Buf.Size - 1 : 0; }
    bool                empty() const           { return Buf.Size <= 1; }
    void                clear()                 { Buf.clear(); }
    void                reserve(int capacity)   { Buf.reserve(capacity); }
    const char*         c_str() const           { return Buf.Data ? Buf.Data : EmptyString; }
     void      append(const char* str, const char* str_end = ((void *)0));
     void      appendf(const char* fmt, ...) ;
     void      appendfv(const char* fmt, va_list args) ;
};

// [Internal] Key+Value for ImGuiStorage
struct ImGuiStoragePair
{
    ImGuiID     key;
    union       { int val_i; float val_f; void* val_p; };
    ImGuiStoragePair(ImGuiID _key, int _val)    { key = _key; val_i = _val; }
    ImGuiStoragePair(ImGuiID _key, float _val)  { key = _key; val_f = _val; }
    ImGuiStoragePair(ImGuiID _key, void* _val)  { key = _key; val_p = _val; }
};

// Helper: Key->Value storage
// Typically you don't have to worry about this since a storage is held within each Window.
// We use it to e.g. store collapse state for a tree (Int 0/1)
// This is optimized for efficient lookup (dichotomy into a contiguous buffer) and rare insertion (typically tied to user interactions aka max once a frame)
// You can use it as custom user storage for temporary values. Declare your own storage if, for example:
// - You want to manipulate the open/close state of a particular sub-tree in your interface (tree node uses Int 0/1 to store their state).
// - You want to store custom debug data easily without adding or editing structures in your code (probably not efficient, but convenient)
// Types are NOT stored, so it is up to you to make sure your Key don't collide with different types.
struct ImGuiStorage
{
    // [Internal]
    ImVector<ImGuiStoragePair>      Data;

    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly, paid once. A typical frame shouldn't need to insert any new pair.
    void                Clear() { Data.clear(); }
     int       GetInt(ImGuiID key, int default_val = 0) const;
     void      SetInt(ImGuiID key, int val);
     bool      GetBool(ImGuiID key, bool default_val = false) const;
     void      SetBool(ImGuiID key, bool val);
     float     GetFloat(ImGuiID key, float default_val = 0.0f) const;
     void      SetFloat(ImGuiID key, float val);
     void*     GetVoidPtr(ImGuiID key) const; // default_val is NULL
     void      SetVoidPtr(ImGuiID key, void* val);

    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set.
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient for quick hacking (e.g. add storage during a live Edit&Continue session if you can't modify existing struct)
    //      float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
     int*      GetIntRef(ImGuiID key, int default_val = 0);
     bool*     GetBoolRef(ImGuiID key, bool default_val = false);
     float*    GetFloatRef(ImGuiID key, float default_val = 0.0f);
     void**    GetVoidPtrRef(ImGuiID key, void* default_val = ((void *)0));

    // Advanced: for quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
     void      BuildSortByKey();
    // Obsolete: use on your own storage if you know only integer are being stored (open/close all tree nodes)
     void      SetAllInt(int val);




};

// Helper: Manually clip large list of items.
// If you have lots evenly spaced items and you have random access to the list, you can perform coarse
// clipping based on visibility to only submit items that are in view.
// The clipper calculates the range of visible items and advance the cursor to compensate for the non-visible items we have skipped.
// (Dear ImGui already clip items based on their bounds but: it needs to first layout the item to do so, and generally
//  fetching/submitting your own data incurs additional cost. Coarse clipping using ImGuiListClipper allows you to easily
//  scale using lists with tens of thousands of items without a problem)
// Usage:
//   ImGuiListClipper clipper;
//   clipper.Begin(1000);         // We have 1000 elements, evenly spaced.
//   while (clipper.Step())
//       for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
//           ImGui::Text("line number %d", i);
// Generally what happens is:
// - Clipper lets you process the first element (DisplayStart = 0, DisplayEnd = 1) regardless of it being visible or not.
// - User code submit that one element.
// - Clipper can measure the height of the first element
// - Clipper calculate the actual range of elements to display based on the current clipping rectangle, position the cursor before the first visible element.
// - User code submit visible elements.
// - The clipper also handles various subtleties related to keyboard/gamepad navigation, wrapping etc.
struct ImGuiListClipper
{
    ImGuiContext*   Ctx;                // Parent UI context
    int             DisplayStart;       // First item to display, updated by each call to Step()
    int             DisplayEnd;         // End of items to display (exclusive)
    int             ItemsCount;         // [Internal] Number of items
    float           ItemsHeight;        // [Internal] Height of item after a first step and item submission can calculate it
    float           StartPosY;          // [Internal] Cursor position at the time of Begin() or after table frozen rows are all processed
    double          StartSeekOffsetY;   // [Internal] Account for frozen rows in a table and initial loss of precision in very large windows.
    void*           TempData;           // [Internal] Internal data

    // items_count: Use INT_MAX if you don't know how many items you have (in which case the cursor won't be advanced in the final step, and you can call SeekCursorForItem() manually if you need)
    // items_height: Use -1.0f to be calculated automatically on first step. Otherwise pass in the distance between your items, typically GetTextLineHeightWithSpacing() or GetFrameHeightWithSpacing().
     ImGuiListClipper();
     ~ImGuiListClipper();
     void  Begin(int items_count, float items_height = -1.0f);
     void  End();             // Automatically called on the last call of Step() that returns false.
     bool  Step();            // Call until it returns false. The DisplayStart/DisplayEnd fields will be set and you can process/draw those items.

    // Call IncludeItemByIndex() or IncludeItemsByIndex() *BEFORE* first call to Step() if you need a range of items to not be clipped, regardless of their visibility.
    // (Due to alignment / padding of certain items it is possible that an extra item may be included on either end of the display range).
    inline void     IncludeItemByIndex(int item_index)                  { IncludeItemsByIndex(item_index, item_index + 1); }
     void  IncludeItemsByIndex(int item_begin, int item_end);  // item_end is exclusive e.g. use (42, 42+1) to make item 42 never clipped.

    // Seek cursor toward given item. This is automatically called while stepping.
    // - The only reason to call this is: you can use ImGuiListClipper::Begin(INT_MAX) if you don't know item count ahead of time.
    // - In this case, after all steps are done, you'll want to call SeekCursorForItem(item_count).
     void  SeekCursorForItem(int item_index);






};

// Helpers: ImVec2/ImVec4 operators
// - It is important that we are keeping those disabled by default so they don't leak in user space.
// - This is in order to allow user enabling implicit cast operators between ImVec2/ImVec4 and their own types (using IM_VEC2_CLASS_EXTRA in imconfig.h)
// - Add '#define IMGUI_DEFINE_MATH_OPERATORS' before including this file (or in imconfig.h) to access courtesy maths operators for ImVec2 and ImVec4.
// - We intentionally provide ImVec2*float but not float*ImVec2: this is rare enough and we want to reduce the surface for possible user mistake.


























// Helpers macros to generate 32-bit encoded colors
// - User can declare their own format by #defining the 5 _SHIFT/_MASK macros in their imconfig file.
// - Any setting other than the default will need custom backend support. The only standard backend that supports anything else than the default is DirectX9.


















// Helper: ImColor() implicitly converts colors to either ImU32 (packed 4x1 byte) or ImVec4 (4x1 float)
// Prefer using IM_COL32() macros if you want a guaranteed compile-time ImU32 for usage with ImDrawList API.
// **Avoid storing ImColor! Store either u32 of ImVec4. This is not a full-featured color class. MAY OBSOLETE.
// **None of the ImGui API are using ImColor directly but you can use it as a convenience to pass colors in either ImU32 or ImVec4 formats. Explicitly cast to ImU32 or ImVec4 if needed.
struct ImColor
{
    ImVec4          Value;

    constexpr ImColor()                                             { }
    constexpr ImColor(float r, float g, float b, float a = 1.0f)    : Value(r, g, b, a) { }
    constexpr ImColor(const ImVec4& col)                            : Value(col) {}
    constexpr ImColor(int r, int g, int b, int a = 255)             : Value((float)r * (1.0f / 255.0f), (float)g * (1.0f / 255.0f), (float)b * (1.0f / 255.0f), (float)a* (1.0f / 255.0f)) {}
    constexpr ImColor(ImU32 rgba)                                   : Value((float)((rgba >> 0) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 8) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 16) & 0xFF) * (1.0f / 255.0f), (float)((rgba >> 24) & 0xFF) * (1.0f / 255.0f)) {}
    inline operator ImU32() const                                   { return ImGui::ColorConvertFloat4ToU32(Value); }
    inline operator ImVec4() const                                  { return Value; }

    // FIXME-OBSOLETE: May need to obsolete/cleanup those helpers.
    inline void    SetHSV(float h, float s, float v, float a = 1.0f){ ImGui::ColorConvertHSVtoRGB(h, s, v, Value.x, Value.y, Value.z); Value.w = a; }
    static ImColor HSV(float h, float s, float v, float a = 1.0f)   { float r, g, b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r, g, b, a); }
};

//-----------------------------------------------------------------------------
// [SECTION] Multi-Select API flags and structures (ImGuiMultiSelectFlags, ImGuiSelectionRequestType, ImGuiSelectionRequest, ImGuiMultiSelectIO, ImGuiSelectionBasicStorage)
//-----------------------------------------------------------------------------

// Multi-selection system
// Documentation at: https://github.com/ocornut/imgui/wiki/Multi-Select
// - Refer to 'Demo->Widgets->Selection State & Multi-Select' for demos using this.
// - This system implements standard multi-selection idioms (CTRL+Mouse/Keyboard, SHIFT+Mouse/Keyboard, etc)
//   with support for clipper (skipping non-visible items), box-select and many other details.
// - Selectable(), Checkbox() are supported but custom widgets may use it as well.
// - TreeNode() is technically supported but... using this correctly is more complicated: you need some sort of linear/random access to your tree,
//   which is suited to advanced trees setups also implementing filters and clipper. We will work toward simplifying and demoing it.
// - In the spirit of Dear ImGui design, your code owns actual selection data.
//   This is designed to allow all kinds of selection storage you may use in your application e.g. set/map/hash.
// About ImGuiSelectionBasicStorage:
// - This is an optional helper to store a selection state and apply selection requests.
// - It is used by our demos and provided as a convenience to quickly implement multi-selection.
// Usage:
// - Identify submitted items with SetNextItemSelectionUserData(), most likely using an index into your current data-set.
// - Store and maintain actual selection data using persistent object identifiers.
// - Usage flow:
//     BEGIN - (1) Call BeginMultiSelect() and retrieve the ImGuiMultiSelectIO* result.
//           - (2) Honor request list (SetAll/SetRange requests) by updating your selection data. Same code as Step 6.
//           - (3) [If using clipper] You need to make sure RangeSrcItem is always submitted. Calculate its index and pass to clipper.IncludeItemByIndex(). If storing indices in ImGuiSelectionUserData, a simple clipper.IncludeItemByIndex(ms_io->RangeSrcItem) call will work.
//     LOOP  - (4) Submit your items with SetNextItemSelectionUserData() + Selectable()/TreeNode() calls.
//     END   - (5) Call EndMultiSelect() and retrieve the ImGuiMultiSelectIO* result.
//           - (6) Honor request list (SetAll/SetRange requests) by updating your selection data. Same code as Step 2.
//     If you submit all items (no clipper), Step 2 and 3 are optional and will be handled by each item themselves. It is fine to always honor those steps.
// About ImGuiSelectionUserData:
// - This can store an application-defined identifier (e.g. index or pointer) submitted via SetNextItemSelectionUserData().
// - In return we store them into RangeSrcItem/RangeFirstItem/RangeLastItem and other fields in ImGuiMultiSelectIO.
// - Most applications will store an object INDEX, hence the chosen name and type. Storing an index is natural, because
//   SetRange requests will give you two end-points and you will need to iterate/interpolate between them to update your selection.
// - However it is perfectly possible to store a POINTER or another IDENTIFIER inside ImGuiSelectionUserData.
//   Our system never assume that you identify items by indices, it never attempts to interpolate between two values.
// - If you enable ImGuiMultiSelectFlags_NoRangeSelect then it is guaranteed that you will never have to interpolate
//   between two ImGuiSelectionUserData, which may be a convenient way to use part of the feature with less code work.
// - As most users will want to store an index, for convenience and to reduce confusion we use ImS64 instead of void*,
//   being syntactically easier to downcast. Feel free to reinterpret_cast and store a pointer inside.

// Flags for BeginMultiSelect()
enum ImGuiMultiSelectFlags_
{
    ImGuiMultiSelectFlags_None                  = 0,
    ImGuiMultiSelectFlags_SingleSelect          = 1 << 0,   // Disable selecting more than one item. This is available to allow single-selection code to share same code/logic if desired. It essentially disables the main purpose of BeginMultiSelect() tho!
    ImGuiMultiSelectFlags_NoSelectAll           = 1 << 1,   // Disable CTRL+A shortcut to select all.
    ImGuiMultiSelectFlags_NoRangeSelect         = 1 << 2,   // Disable Shift+selection mouse/keyboard support (useful for unordered 2D selection). With BoxSelect is also ensure contiguous SetRange requests are not combined into one. This allows not handling interpolation in SetRange requests.
    ImGuiMultiSelectFlags_NoAutoSelect          = 1 << 3,   // Disable selecting items when navigating (useful for e.g. supporting range-select in a list of checkboxes).
    ImGuiMultiSelectFlags_NoAutoClear           = 1 << 4,   // Disable clearing selection when navigating or selecting another one (generally used with ImGuiMultiSelectFlags_NoAutoSelect. useful for e.g. supporting range-select in a list of checkboxes).
    ImGuiMultiSelectFlags_NoAutoClearOnReselect = 1 << 5,   // Disable clearing selection when clicking/selecting an already selected item.
    ImGuiMultiSelectFlags_BoxSelect1d           = 1 << 6,   // Enable box-selection with same width and same x pos items (e.g. full row Selectable()). Box-selection works better with little bit of spacing between items hit-box in order to be able to aim at empty space.
    ImGuiMultiSelectFlags_BoxSelect2d           = 1 << 7,   // Enable box-selection with varying width or varying x pos items support (e.g. different width labels, or 2D layout/grid). This is slower: alters clipping logic so that e.g. horizontal movements will update selection of normally clipped items.
    ImGuiMultiSelectFlags_BoxSelectNoScroll     = 1 << 8,   // Disable scrolling when box-selecting near edges of scope.
    ImGuiMultiSelectFlags_ClearOnEscape         = 1 << 9,   // Clear selection when pressing Escape while scope is focused.
    ImGuiMultiSelectFlags_ClearOnClickVoid      = 1 << 10,  // Clear selection when clicking on empty location within scope.
    ImGuiMultiSelectFlags_ScopeWindow           = 1 << 11,  // Scope for _BoxSelect and _ClearOnClickVoid is whole window (Default). Use if BeginMultiSelect() covers a whole window or used a single time in same window.
    ImGuiMultiSelectFlags_ScopeRect             = 1 << 12,  // Scope for _BoxSelect and _ClearOnClickVoid is rectangle encompassing BeginMultiSelect()/EndMultiSelect(). Use if BeginMultiSelect() is called multiple times in same window.
    ImGuiMultiSelectFlags_SelectOnClick         = 1 << 13,  // Apply selection on mouse down when clicking on unselected item. (Default)
    ImGuiMultiSelectFlags_SelectOnClickRelease  = 1 << 14,  // Apply selection on mouse release when clicking an unselected item. Allow dragging an unselected item without altering selection.
    //ImGuiMultiSelectFlags_RangeSelect2d       = 1 << 15,  // Shift+Selection uses 2d geometry instead of linear sequence, so possible to use Shift+up/down to select vertically in grid. Analogous to what BoxSelect does.
    ImGuiMultiSelectFlags_NavWrapX              = 1 << 16,  // [Temporary] Enable navigation wrapping on X axis. Provided as a convenience because we don't have a design for the general Nav API for this yet. When the more general feature be public we may obsolete this flag in favor of new one.
};

// Main IO structure returned by BeginMultiSelect()/EndMultiSelect().
// This mainly contains a list of selection requests.
// - Use 'Demo->Tools->Debug Log->Selection' to see requests as they happen.
// - Some fields are only useful if your list is dynamic and allows deletion (getting post-deletion focus/state right is shown in the demo)
// - Below: who reads/writes each fields? 'r'=read, 'w'=write, 'ms'=multi-select code, 'app'=application/user code.
struct ImGuiMultiSelectIO
{
    //------------------------------------------// BeginMultiSelect / EndMultiSelect
    ImVector<ImGuiSelectionRequest> Requests;   //  ms:w, app:r     /  ms:w  app:r   // Requests to apply to your selection data.
    ImGuiSelectionUserData      RangeSrcItem;   //  ms:w  app:r     /                // (If using clipper) Begin: Source item (often the first selected item) must never be clipped: use clipper.IncludeItemByIndex() to ensure it is submitted.
    ImGuiSelectionUserData      NavIdItem;      //  ms:w, app:r     /                // (If using deletion) Last known SetNextItemSelectionUserData() value for NavId (if part of submitted items).
    bool                        NavIdSelected;  //  ms:w, app:r     /        app:r   // (If using deletion) Last known selection state for NavId (if part of submitted items).
    bool                        RangeSrcReset;  //        app:w     /  ms:r          // (If using deletion) Set before EndMultiSelect() to reset ResetSrcItem (e.g. if deleted selection).
    int                         ItemsCount;     //  ms:w, app:r     /        app:r   // 'int items_count' parameter to BeginMultiSelect() is copied here for convenience, allowing simpler calls to your ApplyRequests handler. Not used internally.
};

// Selection request type
enum ImGuiSelectionRequestType
{
    ImGuiSelectionRequestType_None = 0,
    ImGuiSelectionRequestType_SetAll,           // Request app to clear selection (if Selected==false) or select all items (if Selected==true). We cannot set RangeFirstItem/RangeLastItem as its contents is entirely up to user (not necessarily an index)
    ImGuiSelectionRequestType_SetRange,         // Request app to select/unselect [RangeFirstItem..RangeLastItem] items (inclusive) based on value of Selected. Only EndMultiSelect() request this, app code can read after BeginMultiSelect() and it will always be false.
};

// Selection request item
struct ImGuiSelectionRequest
{
    //------------------------------------------// BeginMultiSelect / EndMultiSelect
    ImGuiSelectionRequestType   Type;           //  ms:w, app:r     /  ms:w, app:r   // Request type. You'll most often receive 1 Clear + 1 SetRange with a single-item range.
    bool                        Selected;       //  ms:w, app:r     /  ms:w, app:r   // Parameter for SetAll/SetRange requests (true = select, false = unselect)
    ImS8                        RangeDirection; //                  /  ms:w  app:r   // Parameter for SetRange request: +1 when RangeFirstItem comes before RangeLastItem, -1 otherwise. Useful if you want to preserve selection order on a backward Shift+Click.
    ImGuiSelectionUserData      RangeFirstItem; //                  /  ms:w, app:r   // Parameter for SetRange request (this is generally == RangeSrcItem when shift selecting from top to bottom).
    ImGuiSelectionUserData      RangeLastItem;  //                  /  ms:w, app:r   // Parameter for SetRange request (this is generally == RangeSrcItem when shift selecting from bottom to top). Inclusive!
};

// Optional helper to store multi-selection state + apply multi-selection requests.
// - Used by our demos and provided as a convenience to easily implement basic multi-selection.
// - Iterate selection with 'void* it = NULL; ImGuiID id; while (selection.GetNextSelectedItem(&it, &id)) { ... }'
//   Or you can check 'if (Contains(id)) { ... }' for each possible object if their number is not too high to iterate.
// - USING THIS IS NOT MANDATORY. This is only a helper and not a required API.
// To store a multi-selection, in your application you could:
// - Use this helper as a convenience. We use our simple key->value ImGuiStorage as a std::set<ImGuiID> replacement.
// - Use your own external storage: e.g. std::set<MyObjectId>, std::vector<MyObjectId>, interval trees, intrusively stored selection etc.
// In ImGuiSelectionBasicStorage we:
// - always use indices in the multi-selection API (passed to SetNextItemSelectionUserData(), retrieved in ImGuiMultiSelectIO)
// - use the AdapterIndexToStorageId() indirection layer to abstract how persistent selection data is derived from an index.
// - use decently optimized logic to allow queries and insertion of very large selection sets.
// - do not preserve selection order.
// Many combinations are possible depending on how you prefer to store your items and how you prefer to store your selection.
// Large applications are likely to eventually want to get rid of this indirection layer and do their own thing.
// See https://github.com/ocornut/imgui/wiki/Multi-Select for details and pseudo-code using this helper.
struct ImGuiSelectionBasicStorage
{
    // Members
    int             Size;           //          // Number of selected items, maintained by this helper.
    bool            PreserveOrder;  // = false  // GetNextSelectedItem() will return ordered selection (currently implemented by two additional sorts of selection. Could be improved)
    void*           UserData;       // = NULL   // User data for use by adapter function        // e.g. selection.UserData = (void*)my_items;
    ImGuiID         (*AdapterIndexToStorageId)(ImGuiSelectionBasicStorage* self, int idx);      // e.g. selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { return ((MyItems**)self->UserData)[idx]->ID; };
    int             _SelectionOrder;// [Internal] Increasing counter to store selection order
    ImGuiStorage    _Storage;       // [Internal] Selection set. Think of this as similar to e.g. std::set<ImGuiID>. Prefer not accessing directly: iterate with GetNextSelectedItem().

    // Methods
     ImGuiSelectionBasicStorage();
     void  ApplyRequests(ImGuiMultiSelectIO* ms_io);   // Apply selection requests coming from BeginMultiSelect() and EndMultiSelect() functions. It uses 'items_count' passed to BeginMultiSelect()
     bool  Contains(ImGuiID id) const;                 // Query if an item id is in selection.
     void  Clear();                                    // Clear selection
     void  Swap(ImGuiSelectionBasicStorage& r);        // Swap two selections
     void  SetItemSelected(ImGuiID id, bool selected); // Add/remove an item from selection (generally done by ApplyRequests() function)
     bool  GetNextSelectedItem(void** opaque_it, ImGuiID* out_id); // Iterate selection with 'void* it = NULL; ImGuiID id; while (selection.GetNextSelectedItem(&it, &id)) { ... }'
    inline ImGuiID  GetStorageIdFromIndex(int idx)              { return AdapterIndexToStorageId(this, idx); }  // Convert index to item id based on provided adapter.
};

// Optional helper to apply multi-selection requests to existing randomly accessible storage.
// Convenient if you want to quickly wire multi-select API on e.g. an array of bool or items storing their own selection state.
struct ImGuiSelectionExternalStorage
{
    // Members
    void*           UserData;       // User data for use by adapter function                                // e.g. selection.UserData = (void*)my_items;
    void            (*AdapterSetItemSelected)(ImGuiSelectionExternalStorage* self, int idx, bool selected); // e.g. AdapterSetItemSelected = [](ImGuiSelectionExternalStorage* self, int idx, bool selected) { ((MyItems**)self->UserData)[idx]->Selected = selected; }

    // Methods
     ImGuiSelectionExternalStorage();
     void  ApplyRequests(ImGuiMultiSelectIO* ms_io);   // Apply selection requests by using AdapterSetItemSelected() calls
};

//-----------------------------------------------------------------------------
// [SECTION] Drawing API (ImDrawCmd, ImDrawIdx, ImDrawVert, ImDrawChannel, ImDrawListSplitter, ImDrawListFlags, ImDrawList, ImDrawData)
// Hold a series of drawing commands. The user provides a renderer for ImDrawData which essentially contains an array of ImDrawList.
//-----------------------------------------------------------------------------

// The maximum line width to bake anti-aliased textures for. Build atlas with ImFontAtlasFlags_NoBakedLines to disable baking.



// ImDrawCallback: Draw callbacks for advanced uses [configurable type: override in imconfig.h]
// NB: You most likely do NOT need to use draw callbacks just to create your own widget or customized UI rendering,
// you can poke into the draw list for that! Draw callback may be useful for example to:
//  A) Change your GPU render state,
//  B) render a complex 3D scene inside a UI element without an intermediate texture/render target, etc.
// The expected behavior from your rendering function is 'if (cmd.UserCallback != NULL) { cmd.UserCallback(parent_list, cmd); } else { RenderTriangles() }'
// If you want to override the signature of ImDrawCallback, you can simply use e.g. '#define ImDrawCallback MyDrawCallback' (in imconfig.h) + update rendering backend accordingly.

typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);

// Special Draw callback value to request renderer backend to reset the graphics/render state.
// The renderer backend needs to handle this special value, otherwise it will crash trying to call a function at this address.
// This is useful, for example, if you submitted callbacks which you know have altered the render state and you want it to be restored.
// Render state is not reset by default because they are many perfectly useful way of altering render state (e.g. changing shader/blending settings before an Image call).


// Typically, 1 command = 1 GPU draw call (unless command is a callback)
// - VtxOffset: When 'io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset' is enabled,
//   this fields allow us to render meshes larger than 64K vertices while keeping 16-bit indices.
//   Backends made for <1.71. will typically ignore the VtxOffset fields.
// - The ClipRect/TextureId/VtxOffset fields must be contiguous as we memcmp() them together (this is asserted for).
struct ImDrawCmd
{
    ImVec4          ClipRect;           // 4*4  // Clipping rectangle (x1, y1, x2, y2). Subtract ImDrawData->DisplayPos to get clipping rectangle in "viewport" coordinates
    ImTextureID     TextureId;          // 4-8  // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple fonts atlas.
    unsigned int    VtxOffset;          // 4    // Start offset in vertex buffer. ImGuiBackendFlags_RendererHasVtxOffset: always 0, otherwise may be >0 to support meshes larger than 64K vertices with 16-bit indices.
    unsigned int    IdxOffset;          // 4    // Start offset in index buffer.
    unsigned int    ElemCount;          // 4    // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
    ImDrawCallback  UserCallback;       // 4-8  // If != NULL, call the function instead of rendering the vertices. clip_rect and texture_id will be set normally.
    void*           UserCallbackData;   // 4-8  // Callback user data (when UserCallback != NULL). If called AddCallback() with size == 0, this is a copy of the AddCallback() argument. If called AddCallback() with size > 0, this is pointing to a buffer where data is stored.
    int             UserCallbackDataSize;  // 4 // Size of callback user data when using storage, otherwise 0.
    int             UserCallbackDataOffset;// 4 // [Internal] Offset of callback user data when using storage, otherwise -1.

    ImDrawCmd()     { memset(this, 0, sizeof(*this)); } // Also ensure our padding fields are zeroed

    // Since 1.83: returns ImTextureID associated with this draw call. Warning: DO NOT assume this is always same as 'TextureId' (we will change this function for an upcoming feature)
    inline ImTextureID GetTexID() const { return TextureId; }
};

// Vertex layout

struct ImDrawVert
{
    ImVec2  pos;
    ImVec2  uv;
    ImU32   col;
};







// [Internal] For use by ImDrawList
struct ImDrawCmdHeader
{
    ImVec4          ClipRect;
    ImTextureID     TextureId;
    unsigned int    VtxOffset;
};

// [Internal] For use by ImDrawListSplitter
struct ImDrawChannel
{
    ImVector<ImDrawCmd>         _CmdBuffer;
    ImVector<ImDrawIdx>         _IdxBuffer;
};

// Split/Merge functions are used to split the draw list into different layers which can be drawn into out of order.
// This is used by the Columns/Tables API, so items of each column can be batched together in a same draw call.
struct ImDrawListSplitter
{
    int                         _Current;    // Current channel number (0)
    int                         _Count;      // Number of active channels (1+)
    ImVector<ImDrawChannel>     _Channels;   // Draw channels (not resized down so _Count might be < Channels.Size)

    inline ImDrawListSplitter()  { memset(this, 0, sizeof(*this)); }
    inline ~ImDrawListSplitter() { ClearFreeMemory(); }
    inline void                 Clear() { _Current = 0; _Count = 1; } // Do not clear Channels[] so our allocations are reused next frame
     void              ClearFreeMemory();
     void              Split(ImDrawList* draw_list, int count);
     void              Merge(ImDrawList* draw_list);
     void              SetCurrentChannel(ImDrawList* draw_list, int channel_idx);
};

// Flags for ImDrawList functions
// (Legacy: bit 0 must always correspond to ImDrawFlags_Closed to be backward compatible with old API using a bool. Bits 1..3 must be unused)
enum ImDrawFlags_
{
    ImDrawFlags_None                        = 0,
    ImDrawFlags_Closed                      = 1 << 0, // PathStroke(), AddPolyline(): specify that shape should be closed (Important: this is always == 1 for legacy reason)
    ImDrawFlags_RoundCornersTopLeft         = 1 << 4, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-left corner only (when rounding > 0.0f, we default to all corners). Was 0x01.
    ImDrawFlags_RoundCornersTopRight        = 1 << 5, // AddRect(), AddRectFilled(), PathRect(): enable rounding top-right corner only (when rounding > 0.0f, we default to all corners). Was 0x02.
    ImDrawFlags_RoundCornersBottomLeft      = 1 << 6, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-left corner only (when rounding > 0.0f, we default to all corners). Was 0x04.
    ImDrawFlags_RoundCornersBottomRight     = 1 << 7, // AddRect(), AddRectFilled(), PathRect(): enable rounding bottom-right corner only (when rounding > 0.0f, we default to all corners). Wax 0x08.
    ImDrawFlags_RoundCornersNone            = 1 << 8, // AddRect(), AddRectFilled(), PathRect(): disable rounding on all corners (when rounding > 0.0f). This is NOT zero, NOT an implicit flag!
    ImDrawFlags_RoundCornersTop             = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersBottom          = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersLeft            = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersTopLeft,
    ImDrawFlags_RoundCornersRight           = ImDrawFlags_RoundCornersBottomRight | ImDrawFlags_RoundCornersTopRight,
    ImDrawFlags_RoundCornersAll             = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,
    ImDrawFlags_RoundCornersDefault_        = ImDrawFlags_RoundCornersAll, // Default to ALL corners if none of the _RoundCornersXX flags are specified.
    ImDrawFlags_RoundCornersMask_           = ImDrawFlags_RoundCornersAll | ImDrawFlags_RoundCornersNone,
};

// Flags for ImDrawList instance. Those are set automatically by ImGui:: functions from ImGuiIO settings, and generally not manipulated directly.
// It is however possible to temporarily alter flags between calls to ImDrawList:: functions.
enum ImDrawListFlags_
{
    ImDrawListFlags_None                    = 0,
    ImDrawListFlags_AntiAliasedLines        = 1 << 0,  // Enable anti-aliased lines/borders (*2 the number of triangles for 1.0f wide line or lines thin enough to be drawn using textures, otherwise *3 the number of triangles)
    ImDrawListFlags_AntiAliasedLinesUseTex  = 1 << 1,  // Enable anti-aliased lines/borders using textures when possible. Require backend to render with bilinear filtering (NOT point/nearest filtering).
    ImDrawListFlags_AntiAliasedFill         = 1 << 2,  // Enable anti-aliased edge around filled shapes (rounded rectangles, circles).
    ImDrawListFlags_AllowVtxOffset          = 1 << 3,  // Can emit 'VtxOffset > 0' to allow large meshes. Set when 'ImGuiBackendFlags_RendererHasVtxOffset' is enabled.
};

// Draw command list
// This is the low-level list of polygons that ImGui:: functions are filling. At the end of the frame,
// all command lists are passed to your ImGuiIO::RenderDrawListFn function for rendering.
// Each dear imgui window contains its own ImDrawList. You can use ImGui::GetWindowDrawList() to
// access the current window draw list and draw custom primitives.
// You can interleave normal ImGui:: calls and adding primitives to the current draw list.
// In single viewport mode, top-left is == GetMainViewport()->Pos (generally 0,0), bottom-right is == GetMainViewport()->Pos+Size (generally io.DisplaySize).
// You are totally free to apply whatever transformation matrix you want to the data (depending on the use of the transformation you may want to apply it to ClipRect as well!)
// Important: Primitives are always added to the list and not culled (culling is done at higher-level by ImGui:: functions), if you use this API a lot consider coarse culling your drawn objects.
struct ImDrawList
{
    // This is what you have to render
    ImVector<ImDrawCmd>     CmdBuffer;          // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
    ImVector<ImDrawIdx>     IdxBuffer;          // Index buffer. Each command consume ImDrawCmd::ElemCount of those
    ImVector<ImDrawVert>    VtxBuffer;          // Vertex buffer.
    ImDrawListFlags         Flags;              // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.

    // [Internal, used while building lists]
    unsigned int            _VtxCurrentIdx;     // [Internal] generally == VtxBuffer.Size unless we are past 64K vertices, in which case this gets reset to 0.
    ImDrawListSharedData*   _Data;              // Pointer to shared draw data (you can use ImGui::GetDrawListSharedData() to get the one from current ImGui context)
    ImDrawVert*             _VtxWritePtr;       // [Internal] point within VtxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImDrawIdx*              _IdxWritePtr;       // [Internal] point within IdxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImVector<ImVec2>        _Path;              // [Internal] current path building
    ImDrawCmdHeader         _CmdHeader;         // [Internal] template of active commands. Fields should match those of CmdBuffer.back().
    ImDrawListSplitter      _Splitter;          // [Internal] for channels api (note: prefer using your own persistent instance of ImDrawListSplitter!)
    ImVector<ImVec4>        _ClipRectStack;     // [Internal]
    ImVector<ImTextureID>   _TextureIdStack;    // [Internal]
    ImVector<ImU8>          _CallbacksDataBuf;  // [Internal]
    float                   _FringeScale;       // [Internal] anti-alias fringe is scaled by this value, this helps to keep things sharp while zooming at vertex buffer content
    const char*             _OwnerName;         // Pointer to owner window's name for debugging

    // If you want to create ImDrawList instances, pass them ImGui::GetDrawListSharedData().
    // (advanced: you may create and use your own ImDrawListSharedData so you can use ImDrawList without ImGui, but that's more involved)
     ImDrawList(ImDrawListSharedData* shared_data);
     ~ImDrawList();

     void  PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect = false);  // Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
     void  PushClipRectFullScreen();
     void  PopClipRect();
     void  PushTextureID(ImTextureID texture_id);
     void  PopTextureID();
    inline ImVec2   GetClipRectMin() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.x, cr.y); }
    inline ImVec2   GetClipRectMax() const { const ImVec4& cr = _ClipRectStack.back(); return ImVec2(cr.z, cr.w); }

    // Primitives
    // - Filled shapes must always use clockwise winding order. The anti-aliasing fringe depends on it. Counter-clockwise shapes will have "inward" anti-aliasing.
    // - For rectangular primitives, "p_min" and "p_max" represent the upper-left and lower-right corners.
    // - For circle primitives, use "num_segments == 0" to automatically calculate tessellation (preferred).
    //   In older versions (until Dear ImGui 1.77) the AddCircle functions defaulted to num_segments == 12.
    //   In future versions we will use textures to provide cheaper and higher-quality circles.
    //   Use AddNgon() and AddNgonFilled() functions if you need to guarantee a specific number of sides.
     void  AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f);
     void  AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0, float thickness = 1.0f);   // a: upper-left, b: lower-right (== upper-left + size)
     void  AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0);                     // a: upper-left, b: lower-right (== upper-left + size)
     void  AddRectFilledMultiColor(const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
     void  AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
     void  AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
     void  AddTriangle(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness = 1.0f);
     void  AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col);
     void  AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.0f);
     void  AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 0);
     void  AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
     void  AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
     void  AddEllipse(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f);
     void  AddEllipseFilled(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot = 0.0f, int num_segments = 0);
     void  AddText(const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = ((void *)0));
     void  AddText(ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = ((void *)0), float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = ((void *)0));
     void  AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0); // Cubic Bezier (4 control points)
     void  AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness, int num_segments = 0);               // Quadratic Bezier (3 control points)

    // General polygon
    // - Only simple polygons are supported by filling functions (no self-intersections, no holes).
    // - Concave polygon fill is more expensive than convex one: it has O(N^2) complexity. Provided as a convenience fo user but not used by main library.
     void  AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
     void  AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
     void  AddConcavePolyFilled(const ImVec2* points, int num_points, ImU32 col);

    // Image primitives
    // - Read FAQ to understand what ImTextureID is.
    // - "p_min" and "p_max" represent the upper-left and lower-right corners of the rectangle.
    // - "uv_min" and "uv_max" represent the normalized texture coordinates to use for those corners. Using (0,0)->(1,1) texture coordinates will generally display the entire texture.
     void  AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(255)<<16) | ((ImU32)(255)<<8) | ((ImU32)(255)<<0)));
     void  AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(255)<<16) | ((ImU32)(255)<<8) | ((ImU32)(255)<<0)));
     void  AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawFlags flags = 0);

    // Stateful path API, add points then finish with PathFillConvex() or PathStroke()
    // - Important: filled shapes must always use clockwise winding order! The anti-aliasing fringe depends on it. Counter-clockwise shapes will have "inward" anti-aliasing.
    //   so e.g. 'PathArcTo(center, radius, PI * -0.5f, PI)' is ok, whereas 'PathArcTo(center, radius, PI, PI * -0.5f)' won't have correct anti-aliasing when followed by PathFillConvex().
    inline    void  PathClear()                                                 { _Path.Size = 0; }
    inline    void  PathLineTo(const ImVec2& pos)                               { _Path.push_back(pos); }
    inline    void  PathLineToMergeDuplicate(const ImVec2& pos)                 { if (_Path.Size == 0 || memcmp(&_Path.Data[_Path.Size - 1], &pos, 8) != 0) _Path.push_back(pos); }
    inline    void  PathFillConvex(ImU32 col)                                   { AddConvexPolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; }
    inline    void  PathFillConcave(ImU32 col)                                  { AddConcavePolyFilled(_Path.Data, _Path.Size, col); _Path.Size = 0; }
    inline    void  PathStroke(ImU32 col, ImDrawFlags flags = 0, float thickness = 1.0f) { AddPolyline(_Path.Data, _Path.Size, col, flags, thickness); _Path.Size = 0; }
     void  PathArcTo(const ImVec2& center, float radius, float a_min, float a_max, int num_segments = 0);
     void  PathArcToFast(const ImVec2& center, float radius, int a_min_of_12, int a_max_of_12);                // Use precomputed angles for a 12 steps circle
     void  PathEllipticalArcTo(const ImVec2& center, const ImVec2& radius, float rot, float a_min, float a_max, int num_segments = 0); // Ellipse
     void  PathBezierCubicCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0); // Cubic Bezier (4 control points)
     void  PathBezierQuadraticCurveTo(const ImVec2& p2, const ImVec2& p3, int num_segments = 0);               // Quadratic Bezier (3 control points)
     void  PathRect(const ImVec2& rect_min, const ImVec2& rect_max, float rounding = 0.0f, ImDrawFlags flags = 0);

    // Advanced: Draw Callbacks
    // - May be used to alter render state (change sampler, blending, current shader). May be used to emit custom rendering commands (difficult to do correctly, but possible).
    // - Use special ImDrawCallback_ResetRenderState callback to instruct backend to reset its render state to the default.
    // - Your rendering loop must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles. All standard backends are honoring this.
    // - For some backends, the callback may access selected render-states exposed by the backend in a ImGui_ImplXXXX_RenderState structure pointed to by platform_io.Renderer_RenderState.
    // - IMPORTANT: please be mindful of the different level of indirection between using size==0 (copying argument) and using size>0 (copying pointed data into a buffer).
    //   - If userdata_size == 0: we copy/store the 'userdata' argument as-is. It will be available unmodified in ImDrawCmd::UserCallbackData during render.
    //   - If userdata_size > 0,  we copy/store 'userdata_size' bytes pointed to by 'userdata'. We store them in a buffer stored inside the drawlist. ImDrawCmd::UserCallbackData will point inside that buffer so you have to retrieve data from there. Your callback may need to use ImDrawCmd::UserCallbackDataSize if you expect dynamically-sized data.
    //   - Support for userdata_size > 0 was added in v1.91.4, October 2024. So earlier code always only allowed to copy/store a simple void*.
     void  AddCallback(ImDrawCallback callback, void* userdata, size_t userdata_size = 0);

    // Advanced: Miscellaneous
     void  AddDrawCmd();                                               // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible
     ImDrawList* CloneOutput() const;                                  // Create a clone of the CmdBuffer/IdxBuffer/VtxBuffer.

    // Advanced: Channels
    // - Use to split render into layers. By switching channels to can render out-of-order (e.g. submit FG primitives before BG primitives)
    // - Use to minimize draw calls (e.g. if going back-and-forth between multiple clipping rectangles, prefer to append into separate channels then merge at the end)
    // - This API shouldn't have been in ImDrawList in the first place!
    //   Prefer using your own persistent instance of ImDrawListSplitter as you can stack them.
    //   Using the ImDrawList::ChannelsXXXX you cannot stack a split over another.
    inline void     ChannelsSplit(int count)    { _Splitter.Split(this, count); }
    inline void     ChannelsMerge()             { _Splitter.Merge(this); }
    inline void     ChannelsSetCurrent(int n)   { _Splitter.SetCurrentChannel(this, n); }

    // Advanced: Primitives allocations
    // - We render triangles (three vertices)
    // - All primitives needs to be reserved via PrimReserve() beforehand.
     void  PrimReserve(int idx_count, int vtx_count);
     void  PrimUnreserve(int idx_count, int vtx_count);
     void  PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col);      // Axis aligned rectangle (composed of two triangles)
     void  PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
     void  PrimQuadUV(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, const ImVec2& uv_a, const ImVec2& uv_b, const ImVec2& uv_c, const ImVec2& uv_d, ImU32 col);
    inline    void  PrimWriteVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col)    { _VtxWritePtr->pos = pos; _VtxWritePtr->uv = uv; _VtxWritePtr->col = col; _VtxWritePtr++; _VtxCurrentIdx++; }
    inline    void  PrimWriteIdx(ImDrawIdx idx)                                     { *_IdxWritePtr = idx; _IdxWritePtr++; }
    inline    void  PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col)         { PrimWriteIdx((ImDrawIdx)_VtxCurrentIdx); PrimWriteVtx(pos, uv, col); } // Write vertex with unique index

    // Obsolete names
    //inline  void  AddEllipse(const ImVec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f) { AddEllipse(center, ImVec2(radius_x, radius_y), col, rot, num_segments, thickness); } // OBSOLETED in 1.90.5 (Mar 2024)
    //inline  void  AddEllipseFilled(const ImVec2& center, float radius_x, float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0) { AddEllipseFilled(center, ImVec2(radius_x, radius_y), col, rot, num_segments); }                        // OBSOLETED in 1.90.5 (Mar 2024)
    //inline  void  PathEllipticalArcTo(const ImVec2& center, float radius_x, float radius_y, float rot, float a_min, float a_max, int num_segments = 0) { PathEllipticalArcTo(center, ImVec2(radius_x, radius_y), rot, a_min, a_max, num_segments); } // OBSOLETED in 1.90.5 (Mar 2024)
    //inline  void  AddBezierCurve(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0) { AddBezierCubic(p1, p2, p3, p4, col, thickness, num_segments); }                         // OBSOLETED in 1.80 (Jan 2021)
    //inline  void  PathBezierCurveTo(const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, int num_segments = 0) { PathBezierCubicCurveTo(p2, p3, p4, num_segments); }                                                                                // OBSOLETED in 1.80 (Jan 2021)

    // [Internal helpers]
     void  _ResetForNewFrame();
     void  _ClearFreeMemory();
     void  _PopUnusedDrawCmd();
     void  _TryMergeDrawCmds();
     void  _OnChangedClipRect();
     void  _OnChangedTextureID();
     void  _OnChangedVtxOffset();
     void  _SetTextureID(ImTextureID texture_id);
     int   _CalcCircleAutoSegmentCount(float radius) const;
     void  _PathArcToFastEx(const ImVec2& center, float radius, int a_min_sample, int a_max_sample, int a_step);
     void  _PathArcToN(const ImVec2& center, float radius, float a_min, float a_max, int num_segments);
};

// All draw data to render a Dear ImGui frame
// (NB: the style and the naming convention here is a little inconsistent, we currently preserve them for backward compatibility purpose,
// as this is one of the oldest structure exposed by the library! Basically, ImDrawList == CmdList)
struct ImDrawData
{
    bool                Valid;              // Only valid after Render() is called and before the next NewFrame() is called.
    int                 CmdListsCount;      // Number of ImDrawList* to render
    int                 TotalIdxCount;      // For convenience, sum of all ImDrawList's IdxBuffer.Size
    int                 TotalVtxCount;      // For convenience, sum of all ImDrawList's VtxBuffer.Size
    ImVector<ImDrawList*> CmdLists;         // Array of ImDrawList* to render. The ImDrawLists are owned by ImGuiContext and only pointed to from here.
    ImVec2              DisplayPos;         // Top-left position of the viewport to render (== top-left of the orthogonal projection matrix to use) (== GetMainViewport()->Pos for the main viewport, == (0.0) in most single-viewport applications)
    ImVec2              DisplaySize;        // Size of the viewport to render (== GetMainViewport()->Size for the main viewport, == io.DisplaySize in most single-viewport applications)
    ImVec2              FramebufferScale;   // Amount of pixels for each unit of DisplaySize. Based on io.DisplayFramebufferScale. Generally (1,1) on normal display, (2,2) on OSX with Retina display.
    ImGuiViewport*      OwnerViewport;      // Viewport carrying the ImDrawData instance, might be of use to the renderer (generally not).

    // Functions
    ImDrawData()    { Clear(); }
     void  Clear();
     void  AddDrawList(ImDrawList* draw_list);     // Helper to add an external draw list into an existing ImDrawData.
     void  DeIndexAllBuffers();                    // Helper to convert all buffers from indexed to non-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
     void  ScaleClipRects(const ImVec2& fb_scale); // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than Dear ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
};

//-----------------------------------------------------------------------------
// [SECTION] Font API (ImFontConfig, ImFontGlyph, ImFontAtlasFlags, ImFontAtlas, ImFontGlyphRangesBuilder, ImFont)
//-----------------------------------------------------------------------------

// A font input/source (we may rename this to ImFontSource in the future)
struct ImFontConfig
{
    void*           FontData;               //          // TTF/OTF data
    int             FontDataSize;           //          // TTF/OTF data size
    bool            FontDataOwnedByAtlas;   // true     // TTF/OTF data ownership taken by the container ImFontAtlas (will delete memory itself).
    bool            MergeMode;              // false    // Merge into previous ImFont, so you can combine multiple inputs font into one ImFont (e.g. ASCII font + icons + Japanese glyphs). You may want to use GlyphOffset.y when merge font of different heights.
    bool            PixelSnapH;             // false    // Align every glyph AdvanceX to pixel boundaries. Useful e.g. if you are merging a non-pixel aligned font with the default font. If enabled, you can set OversampleH/V to 1.
    int             FontNo;                 // 0        // Index of font within TTF/OTF file
    int             OversampleH;            // 0 (2)    // Rasterize at higher quality for sub-pixel positioning. 0 == auto == 1 or 2 depending on size. Note the difference between 2 and 3 is minimal. You can reduce this to 1 for large glyphs save memory. Read https://github.com/nothings/stb/blob/master/tests/oversample/README.md for details.
    int             OversampleV;            // 0 (1)    // Rasterize at higher quality for sub-pixel positioning. 0 == auto == 1. This is not really useful as we don't use sub-pixel positions on the Y axis.
    float           SizePixels;             //          // Size in pixels for rasterizer (more or less maps to the resulting font height).
    ImVec2          GlyphExtraSpacing;      // 0, 0     // Extra spacing (in pixels) between glyphs when rendered: essentially add to glyph->AdvanceX. Only X axis is supported for now.
    ImVec2          GlyphOffset;            // 0, 0     // Offset all glyphs from this font input.
    const ImWchar*  GlyphRanges;            // NULL     // THE ARRAY DATA NEEDS TO PERSIST AS LONG AS THE FONT IS ALIVE. Pointer to a user-provided list of Unicode range (2 value per range, values are inclusive, zero-terminated list).
    float           GlyphMinAdvanceX;       // 0        // Minimum AdvanceX for glyphs, set Min to align font icons, set both Min/Max to enforce mono-space font
    float           GlyphMaxAdvanceX;       // FLT_MAX  // Maximum AdvanceX for glyphs
    unsigned int    FontBuilderFlags;       // 0        // Settings for custom font builder. THIS IS BUILDER IMPLEMENTATION DEPENDENT. Leave as zero if unsure.
    float           RasterizerMultiply;     // 1.0f     // Linearly brighten (>1.0f) or darken (<1.0f) font output. Brightening small fonts may be a good workaround to make them more readable. This is a silly thing we may remove in the future.
    float           RasterizerDensity;      // 1.0f     // DPI scale for rasterization, not altering other font metrics: make it easy to swap between e.g. a 100% and a 400% fonts for a zooming display. IMPORTANT: If you increase this it is expected that you increase font scale accordingly, otherwise quality may look lowered.
    ImWchar         EllipsisChar;           // 0        // Explicitly specify Unicode codepoint of ellipsis character. When fonts are being merged first specified ellipsis will be used.

    // [Internal]
    char            Name[40];               // Name (strictly to ease debugging)
    ImFont*         DstFont;

     ImFontConfig();
};

// Hold rendering data for one glyph.
// (Note: some language parsers may fail to convert the 31+1 bitfield members, in this case maybe drop store a single u32 or we can rework this)
struct ImFontGlyph
{
    unsigned int    Colored : 1;        // Flag to indicate glyph is colored and should generally ignore tinting (make it usable with no shift on little-endian as this is used in loops)
    unsigned int    Visible : 1;        // Flag to indicate glyph has no visible pixels (e.g. space). Allow early out when rendering.
    unsigned int    Codepoint : 30;     // 0x0000..0x10FFFF
    float           AdvanceX;           // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
    float           X0, Y0, X1, Y1;     // Glyph corners
    float           U0, V0, U1, V1;     // Texture coordinates
};

// Helper to build glyph ranges from text/string data. Feed your application strings/characters to it then call BuildRanges().
// This is essentially a tightly packed of vector of 64k booleans = 8KB storage.
struct ImFontGlyphRangesBuilder
{
    ImVector<ImU32> UsedChars;            // Store 1-bit per Unicode code point (0=unused, 1=used)

    ImFontGlyphRangesBuilder()              { Clear(); }
    inline void     Clear()                 { int size_in_bytes = (0xFFFF + 1) / 8; UsedChars.resize(size_in_bytes / (int)sizeof(ImU32)); memset(UsedChars.Data, 0, (size_t)size_in_bytes); }
    inline bool     GetBit(size_t n) const  { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); return (UsedChars[off] & mask) != 0; }  // Get bit n in the array
    inline void     SetBit(size_t n)        { int off = (int)(n >> 5); ImU32 mask = 1u << (n & 31); UsedChars[off] |= mask; }               // Set bit n in the array
    inline void     AddChar(ImWchar c)      { SetBit(c); }                      // Add character
     void  AddText(const char* text, const char* text_end = ((void *)0));     // Add string (each character of the UTF-8 string are added)
     void  AddRanges(const ImWchar* ranges);                           // Add ranges, e.g. builder.AddRanges(ImFontAtlas::GetGlyphRangesDefault()) to force add all of ASCII/Latin+Ext
     void  BuildRanges(ImVector<ImWchar>* out_ranges);                 // Output new ranges
};

// See ImFontAtlas::AddCustomRectXXX functions.
struct ImFontAtlasCustomRect
{
    unsigned short  X, Y;           // Output   // Packed position in Atlas

    // [Internal]
    unsigned short  Width, Height;  // Input    // Desired rectangle dimension
    unsigned int    GlyphID : 31;   // Input    // For custom font glyphs only (ID < 0x110000)
    unsigned int    GlyphColored : 1; // Input  // For custom font glyphs only: glyph is colored, removed tinting.
    float           GlyphAdvanceX;  // Input    // For custom font glyphs only: glyph xadvance
    ImVec2          GlyphOffset;    // Input    // For custom font glyphs only: glyph display offset
    ImFont*         Font;           // Input    // For custom font glyphs only: target font
    ImFontAtlasCustomRect()         { X = Y = 0xFFFF; Width = Height = 0; GlyphID = 0; GlyphColored = 0; GlyphAdvanceX = 0.0f; GlyphOffset = ImVec2(0, 0); Font = ((void *)0); }
    bool IsPacked() const           { return X != 0xFFFF; }
};

// Flags for ImFontAtlas build
enum ImFontAtlasFlags_
{
    ImFontAtlasFlags_None               = 0,
    ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,   // Don't round the height to next power of two
    ImFontAtlasFlags_NoMouseCursors     = 1 << 1,   // Don't build software mouse cursors into the atlas (save a little texture memory)
    ImFontAtlasFlags_NoBakedLines       = 1 << 2,   // Don't build thick line textures into the atlas (save a little texture memory, allow support for point/nearest filtering). The AntiAliasedLinesUseTex features uses them, otherwise they will be rendered using polygons (more expensive for CPU/GPU).
};

// Load and rasterize multiple TTF/OTF fonts into a same texture. The font atlas will build a single texture holding:
//  - One or more fonts.
//  - Custom graphics data needed to render the shapes needed by Dear ImGui.
//  - Mouse cursor shapes for software cursor rendering (unless setting 'Flags |= ImFontAtlasFlags_NoMouseCursors' in the font atlas).
// It is the user-code responsibility to setup/build the atlas, then upload the pixel data into a texture accessible by your graphics api.
//  - Optionally, call any of the AddFont*** functions. If you don't call any, the default font embedded in the code will be loaded for you.
//  - Call GetTexDataAsAlpha8() or GetTexDataAsRGBA32() to build and retrieve pixels data.
//  - Upload the pixels data into a texture within your graphics system (see imgui_impl_xxxx.cpp examples)
//  - Call SetTexID(my_tex_id); and pass the pointer/identifier to your texture in a format natural to your graphics API.
//    This value will be passed back to you during rendering to identify the texture. Read FAQ entry about ImTextureID for more details.
// Common pitfalls:
// - If you pass a 'glyph_ranges' array to AddFont*** functions, you need to make sure that your array persist up until the
//   atlas is build (when calling GetTexData*** or Build()). We only copy the pointer, not the data.
// - Important: By default, AddFontFromMemoryTTF() takes ownership of the data. Even though we are not writing to it, we will free the pointer on destruction.
//   You can set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed,
// - Even though many functions are suffixed with "TTF", OTF data is supported just as well.
// - This is an old API and it is currently awkward for those and various other reasons! We will address them in the future!
struct ImFontAtlas
{
     ImFontAtlas();
     ~ImFontAtlas();
     ImFont*           AddFont(const ImFontConfig* font_cfg);
     ImFont*           AddFontDefault(const ImFontConfig* font_cfg = ((void *)0));
     ImFont*           AddFontFromFileTTF(const char* filename, float size_pixels, const ImFontConfig* font_cfg = ((void *)0), const ImWchar* glyph_ranges = ((void *)0));
     ImFont*           AddFontFromMemoryTTF(void* font_data, int font_data_size, float size_pixels, const ImFontConfig* font_cfg = ((void *)0), const ImWchar* glyph_ranges = ((void *)0)); // Note: Transfer ownership of 'ttf_data' to ImFontAtlas! Will be deleted after destruction of the atlas. Set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed.
     ImFont*           AddFontFromMemoryCompressedTTF(const void* compressed_font_data, int compressed_font_data_size, float size_pixels, const ImFontConfig* font_cfg = ((void *)0), const ImWchar* glyph_ranges = ((void *)0)); // 'compressed_font_data' still owned by caller. Compress with binary_to_compressed_c.cpp.
     ImFont*           AddFontFromMemoryCompressedBase85TTF(const char* compressed_font_data_base85, float size_pixels, const ImFontConfig* font_cfg = ((void *)0), const ImWchar* glyph_ranges = ((void *)0));              // 'compressed_font_data_base85' still owned by caller. Compress with binary_to_compressed_c.cpp with -base85 parameter.
     void              ClearInputData();           // Clear input data (all ImFontConfig structures including sizes, TTF data, glyph ranges, etc.) = all the data used to build the texture and fonts.
     void              ClearFonts();               // Clear input+output font data (same as ClearInputData() + glyphs storage, UV coordinates).
     void              ClearTexData();             // Clear output texture data (CPU side). Saves RAM once the texture has been copied to graphics memory.
     void              Clear();                    // Clear all input and output.

    // Build atlas, retrieve pixel data.
    // User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
    // The pitch is always = Width * BytesPerPixels (1 or 4)
    // Building in RGBA32 format is provided for convenience and compatibility, but note that unless you manually manipulate or copy color data into
    // the texture (e.g. when using the AddCustomRect*** api), then the RGB pixels emitted will always be white (~75% of memory/bandwidth waste.
     bool              Build();                    // Build pixels data. This is called automatically for you by the GetTexData*** functions.
     void              GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = ((void *)0));  // 1 byte per-pixel
     void              GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = ((void *)0));  // 4 bytes-per-pixel
    bool                        IsBuilt() const             { return Fonts.Size > 0 && TexReady; } // Bit ambiguous: used to detect when user didn't build texture but effectively we should check TexID != 0 except that would be backend dependent...
    void                        SetTexID(ImTextureID id)    { TexID = id; }

    //-------------------------------------------
    // Glyph Ranges
    //-------------------------------------------

    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // NB: Make sure that your string are UTF-8 and NOT in your local code page.
    // Read https://github.com/ocornut/imgui/blob/master/docs/FONTS.md/#about-utf-8-encoding for details.
    // NB: Consider using ImFontGlyphRangesBuilder to build glyph ranges from textual data.
     const ImWchar*    GetGlyphRangesDefault();                // Basic Latin, Extended Latin
     const ImWchar*    GetGlyphRangesGreek();                  // Default + Greek and Coptic
     const ImWchar*    GetGlyphRangesKorean();                 // Default + Korean characters
     const ImWchar*    GetGlyphRangesJapanese();               // Default + Hiragana, Katakana, Half-Width, Selection of 2999 Ideographs
     const ImWchar*    GetGlyphRangesChineseFull();            // Default + Half-Width + Japanese Hiragana/Katakana + full set of about 21000 CJK Unified Ideographs
     const ImWchar*    GetGlyphRangesChineseSimplifiedCommon();// Default + Half-Width + Japanese Hiragana/Katakana + set of 2500 CJK Unified Ideographs for common simplified Chinese
     const ImWchar*    GetGlyphRangesCyrillic();               // Default + about 400 Cyrillic characters
     const ImWchar*    GetGlyphRangesThai();                   // Default + Thai characters
     const ImWchar*    GetGlyphRangesVietnamese();             // Default + Vietnamese characters

    //-------------------------------------------
    // [ALPHA] Custom Rectangles/Glyphs API
    //-------------------------------------------

    // You can request arbitrary rectangles to be packed into the atlas, for your own purposes.
    // - After calling Build(), you can query the rectangle position and render your pixels.
    // - If you render colored output, set 'atlas->TexPixelsUseColors = true' as this may help some backends decide of preferred texture format.
    // - You can also request your rectangles to be mapped as font glyph (given a font + Unicode point),
    //   so you can render e.g. custom colorful icons and use them as regular glyphs.
    // - Read docs/FONTS.md for more details about using colorful icons.
    // - Note: this API may be redesigned later in order to support multi-monitor varying DPI settings.
     int               AddCustomRectRegular(int width, int height);
     int               AddCustomRectFontGlyph(ImFont* font, ImWchar id, int width, int height, float advance_x, const ImVec2& offset = ImVec2(0, 0));
    ImFontAtlasCustomRect*      GetCustomRectByIndex(int index) { (void)( (!!(index >= 0)) || (_wassert(L"index >= 0", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(3519)), 0) ); return &CustomRects[index]; }

    // [Internal]
     void              CalcCustomRectUV(const ImFontAtlasCustomRect* rect, ImVec2* out_uv_min, ImVec2* out_uv_max) const;
     bool              GetMouseCursorTexData(ImGuiMouseCursor cursor, ImVec2* out_offset, ImVec2* out_size, ImVec2 out_uv_border[2], ImVec2 out_uv_fill[2]);

    //-------------------------------------------
    // Members
    //-------------------------------------------

    ImFontAtlasFlags            Flags;              // Build flags (see ImFontAtlasFlags_)
    ImTextureID                 TexID;              // User data to refer to the texture once it has been uploaded to user's graphic systems. It is passed back to you during rendering via the ImDrawCmd structure.
    int                         TexDesiredWidth;    // Texture width desired by user before Build(). Must be a power-of-two. If have many glyphs your graphics API have texture size restrictions you may want to increase texture width to decrease height.
    int                         TexGlyphPadding;    // FIXME: Should be called "TexPackPadding". Padding between glyphs within texture in pixels. Defaults to 1. If your rendering method doesn't rely on bilinear filtering you may set this to 0 (will also need to set AntiAliasedLinesUseTex = false).
    void*                       UserData;           // Store your own atlas related user-data (if e.g. you have multiple font atlas).

    // [Internal]
    // NB: Access texture data via GetTexData*() calls! Which will setup a default font for you.
    bool                        Locked;             // Marked as Locked by ImGui::NewFrame() so attempt to modify the atlas will assert.
    bool                        TexReady;           // Set when texture was built matching current font input
    bool                        TexPixelsUseColors; // Tell whether our texture data is known to use colors (rather than just alpha channel), in order to help backend select a format.
    unsigned char*              TexPixelsAlpha8;    // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
    unsigned int*               TexPixelsRGBA32;    // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    int                         TexWidth;           // Texture width calculated during Build().
    int                         TexHeight;          // Texture height calculated during Build().
    ImVec2                      TexUvScale;         // = (1.0f/TexWidth, 1.0f/TexHeight)
    ImVec2                      TexUvWhitePixel;    // Texture coordinates to a white pixel
    ImVector<ImFont*>           Fonts;              // Hold all the fonts returned by AddFont*. Fonts[0] is the default font upon calling ImGui::NewFrame(), use ImGui::PushFont()/PopFont() to change the current font.
    ImVector<ImFontAtlasCustomRect> CustomRects;    // Rectangles for packing custom texture data into the atlas.
    ImVector<ImFontConfig>      ConfigData;         // Configuration data
    ImVec4                      TexUvLines[(32) + 1];  // UVs for baked anti-aliased lines

    // [Internal] Font builder
    const ImFontBuilderIO*      FontBuilderIO;      // Opaque interface to a font builder (default to stb_truetype, can be changed to use FreeType by defining IMGUI_ENABLE_FREETYPE).
    unsigned int                FontBuilderFlags;   // Shared flags (for all fonts) for custom font builder. THIS IS BUILD IMPLEMENTATION DEPENDENT. Per-font override is also available in ImFontConfig.

    // [Internal] Packing data
    int                         PackIdMouseCursors; // Custom texture rectangle ID for white pixel and mouse cursors
    int                         PackIdLines;        // Custom texture rectangle ID for baked anti-aliased lines

    // [Obsolete]
    //typedef ImFontAtlasCustomRect    CustomRect;         // OBSOLETED in 1.72+
    //typedef ImFontGlyphRangesBuilder GlyphRangesBuilder; // OBSOLETED in 1.67+
};

// Font runtime data and rendering
// ImFontAtlas automatically loads a default embedded font for you when you call GetTexDataAsAlpha8() or GetTexDataAsRGBA32().
struct ImFont
{
    // [Internal] Members: Hot ~20/24 bytes (for CalcTextSize)
    ImVector<float>             IndexAdvanceX;      // 12-16 // out // Sparse. Glyphs->AdvanceX in a directly indexable way (cache-friendly for CalcTextSize functions which only this info, and are often bottleneck in large UI).
    float                       FallbackAdvanceX;   // 4     // out // = FallbackGlyph->AdvanceX
    float                       FontSize;           // 4     // in  // Height of characters/line, set during loading (don't change after loading)

    // [Internal] Members: Hot ~28/40 bytes (for RenderText loop)
    ImVector<ImU16>             IndexLookup;        // 12-16 // out // Sparse. Index glyphs by Unicode code-point.
    ImVector<ImFontGlyph>       Glyphs;             // 12-16 // out // All glyphs.
    const ImFontGlyph*          FallbackGlyph;      // 4-8   // out // = FindGlyph(FontFallbackChar)

    // [Internal] Members: Cold ~32/40 bytes
    // Conceptually ConfigData[] is the list of font sources merged to create this font.
    ImFontAtlas*                ContainerAtlas;     // 4-8   // out // What we has been loaded into
    const ImFontConfig*         ConfigData;         // 4-8   // in  // Pointer within ContainerAtlas->ConfigData to ConfigDataCount instances
    short                       ConfigDataCount;    // 2     // in  // Number of ImFontConfig involved in creating this font. Usually 1, or >1 when merging multiple font sources into one ImFont.
    short                       EllipsisCharCount;  // 1     // out // 1 or 3
    ImWchar                     EllipsisChar;       // 2-4   // out // Character used for ellipsis rendering ('...').
    ImWchar                     FallbackChar;       // 2-4   // out // Character used if a glyph isn't found (U+FFFD, '?')
    float                       EllipsisWidth;      // 4     // out // Total ellipsis Width
    float                       EllipsisCharStep;   // 4     // out // Step between characters when EllipsisCount > 0
    float                       Scale;              // 4     // in  // Base font scale (1.0f), multiplied by the per-window font scale which you can adjust with SetWindowFontScale()
    float                       Ascent, Descent;    // 4+4   // out // Ascent: distance from top to bottom of e.g. 'A' [0..FontSize] (unscaled)
    int                         MetricsTotalSurface;// 4     // out // Total surface in pixels to get an idea of the font rasterization/texture cost (not exact, we approximate the cost of padding between glyphs)
    bool                        DirtyLookupTables;  // 1     // out //
    ImU8                        Used8kPagesMap[(0xFFFF+1)/8192/8]; // 1 bytes if ImWchar=ImWchar16, 16 bytes if ImWchar==ImWchar32. Store 1-bit for each block of 4K codepoints that has one active glyph. This is mainly used to facilitate iterations across all used codepoints.

    // Methods
     ImFont();
     ~ImFont();
     const ImFontGlyph*FindGlyph(ImWchar c);
     const ImFontGlyph*FindGlyphNoFallback(ImWchar c);
    float                       GetCharAdvance(ImWchar c)       { return ((int)c < IndexAdvanceX.Size) ? IndexAdvanceX[(int)c] : FallbackAdvanceX; }
    bool                        IsLoaded() const                { return ContainerAtlas != ((void *)0); }
    const char*                 GetDebugName() const            { return ConfigData ? ConfigData->Name : "<unknown>"; }

    // 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
    // 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
     ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = ((void *)0), const char** remaining = ((void *)0)); // utf8
     const char*       CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width);
     void              RenderChar(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, ImWchar c);
     void              RenderText(ImDrawList* draw_list, float size, const ImVec2& pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, float wrap_width = 0.0f, bool cpu_fine_clip = false);

    // [Internal] Don't use!
     void              BuildLookupTable();
     void              ClearOutputData();
     void              GrowIndex(int new_size);
     void              AddGlyph(const ImFontConfig* src_cfg, ImWchar c, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1, float advance_x);
     void              AddRemapChar(ImWchar dst, ImWchar src, bool overwrite_dst = true); // Makes 'dst' character/glyph points to 'src' character/glyph. Currently needs to be called AFTER fonts have been built.
     void              SetGlyphVisible(ImWchar c, bool visible);
     bool              IsGlyphRangeUnused(unsigned int c_begin, unsigned int c_last);
};

//-----------------------------------------------------------------------------
// [SECTION] Viewports
//-----------------------------------------------------------------------------

// Flags stored in ImGuiViewport::Flags, giving indications to the platform backends.
enum ImGuiViewportFlags_
{
    ImGuiViewportFlags_None                     = 0,
    ImGuiViewportFlags_IsPlatformWindow         = 1 << 0,   // Represent a Platform Window
    ImGuiViewportFlags_IsPlatformMonitor        = 1 << 1,   // Represent a Platform Monitor (unused yet)
    ImGuiViewportFlags_OwnedByApp               = 1 << 2,   // Platform Window: Is created/managed by the user application? (rather than our backend)
    ImGuiViewportFlags_NoDecoration             = 1 << 3,   // Platform Window: Disable platform decorations: title bar, borders, etc. (generally set all windows, but if ImGuiConfigFlags_ViewportsDecoration is set we only set this on popups/tooltips)
    ImGuiViewportFlags_NoTaskBarIcon            = 1 << 4,   // Platform Window: Disable platform task bar icon (generally set on popups/tooltips, or all windows if ImGuiConfigFlags_ViewportsNoTaskBarIcon is set)
    ImGuiViewportFlags_NoFocusOnAppearing       = 1 << 5,   // Platform Window: Don't take focus when created.
    ImGuiViewportFlags_NoFocusOnClick           = 1 << 6,   // Platform Window: Don't take focus when clicked on.
    ImGuiViewportFlags_NoInputs                 = 1 << 7,   // Platform Window: Make mouse pass through so we can drag this window while peaking behind it.
    ImGuiViewportFlags_NoRendererClear          = 1 << 8,   // Platform Window: Renderer doesn't need to clear the framebuffer ahead (because we will fill it entirely).
    ImGuiViewportFlags_NoAutoMerge              = 1 << 9,   // Platform Window: Avoid merging this window into another host window. This can only be set via ImGuiWindowClass viewport flags override (because we need to now ahead if we are going to create a viewport in the first place!).
    ImGuiViewportFlags_TopMost                  = 1 << 10,  // Platform Window: Display on top (for tooltips only).
    ImGuiViewportFlags_CanHostOtherWindows      = 1 << 11,  // Viewport can host multiple imgui windows (secondary viewports are associated to a single window). // FIXME: In practice there's still probably code making the assumption that this is always and only on the MainViewport. Will fix once we add support for "no main viewport".

    // Output status flags (from Platform)
    ImGuiViewportFlags_IsMinimized              = 1 << 12,  // Platform Window: Window is minimized, can skip render. When minimized we tend to avoid using the viewport pos/size for clipping window or testing if they are contained in the viewport.
    ImGuiViewportFlags_IsFocused                = 1 << 13,  // Platform Window: Window is focused (last call to Platform_GetWindowFocus() returned true)
};

// - Currently represents the Platform Window created by the application which is hosting our Dear ImGui windows.
// - With multi-viewport enabled, we extend this concept to have multiple active viewports.
// - In the future we will extend this concept further to also represent Platform Monitor and support a "no main platform window" operation mode.
// - About Main Area vs Work Area:
//   - Main Area = entire viewport.
//   - Work Area = entire viewport minus sections used by main menu bars (for platform windows), or by task bar (for platform monitor).
//   - Windows are generally trying to stay within the Work Area of their host viewport.
struct ImGuiViewport
{
    ImGuiID             ID;                     // Unique identifier for the viewport
    ImGuiViewportFlags  Flags;                  // See ImGuiViewportFlags_
    ImVec2              Pos;                    // Main Area: Position of the viewport (Dear ImGui coordinates are the same as OS desktop/native coordinates)
    ImVec2              Size;                   // Main Area: Size of the viewport.
    ImVec2              WorkPos;                // Work Area: Position of the viewport minus task bars, menus bars, status bars (>= Pos)
    ImVec2              WorkSize;               // Work Area: Size of the viewport minus task bars, menu bars, status bars (<= Size)
    float               DpiScale;               // 1.0f = 96 DPI = No extra scale.
    ImGuiID             ParentViewportId;       // (Advanced) 0: no parent. Instruct the platform backend to setup a parent/child relationship between platform windows.
    ImDrawData*         DrawData;               // The ImDrawData corresponding to this viewport. Valid after Render() and until the next call to NewFrame().

    // Platform/Backend Dependent Data
    // Our design separate the Renderer and Platform backends to facilitate combining default backends with each others.
    // When our create your own backend for a custom engine, it is possible that both Renderer and Platform will be handled
    // by the same system and you may not need to use all the UserData/Handle fields.
    // The library never uses those fields, they are merely storage to facilitate backend implementation.
    void*               RendererUserData;       // void* to hold custom data structure for the renderer (e.g. swap chain, framebuffers etc.). generally set by your Renderer_CreateWindow function.
    void*               PlatformUserData;       // void* to hold custom data structure for the OS / platform (e.g. windowing info, render context). generally set by your Platform_CreateWindow function.
    void*               PlatformHandle;         // void* to hold higher-level, platform window handle (e.g. HWND, GLFWWindow*, SDL_Window*), for FindViewportByPlatformHandle().
    void*               PlatformHandleRaw;      // void* to hold lower-level, platform-native window handle (under Win32 this is expected to be a HWND, unused for other platforms), when using an abstraction layer like GLFW or SDL (where PlatformHandle would be a SDL_Window*)
    bool                PlatformWindowCreated;  // Platform window has been created (Platform_CreateWindow() has been called). This is false during the first frame where a viewport is being created.
    bool                PlatformRequestMove;    // Platform window requested move (e.g. window was moved by the OS / host window manager, authoritative position will be OS window position)
    bool                PlatformRequestResize;  // Platform window requested resize (e.g. window was resized by the OS / host window manager, authoritative size will be OS window size)
    bool                PlatformRequestClose;   // Platform window requested closure (e.g. window was moved by the OS / host window manager, e.g. pressing ALT-F4)

    ImGuiViewport()     { memset(this, 0, sizeof(*this)); }
    ~ImGuiViewport()    { (void)( (!!(PlatformUserData == ((void *)0) && RendererUserData == ((void *)0))) || (_wassert(L"PlatformUserData == ((void *)0) && RendererUserData == ((void *)0)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui.h", (unsigned)(3680)), 0) ); }

    // Helpers
    ImVec2              GetCenter() const       { return ImVec2(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f); }
    ImVec2              GetWorkCenter() const   { return ImVec2(WorkPos.x + WorkSize.x * 0.5f, WorkPos.y + WorkSize.y * 0.5f); }
};

//-----------------------------------------------------------------------------
// [SECTION] ImGuiPlatformIO + other Platform Dependent Interfaces (ImGuiPlatformMonitor, ImGuiPlatformImeData)
//-----------------------------------------------------------------------------

// [BETA] (Optional) Multi-Viewport Support!
// If you are new to Dear ImGui and trying to integrate it into your engine, you can probably ignore this for now.
//
// This feature allows you to seamlessly drag Dear ImGui windows outside of your application viewport.
// This is achieved by creating new Platform/OS windows on the fly, and rendering into them.
// Dear ImGui manages the viewport structures, and the backend create and maintain one Platform/OS window for each of those viewports.
//
// See Recap:   https://github.com/ocornut/imgui/wiki/Multi-Viewports
// See Glossary https://github.com/ocornut/imgui/wiki/Glossary for details about some of the terminology.
//
// About the coordinates system:
// - When multi-viewports are enabled, all Dear ImGui coordinates become absolute coordinates (same as OS coordinates!)
// - So e.g. ImGui::SetNextWindowPos(ImVec2(0,0)) will position a window relative to your primary monitor!
// - If you want to position windows relative to your main application viewport, use ImGui::GetMainViewport()->Pos as a base position.
//
// Steps to use multi-viewports in your application, when using a default backend from the examples/ folder:
// - Application:  Enable feature with 'io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable'.
// - Backend:      The backend initialization will setup all necessary ImGuiPlatformIO's functions and update monitors info every frame.
// - Application:  In your main loop, call ImGui::UpdatePlatformWindows(), ImGui::RenderPlatformWindowsDefault() after EndFrame() or Render().
// - Application:  Fix absolute coordinates used in ImGui::SetWindowPos() or ImGui::SetNextWindowPos() calls.
//
// Steps to use multi-viewports in your application, when using a custom backend:
// - Important:    THIS IS NOT EASY TO DO and comes with many subtleties not described here!
//                 It's also an experimental feature, so some of the requirements may evolve.
//                 Consider using default backends if you can. Either way, carefully follow and refer to examples/ backends for details.
// - Application:  Enable feature with 'io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable'.
// - Backend:      Hook ImGuiPlatformIO's Platform_* and Renderer_* callbacks (see below).
//                 Set 'io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports' and 'io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports'.
//                 Update ImGuiPlatformIO's Monitors list every frame.
//                 Update MousePos every frame, in absolute coordinates.
// - Application:  In your main loop, call ImGui::UpdatePlatformWindows(), ImGui::RenderPlatformWindowsDefault() after EndFrame() or Render().
//                 You may skip calling RenderPlatformWindowsDefault() if its API is not convenient for your needs. Read comments below.
// - Application:  Fix absolute coordinates used in ImGui::SetWindowPos() or ImGui::SetNextWindowPos() calls.
//
// About ImGui::RenderPlatformWindowsDefault():
// - This function is a mostly a _helper_ for the common-most cases, and to facilitate using default backends.
// - You can check its simple source code to understand what it does.
//   It basically iterates secondary viewports and call 4 functions that are setup in ImGuiPlatformIO, if available:
//     Platform_RenderWindow(), Renderer_RenderWindow(), Platform_SwapBuffers(), Renderer_SwapBuffers()
//   Those functions pointers exists only for the benefit of RenderPlatformWindowsDefault().
// - If you have very specific rendering needs (e.g. flipping multiple swap-chain simultaneously, unusual sync/threading issues, etc.),
//   you may be tempted to ignore RenderPlatformWindowsDefault() and write customized code to perform your renderingg.
//   You may decide to setup the platform_io's *RenderWindow and *SwapBuffers pointers and call your functions through those pointers,
//   or you may decide to never setup those pointers and call your code directly. They are a convenience, not an obligatory interface.
//-----------------------------------------------------------------------------

// Access via ImGui::GetPlatformIO()
struct ImGuiPlatformIO
{
     ImGuiPlatformIO();

    //------------------------------------------------------------------
    // Interface with OS and Platform backend (basic)
    //------------------------------------------------------------------

    // Optional: Access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    const char* (*Platform_GetClipboardTextFn)(ImGuiContext* ctx);
    void        (*Platform_SetClipboardTextFn)(ImGuiContext* ctx, const char* text);
    void*       Platform_ClipboardUserData;

    // Optional: Open link/folder/file in OS Shell
    // (default to use ShellExecuteA() on Windows, system() on Linux/Mac)
    bool        (*Platform_OpenInShellFn)(ImGuiContext* ctx, const char* path);
    void*       Platform_OpenInShellUserData;

    // Optional: Notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME on Windows)
    // (default to use native imm32 api on Windows)
    void        (*Platform_SetImeDataFn)(ImGuiContext* ctx, ImGuiViewport* viewport, ImGuiPlatformImeData* data);
    void*       Platform_ImeUserData;
    //void      (*SetPlatformImeDataFn)(ImGuiViewport* viewport, ImGuiPlatformImeData* data); // [Renamed to platform_io.PlatformSetImeDataFn in 1.91.1]

    // Optional: Platform locale
    // [Experimental] Configure decimal point e.g. '.' or ',' useful for some languages (e.g. German), generally pulled from *localeconv()->decimal_point
    ImWchar     Platform_LocaleDecimalPoint;     // '.'

    //------------------------------------------------------------------
    // Interface with Renderer Backend
    //------------------------------------------------------------------

    // Written by some backends during ImGui_ImplXXXX_RenderDrawData() call to point backend_specific ImGui_ImplXXXX_RenderState* structure.
    void*       Renderer_RenderState;

    //------------------------------------------------------------------
    // Input - Interface with OS/backends (Multi-Viewport support!)
    //------------------------------------------------------------------

    // For reference, the second column shows which function are generally calling the Platform Functions:
    //   N = ImGui::NewFrame()                        ~ beginning of the dear imgui frame: read info from platform/OS windows (latest size/position)
    //   F = ImGui::Begin(), ImGui::EndFrame()        ~ during the dear imgui frame
    //   U = ImGui::UpdatePlatformWindows()           ~ after the dear imgui frame: create and update all platform/OS windows
    //   R = ImGui::RenderPlatformWindowsDefault()    ~ render
    //   D = ImGui::DestroyPlatformWindows()          ~ shutdown
    // The general idea is that NewFrame() we will read the current Platform/OS state, and UpdatePlatformWindows() will write to it.

    // The handlers are designed so we can mix and match two imgui_impl_xxxx files, one Platform backend and one Renderer backend.
    // Custom engine backends will often provide both Platform and Renderer interfaces together and so may not need to use all functions.
    // Platform functions are typically called _before_ their Renderer counterpart, apart from Destroy which are called the other way.

    // Platform Backend functions (e.g. Win32, GLFW, SDL) ------------------- Called by -----
    void    (*Platform_CreateWindow)(ImGuiViewport* vp);                    // . . U . .  // Create a new platform window for the given viewport
    void    (*Platform_DestroyWindow)(ImGuiViewport* vp);                   // N . U . D  //
    void    (*Platform_ShowWindow)(ImGuiViewport* vp);                      // . . U . .  // Newly created windows are initially hidden so SetWindowPos/Size/Title can be called on them before showing the window
    void    (*Platform_SetWindowPos)(ImGuiViewport* vp, ImVec2 pos);        // . . U . .  // Set platform window position (given the upper-left corner of client area)
    ImVec2  (*Platform_GetWindowPos)(ImGuiViewport* vp);                    // N . . . .  //
    void    (*Platform_SetWindowSize)(ImGuiViewport* vp, ImVec2 size);      // . . U . .  // Set platform window client area size (ignoring OS decorations such as OS title bar etc.)
    ImVec2  (*Platform_GetWindowSize)(ImGuiViewport* vp);                   // N . . . .  // Get platform window client area size
    void    (*Platform_SetWindowFocus)(ImGuiViewport* vp);                  // N . . . .  // Move window to front and set input focus
    bool    (*Platform_GetWindowFocus)(ImGuiViewport* vp);                  // . . U . .  //
    bool    (*Platform_GetWindowMinimized)(ImGuiViewport* vp);              // N . . . .  // Get platform window minimized state. When minimized, we generally won't attempt to get/set size and contents will be culled more easily
    void    (*Platform_SetWindowTitle)(ImGuiViewport* vp, const char* str); // . . U . .  // Set platform window title (given an UTF-8 string)
    void    (*Platform_SetWindowAlpha)(ImGuiViewport* vp, float alpha);     // . . U . .  // (Optional) Setup global transparency (not per-pixel transparency)
    void    (*Platform_UpdateWindow)(ImGuiViewport* vp);                    // . . U . .  // (Optional) Called by UpdatePlatformWindows(). Optional hook to allow the platform backend from doing general book-keeping every frame.
    void    (*Platform_RenderWindow)(ImGuiViewport* vp, void* render_arg);  // . . . R .  // (Optional) Main rendering (platform side! This is often unused, or just setting a "current" context for OpenGL bindings). 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    void    (*Platform_SwapBuffers)(ImGuiViewport* vp, void* render_arg);   // . . . R .  // (Optional) Call Present/SwapBuffers (platform side! This is often unused!). 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    float   (*Platform_GetWindowDpiScale)(ImGuiViewport* vp);               // N . . . .  // (Optional) [BETA] FIXME-DPI: DPI handling: Return DPI scale for this viewport. 1.0f = 96 DPI.
    void    (*Platform_OnChangedViewport)(ImGuiViewport* vp);               // . F . . .  // (Optional) [BETA] FIXME-DPI: DPI handling: Called during Begin() every time the viewport we are outputting into changes, so backend has a chance to swap fonts to adjust style.
    ImVec4  (*Platform_GetWindowWorkAreaInsets)(ImGuiViewport* vp);         // N . . . .  // (Optional) [BETA] Get initial work area inset for the viewport (won't be covered by main menu bar, dockspace over viewport etc.). Default to (0,0),(0,0). 'safeAreaInsets' in iOS land, 'DisplayCutout' in Android land.
    int     (*Platform_CreateVkSurface)(ImGuiViewport* vp, ImU64 vk_inst, const void* vk_allocators, ImU64* out_vk_surface); // (Optional) For a Vulkan Renderer to call into Platform code (since the surface creation needs to tie them both).

    // Renderer Backend functions (e.g. DirectX, OpenGL, Vulkan) ------------ Called by -----
    void    (*Renderer_CreateWindow)(ImGuiViewport* vp);                    // . . U . .  // Create swap chain, frame buffers etc. (called after Platform_CreateWindow)
    void    (*Renderer_DestroyWindow)(ImGuiViewport* vp);                   // N . U . D  // Destroy swap chain, frame buffers etc. (called before Platform_DestroyWindow)
    void    (*Renderer_SetWindowSize)(ImGuiViewport* vp, ImVec2 size);      // . . U . .  // Resize swap chain, frame buffers etc. (called after Platform_SetWindowSize)
    void    (*Renderer_RenderWindow)(ImGuiViewport* vp, void* render_arg);  // . . . R .  // (Optional) Clear framebuffer, setup render target, then render the viewport->DrawData. 'render_arg' is the value passed to RenderPlatformWindowsDefault().
    void    (*Renderer_SwapBuffers)(ImGuiViewport* vp, void* render_arg);   // . . . R .  // (Optional) Call Present/SwapBuffers. 'render_arg' is the value passed to RenderPlatformWindowsDefault().

    // (Optional) Monitor list
    // - Updated by: app/backend. Update every frame to dynamically support changing monitor or DPI configuration.
    // - Used by: dear imgui to query DPI info, clamp popups/tooltips within same monitor and not have them straddle monitors.
    ImVector<ImGuiPlatformMonitor>  Monitors;

    //------------------------------------------------------------------
    // Output - List of viewports to render into platform windows
    //------------------------------------------------------------------

    // Viewports list (the list is updated by calling ImGui::EndFrame or ImGui::Render)
    // (in the future we will attempt to organize this feature to remove the need for a "main viewport")
    ImVector<ImGuiViewport*>        Viewports;                              // Main viewports, followed by all secondary viewports.
};

// (Optional) This is required when enabling multi-viewport. Represent the bounds of each connected monitor/display and their DPI.
// We use this information for multiple DPI support + clamping the position of popups and tooltips so they don't straddle multiple monitors.
struct ImGuiPlatformMonitor
{
    ImVec2  MainPos, MainSize;      // Coordinates of the area displayed on this monitor (Min = upper left, Max = bottom right)
    ImVec2  WorkPos, WorkSize;      // Coordinates without task bars / side bars / menu bars. Used to avoid positioning popups/tooltips inside this region. If you don't have this info, please copy the value for MainPos/MainSize.
    float   DpiScale;               // 1.0f = 96 DPI
    void*   PlatformHandle;         // Backend dependant data (e.g. HMONITOR, GLFWmonitor*, SDL Display Index, NSScreen*)
    ImGuiPlatformMonitor()          { MainPos = MainSize = WorkPos = WorkSize = ImVec2(0, 0); DpiScale = 1.0f; PlatformHandle = ((void *)0); }
};

// (Optional) Support for IME (Input Method Editor) via the platform_io.Platform_SetImeDataFn() function.
struct ImGuiPlatformImeData
{
    bool    WantVisible;        // A widget wants the IME to be visible
    ImVec2  InputPos;           // Position of the input cursor
    float   InputLineHeight;    // Line height

    ImGuiPlatformImeData() { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Obsolete functions and types
// (Will be removed! Read 'API BREAKING CHANGES' section in imgui.cpp for details)
// Please keep your copy of dear imgui up to date! Occasionally set '#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS' in imconfig.h to stay ahead.
//-----------------------------------------------------------------------------




















































































































// RENAMED IMGUI_DISABLE_METRICS_WINDOW > IMGUI_DISABLE_DEBUG_TOOLS in 1.88 (from June 2022)




//-----------------------------------------------------------------------------







// Include imgui_user.h at the end of imgui.h
// May be convenient for some users to only explicitly include vanilla imgui.h and have extra stuff included.








// dear imgui, v1.91.8
// (internal structures/api)

// You may use this file to debug, understand or extend Dear ImGui features but we don't provide any guarantee of forward compatibility.

/*

Index of this file:

// [SECTION] Header mess
// [SECTION] Forward declarations
// [SECTION] Context pointer
// [SECTION] STB libraries includes
// [SECTION] Macros
// [SECTION] Generic helpers
// [SECTION] ImDrawList support
// [SECTION] Data types support
// [SECTION] Widgets support: flags, enums, data structures
// [SECTION] Popup support
// [SECTION] Inputs support
// [SECTION] Clipper support
// [SECTION] Navigation support
// [SECTION] Typing-select support
// [SECTION] Columns support
// [SECTION] Box-select support
// [SECTION] Multi-select support
// [SECTION] Docking support
// [SECTION] Viewport support
// [SECTION] Settings support
// [SECTION] Localization support
// [SECTION] Error handling, State recovery support
// [SECTION] Metrics, Debug tools
// [SECTION] Generic context hooks
// [SECTION] ImGuiContext (main imgui context)
// [SECTION] ImGuiWindowTempData, ImGuiWindow
// [SECTION] Tab bar, Tab item support
// [SECTION] Table support
// [SECTION] ImGui internal API
// [SECTION] ImFontAtlas internal API
// [SECTION] Test Engine specific hooks (imgui_test_engine)

*/





//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------







// Enable SSE intrinsics if available





// Emscripten has partial SSE 4.2 support where _mm_crc32_u32 is not available. See https://emscripten.org/docs/porting/simd.html#id11 and #8213



// Visual Studio warnings



// Clang/GCC warnings with -Weverything





















// In 1.89.4, we moved the implementation of "courtesy maths operators" from imgui_internal.h in imgui.h
// As they are frequently requested, we do not want to encourage to many people using imgui_internal.h



// Legacy defines







// Enable stb_truetype by default unless FreeType is enabled.
// You can compile with both by defining both IMGUI_ENABLE_FREETYPE and IMGUI_ENABLE_STB_TRUETYPE together.




//-----------------------------------------------------------------------------
// [SECTION] Forward declarations
//-----------------------------------------------------------------------------

// Utilities
// (other types which are not forwarded declared are: ImBitArray<>, ImSpan<>, ImSpanAllocator<>, ImPool<>, ImChunkStream<>)
struct ImBitVector;                 // Store 1-bit per value
struct ImRect;                      // An axis-aligned rectangle (2 points)
struct ImGuiTextIndex;              // Maintain a line index for a text buffer.

// ImDrawList/ImFontAtlas
struct ImDrawDataBuilder;           // Helper to build a ImDrawData instance
struct ImDrawListSharedData;        // Data shared between all ImDrawList instances

// ImGui
struct ImGuiBoxSelectState;         // Box-selection state (currently used by multi-selection, could potentially be used by others)
struct ImGuiColorMod;               // Stacked color modifier, backup of modified data so we can restore it
struct ImGuiContext;                // Main Dear ImGui context
struct ImGuiContextHook;            // Hook for extensions like ImGuiTestEngine
struct ImGuiDataVarInfo;            // Variable information (e.g. to access style variables from an enum)
struct ImGuiDataTypeInfo;           // Type information associated to a ImGuiDataType enum
struct ImGuiDeactivatedItemData;    // Data for IsItemDeactivated()/IsItemDeactivatedAfterEdit() function.
struct ImGuiDockContext;            // Docking system context
struct ImGuiDockRequest;            // Docking system dock/undock queued request
struct ImGuiDockNode;               // Docking system node (hold a list of Windows OR two child dock nodes)
struct ImGuiDockNodeSettings;       // Storage for a dock node in .ini file (we preserve those even if the associated dock node isn't active during the session)
struct ImGuiErrorRecoveryState;     // Storage of stack sizes for error handling and recovery
struct ImGuiGroupData;              // Stacked storage data for BeginGroup()/EndGroup()
struct ImGuiInputTextState;         // Internal state of the currently focused/edited text input box
struct ImGuiInputTextDeactivateData;// Short term storage to backup text of a deactivating InputText() while another is stealing active id
struct ImGuiLastItemData;           // Status storage for last submitted items
struct ImGuiLocEntry;               // A localization entry.
struct ImGuiMenuColumns;            // Simple column measurement, currently used for MenuItem() only
struct ImGuiMultiSelectState;       // Multi-selection persistent state (for focused selection).
struct ImGuiMultiSelectTempData;    // Multi-selection temporary state (while traversing).
struct ImGuiNavItemData;            // Result of a keyboard/gamepad directional navigation move query result
struct ImGuiMetricsConfig;          // Storage for ShowMetricsWindow() and DebugNodeXXX() functions
struct ImGuiNextWindowData;         // Storage for SetNextWindow** functions
struct ImGuiNextItemData;           // Storage for SetNextItem** functions
struct ImGuiOldColumnData;          // Storage data for a single column for legacy Columns() api
struct ImGuiOldColumns;             // Storage data for a columns set for legacy Columns() api
struct ImGuiPopupData;              // Storage for current popup stack
struct ImGuiSettingsHandler;        // Storage for one type registered in the .ini file
struct ImGuiStyleMod;               // Stacked style modifier, backup of modified data so we can restore it
struct ImGuiTabBar;                 // Storage for a tab bar
struct ImGuiTabItem;                // Storage for a tab item (within a tab bar)
struct ImGuiTable;                  // Storage for a table
struct ImGuiTableHeaderData;        // Storage for TableAngledHeadersRow()
struct ImGuiTableColumn;            // Storage for one column of a table
struct ImGuiTableInstanceData;      // Storage for one instance of a same table
struct ImGuiTableTempData;          // Temporary storage for one table (one per table in the stack), shared between tables.
struct ImGuiTableSettings;          // Storage for a table .ini settings
struct ImGuiTableColumnsSettings;   // Storage for a column .ini settings
struct ImGuiTreeNodeStackData;      // Temporary storage for TreeNode().
struct ImGuiTypingSelectState;      // Storage for GetTypingSelectRequest()
struct ImGuiTypingSelectRequest;    // Storage for GetTypingSelectRequest() (aimed to be public)
struct ImGuiWindow;                 // Storage for one window
struct ImGuiWindowDockStyle;        // Storage for window-style data which needs to be stored for docking purpose
struct ImGuiWindowTempData;         // Temporary storage for one window (that's the data which in theory we could ditch at the end of the frame, in practice we currently keep it for each window)
struct ImGuiWindowSettings;         // Storage for a window .ini settings (we keep one of those even if the actual window wasn't instanced during this session)

// Enumerations
// Use your programming IDE "Go to definition" facility on the names of the center columns to find the actual flags/enum lists.
enum ImGuiLocKey : int;                 // -> enum ImGuiLocKey              // Enum: a localization entry for translation.
typedef int ImGuiDataAuthority;         // -> enum ImGuiDataAuthority_      // Enum: for storing the source authority (dock node vs window) of a field
typedef int ImGuiLayoutType;            // -> enum ImGuiLayoutType_         // Enum: Horizontal or vertical

// Flags
typedef int ImGuiActivateFlags;         // -> enum ImGuiActivateFlags_      // Flags: for navigation/focus function (will be for ActivateItem() later)
typedef int ImGuiDebugLogFlags;         // -> enum ImGuiDebugLogFlags_      // Flags: for ShowDebugLogWindow(), g.DebugLogFlags
typedef int ImGuiFocusRequestFlags;     // -> enum ImGuiFocusRequestFlags_  // Flags: for FocusWindow()
typedef int ImGuiItemStatusFlags;       // -> enum ImGuiItemStatusFlags_    // Flags: for g.LastItemData.StatusFlags
typedef int ImGuiOldColumnFlags;        // -> enum ImGuiOldColumnFlags_     // Flags: for BeginColumns()
typedef int ImGuiLogFlags;              // -> enum ImGuiLogFlags_           // Flags: for LogBegin() text capturing function
typedef int ImGuiNavRenderCursorFlags;  // -> enum ImGuiNavRenderCursorFlags_//Flags: for RenderNavCursor()
typedef int ImGuiNavMoveFlags;          // -> enum ImGuiNavMoveFlags_       // Flags: for navigation requests
typedef int ImGuiNextItemDataFlags;     // -> enum ImGuiNextItemDataFlags_  // Flags: for SetNextItemXXX() functions
typedef int ImGuiNextWindowDataFlags;   // -> enum ImGuiNextWindowDataFlags_// Flags: for SetNextWindowXXX() functions
typedef int ImGuiScrollFlags;           // -> enum ImGuiScrollFlags_        // Flags: for ScrollToItem() and navigation requests
typedef int ImGuiSeparatorFlags;        // -> enum ImGuiSeparatorFlags_     // Flags: for SeparatorEx()
typedef int ImGuiTextFlags;             // -> enum ImGuiTextFlags_          // Flags: for TextEx()
typedef int ImGuiTooltipFlags;          // -> enum ImGuiTooltipFlags_       // Flags: for BeginTooltipEx()
typedef int ImGuiTypingSelectFlags;     // -> enum ImGuiTypingSelectFlags_  // Flags: for GetTypingSelectRequest()
typedef int ImGuiWindowRefreshFlags;    // -> enum ImGuiWindowRefreshFlags_ // Flags: for SetNextWindowRefreshPolicy()

//-----------------------------------------------------------------------------
// [SECTION] Context pointer
// See implementation of this variable in imgui.cpp for comments and details.
//-----------------------------------------------------------------------------


extern  ImGuiContext* GImGui;  // Current implicit context pointer

//-----------------------------------------------------------------------------
// [SECTION] Macros
//-----------------------------------------------------------------------------

// Internal Drag and Drop payload types. String starting with '_' are reserved for Dear ImGui.


// Debug Printing Into TTY
// (since IMGUI_VERSION_NUM >= 18729: IMGUI_DEBUG_LOG was reworked into IMGUI_DEBUG_PRINTF (and removed framecount from it). If you were using a #define IMGUI_DEBUG_LOG please rename)






// Debug Logging for ShowDebugLogWindow(). This is designed for relatively rare events so please don't spam.













// Static Asserts


// "Paranoid" Debug Asserts are meant to only be enabled during specific debugging/work, otherwise would slow down the code too much.
// We currently don't have many of those so the effect is currently negligible, but onward intent to add more aggressive ones in the code.
//#define IMGUI_DEBUG_PARANOID





// Misc Macros


















// Hint for branch prediction






// Enforce cdecl calling convention for functions called by the standard library, in case compilation settings changed the default to e.g. __vectorcall





// Warnings





// Debug Tools
// Use 'Metrics/Debugger->Tools->Item Picker' to break into the call-stack of a specific item.
// This will call IM_DEBUG_BREAK() which you may redefine yourself. See https://github.com/scottt/debugbreak for more reference.














// Format specifiers, printing 64-bit hasn't been decently standardized...
// In a real application you should be using PRId64 and PRIu64 from <inttypes.h> (non-windows) and on Windows define them yourself.









//-----------------------------------------------------------------------------
// [SECTION] Generic helpers
// Note that the ImXXX helpers functions are lower-level than ImGui functions.
// ImGui functions or the ImGui context are never called/used from other ImXXX functions.
//-----------------------------------------------------------------------------
// - Helpers: Hashing
// - Helpers: Sorting
// - Helpers: Bit manipulation
// - Helpers: String
// - Helpers: Formatting
// - Helpers: UTF-8 <> wchar conversions
// - Helpers: ImVec2/ImVec4 operators
// - Helpers: Maths
// - Helpers: Geometry
// - Helper: ImVec1
// - Helper: ImVec2ih
// - Helper: ImRect
// - Helper: ImBitArray
// - Helper: ImBitVector
// - Helper: ImSpan<>, ImSpanAllocator<>
// - Helper: ImPool<>
// - Helper: ImChunkStream<>
// - Helper: ImGuiTextIndex
// - Helper: ImGuiStorage
//-----------------------------------------------------------------------------

// Helpers: Hashing
 ImGuiID       ImHashData(const void* data, size_t data_size, ImGuiID seed = 0);
 ImGuiID       ImHashStr(const char* data, size_t data_size = 0, ImGuiID seed = 0);

// Helpers: Sorting

static inline void      ImQsort(void* base, size_t count, size_t size_of_element, int(__cdecl *compare_func)(void const*, void const*)) { if (count > 1) qsort(base, count, size_of_element, compare_func); }

// Helpers: Color Blending
 ImU32         ImAlphaBlendColors(ImU32 col_a, ImU32 col_b);

// Helpers: Bit manipulation
static inline bool      ImIsPowerOfTwo(int v)           { return v != 0 && (v & (v - 1)) == 0; }
static inline bool      ImIsPowerOfTwo(ImU64 v)         { return v != 0 && (v & (v - 1)) == 0; }
static inline int       ImUpperPowerOfTwo(int v)        { v--; v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16; v++; return v; }

// Helpers: String
 int           ImStricmp(const char* str1, const char* str2);                      // Case insensitive compare.
 int           ImStrnicmp(const char* str1, const char* str2, size_t count);       // Case insensitive compare to a certain count.
 void          ImStrncpy(char* dst, const char* src, size_t count);                // Copy to a certain count and always zero terminate (strncpy doesn't).
 char*         ImStrdup(const char* str);                                          // Duplicate a string.
 char*         ImStrdupcpy(char* dst, size_t* p_dst_size, const char* str);        // Copy in provided buffer, recreate buffer if needed.
 const char*   ImStrchrRange(const char* str_begin, const char* str_end, char c);  // Find first occurrence of 'c' in string range.
 const char*   ImStreolRange(const char* str, const char* str_end);                // End end-of-line
 const char*   ImStristr(const char* haystack, const char* haystack_end, const char* needle, const char* needle_end);  // Find a substring in a string range.
 void          ImStrTrimBlanks(char* str);                                         // Remove leading and trailing blanks from a buffer.
 const char*   ImStrSkipBlank(const char* str);                                    // Find first non-blank character.
 int           ImStrlenW(const ImWchar* str);                                      // Computer string length (ImWchar string)
 const char*   ImStrbol(const char* buf_mid_line, const char* buf_begin);          // Find beginning-of-line

static inline char      ImToUpper(char c)               { return (c >= 'a' && c <= 'z') ? c &= ~32 : c; }
static inline bool      ImCharIsBlankA(char c)          { return c == ' ' || c == '\t'; }
static inline bool      ImCharIsBlankW(unsigned int c)  { return c == ' ' || c == '\t' || c == 0x3000; }
static inline bool      ImCharIsXdigitA(char c)         { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }


// Helpers: Formatting
 int           ImFormatString(char* buf, size_t buf_size, const char* fmt, ...) ;
 int           ImFormatStringV(char* buf, size_t buf_size, const char* fmt, va_list args) ;
 void          ImFormatStringToTempBuffer(const char** out_buf, const char** out_buf_end, const char* fmt, ...) ;
 void          ImFormatStringToTempBufferV(const char** out_buf, const char** out_buf_end, const char* fmt, va_list args) ;
 const char*   ImParseFormatFindStart(const char* format);
 const char*   ImParseFormatFindEnd(const char* format);
 const char*   ImParseFormatTrimDecorations(const char* format, char* buf, size_t buf_size);
 void          ImParseFormatSanitizeForPrinting(const char* fmt_in, char* fmt_out, size_t fmt_out_size);
 const char*   ImParseFormatSanitizeForScanning(const char* fmt_in, char* fmt_out, size_t fmt_out_size);
 int           ImParseFormatPrecision(const char* format, int default_value);

// Helpers: UTF-8 <> wchar conversions
 const char*   ImTextCharToUtf8(char out_buf[5], unsigned int c);                                                      // return out_buf
 int           ImTextStrToUtf8(char* out_buf, int out_buf_size, const ImWchar* in_text, const ImWchar* in_text_end);   // return output UTF-8 bytes count
 int           ImTextCharFromUtf8(unsigned int* out_char, const char* in_text, const char* in_text_end);               // read one character. return input UTF-8 bytes count
 int           ImTextStrFromUtf8(ImWchar* out_buf, int out_buf_size, const char* in_text, const char* in_text_end, const char** in_remaining = ((void *)0));   // return input UTF-8 bytes count
 int           ImTextCountCharsFromUtf8(const char* in_text, const char* in_text_end);                                 // return number of UTF-8 code-points (NOT bytes count)
 int           ImTextCountUtf8BytesFromChar(const char* in_text, const char* in_text_end);                             // return number of bytes to express one char in UTF-8
 int           ImTextCountUtf8BytesFromStr(const ImWchar* in_text, const ImWchar* in_text_end);                        // return number of bytes to express string in UTF-8
 const char*   ImTextFindPreviousUtf8Codepoint(const char* in_text_start, const char* in_text_curr);                   // return previous UTF-8 code-point.
 int           ImTextCountLines(const char* in_text, const char* in_text_end);                                         // return number of lines taken by text. trailing carriage return doesn't count as an extra line.

// Helpers: File System










typedef FILE* ImFileHandle;
 ImFileHandle      ImFileOpen(const char* filename, const char* mode);
 bool              ImFileClose(ImFileHandle file);
 ImU64             ImFileGetSize(ImFileHandle file);
 ImU64             ImFileRead(void* data, ImU64 size, ImU64 count, ImFileHandle file);
 ImU64             ImFileWrite(const void* data, ImU64 size, ImU64 count, ImFileHandle file);


 void*             ImFileLoadToMemory(const char* filename, const char* mode, size_t* out_file_size = ((void *)0), int padding_bytes = 0);

// Helpers: Maths

// - Wrapper for standard libs functions. (Note that imgui_demo.cpp does _not_ use them to keep the code easy to copy)










static inline float  ImPow(float x, float y)    { return powf(x, y); }          // DragBehaviorT/SliderBehaviorT uses ImPow with either float/double and need the precision
static inline double ImPow(double x, double y)  { return pow(x, y); }
static inline float  ImLog(float x)             { return logf(x); }             // DragBehaviorT/SliderBehaviorT uses ImLog with either float/double and need the precision
static inline double ImLog(double x)            { return log(x); }
static inline int    ImAbs(int x)               { return x < 0 ? -x : x; }
static inline float  ImAbs(float x)             { return fabsf(x); }
static inline double ImAbs(double x)            { return fabs(x); }
static inline float  ImSign(float x)            { return (x < 0.0f) ? -1.0f : (x > 0.0f) ? 1.0f : 0.0f; } // Sign operator - returns -1, 0 or 1 based on sign of argument
static inline double ImSign(double x)           { return (x < 0.0) ? -1.0 : (x > 0.0) ? 1.0 : 0.0; }

static inline float  ImRsqrt(float x)           { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x))); }


static inline double ImRsqrt(double x)          { return 1.0 / sqrt(x); }
// - ImMin/ImMax/ImClamp/ImLerp/ImSwap are used by widgets which support variety of types: signed/unsigned int/long long float/double
// (Exceptionally using templates here but we could also redefine them for those types)
template<typename T> static inline T ImMin(T lhs, T rhs)                        { return lhs < rhs ? lhs : rhs; }
template<typename T> static inline T ImMax(T lhs, T rhs)                        { return lhs >= rhs ? lhs : rhs; }
template<typename T> static inline T ImClamp(T v, T mn, T mx)                   { return (v < mn) ? mn : (v > mx) ? mx : v; }
template<typename T> static inline T ImLerp(T a, T b, float t)                  { return (T)(a + (b - a) * t); }
template<typename T> static inline void ImSwap(T& a, T& b)                      { T tmp = a; a = b; b = tmp; }
template<typename T> static inline T ImAddClampOverflow(T a, T b, T mn, T mx)   { if (b < 0 && (a < mn - b)) return mn; if (b > 0 && (a > mx - b)) return mx; return a + b; }
template<typename T> static inline T ImSubClampOverflow(T a, T b, T mn, T mx)   { if (b > 0 && (a < mn + b)) return mn; if (b < 0 && (a > mx + b)) return mx; return a - b; }
// - Misc maths helpers
static inline ImVec2 ImMin(const ImVec2& lhs, const ImVec2& rhs)                { return ImVec2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y); }
static inline ImVec2 ImMax(const ImVec2& lhs, const ImVec2& rhs)                { return ImVec2(lhs.x >= rhs.x ? lhs.x : rhs.x, lhs.y >= rhs.y ? lhs.y : rhs.y); }
static inline ImVec2 ImClamp(const ImVec2& v, const ImVec2&mn, const ImVec2&mx) { return ImVec2((v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y); }
static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, float t)          { return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); }
static inline ImVec2 ImLerp(const ImVec2& a, const ImVec2& b, const ImVec2& t)  { return ImVec2(a.x + (b.x - a.x) * t.x, a.y + (b.y - a.y) * t.y); }
static inline ImVec4 ImLerp(const ImVec4& a, const ImVec4& b, float t)          { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }
static inline float  ImSaturate(float f)                                        { return (f < 0.0f) ? 0.0f : (f > 1.0f) ? 1.0f : f; }
static inline float  ImLengthSqr(const ImVec2& lhs)                             { return (lhs.x * lhs.x) + (lhs.y * lhs.y); }
static inline float  ImLengthSqr(const ImVec4& lhs)                             { return (lhs.x * lhs.x) + (lhs.y * lhs.y) + (lhs.z * lhs.z) + (lhs.w * lhs.w); }
static inline float  ImInvLength(const ImVec2& lhs, float fail_value)           { float d = (lhs.x * lhs.x) + (lhs.y * lhs.y); if (d > 0.0f) return ImRsqrt(d); return fail_value; }
static inline float  ImTrunc(float f)                                           { return (float)(int)(f); }
static inline ImVec2 ImTrunc(const ImVec2& v)                                   { return ImVec2((float)(int)(v.x), (float)(int)(v.y)); }
static inline float  ImFloor(float f)                                           { return (float)((f >= 0 || (float)(int)f == f) ? (int)f : (int)f - 1); } // Decent replacement for floorf()
static inline ImVec2 ImFloor(const ImVec2& v)                                   { return ImVec2(ImFloor(v.x), ImFloor(v.y)); }
static inline int    ImModPositive(int a, int b)                                { return (a + b) % b; }
static inline float  ImDot(const ImVec2& a, const ImVec2& b)                    { return a.x * b.x + a.y * b.y; }
static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a)        { return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a); }
static inline float  ImLinearSweep(float current, float target, float speed)    { if (current < target) return ImMin(current + speed, target); if (current > target) return ImMax(current - speed, target); return current; }
static inline float  ImLinearRemapClamp(float s0, float s1, float d0, float d1, float x) { return ImSaturate((x - s0) / (s1 - s0)) * (d1 - d0) + d0; }
static inline ImVec2 ImMul(const ImVec2& lhs, const ImVec2& rhs)                { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline bool   ImIsFloatAboveGuaranteedIntegerPrecision(float f)          { return f <= -16777216 || f >= 16777216; }
static inline float  ImExponentialMovingAverage(float avg, float sample, int n) { avg -= avg / n; avg += sample / n; return avg; }


// Helpers: Geometry
 ImVec2     ImBezierCubicCalc(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, float t);
 ImVec2     ImBezierCubicClosestPoint(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p, int num_segments);       // For curves with explicit number of segments
 ImVec2     ImBezierCubicClosestPointCasteljau(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p, float tess_tol);// For auto-tessellated curves you can use tess_tol = style.CurveTessellationTol
 ImVec2     ImBezierQuadraticCalc(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, float t);
 ImVec2     ImLineClosestPoint(const ImVec2& a, const ImVec2& b, const ImVec2& p);
 bool       ImTriangleContainsPoint(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p);
 ImVec2     ImTriangleClosestPoint(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p);
 void       ImTriangleBarycentricCoords(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& p, float& out_u, float& out_v, float& out_w);
inline float         ImTriangleArea(const ImVec2& a, const ImVec2& b, const ImVec2& c)          { return fabsf((a.x * (b.y - c.y)) + (b.x * (c.y - a.y)) + (c.x * (a.y - b.y))) * 0.5f; }
inline bool          ImTriangleIsClockwise(const ImVec2& a, const ImVec2& b, const ImVec2& c)   { return ((b.x - a.x) * (c.y - b.y)) - ((c.x - b.x) * (b.y - a.y)) > 0.0f; }

// Helper: ImVec1 (1D vector)
// (this odd construct is used to facilitate the transition between 1D and 2D, and the maintenance of some branches/patches)

struct ImVec1
{
    float   x;
    constexpr ImVec1()         : x(0.0f) { }
    constexpr ImVec1(float _x) : x(_x) { }
};

// Helper: ImVec2ih (2D vector, half-size integer, for long-term packed storage)
struct ImVec2ih
{
    short   x, y;
    constexpr ImVec2ih()                           : x(0), y(0) {}
    constexpr ImVec2ih(short _x, short _y)         : x(_x), y(_y) {}
    constexpr explicit ImVec2ih(const ImVec2& rhs) : x((short)rhs.x), y((short)rhs.y) {}
};

// Helper: ImRect (2D axis aligned bounding-box)
// NB: we can't rely on ImVec2 math operators being available here!
struct  ImRect
{
    ImVec2      Min;    // Upper-left
    ImVec2      Max;    // Lower-right

    constexpr ImRect()                                        : Min(0.0f, 0.0f), Max(0.0f, 0.0f)  {}
    constexpr ImRect(const ImVec2& min, const ImVec2& max)    : Min(min), Max(max)                {}
    constexpr ImRect(const ImVec4& v)                         : Min(v.x, v.y), Max(v.z, v.w)      {}
    constexpr ImRect(float x1, float y1, float x2, float y2)  : Min(x1, y1), Max(x2, y2)          {}

    ImVec2      GetCenter() const                   { return ImVec2((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f); }
    ImVec2      GetSize() const                     { return ImVec2(Max.x - Min.x, Max.y - Min.y); }
    float       GetWidth() const                    { return Max.x - Min.x; }
    float       GetHeight() const                   { return Max.y - Min.y; }
    float       GetArea() const                     { return (Max.x - Min.x) * (Max.y - Min.y); }
    ImVec2      GetTL() const                       { return Min; }                   // Top-left
    ImVec2      GetTR() const                       { return ImVec2(Max.x, Min.y); }  // Top-right
    ImVec2      GetBL() const                       { return ImVec2(Min.x, Max.y); }  // Bottom-left
    ImVec2      GetBR() const                       { return Max; }                   // Bottom-right
    bool        Contains(const ImVec2& p) const     { return p.x     >= Min.x && p.y     >= Min.y && p.x     <  Max.x && p.y     <  Max.y; }
    bool        Contains(const ImRect& r) const     { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x <= Max.x && r.Max.y <= Max.y; }
    bool        ContainsWithPad(const ImVec2& p, const ImVec2& pad) const { return p.x >= Min.x - pad.x && p.y >= Min.y - pad.y && p.x < Max.x + pad.x && p.y < Max.y + pad.y; }
    bool        Overlaps(const ImRect& r) const     { return r.Min.y <  Max.y && r.Max.y >  Min.y && r.Min.x <  Max.x && r.Max.x >  Min.x; }
    void        Add(const ImVec2& p)                { if (Min.x > p.x)     Min.x = p.x;     if (Min.y > p.y)     Min.y = p.y;     if (Max.x < p.x)     Max.x = p.x;     if (Max.y < p.y)     Max.y = p.y; }
    void        Add(const ImRect& r)                { if (Min.x > r.Min.x) Min.x = r.Min.x; if (Min.y > r.Min.y) Min.y = r.Min.y; if (Max.x < r.Max.x) Max.x = r.Max.x; if (Max.y < r.Max.y) Max.y = r.Max.y; }
    void        Expand(const float amount)          { Min.x -= amount;   Min.y -= amount;   Max.x += amount;   Max.y += amount; }
    void        Expand(const ImVec2& amount)        { Min.x -= amount.x; Min.y -= amount.y; Max.x += amount.x; Max.y += amount.y; }
    void        Translate(const ImVec2& d)          { Min.x += d.x; Min.y += d.y; Max.x += d.x; Max.y += d.y; }
    void        TranslateX(float dx)                { Min.x += dx; Max.x += dx; }
    void        TranslateY(float dy)                { Min.y += dy; Max.y += dy; }
    void        ClipWith(const ImRect& r)           { Min = ImMax(Min, r.Min); Max = ImMin(Max, r.Max); }                   // Simple version, may lead to an inverted rectangle, which is fine for Contains/Overlaps test but not for display.
    void        ClipWithFull(const ImRect& r)       { Min = ImClamp(Min, r.Min, r.Max); Max = ImClamp(Max, r.Min, r.Max); } // Full version, ensure both points are fully clipped.
    void        Floor()                             { Min.x = ((float)(int)(Min.x)); Min.y = ((float)(int)(Min.y)); Max.x = ((float)(int)(Max.x)); Max.y = ((float)(int)(Max.y)); }
    bool        IsInverted() const                  { return Min.x > Max.x || Min.y > Max.y; }
    ImVec4      ToVec4() const                      { return ImVec4(Min.x, Min.y, Max.x, Max.y); }
};

// Helper: ImBitArray


inline size_t   ImBitArrayGetStorageSizeInBytes(int bitcount)   { return (size_t)((bitcount + 31) >> 5) << 2; }
inline void     ImBitArrayClearAllBits(ImU32* arr, int bitcount){ memset(arr, 0, ImBitArrayGetStorageSizeInBytes(bitcount)); }
inline bool     ImBitArrayTestBit(const ImU32* arr, int n)      { ImU32 mask = (ImU32)1 << (n & 31); return (arr[n >> 5] & mask) != 0; }
inline void     ImBitArrayClearBit(ImU32* arr, int n)           { ImU32 mask = (ImU32)1 << (n & 31); arr[n >> 5] &= ~mask; }
inline void     ImBitArraySetBit(ImU32* arr, int n)             { ImU32 mask = (ImU32)1 << (n & 31); arr[n >> 5] |= mask; }
inline void     ImBitArraySetBitRange(ImU32* arr, int n, int n2) // Works on range [n..n2)
{
    n2--;
    while (n <= n2)
    {
        int a_mod = (n & 31);
        int b_mod = (n2 > (n | 31) ? 31 : (n2 & 31)) + 1;
        ImU32 mask = (ImU32)(((ImU64)1 << b_mod) - 1) & ~(ImU32)(((ImU64)1 << a_mod) - 1);
        arr[n >> 5] |= mask;
        n = (n + 32) & ~31;
    }
}

typedef ImU32* ImBitArrayPtr; // Name for use in structs

// Helper: ImBitArray class (wrapper over ImBitArray functions)
// Store 1-bit per value.
template<int BITCOUNT, int OFFSET = 0>
struct ImBitArray
{
    ImU32           Storage[(BITCOUNT + 31) >> 5];
    ImBitArray()                                { ClearAllBits(); }
    void            ClearAllBits()              { memset(Storage, 0, sizeof(Storage)); }
    void            SetAllBits()                { memset(Storage, 255, sizeof(Storage)); }
    bool            TestBit(int n) const        { n += OFFSET; (void)( (!!(n >= 0 && n < BITCOUNT)) || (_wassert(L"n >= 0 && n < BITCOUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(616)), 0) ); return ((Storage[(n) >> 5] & ((ImU32)1 << ((n) & 31))) != 0); }
    void            SetBit(int n)               { n += OFFSET; (void)( (!!(n >= 0 && n < BITCOUNT)) || (_wassert(L"n >= 0 && n < BITCOUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(617)), 0) ); ImBitArraySetBit(Storage, n); }
    void            ClearBit(int n)             { n += OFFSET; (void)( (!!(n >= 0 && n < BITCOUNT)) || (_wassert(L"n >= 0 && n < BITCOUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(618)), 0) ); ImBitArrayClearBit(Storage, n); }
    void            SetBitRange(int n, int n2)  { n += OFFSET; n2 += OFFSET; (void)( (!!(n >= 0 && n < BITCOUNT && n2 > n && n2 <= BITCOUNT)) || (_wassert(L"n >= 0 && n < BITCOUNT && n2 > n && n2 <= BITCOUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(619)), 0) ); ImBitArraySetBitRange(Storage, n, n2); } // Works on range [n..n2)
    bool            operator[](int n) const     { n += OFFSET; (void)( (!!(n >= 0 && n < BITCOUNT)) || (_wassert(L"n >= 0 && n < BITCOUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(620)), 0) ); return ((Storage[(n) >> 5] & ((ImU32)1 << ((n) & 31))) != 0); }
};

// Helper: ImBitVector
// Store 1-bit per value.
struct  ImBitVector
{
    ImVector<ImU32> Storage;
    void            Create(int sz)              { Storage.resize((sz + 31) >> 5); memset(Storage.Data, 0, (size_t)Storage.Size * sizeof(Storage.Data[0])); }
    void            Clear()                     { Storage.clear(); }
    bool            TestBit(int n) const        { (void)( (!!(n < (Storage.Size << 5))) || (_wassert(L"n < (Storage.Size << 5)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(630)), 0) ); return ((Storage.Data[(n) >> 5] & ((ImU32)1 << ((n) & 31))) != 0); }
    void            SetBit(int n)               { (void)( (!!(n < (Storage.Size << 5))) || (_wassert(L"n < (Storage.Size << 5)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(631)), 0) ); ImBitArraySetBit(Storage.Data, n); }
    void            ClearBit(int n)             { (void)( (!!(n < (Storage.Size << 5))) || (_wassert(L"n < (Storage.Size << 5)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(632)), 0) ); ImBitArrayClearBit(Storage.Data, n); }
};


// Helper: ImSpan<>
// Pointing to a span of data we don't own.
template<typename T>
struct ImSpan
{
    T*                  Data;
    T*                  DataEnd;

    // Constructors, destructor
    inline ImSpan()                                 { Data = DataEnd = ((void *)0); }
    inline ImSpan(T* data, int size)                { Data = data; DataEnd = data + size; }
    inline ImSpan(T* data, T* data_end)             { Data = data; DataEnd = data_end; }

    inline void         set(T* data, int size)      { Data = data; DataEnd = data + size; }
    inline void         set(T* data, T* data_end)   { Data = data; DataEnd = data_end; }
    inline int          size() const                { return (int)(ptrdiff_t)(DataEnd - Data); }
    inline int          size_in_bytes() const       { return (int)(ptrdiff_t)(DataEnd - Data) * (int)sizeof(T); }
    inline T&           operator[](int i)           { T* p = Data + i; (void)( (!!(p >= Data && p < DataEnd)) || (_wassert(L"p >= Data && p < DataEnd", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(653)), 0) ); return *p; }
    inline const T&     operator[](int i) const     { const T* p = Data + i; (void)( (!!(p >= Data && p < DataEnd)) || (_wassert(L"p >= Data && p < DataEnd", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(654)), 0) ); return *p; }

    inline T*           begin()                     { return Data; }
    inline const T*     begin() const               { return Data; }
    inline T*           end()                       { return DataEnd; }
    inline const T*     end() const                 { return DataEnd; }

    // Utilities
    inline int  index_from_ptr(const T* it) const   { (void)( (!!(it >= Data && it < DataEnd)) || (_wassert(L"it >= Data && it < DataEnd", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(662)), 0) ); const ptrdiff_t off = it - Data; return (int)off; }
};

// Helper: ImSpanAllocator<>
// Facilitate storing multiple chunks into a single large block (the "arena")
// - Usage: call Reserve() N times, allocate GetArenaSizeInBytes() worth, pass it to SetArenaBasePtr(), call GetSpan() N times to retrieve the aligned ranges.
template<int CHUNKS>
struct ImSpanAllocator
{
    char*   BasePtr;
    int     CurrOff;
    int     CurrIdx;
    int     Offsets[CHUNKS];
    int     Sizes[CHUNKS];

    ImSpanAllocator()                               { memset(this, 0, sizeof(*this)); }
    inline void  Reserve(int n, size_t sz, int a=4) { (void)( (!!(n == CurrIdx && n < CHUNKS)) || (_wassert(L"n == CurrIdx && n < CHUNKS", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(678)), 0) ); CurrOff = (((CurrOff) + ((a) - 1)) & ~((a) - 1)); Offsets[n] = CurrOff; Sizes[n] = (int)sz; CurrIdx++; CurrOff += (int)sz; }
    inline int   GetArenaSizeInBytes()              { return CurrOff; }
    inline void  SetArenaBasePtr(void* base_ptr)    { BasePtr = (char*)base_ptr; }
    inline void* GetSpanPtrBegin(int n)             { (void)( (!!(n >= 0 && n < CHUNKS && CurrIdx == CHUNKS)) || (_wassert(L"n >= 0 && n < CHUNKS && CurrIdx == CHUNKS", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(681)), 0) ); return (void*)(BasePtr + Offsets[n]); }
    inline void* GetSpanPtrEnd(int n)               { (void)( (!!(n >= 0 && n < CHUNKS && CurrIdx == CHUNKS)) || (_wassert(L"n >= 0 && n < CHUNKS && CurrIdx == CHUNKS", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(682)), 0) ); return (void*)(BasePtr + Offsets[n] + Sizes[n]); }
    template<typename T>
    inline void  GetSpan(int n, ImSpan<T>* span)    { span->set((T*)GetSpanPtrBegin(n), (T*)GetSpanPtrEnd(n)); }
};

// Helper: ImPool<>
// Basic keyed storage for contiguous instances, slow/amortized insertion, O(1) indexable, O(Log N) queries by ID over a dense/hot buffer,
// Honor constructor/destructor. Add/remove invalidate all pointers. Indexes have the same lifetime as the associated object.
typedef int ImPoolIdx;
template<typename T>
struct ImPool
{
    ImVector<T>     Buf;        // Contiguous data
    ImGuiStorage    Map;        // ID->Index
    ImPoolIdx       FreeIdx;    // Next free idx to use
    ImPoolIdx       AliveCount; // Number of active/alive items (for display purpose)

    ImPool()    { FreeIdx = AliveCount = 0; }
    ~ImPool()   { Clear(); }
    T*          GetByKey(ImGuiID key)               { int idx = Map.GetInt(key, -1); return (idx != -1) ? &Buf[idx] : ((void *)0); }
    T*          GetByIndex(ImPoolIdx n)             { return &Buf[n]; }
    ImPoolIdx   GetIndex(const T* p) const          { (void)( (!!(p >= Buf.Data && p < Buf.Data + Buf.Size)) || (_wassert(L"p >= Buf.Data && p < Buf.Data + Buf.Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(703)), 0) ); return (ImPoolIdx)(p - Buf.Data); }
    T*          GetOrAddByKey(ImGuiID key)          { int* p_idx = Map.GetIntRef(key, -1); if (*p_idx != -1) return &Buf[*p_idx]; *p_idx = FreeIdx; return Add(); }
    bool        Contains(const T* p) const          { return (p >= Buf.Data && p < Buf.Data + Buf.Size); }
    void        Clear()                             { for (int n = 0; n < Map.Data.Size; n++) { int idx = Map.Data[n].val_i; if (idx != -1) Buf[idx].~T(); } Map.Clear(); Buf.clear(); FreeIdx = AliveCount = 0; }
    T*          Add()                               { int idx = FreeIdx; if (idx == Buf.Size) { Buf.resize(Buf.Size + 1); FreeIdx++; } else { FreeIdx = *(int*)&Buf[idx]; } new(ImNewWrapper(), &Buf[idx]) T(); AliveCount++; return &Buf[idx]; }
    void        Remove(ImGuiID key, const T* p)     { Remove(key, GetIndex(p)); }
    void        Remove(ImGuiID key, ImPoolIdx idx)  { Buf[idx].~T(); *(int*)&Buf[idx] = FreeIdx; FreeIdx = idx; Map.SetInt(key, -1); AliveCount--; }
    void        Reserve(int capacity)               { Buf.reserve(capacity); Map.Data.reserve(capacity); }

    // To iterate a ImPool: for (int n = 0; n < pool.GetMapSize(); n++) if (T* t = pool.TryGetMapData(n)) { ... }
    // Can be avoided if you know .Remove() has never been called on the pool, or AliveCount == GetMapSize()
    int         GetAliveCount() const               { return AliveCount; }      // Number of active/alive items in the pool (for display purpose)
    int         GetBufSize() const                  { return Buf.Size; }
    int         GetMapSize() const                  { return Map.Data.Size; }   // It is the map we need iterate to find valid items, since we don't have "alive" storage anywhere
    T*          TryGetMapData(ImPoolIdx n)          { int idx = Map.Data[n].val_i; if (idx == -1) return ((void *)0); return GetByIndex(idx); }
};

// Helper: ImChunkStream<>
// Build and iterate a contiguous stream of variable-sized structures.
// This is used by Settings to store persistent data while reducing allocation count.
// We store the chunk size first, and align the final size on 4 bytes boundaries.
// The tedious/zealous amount of casting is to avoid -Wcast-align warnings.
template<typename T>
struct ImChunkStream
{
    ImVector<char>  Buf;

    void    clear()                     { Buf.clear(); }
    bool    empty() const               { return Buf.Size == 0; }
    int     size() const                { return Buf.Size; }
    T*      alloc_chunk(size_t sz)      { size_t HDR_SZ = 4; sz = (((HDR_SZ + sz) + ((4u) - 1)) & ~((4u) - 1)); int off = Buf.Size; Buf.resize(off + (int)sz); ((int*)(void*)(Buf.Data + off))[0] = (int)sz; return (T*)(void*)(Buf.Data + off + (int)HDR_SZ); }
    T*      begin()                     { size_t HDR_SZ = 4; if (!Buf.Data) return ((void *)0); return (T*)(void*)(Buf.Data + HDR_SZ); }
    T*      next_chunk(T* p)            { size_t HDR_SZ = 4; (void)( (!!(p >= begin() && p < end())) || (_wassert(L"p >= begin() && p < end()", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(735)), 0) ); p = (T*)(void*)((char*)(void*)p + chunk_size(p)); if (p == (T*)(void*)((char*)end() + HDR_SZ)) return (T*)0; (void)( (!!(p < end())) || (_wassert(L"p < end()", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(735)), 0) ); return p; }
    int     chunk_size(const T* p)      { return ((const int*)p)[-1]; }
    T*      end()                       { return (T*)(void*)(Buf.Data + Buf.Size); }
    int     offset_from_ptr(const T* p) { (void)( (!!(p >= begin() && p < end())) || (_wassert(L"p >= begin() && p < end()", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(738)), 0) ); const ptrdiff_t off = (const char*)p - Buf.Data; return (int)off; }
    T*      ptr_from_offset(int off)    { (void)( (!!(off >= 4 && off < Buf.Size)) || (_wassert(L"off >= 4 && off < Buf.Size", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(739)), 0) ); return (T*)(void*)(Buf.Data + off); }
    void    swap(ImChunkStream<T>& rhs) { rhs.Buf.swap(Buf); }
};

// Helper: ImGuiTextIndex
// Maintain a line index for a text buffer. This is a strong candidate to be moved into the public API.
struct ImGuiTextIndex
{
    ImVector<int>   LineOffsets;
    int             EndOffset = 0;                          // Because we don't own text buffer we need to maintain EndOffset (may bake in LineOffsets?)

    void            clear()                                 { LineOffsets.clear(); EndOffset = 0; }
    int             size()                                  { return LineOffsets.Size; }
    const char*     get_line_begin(const char* base, int n) { return base + LineOffsets[n]; }
    const char*     get_line_end(const char* base, int n)   { return base + (n + 1 < LineOffsets.Size ? (LineOffsets[n + 1] - 1) : EndOffset); }
    void            append(const char* base, int old_size, int new_size);
};

// Helper: ImGuiStorage
 ImGuiStoragePair* ImLowerBound(ImGuiStoragePair* in_begin, ImGuiStoragePair* in_end, ImGuiID key);

//-----------------------------------------------------------------------------
// [SECTION] ImDrawList support
//-----------------------------------------------------------------------------

// ImDrawList: Helper function to calculate a circle's segment count given its radius and a "maximum error" value.
// Estimation of number of circle segment based on error is derived using method described in https://stackoverflow.com/a/2244088/15194693
// Number of segments (N) is calculated using equation:
//   N = ceil ( pi / acos(1 - error / r) )     where r > 0, error <= r
// Our equation is significantly simpler that one in the post thanks for choosing segment that is
// perpendicular to X axis. Follow steps in the article from this starting condition and you will
// will get this result.
//
// Rendering circles with an odd number of segments, while mathematically correct will produce
// asymmetrical results on the raster grid. Therefore we're rounding N to next even number (7->8, 8->8, 9->10 etc.)





// Raw equation from IM_DRAWLIST_CIRCLE_AUTO_SEGMENT_CALC rewritten for 'r' and 'error'.



// ImDrawList: Lookup table size for adaptive arc drawing, cover full circle.




// Data shared between all ImDrawList instances
// Conceptually this could have been called e.g. ImDrawListSharedContext
// Typically one ImGui context would create and maintain one of this.
// You may want to create your own instance of you try to ImDrawList completely without ImGui. In that case, watch out for future changes to this structure.
struct  ImDrawListSharedData
{
    ImVec2          TexUvWhitePixel;            // UV of white pixel in the atlas
    const ImVec4*   TexUvLines;                 // UV of anti-aliased lines in the atlas
    ImFont*         Font;                       // Current/default font (optional, for simplified AddText overload)
    float           FontSize;                   // Current/default font size (optional, for simplified AddText overload)
    float           FontScale;                  // Current/default font scale (== FontSize / Font->FontSize)
    float           CurveTessellationTol;       // Tessellation tolerance when using PathBezierCurveTo()
    float           CircleSegmentMaxError;      // Number of circle segments to use per pixel of radius for AddCircle() etc
    ImVec4          ClipRectFullscreen;         // Value for PushClipRectFullscreen()
    ImDrawListFlags InitialFlags;               // Initial flags at the beginning of the frame (it is possible to alter flags on a per-drawlist basis afterwards)
    ImVector<ImVec2> TempBuffer;                // Temporary write buffer

    // Lookup tables
    ImVec2          ArcFastVtx[48]; // Sample points on the quarter of the circle.
    float           ArcFastRadiusCutoff;                        // Cutoff radius after which arc drawing will fallback to slower PathArcTo()
    ImU8            CircleSegmentCounts[64];    // Precomputed segment count for given radius before we calculate it dynamically (to avoid calculation overhead)

    ImDrawListSharedData();
    void SetCircleTessellationMaxError(float max_error);
};

struct ImDrawDataBuilder
{
    ImVector<ImDrawList*>*  Layers[2];      // Pointers to global layers for: regular, tooltip. LayersP[0] is owned by DrawData.
    ImVector<ImDrawList*>   LayerData1;

    ImDrawDataBuilder()                     { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Data types support
//-----------------------------------------------------------------------------

struct ImGuiDataVarInfo
{
    ImGuiDataType   Type;
    ImU32           Count;      // 1+
    ImU32           Offset;     // Offset in parent structure
    void* GetVarPtr(void* parent) const { return (void*)((unsigned char*)parent + Offset); }
};

struct ImGuiDataTypeStorage
{
    ImU8        Data[8];        // Opaque storage to fit any data up to ImGuiDataType_COUNT
};

// Type information associated to one ImGuiDataType. Retrieve with DataTypeGetInfo().
struct ImGuiDataTypeInfo
{
    size_t      Size;           // Size in bytes
    const char* Name;           // Short descriptive name for the type, for debugging
    const char* PrintFmt;       // Default printf format for the type
    const char* ScanFmt;        // Default scanf format for the type
};

// Extend ImGuiDataType_
enum ImGuiDataTypePrivate_
{
    ImGuiDataType_Pointer = ImGuiDataType_COUNT + 1,
    ImGuiDataType_ID,
};

//-----------------------------------------------------------------------------
// [SECTION] Widgets support: flags, enums, data structures
//-----------------------------------------------------------------------------

// Extend ImGuiItemFlags
// - input: PushItemFlag() manipulates g.CurrentItemFlags, g.NextItemData.ItemFlags, ItemAdd() calls may add extra flags too.
// - output: stored in g.LastItemData.ItemFlags
enum ImGuiItemFlagsPrivate_
{
    // Controlled by user
    ImGuiItemFlags_Disabled                 = 1 << 10, // false     // Disable interactions (DOES NOT affect visuals. DO NOT mix direct use of this with BeginDisabled(). See BeginDisabled()/EndDisabled() for full disable feature, and github #211).
    ImGuiItemFlags_ReadOnly                 = 1 << 11, // false     // [ALPHA] Allow hovering interactions but underlying value is not changed.
    ImGuiItemFlags_MixedValue               = 1 << 12, // false     // [BETA] Represent a mixed/indeterminate value, generally multi-selection where values differ. Currently only supported by Checkbox() (later should support all sorts of widgets)
    ImGuiItemFlags_NoWindowHoverableCheck   = 1 << 13, // false     // Disable hoverable check in ItemHoverable()
    ImGuiItemFlags_AllowOverlap             = 1 << 14, // false     // Allow being overlapped by another widget. Not-hovered to Hovered transition deferred by a frame.
    ImGuiItemFlags_NoNavDisableMouseHover   = 1 << 15, // false     // Nav keyboard/gamepad mode doesn't disable hover highlight (behave as if NavHighlightItemUnderNav==false).
    ImGuiItemFlags_NoMarkEdited             = 1 << 16, // false     // Skip calling MarkItemEdited()

    // Controlled by widget code
    ImGuiItemFlags_Inputable                = 1 << 20, // false     // [WIP] Auto-activate input mode when tab focused. Currently only used and supported by a few items before it becomes a generic feature.
    ImGuiItemFlags_HasSelectionUserData     = 1 << 21, // false     // Set by SetNextItemSelectionUserData()
    ImGuiItemFlags_IsMultiSelect            = 1 << 22, // false     // Set by SetNextItemSelectionUserData()

    ImGuiItemFlags_Default_                 = ImGuiItemFlags_AutoClosePopups,    // Please don't change, use PushItemFlag() instead.

    // Obsolete
    //ImGuiItemFlags_SelectableDontClosePopup = !ImGuiItemFlags_AutoClosePopups, // Can't have a redirect as we inverted the behavior
};

// Status flags for an already submitted item
// - output: stored in g.LastItemData.StatusFlags
enum ImGuiItemStatusFlags_
{
    ImGuiItemStatusFlags_None               = 0,
    ImGuiItemStatusFlags_HoveredRect        = 1 << 0,   // Mouse position is within item rectangle (does NOT mean that the window is in correct z-order and can be hovered!, this is only one part of the most-common IsItemHovered test)
    ImGuiItemStatusFlags_HasDisplayRect     = 1 << 1,   // g.LastItemData.DisplayRect is valid
    ImGuiItemStatusFlags_Edited             = 1 << 2,   // Value exposed by item was edited in the current frame (should match the bool return value of most widgets)
    ImGuiItemStatusFlags_ToggledSelection   = 1 << 3,   // Set when Selectable(), TreeNode() reports toggling a selection. We can't report "Selected", only state changes, in order to easily handle clipping with less issues.
    ImGuiItemStatusFlags_ToggledOpen        = 1 << 4,   // Set when TreeNode() reports toggling their open state.
    ImGuiItemStatusFlags_HasDeactivated     = 1 << 5,   // Set if the widget/group is able to provide data for the ImGuiItemStatusFlags_Deactivated flag.
    ImGuiItemStatusFlags_Deactivated        = 1 << 6,   // Only valid if ImGuiItemStatusFlags_HasDeactivated is set.
    ImGuiItemStatusFlags_HoveredWindow      = 1 << 7,   // Override the HoveredWindow test to allow cross-window hover testing.
    ImGuiItemStatusFlags_Visible            = 1 << 8,   // [WIP] Set when item is overlapping the current clipping rectangle (Used internally. Please don't use yet: API/system will change as we refactor Itemadd()).
    ImGuiItemStatusFlags_HasClipRect        = 1 << 9,   // g.LastItemData.ClipRect is valid.
    ImGuiItemStatusFlags_HasShortcut        = 1 << 10,  // g.LastItemData.Shortcut valid. Set by SetNextItemShortcut() -> ItemAdd().

    // Additional status + semantic for ImGuiTestEngine







};

// Extend ImGuiHoveredFlags_
enum ImGuiHoveredFlagsPrivate_
{
    ImGuiHoveredFlags_DelayMask_                    = ImGuiHoveredFlags_DelayNone | ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay,
    ImGuiHoveredFlags_AllowedMaskForIsWindowHovered = ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_NoPopupHierarchy | ImGuiHoveredFlags_DockHierarchy | ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_ForTooltip | ImGuiHoveredFlags_Stationary,
    ImGuiHoveredFlags_AllowedMaskForIsItemHovered   = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped | ImGuiHoveredFlags_AllowWhenDisabled | ImGuiHoveredFlags_NoNavOverride | ImGuiHoveredFlags_ForTooltip | ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayMask_,
};

// Extend ImGuiInputTextFlags_
enum ImGuiInputTextFlagsPrivate_
{
    // [Internal]
    ImGuiInputTextFlags_Multiline           = 1 << 26,  // For internal use by InputTextMultiline()
    ImGuiInputTextFlags_MergedItem          = 1 << 27,  // For internal use by TempInputText(), will skip calling ItemAdd(). Require bounding-box to strictly match.
    ImGuiInputTextFlags_LocalizeDecimalPoint= 1 << 28,  // For internal use by InputScalar() and TempInputScalar()
};

// Extend ImGuiButtonFlags_
enum ImGuiButtonFlagsPrivate_
{
    ImGuiButtonFlags_PressedOnClick         = 1 << 4,   // return true on click (mouse down event)
    ImGuiButtonFlags_PressedOnClickRelease  = 1 << 5,   // [Default] return true on click + release on same item <-- this is what the majority of Button are using
    ImGuiButtonFlags_PressedOnClickReleaseAnywhere = 1 << 6, // return true on click + release even if the release event is not done while hovering the item
    ImGuiButtonFlags_PressedOnRelease       = 1 << 7,   // return true on release (default requires click+release)
    ImGuiButtonFlags_PressedOnDoubleClick   = 1 << 8,   // return true on double-click (default requires click+release)
    ImGuiButtonFlags_PressedOnDragDropHold  = 1 << 9,   // return true when held into while we are drag and dropping another item (used by e.g. tree nodes, collapsing headers)
    //ImGuiButtonFlags_Repeat               = 1 << 10,  // hold to repeat -> use ImGuiItemFlags_ButtonRepeat instead.
    ImGuiButtonFlags_FlattenChildren        = 1 << 11,  // allow interactions even if a child window is overlapping
    ImGuiButtonFlags_AllowOverlap           = 1 << 12,  // require previous frame HoveredId to either match id or be null before being usable.
    //ImGuiButtonFlags_DontClosePopups      = 1 << 13,  // disable automatically closing parent popup on press
    //ImGuiButtonFlags_Disabled             = 1 << 14,  // disable interactions -> use BeginDisabled() or ImGuiItemFlags_Disabled
    ImGuiButtonFlags_AlignTextBaseLine      = 1 << 15,  // vertically align button to match text baseline - ButtonEx() only // FIXME: Should be removed and handled by SmallButton(), not possible currently because of DC.CursorPosPrevLine
    ImGuiButtonFlags_NoKeyModsAllowed       = 1 << 16,  // disable mouse interaction if a key modifier is held
    ImGuiButtonFlags_NoHoldingActiveId      = 1 << 17,  // don't set ActiveId while holding the mouse (ImGuiButtonFlags_PressedOnClick only)
    ImGuiButtonFlags_NoNavFocus             = 1 << 18,  // don't override navigation focus when activated (FIXME: this is essentially used every time an item uses ImGuiItemFlags_NoNav, but because legacy specs don't requires LastItemData to be set ButtonBehavior(), we can't poll g.LastItemData.ItemFlags)
    ImGuiButtonFlags_NoHoveredOnFocus       = 1 << 19,  // don't report as hovered when nav focus is on this item
    ImGuiButtonFlags_NoSetKeyOwner          = 1 << 20,  // don't set key/input owner on the initial click (note: mouse buttons are keys! often, the key in question will be ImGuiKey_MouseLeft!)
    ImGuiButtonFlags_NoTestKeyOwner         = 1 << 21,  // don't test key/input owner when polling the key (note: mouse buttons are keys! often, the key in question will be ImGuiKey_MouseLeft!)
    ImGuiButtonFlags_PressedOnMask_         = ImGuiButtonFlags_PressedOnClick | ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnClickReleaseAnywhere | ImGuiButtonFlags_PressedOnRelease | ImGuiButtonFlags_PressedOnDoubleClick | ImGuiButtonFlags_PressedOnDragDropHold,
    ImGuiButtonFlags_PressedOnDefault_      = ImGuiButtonFlags_PressedOnClickRelease,
};

// Extend ImGuiComboFlags_
enum ImGuiComboFlagsPrivate_
{
    ImGuiComboFlags_CustomPreview           = 1 << 20,  // enable BeginComboPreview()
};

// Extend ImGuiSliderFlags_
enum ImGuiSliderFlagsPrivate_
{
    ImGuiSliderFlags_Vertical               = 1 << 20,  // Should this slider be orientated vertically?
    ImGuiSliderFlags_ReadOnly               = 1 << 21,  // Consider using g.NextItemData.ItemFlags |= ImGuiItemFlags_ReadOnly instead.
};

// Extend ImGuiSelectableFlags_
enum ImGuiSelectableFlagsPrivate_
{
    // NB: need to be in sync with last value of ImGuiSelectableFlags_
    ImGuiSelectableFlags_NoHoldingActiveID      = 1 << 20,
    ImGuiSelectableFlags_SelectOnNav            = 1 << 21,  // (WIP) Auto-select when moved into. This is not exposed in public API as to handle multi-select and modifiers we will need user to explicitly control focus scope. May be replaced with a BeginSelection() API.
    ImGuiSelectableFlags_SelectOnClick          = 1 << 22,  // Override button behavior to react on Click (default is Click+Release)
    ImGuiSelectableFlags_SelectOnRelease        = 1 << 23,  // Override button behavior to react on Release (default is Click+Release)
    ImGuiSelectableFlags_SpanAvailWidth         = 1 << 24,  // Span all avail width even if we declared less for layout purpose. FIXME: We may be able to remove this (added in 6251d379, 2bcafc86 for menus)
    ImGuiSelectableFlags_SetNavIdOnHover        = 1 << 25,  // Set Nav/Focus ID on mouse hover (used by MenuItem)
    ImGuiSelectableFlags_NoPadWithHalfSpacing   = 1 << 26,  // Disable padding each side with ItemSpacing * 0.5f
    ImGuiSelectableFlags_NoSetKeyOwner          = 1 << 27,  // Don't set key/input owner on the initial click (note: mouse buttons are keys! often, the key in question will be ImGuiKey_MouseLeft!)
};

// Extend ImGuiTreeNodeFlags_
enum ImGuiTreeNodeFlagsPrivate_
{
    ImGuiTreeNodeFlags_ClipLabelForTrailingButton = 1 << 28,// FIXME-WIP: Hard-coded for CollapsingHeader()
    ImGuiTreeNodeFlags_UpsideDownArrow            = 1 << 29,// FIXME-WIP: Turn Down arrow into an Up arrow, for reversed trees (#6517)
    ImGuiTreeNodeFlags_OpenOnMask_                = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow,
};

enum ImGuiSeparatorFlags_
{
    ImGuiSeparatorFlags_None                    = 0,
    ImGuiSeparatorFlags_Horizontal              = 1 << 0,   // Axis default to current layout type, so generally Horizontal unless e.g. in a menu bar
    ImGuiSeparatorFlags_Vertical                = 1 << 1,
    ImGuiSeparatorFlags_SpanAllColumns          = 1 << 2,   // Make separator cover all columns of a legacy Columns() set.
};

// Flags for FocusWindow(). This is not called ImGuiFocusFlags to avoid confusion with public-facing ImGuiFocusedFlags.
// FIXME: Once we finishing replacing more uses of GetTopMostPopupModal()+IsWindowWithinBeginStackOf()
// and FindBlockingModal() with this, we may want to change the flag to be opt-out instead of opt-in.
enum ImGuiFocusRequestFlags_
{
    ImGuiFocusRequestFlags_None                 = 0,
    ImGuiFocusRequestFlags_RestoreFocusedChild  = 1 << 0,   // Find last focused child (if any) and focus it instead.
    ImGuiFocusRequestFlags_UnlessBelowModal     = 1 << 1,   // Do not set focus if the window is below a modal.
};

enum ImGuiTextFlags_
{
    ImGuiTextFlags_None                         = 0,
    ImGuiTextFlags_NoWidthForLargeClippedText   = 1 << 0,
};

enum ImGuiTooltipFlags_
{
    ImGuiTooltipFlags_None                      = 0,
    ImGuiTooltipFlags_OverridePrevious          = 1 << 1,   // Clear/ignore previously submitted tooltip (defaults to append)
};

// FIXME: this is in development, not exposed/functional as a generic feature yet.
// Horizontal/Vertical enums are fixed to 0/1 so they may be used to index ImVec2
enum ImGuiLayoutType_
{
    ImGuiLayoutType_Horizontal = 0,
    ImGuiLayoutType_Vertical = 1
};

// Flags for LogBegin() text capturing function
enum ImGuiLogFlags_
{
    ImGuiLogFlags_None = 0,

    ImGuiLogFlags_OutputTTY         = 1 << 0,
    ImGuiLogFlags_OutputFile        = 1 << 1,
    ImGuiLogFlags_OutputBuffer      = 1 << 2,
    ImGuiLogFlags_OutputClipboard   = 1 << 3,
    ImGuiLogFlags_OutputMask_       = ImGuiLogFlags_OutputTTY | ImGuiLogFlags_OutputFile | ImGuiLogFlags_OutputBuffer | ImGuiLogFlags_OutputClipboard,
};

// X/Y enums are fixed to 0/1 so they may be used to index ImVec2
enum ImGuiAxis
{
    ImGuiAxis_None = -1,
    ImGuiAxis_X = 0,
    ImGuiAxis_Y = 1
};

enum ImGuiPlotType
{
    ImGuiPlotType_Lines,
    ImGuiPlotType_Histogram,
};

// Stacked color modifier, backup of modified data so we can restore it
struct ImGuiColorMod
{
    ImGuiCol        Col;
    ImVec4          BackupValue;
};

// Stacked style modifier, backup of modified data so we can restore it. Data type inferred from the variable.
struct ImGuiStyleMod
{
    ImGuiStyleVar   VarIdx;
    union           { int BackupInt[2]; float BackupFloat[2]; };
    ImGuiStyleMod(ImGuiStyleVar idx, int v)     { VarIdx = idx; BackupInt[0] = v; }
    ImGuiStyleMod(ImGuiStyleVar idx, float v)   { VarIdx = idx; BackupFloat[0] = v; }
    ImGuiStyleMod(ImGuiStyleVar idx, ImVec2 v)  { VarIdx = idx; BackupFloat[0] = v.x; BackupFloat[1] = v.y; }
};

// Storage data for BeginComboPreview()/EndComboPreview()
struct  ImGuiComboPreviewData
{
    ImRect          PreviewRect;
    ImVec2          BackupCursorPos;
    ImVec2          BackupCursorMaxPos;
    ImVec2          BackupCursorPosPrevLine;
    float           BackupPrevLineTextBaseOffset;
    ImGuiLayoutType BackupLayout;

    ImGuiComboPreviewData() { memset(this, 0, sizeof(*this)); }
};

// Stacked storage data for BeginGroup()/EndGroup()
struct  ImGuiGroupData
{
    ImGuiID     WindowID;
    ImVec2      BackupCursorPos;
    ImVec2      BackupCursorMaxPos;
    ImVec2      BackupCursorPosPrevLine;
    ImVec1      BackupIndent;
    ImVec1      BackupGroupOffset;
    ImVec2      BackupCurrLineSize;
    float       BackupCurrLineTextBaseOffset;
    ImGuiID     BackupActiveIdIsAlive;
    bool        BackupDeactivatedIdIsAlive;
    bool        BackupHoveredIdIsAlive;
    bool        BackupIsSameLine;
    bool        EmitItem;
};

// Simple column measurement, currently used for MenuItem() only.. This is very short-sighted/throw-away code and NOT a generic helper.
struct  ImGuiMenuColumns
{
    ImU32       TotalWidth;
    ImU32       NextTotalWidth;
    ImU16       Spacing;
    ImU16       OffsetIcon;         // Always zero for now
    ImU16       OffsetLabel;        // Offsets are locked in Update()
    ImU16       OffsetShortcut;
    ImU16       OffsetMark;
    ImU16       Widths[4];          // Width of:   Icon, Label, Shortcut, Mark  (accumulators for current frame)

    ImGuiMenuColumns() { memset(this, 0, sizeof(*this)); }
    void        Update(float spacing, bool window_reappearing);
    float       DeclColumns(float w_icon, float w_label, float w_shortcut, float w_mark);
    void        CalcNextTotalWidth(bool update_offsets);
};

// Internal temporary state for deactivating InputText() instances.
struct  ImGuiInputTextDeactivatedState
{
    ImGuiID            ID;              // widget id owning the text state (which just got deactivated)
    ImVector<char>     TextA;           // text buffer

    ImGuiInputTextDeactivatedState()    { memset(this, 0, sizeof(*this)); }
    void    ClearFreeMemory()           { ID = 0; TextA.clear(); }
};

// Forward declare imstb_textedit.h structure + make its main configuration define accessible







namespace ImStb { struct STB_TexteditState; }
typedef ImStb::STB_TexteditState ImStbTexteditState;

// Internal state of the currently focused/edited text input box
// For a given item ID, access with ImGui::GetInputTextState()
struct  ImGuiInputTextState
{
    ImGuiContext*           Ctx;                    // parent UI context (needs to be set explicitly by parent).
    ImStbTexteditState*     Stb;                    // State for stb_textedit.h
    ImGuiInputTextFlags     Flags;                  // copy of InputText() flags. may be used to check if e.g. ImGuiInputTextFlags_Password is set.
    ImGuiID                 ID;                     // widget id owning the text state
    int                     TextLen;                // UTF-8 length of the string in TextA (in bytes)
    const char*             TextSrc;                // == TextA.Data unless read-only, in which case == buf passed to InputText(). Field only set and valid _inside_ the call InputText() call.
    ImVector<char>          TextA;                  // main UTF8 buffer. TextA.Size is a buffer size! Should always be >= buf_size passed by user (and of course >= CurLenA + 1).
    ImVector<char>          TextToRevertTo;         // value to revert to when pressing Escape = backup of end-user buffer at the time of focus (in UTF-8, unaltered)
    ImVector<char>          CallbackTextBackup;     // temporary storage for callback to support automatic reconcile of undo-stack
    int                     BufCapacity;            // end-user buffer capacity (include zero terminator)
    ImVec2                  Scroll;                 // horizontal offset (managed manually) + vertical scrolling (pulled from child window's own Scroll.y)
    float                   CursorAnim;             // timer for cursor blink, reset on every user action so the cursor reappears immediately
    bool                    CursorFollow;           // set when we want scrolling to follow the current cursor position (not always!)
    bool                    SelectedAllMouseLock;   // after a double-click to select all, we ignore further mouse drags to update selection
    bool                    Edited;                 // edited this frame
    bool                    WantReloadUserBuf;      // force a reload of user buf so it may be modified externally. may be automatic in future version.
    int                     ReloadSelectionStart;
    int                     ReloadSelectionEnd;

    ImGuiInputTextState();
    ~ImGuiInputTextState();
    void        ClearText()                 { TextLen = 0; TextA[0] = 0; CursorClamp(); }
    void        ClearFreeMemory()           { TextA.clear(); TextToRevertTo.clear(); }
    void        OnKeyPressed(int key);      // Cannot be inline because we call in code in stb_textedit.h implementation
    void        OnCharPressed(unsigned int c);

    // Cursor & Selection
    void        CursorAnimReset();
    void        CursorClamp();
    bool        HasSelection() const;
    void        ClearSelection();
    int         GetCursorPos() const;
    int         GetSelectionStart() const;
    int         GetSelectionEnd() const;
    void        SelectAll();

    // Reload user buf (WIP #2890)
    // If you modify underlying user-passed const char* while active you need to call this (InputText V2 may lift this)
    //   strcpy(my_buf, "hello");
    //   if (ImGuiInputTextState* state = ImGui::GetInputTextState(id)) // id may be ImGui::GetItemID() is last item
    //       state->ReloadUserBufAndSelectAll();
    void        ReloadUserBufAndSelectAll();
    void        ReloadUserBufAndKeepSelection();
    void        ReloadUserBufAndMoveToEnd();
};

enum ImGuiWindowRefreshFlags_
{
    ImGuiWindowRefreshFlags_None                = 0,
    ImGuiWindowRefreshFlags_TryToAvoidRefresh   = 1 << 0,   // [EXPERIMENTAL] Try to keep existing contents, USER MUST NOT HONOR BEGIN() RETURNING FALSE AND NOT APPEND.
    ImGuiWindowRefreshFlags_RefreshOnHover      = 1 << 1,   // [EXPERIMENTAL] Always refresh on hover
    ImGuiWindowRefreshFlags_RefreshOnFocus      = 1 << 2,   // [EXPERIMENTAL] Always refresh on focus
    // Refresh policy/frequency, Load Balancing etc.
};

enum ImGuiNextWindowDataFlags_
{
    ImGuiNextWindowDataFlags_None               = 0,
    ImGuiNextWindowDataFlags_HasPos             = 1 << 0,
    ImGuiNextWindowDataFlags_HasSize            = 1 << 1,
    ImGuiNextWindowDataFlags_HasContentSize     = 1 << 2,
    ImGuiNextWindowDataFlags_HasCollapsed       = 1 << 3,
    ImGuiNextWindowDataFlags_HasSizeConstraint  = 1 << 4,
    ImGuiNextWindowDataFlags_HasFocus           = 1 << 5,
    ImGuiNextWindowDataFlags_HasBgAlpha         = 1 << 6,
    ImGuiNextWindowDataFlags_HasScroll          = 1 << 7,
    ImGuiNextWindowDataFlags_HasChildFlags      = 1 << 8,
    ImGuiNextWindowDataFlags_HasRefreshPolicy   = 1 << 9,
    ImGuiNextWindowDataFlags_HasViewport        = 1 << 10,
    ImGuiNextWindowDataFlags_HasDock            = 1 << 11,
    ImGuiNextWindowDataFlags_HasWindowClass     = 1 << 12,
};

// Storage for SetNexWindow** functions
struct ImGuiNextWindowData
{
    ImGuiNextWindowDataFlags    Flags;
    ImGuiCond                   PosCond;
    ImGuiCond                   SizeCond;
    ImGuiCond                   CollapsedCond;
    ImGuiCond                   DockCond;
    ImVec2                      PosVal;
    ImVec2                      PosPivotVal;
    ImVec2                      SizeVal;
    ImVec2                      ContentSizeVal;
    ImVec2                      ScrollVal;
    ImGuiChildFlags             ChildFlags;
    bool                        PosUndock;
    bool                        CollapsedVal;
    ImRect                      SizeConstraintRect;
    ImGuiSizeCallback           SizeCallback;
    void*                       SizeCallbackUserData;
    float                       BgAlphaVal;             // Override background alpha
    ImGuiID                     ViewportId;
    ImGuiID                     DockId;
    ImGuiWindowClass            WindowClass;
    ImVec2                      MenuBarOffsetMinVal;    // (Always on) This is not exposed publicly, so we don't clear it and it doesn't have a corresponding flag (could we? for consistency?)
    ImGuiWindowRefreshFlags     RefreshFlagsVal;

    ImGuiNextWindowData()       { memset(this, 0, sizeof(*this)); }
    inline void ClearFlags()    { Flags = ImGuiNextWindowDataFlags_None; }
};

enum ImGuiNextItemDataFlags_
{
    ImGuiNextItemDataFlags_None         = 0,
    ImGuiNextItemDataFlags_HasWidth     = 1 << 0,
    ImGuiNextItemDataFlags_HasOpen      = 1 << 1,
    ImGuiNextItemDataFlags_HasShortcut  = 1 << 2,
    ImGuiNextItemDataFlags_HasRefVal    = 1 << 3,
    ImGuiNextItemDataFlags_HasStorageID = 1 << 4,
};

struct ImGuiNextItemData
{
    ImGuiNextItemDataFlags      HasFlags;           // Called HasFlags instead of Flags to avoid mistaking this
    ImGuiItemFlags              ItemFlags;          // Currently only tested/used for ImGuiItemFlags_AllowOverlap and ImGuiItemFlags_HasSelectionUserData.
    // Non-flags members are NOT cleared by ItemAdd() meaning they are still valid during NavProcessItem()
    ImGuiID                     FocusScopeId;       // Set by SetNextItemSelectionUserData()
    ImGuiSelectionUserData      SelectionUserData;  // Set by SetNextItemSelectionUserData() (note that NULL/0 is a valid value, we use -1 == ImGuiSelectionUserData_Invalid to mark invalid values)
    float                       Width;              // Set by SetNextItemWidth()
    ImGuiKeyChord               Shortcut;           // Set by SetNextItemShortcut()
    ImGuiInputFlags             ShortcutFlags;      // Set by SetNextItemShortcut()
    bool                        OpenVal;            // Set by SetNextItemOpen()
    ImU8                        OpenCond;           // Set by SetNextItemOpen()
    ImGuiDataTypeStorage        RefVal;             // Not exposed yet, for ImGuiInputTextFlags_ParseEmptyAsRefVal
    ImGuiID                     StorageId;          // Set by SetNextItemStorageID()

    ImGuiNextItemData()         { memset(this, 0, sizeof(*this)); SelectionUserData = -1; }
    inline void ClearFlags()    { HasFlags = ImGuiNextItemDataFlags_None; ItemFlags = ImGuiItemFlags_None; } // Also cleared manually by ItemAdd()!
};

// Status storage for the last submitted item
struct ImGuiLastItemData
{
    ImGuiID                 ID;
    ImGuiItemFlags          ItemFlags;          // See ImGuiItemFlags_ (called 'InFlags' before v1.91.4).
    ImGuiItemStatusFlags    StatusFlags;        // See ImGuiItemStatusFlags_
    ImRect                  Rect;               // Full rectangle
    ImRect                  NavRect;            // Navigation scoring rectangle (not displayed)
    // Rarely used fields are not explicitly cleared, only valid when the corresponding ImGuiItemStatusFlags are set.
    ImRect                  DisplayRect;        // Display rectangle. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasDisplayRect) is set.
    ImRect                  ClipRect;           // Clip rectangle at the time of submitting item. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasClipRect) is set..
    ImGuiKeyChord           Shortcut;           // Shortcut at the time of submitting item. ONLY VALID IF (StatusFlags & ImGuiItemStatusFlags_HasShortcut) is set..

    ImGuiLastItemData()     { memset(this, 0, sizeof(*this)); }
};

// Store data emitted by TreeNode() for usage by TreePop()
// - To implement ImGuiTreeNodeFlags_NavLeftJumpsBackHere: store the minimum amount of data
//   which we can't infer in TreePop(), to perform the equivalent of NavApplyItemToResult().
//   Only stored when the node is a potential candidate for landing on a Left arrow jump.
struct ImGuiTreeNodeStackData
{
    ImGuiID                 ID;
    ImGuiTreeNodeFlags      TreeFlags;
    ImGuiItemFlags          ItemFlags;  // Used for nav landing
    ImRect                  NavRect;    // Used for nav landing
};

// sizeof() = 20
struct  ImGuiErrorRecoveryState
{
    short   SizeOfWindowStack;
    short   SizeOfIDStack;
    short   SizeOfTreeStack;
    short   SizeOfColorStack;
    short   SizeOfStyleVarStack;
    short   SizeOfFontStack;
    short   SizeOfFocusScopeStack;
    short   SizeOfGroupStack;
    short   SizeOfItemFlagsStack;
    short   SizeOfBeginPopupStack;
    short   SizeOfDisabledStack;

    ImGuiErrorRecoveryState() { memset(this, 0, sizeof(*this)); }
};

// Data saved for each window pushed into the stack
struct ImGuiWindowStackData
{
    ImGuiWindow*            Window;
    ImGuiLastItemData       ParentLastItemDataBackup;
    ImGuiErrorRecoveryState StackSizesInBegin;          // Store size of various stacks for asserting
    bool                    DisabledOverrideReenable;   // Non-child window override disabled flag
};

struct ImGuiShrinkWidthItem
{
    int         Index;
    float       Width;
    float       InitialWidth;
};

struct ImGuiPtrOrIndex
{
    void*       Ptr;            // Either field can be set, not both. e.g. Dock node tab bars are loose while BeginTabBar() ones are in a pool.
    int         Index;          // Usually index in a main pool.

    ImGuiPtrOrIndex(void* ptr)  { Ptr = ptr; Index = -1; }
    ImGuiPtrOrIndex(int index)  { Ptr = ((void *)0); Index = index; }
};

// Data used by IsItemDeactivated()/IsItemDeactivatedAfterEdit() functions
struct ImGuiDeactivatedItemData
{
    ImGuiID     ID;
    int         ElapseFrame;
    bool        HasBeenEditedBefore;
    bool        IsAlive;
};

//-----------------------------------------------------------------------------
// [SECTION] Popup support
//-----------------------------------------------------------------------------

enum ImGuiPopupPositionPolicy
{
    ImGuiPopupPositionPolicy_Default,
    ImGuiPopupPositionPolicy_ComboBox,
    ImGuiPopupPositionPolicy_Tooltip,
};

// Storage for popup stacks (g.OpenPopupStack and g.BeginPopupStack)
struct ImGuiPopupData
{
    ImGuiID             PopupId;        // Set on OpenPopup()
    ImGuiWindow*        Window;         // Resolved on BeginPopup() - may stay unresolved if user never calls OpenPopup()
    ImGuiWindow*        RestoreNavWindow;// Set on OpenPopup(), a NavWindow that will be restored on popup close
    int                 ParentNavLayer; // Resolved on BeginPopup(). Actually a ImGuiNavLayer type (declared down below), initialized to -1 which is not part of an enum, but serves well-enough as "not any of layers" value
    int                 OpenFrameCount; // Set on OpenPopup()
    ImGuiID             OpenParentId;   // Set on OpenPopup(), we need this to differentiate multiple menu sets from each others (e.g. inside menu bar vs loose menu items)
    ImVec2              OpenPopupPos;   // Set on OpenPopup(), preferred popup position (typically == OpenMousePos when using mouse)
    ImVec2              OpenMousePos;   // Set on OpenPopup(), copy of mouse position at the time of opening popup

    ImGuiPopupData()    { memset(this, 0, sizeof(*this)); ParentNavLayer = OpenFrameCount = -1; }
};

//-----------------------------------------------------------------------------
// [SECTION] Inputs support
//-----------------------------------------------------------------------------

// Bit array for named keys
typedef ImBitArray<ImGuiKey_NamedKey_COUNT, -ImGuiKey_NamedKey_BEGIN>    ImBitArrayForNamedKeys;

// [Internal] Key ranges











// [Internal] Named shortcuts for Navigation









enum ImGuiInputEventType
{
    ImGuiInputEventType_None = 0,
    ImGuiInputEventType_MousePos,
    ImGuiInputEventType_MouseWheel,
    ImGuiInputEventType_MouseButton,
    ImGuiInputEventType_MouseViewport,
    ImGuiInputEventType_Key,
    ImGuiInputEventType_Text,
    ImGuiInputEventType_Focus,
    ImGuiInputEventType_COUNT
};

enum ImGuiInputSource
{
    ImGuiInputSource_None = 0,
    ImGuiInputSource_Mouse,         // Note: may be Mouse or TouchScreen or Pen. See io.MouseSource to distinguish them.
    ImGuiInputSource_Keyboard,
    ImGuiInputSource_Gamepad,
    ImGuiInputSource_COUNT
};

// FIXME: Structures in the union below need to be declared as anonymous unions appears to be an extension?
// Using ImVec2() would fail on Clang 'union member 'MousePos' has a non-trivial default constructor'
struct ImGuiInputEventMousePos      { float PosX, PosY; ImGuiMouseSource MouseSource; };
struct ImGuiInputEventMouseWheel    { float WheelX, WheelY; ImGuiMouseSource MouseSource; };
struct ImGuiInputEventMouseButton   { int Button; bool Down; ImGuiMouseSource MouseSource; };
struct ImGuiInputEventMouseViewport { ImGuiID HoveredViewportID; };
struct ImGuiInputEventKey           { ImGuiKey Key; bool Down; float AnalogValue; };
struct ImGuiInputEventText          { unsigned int Char; };
struct ImGuiInputEventAppFocused    { bool Focused; };

struct ImGuiInputEvent
{
    ImGuiInputEventType             Type;
    ImGuiInputSource                Source;
    ImU32                           EventId;        // Unique, sequential increasing integer to identify an event (if you need to correlate them to other data).
    union
    {
        ImGuiInputEventMousePos     MousePos;       // if Type == ImGuiInputEventType_MousePos
        ImGuiInputEventMouseWheel   MouseWheel;     // if Type == ImGuiInputEventType_MouseWheel
        ImGuiInputEventMouseButton  MouseButton;    // if Type == ImGuiInputEventType_MouseButton
        ImGuiInputEventMouseViewport MouseViewport; // if Type == ImGuiInputEventType_MouseViewport
        ImGuiInputEventKey          Key;            // if Type == ImGuiInputEventType_Key
        ImGuiInputEventText         Text;           // if Type == ImGuiInputEventType_Text
        ImGuiInputEventAppFocused   AppFocused;     // if Type == ImGuiInputEventType_Focus
    };
    bool                            AddedByTestEngine;

    ImGuiInputEvent() { memset(this, 0, sizeof(*this)); }
};

// Input function taking an 'ImGuiID owner_id' argument defaults to (ImGuiKeyOwner_Any == 0) aka don't test ownership, which matches legacy behavior.


//#define ImGuiKeyOwner_None ImGuiKeyOwner_NoOwner  // We previously called this 'ImGuiKeyOwner_None' but it was inconsistent with our pattern that _None values == 0 and quite dangerous. Also using _NoOwner makes the IsKeyPressed() calls more explicit.

typedef ImS16 ImGuiKeyRoutingIndex;

// Routing table entry (sizeof() == 16 bytes)
struct ImGuiKeyRoutingData
{
    ImGuiKeyRoutingIndex            NextEntryIndex;
    ImU16                           Mods;               // Technically we'd only need 4-bits but for simplify we store ImGuiMod_ values which need 16-bits.
    ImU8                            RoutingCurrScore;   // [DEBUG] For debug display
    ImU8                            RoutingNextScore;   // Lower is better (0: perfect score)
    ImGuiID                         RoutingCurr;
    ImGuiID                         RoutingNext;

    ImGuiKeyRoutingData()           { NextEntryIndex = -1; Mods = 0; RoutingCurrScore = RoutingNextScore = 255; RoutingCurr = RoutingNext = ((ImGuiID)-1); }
};

// Routing table: maintain a desired owner for each possible key-chord (key + mods), and setup owner in NewFrame() when mods are matching.
// Stored in main context (1 instance)
struct ImGuiKeyRoutingTable
{
    ImGuiKeyRoutingIndex            Index[ImGuiKey_NamedKey_COUNT]; // Index of first entry in Entries[]
    ImVector<ImGuiKeyRoutingData>   Entries;
    ImVector<ImGuiKeyRoutingData>   EntriesNext;                    // Double-buffer to avoid reallocation (could use a shared buffer)

    ImGuiKeyRoutingTable()          { Clear(); }
    void Clear()                    { for (int n = 0; n < ((int)(sizeof(Index) / sizeof(*(Index)))); n++) Index[n] = -1; Entries.clear(); EntriesNext.clear(); }
};

// This extends ImGuiKeyData but only for named keys (legacy keys don't support the new features)
// Stored in main context (1 per named key). In the future it might be merged into ImGuiKeyData.
struct ImGuiKeyOwnerData
{
    ImGuiID     OwnerCurr;
    ImGuiID     OwnerNext;
    bool        LockThisFrame;      // Reading this key requires explicit owner id (until end of frame). Set by ImGuiInputFlags_LockThisFrame.
    bool        LockUntilRelease;   // Reading this key requires explicit owner id (until key is released). Set by ImGuiInputFlags_LockUntilRelease. When this is true LockThisFrame is always true as well.

    ImGuiKeyOwnerData()             { OwnerCurr = OwnerNext = ((ImGuiID)-1); LockThisFrame = LockUntilRelease = false; }
};

// Extend ImGuiInputFlags_
// Flags for extended versions of IsKeyPressed(), IsMouseClicked(), Shortcut(), SetKeyOwner(), SetItemKeyOwner()
// Don't mistake with ImGuiInputTextFlags! (which is for ImGui::InputText() function)
enum ImGuiInputFlagsPrivate_
{
    // Flags for IsKeyPressed(), IsKeyChordPressed(), IsMouseClicked(), Shortcut()
    // - Repeat mode: Repeat rate selection
    ImGuiInputFlags_RepeatRateDefault           = 1 << 1,   // Repeat rate: Regular (default)
    ImGuiInputFlags_RepeatRateNavMove           = 1 << 2,   // Repeat rate: Fast
    ImGuiInputFlags_RepeatRateNavTweak          = 1 << 3,   // Repeat rate: Faster
    // - Repeat mode: Specify when repeating key pressed can be interrupted.
    // - In theory ImGuiInputFlags_RepeatUntilOtherKeyPress may be a desirable default, but it would break too many behavior so everything is opt-in.
    ImGuiInputFlags_RepeatUntilRelease          = 1 << 4,   // Stop repeating when released (default for all functions except Shortcut). This only exists to allow overriding Shortcut() default behavior.
    ImGuiInputFlags_RepeatUntilKeyModsChange    = 1 << 5,   // Stop repeating when released OR if keyboard mods are changed (default for Shortcut)
    ImGuiInputFlags_RepeatUntilKeyModsChangeFromNone = 1 << 6,  // Stop repeating when released OR if keyboard mods are leaving the None state. Allows going from Mod+Key to Key by releasing Mod.
    ImGuiInputFlags_RepeatUntilOtherKeyPress    = 1 << 7,   // Stop repeating when released OR if any other keyboard key is pressed during the repeat

    // Flags for SetKeyOwner(), SetItemKeyOwner()
    // - Locking key away from non-input aware code. Locking is useful to make input-owner-aware code steal keys from non-input-owner-aware code. If all code is input-owner-aware locking would never be necessary.
    ImGuiInputFlags_LockThisFrame               = 1 << 20,  // Further accesses to key data will require EXPLICIT owner ID (ImGuiKeyOwner_Any/0 will NOT accepted for polling). Cleared at end of frame.
    ImGuiInputFlags_LockUntilRelease            = 1 << 21,  // Further accesses to key data will require EXPLICIT owner ID (ImGuiKeyOwner_Any/0 will NOT accepted for polling). Cleared when the key is released or at end of each frame if key is released.

    // - Condition for SetItemKeyOwner()
    ImGuiInputFlags_CondHovered                 = 1 << 22,  // Only set if item is hovered (default to both)
    ImGuiInputFlags_CondActive                  = 1 << 23,  // Only set if item is active (default to both)
    ImGuiInputFlags_CondDefault_                = ImGuiInputFlags_CondHovered | ImGuiInputFlags_CondActive,

    // [Internal] Mask of which function support which flags
    ImGuiInputFlags_RepeatRateMask_             = ImGuiInputFlags_RepeatRateDefault | ImGuiInputFlags_RepeatRateNavMove | ImGuiInputFlags_RepeatRateNavTweak,
    ImGuiInputFlags_RepeatUntilMask_            = ImGuiInputFlags_RepeatUntilRelease | ImGuiInputFlags_RepeatUntilKeyModsChange | ImGuiInputFlags_RepeatUntilKeyModsChangeFromNone | ImGuiInputFlags_RepeatUntilOtherKeyPress,
    ImGuiInputFlags_RepeatMask_                 = ImGuiInputFlags_Repeat | ImGuiInputFlags_RepeatRateMask_ | ImGuiInputFlags_RepeatUntilMask_,
    ImGuiInputFlags_CondMask_                   = ImGuiInputFlags_CondHovered | ImGuiInputFlags_CondActive,
    ImGuiInputFlags_RouteTypeMask_              = ImGuiInputFlags_RouteActive | ImGuiInputFlags_RouteFocused | ImGuiInputFlags_RouteGlobal | ImGuiInputFlags_RouteAlways,
    ImGuiInputFlags_RouteOptionsMask_           = ImGuiInputFlags_RouteOverFocused | ImGuiInputFlags_RouteOverActive | ImGuiInputFlags_RouteUnlessBgFocused | ImGuiInputFlags_RouteFromRootWindow,
    ImGuiInputFlags_SupportedByIsKeyPressed     = ImGuiInputFlags_RepeatMask_,
    ImGuiInputFlags_SupportedByIsMouseClicked   = ImGuiInputFlags_Repeat,
    ImGuiInputFlags_SupportedByShortcut         = ImGuiInputFlags_RepeatMask_ | ImGuiInputFlags_RouteTypeMask_ | ImGuiInputFlags_RouteOptionsMask_,
    ImGuiInputFlags_SupportedBySetNextItemShortcut = ImGuiInputFlags_RepeatMask_ | ImGuiInputFlags_RouteTypeMask_ | ImGuiInputFlags_RouteOptionsMask_ | ImGuiInputFlags_Tooltip,
    ImGuiInputFlags_SupportedBySetKeyOwner      = ImGuiInputFlags_LockThisFrame | ImGuiInputFlags_LockUntilRelease,
    ImGuiInputFlags_SupportedBySetItemKeyOwner  = ImGuiInputFlags_SupportedBySetKeyOwner | ImGuiInputFlags_CondMask_,
};

//-----------------------------------------------------------------------------
// [SECTION] Clipper support
//-----------------------------------------------------------------------------

// Note that Max is exclusive, so perhaps should be using a Begin/End convention.
struct ImGuiListClipperRange
{
    int     Min;
    int     Max;
    bool    PosToIndexConvert;      // Begin/End are absolute position (will be converted to indices later)
    ImS8    PosToIndexOffsetMin;    // Add to Min after converting to indices
    ImS8    PosToIndexOffsetMax;    // Add to Min after converting to indices

    static ImGuiListClipperRange    FromIndices(int min, int max)                               { ImGuiListClipperRange r = { min, max, false, 0, 0 }; return r; }
    static ImGuiListClipperRange    FromPositions(float y1, float y2, int off_min, int off_max) { ImGuiListClipperRange r = { (int)y1, (int)y2, true, (ImS8)off_min, (ImS8)off_max }; return r; }
};

// Temporary clipper data, buffers shared/reused between instances
struct ImGuiListClipperData
{
    ImGuiListClipper*               ListClipper;
    float                           LossynessOffset;
    int                             StepNo;
    int                             ItemsFrozen;
    ImVector<ImGuiListClipperRange> Ranges;

    ImGuiListClipperData()          { memset(this, 0, sizeof(*this)); }
    void                            Reset(ImGuiListClipper* clipper) { ListClipper = clipper; StepNo = ItemsFrozen = 0; Ranges.resize(0); }
};

//-----------------------------------------------------------------------------
// [SECTION] Navigation support
//-----------------------------------------------------------------------------

enum ImGuiActivateFlags_
{
    ImGuiActivateFlags_None                 = 0,
    ImGuiActivateFlags_PreferInput          = 1 << 0,       // Favor activation that requires keyboard text input (e.g. for Slider/Drag). Default for Enter key.
    ImGuiActivateFlags_PreferTweak          = 1 << 1,       // Favor activation for tweaking with arrows or gamepad (e.g. for Slider/Drag). Default for Space key and if keyboard is not used.
    ImGuiActivateFlags_TryToPreserveState   = 1 << 2,       // Request widget to preserve state if it can (e.g. InputText will try to preserve cursor/selection)
    ImGuiActivateFlags_FromTabbing          = 1 << 3,       // Activation requested by a tabbing request
    ImGuiActivateFlags_FromShortcut         = 1 << 4,       // Activation requested by an item shortcut via SetNextItemShortcut() function.
};

// Early work-in-progress API for ScrollToItem()
enum ImGuiScrollFlags_
{
    ImGuiScrollFlags_None                   = 0,
    ImGuiScrollFlags_KeepVisibleEdgeX       = 1 << 0,       // If item is not visible: scroll as little as possible on X axis to bring item back into view [default for X axis]
    ImGuiScrollFlags_KeepVisibleEdgeY       = 1 << 1,       // If item is not visible: scroll as little as possible on Y axis to bring item back into view [default for Y axis for windows that are already visible]
    ImGuiScrollFlags_KeepVisibleCenterX     = 1 << 2,       // If item is not visible: scroll to make the item centered on X axis [rarely used]
    ImGuiScrollFlags_KeepVisibleCenterY     = 1 << 3,       // If item is not visible: scroll to make the item centered on Y axis
    ImGuiScrollFlags_AlwaysCenterX          = 1 << 4,       // Always center the result item on X axis [rarely used]
    ImGuiScrollFlags_AlwaysCenterY          = 1 << 5,       // Always center the result item on Y axis [default for Y axis for appearing window)
    ImGuiScrollFlags_NoScrollParent         = 1 << 6,       // Disable forwarding scrolling to parent window if required to keep item/rect visible (only scroll window the function was applied to).
    ImGuiScrollFlags_MaskX_                 = ImGuiScrollFlags_KeepVisibleEdgeX | ImGuiScrollFlags_KeepVisibleCenterX | ImGuiScrollFlags_AlwaysCenterX,
    ImGuiScrollFlags_MaskY_                 = ImGuiScrollFlags_KeepVisibleEdgeY | ImGuiScrollFlags_KeepVisibleCenterY | ImGuiScrollFlags_AlwaysCenterY,
};

enum ImGuiNavRenderCursorFlags_
{
    ImGuiNavRenderCursorFlags_None          = 0,
    ImGuiNavRenderCursorFlags_Compact       = 1 << 1,       // Compact highlight, no padding/distance from focused item
    ImGuiNavRenderCursorFlags_AlwaysDraw    = 1 << 2,       // Draw rectangular highlight if (g.NavId == id) even when g.NavCursorVisible == false, aka even when using the mouse.
    ImGuiNavRenderCursorFlags_NoRounding    = 1 << 3,






};

enum ImGuiNavMoveFlags_
{
    ImGuiNavMoveFlags_None                  = 0,
    ImGuiNavMoveFlags_LoopX                 = 1 << 0,   // On failed request, restart from opposite side
    ImGuiNavMoveFlags_LoopY                 = 1 << 1,
    ImGuiNavMoveFlags_WrapX                 = 1 << 2,   // On failed request, request from opposite side one line down (when NavDir==right) or one line up (when NavDir==left)
    ImGuiNavMoveFlags_WrapY                 = 1 << 3,   // This is not super useful but provided for completeness
    ImGuiNavMoveFlags_WrapMask_             = ImGuiNavMoveFlags_LoopX | ImGuiNavMoveFlags_LoopY | ImGuiNavMoveFlags_WrapX | ImGuiNavMoveFlags_WrapY,
    ImGuiNavMoveFlags_AllowCurrentNavId     = 1 << 4,   // Allow scoring and considering the current NavId as a move target candidate. This is used when the move source is offset (e.g. pressing PageDown actually needs to send a Up move request, if we are pressing PageDown from the bottom-most item we need to stay in place)
    ImGuiNavMoveFlags_AlsoScoreVisibleSet   = 1 << 5,   // Store alternate result in NavMoveResultLocalVisible that only comprise elements that are already fully visible (used by PageUp/PageDown)
    ImGuiNavMoveFlags_ScrollToEdgeY         = 1 << 6,   // Force scrolling to min/max (used by Home/End) // FIXME-NAV: Aim to remove or reword, probably unnecessary
    ImGuiNavMoveFlags_Forwarded             = 1 << 7,
    ImGuiNavMoveFlags_DebugNoResult         = 1 << 8,   // Dummy scoring for debug purpose, don't apply result
    ImGuiNavMoveFlags_FocusApi              = 1 << 9,   // Requests from focus API can land/focus/activate items even if they are marked with _NoTabStop (see NavProcessItemForTabbingRequest() for details)
    ImGuiNavMoveFlags_IsTabbing             = 1 << 10,  // == Focus + Activate if item is Inputable + DontChangeNavHighlight
    ImGuiNavMoveFlags_IsPageMove            = 1 << 11,  // Identify a PageDown/PageUp request.
    ImGuiNavMoveFlags_Activate              = 1 << 12,  // Activate/select target item.
    ImGuiNavMoveFlags_NoSelect              = 1 << 13,  // Don't trigger selection by not setting g.NavJustMovedTo
    ImGuiNavMoveFlags_NoSetNavCursorVisible = 1 << 14,  // Do not alter the nav cursor visible state
    ImGuiNavMoveFlags_NoClearActiveId       = 1 << 15,  // (Experimental) Do not clear active id when applying move result
};

enum ImGuiNavLayer
{
    ImGuiNavLayer_Main  = 0,    // Main scrolling layer
    ImGuiNavLayer_Menu  = 1,    // Menu layer (access with Alt)
    ImGuiNavLayer_COUNT
};

// Storage for navigation query/results
struct ImGuiNavItemData
{
    ImGuiWindow*        Window;         // Init,Move    // Best candidate window (result->ItemWindow->RootWindowForNav == request->Window)
    ImGuiID             ID;             // Init,Move    // Best candidate item ID
    ImGuiID             FocusScopeId;   // Init,Move    // Best candidate focus scope ID
    ImRect              RectRel;        // Init,Move    // Best candidate bounding box in window relative space
    ImGuiItemFlags      ItemFlags;      // ????,Move    // Best candidate item flags
    float               DistBox;        //      Move    // Best candidate box distance to current NavId
    float               DistCenter;     //      Move    // Best candidate center distance to current NavId
    float               DistAxial;      //      Move    // Best candidate axial distance to current NavId
    ImGuiSelectionUserData SelectionUserData;//I+Mov    // Best candidate SetNextItemSelectionUserData() value. Valid if (ItemFlags & ImGuiItemFlags_HasSelectionUserData)

    ImGuiNavItemData()  { Clear(); }
    void Clear()        { Window = ((void *)0); ID = FocusScopeId = 0; ItemFlags = 0; SelectionUserData = -1; DistBox = DistCenter = DistAxial = 3.402823466e+38F; }
};

// Storage for PushFocusScope(), g.FocusScopeStack[], g.NavFocusRoute[]
struct ImGuiFocusScopeData
{
    ImGuiID             ID;
    ImGuiID             WindowID;
};

//-----------------------------------------------------------------------------
// [SECTION] Typing-select support
//-----------------------------------------------------------------------------

// Flags for GetTypingSelectRequest()
enum ImGuiTypingSelectFlags_
{
    ImGuiTypingSelectFlags_None                 = 0,
    ImGuiTypingSelectFlags_AllowBackspace       = 1 << 0,   // Backspace to delete character inputs. If using: ensure GetTypingSelectRequest() is not called more than once per frame (filter by e.g. focus state)
    ImGuiTypingSelectFlags_AllowSingleCharMode  = 1 << 1,   // Allow "single char" search mode which is activated when pressing the same character multiple times.
};

// Returned by GetTypingSelectRequest(), designed to eventually be public.
struct  ImGuiTypingSelectRequest
{
    ImGuiTypingSelectFlags  Flags;              // Flags passed to GetTypingSelectRequest()
    int                     SearchBufferLen;
    const char*             SearchBuffer;       // Search buffer contents (use full string. unless SingleCharMode is set, in which case use SingleCharSize).
    bool                    SelectRequest;      // Set when buffer was modified this frame, requesting a selection.
    bool                    SingleCharMode;     // Notify when buffer contains same character repeated, to implement special mode. In this situation it preferred to not display any on-screen search indication.
    ImS8                    SingleCharSize;     // Length in bytes of first letter codepoint (1 for ascii, 2-4 for UTF-8). If (SearchBufferLen==RepeatCharSize) only 1 letter has been input.
};

// Storage for GetTypingSelectRequest()
struct  ImGuiTypingSelectState
{
    ImGuiTypingSelectRequest Request;           // User-facing data
    char            SearchBuffer[64];           // Search buffer: no need to make dynamic as this search is very transient.
    ImGuiID         FocusScope;
    int             LastRequestFrame = 0;
    float           LastRequestTime = 0.0f;
    bool            SingleCharModeLock = false; // After a certain single char repeat count we lock into SingleCharMode. Two benefits: 1) buffer never fill, 2) we can provide an immediate SingleChar mode without timer elapsing.

    ImGuiTypingSelectState() { memset(this, 0, sizeof(*this)); }
    void            Clear()  { SearchBuffer[0] = 0; SingleCharModeLock = false; } // We preserve remaining data for easier debugging
};

//-----------------------------------------------------------------------------
// [SECTION] Columns support
//-----------------------------------------------------------------------------

// Flags for internal's BeginColumns(). This is an obsolete API. Prefer using BeginTable() nowadays!
enum ImGuiOldColumnFlags_
{
    ImGuiOldColumnFlags_None                    = 0,
    ImGuiOldColumnFlags_NoBorder                = 1 << 0,   // Disable column dividers
    ImGuiOldColumnFlags_NoResize                = 1 << 1,   // Disable resizing columns when clicking on the dividers
    ImGuiOldColumnFlags_NoPreserveWidths        = 1 << 2,   // Disable column width preservation when adjusting columns
    ImGuiOldColumnFlags_NoForceWithinWindow     = 1 << 3,   // Disable forcing columns to fit within window
    ImGuiOldColumnFlags_GrowParentContentsSize  = 1 << 4,   // Restore pre-1.51 behavior of extending the parent window contents size but _without affecting the columns width at all_. Will eventually remove.

    // Obsolete names (will be removed)








};

struct ImGuiOldColumnData
{
    float               OffsetNorm;             // Column start offset, normalized 0.0 (far left) -> 1.0 (far right)
    float               OffsetNormBeforeResize;
    ImGuiOldColumnFlags Flags;                  // Not exposed
    ImRect              ClipRect;

    ImGuiOldColumnData() { memset(this, 0, sizeof(*this)); }
};

struct ImGuiOldColumns
{
    ImGuiID             ID;
    ImGuiOldColumnFlags Flags;
    bool                IsFirstFrame;
    bool                IsBeingResized;
    int                 Current;
    int                 Count;
    float               OffMinX, OffMaxX;       // Offsets from HostWorkRect.Min.x
    float               LineMinY, LineMaxY;
    float               HostCursorPosY;         // Backup of CursorPos at the time of BeginColumns()
    float               HostCursorMaxPosX;      // Backup of CursorMaxPos at the time of BeginColumns()
    ImRect              HostInitialClipRect;    // Backup of ClipRect at the time of BeginColumns()
    ImRect              HostBackupClipRect;     // Backup of ClipRect during PushColumnsBackground()/PopColumnsBackground()
    ImRect              HostBackupParentWorkRect;//Backup of WorkRect at the time of BeginColumns()
    ImVector<ImGuiOldColumnData> Columns;
    ImDrawListSplitter  Splitter;

    ImGuiOldColumns()   { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Box-select support
//-----------------------------------------------------------------------------

struct ImGuiBoxSelectState
{
    // Active box-selection data (persistent, 1 active at a time)
    ImGuiID                 ID;
    bool                    IsActive;
    bool                    IsStarting;
    bool                    IsStartedFromVoid;  // Starting click was not from an item.
    bool                    IsStartedSetNavIdOnce;
    bool                    RequestClear;
    ImGuiKeyChord           KeyMods : 16;       // Latched key-mods for box-select logic.
    ImVec2                  StartPosRel;        // Start position in window-contents relative space (to support scrolling)
    ImVec2                  EndPosRel;          // End position in window-contents relative space
    ImVec2                  ScrollAccum;        // Scrolling accumulator (to behave at high-frame spaces)
    ImGuiWindow*            Window;

    // Temporary/Transient data
    bool                    UnclipMode;         // (Temp/Transient, here in hot area). Set/cleared by the BeginMultiSelect()/EndMultiSelect() owning active box-select.
    ImRect                  UnclipRect;         // Rectangle where ItemAdd() clipping may be temporarily disabled. Need support by multi-select supporting widgets.
    ImRect                  BoxSelectRectPrev;  // Selection rectangle in absolute coordinates (derived every frame from BoxSelectStartPosRel and MousePos)
    ImRect                  BoxSelectRectCurr;

    ImGuiBoxSelectState()   { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Multi-select support
//-----------------------------------------------------------------------------

// We always assume that -1 is an invalid value (which works for indices and pointers)


// Temporary storage for multi-select
struct  ImGuiMultiSelectTempData
{
    ImGuiMultiSelectIO      IO;                 // MUST BE FIRST FIELD. Requests are set and returned by BeginMultiSelect()/EndMultiSelect() + written to by user during the loop.
    ImGuiMultiSelectState*  Storage;
    ImGuiID                 FocusScopeId;       // Copied from g.CurrentFocusScopeId (unless another selection scope was pushed manually)
    ImGuiMultiSelectFlags   Flags;
    ImVec2                  ScopeRectMin;
    ImVec2                  BackupCursorMaxPos;
    ImGuiSelectionUserData  LastSubmittedItem;  // Copy of last submitted item data, used to merge output ranges.
    ImGuiID                 BoxSelectId;
    ImGuiKeyChord           KeyMods;
    ImS8                    LoopRequestSetAll;  // -1: no operation, 0: clear all, 1: select all.
    bool                    IsEndIO;            // Set when switching IO from BeginMultiSelect() to EndMultiSelect() state.
    bool                    IsFocused;          // Set if currently focusing the selection scope (any item of the selection). May be used if you have custom shortcut associated to selection.
    bool                    IsKeyboardSetRange; // Set by BeginMultiSelect() when using Shift+Navigation. Because scrolling may be affected we can't afford a frame of lag with Shift+Navigation.
    bool                    NavIdPassedBy;
    bool                    RangeSrcPassedBy;   // Set by the item that matches RangeSrcItem.
    bool                    RangeDstPassedBy;   // Set by the item that matches NavJustMovedToId when IsSetRange is set.

    ImGuiMultiSelectTempData()  { Clear(); }
    void Clear()            { size_t io_sz = sizeof(IO); ClearIO(); memset((void*)(&IO + 1), 0, sizeof(*this) - io_sz); } // Zero-clear except IO as we preserve IO.Requests[] buffer allocation.
    void ClearIO()          { IO.Requests.resize(0); IO.RangeSrcItem = IO.NavIdItem = ((ImGuiSelectionUserData)-1); IO.NavIdSelected = IO.RangeSrcReset = false; }
};

// Persistent storage for multi-select (as long as selection is alive)
struct  ImGuiMultiSelectState
{
    ImGuiWindow*            Window;
    ImGuiID                 ID;
    int                     LastFrameActive;    // Last used frame-count, for GC.
    int                     LastSelectionSize;  // Set by BeginMultiSelect() based on optional info provided by user. May be -1 if unknown.
    ImS8                    RangeSelected;      // -1 (don't have) or true/false
    ImS8                    NavIdSelected;      // -1 (don't have) or true/false
    ImGuiSelectionUserData  RangeSrcItem;       //
    ImGuiSelectionUserData  NavIdItem;          // SetNextItemSelectionUserData() value for NavId (if part of submitted items)

    ImGuiMultiSelectState() { Window = ((void *)0); ID = 0; LastFrameActive = LastSelectionSize = 0; RangeSelected = NavIdSelected = -1; RangeSrcItem = NavIdItem = ((ImGuiSelectionUserData)-1); }
};

//-----------------------------------------------------------------------------
// [SECTION] Docking support
//-----------------------------------------------------------------------------






// Extend ImGuiDockNodeFlags_
enum ImGuiDockNodeFlagsPrivate_
{
    // [Internal]
    ImGuiDockNodeFlags_DockSpace                = 1 << 10,  // Saved // A dockspace is a node that occupy space within an existing user window. Otherwise the node is floating and create its own window.
    ImGuiDockNodeFlags_CentralNode              = 1 << 11,  // Saved // The central node has 2 main properties: stay visible when empty, only use "remaining" spaces from its neighbor.
    ImGuiDockNodeFlags_NoTabBar                 = 1 << 12,  // Saved // Tab bar is completely unavailable. No triangle in the corner to enable it back.
    ImGuiDockNodeFlags_HiddenTabBar             = 1 << 13,  // Saved // Tab bar is hidden, with a triangle in the corner to show it again (NB: actual tab-bar instance may be destroyed as this is only used for single-window tab bar)
    ImGuiDockNodeFlags_NoWindowMenuButton       = 1 << 14,  // Saved // Disable window/docking menu (that one that appears instead of the collapse button)
    ImGuiDockNodeFlags_NoCloseButton            = 1 << 15,  // Saved // Disable close button
    ImGuiDockNodeFlags_NoResizeX                = 1 << 16,  //       //
    ImGuiDockNodeFlags_NoResizeY                = 1 << 17,  //       //
    ImGuiDockNodeFlags_DockedWindowsInFocusRoute= 1 << 18,  //       // Any docked window will be automatically be focus-route chained (window->ParentWindowForFocusRoute set to this) so Shortcut() in this window can run when any docked window is focused.

    // Disable docking/undocking actions in this dockspace or individual node (existing docked nodes will be preserved)
    // Those are not exposed in public because the desirable sharing/inheriting/copy-flag-on-split behaviors are quite difficult to design and understand.
    // The two public flags ImGuiDockNodeFlags_NoDockingOverCentralNode/ImGuiDockNodeFlags_NoDockingSplit don't have those issues.
    ImGuiDockNodeFlags_NoDockingSplitOther      = 1 << 19,  //       // Disable this node from splitting other windows/nodes.
    ImGuiDockNodeFlags_NoDockingOverMe          = 1 << 20,  //       // Disable other windows/nodes from being docked over this node.
    ImGuiDockNodeFlags_NoDockingOverOther       = 1 << 21,  //       // Disable this node from being docked over another window or non-empty node.
    ImGuiDockNodeFlags_NoDockingOverEmpty       = 1 << 22,  //       // Disable this node from being docked over an empty node (e.g. DockSpace with no other windows)
    ImGuiDockNodeFlags_NoDocking                = ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingOverOther | ImGuiDockNodeFlags_NoDockingOverEmpty | ImGuiDockNodeFlags_NoDockingSplit | ImGuiDockNodeFlags_NoDockingSplitOther,

    // Masks
    ImGuiDockNodeFlags_SharedFlagsInheritMask_  = ~0,
    ImGuiDockNodeFlags_NoResizeFlagsMask_       = (int)ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY,

    // When splitting, those local flags are moved to the inheriting child, never duplicated
    ImGuiDockNodeFlags_LocalFlagsTransferMask_  = (int)ImGuiDockNodeFlags_NoDockingSplit | ImGuiDockNodeFlags_NoResizeFlagsMask_ | (int)ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_CentralNode | ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton,
    ImGuiDockNodeFlags_SavedFlagsMask_          = ImGuiDockNodeFlags_NoResizeFlagsMask_ | ImGuiDockNodeFlags_DockSpace | ImGuiDockNodeFlags_CentralNode | ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton,
};

// Store the source authority (dock node vs window) of a field
enum ImGuiDataAuthority_
{
    ImGuiDataAuthority_Auto,
    ImGuiDataAuthority_DockNode,
    ImGuiDataAuthority_Window,
};

enum ImGuiDockNodeState
{
    ImGuiDockNodeState_Unknown,
    ImGuiDockNodeState_HostWindowHiddenBecauseSingleWindow,
    ImGuiDockNodeState_HostWindowHiddenBecauseWindowsAreResizing,
    ImGuiDockNodeState_HostWindowVisible,
};

// sizeof() 156~192
struct  ImGuiDockNode
{
    ImGuiID                 ID;
    ImGuiDockNodeFlags      SharedFlags;                // (Write) Flags shared by all nodes of a same dockspace hierarchy (inherited from the root node)
    ImGuiDockNodeFlags      LocalFlags;                 // (Write) Flags specific to this node
    ImGuiDockNodeFlags      LocalFlagsInWindows;        // (Write) Flags specific to this node, applied from windows
    ImGuiDockNodeFlags      MergedFlags;                // (Read)  Effective flags (== SharedFlags | LocalFlagsInNode | LocalFlagsInWindows)
    ImGuiDockNodeState      State;
    ImGuiDockNode*          ParentNode;
    ImGuiDockNode*          ChildNodes[2];              // [Split node only] Child nodes (left/right or top/bottom). Consider switching to an array.
    ImVector<ImGuiWindow*>  Windows;                    // Note: unordered list! Iterate TabBar->Tabs for user-order.
    ImGuiTabBar*            TabBar;
    ImVec2                  Pos;                        // Current position
    ImVec2                  Size;                       // Current size
    ImVec2                  SizeRef;                    // [Split node only] Last explicitly written-to size (overridden when using a splitter affecting the node), used to calculate Size.
    ImGuiAxis               SplitAxis;                  // [Split node only] Split axis (X or Y)
    ImGuiWindowClass        WindowClass;                // [Root node only]
    ImU32                   LastBgColor;

    ImGuiWindow*            HostWindow;
    ImGuiWindow*            VisibleWindow;              // Generally point to window which is ID is == SelectedTabID, but when CTRL+Tabbing this can be a different window.
    ImGuiDockNode*          CentralNode;                // [Root node only] Pointer to central node.
    ImGuiDockNode*          OnlyNodeWithWindows;        // [Root node only] Set when there is a single visible node within the hierarchy.
    int                     CountNodeWithWindows;       // [Root node only]
    int                     LastFrameAlive;             // Last frame number the node was updated or kept alive explicitly with DockSpace() + ImGuiDockNodeFlags_KeepAliveOnly
    int                     LastFrameActive;            // Last frame number the node was updated.
    int                     LastFrameFocused;           // Last frame number the node was focused.
    ImGuiID                 LastFocusedNodeId;          // [Root node only] Which of our child docking node (any ancestor in the hierarchy) was last focused.
    ImGuiID                 SelectedTabId;              // [Leaf node only] Which of our tab/window is selected.
    ImGuiID                 WantCloseTabId;             // [Leaf node only] Set when closing a specific tab/window.
    ImGuiID                 RefViewportId;              // Reference viewport ID from visible window when HostWindow == NULL.
    ImGuiDataAuthority      AuthorityForPos         :3;
    ImGuiDataAuthority      AuthorityForSize        :3;
    ImGuiDataAuthority      AuthorityForViewport    :3;
    bool                    IsVisible               :1; // Set to false when the node is hidden (usually disabled as it has no active window)
    bool                    IsFocused               :1;
    bool                    IsBgDrawnThisFrame      :1;
    bool                    HasCloseButton          :1; // Provide space for a close button (if any of the docked window has one). Note that button may be hidden on window without one.
    bool                    HasWindowMenuButton     :1;
    bool                    HasCentralNodeChild     :1;
    bool                    WantCloseAll            :1; // Set when closing all tabs at once.
    bool                    WantLockSizeOnce        :1;
    bool                    WantMouseMove           :1; // After a node extraction we need to transition toward moving the newly created host window
    bool                    WantHiddenTabBarUpdate  :1;
    bool                    WantHiddenTabBarToggle  :1;

    ImGuiDockNode(ImGuiID id);
    ~ImGuiDockNode();
    bool                    IsRootNode() const      { return ParentNode == ((void *)0); }
    bool                    IsDockSpace() const     { return (MergedFlags & ImGuiDockNodeFlags_DockSpace) != 0; }
    bool                    IsFloatingNode() const  { return ParentNode == ((void *)0) && (MergedFlags & ImGuiDockNodeFlags_DockSpace) == 0; }
    bool                    IsCentralNode() const   { return (MergedFlags & ImGuiDockNodeFlags_CentralNode) != 0; }
    bool                    IsHiddenTabBar() const  { return (MergedFlags & ImGuiDockNodeFlags_HiddenTabBar) != 0; } // Hidden tab bar can be shown back by clicking the small triangle
    bool                    IsNoTabBar() const      { return (MergedFlags & ImGuiDockNodeFlags_NoTabBar) != 0; }     // Never show a tab bar
    bool                    IsSplitNode() const     { return ChildNodes[0] != ((void *)0); }
    bool                    IsLeafNode() const      { return ChildNodes[0] == ((void *)0); }
    bool                    IsEmpty() const         { return ChildNodes[0] == ((void *)0) && Windows.Size == 0; }
    ImRect                  Rect() const            { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }

    void                    SetLocalFlags(ImGuiDockNodeFlags flags) { LocalFlags = flags; UpdateMergedFlags(); }
    void                    UpdateMergedFlags()     { MergedFlags = SharedFlags | LocalFlags | LocalFlagsInWindows; }
};

// List of colors that are stored at the time of Begin() into Docked Windows.
// We currently store the packed colors in a simple array window->DockStyle.Colors[].
// A better solution may involve appending into a log of colors in ImGuiContext + store offsets into those arrays in ImGuiWindow,
// but it would be more complex as we'd need to double-buffer both as e.g. drop target may refer to window from last frame.
enum ImGuiWindowDockStyleCol
{
    ImGuiWindowDockStyleCol_Text,
    ImGuiWindowDockStyleCol_TabHovered,
    ImGuiWindowDockStyleCol_TabFocused,
    ImGuiWindowDockStyleCol_TabSelected,
    ImGuiWindowDockStyleCol_TabSelectedOverline,
    ImGuiWindowDockStyleCol_TabDimmed,
    ImGuiWindowDockStyleCol_TabDimmedSelected,
    ImGuiWindowDockStyleCol_TabDimmedSelectedOverline,
    ImGuiWindowDockStyleCol_COUNT
};

// We don't store style.Alpha: dock_node->LastBgColor embeds it and otherwise it would only affect the docking tab, which intuitively I would say we don't want to.
struct ImGuiWindowDockStyle
{
    ImU32 Colors[ImGuiWindowDockStyleCol_COUNT];
};

struct ImGuiDockContext
{
    ImGuiStorage                    Nodes;          // Map ID -> ImGuiDockNode*: Active nodes
    ImVector<ImGuiDockRequest>      Requests;
    ImVector<ImGuiDockNodeSettings> NodesSettings;
    bool                            WantFullRebuild;
    ImGuiDockContext()              { memset(this, 0, sizeof(*this)); }
};


//-----------------------------------------------------------------------------
// [SECTION] Viewport support
//-----------------------------------------------------------------------------

// ImGuiViewport Private/Internals fields (cardinal sin: we are using inheritance!)
// Every instance of ImGuiViewport is in fact a ImGuiViewportP.
struct ImGuiViewportP : public ImGuiViewport
{
    ImGuiWindow*        Window;                 // Set when the viewport is owned by a window (and ImGuiViewportFlags_CanHostOtherWindows is NOT set)
    int                 Idx;
    int                 LastFrameActive;        // Last frame number this viewport was activated by a window
    int                 LastFocusedStampCount;  // Last stamp number from when a window hosted by this viewport was focused (by comparing this value between two viewport we have an implicit viewport z-order we use as fallback)
    ImGuiID             LastNameHash;
    ImVec2              LastPos;
    ImVec2              LastSize;
    float               Alpha;                  // Window opacity (when dragging dockable windows/viewports we make them transparent)
    float               LastAlpha;
    bool                LastFocusedHadNavWindow;// Instead of maintaining a LastFocusedWindow (which may harder to correctly maintain), we merely store weither NavWindow != NULL last time the viewport was focused.
    short               PlatformMonitor;
    int                 BgFgDrawListsLastFrame[2]; // Last frame number the background (0) and foreground (1) draw lists were used
    ImDrawList*         BgFgDrawLists[2];       // Convenience background (0) and foreground (1) draw lists. We use them to draw software mouser cursor when io.MouseDrawCursor is set and to draw most debug overlays.
    ImDrawData          DrawDataP;
    ImDrawDataBuilder   DrawDataBuilder;        // Temporary data while building final ImDrawData
    ImVec2              LastPlatformPos;
    ImVec2              LastPlatformSize;
    ImVec2              LastRendererSize;

    // Per-viewport work area
    // - Insets are >= 0.0f values, distance from viewport corners to work area.
    // - BeginMainMenuBar() and DockspaceOverViewport() tend to use work area to avoid stepping over existing contents.
    // - Generally 'safeAreaInsets' in iOS land, 'DisplayCutout' in Android land.
    ImVec2              WorkInsetMin;           // Work Area inset locked for the frame. GetWorkRect() always fits within GetMainRect().
    ImVec2              WorkInsetMax;           // "
    ImVec2              BuildWorkInsetMin;      // Work Area inset accumulator for current frame, to become next frame's WorkInset
    ImVec2              BuildWorkInsetMax;      // "

    ImGuiViewportP()                    { Window = ((void *)0); Idx = -1; LastFrameActive = BgFgDrawListsLastFrame[0] = BgFgDrawListsLastFrame[1] = LastFocusedStampCount = -1; LastNameHash = 0; Alpha = LastAlpha = 1.0f; LastFocusedHadNavWindow = false; PlatformMonitor = -1; BgFgDrawLists[0] = BgFgDrawLists[1] = ((void *)0); LastPlatformPos = LastPlatformSize = LastRendererSize = ImVec2(3.402823466e+38F, 3.402823466e+38F); }
    ~ImGuiViewportP()                   { if (BgFgDrawLists[0]) IM_DELETE(BgFgDrawLists[0]); if (BgFgDrawLists[1]) IM_DELETE(BgFgDrawLists[1]); }
    void    ClearRequestFlags()         { PlatformRequestClose = PlatformRequestMove = PlatformRequestResize = false; }

    // Calculate work rect pos/size given a set of offset (we have 1 pair of offset for rect locked from last frame data, and 1 pair for currently building rect)
    ImVec2  CalcWorkRectPos(const ImVec2& inset_min) const                           { return ImVec2(Pos.x + inset_min.x, Pos.y + inset_min.y); }
    ImVec2  CalcWorkRectSize(const ImVec2& inset_min, const ImVec2& inset_max) const { return ImVec2(ImMax(0.0f, Size.x - inset_min.x - inset_max.x), ImMax(0.0f, Size.y - inset_min.y - inset_max.y)); }
    void    UpdateWorkRect()            { WorkPos = CalcWorkRectPos(WorkInsetMin); WorkSize = CalcWorkRectSize(WorkInsetMin, WorkInsetMax); } // Update public fields

    // Helpers to retrieve ImRect (we don't need to store BuildWorkRect as every access tend to change it, hence the code asymmetry)
    ImRect  GetMainRect() const         { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    ImRect  GetWorkRect() const         { return ImRect(WorkPos.x, WorkPos.y, WorkPos.x + WorkSize.x, WorkPos.y + WorkSize.y); }
    ImRect  GetBuildWorkRect() const    { ImVec2 pos = CalcWorkRectPos(BuildWorkInsetMin); ImVec2 size = CalcWorkRectSize(BuildWorkInsetMin, BuildWorkInsetMax); return ImRect(pos.x, pos.y, pos.x + size.x, pos.y + size.y); }
};

//-----------------------------------------------------------------------------
// [SECTION] Settings support
//-----------------------------------------------------------------------------

// Windows data saved in imgui.ini file
// Because we never destroy or rename ImGuiWindowSettings, we can store the names in a separate buffer easily.
// (this is designed to be stored in a ImChunkStream buffer, with the variable-length Name following our structure)
struct ImGuiWindowSettings
{
    ImGuiID     ID;
    ImVec2ih    Pos;            // NB: Settings position are stored RELATIVE to the viewport! Whereas runtime ones are absolute positions.
    ImVec2ih    Size;
    ImVec2ih    ViewportPos;
    ImGuiID     ViewportId;
    ImGuiID     DockId;         // ID of last known DockNode (even if the DockNode is invisible because it has only 1 active window), or 0 if none.
    ImGuiID     ClassId;        // ID of window class if specified
    short       DockOrder;      // Order of the last time the window was visible within its DockNode. This is used to reorder windows that are reappearing on the same frame. Same value between windows that were active and windows that were none are possible.
    bool        Collapsed;
    bool        IsChild;
    bool        WantApply;      // Set when loaded from .ini data (to enable merging/loading .ini data into an already running context)
    bool        WantDelete;     // Set to invalidate/delete the settings entry

    ImGuiWindowSettings()       { memset(this, 0, sizeof(*this)); DockOrder = -1; }
    char* GetName()             { return (char*)(this + 1); }
};

struct ImGuiSettingsHandler
{
    const char* TypeName;       // Short description stored in .ini file. Disallowed characters: '[' ']'
    ImGuiID     TypeHash;       // == ImHashStr(TypeName)
    void        (*ClearAllFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler);                                // Clear all settings data
    void        (*ReadInitFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler);                                // Read: Called before reading (in registration order)
    void*       (*ReadOpenFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler, const char* name);              // Read: Called when entering into a new ini entry e.g. "[Window][Name]"
    void        (*ReadLineFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler, void* entry, const char* line); // Read: Called for every line of text within an ini entry
    void        (*ApplyAllFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler);                                // Read: Called after reading (in registration order)
    void        (*WriteAllFn)(ImGuiContext* ctx, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf);      // Write: Output every entries into 'out_buf'
    void*       UserData;

    ImGuiSettingsHandler() { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] Localization support
//-----------------------------------------------------------------------------

// This is experimental and not officially supported, it'll probably fall short of features, if/when it does we may backtrack.
enum ImGuiLocKey : int
{
    ImGuiLocKey_VersionStr,
    ImGuiLocKey_TableSizeOne,
    ImGuiLocKey_TableSizeAllFit,
    ImGuiLocKey_TableSizeAllDefault,
    ImGuiLocKey_TableResetOrder,
    ImGuiLocKey_WindowingMainMenuBar,
    ImGuiLocKey_WindowingPopup,
    ImGuiLocKey_WindowingUntitled,
    ImGuiLocKey_OpenLink_s,
    ImGuiLocKey_CopyLink,
    ImGuiLocKey_DockingHideTabBar,
    ImGuiLocKey_DockingHoldShiftToDock,
    ImGuiLocKey_DockingDragToUndockOrMoveNode,
    ImGuiLocKey_COUNT
};

struct ImGuiLocEntry
{
    ImGuiLocKey     Key;
    const char*     Text;
};

//-----------------------------------------------------------------------------
// [SECTION] Error handling, State recovery support
//-----------------------------------------------------------------------------

// Macros used by Recoverable Error handling
// - Only dispatch error if _EXPR: evaluate as assert (similar to an assert macro).
// - The message will always be a string literal, in order to increase likelihood of being display by an assert handler.
// - See 'Demo->Configuration->Error Handling' and ImGuiIO definitions for details on error handling.
// - Read https://github.com/ocornut/imgui/wiki/Error-Handling for details on error handling.



// The error callback is currently not public, as it is expected that only advanced users will rely on it.
typedef void (*ImGuiErrorCallback)(ImGuiContext* ctx, void* user_data, const char* msg); // Function signature for g.ErrorCallback

//-----------------------------------------------------------------------------
// [SECTION] Metrics, Debug Tools
//-----------------------------------------------------------------------------

// See IMGUI_DEBUG_LOG() and IMGUI_DEBUG_LOG_XXX() macros.
enum ImGuiDebugLogFlags_
{
    // Event types
    ImGuiDebugLogFlags_None                 = 0,
    ImGuiDebugLogFlags_EventError           = 1 << 0,   // Error submitted by IM_ASSERT_USER_ERROR()
    ImGuiDebugLogFlags_EventActiveId        = 1 << 1,
    ImGuiDebugLogFlags_EventFocus           = 1 << 2,
    ImGuiDebugLogFlags_EventPopup           = 1 << 3,
    ImGuiDebugLogFlags_EventNav             = 1 << 4,
    ImGuiDebugLogFlags_EventClipper         = 1 << 5,
    ImGuiDebugLogFlags_EventSelection       = 1 << 6,
    ImGuiDebugLogFlags_EventIO              = 1 << 7,
    ImGuiDebugLogFlags_EventFont            = 1 << 8,
    ImGuiDebugLogFlags_EventInputRouting    = 1 << 9,
    ImGuiDebugLogFlags_EventDocking         = 1 << 10,
    ImGuiDebugLogFlags_EventViewport        = 1 << 11,

    ImGuiDebugLogFlags_EventMask_           = ImGuiDebugLogFlags_EventError | ImGuiDebugLogFlags_EventActiveId | ImGuiDebugLogFlags_EventFocus | ImGuiDebugLogFlags_EventPopup | ImGuiDebugLogFlags_EventNav | ImGuiDebugLogFlags_EventClipper | ImGuiDebugLogFlags_EventSelection | ImGuiDebugLogFlags_EventIO | ImGuiDebugLogFlags_EventFont | ImGuiDebugLogFlags_EventInputRouting | ImGuiDebugLogFlags_EventDocking | ImGuiDebugLogFlags_EventViewport,
    ImGuiDebugLogFlags_OutputToTTY          = 1 << 20,  // Also send output to TTY
    ImGuiDebugLogFlags_OutputToTestEngine   = 1 << 21,  // Also send output to Test Engine
};

struct ImGuiDebugAllocEntry
{
    int         FrameCount;
    ImS16       AllocCount;
    ImS16       FreeCount;
};

struct ImGuiDebugAllocInfo
{
    int         TotalAllocCount;            // Number of call to MemAlloc().
    int         TotalFreeCount;
    ImS16       LastEntriesIdx;             // Current index in buffer
    ImGuiDebugAllocEntry LastEntriesBuf[6]; // Track last 6 frames that had allocations

    ImGuiDebugAllocInfo() { memset(this, 0, sizeof(*this)); }
};

struct ImGuiMetricsConfig
{
    bool        ShowDebugLog = false;
    bool        ShowIDStackTool = false;
    bool        ShowWindowsRects = false;
    bool        ShowWindowsBeginOrder = false;
    bool        ShowTablesRects = false;
    bool        ShowDrawCmdMesh = true;
    bool        ShowDrawCmdBoundingBoxes = true;
    bool        ShowTextEncodingViewer = false;
    bool        ShowAtlasTintedWithTextColor = false;
    bool        ShowDockingNodes = false;
    int         ShowWindowsRectsType = -1;
    int         ShowTablesRectsType = -1;
    int         HighlightMonitorIdx = -1;
    ImGuiID     HighlightViewportID = 0;
};

struct ImGuiStackLevelInfo
{
    ImGuiID                 ID;
    ImS8                    QueryFrameCount;            // >= 1: Query in progress
    bool                    QuerySuccess;               // Obtained result from DebugHookIdInfo()
    ImGuiDataType           DataType : 8;
    char                    Desc[57];                   // Arbitrarily sized buffer to hold a result (FIXME: could replace Results[] with a chunk stream?) FIXME: Now that we added CTRL+C this should be fixed.

    ImGuiStackLevelInfo()   { memset(this, 0, sizeof(*this)); }
};

// State for ID Stack tool queries
struct ImGuiIDStackTool
{
    int                     LastActiveFrame;
    int                     StackLevel;                 // -1: query stack and resize Results, >= 0: individual stack level
    ImGuiID                 QueryId;                    // ID to query details for
    ImVector<ImGuiStackLevelInfo> Results;
    bool                    CopyToClipboardOnCtrlC;
    float                   CopyToClipboardLastTime;

    ImGuiIDStackTool()      { memset(this, 0, sizeof(*this)); CopyToClipboardLastTime = -3.402823466e+38F; }
};

//-----------------------------------------------------------------------------
// [SECTION] Generic context hooks
//-----------------------------------------------------------------------------

typedef void (*ImGuiContextHookCallback)(ImGuiContext* ctx, ImGuiContextHook* hook);
enum ImGuiContextHookType { ImGuiContextHookType_NewFramePre, ImGuiContextHookType_NewFramePost, ImGuiContextHookType_EndFramePre, ImGuiContextHookType_EndFramePost, ImGuiContextHookType_RenderPre, ImGuiContextHookType_RenderPost, ImGuiContextHookType_Shutdown, ImGuiContextHookType_PendingRemoval_ };

struct ImGuiContextHook
{
    ImGuiID                     HookId;     // A unique ID assigned by AddContextHook()
    ImGuiContextHookType        Type;
    ImGuiID                     Owner;
    ImGuiContextHookCallback    Callback;
    void*                       UserData;

    ImGuiContextHook()          { memset(this, 0, sizeof(*this)); }
};

//-----------------------------------------------------------------------------
// [SECTION] ImGuiContext (main Dear ImGui context)
//-----------------------------------------------------------------------------

struct ImGuiContext
{
    bool                    Initialized;
    bool                    FontAtlasOwnedByContext;            // IO.Fonts-> is owned by the ImGuiContext and will be destructed along with it.
    ImGuiIO                 IO;
    ImGuiPlatformIO         PlatformIO;
    ImGuiStyle              Style;
    ImGuiConfigFlags        ConfigFlagsCurrFrame;               // = g.IO.ConfigFlags at the time of NewFrame()
    ImGuiConfigFlags        ConfigFlagsLastFrame;
    ImFont*                 Font;                               // (Shortcut) == FontStack.empty() ? IO.Font : FontStack.back()
    float                   FontSize;                           // (Shortcut) == FontBaseSize * g.CurrentWindow->FontWindowScale == window->FontSize(). Text height for current window.
    float                   FontBaseSize;                       // (Shortcut) == IO.FontGlobalScale * Font->Scale * Font->FontSize. Base text height.
    float                   FontScale;                          // == FontSize / Font->FontSize
    float                   CurrentDpiScale;                    // Current window/viewport DpiScale == CurrentViewport->DpiScale
    ImDrawListSharedData    DrawListSharedData;
    double                  Time;
    int                     FrameCount;
    int                     FrameCountEnded;
    int                     FrameCountPlatformEnded;
    int                     FrameCountRendered;
    ImGuiID                 WithinEndChildID;                   // Set within EndChild()
    bool                    WithinFrameScope;                   // Set by NewFrame(), cleared by EndFrame()
    bool                    WithinFrameScopeWithImplicitWindow; // Set by NewFrame(), cleared by EndFrame() when the implicit debug window has been pushed
    bool                    GcCompactAll;                       // Request full GC
    bool                    TestEngineHookItems;                // Will call test engine hooks: ImGuiTestEngineHook_ItemAdd(), ImGuiTestEngineHook_ItemInfo(), ImGuiTestEngineHook_Log()
    void*                   TestEngine;                         // Test engine user data
    char                    ContextName[16];                    // Storage for a context name (to facilitate debugging multi-context setups)

    // Inputs
    ImVector<ImGuiInputEvent> InputEventsQueue;                 // Input events which will be trickled/written into IO structure.
    ImVector<ImGuiInputEvent> InputEventsTrail;                 // Past input events processed in NewFrame(). This is to allow domain-specific application to access e.g mouse/pen trail.
    ImGuiMouseSource        InputEventsNextMouseSource;
    ImU32                   InputEventsNextEventId;

    // Windows state
    ImVector<ImGuiWindow*>  Windows;                            // Windows, sorted in display order, back to front
    ImVector<ImGuiWindow*>  WindowsFocusOrder;                  // Root windows, sorted in focus order, back to front.
    ImVector<ImGuiWindow*>  WindowsTempSortBuffer;              // Temporary buffer used in EndFrame() to reorder windows so parents are kept before their child
    ImVector<ImGuiWindowStackData> CurrentWindowStack;
    ImGuiStorage            WindowsById;                        // Map window's ImGuiID to ImGuiWindow*
    int                     WindowsActiveCount;                 // Number of unique windows submitted by frame
    ImVec2                  WindowsHoverPadding;                // Padding around resizable windows for which hovering on counts as hovering the window == ImMax(style.TouchExtraPadding, WINDOWS_HOVER_PADDING).
    ImGuiID                 DebugBreakInWindow;                 // Set to break in Begin() call.
    ImGuiWindow*            CurrentWindow;                      // Window being drawn into
    ImGuiWindow*            HoveredWindow;                      // Window the mouse is hovering. Will typically catch mouse inputs.
    ImGuiWindow*            HoveredWindowUnderMovingWindow;     // Hovered window ignoring MovingWindow. Only set if MovingWindow is set.
    ImGuiWindow*            HoveredWindowBeforeClear;           // Window the mouse is hovering. Filled even with _NoMouse. This is currently useful for multi-context compositors.
    ImGuiWindow*            MovingWindow;                       // Track the window we clicked on (in order to preserve focus). The actual window that is moved is generally MovingWindow->RootWindowDockTree.
    ImGuiWindow*            WheelingWindow;                     // Track the window we started mouse-wheeling on. Until a timer elapse or mouse has moved, generally keep scrolling the same window even if during the course of scrolling the mouse ends up hovering a child window.
    ImVec2                  WheelingWindowRefMousePos;
    int                     WheelingWindowStartFrame;           // This may be set one frame before WheelingWindow is != NULL
    int                     WheelingWindowScrolledFrame;
    float                   WheelingWindowReleaseTimer;
    ImVec2                  WheelingWindowWheelRemainder;
    ImVec2                  WheelingAxisAvg;

    // Item/widgets state and tracking information
    ImGuiID                 DebugDrawIdConflicts;               // Set when we detect multiple items with the same identifier
    ImGuiID                 DebugHookIdInfo;                    // Will call core hooks: DebugHookIdInfo() from GetID functions, used by ID Stack Tool [next HoveredId/ActiveId to not pull in an extra cache-line]
    ImGuiID                 HoveredId;                          // Hovered widget, filled during the frame
    ImGuiID                 HoveredIdPreviousFrame;
    int                     HoveredIdPreviousFrameItemCount;    // Count numbers of items using the same ID as last frame's hovered id
    float                   HoveredIdTimer;                     // Measure contiguous hovering time
    float                   HoveredIdNotActiveTimer;            // Measure contiguous hovering time where the item has not been active
    bool                    HoveredIdAllowOverlap;
    bool                    HoveredIdIsDisabled;                // At least one widget passed the rect test, but has been discarded by disabled flag or popup inhibit. May be true even if HoveredId == 0.
    bool                    ItemUnclipByLog;                    // Disable ItemAdd() clipping, essentially a memory-locality friendly copy of LogEnabled
    ImGuiID                 ActiveId;                           // Active widget
    ImGuiID                 ActiveIdIsAlive;                    // Active widget has been seen this frame (we can't use a bool as the ActiveId may change within the frame)
    float                   ActiveIdTimer;
    bool                    ActiveIdIsJustActivated;            // Set at the time of activation for one frame
    bool                    ActiveIdAllowOverlap;               // Active widget allows another widget to steal active id (generally for overlapping widgets, but not always)
    bool                    ActiveIdNoClearOnFocusLoss;         // Disable losing active id if the active id window gets unfocused.
    bool                    ActiveIdHasBeenPressedBefore;       // Track whether the active id led to a press (this is to allow changing between PressOnClick and PressOnRelease without pressing twice). Used by range_select branch.
    bool                    ActiveIdHasBeenEditedBefore;        // Was the value associated to the widget Edited over the course of the Active state.
    bool                    ActiveIdHasBeenEditedThisFrame;
    bool                    ActiveIdFromShortcut;
    int                     ActiveIdMouseButton : 8;
    ImVec2                  ActiveIdClickOffset;                // Clicked offset from upper-left corner, if applicable (currently only set by ButtonBehavior)
    ImGuiWindow*            ActiveIdWindow;
    ImGuiInputSource        ActiveIdSource;                     // Activating source: ImGuiInputSource_Mouse OR ImGuiInputSource_Keyboard OR ImGuiInputSource_Gamepad
    ImGuiID                 ActiveIdPreviousFrame;
    ImGuiDeactivatedItemData DeactivatedItemData;
    ImGuiDataTypeStorage    ActiveIdValueOnActivation;          // Backup of initial value at the time of activation. ONLY SET BY SPECIFIC WIDGETS: DragXXX and SliderXXX.
    ImGuiID                 LastActiveId;                       // Store the last non-zero ActiveId, useful for animation.
    float                   LastActiveIdTimer;                  // Store the last non-zero ActiveId timer since the beginning of activation, useful for animation.

    // Key/Input Ownership + Shortcut Routing system
    // - The idea is that instead of "eating" a given key, we can link to an owner.
    // - Input query can then read input by specifying ImGuiKeyOwner_Any (== 0), ImGuiKeyOwner_NoOwner (== -1) or a custom ID.
    // - Routing is requested ahead of time for a given chord (Key + Mods) and granted in NewFrame().
    double                  LastKeyModsChangeTime;              // Record the last time key mods changed (affect repeat delay when using shortcut logic)
    double                  LastKeyModsChangeFromNoneTime;      // Record the last time key mods changed away from being 0 (affect repeat delay when using shortcut logic)
    double                  LastKeyboardKeyPressTime;           // Record the last time a keyboard key (ignore mouse/gamepad ones) was pressed.
    ImBitArrayForNamedKeys  KeysMayBeCharInput;                 // Lookup to tell if a key can emit char input, see IsKeyChordPotentiallyCharInput(). sizeof() = 20 bytes
    ImGuiKeyOwnerData       KeysOwnerData[ImGuiKey_NamedKey_COUNT];
    ImGuiKeyRoutingTable    KeysRoutingTable;
    ImU32                   ActiveIdUsingNavDirMask;            // Active widget will want to read those nav move requests (e.g. can activate a button and move away from it)
    bool                    ActiveIdUsingAllKeyboardKeys;       // Active widget will want to read all keyboard keys inputs. (this is a shortcut for not taking ownership of 100+ keys, frequently used by drag operations)
    ImGuiKeyChord           DebugBreakInShortcutRouting;        // Set to break in SetShortcutRouting()/Shortcut() calls.
    //ImU32                 ActiveIdUsingNavInputMask;          // [OBSOLETE] Since (IMGUI_VERSION_NUM >= 18804) : 'g.ActiveIdUsingNavInputMask |= (1 << ImGuiNavInput_Cancel);' becomes --> 'SetKeyOwner(ImGuiKey_Escape, g.ActiveId) and/or SetKeyOwner(ImGuiKey_NavGamepadCancel, g.ActiveId);'

    // Next window/item data
    ImGuiID                 CurrentFocusScopeId;                // Value for currently appending items == g.FocusScopeStack.back(). Not to be mistaken with g.NavFocusScopeId.
    ImGuiItemFlags          CurrentItemFlags;                   // Value for currently appending items == g.ItemFlagsStack.back()
    ImGuiID                 DebugLocateId;                      // Storage for DebugLocateItemOnHover() feature: this is read by ItemAdd() so we keep it in a hot/cached location
    ImGuiNextItemData       NextItemData;                       // Storage for SetNextItem** functions
    ImGuiLastItemData       LastItemData;                       // Storage for last submitted item (setup by ItemAdd)
    ImGuiNextWindowData     NextWindowData;                     // Storage for SetNextWindow** functions
    bool                    DebugShowGroupRects;

    // Shared stacks
    ImGuiCol                        DebugFlashStyleColorIdx;    // (Keep close to ColorStack to share cache line)
    ImVector<ImGuiColorMod>         ColorStack;                 // Stack for PushStyleColor()/PopStyleColor() - inherited by Begin()
    ImVector<ImGuiStyleMod>         StyleVarStack;              // Stack for PushStyleVar()/PopStyleVar() - inherited by Begin()
    ImVector<ImFont*>               FontStack;                  // Stack for PushFont()/PopFont() - inherited by Begin()
    ImVector<ImGuiFocusScopeData>   FocusScopeStack;            // Stack for PushFocusScope()/PopFocusScope() - inherited by BeginChild(), pushed into by Begin()
    ImVector<ImGuiItemFlags>        ItemFlagsStack;             // Stack for PushItemFlag()/PopItemFlag() - inherited by Begin()
    ImVector<ImGuiGroupData>        GroupStack;                 // Stack for BeginGroup()/EndGroup() - not inherited by Begin()
    ImVector<ImGuiPopupData>        OpenPopupStack;             // Which popups are open (persistent)
    ImVector<ImGuiPopupData>        BeginPopupStack;            // Which level of BeginPopup() we are in (reset every frame)
    ImVector<ImGuiTreeNodeStackData>TreeNodeStack;              // Stack for TreeNode()

    // Viewports
    ImVector<ImGuiViewportP*> Viewports;                        // Active viewports (always 1+, and generally 1 unless multi-viewports are enabled). Each viewports hold their copy of ImDrawData.
    ImGuiViewportP*         CurrentViewport;                    // We track changes of viewport (happening in Begin) so we can call Platform_OnChangedViewport()
    ImGuiViewportP*         MouseViewport;
    ImGuiViewportP*         MouseLastHoveredViewport;           // Last known viewport that was hovered by mouse (even if we are not hovering any viewport any more) + honoring the _NoInputs flag.
    ImGuiID                 PlatformLastFocusedViewportId;
    ImGuiPlatformMonitor    FallbackMonitor;                    // Virtual monitor used as fallback if backend doesn't provide monitor information.
    ImRect                  PlatformMonitorsFullWorkRect;       // Bounding box of all platform monitors
    int                     ViewportCreatedCount;               // Unique sequential creation counter (mostly for testing/debugging)
    int                     PlatformWindowsCreatedCount;        // Unique sequential creation counter (mostly for testing/debugging)
    int                     ViewportFocusedStampCount;          // Every time the front-most window changes, we stamp its viewport with an incrementing counter

    // Keyboard/Gamepad Navigation
    bool                    NavCursorVisible;                   // Nav focus cursor/rectangle is visible? We hide it after a mouse click. We show it after a nav move.
    bool                    NavHighlightItemUnderNav;           // Disable mouse hovering highlight. Highlight navigation focused item instead of mouse hovered item.
    //bool                  NavDisableHighlight;                // Old name for !g.NavCursorVisible before 1.91.4 (2024/10/18). OPPOSITE VALUE (g.NavDisableHighlight == !g.NavCursorVisible)
    //bool                  NavDisableMouseHover;               // Old name for g.NavHighlightItemUnderNav before 1.91.1 (2024/10/18) this was called When user starts using keyboard/gamepad, we hide mouse hovering highlight until mouse is touched again.
    bool                    NavMousePosDirty;                   // When set we will update mouse position if io.ConfigNavMoveSetMousePos is set (not enabled by default)
    bool                    NavIdIsAlive;                       // Nav widget has been seen this frame ~~ NavRectRel is valid
    ImGuiID                 NavId;                              // Focused item for navigation
    ImGuiWindow*            NavWindow;                          // Focused window for navigation. Could be called 'FocusedWindow'
    ImGuiID                 NavFocusScopeId;                    // Focused focus scope (e.g. selection code often wants to "clear other items" when landing on an item of the same scope)
    ImGuiNavLayer           NavLayer;                           // Focused layer (main scrolling layer, or menu/title bar layer)
    ImGuiID                 NavActivateId;                      // ~~ (g.ActiveId == 0) && (IsKeyPressed(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate)) ? NavId : 0, also set when calling ActivateItem()
    ImGuiID                 NavActivateDownId;                  // ~~ IsKeyDown(ImGuiKey_Space) || IsKeyDown(ImGuiKey_Enter) || IsKeyDown(ImGuiKey_NavGamepadActivate) ? NavId : 0
    ImGuiID                 NavActivatePressedId;               // ~~ IsKeyPressed(ImGuiKey_Space) || IsKeyPressed(ImGuiKey_Enter) || IsKeyPressed(ImGuiKey_NavGamepadActivate) ? NavId : 0 (no repeat)
    ImGuiActivateFlags      NavActivateFlags;
    ImVector<ImGuiFocusScopeData> NavFocusRoute;                // Reversed copy focus scope stack for NavId (should contains NavFocusScopeId). This essentially follow the window->ParentWindowForFocusRoute chain.
    ImGuiID                 NavHighlightActivatedId;
    float                   NavHighlightActivatedTimer;
    ImGuiID                 NavNextActivateId;                  // Set by ActivateItem(), queued until next frame.
    ImGuiActivateFlags      NavNextActivateFlags;
    ImGuiInputSource        NavInputSource;                     // Keyboard or Gamepad mode? THIS CAN ONLY BE ImGuiInputSource_Keyboard or ImGuiInputSource_Mouse
    ImGuiSelectionUserData  NavLastValidSelectionUserData;      // Last valid data passed to SetNextItemSelectionUser(), or -1. For current window. Not reset when focusing an item that doesn't have selection data.
    ImS8                    NavCursorHideFrames;

    // Navigation: Init & Move Requests
    bool                    NavAnyRequest;                      // ~~ NavMoveRequest || NavInitRequest this is to perform early out in ItemAdd()
    bool                    NavInitRequest;                     // Init request for appearing window to select first item
    bool                    NavInitRequestFromMove;
    ImGuiNavItemData        NavInitResult;                      // Init request result (first item of the window, or one for which SetItemDefaultFocus() was called)
    bool                    NavMoveSubmitted;                   // Move request submitted, will process result on next NewFrame()
    bool                    NavMoveScoringItems;                // Move request submitted, still scoring incoming items
    bool                    NavMoveForwardToNextFrame;
    ImGuiNavMoveFlags       NavMoveFlags;
    ImGuiScrollFlags        NavMoveScrollFlags;
    ImGuiKeyChord           NavMoveKeyMods;
    ImGuiDir                NavMoveDir;                         // Direction of the move request (left/right/up/down)
    ImGuiDir                NavMoveDirForDebug;
    ImGuiDir                NavMoveClipDir;                     // FIXME-NAV: Describe the purpose of this better. Might want to rename?
    ImRect                  NavScoringRect;                     // Rectangle used for scoring, in screen space. Based of window->NavRectRel[], modified for directional navigation scoring.
    ImRect                  NavScoringNoClipRect;               // Some nav operations (such as PageUp/PageDown) enforce a region which clipper will attempt to always keep submitted
    int                     NavScoringDebugCount;               // Metrics for debugging
    int                     NavTabbingDir;                      // Generally -1 or +1, 0 when tabbing without a nav id
    int                     NavTabbingCounter;                  // >0 when counting items for tabbing
    ImGuiNavItemData        NavMoveResultLocal;                 // Best move request candidate within NavWindow
    ImGuiNavItemData        NavMoveResultLocalVisible;          // Best move request candidate within NavWindow that are mostly visible (when using ImGuiNavMoveFlags_AlsoScoreVisibleSet flag)
    ImGuiNavItemData        NavMoveResultOther;                 // Best move request candidate within NavWindow's flattened hierarchy (when using ImGuiWindowFlags_NavFlattened flag)
    ImGuiNavItemData        NavTabbingResultFirst;              // First tabbing request candidate within NavWindow and flattened hierarchy

    // Navigation: record of last move request
    ImGuiID                 NavJustMovedFromFocusScopeId;       // Just navigated from this focus scope id (result of a successfully MoveRequest).
    ImGuiID                 NavJustMovedToId;                   // Just navigated to this id (result of a successfully MoveRequest).
    ImGuiID                 NavJustMovedToFocusScopeId;         // Just navigated to this focus scope id (result of a successfully MoveRequest).
    ImGuiKeyChord           NavJustMovedToKeyMods;
    bool                    NavJustMovedToIsTabbing;            // Copy of ImGuiNavMoveFlags_IsTabbing. Maybe we should store whole flags.
    bool                    NavJustMovedToHasSelectionData;     // Copy of move result's ItemFlags & ImGuiItemFlags_HasSelectionUserData). Maybe we should just store ImGuiNavItemData.

    // Navigation: Windowing (CTRL+TAB for list, or Menu button + keys or directional pads to move/resize)
    ImGuiKeyChord           ConfigNavWindowingKeyNext;          // = ImGuiMod_Ctrl | ImGuiKey_Tab (or ImGuiMod_Super | ImGuiKey_Tab on OS X). For reconfiguration (see #4828)
    ImGuiKeyChord           ConfigNavWindowingKeyPrev;          // = ImGuiMod_Ctrl | ImGuiMod_Shift | ImGuiKey_Tab (or ImGuiMod_Super | ImGuiMod_Shift | ImGuiKey_Tab on OS X)
    ImGuiWindow*            NavWindowingTarget;                 // Target window when doing CTRL+Tab (or Pad Menu + FocusPrev/Next), this window is temporarily displayed top-most!
    ImGuiWindow*            NavWindowingTargetAnim;             // Record of last valid NavWindowingTarget until DimBgRatio and NavWindowingHighlightAlpha becomes 0.0f, so the fade-out can stay on it.
    ImGuiWindow*            NavWindowingListWindow;             // Internal window actually listing the CTRL+Tab contents
    float                   NavWindowingTimer;
    float                   NavWindowingHighlightAlpha;
    bool                    NavWindowingToggleLayer;
    ImGuiKey                NavWindowingToggleKey;
    ImVec2                  NavWindowingAccumDeltaPos;
    ImVec2                  NavWindowingAccumDeltaSize;

    // Render
    float                   DimBgRatio;                         // 0.0..1.0 animation when fading in a dimming background (for modal window and CTRL+TAB list)

    // Drag and Drop
    bool                    DragDropActive;
    bool                    DragDropWithinSource;               // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag source.
    bool                    DragDropWithinTarget;               // Set when within a BeginDragDropXXX/EndDragDropXXX block for a drag target.
    ImGuiDragDropFlags      DragDropSourceFlags;
    int                     DragDropSourceFrameCount;
    int                     DragDropMouseButton;
    ImGuiPayload            DragDropPayload;
    ImRect                  DragDropTargetRect;                 // Store rectangle of current target candidate (we favor small targets when overlapping)
    ImRect                  DragDropTargetClipRect;             // Store ClipRect at the time of item's drawing
    ImGuiID                 DragDropTargetId;
    ImGuiDragDropFlags      DragDropAcceptFlags;
    float                   DragDropAcceptIdCurrRectSurface;    // Target item surface (we resolve overlapping targets by prioritizing the smaller surface)
    ImGuiID                 DragDropAcceptIdCurr;               // Target item id (set at the time of accepting the payload)
    ImGuiID                 DragDropAcceptIdPrev;               // Target item id from previous frame (we need to store this to allow for overlapping drag and drop targets)
    int                     DragDropAcceptFrameCount;           // Last time a target expressed a desire to accept the source
    ImGuiID                 DragDropHoldJustPressedId;          // Set when holding a payload just made ButtonBehavior() return a press.
    ImVector<unsigned char> DragDropPayloadBufHeap;             // We don't expose the ImVector<> directly, ImGuiPayload only holds pointer+size
    unsigned char           DragDropPayloadBufLocal[16];        // Local buffer for small payloads

    // Clipper
    int                             ClipperTempDataStacked;
    ImVector<ImGuiListClipperData>  ClipperTempData;

    // Tables
    ImGuiTable*                     CurrentTable;
    ImGuiID                         DebugBreakInTable;          // Set to break in BeginTable() call.
    int                             TablesTempDataStacked;      // Temporary table data size (because we leave previous instances undestructed, we generally don't use TablesTempData.Size)
    ImVector<ImGuiTableTempData>    TablesTempData;             // Temporary table data (buffers reused/shared across instances, support nesting)
    ImPool<ImGuiTable>              Tables;                     // Persistent table data
    ImVector<float>                 TablesLastTimeActive;       // Last used timestamp of each tables (SOA, for efficient GC)
    ImVector<ImDrawChannel>         DrawChannelsTempMergeBuffer;

    // Tab bars
    ImGuiTabBar*                    CurrentTabBar;
    ImPool<ImGuiTabBar>             TabBars;
    ImVector<ImGuiPtrOrIndex>       CurrentTabBarStack;
    ImVector<ImGuiShrinkWidthItem>  ShrinkWidthBuffer;

    // Multi-Select state
    ImGuiBoxSelectState             BoxSelectState;
    ImGuiMultiSelectTempData*       CurrentMultiSelect;
    int                             MultiSelectTempDataStacked; // Temporary multi-select data size (because we leave previous instances undestructed, we generally don't use MultiSelectTempData.Size)
    ImVector<ImGuiMultiSelectTempData> MultiSelectTempData;
    ImPool<ImGuiMultiSelectState>   MultiSelectStorage;

    // Hover Delay system
    ImGuiID                 HoverItemDelayId;
    ImGuiID                 HoverItemDelayIdPreviousFrame;
    float                   HoverItemDelayTimer;                // Currently used by IsItemHovered()
    float                   HoverItemDelayClearTimer;           // Currently used by IsItemHovered(): grace time before g.TooltipHoverTimer gets cleared.
    ImGuiID                 HoverItemUnlockedStationaryId;      // Mouse has once been stationary on this item. Only reset after departing the item.
    ImGuiID                 HoverWindowUnlockedStationaryId;    // Mouse has once been stationary on this window. Only reset after departing the window.

    // Mouse state
    ImGuiMouseCursor        MouseCursor;
    float                   MouseStationaryTimer;               // Time the mouse has been stationary (with some loose heuristic)
    ImVec2                  MouseLastValidPos;

    // Widget state
    ImGuiInputTextState     InputTextState;
    ImGuiInputTextDeactivatedState InputTextDeactivatedState;
    ImFont                  InputTextPasswordFont;
    ImGuiID                 TempInputId;                        // Temporary text input when CTRL+clicking on a slider, etc.
    ImGuiDataTypeStorage    DataTypeZeroValue;                  // 0 for all data types
    int                     BeginMenuDepth;
    int                     BeginComboDepth;
    ImGuiColorEditFlags     ColorEditOptions;                   // Store user options for color edit widgets
    ImGuiID                 ColorEditCurrentID;                 // Set temporarily while inside of the parent-most ColorEdit4/ColorPicker4 (because they call each others).
    ImGuiID                 ColorEditSavedID;                   // ID we are saving/restoring HS for
    float                   ColorEditSavedHue;                  // Backup of last Hue associated to LastColor, so we can restore Hue in lossy RGB<>HSV round trips
    float                   ColorEditSavedSat;                  // Backup of last Saturation associated to LastColor, so we can restore Saturation in lossy RGB<>HSV round trips
    ImU32                   ColorEditSavedColor;                // RGB value with alpha set to 0.
    ImVec4                  ColorPickerRef;                     // Initial/reference color at the time of opening the color picker.
    ImGuiComboPreviewData   ComboPreviewData;
    ImRect                  WindowResizeBorderExpectedRect;     // Expected border rect, switch to relative edit if moving
    bool                    WindowResizeRelativeMode;
    short                   ScrollbarSeekMode;                  // 0: scroll to clicked location, -1/+1: prev/next page.
    float                   ScrollbarClickDeltaToGrabCenter;    // When scrolling to mouse location: distance between mouse and center of grab box, normalized in parent space.
    float                   SliderGrabClickOffset;
    float                   SliderCurrentAccum;                 // Accumulated slider delta when using navigation controls.
    bool                    SliderCurrentAccumDirty;            // Has the accumulated slider delta changed since last time we tried to apply it?
    bool                    DragCurrentAccumDirty;
    float                   DragCurrentAccum;                   // Accumulator for dragging modification. Always high-precision, not rounded by end-user precision settings
    float                   DragSpeedDefaultRatio;              // If speed == 0.0f, uses (max-min) * DragSpeedDefaultRatio
    float                   DisabledAlphaBackup;                // Backup for style.Alpha for BeginDisabled()
    short                   DisabledStackSize;
    short                   TooltipOverrideCount;
    ImGuiWindow*            TooltipPreviousWindow;              // Window of last tooltip submitted during the frame
    ImVector<char>          ClipboardHandlerData;               // If no custom clipboard handler is defined
    ImVector<ImGuiID>       MenusIdSubmittedThisFrame;          // A list of menu IDs that were rendered at least once
    ImGuiTypingSelectState  TypingSelectState;                  // State for GetTypingSelectRequest()

    // Platform support
    ImGuiPlatformImeData    PlatformImeData;                    // Data updated by current frame
    ImGuiPlatformImeData    PlatformImeDataPrev;                // Previous frame data. When changed we call the platform_io.Platform_SetImeDataFn() handler.
    ImGuiID                 PlatformImeViewport;

    // Extensions
    // FIXME: We could provide an API to register one slot in an array held in ImGuiContext?
    ImGuiDockContext        DockContext;
    void                    (*DockNodeWindowMenuHandler)(ImGuiContext* ctx, ImGuiDockNode* node, ImGuiTabBar* tab_bar);

    // Settings
    bool                    SettingsLoaded;
    float                   SettingsDirtyTimer;                 // Save .ini Settings to memory when time reaches zero
    ImGuiTextBuffer         SettingsIniData;                    // In memory .ini settings
    ImVector<ImGuiSettingsHandler>      SettingsHandlers;       // List of .ini settings handlers
    ImChunkStream<ImGuiWindowSettings>  SettingsWindows;        // ImGuiWindow .ini settings entries
    ImChunkStream<ImGuiTableSettings>   SettingsTables;         // ImGuiTable .ini settings entries
    ImVector<ImGuiContextHook>          Hooks;                  // Hooks for extensions (e.g. test engine)
    ImGuiID                             HookIdNext;             // Next available HookId

    // Localization
    const char*             LocalizationTable[ImGuiLocKey_COUNT];

    // Capture/Logging
    bool                    LogEnabled;                         // Currently capturing
    ImGuiLogFlags           LogFlags;                           // Capture flags/type
    ImGuiWindow*            LogWindow;
    ImFileHandle            LogFile;                            // If != NULL log to stdout/ file
    ImGuiTextBuffer         LogBuffer;                          // Accumulation buffer when log to clipboard. This is pointer so our GImGui static constructor doesn't call heap allocators.
    const char*             LogNextPrefix;
    const char*             LogNextSuffix;
    float                   LogLinePosY;
    bool                    LogLineFirstItem;
    int                     LogDepthRef;
    int                     LogDepthToExpand;
    int                     LogDepthToExpandDefault;            // Default/stored value for LogDepthMaxExpand if not specified in the LogXXX function call.

    // Error Handling
    ImGuiErrorCallback      ErrorCallback;                      // = NULL. May be exposed in public API eventually.
    void*                   ErrorCallbackUserData;              // = NULL
    ImVec2                  ErrorTooltipLockedPos;
    bool                    ErrorFirst;
    int                     ErrorCountCurrentFrame;             // [Internal] Number of errors submitted this frame.
    ImGuiErrorRecoveryState StackSizesInNewFrame;               // [Internal]
    ImGuiErrorRecoveryState*StackSizesInBeginForCurrentWindow;  // [Internal]

    // Debug Tools
    // (some of the highly frequently used data are interleaved in other structures above: DebugBreakXXX fields, DebugHookIdInfo, DebugLocateId etc.)
    int                     DebugDrawIdConflictsCount;          // Locked count (preserved when holding CTRL)
    ImGuiDebugLogFlags      DebugLogFlags;
    ImGuiTextBuffer         DebugLogBuf;
    ImGuiTextIndex          DebugLogIndex;
    int                     DebugLogSkippedErrors;
    ImGuiDebugLogFlags      DebugLogAutoDisableFlags;
    ImU8                    DebugLogAutoDisableFrames;
    ImU8                    DebugLocateFrames;                  // For DebugLocateItemOnHover(). This is used together with DebugLocateId which is in a hot/cached spot above.
    bool                    DebugBreakInLocateId;               // Debug break in ItemAdd() call for g.DebugLocateId.
    ImGuiKeyChord           DebugBreakKeyChord;                 // = ImGuiKey_Pause
    ImS8                    DebugBeginReturnValueCullDepth;     // Cycle between 0..9 then wrap around.
    bool                    DebugItemPickerActive;              // Item picker is active (started with DebugStartItemPicker())
    ImU8                    DebugItemPickerMouseButton;
    ImGuiID                 DebugItemPickerBreakId;             // Will call IM_DEBUG_BREAK() when encountering this ID
    float                   DebugFlashStyleColorTime;
    ImVec4                  DebugFlashStyleColorBackup;
    ImGuiMetricsConfig      DebugMetricsConfig;
    ImGuiIDStackTool        DebugIDStackTool;
    ImGuiDebugAllocInfo     DebugAllocInfo;
    ImGuiDockNode*          DebugHoveredDockNode;               // Hovered dock node.

    // Misc
    float                   FramerateSecPerFrame[60];           // Calculate estimate of framerate for user over the last 60 frames..
    int                     FramerateSecPerFrameIdx;
    int                     FramerateSecPerFrameCount;
    float                   FramerateSecPerFrameAccum;
    int                     WantCaptureMouseNextFrame;          // Explicit capture override via SetNextFrameWantCaptureMouse()/SetNextFrameWantCaptureKeyboard(). Default to -1.
    int                     WantCaptureKeyboardNextFrame;       // "
    int                     WantTextInputNextFrame;
    ImVector<char>          TempBuffer;                         // Temporary text buffer
    char                    TempKeychordName[64];

    ImGuiContext(ImFontAtlas* shared_font_atlas);
};

//-----------------------------------------------------------------------------
// [SECTION] ImGuiWindowTempData, ImGuiWindow
//-----------------------------------------------------------------------------

// Transient per-window data, reset at the beginning of the frame. This used to be called ImGuiDrawContext, hence the DC variable name in ImGuiWindow.
// (That's theory, in practice the delimitation between ImGuiWindow and ImGuiWindowTempData is quite tenuous and could be reconsidered..)
// (This doesn't need a constructor because we zero-clear it as part of ImGuiWindow and all frame-temporary data are setup on Begin)
struct  ImGuiWindowTempData
{
    // Layout
    ImVec2                  CursorPos;              // Current emitting position, in absolute coordinates.
    ImVec2                  CursorPosPrevLine;
    ImVec2                  CursorStartPos;         // Initial position after Begin(), generally ~ window position + WindowPadding.
    ImVec2                  CursorMaxPos;           // Used to implicitly calculate ContentSize at the beginning of next frame, for scrolling range and auto-resize. Always growing during the frame.
    ImVec2                  IdealMaxPos;            // Used to implicitly calculate ContentSizeIdeal at the beginning of next frame, for auto-resize only. Always growing during the frame.
    ImVec2                  CurrLineSize;
    ImVec2                  PrevLineSize;
    float                   CurrLineTextBaseOffset; // Baseline offset (0.0f by default on a new line, generally == style.FramePadding.y when a framed item has been added).
    float                   PrevLineTextBaseOffset;
    bool                    IsSameLine;
    bool                    IsSetPos;
    ImVec1                  Indent;                 // Indentation / start position from left of window (increased by TreePush/TreePop, etc.)
    ImVec1                  ColumnsOffset;          // Offset to the current column (if ColumnsCurrent > 0). FIXME: This and the above should be a stack to allow use cases like Tree->Column->Tree. Need revamp columns API.
    ImVec1                  GroupOffset;
    ImVec2                  CursorStartPosLossyness;// Record the loss of precision of CursorStartPos due to really large scrolling amount. This is used by clipper to compensate and fix the most common use case of large scroll area.

    // Keyboard/Gamepad navigation
    ImGuiNavLayer           NavLayerCurrent;        // Current layer, 0..31 (we currently only use 0..1)
    short                   NavLayersActiveMask;    // Which layers have been written to (result from previous frame)
    short                   NavLayersActiveMaskNext;// Which layers have been written to (accumulator for current frame)
    bool                    NavIsScrollPushableX;   // Set when current work location may be scrolled horizontally when moving left / right. This is generally always true UNLESS within a column.
    bool                    NavHideHighlightOneFrame;
    bool                    NavWindowHasScrollY;    // Set per window when scrolling can be used (== ScrollMax.y > 0.0f)

    // Miscellaneous
    bool                    MenuBarAppending;       // FIXME: Remove this
    ImVec2                  MenuBarOffset;          // MenuBarOffset.x is sort of equivalent of a per-layer CursorPos.x, saved/restored as we switch to the menu bar. The only situation when MenuBarOffset.y is > 0 if when (SafeAreaPadding.y > FramePadding.y), often used on TVs.
    ImGuiMenuColumns        MenuColumns;            // Simplified columns storage for menu items measurement
    int                     TreeDepth;              // Current tree depth.
    ImU32                   TreeHasStackDataDepthMask; // Store whether given depth has ImGuiTreeNodeStackData data. Could be turned into a ImU64 if necessary.
    ImVector<ImGuiWindow*>  ChildWindows;
    ImGuiStorage*           StateStorage;           // Current persistent per-window storage (store e.g. tree node open/close state)
    ImGuiOldColumns*        CurrentColumns;         // Current columns set
    int                     CurrentTableIdx;        // Current table index (into g.Tables)
    ImGuiLayoutType         LayoutType;
    ImGuiLayoutType         ParentLayoutType;       // Layout type of parent window at the time of Begin()
    ImU32                   ModalDimBgColor;

    // Status flags
    ImGuiItemStatusFlags    WindowItemStatusFlags;
    ImGuiItemStatusFlags    ChildItemStatusFlags;
    ImGuiItemStatusFlags    DockTabItemStatusFlags;
    ImRect                  DockTabItemRect;

    // Local parameters stacks
    // We store the current settings outside of the vectors to increase memory locality (reduce cache misses). The vectors are rarely modified. Also it allows us to not heap allocate for short-lived windows which are not using those settings.
    float                   ItemWidth;              // Current item width (>0.0: width in pixels, <0.0: align xx pixels to the right of window).
    float                   TextWrapPos;            // Current text wrap pos.
    ImVector<float>         ItemWidthStack;         // Store item widths to restore (attention: .back() is not == ItemWidth)
    ImVector<float>         TextWrapPosStack;       // Store text wrap pos to restore (attention: .back() is not == TextWrapPos)
};

// Storage for one window
struct  ImGuiWindow
{
    ImGuiContext*           Ctx;                                // Parent UI context (needs to be set explicitly by parent).
    char*                   Name;                               // Window name, owned by the window.
    ImGuiID                 ID;                                 // == ImHashStr(Name)
    ImGuiWindowFlags        Flags, FlagsPreviousFrame;          // See enum ImGuiWindowFlags_
    ImGuiChildFlags         ChildFlags;                         // Set when window is a child window. See enum ImGuiChildFlags_
    ImGuiWindowClass        WindowClass;                        // Advanced users only. Set with SetNextWindowClass()
    ImGuiViewportP*         Viewport;                           // Always set in Begin(). Inactive windows may have a NULL value here if their viewport was discarded.
    ImGuiID                 ViewportId;                         // We backup the viewport id (since the viewport may disappear or never be created if the window is inactive)
    ImVec2                  ViewportPos;                        // We backup the viewport position (since the viewport may disappear or never be created if the window is inactive)
    int                     ViewportAllowPlatformMonitorExtend; // Reset to -1 every frame (index is guaranteed to be valid between NewFrame..EndFrame), only used in the Appearing frame of a tooltip/popup to enforce clamping to a given monitor
    ImVec2                  Pos;                                // Position (always rounded-up to nearest pixel)
    ImVec2                  Size;                               // Current size (==SizeFull or collapsed title bar size)
    ImVec2                  SizeFull;                           // Size when non collapsed
    ImVec2                  ContentSize;                        // Size of contents/scrollable client area (calculated from the extents reach of the cursor) from previous frame. Does not include window decoration or window padding.
    ImVec2                  ContentSizeIdeal;
    ImVec2                  ContentSizeExplicit;                // Size of contents/scrollable client area explicitly request by the user via SetNextWindowContentSize().
    ImVec2                  WindowPadding;                      // Window padding at the time of Begin().
    float                   WindowRounding;                     // Window rounding at the time of Begin(). May be clamped lower to avoid rendering artifacts with title bar, menu bar etc.
    float                   WindowBorderSize;                   // Window border size at the time of Begin().
    float                   TitleBarHeight, MenuBarHeight;      // Note that those used to be function before 2024/05/28. If you have old code calling TitleBarHeight() you can change it to TitleBarHeight.
    float                   DecoOuterSizeX1, DecoOuterSizeY1;   // Left/Up offsets. Sum of non-scrolling outer decorations (X1 generally == 0.0f. Y1 generally = TitleBarHeight + MenuBarHeight). Locked during Begin().
    float                   DecoOuterSizeX2, DecoOuterSizeY2;   // Right/Down offsets (X2 generally == ScrollbarSize.x, Y2 == ScrollbarSizes.y).
    float                   DecoInnerSizeX1, DecoInnerSizeY1;   // Applied AFTER/OVER InnerRect. Specialized for Tables as they use specialized form of clipping and frozen rows/columns are inside InnerRect (and not part of regular decoration sizes).
    int                     NameBufLen;                         // Size of buffer storing Name. May be larger than strlen(Name)!
    ImGuiID                 MoveId;                             // == window->GetID("#MOVE")
    ImGuiID                 TabId;                              // == window->GetID("#TAB")
    ImGuiID                 ChildId;                            // ID of corresponding item in parent window (for navigation to return from child window to parent window)
    ImGuiID                 PopupId;                            // ID in the popup stack when this window is used as a popup/menu (because we use generic Name/ID for recycling)
    ImVec2                  Scroll;
    ImVec2                  ScrollMax;
    ImVec2                  ScrollTarget;                       // target scroll position. stored as cursor position with scrolling canceled out, so the highest point is always 0.0f. (FLT_MAX for no change)
    ImVec2                  ScrollTargetCenterRatio;            // 0.0f = scroll so that target position is at top, 0.5f = scroll so that target position is centered
    ImVec2                  ScrollTargetEdgeSnapDist;           // 0.0f = no snapping, >0.0f snapping threshold
    ImVec2                  ScrollbarSizes;                     // Size taken by each scrollbars on their smaller axis. Pay attention! ScrollbarSizes.x == width of the vertical scrollbar, ScrollbarSizes.y = height of the horizontal scrollbar.
    bool                    ScrollbarX, ScrollbarY;             // Are scrollbars visible?
    bool                    ViewportOwned;
    bool                    Active;                             // Set to true on Begin(), unless Collapsed
    bool                    WasActive;
    bool                    WriteAccessed;                      // Set to true when any widget access the current window
    bool                    Collapsed;                          // Set when collapsing window to become only title-bar
    bool                    WantCollapseToggle;
    bool                    SkipItems;                          // Set when items can safely be all clipped (e.g. window not visible or collapsed)
    bool                    SkipRefresh;                        // [EXPERIMENTAL] Reuse previous frame drawn contents, Begin() returns false.
    bool                    Appearing;                          // Set during the frame where the window is appearing (or re-appearing)
    bool                    Hidden;                             // Do not display (== HiddenFrames*** > 0)
    bool                    IsFallbackWindow;                   // Set on the "Debug##Default" window.
    bool                    IsExplicitChild;                    // Set when passed _ChildWindow, left to false by BeginDocked()
    bool                    HasCloseButton;                     // Set when the window has a close button (p_open != NULL)
    signed char             ResizeBorderHovered;                // Current border being hovered for resize (-1: none, otherwise 0-3)
    signed char             ResizeBorderHeld;                   // Current border being held for resize (-1: none, otherwise 0-3)
    short                   BeginCount;                         // Number of Begin() during the current frame (generally 0 or 1, 1+ if appending via multiple Begin/End pairs)
    short                   BeginCountPreviousFrame;            // Number of Begin() during the previous frame
    short                   BeginOrderWithinParent;             // Begin() order within immediate parent window, if we are a child window. Otherwise 0.
    short                   BeginOrderWithinContext;            // Begin() order within entire imgui context. This is mostly used for debugging submission order related issues.
    short                   FocusOrder;                         // Order within WindowsFocusOrder[], altered when windows are focused.
    ImS8                    AutoFitFramesX, AutoFitFramesY;
    bool                    AutoFitOnlyGrows;
    ImGuiDir                AutoPosLastDirection;
    ImS8                    HiddenFramesCanSkipItems;           // Hide the window for N frames
    ImS8                    HiddenFramesCannotSkipItems;        // Hide the window for N frames while allowing items to be submitted so we can measure their size
    ImS8                    HiddenFramesForRenderOnly;          // Hide the window until frame N at Render() time only
    ImS8                    DisableInputsFrames;                // Disable window interactions for N frames
    ImGuiCond               SetWindowPosAllowFlags : 8;         // store acceptable condition flags for SetNextWindowPos() use.
    ImGuiCond               SetWindowSizeAllowFlags : 8;        // store acceptable condition flags for SetNextWindowSize() use.
    ImGuiCond               SetWindowCollapsedAllowFlags : 8;   // store acceptable condition flags for SetNextWindowCollapsed() use.
    ImGuiCond               SetWindowDockAllowFlags : 8;        // store acceptable condition flags for SetNextWindowDock() use.
    ImVec2                  SetWindowPosVal;                    // store window position when using a non-zero Pivot (position set needs to be processed when we know the window size)
    ImVec2                  SetWindowPosPivot;                  // store window pivot for positioning. ImVec2(0, 0) when positioning from top-left corner; ImVec2(0.5f, 0.5f) for centering; ImVec2(1, 1) for bottom right.

    ImVector<ImGuiID>       IDStack;                            // ID stack. ID are hashes seeded with the value at the top of the stack. (In theory this should be in the TempData structure)
    ImGuiWindowTempData     DC;                                 // Temporary per-window data, reset at the beginning of the frame. This used to be called ImGuiDrawContext, hence the "DC" variable name.

    // The best way to understand what those rectangles are is to use the 'Metrics->Tools->Show Windows Rectangles' viewer.
    // The main 'OuterRect', omitted as a field, is window->Rect().
    ImRect                  OuterRectClipped;                   // == Window->Rect() just after setup in Begin(). == window->Rect() for root window.
    ImRect                  InnerRect;                          // Inner rectangle (omit title bar, menu bar, scroll bar)
    ImRect                  InnerClipRect;                      // == InnerRect shrunk by WindowPadding*0.5f on each side, clipped within viewport or parent clip rect.
    ImRect                  WorkRect;                           // Initially covers the whole scrolling region. Reduced by containers e.g columns/tables when active. Shrunk by WindowPadding*1.0f on each side. This is meant to replace ContentRegionRect over time (from 1.71+ onward).
    ImRect                  ParentWorkRect;                     // Backup of WorkRect before entering a container such as columns/tables. Used by e.g. SpanAllColumns functions to easily access. Stacked containers are responsible for maintaining this. // FIXME-WORKRECT: Could be a stack?
    ImRect                  ClipRect;                           // Current clipping/scissoring rectangle, evolve as we are using PushClipRect(), etc. == DrawList->clip_rect_stack.back().
    ImRect                  ContentRegionRect;                  // FIXME: This is currently confusing/misleading. It is essentially WorkRect but not handling of scrolling. We currently rely on it as right/bottom aligned sizing operation need some size to rely on.
    ImVec2ih                HitTestHoleSize;                    // Define an optional rectangular hole where mouse will pass-through the window.
    ImVec2ih                HitTestHoleOffset;

    int                     LastFrameActive;                    // Last frame number the window was Active.
    int                     LastFrameJustFocused;               // Last frame number the window was made Focused.
    float                   LastTimeActive;                     // Last timestamp the window was Active (using float as we don't need high precision there)
    float                   ItemWidthDefault;
    ImGuiStorage            StateStorage;
    ImVector<ImGuiOldColumns> ColumnsStorage;
    float                   FontWindowScale;                    // User scale multiplier per-window, via SetWindowFontScale()
    float                   FontWindowScaleParents;
    float                   FontDpiScale;
    float                   FontRefSize;                        // This is a copy of window->CalcFontSize() at the time of Begin(), trying to phase out CalcFontSize() especially as it may be called on non-current window.
    int                     SettingsOffset;                     // Offset into SettingsWindows[] (offsets are always valid as we only grow the array from the back)

    ImDrawList*             DrawList;                           // == &DrawListInst (for backward compatibility reason with code using imgui_internal.h we keep this a pointer)
    ImDrawList              DrawListInst;
    ImGuiWindow*            ParentWindow;                       // If we are a child _or_ popup _or_ docked window, this is pointing to our parent. Otherwise NULL.
    ImGuiWindow*            ParentWindowInBeginStack;
    ImGuiWindow*            RootWindow;                         // Point to ourself or first ancestor that is not a child window. Doesn't cross through popups/dock nodes.
    ImGuiWindow*            RootWindowPopupTree;                // Point to ourself or first ancestor that is not a child window. Cross through popups parent<>child.
    ImGuiWindow*            RootWindowDockTree;                 // Point to ourself or first ancestor that is not a child window. Cross through dock nodes.
    ImGuiWindow*            RootWindowForTitleBarHighlight;     // Point to ourself or first ancestor which will display TitleBgActive color when this window is active.
    ImGuiWindow*            RootWindowForNav;                   // Point to ourself or first ancestor which doesn't have the NavFlattened flag.
    ImGuiWindow*            ParentWindowForFocusRoute;          // Set to manual link a window to its logical parent so that Shortcut() chain are honoerd (e.g. Tool linked to Document)

    ImGuiWindow*            NavLastChildNavWindow;              // When going to the menu bar, we remember the child window we came from. (This could probably be made implicit if we kept g.Windows sorted by last focused including child window.)
    ImGuiID                 NavLastIds[ImGuiNavLayer_COUNT];    // Last known NavId for this window, per layer (0/1)
    ImRect                  NavRectRel[ImGuiNavLayer_COUNT];    // Reference rectangle, in window relative space
    ImVec2                  NavPreferredScoringPosRel[ImGuiNavLayer_COUNT]; // Preferred X/Y position updated when moving on a given axis, reset to FLT_MAX.
    ImGuiID                 NavRootFocusScopeId;                // Focus Scope ID at the time of Begin()

    int                     MemoryDrawListIdxCapacity;          // Backup of last idx/vtx count, so when waking up the window we can preallocate and avoid iterative alloc/copy
    int                     MemoryDrawListVtxCapacity;
    bool                    MemoryCompacted;                    // Set when window extraneous data have been garbage collected

    // Docking
    bool                    DockIsActive        :1;             // When docking artifacts are actually visible. When this is set, DockNode is guaranteed to be != NULL. ~~ (DockNode != NULL) && (DockNode->Windows.Size > 1).
    bool                    DockNodeIsVisible   :1;
    bool                    DockTabIsVisible    :1;             // Is our window visible this frame? ~~ is the corresponding tab selected?
    bool                    DockTabWantClose    :1;
    short                   DockOrder;                          // Order of the last time the window was visible within its DockNode. This is used to reorder windows that are reappearing on the same frame. Same value between windows that were active and windows that were none are possible.
    ImGuiWindowDockStyle    DockStyle;
    ImGuiDockNode*          DockNode;                           // Which node are we docked into. Important: Prefer testing DockIsActive in many cases as this will still be set when the dock node is hidden.
    ImGuiDockNode*          DockNodeAsHost;                     // Which node are we owning (for parent windows)
    ImGuiID                 DockId;                             // Backup of last valid DockNode->ID, so single window remember their dock node id even when they are not bound any more

public:
    ImGuiWindow(ImGuiContext* context, const char* name);
    ~ImGuiWindow();

    ImGuiID     GetID(const char* str, const char* str_end = ((void *)0));
    ImGuiID     GetID(const void* ptr);
    ImGuiID     GetID(int n);
    ImGuiID     GetIDFromPos(const ImVec2& p_abs);
    ImGuiID     GetIDFromRectangle(const ImRect& r_abs);

    // We don't use g.FontSize because the window may be != g.CurrentWindow.
    ImRect      Rect() const            { return ImRect(Pos.x, Pos.y, Pos.x + Size.x, Pos.y + Size.y); }
    float       CalcFontSize() const    { ImGuiContext& g = *Ctx; return g.FontBaseSize * FontWindowScale * FontDpiScale * FontWindowScaleParents; }
    ImRect      TitleBarRect() const    { return ImRect(Pos, ImVec2(Pos.x + SizeFull.x, Pos.y + TitleBarHeight)); }
    ImRect      MenuBarRect() const     { float y1 = Pos.y + TitleBarHeight; return ImRect(Pos.x, y1, Pos.x + SizeFull.x, y1 + MenuBarHeight); }
};

//-----------------------------------------------------------------------------
// [SECTION] Tab bar, Tab item support
//-----------------------------------------------------------------------------

// Extend ImGuiTabBarFlags_
enum ImGuiTabBarFlagsPrivate_
{
    ImGuiTabBarFlags_DockNode                   = 1 << 20,  // Part of a dock node [we don't use this in the master branch but it facilitate branch syncing to keep this around]
    ImGuiTabBarFlags_IsFocused                  = 1 << 21,
    ImGuiTabBarFlags_SaveSettings               = 1 << 22,  // FIXME: Settings are handled by the docking system, this only request the tab bar to mark settings dirty when reordering tabs
};

// Extend ImGuiTabItemFlags_
enum ImGuiTabItemFlagsPrivate_
{
    ImGuiTabItemFlags_SectionMask_              = ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_Trailing,
    ImGuiTabItemFlags_NoCloseButton             = 1 << 20,  // Track whether p_open was set or not (we'll need this info on the next frame to recompute ContentWidth during layout)
    ImGuiTabItemFlags_Button                    = 1 << 21,  // Used by TabItemButton, change the tab item behavior to mimic a button
    ImGuiTabItemFlags_Invisible                 = 1 << 22,  // To reserve space e.g. with ImGuiTabItemFlags_Leading
    ImGuiTabItemFlags_Unsorted                  = 1 << 23,  // [Docking] Trailing tabs with the _Unsorted flag will be sorted based on the DockOrder of their Window.
};

// Storage for one active tab item (sizeof() 48 bytes)
struct ImGuiTabItem
{
    ImGuiID             ID;
    ImGuiTabItemFlags   Flags;
    ImGuiWindow*        Window;                 // When TabItem is part of a DockNode's TabBar, we hold on to a window.
    int                 LastFrameVisible;
    int                 LastFrameSelected;      // This allows us to infer an ordered list of the last activated tabs with little maintenance
    float               Offset;                 // Position relative to beginning of tab
    float               Width;                  // Width currently displayed
    float               ContentWidth;           // Width of label, stored during BeginTabItem() call
    float               RequestedWidth;         // Width optionally requested by caller, -1.0f is unused
    ImS32               NameOffset;             // When Window==NULL, offset to name within parent ImGuiTabBar::TabsNames
    ImS16               BeginOrder;             // BeginTabItem() order, used to re-order tabs after toggling ImGuiTabBarFlags_Reorderable
    ImS16               IndexDuringLayout;      // Index only used during TabBarLayout(). Tabs gets reordered so 'Tabs[n].IndexDuringLayout == n' but may mismatch during additions.
    bool                WantClose;              // Marked as closed by SetTabItemClosed()

    ImGuiTabItem()      { memset(this, 0, sizeof(*this)); LastFrameVisible = LastFrameSelected = -1; RequestedWidth = -1.0f; NameOffset = -1; BeginOrder = IndexDuringLayout = -1; }
};

// Storage for a tab bar (sizeof() 160 bytes)
struct  ImGuiTabBar
{
    ImGuiWindow*        Window;
    ImVector<ImGuiTabItem> Tabs;
    ImGuiTabBarFlags    Flags;
    ImGuiID             ID;                     // Zero for tab-bars used by docking
    ImGuiID             SelectedTabId;          // Selected tab/window
    ImGuiID             NextSelectedTabId;      // Next selected tab/window. Will also trigger a scrolling animation
    ImGuiID             VisibleTabId;           // Can occasionally be != SelectedTabId (e.g. when previewing contents for CTRL+TAB preview)
    int                 CurrFrameVisible;
    int                 PrevFrameVisible;
    ImRect              BarRect;
    float               CurrTabsContentsHeight;
    float               PrevTabsContentsHeight; // Record the height of contents submitted below the tab bar
    float               WidthAllTabs;           // Actual width of all tabs (locked during layout)
    float               WidthAllTabsIdeal;      // Ideal width if all tabs were visible and not clipped
    float               ScrollingAnim;
    float               ScrollingTarget;
    float               ScrollingTargetDistToVisibility;
    float               ScrollingSpeed;
    float               ScrollingRectMinX;
    float               ScrollingRectMaxX;
    float               SeparatorMinX;
    float               SeparatorMaxX;
    ImGuiID             ReorderRequestTabId;
    ImS16               ReorderRequestOffset;
    ImS8                BeginCount;
    bool                WantLayout;
    bool                VisibleTabWasSubmitted;
    bool                TabsAddedNew;           // Set to true when a new tab item or button has been added to the tab bar during last frame
    ImS16               TabsActiveCount;        // Number of tabs submitted this frame.
    ImS16               LastTabItemIdx;         // Index of last BeginTabItem() tab for use by EndTabItem()
    float               ItemSpacingY;
    ImVec2              FramePadding;           // style.FramePadding locked at the time of BeginTabBar()
    ImVec2              BackupCursorPos;
    ImGuiTextBuffer     TabsNames;              // For non-docking tab bar we re-append names in a contiguous buffer.

    ImGuiTabBar();
};

//-----------------------------------------------------------------------------
// [SECTION] Table support
//-----------------------------------------------------------------------------




// Our current column maximum is 64 but we may raise that in the future.
typedef ImS16 ImGuiTableColumnIdx;
typedef ImU16 ImGuiTableDrawChannelIdx;

// [Internal] sizeof() ~ 112
// We use the terminology "Enabled" to refer to a column that is not Hidden by user/api.
// We use the terminology "Clipped" to refer to a column that is out of sight because of scrolling/clipping.
// This is in contrast with some user-facing api such as IsItemVisible() / IsRectVisible() which use "Visible" to mean "not clipped".
struct ImGuiTableColumn
{
    ImGuiTableColumnFlags   Flags;                          // Flags after some patching (not directly same as provided by user). See ImGuiTableColumnFlags_
    float                   WidthGiven;                     // Final/actual width visible == (MaxX - MinX), locked in TableUpdateLayout(). May be > WidthRequest to honor minimum width, may be < WidthRequest to honor shrinking columns down in tight space.
    float                   MinX;                           // Absolute positions
    float                   MaxX;
    float                   WidthRequest;                   // Master width absolute value when !(Flags & _WidthStretch). When Stretch this is derived every frame from StretchWeight in TableUpdateLayout()
    float                   WidthAuto;                      // Automatic width
    float                   WidthMax;                       // Maximum width (FIXME: overwritten by each instance)
    float                   StretchWeight;                  // Master width weight when (Flags & _WidthStretch). Often around ~1.0f initially.
    float                   InitStretchWeightOrWidth;       // Value passed to TableSetupColumn(). For Width it is a content width (_without padding_).
    ImRect                  ClipRect;                       // Clipping rectangle for the column
    ImGuiID                 UserID;                         // Optional, value passed to TableSetupColumn()
    float                   WorkMinX;                       // Contents region min ~(MinX + CellPaddingX + CellSpacingX1) == cursor start position when entering column
    float                   WorkMaxX;                       // Contents region max ~(MaxX - CellPaddingX - CellSpacingX2)
    float                   ItemWidth;                      // Current item width for the column, preserved across rows
    float                   ContentMaxXFrozen;              // Contents maximum position for frozen rows (apart from headers), from which we can infer content width.
    float                   ContentMaxXUnfrozen;
    float                   ContentMaxXHeadersUsed;         // Contents maximum position for headers rows (regardless of freezing). TableHeader() automatically softclip itself + report ideal desired size, to avoid creating extraneous draw calls
    float                   ContentMaxXHeadersIdeal;
    ImS16                   NameOffset;                     // Offset into parent ColumnsNames[]
    ImGuiTableColumnIdx     DisplayOrder;                   // Index within Table's IndexToDisplayOrder[] (column may be reordered by users)
    ImGuiTableColumnIdx     IndexWithinEnabledSet;          // Index within enabled/visible set (<= IndexToDisplayOrder)
    ImGuiTableColumnIdx     PrevEnabledColumn;              // Index of prev enabled/visible column within Columns[], -1 if first enabled/visible column
    ImGuiTableColumnIdx     NextEnabledColumn;              // Index of next enabled/visible column within Columns[], -1 if last enabled/visible column
    ImGuiTableColumnIdx     SortOrder;                      // Index of this column within sort specs, -1 if not sorting on this column, 0 for single-sort, may be >0 on multi-sort
    ImGuiTableDrawChannelIdx DrawChannelCurrent;            // Index within DrawSplitter.Channels[]
    ImGuiTableDrawChannelIdx DrawChannelFrozen;             // Draw channels for frozen rows (often headers)
    ImGuiTableDrawChannelIdx DrawChannelUnfrozen;           // Draw channels for unfrozen rows
    bool                    IsEnabled;                      // IsUserEnabled && (Flags & ImGuiTableColumnFlags_Disabled) == 0
    bool                    IsUserEnabled;                  // Is the column not marked Hidden by the user? (unrelated to being off view, e.g. clipped by scrolling).
    bool                    IsUserEnabledNextFrame;
    bool                    IsVisibleX;                     // Is actually in view (e.g. overlapping the host window clipping rectangle, not scrolled).
    bool                    IsVisibleY;
    bool                    IsRequestOutput;                // Return value for TableSetColumnIndex() / TableNextColumn(): whether we request user to output contents or not.
    bool                    IsSkipItems;                    // Do we want item submissions to this column to be completely ignored (no layout will happen).
    bool                    IsPreserveWidthAuto;
    ImS8                    NavLayerCurrent;                // ImGuiNavLayer in 1 byte
    ImU8                    AutoFitQueue;                   // Queue of 8 values for the next 8 frames to request auto-fit
    ImU8                    CannotSkipItemsQueue;           // Queue of 8 values for the next 8 frames to disable Clipped/SkipItem
    ImU8                    SortDirection : 2;              // ImGuiSortDirection_Ascending or ImGuiSortDirection_Descending
    ImU8                    SortDirectionsAvailCount : 2;   // Number of available sort directions (0 to 3)
    ImU8                    SortDirectionsAvailMask : 4;    // Mask of available sort directions (1-bit each)
    ImU8                    SortDirectionsAvailList;        // Ordered list of available sort directions (2-bits each, total 8-bits)

    ImGuiTableColumn()
    {
        memset(this, 0, sizeof(*this));
        StretchWeight = WidthRequest = -1.0f;
        NameOffset = -1;
        DisplayOrder = IndexWithinEnabledSet = -1;
        PrevEnabledColumn = NextEnabledColumn = -1;
        SortOrder = -1;
        SortDirection = ImGuiSortDirection_None;
        DrawChannelCurrent = DrawChannelFrozen = DrawChannelUnfrozen = (ImU8)-1;
    }
};

// Transient cell data stored per row.
// sizeof() ~ 6 bytes
struct ImGuiTableCellData
{
    ImU32                       BgColor;    // Actual color
    ImGuiTableColumnIdx         Column;     // Column number
};

// Parameters for TableAngledHeadersRowEx()
// This may end up being refactored for more general purpose.
// sizeof() ~ 12 bytes
struct ImGuiTableHeaderData
{
    ImGuiTableColumnIdx         Index;      // Column index
    ImU32                       TextColor;
    ImU32                       BgColor0;
    ImU32                       BgColor1;
};

// Per-instance data that needs preserving across frames (seemingly most others do not need to be preserved aside from debug needs. Does that means they could be moved to ImGuiTableTempData?)
// sizeof() ~ 24 bytes
struct ImGuiTableInstanceData
{
    ImGuiID                     TableInstanceID;
    float                       LastOuterHeight;            // Outer height from last frame
    float                       LastTopHeadersRowHeight;    // Height of first consecutive header rows from last frame (FIXME: this is used assuming consecutive headers are in same frozen set)
    float                       LastFrozenHeight;           // Height of frozen section from last frame
    int                         HoveredRowLast;             // Index of row which was hovered last frame.
    int                         HoveredRowNext;             // Index of row hovered this frame, set after encountering it.

    ImGuiTableInstanceData()    { TableInstanceID = 0; LastOuterHeight = LastTopHeadersRowHeight = LastFrozenHeight = 0.0f; HoveredRowLast = HoveredRowNext = -1; }
};

// sizeof() ~ 592 bytes + heap allocs described in TableBeginInitMemory()
struct  ImGuiTable
{
    ImGuiID                     ID;
    ImGuiTableFlags             Flags;
    void*                       RawData;                    // Single allocation to hold Columns[], DisplayOrderToIndex[] and RowCellData[]
    ImGuiTableTempData*         TempData;                   // Transient data while table is active. Point within g.CurrentTableStack[]
    ImSpan<ImGuiTableColumn>    Columns;                    // Point within RawData[]
    ImSpan<ImGuiTableColumnIdx> DisplayOrderToIndex;        // Point within RawData[]. Store display order of columns (when not reordered, the values are 0...Count-1)
    ImSpan<ImGuiTableCellData>  RowCellData;                // Point within RawData[]. Store cells background requests for current row.
    ImBitArrayPtr               EnabledMaskByDisplayOrder;  // Column DisplayOrder -> IsEnabled map
    ImBitArrayPtr               EnabledMaskByIndex;         // Column Index -> IsEnabled map (== not hidden by user/api) in a format adequate for iterating column without touching cold data
    ImBitArrayPtr               VisibleMaskByIndex;         // Column Index -> IsVisibleX|IsVisibleY map (== not hidden by user/api && not hidden by scrolling/cliprect)
    ImGuiTableFlags             SettingsLoadedFlags;        // Which data were loaded from the .ini file (e.g. when order is not altered we won't save order)
    int                         SettingsOffset;             // Offset in g.SettingsTables
    int                         LastFrameActive;
    int                         ColumnsCount;               // Number of columns declared in BeginTable()
    int                         CurrentRow;
    int                         CurrentColumn;
    ImS16                       InstanceCurrent;            // Count of BeginTable() calls with same ID in the same frame (generally 0). This is a little bit similar to BeginCount for a window, but multiple table with same ID look are multiple tables, they are just synched.
    ImS16                       InstanceInteracted;         // Mark which instance (generally 0) of the same ID is being interacted with
    float                       RowPosY1;
    float                       RowPosY2;
    float                       RowMinHeight;               // Height submitted to TableNextRow()
    float                       RowCellPaddingY;            // Top and bottom padding. Reloaded during row change.
    float                       RowTextBaseline;
    float                       RowIndentOffsetX;
    ImGuiTableRowFlags          RowFlags : 16;              // Current row flags, see ImGuiTableRowFlags_
    ImGuiTableRowFlags          LastRowFlags : 16;
    int                         RowBgColorCounter;          // Counter for alternating background colors (can be fast-forwarded by e.g clipper), not same as CurrentRow because header rows typically don't increase this.
    ImU32                       RowBgColor[2];              // Background color override for current row.
    ImU32                       BorderColorStrong;
    ImU32                       BorderColorLight;
    float                       BorderX1;
    float                       BorderX2;
    float                       HostIndentX;
    float                       MinColumnWidth;
    float                       OuterPaddingX;
    float                       CellPaddingX;               // Padding from each borders. Locked in BeginTable()/Layout.
    float                       CellSpacingX1;              // Spacing between non-bordered cells. Locked in BeginTable()/Layout.
    float                       CellSpacingX2;
    float                       InnerWidth;                 // User value passed to BeginTable(), see comments at the top of BeginTable() for details.
    float                       ColumnsGivenWidth;          // Sum of current column width
    float                       ColumnsAutoFitWidth;        // Sum of ideal column width in order nothing to be clipped, used for auto-fitting and content width submission in outer window
    float                       ColumnsStretchSumWeights;   // Sum of weight of all enabled stretching columns
    float                       ResizedColumnNextWidth;
    float                       ResizeLockMinContentsX2;    // Lock minimum contents width while resizing down in order to not create feedback loops. But we allow growing the table.
    float                       RefScale;                   // Reference scale to be able to rescale columns on font/dpi changes.
    float                       AngledHeadersHeight;        // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    float                       AngledHeadersSlope;         // Set by TableAngledHeadersRow(), used in TableUpdateLayout()
    ImRect                      OuterRect;                  // Note: for non-scrolling table, OuterRect.Max.y is often FLT_MAX until EndTable(), unless a height has been specified in BeginTable().
    ImRect                      InnerRect;                  // InnerRect but without decoration. As with OuterRect, for non-scrolling tables, InnerRect.Max.y is
    ImRect                      WorkRect;
    ImRect                      InnerClipRect;
    ImRect                      BgClipRect;                 // We use this to cpu-clip cell background color fill, evolve during the frame as we cross frozen rows boundaries
    ImRect                      Bg0ClipRectForDrawCmd;      // Actual ImDrawCmd clip rect for BG0/1 channel. This tends to be == OuterWindow->ClipRect at BeginTable() because output in BG0/BG1 is cpu-clipped
    ImRect                      Bg2ClipRectForDrawCmd;      // Actual ImDrawCmd clip rect for BG2 channel. This tends to be a correct, tight-fit, because output to BG2 are done by widgets relying on regular ClipRect.
    ImRect                      HostClipRect;               // This is used to check if we can eventually merge our columns draw calls into the current draw call of the current window.
    ImRect                      HostBackupInnerClipRect;    // Backup of InnerWindow->ClipRect during PushTableBackground()/PopTableBackground()
    ImGuiWindow*                OuterWindow;                // Parent window for the table
    ImGuiWindow*                InnerWindow;                // Window holding the table data (== OuterWindow or a child window)
    ImGuiTextBuffer             ColumnsNames;               // Contiguous buffer holding columns names
    ImDrawListSplitter*         DrawSplitter;               // Shortcut to TempData->DrawSplitter while in table. Isolate draw commands per columns to avoid switching clip rect constantly
    ImGuiTableInstanceData      InstanceDataFirst;
    ImVector<ImGuiTableInstanceData>    InstanceDataExtra;  // FIXME-OPT: Using a small-vector pattern would be good.
    ImGuiTableColumnSortSpecs   SortSpecsSingle;
    ImVector<ImGuiTableColumnSortSpecs> SortSpecsMulti;     // FIXME-OPT: Using a small-vector pattern would be good.
    ImGuiTableSortSpecs         SortSpecs;                  // Public facing sorts specs, this is what we return in TableGetSortSpecs()
    ImGuiTableColumnIdx         SortSpecsCount;
    ImGuiTableColumnIdx         ColumnsEnabledCount;        // Number of enabled columns (<= ColumnsCount)
    ImGuiTableColumnIdx         ColumnsEnabledFixedCount;   // Number of enabled columns using fixed width (<= ColumnsCount)
    ImGuiTableColumnIdx         DeclColumnsCount;           // Count calls to TableSetupColumn()
    ImGuiTableColumnIdx         AngledHeadersCount;         // Count columns with angled headers
    ImGuiTableColumnIdx         HoveredColumnBody;          // Index of column whose visible region is being hovered. Important: == ColumnsCount when hovering empty region after the right-most column!
    ImGuiTableColumnIdx         HoveredColumnBorder;        // Index of column whose right-border is being hovered (for resizing).
    ImGuiTableColumnIdx         HighlightColumnHeader;      // Index of column which should be highlighted.
    ImGuiTableColumnIdx         AutoFitSingleColumn;        // Index of single column requesting auto-fit.
    ImGuiTableColumnIdx         ResizedColumn;              // Index of column being resized. Reset when InstanceCurrent==0.
    ImGuiTableColumnIdx         LastResizedColumn;          // Index of column being resized from previous frame.
    ImGuiTableColumnIdx         HeldHeaderColumn;           // Index of column header being held.
    ImGuiTableColumnIdx         ReorderColumn;              // Index of column being reordered. (not cleared)
    ImGuiTableColumnIdx         ReorderColumnDir;           // -1 or +1
    ImGuiTableColumnIdx         LeftMostEnabledColumn;      // Index of left-most non-hidden column.
    ImGuiTableColumnIdx         RightMostEnabledColumn;     // Index of right-most non-hidden column.
    ImGuiTableColumnIdx         LeftMostStretchedColumn;    // Index of left-most stretched column.
    ImGuiTableColumnIdx         RightMostStretchedColumn;   // Index of right-most stretched column.
    ImGuiTableColumnIdx         ContextPopupColumn;         // Column right-clicked on, of -1 if opening context menu from a neutral/empty spot
    ImGuiTableColumnIdx         FreezeRowsRequest;          // Requested frozen rows count
    ImGuiTableColumnIdx         FreezeRowsCount;            // Actual frozen row count (== FreezeRowsRequest, or == 0 when no scrolling offset)
    ImGuiTableColumnIdx         FreezeColumnsRequest;       // Requested frozen columns count
    ImGuiTableColumnIdx         FreezeColumnsCount;         // Actual frozen columns count (== FreezeColumnsRequest, or == 0 when no scrolling offset)
    ImGuiTableColumnIdx         RowCellDataCurrent;         // Index of current RowCellData[] entry in current row
    ImGuiTableDrawChannelIdx    DummyDrawChannel;           // Redirect non-visible columns here.
    ImGuiTableDrawChannelIdx    Bg2DrawChannelCurrent;      // For Selectable() and other widgets drawing across columns after the freezing line. Index within DrawSplitter.Channels[]
    ImGuiTableDrawChannelIdx    Bg2DrawChannelUnfrozen;
    ImS8                        NavLayer;                   // ImGuiNavLayer at the time of BeginTable().
    bool                        IsLayoutLocked;             // Set by TableUpdateLayout() which is called when beginning the first row.
    bool                        IsInsideRow;                // Set when inside TableBeginRow()/TableEndRow().
    bool                        IsInitializing;
    bool                        IsSortSpecsDirty;
    bool                        IsUsingHeaders;             // Set when the first row had the ImGuiTableRowFlags_Headers flag.
    bool                        IsContextPopupOpen;         // Set when default context menu is open (also see: ContextPopupColumn, InstanceInteracted).
    bool                        DisableDefaultContextMenu;  // Disable default context menu contents. You may submit your own using TableBeginContextMenuPopup()/EndPopup()
    bool                        IsSettingsRequestLoad;
    bool                        IsSettingsDirty;            // Set when table settings have changed and needs to be reported into ImGuiTableSetttings data.
    bool                        IsDefaultDisplayOrder;      // Set when display order is unchanged from default (DisplayOrder contains 0...Count-1)
    bool                        IsResetAllRequest;
    bool                        IsResetDisplayOrderRequest;
    bool                        IsUnfrozenRows;             // Set when we got past the frozen row.
    bool                        IsDefaultSizingPolicy;      // Set if user didn't explicitly set a sizing policy in BeginTable()
    bool                        IsActiveIdAliveBeforeTable;
    bool                        IsActiveIdInTable;
    bool                        HasScrollbarYCurr;          // Whether ANY instance of this table had a vertical scrollbar during the current frame.
    bool                        HasScrollbarYPrev;          // Whether ANY instance of this table had a vertical scrollbar during the previous.
    bool                        MemoryCompacted;
    bool                        HostSkipItems;              // Backup of InnerWindow->SkipItem at the end of BeginTable(), because we will overwrite InnerWindow->SkipItem on a per-column basis

    ImGuiTable()                { memset(this, 0, sizeof(*this)); LastFrameActive = -1; }
    ~ImGuiTable()               { ImGui::MemFree(RawData); }
};

// Transient data that are only needed between BeginTable() and EndTable(), those buffers are shared (1 per level of stacked table).
// - Accessing those requires chasing an extra pointer so for very frequently used data we leave them in the main table structure.
// - We also leave out of this structure data that tend to be particularly useful for debugging/metrics.
// FIXME-TABLE: more transient data could be stored in a stacked ImGuiTableTempData: e.g. SortSpecs.
// sizeof() ~ 136 bytes.
struct  ImGuiTableTempData
{
    int                         TableIndex;                 // Index in g.Tables.Buf[] pool
    float                       LastTimeActive;             // Last timestamp this structure was used
    float                       AngledHeadersExtraWidth;    // Used in EndTable()
    ImVector<ImGuiTableHeaderData> AngledHeadersRequests;   // Used in TableAngledHeadersRow()

    ImVec2                      UserOuterSize;              // outer_size.x passed to BeginTable()
    ImDrawListSplitter          DrawSplitter;

    ImRect                      HostBackupWorkRect;         // Backup of InnerWindow->WorkRect at the end of BeginTable()
    ImRect                      HostBackupParentWorkRect;   // Backup of InnerWindow->ParentWorkRect at the end of BeginTable()
    ImVec2                      HostBackupPrevLineSize;     // Backup of InnerWindow->DC.PrevLineSize at the end of BeginTable()
    ImVec2                      HostBackupCurrLineSize;     // Backup of InnerWindow->DC.CurrLineSize at the end of BeginTable()
    ImVec2                      HostBackupCursorMaxPos;     // Backup of InnerWindow->DC.CursorMaxPos at the end of BeginTable()
    ImVec1                      HostBackupColumnsOffset;    // Backup of OuterWindow->DC.ColumnsOffset at the end of BeginTable()
    float                       HostBackupItemWidth;        // Backup of OuterWindow->DC.ItemWidth at the end of BeginTable()
    int                         HostBackupItemWidthStackSize;//Backup of OuterWindow->DC.ItemWidthStack.Size at the end of BeginTable()

    ImGuiTableTempData()        { memset(this, 0, sizeof(*this)); LastTimeActive = -1.0f; }
};

// sizeof() ~ 12
struct ImGuiTableColumnSettings
{
    float                   WidthOrWeight;
    ImGuiID                 UserID;
    ImGuiTableColumnIdx     Index;
    ImGuiTableColumnIdx     DisplayOrder;
    ImGuiTableColumnIdx     SortOrder;
    ImU8                    SortDirection : 2;
    ImU8                    IsEnabled : 1; // "Visible" in ini file
    ImU8                    IsStretch : 1;

    ImGuiTableColumnSettings()
    {
        WidthOrWeight = 0.0f;
        UserID = 0;
        Index = -1;
        DisplayOrder = SortOrder = -1;
        SortDirection = ImGuiSortDirection_None;
        IsEnabled = 1;
        IsStretch = 0;
    }
};

// This is designed to be stored in a single ImChunkStream (1 header followed by N ImGuiTableColumnSettings, etc.)
struct ImGuiTableSettings
{
    ImGuiID                     ID;                     // Set to 0 to invalidate/delete the setting
    ImGuiTableFlags             SaveFlags;              // Indicate data we want to save using the Resizable/Reorderable/Sortable/Hideable flags (could be using its own flags..)
    float                       RefScale;               // Reference scale to be able to rescale columns on font/dpi changes.
    ImGuiTableColumnIdx         ColumnsCount;
    ImGuiTableColumnIdx         ColumnsCountMax;        // Maximum number of columns this settings instance can store, we can recycle a settings instance with lower number of columns but not higher
    bool                        WantApply;              // Set when loaded from .ini data (to enable merging/loading .ini data into an already running context)

    ImGuiTableSettings()        { memset(this, 0, sizeof(*this)); }
    ImGuiTableColumnSettings*   GetColumnSettings()     { return (ImGuiTableColumnSettings*)(this + 1); }
};

//-----------------------------------------------------------------------------
// [SECTION] ImGui internal API
// No guarantee of forward compatibility here!
//-----------------------------------------------------------------------------

namespace ImGui
{
    // Windows
    // We should always have a CurrentWindow in the stack (there is an implicit "Debug" window)
    // If this ever crashes because g.CurrentWindow is NULL, it means that either:
    // - ImGui::NewFrame() has never been called, which is illegal.
    // - You are calling ImGui functions after ImGui::EndFrame()/ImGui::Render() and before the next ImGui::NewFrame(), which is also illegal.
     ImGuiIO&         GetIOEx(ImGuiContext* ctx);
     ImGuiPlatformIO& GetPlatformIOEx(ImGuiContext* ctx);
    inline    ImGuiWindow*  GetCurrentWindowRead()      { ImGuiContext& g = *GImGui; return g.CurrentWindow; }
    inline    ImGuiWindow*  GetCurrentWindow()          { ImGuiContext& g = *GImGui; g.CurrentWindow->WriteAccessed = true; return g.CurrentWindow; }
     ImGuiWindow*  FindWindowByID(ImGuiID id);
     ImGuiWindow*  FindWindowByName(const char* name);
     void          UpdateWindowParentAndRootLinks(ImGuiWindow* window, ImGuiWindowFlags flags, ImGuiWindow* parent_window);
     void          UpdateWindowSkipRefresh(ImGuiWindow* window);
     ImVec2        CalcWindowNextAutoFitSize(ImGuiWindow* window);
     bool          IsWindowChildOf(ImGuiWindow* window, ImGuiWindow* potential_parent, bool popup_hierarchy, bool dock_hierarchy);
     bool          IsWindowWithinBeginStackOf(ImGuiWindow* window, ImGuiWindow* potential_parent);
     bool          IsWindowAbove(ImGuiWindow* potential_above, ImGuiWindow* potential_below);
     bool          IsWindowNavFocusable(ImGuiWindow* window);
     void          SetWindowPos(ImGuiWindow* window, const ImVec2& pos, ImGuiCond cond = 0);
     void          SetWindowSize(ImGuiWindow* window, const ImVec2& size, ImGuiCond cond = 0);
     void          SetWindowCollapsed(ImGuiWindow* window, bool collapsed, ImGuiCond cond = 0);
     void          SetWindowHitTestHole(ImGuiWindow* window, const ImVec2& pos, const ImVec2& size);
     void          SetWindowHiddenAndSkipItemsForCurrentFrame(ImGuiWindow* window);
    inline void             SetWindowParentWindowForFocusRoute(ImGuiWindow* window, ImGuiWindow* parent_window) { window->ParentWindowForFocusRoute = parent_window; } // You may also use SetNextWindowClass()'s FocusRouteParentWindowId field.
    inline ImRect           WindowRectAbsToRel(ImGuiWindow* window, const ImRect& r) { ImVec2 off = window->DC.CursorStartPos; return ImRect(r.Min.x - off.x, r.Min.y - off.y, r.Max.x - off.x, r.Max.y - off.y); }
    inline ImRect           WindowRectRelToAbs(ImGuiWindow* window, const ImRect& r) { ImVec2 off = window->DC.CursorStartPos; return ImRect(r.Min.x + off.x, r.Min.y + off.y, r.Max.x + off.x, r.Max.y + off.y); }
    inline ImVec2           WindowPosAbsToRel(ImGuiWindow* window, const ImVec2& p)  { ImVec2 off = window->DC.CursorStartPos; return ImVec2(p.x - off.x, p.y - off.y); }
    inline ImVec2           WindowPosRelToAbs(ImGuiWindow* window, const ImVec2& p)  { ImVec2 off = window->DC.CursorStartPos; return ImVec2(p.x + off.x, p.y + off.y); }

    // Windows: Display Order and Focus Order
     void          FocusWindow(ImGuiWindow* window, ImGuiFocusRequestFlags flags = 0);
     void          FocusTopMostWindowUnderOne(ImGuiWindow* under_this_window, ImGuiWindow* ignore_window, ImGuiViewport* filter_viewport, ImGuiFocusRequestFlags flags);
     void          BringWindowToFocusFront(ImGuiWindow* window);
     void          BringWindowToDisplayFront(ImGuiWindow* window);
     void          BringWindowToDisplayBack(ImGuiWindow* window);
     void          BringWindowToDisplayBehind(ImGuiWindow* window, ImGuiWindow* above_window);
     int           FindWindowDisplayIndex(ImGuiWindow* window);
     ImGuiWindow*  FindBottomMostVisibleWindowWithinBeginStack(ImGuiWindow* window);

    // Windows: Idle, Refresh Policies [EXPERIMENTAL]
     void          SetNextWindowRefreshPolicy(ImGuiWindowRefreshFlags flags);

    // Fonts, drawing
     void          SetCurrentFont(ImFont* font);
    inline ImFont*          GetDefaultFont() { ImGuiContext& g = *GImGui; return g.IO.FontDefault ? g.IO.FontDefault : g.IO.Fonts->Fonts[0]; }
     void          PushPasswordFont();
    inline ImDrawList*      GetForegroundDrawList(ImGuiWindow* window) { return GetForegroundDrawList(window->Viewport); }
     void          AddDrawListToDrawDataEx(ImDrawData* draw_data, ImVector<ImDrawList*>* out_list, ImDrawList* draw_list);

    // Init
     void          Initialize();
     void          Shutdown();    // Since 1.60 this is a _private_ function. You can call DestroyContext() to destroy the context created by CreateContext().

    // NewFrame
     void          UpdateInputEvents(bool trickle_fast_inputs);
     void          UpdateHoveredWindowAndCaptureFlags();
     void          FindHoveredWindowEx(const ImVec2& pos, bool find_first_and_in_any_viewport, ImGuiWindow** out_hovered_window, ImGuiWindow** out_hovered_window_under_moving_window);
     void          StartMouseMovingWindow(ImGuiWindow* window);
     void          StartMouseMovingWindowOrNode(ImGuiWindow* window, ImGuiDockNode* node, bool undock);
     void          UpdateMouseMovingWindowNewFrame();
     void          UpdateMouseMovingWindowEndFrame();

    // Generic context hooks
     ImGuiID       AddContextHook(ImGuiContext* context, const ImGuiContextHook* hook);
     void          RemoveContextHook(ImGuiContext* context, ImGuiID hook_to_remove);
     void          CallContextHooks(ImGuiContext* context, ImGuiContextHookType type);

    // Viewports
     void          TranslateWindowsInViewport(ImGuiViewportP* viewport, const ImVec2& old_pos, const ImVec2& new_pos, const ImVec2& old_size, const ImVec2& new_size);
     void          ScaleWindowsInViewport(ImGuiViewportP* viewport, float scale);
     void          DestroyPlatformWindow(ImGuiViewportP* viewport);
     void          SetWindowViewport(ImGuiWindow* window, ImGuiViewportP* viewport);
     void          SetCurrentViewport(ImGuiWindow* window, ImGuiViewportP* viewport);
     const ImGuiPlatformMonitor*   GetViewportPlatformMonitor(ImGuiViewport* viewport);
     ImGuiViewportP*               FindHoveredViewportFromPlatformWindowStack(const ImVec2& mouse_platform_pos);

    // Settings
     void                  MarkIniSettingsDirty();
     void                  MarkIniSettingsDirty(ImGuiWindow* window);
     void                  ClearIniSettings();
     void                  AddSettingsHandler(const ImGuiSettingsHandler* handler);
     void                  RemoveSettingsHandler(const char* type_name);
     ImGuiSettingsHandler* FindSettingsHandler(const char* type_name);

    // Settings - Windows
     ImGuiWindowSettings*  CreateNewWindowSettings(const char* name);
     ImGuiWindowSettings*  FindWindowSettingsByID(ImGuiID id);
     ImGuiWindowSettings*  FindWindowSettingsByWindow(ImGuiWindow* window);
     void                  ClearWindowSettings(const char* name);

    // Localization
     void          LocalizeRegisterEntries(const ImGuiLocEntry* entries, int count);
    inline const char*      LocalizeGetMsg(ImGuiLocKey key) { ImGuiContext& g = *GImGui; const char* msg = g.LocalizationTable[key]; return msg ? msg : "*Missing Text*"; }

    // Scrolling
     void          SetScrollX(ImGuiWindow* window, float scroll_x);
     void          SetScrollY(ImGuiWindow* window, float scroll_y);
     void          SetScrollFromPosX(ImGuiWindow* window, float local_x, float center_x_ratio);
     void          SetScrollFromPosY(ImGuiWindow* window, float local_y, float center_y_ratio);

    // Early work-in-progress API (ScrollToItem() will become public)
     void          ScrollToItem(ImGuiScrollFlags flags = 0);
     void          ScrollToRect(ImGuiWindow* window, const ImRect& rect, ImGuiScrollFlags flags = 0);
     ImVec2        ScrollToRectEx(ImGuiWindow* window, const ImRect& rect, ImGuiScrollFlags flags = 0);
//#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    inline void             ScrollToBringRectIntoView(ImGuiWindow* window, const ImRect& rect) { ScrollToRect(window, rect, ImGuiScrollFlags_KeepVisibleEdgeY); }
//#endif

    // Basic Accessors
    inline ImGuiItemStatusFlags GetItemStatusFlags() { ImGuiContext& g = *GImGui; return g.LastItemData.StatusFlags; }
    inline ImGuiItemFlags   GetItemFlags()  { ImGuiContext& g = *GImGui; return g.LastItemData.ItemFlags; }
    inline ImGuiID          GetActiveID()   { ImGuiContext& g = *GImGui; return g.ActiveId; }
    inline ImGuiID          GetFocusID()    { ImGuiContext& g = *GImGui; return g.NavId; }
     void          SetActiveID(ImGuiID id, ImGuiWindow* window);
     void          SetFocusID(ImGuiID id, ImGuiWindow* window);
     void          ClearActiveID();
     ImGuiID       GetHoveredID();
     void          SetHoveredID(ImGuiID id);
     void          KeepAliveID(ImGuiID id);
     void          MarkItemEdited(ImGuiID id);     // Mark data associated to given item as "edited", used by IsItemDeactivatedAfterEdit() function.
     void          PushOverrideID(ImGuiID id);     // Push given value as-is at the top of the ID stack (whereas PushID combines old and new hashes)
     ImGuiID       GetIDWithSeed(const char* str_id_begin, const char* str_id_end, ImGuiID seed);
     ImGuiID       GetIDWithSeed(int n, ImGuiID seed);

    // Basic Helpers for widget code
     void          ItemSize(const ImVec2& size, float text_baseline_y = -1.0f);
    inline void             ItemSize(const ImRect& bb, float text_baseline_y = -1.0f) { ItemSize(bb.GetSize(), text_baseline_y); } // FIXME: This is a misleading API since we expect CursorPos to be bb.Min.
     bool          ItemAdd(const ImRect& bb, ImGuiID id, const ImRect* nav_bb = ((void *)0), ImGuiItemFlags extra_flags = 0);
     bool          ItemHoverable(const ImRect& bb, ImGuiID id, ImGuiItemFlags item_flags);
     bool          IsWindowContentHoverable(ImGuiWindow* window, ImGuiHoveredFlags flags = 0);
     bool          IsClippedEx(const ImRect& bb, ImGuiID id);
     void          SetLastItemData(ImGuiID item_id, ImGuiItemFlags item_flags, ImGuiItemStatusFlags status_flags, const ImRect& item_rect);
     ImVec2        CalcItemSize(ImVec2 size, float default_w, float default_h);
     float         CalcWrapWidthForPos(const ImVec2& pos, float wrap_pos_x);
     void          PushMultiItemsWidths(int components, float width_full);
     void          ShrinkWidths(ImGuiShrinkWidthItem* items, int count, float width_excess);

    // Parameter stacks (shared)
     const ImGuiDataVarInfo* GetStyleVarInfo(ImGuiStyleVar idx);
     void          BeginDisabledOverrideReenable();
     void          EndDisabledOverrideReenable();

    // Logging/Capture
     void          LogBegin(ImGuiLogFlags flags, int auto_open_depth);         // -> BeginCapture() when we design v2 api, for now stay under the radar by using the old name.
     void          LogToBuffer(int auto_open_depth = -1);                      // Start logging/capturing to internal buffer
     void          LogRenderedText(const ImVec2* ref_pos, const char* text, const char* text_end = ((void *)0));
     void          LogSetNextTextDecoration(const char* prefix, const char* suffix);

    // Childs
     bool          BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags);

    // Popups, Modals
     bool          BeginPopupEx(ImGuiID id, ImGuiWindowFlags extra_window_flags);
     void          OpenPopupEx(ImGuiID id, ImGuiPopupFlags popup_flags = ImGuiPopupFlags_None);
     void          ClosePopupToLevel(int remaining, bool restore_focus_to_window_under_popup);
     void          ClosePopupsOverWindow(ImGuiWindow* ref_window, bool restore_focus_to_window_under_popup);
     void          ClosePopupsExceptModals();
     bool          IsPopupOpen(ImGuiID id, ImGuiPopupFlags popup_flags);
     ImRect        GetPopupAllowedExtentRect(ImGuiWindow* window);
     ImGuiWindow*  GetTopMostPopupModal();
     ImGuiWindow*  GetTopMostAndVisiblePopupModal();
     ImGuiWindow*  FindBlockingModal(ImGuiWindow* window);
     ImVec2        FindBestWindowPosForPopup(ImGuiWindow* window);
     ImVec2        FindBestWindowPosForPopupEx(const ImVec2& ref_pos, const ImVec2& size, ImGuiDir* last_dir, const ImRect& r_outer, const ImRect& r_avoid, ImGuiPopupPositionPolicy policy);

    // Tooltips
     bool          BeginTooltipEx(ImGuiTooltipFlags tooltip_flags, ImGuiWindowFlags extra_window_flags);
     bool          BeginTooltipHidden();

    // Menus
     bool          BeginViewportSideBar(const char* name, ImGuiViewport* viewport, ImGuiDir dir, float size, ImGuiWindowFlags window_flags);
     bool          BeginMenuEx(const char* label, const char* icon, bool enabled = true);
     bool          MenuItemEx(const char* label, const char* icon, const char* shortcut = ((void *)0), bool selected = false, bool enabled = true);

    // Combos
     bool          BeginComboPopup(ImGuiID popup_id, const ImRect& bb, ImGuiComboFlags flags);
     bool          BeginComboPreview();
     void          EndComboPreview();

    // Keyboard/Gamepad Navigation
     void          NavInitWindow(ImGuiWindow* window, bool force_reinit);
     void          NavInitRequestApplyResult();
     bool          NavMoveRequestButNoResultYet();
     void          NavMoveRequestSubmit(ImGuiDir move_dir, ImGuiDir clip_dir, ImGuiNavMoveFlags move_flags, ImGuiScrollFlags scroll_flags);
     void          NavMoveRequestForward(ImGuiDir move_dir, ImGuiDir clip_dir, ImGuiNavMoveFlags move_flags, ImGuiScrollFlags scroll_flags);
     void          NavMoveRequestResolveWithLastItem(ImGuiNavItemData* result);
     void          NavMoveRequestResolveWithPastTreeNode(ImGuiNavItemData* result, ImGuiTreeNodeStackData* tree_node_data);
     void          NavMoveRequestCancel();
     void          NavMoveRequestApplyResult();
     void          NavMoveRequestTryWrapping(ImGuiWindow* window, ImGuiNavMoveFlags move_flags);
     void          NavHighlightActivated(ImGuiID id);
     void          NavClearPreferredPosForAxis(ImGuiAxis axis);
     void          SetNavCursorVisibleAfterMove();
     void          NavUpdateCurrentWindowIsScrollPushableX();
     void          SetNavWindow(ImGuiWindow* window);
     void          SetNavID(ImGuiID id, ImGuiNavLayer nav_layer, ImGuiID focus_scope_id, const ImRect& rect_rel);
     void          SetNavFocusScope(ImGuiID focus_scope_id);

    // Focus/Activation
    // This should be part of a larger set of API: FocusItem(offset = -1), FocusItemByID(id), ActivateItem(offset = -1), ActivateItemByID(id) etc. which are
    // much harder to design and implement than expected. I have a couple of private branches on this matter but it's not simple. For now implementing the easy ones.
     void          FocusItem();                    // Focus last item (no selection/activation).
     void          ActivateItemByID(ImGuiID id);   // Activate an item by ID (button, checkbox, tree node etc.). Activation is queued and processed on the next frame when the item is encountered again.

    // Inputs
    // FIXME: Eventually we should aim to move e.g. IsActiveIdUsingKey() into IsKeyXXX functions.
    inline bool             IsNamedKey(ImGuiKey key)                    { return key >= ImGuiKey_NamedKey_BEGIN && key < ImGuiKey_NamedKey_END; }
    inline bool             IsNamedKeyOrMod(ImGuiKey key)               { return (key >= ImGuiKey_NamedKey_BEGIN && key < ImGuiKey_NamedKey_END) || key == ImGuiMod_Ctrl || key == ImGuiMod_Shift || key == ImGuiMod_Alt || key == ImGuiMod_Super; }
    inline bool             IsLegacyKey(ImGuiKey key)                   { return key >= 0 && key < 512; }
    inline bool             IsKeyboardKey(ImGuiKey key)                 { return key >= (ImGuiKey_NamedKey_BEGIN) && key < (ImGuiKey_GamepadStart); }
    inline bool             IsGamepadKey(ImGuiKey key)                  { return key >= (ImGuiKey_GamepadStart) && key < (ImGuiKey_GamepadRStickDown + 1); }
    inline bool             IsMouseKey(ImGuiKey key)                    { return key >= (ImGuiKey_MouseLeft) && key < (ImGuiKey_MouseWheelY + 1); }
    inline bool             IsAliasKey(ImGuiKey key)                    { return key >= ((ImGuiKey_MouseLeft)) && key < ((ImGuiKey_MouseWheelY + 1)); }
    inline bool             IsLRModKey(ImGuiKey key)                    { return key >= ImGuiKey_LeftCtrl && key <= ImGuiKey_RightSuper; }
    ImGuiKeyChord           FixupKeyChord(ImGuiKeyChord key_chord);
    inline ImGuiKey         ConvertSingleModFlagToKey(ImGuiKey key)
    {
        if (key == ImGuiMod_Ctrl) return ImGuiKey_ReservedForModCtrl;
        if (key == ImGuiMod_Shift) return ImGuiKey_ReservedForModShift;
        if (key == ImGuiMod_Alt) return ImGuiKey_ReservedForModAlt;
        if (key == ImGuiMod_Super) return ImGuiKey_ReservedForModSuper;
        return key;
    }

     ImGuiKeyData* GetKeyData(ImGuiContext* ctx, ImGuiKey key);
    inline ImGuiKeyData*    GetKeyData(ImGuiKey key)                                    { ImGuiContext& g = *GImGui; return GetKeyData(&g, key); }
     const char*   GetKeyChordName(ImGuiKeyChord key_chord);
    inline ImGuiKey         MouseButtonToKey(ImGuiMouseButton button)                   { (void)( (!!(button >= 0 && button < ImGuiMouseButton_COUNT)) || (_wassert(L"button >= 0 && button < ImGuiMouseButton_COUNT", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(3445)), 0) ); return (ImGuiKey)(ImGuiKey_MouseLeft + button); }
     bool          IsMouseDragPastThreshold(ImGuiMouseButton button, float lock_threshold = -1.0f);
     ImVec2        GetKeyMagnitude2d(ImGuiKey key_left, ImGuiKey key_right, ImGuiKey key_up, ImGuiKey key_down);
     float         GetNavTweakPressedAmount(ImGuiAxis axis);
     int           CalcTypematicRepeatAmount(float t0, float t1, float repeat_delay, float repeat_rate);
     void          GetTypematicRepeatRate(ImGuiInputFlags flags, float* repeat_delay, float* repeat_rate);
     void          TeleportMousePos(const ImVec2& pos);
     void          SetActiveIdUsingAllKeyboardKeys();
    inline bool             IsActiveIdUsingNavDir(ImGuiDir dir)                         { ImGuiContext& g = *GImGui; return (g.ActiveIdUsingNavDirMask & (1 << dir)) != 0; }

    // [EXPERIMENTAL] Low-Level: Key/Input Ownership
    // - The idea is that instead of "eating" a given input, we can link to an owner id.
    // - Ownership is most often claimed as a result of reacting to a press/down event (but occasionally may be claimed ahead).
    // - Input queries can then read input by specifying ImGuiKeyOwner_Any (== 0), ImGuiKeyOwner_NoOwner (== -1) or a custom ID.
    // - Legacy input queries (without specifying an owner or _Any or _None) are equivalent to using ImGuiKeyOwner_Any (== 0).
    // - Input ownership is automatically released on the frame after a key is released. Therefore:
    //   - for ownership registration happening as a result of a down/press event, the SetKeyOwner() call may be done once (common case).
    //   - for ownership registration happening ahead of a down/press event, the SetKeyOwner() call needs to be made every frame (happens if e.g. claiming ownership on hover).
    // - SetItemKeyOwner() is a shortcut for common simple case. A custom widget will probably want to call SetKeyOwner() multiple times directly based on its interaction state.
    // - This is marked experimental because not all widgets are fully honoring the Set/Test idioms. We will need to move forward step by step.
    //   Please open a GitHub Issue to submit your usage scenario or if there's a use case you need solved.
     ImGuiID       GetKeyOwner(ImGuiKey key);
     void          SetKeyOwner(ImGuiKey key, ImGuiID owner_id, ImGuiInputFlags flags = 0);
     void          SetKeyOwnersForKeyChord(ImGuiKeyChord key, ImGuiID owner_id, ImGuiInputFlags flags = 0);
     void          SetItemKeyOwner(ImGuiKey key, ImGuiInputFlags flags);       // Set key owner to last item if it is hovered or active. Equivalent to 'if (IsItemHovered() || IsItemActive()) { SetKeyOwner(key, GetItemID());'.
     bool          TestKeyOwner(ImGuiKey key, ImGuiID owner_id);               // Test that key is either not owned, either owned by 'owner_id'
    inline ImGuiKeyOwnerData* GetKeyOwnerData(ImGuiContext* ctx, ImGuiKey key)          { if (key & ImGuiMod_Mask_) key = ConvertSingleModFlagToKey(key); (void)( (!!(IsNamedKey(key))) || (_wassert(L"IsNamedKey(key)", L"C:\\repos\\i2d-imgui\\deps\\cimgui\\generator\\../imgui/imgui_internal.h", (unsigned)(3471)), 0) ); return &ctx->KeysOwnerData[key - ImGuiKey_NamedKey_BEGIN]; }

    // [EXPERIMENTAL] High-Level: Input Access functions w/ support for Key/Input Ownership
    // - Important: legacy IsKeyPressed(ImGuiKey, bool repeat=true) _DEFAULTS_ to repeat, new IsKeyPressed() requires _EXPLICIT_ ImGuiInputFlags_Repeat flag.
    // - Expected to be later promoted to public API, the prototypes are designed to replace existing ones (since owner_id can default to Any == 0)
    // - Specifying a value for 'ImGuiID owner' will test that EITHER the key is NOT owned (UNLESS locked), EITHER the key is owned by 'owner'.
    //   Legacy functions use ImGuiKeyOwner_Any meaning that they typically ignore ownership, unless a call to SetKeyOwner() explicitly used ImGuiInputFlags_LockThisFrame or ImGuiInputFlags_LockUntilRelease.
    // - Binding generators may want to ignore those for now, or suffix them with Ex() until we decide if this gets moved into public API.
     bool          IsKeyDown(ImGuiKey key, ImGuiID owner_id);
     bool          IsKeyPressed(ImGuiKey key, ImGuiInputFlags flags, ImGuiID owner_id = 0);    // Important: when transitioning from old to new IsKeyPressed(): old API has "bool repeat = true", so would default to repeat. New API requiress explicit ImGuiInputFlags_Repeat.
     bool          IsKeyReleased(ImGuiKey key, ImGuiID owner_id);
     bool          IsKeyChordPressed(ImGuiKeyChord key_chord, ImGuiInputFlags flags, ImGuiID owner_id = 0);
     bool          IsMouseDown(ImGuiMouseButton button, ImGuiID owner_id);
     bool          IsMouseClicked(ImGuiMouseButton button, ImGuiInputFlags flags, ImGuiID owner_id = 0);
     bool          IsMouseReleased(ImGuiMouseButton button, ImGuiID owner_id);
     bool          IsMouseDoubleClicked(ImGuiMouseButton button, ImGuiID owner_id);

    // Shortcut Testing & Routing
    // - Set Shortcut() and SetNextItemShortcut() in imgui.h
    // - When a policy (except for ImGuiInputFlags_RouteAlways *) is set, Shortcut() will register itself with SetShortcutRouting(),
    //   allowing the system to decide where to route the input among other route-aware calls.
    //   (* using ImGuiInputFlags_RouteAlways is roughly equivalent to calling IsKeyChordPressed(key) and bypassing route registration and check)
    // - When using one of the routing option:
    //   - The default route is ImGuiInputFlags_RouteFocused (accept inputs if window is in focus stack. Deep-most focused window takes inputs. ActiveId takes inputs over deep-most focused window.)
    //   - Routes are requested given a chord (key + modifiers) and a routing policy.
    //   - Routes are resolved during NewFrame(): if keyboard modifiers are matching current ones: SetKeyOwner() is called + route is granted for the frame.
    //   - Each route may be granted to a single owner. When multiple requests are made we have policies to select the winning route (e.g. deep most window).
    //   - Multiple read sites may use the same owner id can all access the granted route.
    //   - When owner_id is 0 we use the current Focus Scope ID as a owner ID in order to identify our location.
    // - You can chain two unrelated windows in the focus stack using SetWindowParentWindowForFocusRoute()
    //   e.g. if you have a tool window associated to a document, and you want document shortcuts to run when the tool is focused.
     bool          Shortcut(ImGuiKeyChord key_chord, ImGuiInputFlags flags, ImGuiID owner_id);
     bool          SetShortcutRouting(ImGuiKeyChord key_chord, ImGuiInputFlags flags, ImGuiID owner_id); // owner_id needs to be explicit and cannot be 0
     bool          TestShortcutRouting(ImGuiKeyChord key_chord, ImGuiID owner_id);
     ImGuiKeyRoutingData* GetShortcutRoutingData(ImGuiKeyChord key_chord);

    // Docking
    // (some functions are only declared in imgui.cpp, see Docking section)
     void          DockContextInitialize(ImGuiContext* ctx);
     void          DockContextShutdown(ImGuiContext* ctx);
     void          DockContextClearNodes(ImGuiContext* ctx, ImGuiID root_id, bool clear_settings_refs); // Use root_id==0 to clear all
     void          DockContextRebuildNodes(ImGuiContext* ctx);
     void          DockContextNewFrameUpdateUndocking(ImGuiContext* ctx);
     void          DockContextNewFrameUpdateDocking(ImGuiContext* ctx);
     void          DockContextEndFrame(ImGuiContext* ctx);
     ImGuiID       DockContextGenNodeID(ImGuiContext* ctx);
     void          DockContextQueueDock(ImGuiContext* ctx, ImGuiWindow* target, ImGuiDockNode* target_node, ImGuiWindow* payload, ImGuiDir split_dir, float split_ratio, bool split_outer);
     void          DockContextQueueUndockWindow(ImGuiContext* ctx, ImGuiWindow* window);
     void          DockContextQueueUndockNode(ImGuiContext* ctx, ImGuiDockNode* node);
     void          DockContextProcessUndockWindow(ImGuiContext* ctx, ImGuiWindow* window, bool clear_persistent_docking_ref = true);
     void          DockContextProcessUndockNode(ImGuiContext* ctx, ImGuiDockNode* node);
     bool          DockContextCalcDropPosForDocking(ImGuiWindow* target, ImGuiDockNode* target_node, ImGuiWindow* payload_window, ImGuiDockNode* payload_node, ImGuiDir split_dir, bool split_outer, ImVec2* out_pos);
     ImGuiDockNode*DockContextFindNodeByID(ImGuiContext* ctx, ImGuiID id);
     void          DockNodeWindowMenuHandler_Default(ImGuiContext* ctx, ImGuiDockNode* node, ImGuiTabBar* tab_bar);
     bool          DockNodeBeginAmendTabBar(ImGuiDockNode* node);
     void          DockNodeEndAmendTabBar();
    inline ImGuiDockNode*   DockNodeGetRootNode(ImGuiDockNode* node)                 { while (node->ParentNode) node = node->ParentNode; return node; }
    inline bool             DockNodeIsInHierarchyOf(ImGuiDockNode* node, ImGuiDockNode* parent) { while (node) { if (node == parent) return true; node = node->ParentNode; } return false; }
    inline int              DockNodeGetDepth(const ImGuiDockNode* node)              { int depth = 0; while (node->ParentNode) { node = node->ParentNode; depth++; } return depth; }
    inline ImGuiID          DockNodeGetWindowMenuButtonId(const ImGuiDockNode* node) { return ImHashStr("#COLLAPSE", 0, node->ID); }
    inline ImGuiDockNode*   GetWindowDockNode()                                      { ImGuiContext& g = *GImGui; return g.CurrentWindow->DockNode; }
     bool          GetWindowAlwaysWantOwnTabBar(ImGuiWindow* window);
     void          BeginDocked(ImGuiWindow* window, bool* p_open);
     void          BeginDockableDragDropSource(ImGuiWindow* window);
     void          BeginDockableDragDropTarget(ImGuiWindow* window);
     void          SetWindowDock(ImGuiWindow* window, ImGuiID dock_id, ImGuiCond cond);

    // Docking - Builder function needs to be generally called before the node is used/submitted.
    // - The DockBuilderXXX functions are designed to _eventually_ become a public API, but it is too early to expose it and guarantee stability.
    // - Do not hold on ImGuiDockNode* pointers! They may be invalidated by any split/merge/remove operation and every frame.
    // - To create a DockSpace() node, make sure to set the ImGuiDockNodeFlags_DockSpace flag when calling DockBuilderAddNode().
    //   You can create dockspace nodes (attached to a window) _or_ floating nodes (carry its own window) with this API.
    // - DockBuilderSplitNode() create 2 child nodes within 1 node. The initial node becomes a parent node.
    // - If you intend to split the node immediately after creation using DockBuilderSplitNode(), make sure
    //   to call DockBuilderSetNodeSize() beforehand. If you don't, the resulting split sizes may not be reliable.
    // - Call DockBuilderFinish() after you are done.
     void          DockBuilderDockWindow(const char* window_name, ImGuiID node_id);
     ImGuiDockNode*DockBuilderGetNode(ImGuiID node_id);
    inline ImGuiDockNode*   DockBuilderGetCentralNode(ImGuiID node_id)              { ImGuiDockNode* node = DockBuilderGetNode(node_id); if (!node) return ((void *)0); return DockNodeGetRootNode(node)->CentralNode; }
     ImGuiID       DockBuilderAddNode(ImGuiID node_id = 0, ImGuiDockNodeFlags flags = 0);
     void          DockBuilderRemoveNode(ImGuiID node_id);                 // Remove node and all its child, undock all windows
     void          DockBuilderRemoveNodeDockedWindows(ImGuiID node_id, bool clear_settings_refs = true);
     void          DockBuilderRemoveNodeChildNodes(ImGuiID node_id);       // Remove all split/hierarchy. All remaining docked windows will be re-docked to the remaining root node (node_id).
     void          DockBuilderSetNodePos(ImGuiID node_id, ImVec2 pos);
     void          DockBuilderSetNodeSize(ImGuiID node_id, ImVec2 size);
     ImGuiID       DockBuilderSplitNode(ImGuiID node_id, ImGuiDir split_dir, float size_ratio_for_node_at_dir, ImGuiID* out_id_at_dir, ImGuiID* out_id_at_opposite_dir); // Create 2 child nodes in this parent node.
     void          DockBuilderCopyDockSpace(ImGuiID src_dockspace_id, ImGuiID dst_dockspace_id, ImVector<const char*>* in_window_remap_pairs);
     void          DockBuilderCopyNode(ImGuiID src_node_id, ImGuiID dst_node_id, ImVector<ImGuiID>* out_node_remap_pairs);
     void          DockBuilderCopyWindowSettings(const char* src_name, const char* dst_name);
     void          DockBuilderFinish(ImGuiID node_id);

    // [EXPERIMENTAL] Focus Scope
    // This is generally used to identify a unique input location (for e.g. a selection set)
    // There is one per window (automatically set in Begin), but:
    // - Selection patterns generally need to react (e.g. clear a selection) when landing on one item of the set.
    //   So in order to identify a set multiple lists in same window may each need a focus scope.
    //   If you imagine an hypothetical BeginSelectionGroup()/EndSelectionGroup() api, it would likely call PushFocusScope()/EndFocusScope()
    // - Shortcut routing also use focus scope as a default location identifier if an owner is not provided.
    // We don't use the ID Stack for this as it is common to want them separate.
     void          PushFocusScope(ImGuiID id);
     void          PopFocusScope();
    inline ImGuiID          GetCurrentFocusScope() { ImGuiContext& g = *GImGui; return g.CurrentFocusScopeId; }   // Focus scope we are outputting into, set by PushFocusScope()

    // Drag and Drop
     bool          IsDragDropActive();
     bool          BeginDragDropTargetCustom(const ImRect& bb, ImGuiID id);
     void          ClearDragDrop();
     bool          IsDragDropPayloadBeingAccepted();
     void          RenderDragDropTargetRect(const ImRect& bb, const ImRect& item_clip_rect);

    // Typing-Select API
    // (provide Windows Explorer style "select items by typing partial name" + "cycle through items by typing same letter" feature)
    // (this is currently not documented nor used by main library, but should work. See "widgets_typingselect" in imgui_test_suite for usage code. Please let us know if you use this!)
     ImGuiTypingSelectRequest* GetTypingSelectRequest(ImGuiTypingSelectFlags flags = ImGuiTypingSelectFlags_None);
     int           TypingSelectFindMatch(ImGuiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data, int nav_item_idx);
     int           TypingSelectFindNextSingleCharMatch(ImGuiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data, int nav_item_idx);
     int           TypingSelectFindBestLeadingMatch(ImGuiTypingSelectRequest* req, int items_count, const char* (*get_item_name_func)(void*, int), void* user_data);

    // Box-Select API
     bool          BeginBoxSelect(const ImRect& scope_rect, ImGuiWindow* window, ImGuiID box_select_id, ImGuiMultiSelectFlags ms_flags);
     void          EndBoxSelect(const ImRect& scope_rect, ImGuiMultiSelectFlags ms_flags);

    // Multi-Select API
     void          MultiSelectItemHeader(ImGuiID id, bool* p_selected, ImGuiButtonFlags* p_button_flags);
     void          MultiSelectItemFooter(ImGuiID id, bool* p_selected, bool* p_pressed);
     void          MultiSelectAddSetAll(ImGuiMultiSelectTempData* ms, bool selected);
     void          MultiSelectAddSetRange(ImGuiMultiSelectTempData* ms, bool selected, int range_dir, ImGuiSelectionUserData first_item, ImGuiSelectionUserData last_item);
    inline ImGuiBoxSelectState*     GetBoxSelectState(ImGuiID id)   { ImGuiContext& g = *GImGui; return (id != 0 && g.BoxSelectState.ID == id && g.BoxSelectState.IsActive) ? &g.BoxSelectState : ((void *)0); }
    inline ImGuiMultiSelectState*   GetMultiSelectState(ImGuiID id) { ImGuiContext& g = *GImGui; return g.MultiSelectStorage.GetByKey(id); }

    // Internal Columns API (this is not exposed because we will encourage transitioning to the Tables API)
     void          SetWindowClipRectBeforeSetChannel(ImGuiWindow* window, const ImRect& clip_rect);
     void          BeginColumns(const char* str_id, int count, ImGuiOldColumnFlags flags = 0); // setup number of columns. use an identifier to distinguish multiple column sets. close with EndColumns().
     void          EndColumns();                                                               // close columns
     void          PushColumnClipRect(int column_index);
     void          PushColumnsBackground();
     void          PopColumnsBackground();
     ImGuiID       GetColumnsID(const char* str_id, int count);
     ImGuiOldColumns* FindOrCreateColumns(ImGuiWindow* window, ImGuiID id);
     float         GetColumnOffsetFromNorm(const ImGuiOldColumns* columns, float offset_norm);
     float         GetColumnNormFromOffset(const ImGuiOldColumns* columns, float offset);

    // Tables: Candidates for public API
     void          TableOpenContextMenu(int column_n = -1);
     void          TableSetColumnWidth(int column_n, float width);
     void          TableSetColumnSortDirection(int column_n, ImGuiSortDirection sort_direction, bool append_to_sort_specs);
     int           TableGetHoveredRow();       // Retrieve *PREVIOUS FRAME* hovered row. This difference with TableGetHoveredColumn() is the reason why this is not public yet.
     float         TableGetHeaderRowHeight();
     float         TableGetHeaderAngledMaxLabelWidth();
     void          TablePushBackgroundChannel();
     void          TablePopBackgroundChannel();
     void          TableAngledHeadersRowEx(ImGuiID row_id, float angle, float max_label_width, const ImGuiTableHeaderData* data, int data_count);

    // Tables: Internals
    inline    ImGuiTable*   GetCurrentTable() { ImGuiContext& g = *GImGui; return g.CurrentTable; }
     ImGuiTable*   TableFindByID(ImGuiID id);
     bool          BeginTableEx(const char* name, ImGuiID id, int columns_count, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0, 0), float inner_width = 0.0f);
     void          TableBeginInitMemory(ImGuiTable* table, int columns_count);
     void          TableBeginApplyRequests(ImGuiTable* table);
     void          TableSetupDrawChannels(ImGuiTable* table);
     void          TableUpdateLayout(ImGuiTable* table);
     void          TableUpdateBorders(ImGuiTable* table);
     void          TableUpdateColumnsWeightFromWidth(ImGuiTable* table);
     void          TableDrawBorders(ImGuiTable* table);
     void          TableDrawDefaultContextMenu(ImGuiTable* table, ImGuiTableFlags flags_for_section_to_display);
     bool          TableBeginContextMenuPopup(ImGuiTable* table);
     void          TableMergeDrawChannels(ImGuiTable* table);
    inline ImGuiTableInstanceData*  TableGetInstanceData(ImGuiTable* table, int instance_no) { if (instance_no == 0) return &table->InstanceDataFirst; return &table->InstanceDataExtra[instance_no - 1]; }
    inline ImGuiID                  TableGetInstanceID(ImGuiTable* table, int instance_no)   { return TableGetInstanceData(table, instance_no)->TableInstanceID; }
     void          TableSortSpecsSanitize(ImGuiTable* table);
     void          TableSortSpecsBuild(ImGuiTable* table);
     ImGuiSortDirection TableGetColumnNextSortDirection(ImGuiTableColumn* column);
     void          TableFixColumnSortDirection(ImGuiTable* table, ImGuiTableColumn* column);
     float         TableGetColumnWidthAuto(ImGuiTable* table, ImGuiTableColumn* column);
     void          TableBeginRow(ImGuiTable* table);
     void          TableEndRow(ImGuiTable* table);
     void          TableBeginCell(ImGuiTable* table, int column_n);
     void          TableEndCell(ImGuiTable* table);
     ImRect        TableGetCellBgRect(const ImGuiTable* table, int column_n);
     const char*   TableGetColumnName(const ImGuiTable* table, int column_n);
     ImGuiID       TableGetColumnResizeID(ImGuiTable* table, int column_n, int instance_no = 0);
     float         TableCalcMaxColumnWidth(const ImGuiTable* table, int column_n);
     void          TableSetColumnWidthAutoSingle(ImGuiTable* table, int column_n);
     void          TableSetColumnWidthAutoAll(ImGuiTable* table);
     void          TableRemove(ImGuiTable* table);
     void          TableGcCompactTransientBuffers(ImGuiTable* table);
     void          TableGcCompactTransientBuffers(ImGuiTableTempData* table);
     void          TableGcCompactSettings();

    // Tables: Settings
     void                  TableLoadSettings(ImGuiTable* table);
     void                  TableSaveSettings(ImGuiTable* table);
     void                  TableResetSettings(ImGuiTable* table);
     ImGuiTableSettings*   TableGetBoundSettings(ImGuiTable* table);
     void                  TableSettingsAddSettingsHandler();
     ImGuiTableSettings*   TableSettingsCreate(ImGuiID id, int columns_count);
     ImGuiTableSettings*   TableSettingsFindByID(ImGuiID id);

    // Tab Bars
    inline    ImGuiTabBar*  GetCurrentTabBar() { ImGuiContext& g = *GImGui; return g.CurrentTabBar; }
     bool          BeginTabBarEx(ImGuiTabBar* tab_bar, const ImRect& bb, ImGuiTabBarFlags flags);
     ImGuiTabItem* TabBarFindTabByID(ImGuiTabBar* tab_bar, ImGuiID tab_id);
     ImGuiTabItem* TabBarFindTabByOrder(ImGuiTabBar* tab_bar, int order);
     ImGuiTabItem* TabBarFindMostRecentlySelectedTabForActiveWindow(ImGuiTabBar* tab_bar);
     ImGuiTabItem* TabBarGetCurrentTab(ImGuiTabBar* tab_bar);
    inline int              TabBarGetTabOrder(ImGuiTabBar* tab_bar, ImGuiTabItem* tab) { return tab_bar->Tabs.index_from_ptr(tab); }
     const char*   TabBarGetTabName(ImGuiTabBar* tab_bar, ImGuiTabItem* tab);
     void          TabBarAddTab(ImGuiTabBar* tab_bar, ImGuiTabItemFlags tab_flags, ImGuiWindow* window);
     void          TabBarRemoveTab(ImGuiTabBar* tab_bar, ImGuiID tab_id);
     void          TabBarCloseTab(ImGuiTabBar* tab_bar, ImGuiTabItem* tab);
     void          TabBarQueueFocus(ImGuiTabBar* tab_bar, ImGuiTabItem* tab);
     void          TabBarQueueFocus(ImGuiTabBar* tab_bar, const char* tab_name);
     void          TabBarQueueReorder(ImGuiTabBar* tab_bar, ImGuiTabItem* tab, int offset);
     void          TabBarQueueReorderFromMousePos(ImGuiTabBar* tab_bar, ImGuiTabItem* tab, ImVec2 mouse_pos);
     bool          TabBarProcessReorder(ImGuiTabBar* tab_bar);
     bool          TabItemEx(ImGuiTabBar* tab_bar, const char* label, bool* p_open, ImGuiTabItemFlags flags, ImGuiWindow* docked_window);
     void          TabItemSpacing(const char* str_id, ImGuiTabItemFlags flags, float width);
     ImVec2        TabItemCalcSize(const char* label, bool has_close_button_or_unsaved_marker);
     ImVec2        TabItemCalcSize(ImGuiWindow* window);
     void          TabItemBackground(ImDrawList* draw_list, const ImRect& bb, ImGuiTabItemFlags flags, ImU32 col);
     void          TabItemLabelAndCloseButton(ImDrawList* draw_list, const ImRect& bb, ImGuiTabItemFlags flags, ImVec2 frame_padding, const char* label, ImGuiID tab_id, ImGuiID close_button_id, bool is_contents_visible, bool* out_just_closed, bool* out_text_clipped);

    // Render helpers
    // AVOID USING OUTSIDE OF IMGUI.CPP! NOT FOR PUBLIC CONSUMPTION. THOSE FUNCTIONS ARE A MESS. THEIR SIGNATURE AND BEHAVIOR WILL CHANGE, THEY NEED TO BE REFACTORED INTO SOMETHING DECENT.
    // NB: All position are in absolute pixels coordinates (we are never using window coordinates internally)
     void          RenderText(ImVec2 pos, const char* text, const char* text_end = ((void *)0), bool hide_text_after_hash = true);
     void          RenderTextWrapped(ImVec2 pos, const char* text, const char* text_end, float wrap_width);
     void          RenderTextClipped(const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align = ImVec2(0, 0), const ImRect* clip_rect = ((void *)0));
     void          RenderTextClippedEx(ImDrawList* draw_list, const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align = ImVec2(0, 0), const ImRect* clip_rect = ((void *)0));
     void          RenderTextEllipsis(ImDrawList* draw_list, const ImVec2& pos_min, const ImVec2& pos_max, float clip_max_x, float ellipsis_max_x, const char* text, const char* text_end, const ImVec2* text_size_if_known);
     void          RenderFrame(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, bool borders = true, float rounding = 0.0f);
     void          RenderFrameBorder(ImVec2 p_min, ImVec2 p_max, float rounding = 0.0f);
     void          RenderColorRectWithAlphaCheckerboard(ImDrawList* draw_list, ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, float grid_step, ImVec2 grid_off, float rounding = 0.0f, ImDrawFlags flags = 0);
     void          RenderNavCursor(const ImRect& bb, ImGuiID id, ImGuiNavRenderCursorFlags flags = ImGuiNavRenderCursorFlags_None); // Navigation highlight



     const char*   FindRenderedTextEnd(const char* text, const char* text_end = ((void *)0)); // Find the optional ## from which we stop displaying text.
     void          RenderMouseCursor(ImVec2 pos, float scale, ImGuiMouseCursor mouse_cursor, ImU32 col_fill, ImU32 col_border, ImU32 col_shadow);

    // Render helpers (those functions don't access any ImGui state!)
     void          RenderArrow(ImDrawList* draw_list, ImVec2 pos, ImU32 col, ImGuiDir dir, float scale = 1.0f);
     void          RenderBullet(ImDrawList* draw_list, ImVec2 pos, ImU32 col);
     void          RenderCheckMark(ImDrawList* draw_list, ImVec2 pos, ImU32 col, float sz);
     void          RenderArrowPointingAt(ImDrawList* draw_list, ImVec2 pos, ImVec2 half_sz, ImGuiDir direction, ImU32 col);
     void          RenderArrowDockMenu(ImDrawList* draw_list, ImVec2 p_min, float sz, ImU32 col);
     void          RenderRectFilledRangeH(ImDrawList* draw_list, const ImRect& rect, ImU32 col, float x_start_norm, float x_end_norm, float rounding);
     void          RenderRectFilledWithHole(ImDrawList* draw_list, const ImRect& outer, const ImRect& inner, ImU32 col, float rounding);
     ImDrawFlags   CalcRoundingFlagsForRectInRect(const ImRect& r_in, const ImRect& r_outer, float threshold);

    // Widgets
     void          TextEx(const char* text, const char* text_end = ((void *)0), ImGuiTextFlags flags = 0);
     bool          ButtonEx(const char* label, const ImVec2& size_arg = ImVec2(0, 0), ImGuiButtonFlags flags = 0);
     bool          ArrowButtonEx(const char* str_id, ImGuiDir dir, ImVec2 size_arg, ImGuiButtonFlags flags = 0);
     bool          ImageButtonEx(ImGuiID id, ImTextureID user_texture_id, const ImVec2& image_size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& bg_col, const ImVec4& tint_col, ImGuiButtonFlags flags = 0);
     void          SeparatorEx(ImGuiSeparatorFlags flags, float thickness = 1.0f);
     void          SeparatorTextEx(ImGuiID id, const char* label, const char* label_end, float extra_width);
     bool          CheckboxFlags(const char* label, ImS64* flags, ImS64 flags_value);
     bool          CheckboxFlags(const char* label, ImU64* flags, ImU64 flags_value);

    // Widgets: Window Decorations
     bool          CloseButton(ImGuiID id, const ImVec2& pos);
     bool          CollapseButton(ImGuiID id, const ImVec2& pos, ImGuiDockNode* dock_node);
     void          Scrollbar(ImGuiAxis axis);
     bool          ScrollbarEx(const ImRect& bb, ImGuiID id, ImGuiAxis axis, ImS64* p_scroll_v, ImS64 avail_v, ImS64 contents_v, ImDrawFlags draw_rounding_flags = 0);
     ImRect        GetWindowScrollbarRect(ImGuiWindow* window, ImGuiAxis axis);
     ImGuiID       GetWindowScrollbarID(ImGuiWindow* window, ImGuiAxis axis);
     ImGuiID       GetWindowResizeCornerID(ImGuiWindow* window, int n); // 0..3: corners
     ImGuiID       GetWindowResizeBorderID(ImGuiWindow* window, ImGuiDir dir);

    // Widgets low-level behaviors
     bool          ButtonBehavior(const ImRect& bb, ImGuiID id, bool* out_hovered, bool* out_held, ImGuiButtonFlags flags = 0);
     bool          DragBehavior(ImGuiID id, ImGuiDataType data_type, void* p_v, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
     bool          SliderBehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb);
     bool          SplitterBehavior(const ImRect& bb, ImGuiID id, ImGuiAxis axis, float* size1, float* size2, float min_size1, float min_size2, float hover_extend = 0.0f, float hover_visibility_delay = 0.0f, ImU32 bg_col = 0);

    // Widgets: Tree Nodes
     bool          TreeNodeBehavior(ImGuiID id, ImGuiTreeNodeFlags flags, const char* label, const char* label_end = ((void *)0));
     void          TreePushOverrideID(ImGuiID id);
     bool          TreeNodeGetOpen(ImGuiID storage_id);
     void          TreeNodeSetOpen(ImGuiID storage_id, bool open);
     bool          TreeNodeUpdateNextOpen(ImGuiID storage_id, ImGuiTreeNodeFlags flags);   // Return open state. Consume previous SetNextItemOpen() data, if any. May return true when logging.

    // Template functions are instantiated in imgui_widgets.cpp for a finite number of types.
    // To use them externally (for custom widget) you may need an "extern template" statement in your code in order to link to existing instances and silence Clang warnings (see #2036).
    // e.g. " extern template IMGUI_API float RoundScalarWithFormatT<float, float>(const char* format, ImGuiDataType data_type, float v); "
    template<typename T, typename SIGNED_T, typename FLOAT_T>    float ScaleRatioFromValueT(ImGuiDataType data_type, T v, T v_min, T v_max, bool is_logarithmic, float logarithmic_zero_epsilon, float zero_deadzone_size);
    template<typename T, typename SIGNED_T, typename FLOAT_T>    T     ScaleValueFromRatioT(ImGuiDataType data_type, float t, T v_min, T v_max, bool is_logarithmic, float logarithmic_zero_epsilon, float zero_deadzone_size);
    template<typename T, typename SIGNED_T, typename FLOAT_T>    bool  DragBehaviorT(ImGuiDataType data_type, T* v, float v_speed, T v_min, T v_max, const char* format, ImGuiSliderFlags flags);
    template<typename T, typename SIGNED_T, typename FLOAT_T>    bool  SliderBehaviorT(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, T* v, T v_min, T v_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb);
    template<typename T>                                         T     RoundScalarWithFormatT(const char* format, ImGuiDataType data_type, T v);
    template<typename T>                                         bool  CheckboxFlagsT(const char* label, T* flags, T flags_value);

    // Data type helpers
     const ImGuiDataTypeInfo*  DataTypeGetInfo(ImGuiDataType data_type);
     int           DataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const void* p_data, const char* format);
     void          DataTypeApplyOp(ImGuiDataType data_type, int op, void* output, const void* arg_1, const void* arg_2);
     bool          DataTypeApplyFromText(const char* buf, ImGuiDataType data_type, void* p_data, const char* format, void* p_data_when_empty = ((void *)0));
     int           DataTypeCompare(ImGuiDataType data_type, const void* arg_1, const void* arg_2);
     bool          DataTypeClamp(ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max);
     bool          DataTypeIsZero(ImGuiDataType data_type, const void* p_data);

    // InputText
     bool          InputTextEx(const char* label, const char* hint, char* buf, int buf_size, const ImVec2& size_arg, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback = ((void *)0), void* user_data = ((void *)0));
     void          InputTextDeactivateHook(ImGuiID id);
     bool          TempInputText(const ImRect& bb, ImGuiID id, const char* label, char* buf, int buf_size, ImGuiInputTextFlags flags);
     bool          TempInputScalar(const ImRect& bb, ImGuiID id, const char* label, ImGuiDataType data_type, void* p_data, const char* format, const void* p_clamp_min = ((void *)0), const void* p_clamp_max = ((void *)0));
    inline bool             TempInputIsActive(ImGuiID id)       { ImGuiContext& g = *GImGui; return (g.ActiveId == id && g.TempInputId == id); }
    inline ImGuiInputTextState* GetInputTextState(ImGuiID id)   { ImGuiContext& g = *GImGui; return (id != 0 && g.InputTextState.ID == id) ? &g.InputTextState : ((void *)0); } // Get input text state if active
     void          SetNextItemRefVal(ImGuiDataType data_type, void* p_data);

    // Color
     void          ColorTooltip(const char* text, const float* col, ImGuiColorEditFlags flags);
     void          ColorEditOptionsPopup(const float* col, ImGuiColorEditFlags flags);
     void          ColorPickerOptionsPopup(const float* ref_col, ImGuiColorEditFlags flags);

    // Plot
     int           PlotEx(ImGuiPlotType plot_type, const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const ImVec2& size_arg);

    // Shade functions (write over already created vertices)
     void          ShadeVertsLinearColorGradientKeepAlpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1);
     void          ShadeVertsLinearUV(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, bool clamp);
     void          ShadeVertsTransformPos(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, const ImVec2& pivot_in, float cos_a, float sin_a, const ImVec2& pivot_out);

    // Garbage collection
     void          GcCompactTransientMiscBuffers();
     void          GcCompactTransientWindowBuffers(ImGuiWindow* window);
     void          GcAwakeTransientWindowBuffers(ImGuiWindow* window);

    // Error handling, State Recovery
     bool          ErrorLog(const char* msg);
     void          ErrorRecoveryStoreState(ImGuiErrorRecoveryState* state_out);
     void          ErrorRecoveryTryToRecoverState(const ImGuiErrorRecoveryState* state_in);
     void          ErrorRecoveryTryToRecoverWindowState(const ImGuiErrorRecoveryState* state_in);
     void          ErrorCheckUsingSetCursorPosToExtendParentBoundaries();
     void          ErrorCheckEndFrameFinalizeErrorTooltip();
     bool          BeginErrorTooltip();
     void          EndErrorTooltip();

    // Debug Tools
     void          DebugAllocHook(ImGuiDebugAllocInfo* info, int frame_count, void* ptr, size_t size); // size >= 0 : alloc, size = -1 : free
     void          DebugDrawCursorPos(ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(0)<<16) | ((ImU32)(0)<<8) | ((ImU32)(255)<<0)));
     void          DebugDrawLineExtents(ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(0)<<16) | ((ImU32)(0)<<8) | ((ImU32)(255)<<0)));
     void          DebugDrawItemRect(ImU32 col = (((ImU32)(255)<<24) | ((ImU32)(0)<<16) | ((ImU32)(0)<<8) | ((ImU32)(255)<<0)));
     void          DebugTextUnformattedWithLocateItem(const char* line_begin, const char* line_end);
     void          DebugLocateItem(ImGuiID target_id);                     // Call sparingly: only 1 at the same time!
     void          DebugLocateItemOnHover(ImGuiID target_id);              // Only call on reaction to a mouse Hover: because only 1 at the same time!
     void          DebugLocateItemResolveWithLastItem();
     void          DebugBreakClearData();
     bool          DebugBreakButton(const char* label, const char* description_of_location);
     void          DebugBreakButtonTooltip(bool keyboard_only, const char* description_of_location);
     void          ShowFontAtlas(ImFontAtlas* atlas);
     void          DebugHookIdInfo(ImGuiID id, ImGuiDataType data_type, const void* data_id, const void* data_id_end);
     void          DebugNodeColumns(ImGuiOldColumns* columns);
     void          DebugNodeDockNode(ImGuiDockNode* node, const char* label);
     void          DebugNodeDrawList(ImGuiWindow* window, ImGuiViewportP* viewport, const ImDrawList* draw_list, const char* label);
     void          DebugNodeDrawCmdShowMeshAndBoundingBox(ImDrawList* out_draw_list, const ImDrawList* draw_list, const ImDrawCmd* draw_cmd, bool show_mesh, bool show_aabb);
     void          DebugNodeFont(ImFont* font);
     void          DebugNodeFontGlyph(ImFont* font, const ImFontGlyph* glyph);
     void          DebugNodeStorage(ImGuiStorage* storage, const char* label);
     void          DebugNodeTabBar(ImGuiTabBar* tab_bar, const char* label);
     void          DebugNodeTable(ImGuiTable* table);
     void          DebugNodeTableSettings(ImGuiTableSettings* settings);
     void          DebugNodeInputTextState(ImGuiInputTextState* state);
     void          DebugNodeTypingSelectState(ImGuiTypingSelectState* state);
     void          DebugNodeMultiSelectState(ImGuiMultiSelectState* state);
     void          DebugNodeWindow(ImGuiWindow* window, const char* label);
     void          DebugNodeWindowSettings(ImGuiWindowSettings* settings);
     void          DebugNodeWindowsList(ImVector<ImGuiWindow*>* windows, const char* label);
     void          DebugNodeWindowsListByBeginStackParent(ImGuiWindow** windows, int windows_size, ImGuiWindow* parent_in_begin_stack);
     void          DebugNodeViewport(ImGuiViewportP* viewport);
     void          DebugNodePlatformMonitor(ImGuiPlatformMonitor* monitor, const char* label, int idx);
     void          DebugRenderKeyboardPreview(ImDrawList* draw_list);
     void          DebugRenderViewportThumbnail(ImDrawList* draw_list, ImGuiViewportP* viewport, const ImRect& bb);

    // Obsolete functions













} // namespace ImGui

//-----------------------------------------------------------------------------
// Docking: Internal Types
//-----------------------------------------------------------------------------
// - ImGuiDockRequestType
// - ImGuiDockRequest
// - ImGuiDockPreviewData
// - ImGuiDockNodeSettings
// - ImGuiDockContext
//-----------------------------------------------------------------------------

enum ImGuiDockRequestType
{
    ImGuiDockRequestType_None = 0,
    ImGuiDockRequestType_Dock,
    ImGuiDockRequestType_Undock,
    ImGuiDockRequestType_Split                  // Split is the same as Dock but without a DockPayload
};

struct ImGuiDockRequest
{
    ImGuiDockRequestType    Type;
    ImGuiWindow*            DockTargetWindow;   // Destination/Target Window to dock into (may be a loose window or a DockNode, might be NULL in which case DockTargetNode cannot be NULL)
    ImGuiDockNode*          DockTargetNode;     // Destination/Target Node to dock into
    ImGuiWindow*            DockPayload;        // Source/Payload window to dock (may be a loose window or a DockNode), [Optional]
    ImGuiDir                DockSplitDir;
    float                   DockSplitRatio;
    bool                    DockSplitOuter;
    ImGuiWindow*            UndockTargetWindow;
    ImGuiDockNode*          UndockTargetNode;

    ImGuiDockRequest();
};

struct ImGuiDockPreviewData
{
    ImGuiDockNode   FutureNode;
    bool            IsDropAllowed;
    bool            IsCenterAvailable;
    bool            IsSidesAvailable;           // Hold your breath, grammar freaks..
    bool            IsSplitDirExplicit;         // Set when hovered the drop rect (vs. implicit SplitDir==None when hovered the window)
    ImGuiDockNode*  SplitNode;
    ImGuiDir        SplitDir;
    float           SplitRatio;
    ImRect          DropRectsDraw[4 + 1];  // May be slightly different from hit-testing drop rects used in DockNodeCalcDropRects()

    ImGuiDockPreviewData();
};

// Persistent Settings data, stored contiguously in SettingsNodes (sizeof() ~32 bytes)
struct ImGuiDockNodeSettings
{
    ImGuiID             ID;
    ImGuiID             ParentNodeId;
    ImGuiID             ParentWindowId;
    ImGuiID             SelectedTabId;
    signed char         SplitAxis;
    char                Depth;
    ImGuiDockNodeFlags  Flags;                  // NB: We save individual flags one by one in ascii format (ImGuiDockNodeFlags_SavedFlagsMask_)
    ImVec2ih            Pos;
    ImVec2ih            Size;
    ImVec2ih            SizeRef;
    ImGuiDockNodeSettings();
};

//-----------------------------------------------------------------------------
// [SECTION] ImFontAtlas internal API
//-----------------------------------------------------------------------------

// This structure is likely to evolve as we add support for incremental atlas updates.
// Conceptually this could be in ImGuiPlatformIO, but we are far from ready to make this public.
struct ImFontBuilderIO
{
    bool    (*FontBuilder_Build)(ImFontAtlas* atlas);
};

// Helper for font builder

 const ImFontBuilderIO* ImFontAtlasGetBuilderForStbTruetype();
 void      ImFontAtlasUpdateConfigDataPointers(ImFontAtlas* atlas);
 void      ImFontAtlasBuildInit(ImFontAtlas* atlas);
 void      ImFontAtlasBuildSetupFont(ImFontAtlas* atlas, ImFont* font, ImFontConfig* font_config, float ascent, float descent);
 void      ImFontAtlasBuildPackCustomRects(ImFontAtlas* atlas, void* stbrp_context_opaque);
 void      ImFontAtlasBuildFinish(ImFontAtlas* atlas);
 void      ImFontAtlasBuildRender8bppRectFromString(ImFontAtlas* atlas, int x, int y, int w, int h, const char* in_str, char in_marker_char, unsigned char in_marker_pixel_value);
 void      ImFontAtlasBuildRender32bppRectFromString(ImFontAtlas* atlas, int x, int y, int w, int h, const char* in_str, char in_marker_char, unsigned int in_marker_pixel_value);
 void      ImFontAtlasBuildMultiplyCalcLookupTable(unsigned char out_table[256], float in_multiply_factor);
 void      ImFontAtlasBuildMultiplyRectAlpha8(const unsigned char table[256], unsigned char* pixels, int x, int y, int w, int h, int stride);
 void      ImFontAtlasBuildGetOversampleFactors(const ImFontConfig* cfg, int* out_oversample_h, int* out_oversample_v);

//-----------------------------------------------------------------------------
// [SECTION] Test Engine specific hooks (imgui_test_engine)
//-----------------------------------------------------------------------------















//-----------------------------------------------------------------------------






