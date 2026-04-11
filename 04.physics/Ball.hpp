#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include <istream>


class Ball {
    public:
        Velocity getVelocity() const;
        void draw(Painter& painter) const;
        Point getCenter() const;
        double getRadius() const;
        double getMass() const;
        bool isBallColidable();
        void setVelocity(const Velocity& velocity);
        void setCenter(const Point& center);

        friend std::istream& operator>>(std::istream& stream, Ball& ball);
    private:
        Velocity velocity;
        Point center;
        Color color;
        double radius{0.0};
        bool isCollidable{false};
    };

inline std::istream& operator>>(std::istream& stream, Ball& ball) {
    Point centerCoords;
    Point velocityVectorCoords;
    
    stream >> centerCoords >> velocityVectorCoords;
    stream >> ball.color;
    stream >> ball.radius;
    stream >> std::boolalpha >> ball.isCollidable;
    
    ball.center = centerCoords;
    ball.velocity.setVector(velocityVectorCoords);
    
    return stream;
}


