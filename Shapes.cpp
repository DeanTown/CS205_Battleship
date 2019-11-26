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

/******************** Circle class ********************/

void Circle::calculateArea() {
    area = PI * radius * radius;
}

void Circle::calculatePerimeter() {
    perimeter = 2.0 * PI * radius;
}

Circle::Circle() : Shape(), radius(0) { }

Circle::Circle(double rad) : Shape() {
    setRadius(rad);
}

Circle::Circle(color b, color f) : Shape({0, 0}, b, f), radius(0) { }

Circle::Circle(double rb, double gb, double bb,
               double rf, double gf, double bf) :
        Shape(0, 0, rb, gb, bb, rf, gf, bf), radius(0) {}

Circle::Circle(double rad, color b, color f)  {
    // example without initializer list
    setCenter({0, 0});
    setBorderColor(b);
    setFillColor(f);
    setRadius(rad);
    calculateArea();
    calculatePerimeter();
}

Circle::Circle(double rad,
               double rb, double gb, double bb,
               double rf, double gf, double bf) :
        Shape(0, 0, rb, gb, bb, rf, gf, bf) {
    setRadius(rad);
}

Circle::Circle(double rad, point c) :
        Shape(c, {0, 0, 0}, {0, 0, 0}) {
    setRadius(rad);
}

Circle::Circle(double rad, int xIn, int yIn) :
        Shape(xIn, yIn, 0, 0, 0, 0, 0, 0) {
    setRadius(rad);
}

Circle::Circle(double rad, color b, color f, point c) :
        Shape(c, b, f) {
    setRadius(rad);
}

Circle::Circle(double rad,
               double rb, double gb, double bb,
               double rf, double gf, double bf,
               int xIn, int yIn) :
        Shape(xIn, yIn, rb, gb, bb, rf, gf, bf) {
    setRadius(rad);
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double rad) {
    // do not want to accept negative values for radius
    radius = (rad < 0) ? 0 : rad;
    calculateArea();
    calculatePerimeter();
}

void Circle::draw() const {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2i(center.x, center.y);
    glColor3f(border.red, border.green, border.blue);
    for (double i = 0; i < 2.0*PI+0.05; i += 2.0*PI/360.0) {
        glVertex2i(center.x + radius * cos(i),
                   center.y + radius * sin(i));
    }
    glEnd();
}

char Circle::getType() const {
    return 'c';
}

bool Circle::isOverlapping(const point &p) const {
    return distance(p, center) <= radius;
}

bool Circle::isOverlappingCircle(const Circle &c) const {
    return distance(center, c.center) <= radius + c.radius;
}

bool Circle::isOverlappingLineSeg(const point &p1, const point &p2) const {
    if (p1.x == p2.x) {
        // vertical line
        if (p1.x >= center.x-radius && p1.x <= center.x+radius) {
            if ((p1.y < center.y && p2.y > center.y) ||
                (p1.y > center.y && p2.y < center.y)) {
                return true;
            }
        }
        return false;
    }
    if (p1.y == p2.y) {
        // horizontal line
        if (p1.y >= center.y-radius && p1.y <= center.y+radius) {
            if ((p1.x < center.x && p2.x > center.x) ||
                (p1.x > center.x && p2.x < center.x)) {
                return true;
            }
        }
        return false;
    }
    return false;
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

Tangle::Tangle(double l, double w, point c, point boardCell) {
    setDimensions(l, w);
    setCenter(c);
    this->boardCell = boardCell;
}

double Tangle::getLength() const {
    return length;
}

double Tangle::getWidth() const {
    return width;
}

point Tangle::getBoardCell() const {
    return boardCell;
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

    glLineWidth((GLfloat)1.0);
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
/*
Tangle* Tangle::drag(Tangle *sqr, point *mouse)
{
    sqr->center.x = mouse->x - 0.1;
    sqr->pts[0].y = mouse->y - 0.1;
    sqr->pts[1].x = mouse->x + 0.1;
    sqr->pts[1].y = mouse->y - 0.1;

    sqr->pts[3].x = mouse->x - 0.1;
    sqr->pts[3].y = mouse->y + 0.1;

    sqr->pts[2].x = mouse->x + 0.1;
    sqr->pts[2].y = mouse->y + 0.1;

    return sqr;
}
*/
//bool isOverlappingTangle(const std::unique_ptr<Shape> &s, const Tangle &r) {
//    if (s->getType() == 't') {
//        return r.isOverlappingTangle(dynamic_cast<Tangle&>(*s));
//    } else {
//        return isOverlappingTangleCircle(r, dynamic_cast<Circle&>(*s));
//    }
//}

//
///******************** Triangle class ********************/
//
//Triangle::Triangle() : Shape(), length(0), width(0) { }
//
//Triangle::Triangle(double l, double w) : Shape() {
//    setDimensions(l, w);
//}
//
//Triangle::Triangle(double l, double w, color b, color f, point c) : Shape(c, b, f) {
//    setDimensions(l, w);
//}
//
//Triangle::Triangle(double l, double w, point c, point boardCell) {
//    setDimensions(l, w);
//    setCenter(c);
//    this->boardCell = boardCell;
//}
//
//double Triangle::getLength() const {
//    return length;
//}
//
//double Triangle::getWidth() const {
//    return width;
//}
//
//point Triangle::getBoardCell() const {
//    return boardCell;
//}
//
//void Triangle::setDimensions(double l, double w) {
//    // we don't want to accept negative values for length and width
//    length = (l < 0) ? 0 : l;
//    width = (w < 0) ? 0 : w;
//    // update area and perimeter
//
//}
//
//void Triangle::draw() const {
//    // draw fill
//    glColor3f(fill.red, fill.green, fill.blue);
//    glBegin(GL_TRIANGLES);
//
//    glVertex2f(300.0,210.0);
//    glVertex2f(340.0,215.0);
//    glVertex2f(320.0,250.0);
//    glEnd();
//}
//
//bool Triangle::isOverlapping(const point &p) const {
//    return (p.x >= center.x-(width/2.0) && // left side
//            p.x <= center.x+(width/2.0) && // right side
//            p.y >= center.y-(length/2.0) && // top
//            p.y <= center.y+(length/2.0)); // bottom
//}
//
//bool Triangle::isOverlappingTriangle(const Triangle &trian) const {
//    return !(center.x+(width/2.0) < trian.center.x-(trian.width/2.0) || // self is left of rectangle
//                                                                        trian.center.x+(trian.width/2.0) < center.x-(width/2.0) || // rectangle is left of self
//             center.y-(length/2.0) > trian.center.y+(trian.length/2.0) || // self is below rectangle
//                                                                          trian.center.y-(trian.length/2.0) > center.y+(length/2.0)); // rectangle is below self
//}
//point Triangle::mouse(int x, int y)
//{
//    int windowWidth = 400, windowHeight = 400;
//    return point(float(x)/windowWidth, 1.0 - float(y)/windowHeight);
//}