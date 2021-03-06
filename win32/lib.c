#define _WIN32_IE 0x0300
#define _WIN32_WINNT 0x0501
#define WINVER _WIN32_WINNT

#include <core.h>
#include <ogl/oglstd.h>



char *_ConvertUTF8(char *utf8, long oldw) {
    if (utf8) {
        long size = (strlen(utf8) + 1) * 4;
        LPWSTR wide = calloc(size, sizeof(*wide));

        MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide, size);
        if (!oldw)
            return (char*)wide;
        else {
            utf8 = calloc((size = (wcslen(wide) + 1) * 4), sizeof(*utf8));
            WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wide, -1,
                                utf8, size - 1, "#", 0);
            free(wide);
        }
    }
    return utf8;
}



void lRestartEngine(ENGD *engd) {
    intptr_t *data;

    cEngineCallback(engd, ECB_GUSR, (intptr_t)&data);
    data[0] = 0;
}



void lShowMainWindow(ENGD *engd, long show) {
    intptr_t *data;

    cEngineCallback(engd, ECB_GUSR, (intptr_t)&data);
    ShowWindow((HWND)data[0], (show)? SW_SHOW : SW_HIDE);
}



char *lLoadFile(char *name, long *size) {
    static long oldw = 2;
    char *retn;
    DWORD flen;
    HANDLE file;

    if (oldw == 2)
        oldw = ((GetVersion() & 0xFF) < 5)? 1 : 0;

    if (oldw) {
        name = _ConvertUTF8(name, oldw);
        file = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, 0,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    }
    else {
        retn = malloc(strlen(name) + 5);
        retn[0] = retn[1] = retn[3] = '\\';
        retn[2] = '?';
        strcpy(retn + 4, name);
        for (flen = 0; retn[flen]; flen++)
            if (retn[flen] == '/')
                retn[flen] = '\\';
        name = _ConvertUTF8(retn, oldw);
        file = CreateFileW((LPWSTR)name, GENERIC_READ, FILE_SHARE_READ, 0,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        free(retn);
    }
    free(name);
    retn = 0;
    if (file != INVALID_HANDLE_VALUE) {
        flen = GetFileSize(file, 0);
        retn = malloc(flen + 1);
        ReadFile(file, retn, flen, &flen, 0);
        CloseHandle(file);
        retn[flen] = '\0';
        if (size)
            *size = flen;
    }
    return retn;
}



void lMakeThread(void *thrd) {
    DWORD retn;

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cThrdFunc, thrd, 0, &retn);
}



long lPickSemaphore(SEMD *drop, SEMD *pick, SEM_TYPE mask) {
    HANDLE *dobj = (typeof(dobj))drop + 1, *pobj = (typeof(pobj))pick + 1;
    long iter;

    for (iter = 0; iter < (long)dobj[-1]; iter++)
        if (mask & (1 << iter))
            ResetEvent(dobj[iter]);

    for (iter = 0; iter < (long)pobj[-1]; iter++)
        if (mask & (1 << iter))
            SetEvent(pobj[iter]);

    return TRUE;
}



SEM_TYPE lWaitSemaphore(SEMD *wait, SEM_TYPE mask) {
    HANDLE objs[MAXIMUM_WAIT_OBJECTS], *iter, *list = (typeof(list))wait + 1;
    SEM_TYPE retn, temp;
    long indx;

    if (mask) {
        indx = 0;
        iter = objs;
        retn = mask &= (1 << (long)list[-1]) - 1;
        while (retn) {
            *iter++ = list[temp = cFindBit(retn)];
            retn &= ~(1 << temp);
            indx++;
        }
        WaitForMultipleObjects(indx, objs, TRUE, INFINITE);
        retn = mask;
    }
    else {
        retn = WaitForMultipleObjects((long)list[-1], list, FALSE, INFINITE);
        retn = (retn < MAXIMUM_WAIT_OBJECTS)? 1 << retn : 0;
    }
    return retn;
}



void lFreeSemaphore(SEMD **retn, long nthr) {
    HANDLE **list = (typeof(list))retn;
    long iter;

    if (list) {
        for (iter = 1; iter <= nthr; iter++)
            CloseHandle((*list)[iter]);
        free(*list);
        *list = 0;
    }
}



void lMakeSemaphore(SEMD **retn, long nthr, SEM_TYPE mask) {
    HANDLE **list = (typeof(list))retn;
    long iter;

    if (list) {
        *list = malloc((nthr + 1) * sizeof(**list));
        (*list)[0] = (HANDLE)nthr;
        for (iter = 0; iter < nthr; iter++)
            (*list)[iter + 1] = CreateEvent(0, TRUE, (mask >> iter) & 1, 0);
    }
}



