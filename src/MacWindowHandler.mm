#import <AppKit/AppKit.h>
#import <QWidget>

void configureMacWindow(QWidget* qtWindow) {
    // Get NSWindow handle from Qt window
    NSView* nsView = (__bridge NSView*)reinterpret_cast<void*>(qtWindow->winId());
    NSWindow* nsWindow = [nsView window];

    // Configure unified toolbar appearance
    [nsWindow setTitleVisibility:NSWindowTitleHidden];
    [nsWindow setTitlebarAppearsTransparent:YES];
    nsWindow.styleMask |= NSWindowStyleMaskFullSizeContentView;

    // Create native toolbar (optional)
    NSToolbar* toolbar = [[NSToolbar alloc] initWithIdentifier:@"mainToolbar"];
    [toolbar setShowsBaselineSeparator:NO];
    [nsWindow setToolbar:toolbar];
}