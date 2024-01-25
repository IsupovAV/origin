#include <iostream>
#include <numeric>

class Fraction {
public:
    Fraction(int numerator, int denominator) {
        // Случай, когда знаменатель равен нулю, пока не рассматриваем.
        // В принципе можно бросить исключение типа domain_error, но что
        // делать дальше, как программа должна его обработать зависит от
        // исходной, задачи.
        numerator_ = numerator;
        denominator_ = denominator;
        // убираем знак из знаменателя дроби вида -p/-q (p > 0, q > 0)
        // приводим к виду p/q, p/-q к виду -p/q
        int sgn = sign_(denominator_);
        numerator_ *= sgn;
        denominator_ *= sgn;
    }

    // Функции "про запас" для получения доступа извне отдельно
    // к числителю и знаменателю дроби, в этой задаче не используются.
    [[nodiscard]] int GetNumerator() const {
        return numerator_;
    }

    [[nodiscard]] int GetDenomerator() const {
        return denominator_;
    }

    bool operator ==(const Fraction&f) const {
        return numerator_ * f.denominator_ == f.numerator_ * denominator_;
    }

    bool operator !=(const Fraction&f) const {
        return !(*this == f);
    }

    bool operator <(const Fraction&f) const {
        return numerator_ * f.denominator_ < f.numerator_ * denominator_;
    }

    bool operator >=(const Fraction&f) const {
        return !(*this < f);
    }

    bool operator >(const Fraction&f) const {
        return numerator_ * f.denominator_ > f.numerator_ * denominator_;
    }

    bool operator <=(const Fraction&f) const {
        return !(*this > f);
    }


private:
    // Определяет знак числа и возвращает:
    // 1, если x > 0, -1, когда x < 0, 0 при x == 0
    int sign_(const int& x) {
        return (x > 0) - (x < 0);
    }

    int numerator_; // числитель
    int denominator_; // знаменатель
};

int main()
{
    const Fraction f1(4, 3);
    const Fraction f2(6, 11);


    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

    return 0;
}
