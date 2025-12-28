
#include <iostream>
#include <limits>
#include <cmath>
#include <set>
#include <string>


class IStatistics {
    public:
        virtual ~IStatistics() {}

        virtual void update(double next) = 0;
        virtual double eval() const = 0;
        virtual const char * name() const = 0;
    };

class Min : public IStatistics {
    public:
        Min() : m_min{std::numeric_limits<double>::max()} {}

        void update(double next) override {
            if (next < m_min) {
                m_min = next;
            }
        }

        double eval() const override {
            return m_min;
        }

        const char * name() const override {
            return "min";
        }

    private:
        double m_min;
};

class Max : public IStatistics {
    public:
        Max() : m_max{std::numeric_limits<double>::lowest()} {}

        void update(double next) override {
            if (next > m_max) {
                m_max = next;
            }
        }

        double eval() const override {
            return m_max;
        }

        const char * name() const override {
            return "max";
        }

    private:
        double m_max;
    };


class Mean : public IStatistics {
    public:
        void update(double next) override {
            sum+= next;
            count++;
        }

        double eval() const override {
            return sum / count; 
            }

        const char * name() const override {
            return "mean";
        }

    private:
        double sum = 0;
        int count = 0;
    };


class Std : public IStatistics {
    public:
        void update(double next) override {
            sum+= next;
            sum_squared += next * next;
            count++;
        }

        double eval() const override {
            double mean = sum / count;
            double dispercy = (sum_squared / count) - (mean * mean);
            return std::sqrt(dispercy);
        }

        const char * name() const override {
            return "std";
        }

    private:
        double sum_squared = 0;
        double sum = 0;
        int count = 0;
    };

template<int percentil>
class Pct : public IStatistics {
    public:
        void update(double next) override {
            values.insert(next);
        }

        double eval() const override {
            double pct = (percentil / 100.) * (values.size() - 1);
            auto it = values.begin();
            std::advance(it, (int)(std::round(pct)));
            return *it;
        }

        const char * name() const override {
            return class_name.c_str();
        }

    private:
        std::multiset<double> values;
        std::string class_name = "pct" + std::to_string(percentil);
    };
