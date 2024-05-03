//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
//#include <unistd.h>
#include "window.h"

using namespace std;

// constructor
//Xwindow::Xwindow(int width, int height) {
//
//  d = XOpenDisplay(NULL); // returns pointer to Display server, or NULL as default
//  if (d == NULL) {
//    cerr << "Cannot open display" << endl;
//    exit(1);
//  }
//  s = DefaultScreen(d); // retrieve the default screen number for the given X server connection
//  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
//                          BlackPixel(d, s), WhitePixel(d, s)); // w stores ID of created window
//                          // initial coordinates (10, 10), width, height, border width, border color
//  XSelectInput(d, w, ExposureMask | KeyPressMask);
//  XMapRaised(d, w);
//
//  Pixmap pix = XCreatePixmap(d,w,width,
//        height,DefaultDepth(d,DefaultScreen(d))); // w is the "drawable" associated with the Pixmap
//  gc = XCreateGC(d, pix, 0,(XGCValues *)0);
//
//  XFlush(d);
//  XFlush(d);
//
//  // Set up colours.
//  XColor xcolour;
//  Colormap cmap;
//  char color_vals[5][10]={"white", "black", "red", "green", "blue"};
//
//  cmap=DefaultColormap(d,DefaultScreen(d));
//  for(int i=0; i < 5; ++i) {
//      XParseColor(d,cmap,color_vals[i],&xcolour);
//      XAllocColor(d,cmap,&xcolour);
//      colours[i]=xcolour.pixel;
//  }
//
//  XSetForeground(d,gc,colours[Black]);
//
//  // Make window non-resizeable.
//  XSizeHints hints;
//  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
//  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
//  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
//  XSetNormalHints(d, w, &hints);
//
//  XSynchronize(d,True);
//
//  usleep(1000);
//}
//
//// destructor
//Xwindow::~Xwindow() {
//  XFreeGC(d, gc);
//  XCloseDisplay(d);
//}
//
//// method
//// draws a rectangle (filled with Black) on window "w" with the graphics content "gc" 
//// at (x, y) with "width" and "height"
//void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
//  XSetForeground(d, gc, colours[colour]);
//  XFillRectangle(d, w, gc, x, y, width, height);
//  XSetForeground(d, gc, colours[Black]);
//}
//
//// method
//// draws a string with message "msg" at position (x, y) on window "w"
//void Xwindow::drawString(int x, int y, string msg) {
//  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
//}
//
