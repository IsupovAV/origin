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

    Fraction operator +(const Fraction&f) const {
        int p = numerator_ * f.denominator_ + f.numerator_ * denominator_;
        int q = denominator_ * f.denominator_;
        return simply_(p, q);
    }

    // унарный минус
    Fraction operator -() const {
        return {-numerator_, denominator_};
    }

    Fraction operator -(const Fraction&f) const {
        return *this + (-f);
    }

    Fraction operator *(const Fraction&f) const {
        int p = numerator_ * f.numerator_;
        int q = denominator_ * f.denominator_;
        return simply_(p, q);
    }

    Fraction operator /(const Fraction&f) const {
        Fraction f1 = {f.denominator_, f.numerator_};
        return *this * f1;
    }

    //префиксная версия возвращает значение после инкремента
    Fraction operator++() {
        numerator_ += denominator_;
        return *this;
    }

    //постфиксная версия возвращает значение до декремента
    Fraction operator++(int) {
        Fraction temp(*this);
        ++*this;
        return temp;
    }

    //префиксная версия возвращает значение после декремента
    Fraction operator--() {
        numerator_ -= denominator_;
        return *this;
    }

    //постфиксная версия возвращает значение до декремента
    Fraction operator--(int) {
        Fraction temp(*this);
        --*this;
        return temp;
    }

private:
    // Определяет знак числа и возвращает:
    // 1, если x > 0, -1, когда x < 0, 0 при x == 0
    int sign_(int x) {
        return (x > 0) - (x < 0);
    }

    // сокращение дроби с числителем p и знаменателем q
    Fraction simply_(int p, int q) const {
        // поиск наибольшего общего делителя из стандартной библиотеки
        int g = std::gcd(p, q);
        return {p / g, q / g};
    }

    int numerator_; // числитель
    int denominator_; // знаменатель
};

// Перегруженный оператор вывода, дроби в общепринятом виде p/q
std::ostream& operator <<(std::ostream&out, const Fraction&f) {
    out << f.GetNumerator() << '/' << f.GetDenomerator();
    return out;
}

int main() {
    int num, denom;
    std::cout << "Введите числитель дроби 1: ";
    std::cin >> num;
    std::cout << "Введите знаменатель дроби 1: ";
    std::cin >> denom;
    Fraction f1(num, denom);
    std::cout << "Введите числитель дроби 2: ";
    std::cin >> num;
    std::cout << "Введите знаменатель дроби 2: ";
    std::cin >> denom;
    Fraction f2(num, denom);

    std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
    std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
    std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;

    // Проверяем префиксные и постфиксные операции
    std::cout << "++" << f1 << " * " << f2 << " = " << ++f1 * f2 << std::endl;
    std::cout << "Значение дроби 1 = " << f1 << std::endl;
    std::cout << f1 << "-- * " << f2 << " = " << f1-- * f2 << std::endl;
    std::cout << "Значение дроби 1 = " << f1 << std::endl;

    return 0;
}
