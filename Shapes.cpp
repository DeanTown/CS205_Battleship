//
// Created by Hannah Meharg on 11/19/19.
//


#include "graphics.h"
#include "Shapes.h"
#include <cmath>

/******************** point struct ********************/

point::point() : x(0), y(0) { }

point::point(int xIn, int yIn) : x(xIn), y(yIn) { }

point::point(double xIn, double yIn) {
    x = int(xIn);
    y = int(yIn);
}

double distance(const point &p1, const point &p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

/******************** Shape class ********************/

Shape::Shape() : area(0), perimeter(0), center({0, 0}),
                 fill({0, 0, 0}), border({0, 0, 0}) {
    // color defaults to black
}

Shape::Shape(point c, color b, color f) : area(0), perimeter(0),
                                          center(c),
                                          border(b), fill(f) { }

Shape::Shape(int xIn, int yIn,
             double rb, double gb, double bb,
             double rf, double gf, double bf) : area(0),
                                                perimeter(0),
                                                center({xIn, yIn}),
                                                border({rb, gb, bb}),
                                                fill({rf, gf, bf}) { }

point Shape::getCenter() const {
    return center;
}

color Shape::getBorderColor() const {
    return border;
}

color Shape::getFillColor() const {
    return fill;
}

double Shape::getArea() const {
    return area;
}

double Shape::getPerimeter() const {
    return perimeter;
}

void Shape::setCenter(point c) {
    center = c;
}

void Shape::setCenter(int xIn, int yIn) {
    center = {xIn, yIn};
}

void Shape::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Shape::setBorderColor(color b) {
    border = b;
}

void Shape::setBorderColor(double r, double g, double b) {
    border = {r, g, b};
}

void Shape::setFillColor(color f) {
    fill = f;
}

void Shape::setFillColor(double r, double g, double b) {
    fill = {r, g, b};
}


/******************** Tangle class ********************/

void Tangle::calculateArea() {
    area = length * width;
}

void Tangle::calculatePerimeter() {
    perimeter = 2.0 * length + 2.0 * width;
}

Tangle::Tangle() : Shape(), length(0), width(0) { }

Tangle::Tangle(double l, double w) : Shape() {
    setDimensions(l, w);
}

Tangle::Tangle(double l, double w, color b, color f, point c) : Shape(c, b, f) {
    setDimensions(l, w);
}

double Tangle::getLength() const {
    return length;
}

double Tangle::getWidth() const {
    return width;
}

void Tangle::setDimensions(double l, double w) {
    // we don't want to accept negative values for length and width
    length = (l < 0) ? 0 : l;
    width = (w < 0) ? 0 : w;
    // update area and perimeter
    calculateArea();
    calculatePerimeter();
}

void Tangle::draw() const {
    // draw fill
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    // top right
    glVertex2i(center.x+(width/2.0), center.y-(length/2.0));
    // bottom right
    glVertex2i(center.x+(width/2.0), center.y+(length/2.0));
    // bottom left
    glVertex2i(center.x-(width/2.0), center.y+(length/2.0));
    glEnd();

    glLineWidth((GLfloat)5.0);
    // draw border
    glColor3f(border.red, border.green, border.blue);
    glBegin(GL_LINE_STRIP);
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    // top right
    glVertex2i(center.x+(width/2.0), center.y-(length/2.0));
    // bottom right
    glVertex2i(center.x+(width/2.0), center.y+(length/2.0));
    // bottom left
    glVertex2i(center.x-(width/2.0), center.y+(length/2.0));
    // top left
    glVertex2i(center.x-(width/2.0), center.y-(length/2.0));
    glEnd();
}

char Tangle::getType() const {
    return 't';
}

bool Tangle::isOverlapping(const point &p) const {
    return (p.x >= center.x-(width/2.0) && // left side
            p.x <= center.x+(width/2.0) && // right side
            p.y >= center.y-(length/2.0) && // top
            p.y <= center.y+(length/2.0)); // bottom
}

bool Tangle::isOverlappingTangle(const Tangle &rectangle) const {
    return !(center.x+(width/2.0) < rectangle.center.x-(rectangle.width/2.0) || // self is left of rectangle
             rectangle.center.x+(rectangle.width/2.0) < center.x-(width/2.0) || // rectangle is left of self
             center.y-(length/2.0) > rectangle.center.y+(rectangle.length/2.0) || // self is below rectangle
             rectangle.center.y-(rectangle.length/2.0) > center.y+(length/2.0)); // rectangle is below self
}
point Tangle::mouse(int x, int y)
{
    int windowWidth = 400, windowHeight = 400;
    return point(float(x)/windowWidth, 1.0 - float(y)/windowHeight);
}



//bool isOverlappingTangle(const std::unique_ptr<Shape> &s, const Tangle &r) {
//    if (s->getType() == 't') {
//        return r.isOverlappingTangle(dynamic_cast<Tangle&>(*s));
//    } else {
//        return isOverlappingTangleCircle(r, dynamic_cast<Circle&>(*s));
//    }
//}
