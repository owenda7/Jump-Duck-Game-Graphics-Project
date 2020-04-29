#ifndef OA_FINAL_PROJECT_GRAPHICS_RECT_H
#define OA_FINAL_PROJECT_GRAPHICS_RECT_H

#include "shape.h"

class Rect : public Shape {
private:
    double width{};
    double height{};
public:
    /* Constructors */
    Rect();
    explicit Rect(double height, double width);
    explicit Rect(color fill);
    explicit Rect(point2D center);
    Rect(color fill, point2D center);
    Rect(double red, double green, double blue, double alpha);
    Rect(double red, double green, double blue, double alpha, double x, double y);
    Rect(color fill, double x, double y);
    Rect(double red, double green, double blue, double alpha, point2D center);
    Rect(point2D center, double height, double width);
    Rect(color fill, point2D center, double height, double width);
    Rect(double red, double green, double blue, double alpha, double x, double y, double height, double width);
    Rect(color fill, double x, double y, double height, double width);
    Rect(double red, double green, double blue, double alpha, point2D center, double height, double width);

    /* Destructor */
    virtual ~Rect() = default;

    /* Getter */
    double getHeight() const;
    double getWidth() const;

    /* Setter */
    void setHeight(double h);
    void changeHeight(double delta);
    void setWidth(double w);
    void changeWidth(double delta);

    /* Draw */
    void draw() const override;

};

#endif //OA_FINAL_PROJECT_GRAPHICS_RECT_H
