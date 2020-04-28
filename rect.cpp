#include "rect.h"
#include "game.h"

Rect::Rect() : Shape(), height(0), width(0) {
}

Rect::Rect(double height, double width) : Shape() {
    setHeight(height);
    setWidth(width);
}

Rect::Rect(color fill) : Shape(fill), height(0), width(0) {
}

Rect::Rect(point2D center) : Shape(center), height(0), width(0) {
}

Rect::Rect(color fill, point2D center) : Shape(fill, center), height(0), width(0) {
}

Rect::Rect(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), height(0), width(0) {
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), height(0), width(0) {
}

Rect::Rect(color fill, double x, double y) : Shape(fill, x, y), height(0), width(0) {
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), height(0), width(0) {
}


Rect::Rect(point2D center, double height, double width) : Shape(center) {
    setHeight(height);
    setWidth(width);
}

Rect::Rect(color fill, point2D center, double height, double width) : Shape(fill, center) {
    setHeight(height);
    setWidth(width);
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y, double height, double width) : Shape(red, green, blue, alpha, x, y) {
    setHeight(height);
    setWidth(width);
}

Rect::Rect(color fill, double x, double y, double height, double width) : Shape(fill, x, y) {
    setHeight(height);
    setWidth(width);
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center, double height, double width) : Shape(red, green, blue, alpha, center) {
    setHeight(height);
    setWidth(width);
}

double Rect::getHeight() const {
    return height;
}

double Rect::getWidth() const {
    return width;
}

void Rect::setHeight(double h) {
    if (h < 0) {
        h = 0;
    }
    height = h;
}

void Rect::changeHeight(double delta) {
    setHeight(height + delta);
}

void Rect::setWidth(double w) {
    if (w < 0) {
        w = 0;
    }
    width = w;
}

void Rect::changeWidth(double delta) {
    setWidth(width + delta);
}

void Rect::draw() const {
    // Set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // Draw Rect as Triangle Fan
    glBegin(GL_QUADS);
    // Draw four verticies from center
    glVertex2i(center.x - width / 2, center.y + height / 2);
    glVertex2i(center.x + width / 2, center.y + height / 2);
    glVertex2i(center.x + width / 2, center.y - height / 2);
    glVertex2i(center.x - width / 2, center.y - height / 2);
    // End Quadrilateral
    glEnd();
}
