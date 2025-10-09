#include "platform.h"

#include "win.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE:
    SetTimer(hwnd, 1, 50, NULL);
    init_engine();
    return 0;
  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BG_COLOR));
    float width = rect.right - rect.left;
    float height = rect.bottom - rect.top;

    HPEN hPen = CreatePen(PS_SOLID, 1, COLOR);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    void draw_line(const ScreenPoint *sp1, const ScreenPoint *sp2) {
      MoveToEx(hdc, sp1->coordinates[0], sp1->coordinates[1], NULL);
      LineTo(hdc, sp2->coordinates[0], sp2->coordinates[1]);
    };

    Screen screen = {.width = width, .height = height, .draw_line = &draw_line};

    render(screen);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    EndPaint(hwnd, &ps);
    return 0;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_TIMER:
    tic();

    InvalidateRect(hwnd, NULL, TRUE);
    return 0;

  case WM_KEYDOWN:
    return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  const char CLASS_NAME[] = "C3DGraphicEngine";

  WNDCLASS wc = {0};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0, CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
                             WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  MSG msg = {0};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}