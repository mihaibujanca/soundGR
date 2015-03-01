typedef short Int16;
#include <iostream>
#include "sampler.cpp"

#include <signal.h>
#include <X11/Xlib.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

const int MID_Y = 400;
const int LEFT_X = 200;
const int RIGHT_X = 1200;

void mouseClick(int button)
{
    Display *display = XOpenDisplay(NULL);

    XEvent event;

    if(display == NULL)
    {
        fprintf(stderr, "Error !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    XCloseDisplay(display);
}

void userup(int s) {
    
    int x , y;
    x = LEFT_X;
    y = MID_Y;
    
    Display *display = XOpenDisplay(0);

    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    mouseClick(Button1);
    XFlush(display);
    XCloseDisplay(display);
}
void userdown(int s) {
    int x , y;
    x = RIGHT_X;
    y = MID_Y;
    
    Display *display = XOpenDisplay(0);

    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    mouseClick(Button1);
    XFlush(display);
    XCloseDisplay(display);

}

int main() {
    signal(SIGUSR1, userup);
    signal(SIGUSR2, userdown);
    
    if (!KairosSampler::isAvailable()) {
        // error...
        cout << "ERROR" << endl;
    }

    KairosSampler sampler;

    sampler.start();

    char c;
    while (cin >> c) ;
    
    sampler.stop();

//    const sf::SoundBuffer& buffer = sampler.getBuffer();
//    buffer.saveToFile("my_record.ogg");

    return 0;
}
 