
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
            m_sum+= next;
            m_count++;
        }

        double eval() const override {
            if (m_count == 0) {
                return 0;
            } else {
                return m_sum / m_count; 
            }
            }

        const char * name() const override {
            return "mean";
        }

    private:
        double m_sum = 0.0;
        int m_count = 0;
    };


class Std : public IStatistics {
    public:
        void update(double next) override {
            m_sum+= next;
            m_sum_squared += next * next;
            m_count++;
        }

        double eval() const override {
            if (m_count == 0) {
                return 0;
            } else {
                double mean = m_sum / m_count;
                double dispercy = (m_sum_squared / m_count) - (mean * mean);
                return std::sqrt(dispercy);
            }
        }

        const char * name() const override {
            return "std";
        }

    private:
        double m_sum_squared = 0.0;
        double m_sum = 0.0;
        int m_count = 0;
    };

template<int percentil>
class Pct : public IStatistics {
    public:
        void update(double next) override {
            m_values.insert(next);
        }

        double eval() const override {
            double pct = (percentil / 100.) * (m_values.size() - 1);
            auto it = m_values.begin();
            std::advance(it, static_cast<int>(std::round(pct)));
            return *it;
        }

        const char * name() const override {
            return m_class_name.c_str();
        }

    private:
        std::multiset<double> m_values;
        std::string m_class_name = "pct" + std::to_string(percentil);
    };
