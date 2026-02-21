#include "ActivationKernel.h"
#include <stdexcept>
#include <cmath>

// Implementación de constructores
template<class T>
ActivationKernel<T>::ActivationKernel() : std::vector<T>() {}

template<class T>
ActivationKernel<T>::ActivationKernel(size_t n) : std::vector<T>(n, T()) {}

// Implementación de operator[] (acceso por índice)
template<class T>
T& ActivationKernel<T>::operator[](size_t index) {
    return std::vector<T>::operator[](index);
}

template<class T>
const T& ActivationKernel<T>::operator[](size_t index) const {
    return std::vector<T>::operator[](index);
}

// Implementación de degree()
template<class T>
size_t ActivationKernel<T>::degree() const {
    if (this->empty()) return 0;
    for (int i = static_cast<int>(this->size()) - 1; i >= 0; --i) {
        if ((*this)[i] != T()) return static_cast<size_t>(i);
    }
    return 0;
}

// Implementación de getSize()
template<class T>
size_t ActivationKernel<T>::getSize() const {
    return this->size();
}

// Implementación de display()
template<class T>
void ActivationKernel<T>::display(const std::string& name) const {
    if (!name.empty()) {
        std::cout << name << ": ";
    }
    if (this->empty() || (this->size() == 1 && (*this)[0] == T())) {
        std::cout << "0";
        return;
    }

    bool firstTerm = true;
    for (size_t i = 0; i < this->size(); ++i) {
        T coef = (*this)[i];
        if (coef == T()) continue;

        if (!firstTerm && coef > T()) {
            std::cout << " + ";
        } else if (coef < T()) {
            std::cout << " - ";
            coef = -coef;
        } else if (!firstTerm) {
            std::cout << " + ";
        }

        if (i == 0 || coef != T(1)) {
            std::cout << coef;
        }

        if (i == 1) {
            std::cout << "x";
        } else if (i > 1) {
            std::cout << "x²";
            if (i > 2) {
                for (size_t j = 3; j <= i; ++j) {
                    std::cout << "²";
                }
            }
        }

        firstTerm = false;
    }
    std::cout << std::endl;
}


//  TODO #1: operator() - Evaluar el polinomio en un punto x (Usa Horner para ser más eficiente)

template<class T>
T ActivationKernel<T>::operator()(const T& x) const {
    if (this->empty()) return T();
    
    // Empiezo desde el coeficiente más grande
    T res = (*this)[this->size() - 1];
    
    // Voy bajando y aplicando Horner
    for (int i = static_cast<int>(this->size()) - 2; i >= 0; --i) {
        res = res * x + (*this)[i];
    }
    
    return res;
}

//  TODO #2: operator+ - Suma de polinomios

template<class T>
ActivationKernel<T> ActivationKernel<T>::operator+(const ActivationKernel<T>& other) const {
    // El resultado tiene que ser del tamaño del más grande
    size_t tam = std::max(this->size(), other.size());
    ActivationKernel<T> resultado(tam);
    
    for (size_t i = 0; i < tam; ++i) {
        T coefA = (i < this->size()) ? (*this)[i] : T();
        T coefB = (i < other.size()) ? other[i] : T();
        resultado[i] = coefA + coefB;
    }
    
    return resultado;
}

//  TODO #3: operator- - Resta de polinomios ()igual a la suma pero restando)

template<class T>
ActivationKernel<T> ActivationKernel<T>::operator-(const ActivationKernel<T>& other) const {
    size_t tam = std::max(this->size(), other.size());
    ActivationKernel<T> resultado(tam);
    
    for (size_t i = 0; i < tam; ++i) {
        T coefA = (i < this->size()) ? (*this)[i] : T();
        T coefB = (i < other.size()) ? other[i] : T();
        resultado[i] = coefA - coefB;
    }
    
    return resultado;
}

//  TODO #4: Derivative() - Calcular la derivada (La derivada de x^n es n*x^(n-1) )

