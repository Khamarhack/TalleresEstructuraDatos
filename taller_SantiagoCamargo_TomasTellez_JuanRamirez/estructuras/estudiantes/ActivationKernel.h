#ifndef ACTIVATION_KERNEL_H
#define ACTIVATION_KERNEL_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

/**
 * ActivationKernel<T>
 *
 * Representa un Núcleo de Activación Polinomial (NAP), que es un polinomio
 * que representa la función de respuesta neuronal de una nave aguacate.
 *
 * Representación matemática:
 * NAP(x) = a₀ + a₁·x + a₂·x² + a₃·x³ + ... + aₙ·xⁿ
 *
 * Hereda PRIVADAMENTE de std::vector<T> para almacenar los coeficientes.
 * El coeficiente en el índice i corresponde al término de grado i.
 *
 * Ejemplo: El polinomio 2.0 + 3.0x² se almacenaría como:
 * vector: [2.0, 0.0, 3.0]
 * índice:   [0]   [1]   [2]
 * grado:     0     1     2
 */
template<class T>
class ActivationKernel : private std::vector<T> {
public:
    // Constructores
    ActivationKernel();
    explicit ActivationKernel(size_t n);

    // Acceder al coeficiente por grado
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    // Obtener grado del polinomio (índice del coeficiente no-cero más alto)
    size_t degree() const;

    // Obtener tamaño (grado + 1)
    size_t getSize() const;

    // Mostrar el polinomio en pantalla
    void display(const std::string& name = "NAP") const;

    // TODO #1: Evaluar el polinomio en un punto x usando el método de Horner
    // Complejidad: O(n) donde n = grado del polinomio
    T operator()(const T& x) const;

    // TODO #2: Sumar dos polinomios coeficiente por coeficiente
    // Complejidad: O(max(n,m)) donde n, m son los grados
    ActivationKernel<T> operator+(const ActivationKernel<T>& other) const;

    // TODO #3: Restar dos polinomios coeficiente por coeficiente
    // Complejidad: O(max(n,m)) donde n, m son los grados
    ActivationKernel<T> operator-(const ActivationKernel<T>& other) const;

    // TODO #4: Calcular la derivada simbólica
    // Complejidad: O(n) donde n = grado del polinomio
    ActivationKernel<T> Derivative() const;

    // TODO #5: Normalizar el polinomio por la norma L2
    // Complejidad: O(n) donde n = grado del polinomio
    ActivationKernel<T> Normalize() const;

    // TODO #6: Multiplicar dos polinomios usando convolución
    // Complejidad: O(n*m) donde n, m son los grados
    ActivationKernel<T> operator*(const ActivationKernel<T>& other) const;

    // TODO #7: Calcular la integral definida de a hasta b
    // Complejidad: O(n) donde n = grado del polinomio
    T Integrate(T a, T b) const;

    // TODO #8: Componer polinomios: f(g(x)) donde f=this, g=inner
    // Complejidad: O(n*m²) en el peor caso
    ActivationKernel<T> Compose(const ActivationKernel<T>& inner) const;
};

#endif // ACTIVATION_KERNEL_H
