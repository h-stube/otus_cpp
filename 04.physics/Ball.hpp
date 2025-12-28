#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"


class Ball {
    public:
        Velocity getVelocity() const;
        void draw(Painter& painter) const;
        Point getCenter() const;
        double getRadius() const;
        double getMass() const;
        bool isBallColidable();
        void setVelocity(const Velocity& velocity);

        Ball& operator<<(Point& in_center) {center = in_center; return *this;}
        Ball& operator<<(Color& in_color) {color = in_color; return *this;}
        Ball& operator<<(double in_radius) {radius = in_radius; return *this;}
        Ball& operator<<(bool in_isCollidable) {isCollidable = in_isCollidable; return *this;}

    private:
        Velocity velocity;
        Point center;
        double radius;
        Color color;
        bool isCollidable;
    };