long lCountCPUs() {
    SYSTEM_INFO syin = {};

    GetSystemInfo(&syin);
    return min(MAXIMUM_WAIT_OBJECTS, max(1, syin.dwNumberOfProcessors));
}



uint64_t lTimeFunc() {
    static int32_t lock = 0;
    static int32_t hbit = 0;
    static int32_t lbit = 0;
    int64_t retn;

    /// yes, this is a spinlock, requiring at least a 80486
    while (__sync_fetch_and_or(&lock, 1));

    retn = lbit;
    lbit = GetTickCount();
    if ((retn < 0) && (lbit >= 0))
        hbit++;
    retn = ((uint64_t)lbit & 0xFFFFFFFF) | ((uint64_t)hbit << 32);

    /// releasing the lock
    lock = 0;
    return retn;
}



LRESULT APIENTRY WindowProc(HWND hWnd, UINT uMsg, WPARAM wPrm, LPARAM lPrm) {
    switch (uMsg) {
        case WM_CREATE:
            SetWindowLongPtr(hWnd, GWLP_USERDATA,
                            (LONG_PTR)((CREATESTRUCT*)lPrm)->lpCreateParams);
            SetTimer(hWnd, 1, 1000, 0);
            return 0;


        case WM_KEYDOWN:
            if (wPrm == VK_ESCAPE)
        case WM_CLOSE:
                cEngineCallback((ENGD*)GetWindowLongPtr(hWnd, GWLP_USERDATA),
                                 ECB_QUIT, ~0);
            return 0;


        case WM_LBUTTONDOWN:
            SetCapture(hWnd);
            return 0;


        case WM_LBUTTONUP:
            ReleaseCapture();
            return 0;


        case WM_TIMER: {
            char fout[64];

            cOutputFPS((ENGD*)GetWindowLongPtr(hWnd, GWLP_USERDATA), fout);
            SetWindowText(hWnd, fout);
            printf("%s\n", fout);
            return 0;
        }

        case WM_DESTROY:
            KillTimer(hWnd, 1);
            PostQuitMessage(0);
            return 0;


        default:
            return DefWindowProc(hWnd, uMsg, wPrm, lPrm);
    }
}



