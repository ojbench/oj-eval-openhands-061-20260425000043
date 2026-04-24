
#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>     // 数学函数
#include <iomanip>   // 控制输出格式
#include <iostream>  // 输入输出
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
private:
  double a, b; // a + bi
public:
  complex();                   // 默认构造函数 0+0i
  complex(double a);           // 构造函数 a+0i
  complex(double a, double b); // 构造函数 a+bi

  double &real(); // 返回实部
  double &imag(); // 返回虚部

  complex operator-() const; // 返回负数
  complex operator~() const; // 返回共轭复数

  complex operator+(const complex &rhs) const; // 加法
  complex operator-(const complex &rhs) const; // 减法
  complex operator*(const complex &rhs) const; // 乘法
  complex operator/(const complex &rhs) const; // 除法

  complex &operator+=(const complex &rhs);
  complex &operator-=(const complex &rhs);
  complex &operator*=(const complex &rhs);
  complex &operator/=(const complex &rhs);

  bool operator==(const complex &rhs) const; // 判断相等

  explicit operator bool() const; // 转换为 bool

  friend std::ostream &operator<<(std::ostream &os, const complex &x); // 输出
};

// 实现构造函数
complex::complex() : a(0), b(0) {}

complex::complex(double a) : a(a), b(0) {}

complex::complex(double a, double b) : a(a), b(b) {}

// 实现访问实部和虚部
double &complex::real() {
  return a;
}

double &complex::imag() {
  return b;
}

// 实现单目运算符
complex complex::operator-() const {
  return complex(-a, -b);
}

complex complex::operator~() const {
  return complex(a, -b);
}

// 实现四则运算
complex complex::operator+(const complex &rhs) const {
  return complex(a + rhs.a, b + rhs.b);
}

complex complex::operator-(const complex &rhs) const {
  return complex(a - rhs.a, b - rhs.b);
}

complex complex::operator*(const complex &rhs) const {
  // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
  return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
}

complex complex::operator/(const complex &rhs) const {
  // Check for division by zero
  if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
    throw divided_by_zero();
  }
  // (a + bi) / (c + di) = (a + bi)(c - di) / (c^2 + d^2)
  double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
  return complex((a * rhs.a + b * rhs.b) / denominator, 
                 (b * rhs.a - a * rhs.b) / denominator);
}

// 实现复合赋值运算符
complex &complex::operator+=(const complex &rhs) {
  a += rhs.a;
  b += rhs.b;
  return *this;
}

complex &complex::operator-=(const complex &rhs) {
  a -= rhs.a;
  b -= rhs.b;
  return *this;
}

complex &complex::operator*=(const complex &rhs) {
  // (a + bi) *= (c + di) = (ac - bd) + (ad + bc)i
  double new_a = a * rhs.a - b * rhs.b;
  double new_b = a * rhs.b + b * rhs.a;
  a = new_a;
  b = new_b;
  return *this;
}

complex &complex::operator/=(const complex &rhs) {
  // Check for division by zero
  if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
    throw divided_by_zero();
  }
  // (a + bi) / (c + di) = (a + bi)(c - di) / (c^2 + d^2)
  double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
  double new_a = (a * rhs.a + b * rhs.b) / denominator;
  double new_b = (b * rhs.a - a * rhs.b) / denominator;
  a = new_a;
  b = new_b;
  return *this;
}

// 实现比较运算符
bool complex::operator==(const complex &rhs) const {
  return std::abs(a - rhs.a) < 1e-6 && std::abs(b - rhs.b) < 1e-6;
}

// 实现类型转换
complex::operator bool() const {
  return std::abs(a) >= 1e-6 || std::abs(b) >= 1e-6;
}

// 实现输出运算符
std::ostream &operator<<(std::ostream &os, const complex &x) {
  // Set output format to fixed with 6 decimal places
  os << std::fixed << std::setprecision(6);
  
  // Handle real part
  if (sign(x.a) == -1) {
    os << x.a;
  } else {
    os << x.a;
  }
  
  // Handle imaginary part
  if (sign(x.b) == -1) {
    os << x.b << "i";
  } else {
    os << "+" << x.b << "i";
  }
  
  return os;
}

} // namespace sjtu

#endif
