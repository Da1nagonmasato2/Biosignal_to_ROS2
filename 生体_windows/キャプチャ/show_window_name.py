import win32gui

def enum_windows(hwnd, results):
    title = win32gui.GetWindowText(hwnd)
    if title:
        results.append(title)

titles = []
win32gui.EnumWindows(enum_windows, titles)
for t in titles:
    print(t)
