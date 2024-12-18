// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size) {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw std::out_of_range("Vector size exceeds MAX_VECTOR_SIZE");
        pMem = new T[sz](); // Инициализация значениями по умолчанию
    }

    TDynamicVector(T* arr, size_t s) : sz(s) {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz) {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem) {
        v.sz = 0;
        v.pMem = nullptr;
    }

    ~TDynamicVector() {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this == &v) return *this; // Защита от самоприсваивания
        T* tmp = new T[v.sz];
        std::copy(v.pMem, v.pMem + v.sz, tmp);
        delete[] pMem; // Освобождаем старую память
        pMem = tmp;
        sz = v.sz;
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        if (this == &v) return *this; // Защита от самоприсваивания
        delete[] pMem; // Освобождаем старую память
        pMem = v.pMem;
        sz = v.sz;
        v.pMem = nullptr;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // Индексация
    T& operator[](size_t ind) {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& operator[](size_t ind) const {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // Индексация с контролем
    T& at(size_t ind) {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& at(size_t ind) const {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) // Проверка размеров
            return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true; // Все элементы равны
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        return !(*this == v);
    }

    // Скалярные операции
    TDynamicVector operator+(T val) {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + val;
        }
        return res;
    }

    TDynamicVector operator-(T val) {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - val;
        }
        return res;
    }

    TDynamicVector operator*(T val) {
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }
        return res;
    }

    // Векторные операции
    TDynamicVector operator+(const TDynamicVector& v) {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors must have the same size for addition");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v) {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors must have the same size for subtraction");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }

    T operator*(const TDynamicVector& v) noexcept(noexcept(T())) {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors must have the same size for scalar product");

        T result = T();
        for (size_t i = 0; i < sz; i++) {
            result += pMem[i] * v.pMem[i];
        }
        return result;
    }

    // Ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << " ";
        }
        return ostr;
    }
};

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at; 
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
        if (s > MAX_MATRIX_SIZE)
            throw std::out_of_range("Matrix size exceeds MAX_MATRIX_SIZE");

        for (size_t i = 0; i < this->sz; i++) {
            this->pMem[i] = TDynamicVector<T>(s);
        }
    }

    size_t size() const noexcept { return sz; }

    // Сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (sz != m.sz)
            return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i])
                return false;
        }
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept {
        return !(*this == m);
    }

    // Матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * val;
        }
        return res;
    }

    // Матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        if (sz != v.size())
            throw std::invalid_argument("Matrix size and vector size must match for multiplication");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * v;
        }
        return res;
    }


  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::invalid_argument("Matrix sizes must match for addition");

      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = pMem[i] + m[i];
      }
      return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::invalid_argument("Matrix sizes must match for subtraction");

      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = pMem[i] - m[i];
      }
      return res;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) {
      if (sz != m.sz)
          throw std::invalid_argument("Matrix sizes must match for multiplication");

      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res[i][j] = T();
              for (size_t k = 0; k < sz; k++) {
                  res[i][j] += pMem[i][k] * m[k][j];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          istr >> m.pMem[i]; // Ввод каждой строки матрицы
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          ostr << m.pMem[i] << std::endl; // Вывод каждой строки матрицы
      }
      return ostr;
  }

};

#endif
