#include "Ball.hpp"
#include <cmath>

#define PI 3.14159265358979323846

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(this->center, this->radius, Color(255,255,0));
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    this->center = center;
}

/**
 * @brief Возвращает центр обьекта
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return center;
}

/**
 * @brief Возвращает радиус объекта
 * @return радиус обьекта
 */
double Ball::getRadius() const {
    return radius;
}

/**
 * @brief Устанавливает радиус обьекта
  */
void Ball::setRadius(const double radius) {
    this->radius = radius;
}
/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return PI * std::pow(this->radius, 3) * 4. / 3.;
}

/**
 * @brief Устанавливает параметр шара, отвечающий за его способность
 *  сталкиваться с другими шарами 
  */
void Ball::setCollidability(bool isCollidable){
    this->isCollidable = isCollidable;
}

/**
 * @brief Устанавливает параметр шара, отвечающий за его способность
 *  сталкиваться с другими шарами 
  */
bool Ball::isBallColidable(){
    return isCollidable;
}