template<class T>
ActivationKernel<T> ActivationKernel<T>::Derivative() const {
    // Si es constante, la derivada es 0
    if (this->size() <= 1) return ActivationKernel<T>();
    
    ActivationKernel<T> der(this->size() - 1);
    
    // Para cada término multiplico el coeficiente por su exponente
    for (size_t i = 1; i < this->size(); ++i) {
        der[i - 1] = static_cast<T>(i) * (*this)[i];
    }
    
    return der;
}

//  TODO #5: Normalize() - Normalizar por norma L2

template<class T>
ActivationKernel<T> ActivationKernel<T>::Normalize() const {
    if (this->empty()) return ActivationKernel<T>();
    
    // Primero calculo la norma (sqrt de suma de cuadrados)
    T sumCuadrados = T();
    for (size_t i = 0; i < this->size(); ++i) {
        sumCuadrados += (*this)[i] * (*this)[i];
    }
    
    T norma = std::sqrt(sumCuadrados);
    
    // Si la norma es 0 no puedo dividir
    if (norma == T()) return *this;
    
    // Ahora divido cada coeficiente por la norma
    ActivationKernel<T> norm(this->size());
    for (size_t i = 0; i < this->size(); ++i) {
        norm[i] = (*this)[i] / norma;
    }
    
    return norm;
}

//  TODO #6: operator* - Multiplicación de polinomios (Uso convolución: cada par (i,j) contribuye a la posición i+j)

template<class T>
ActivationKernel<T> ActivationKernel<T>::operator*(const ActivationKernel<T>& other) const {
    if (this->empty() || other.empty()) return ActivationKernel<T>();
    
    // El tamaño del resultado es la suma de los tamaños menos 1
    size_t tamRes = this->size() + other.size() - 1;
    ActivationKernel<T> prod(tamRes);
    
    // Multiplico cada término de A con cada término de B
    for (size_t i = 0; i < this->size(); ++i) {
        for (size_t j = 0; j < other.size(); ++j) {
            prod[i + j] += (*this)[i] * other[j];
        }
    }
    
    return prod;
}

//TODO #7: Integrate() - Integral definida de a hasta b (Calculo F(b) - F(a) donde F es la primitiva)

template<class T>
T ActivationKernel<T>::Integrate(T a, T b) const {
    if (this->empty()) return T();
    
    // Función para evaluar la primitiva en un punto
    // La primitiva de x^n es x^(n+1)/(n+1)
    // Uso Horner para evaluarla
    
    // Evalúo en b
    T Fb = T();
    int n = static_cast<int>(this->size());
    for (int k = n - 1; k >= 0; --k) {
        Fb = (Fb + (*this)[k] / static_cast<T>(k + 1)) * b;
    }
    
    // Evalúo en a
    T Fa = T();
    for (int k = n - 1; k >= 0; --k) {
        Fa = (Fa + (*this)[k] / static_cast<T>(k + 1)) * a;
    }
    
    return Fb - Fa;
}

//  TODO #8: Compose() - Composición f(g(x)) (Básicamente f(g(x)) = f[0]*g^0 + f[1]*g^1 + f[2]*g^2 + ...)

template<class T>
ActivationKernel<T> ActivationKernel<T>::Compose(const ActivationKernel<T>& inner) const {
    if (this->empty()) return ActivationKernel<T>();
    
    ActivationKernel<T> resultado;
    
    // g^0 = 1 (polinomio constante)
    ActivationKernel<T> potencia(1);
    potencia[0] = T(1);
    
    for (size_t i = 0; i < this->size(); ++i) {
        // Solo sumo si el coeficiente no es cero
        if ((*this)[i] != T()) {
            // Multiplico la potencia por el coeficiente f[i]
            ActivationKernel<T> termino(potencia.getSize());
            for (size_t k = 0; k < potencia.getSize(); ++k) {
                termino[k] = (*this)[i] * potencia[k];
            }
            
            // Lo sumo al resultado
            if (resultado.getSize() == 0) {
                resultado = termino;
            } else {
                resultado = resultado + termino;
            }
        }
        
        // Calculo la siguiente potencia: potencia *= inner
        potencia = potencia * inner;
    }
    
    return resultado;
}