BOOL APIENTRY ULWstub(HWND hwnd, HDC hdst, POINT *pdst, SIZE *size, HDC hsrc,
                      POINT *psrc, COLORREF ckey, BGRA *bptr, DWORD flgs) {
    enum {MAX_RECT = 2000};
    long x, y, xpos, ypos;
    HRGN retn, temp;
    struct {
        RGNDATAHEADER head;
        RECT rect[MAX_RECT];
    } rgns;

    /// manual stack checking
    ((DWORD*)rgns.rect)[7 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[6 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[5 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[4 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[3 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[2 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[1 * 1024] = 0; asm volatile("" ::: "memory");
    ((DWORD*)rgns.rect)[0 * 1024] = 0; asm volatile("" ::: "memory");

    if (flgs != ULW_OPAQUE) {
        retn = CreateRectRgn(0, 0, 0, 0);
        rgns.head = (RGNDATAHEADER){sizeof(rgns.head), RDH_RECTANGLES,
                                    0, 0, {0, 0, size->cx, size->cy}};
        for (y = size->cy - 1; y >= 0; y--) {
            ypos = (psrc->y < 0)? y : size->cy - 1 - y;
            for (xpos = 0, x = size->cx - 1; x >= 0; x--) {
                if (bptr[size->cx * y + x].chnl[3] && !xpos)
                    xpos = x + 1;
                else if ((!bptr[size->cx * y + x].chnl[3] || !x) && xpos) {
                    rgns.rect[rgns.head.nCount++] =
                        (RECT){(!x && bptr[size->cx * y].chnl[3])? 0 : x + 1,
                                 ypos, xpos, ypos + 1};
                    xpos = 0;
                }
                if (!(x | y) || (rgns.head.nCount >= MAX_RECT)) {
                    rgns.head.nRgnSize = rgns.head.nCount * sizeof(RECT);
                    temp = ExtCreateRegion(0, rgns.head.dwSize +
                                              rgns.head.nRgnSize,
                                          (RGNDATA*)&rgns);
                    CombineRgn(temp, temp, retn, RGN_OR);
                    DeleteObject(retn);
                    retn = temp;
                    rgns.head.nCount = 0;
                }
            }
        }
        SetWindowRgn(hwnd, retn, TRUE);
    }
    BitBlt(hdst, 0, 0, size->cx, size->cy, hsrc, 0, 0, SRCCOPY);
    return TRUE;
}



void lRunMainLoop(ENGD *engd, long xpos, long ypos, long xdim, long ydim,
                  BGRA **bptr, intptr_t *data, uint32_t flgs) {
    enum {EXT_ATTR = WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED};
    BLENDFUNCTION bstr = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    WNDCLASSEX wndc = {sizeof(wndc), CS_HREDRAW | CS_VREDRAW, WindowProc,
                       0, 0, 0, 0, LoadCursor(0, IDC_HAND), 0, 0, " ", 0};
    PIXELFORMATDESCRIPTOR ppfd = {sizeof(ppfd), 1, PFD_SUPPORT_OPENGL |
                                  PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
                                  PFD_TYPE_RGBA, 32};
    BITMAPINFO bmpi = {{sizeof(bmpi.bmiHeader), 0, 0,
                        1, 8 * sizeof(BGRA), BI_RGB}};
    struct { /// DWM_BLURBEHIND from DWM API (Vista and later)
        DWORD dwFlags;
        BOOL  fEnable;     /// dwFlags | 0x01 (DWM_BB_ENABLE)
        HRGN  hRgnBlur;    /// dwFlags | 0x02 (DWM_BB_BLURREGION)
        BOOL  fTransition; /// dwFlags | 0x04 (DWM_BB_TRANSITIONONMAXIMIZED)
    } blur = {0x03, TRUE, CreateRectRgn(0, 0, 1, 1), TRUE};
    SIZE dims = {xdim - xpos, ydim - ypos};
    POINT cpos, mpos, zpos = {};
    MSG pmsg = {};

    BLENDFUNCTION *bfun;
    BOOL APIENTRY (*ULW)(HWND, HDC, POINT*, SIZE*, HDC, POINT*,
                         COLORREF, BLENDFUNCTION*, DWORD) = 0;
    BOOL APIENTRY (*SLW)(HWND, COLORREF, BYTE, DWORD) = 0;
    HRESULT APIENTRY (*EBW)(HWND, typeof(blur)*) = 0;
    HRESULT APIENTRY (*ICE)(BOOL*) = 0;
    HINSTANCE husr, hdwm;
    UINT opts, attr;
    HDC devc, mwdc;
    HBITMAP hdib;
    HGLRC mwrc;
    HWND hwnd;
    BOOL comp;

    mwrc = 0;
    devc = CreateCompatibleDC(0);
    bmpi.bmiHeader.biWidth = dims.cx;
    bmpi.bmiHeader.biHeight = (~flgs & COM_RGPU)? -dims.cy : dims.cy;
    hdib = CreateDIBSection(devc, &bmpi, DIB_RGB_COLORS, (void*)bptr, 0, 0);
    SelectObject(devc, hdib);

    if ((hdwm = LoadLibrary("dwmapi")))
        EBW = (typeof(EBW))GetProcAddress(hdwm, "DwmEnableBlurBehindWindow");

    bfun = &bstr;
    opts = ULW_ALPHA;
    attr = EXT_ATTR;
    mpos = (POINT){xpos, ypos};

    husr = LoadLibrary("user32");
    if ((flgs & COM_OPAQ) || (flgs & WIN_IRGN)
    || !(ULW = (typeof(ULW))GetProcAddress(husr, "UpdateLayeredWindow"))) {
        bfun = (typeof(bfun))*bptr;
        zpos.y = bmpi.bmiHeader.biHeight;
        ULW = (typeof(ULW))ULWstub;
        attr &= ~WS_EX_LAYERED;
        if (flgs & COM_OPAQ)
            opts = ULW_OPAQUE;
    }
    RegisterClassEx(&wndc);
    hwnd = CreateWindowEx(attr, wndc.lpszClassName, 0, WS_POPUP | WS_VISIBLE,
                          0, 0, 0, 0, 0, 0, wndc.hInstance, engd);
    data[0] = (intptr_t)hwnd;
    mwdc = GetDC(hwnd);

    if (EBW) {
        comp = FALSE;
        ICE = (typeof(ICE))GetProcAddress(hdwm, "DwmIsCompositionEnabled");
        /// if there`s DWM, there absolutely have to be layered windows
        SLW = (typeof(SLW))GetProcAddress(husr, "SetLayeredWindowAttributes");
        ICE(&comp);
        attr = GetVersion();
        /// major 6 minor 1 is Win7; in newer versions ICE() is lying to us
        if (!comp && (MAKEWORD(HIBYTE(attr), LOBYTE(attr)) <= 0x0601))
            EBW = 0;
        else {
            /// does nothing visible to the window,
            /// but enables input transparency!
            SLW(hwnd, 0x000000, 0xFF, 2 /** 2 == LWA_ALPHA **/);
            EBW(hwnd, &blur);
        }
    }
    if (flgs & COM_RGPU) {
        ppfd.iLayerType = PFD_MAIN_PLANE;
        SetPixelFormat(mwdc, ChoosePixelFormat(mwdc, &ppfd), &ppfd);
        wglMakeCurrent(mwdc, mwrc = wglCreateContext(mwdc));
    }
    /// "+1" is a dirty hack to not let Windows consider us fullscreen if OGL
    /// is active: all sorts of weird things happen to fullscreen OGL windows
    /// when they are DWM + layered, at least on Intel HD 3000 + Vista / Win7
    SetWindowPos(hwnd, 0, mpos.x, mpos.y, dims.cx, dims.cy + ((EBW)? 1 : 0),
                 SWP_NOZORDER | SWP_NOACTIVATE);
    lShowMainWindow(engd, flgs & COM_SHOW);
    while (data[0]) {
        if (PeekMessage(&pmsg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&pmsg);
            DispatchMessage(&pmsg);
            continue;
        }
        GetCursorPos(&cpos);
        ScreenToClient(hwnd, &cpos);
        attr = ((GetActiveWindow() == hwnd)?    UFR_MOUS : 0)
             | ((GetAsyncKeyState(VK_LBUTTON))? UFR_LBTN : 0)
             | ((GetAsyncKeyState(VK_MBUTTON))? UFR_MBTN : 0)
             | ((GetAsyncKeyState(VK_RBUTTON))? UFR_RBTN : 0)
             | ((GetAsyncKeyState(VK_UP     ))? UFR_PL1W : 0)
             | ((GetAsyncKeyState(VK_DOWN   ))? UFR_PL1S : 0)
             | ((GetAsyncKeyState(VK_LEFT   ))? UFR_PL1A : 0)
             | ((GetAsyncKeyState(VK_RIGHT  ))? UFR_PL1D : 0)
             | ((GetAsyncKeyState('W'       ))? UFR_PL2W : 0)
             | ((GetAsyncKeyState('S'       ))? UFR_PL2S : 0)
             | ((GetAsyncKeyState('A'       ))? UFR_PL2A : 0)
             | ((GetAsyncKeyState('D'       ))? UFR_PL2D : 0);
        attr = cPrepareFrame(engd, cpos.x, cpos.y, attr);
        if (attr & PFR_SKIP)
            Sleep(1);
        if (!IsWindow(hwnd))
            break;
        if (attr & PFR_HALT)
            continue;
        if (~flgs & COM_RGPU)
            BitBlt(devc, 0, 0, dims.cx, dims.cy, mwdc, 0, 0, BLACKNESS);
        cOutputFrame(engd, !EBW);
        if (!EBW)
            ULW(hwnd, mwdc, &mpos, &dims, devc, &zpos, 0, bfun, opts);
        else {
            if (flgs & COM_RGPU)
                SwapBuffers(mwdc);
            else
                BitBlt(mwdc, 0, 0, dims.cx, dims.cy, devc, 0, 0, SRCCOPY);
            SetWindowLongPtr(hwnd, GWL_EXSTYLE, (attr & PFR_PICK)? EXT_ATTR :
                                               WS_EX_TRANSPARENT | EXT_ATTR);
        }
    }
    cDeallocFrame(engd, !EBW);
    if (flgs & COM_RGPU) {
        wglMakeCurrent(0, 0);
        wglDeleteContext(mwrc);
    }
    KillTimer(hwnd, 1);
    ReleaseDC(hwnd, mwdc);
    DestroyWindow(hwnd);
    DeleteDC(mwdc);
    DeleteDC(devc);
    DeleteObject(hdib);
    DeleteObject(blur.hRgnBlur);
    /// mandatory: we are a library, not an application
    UnregisterClass(wndc.lpszClassName, wndc.hInstance);
    /// finally, we need to purge the message queue, as it may be reused,
    /// and nobody wants garbage messages for windows that are long gone
    while (PeekMessage(&pmsg, 0, 0, 0, PM_REMOVE));
    FreeLibrary(husr);
    FreeLibrary(hdwm);
}
