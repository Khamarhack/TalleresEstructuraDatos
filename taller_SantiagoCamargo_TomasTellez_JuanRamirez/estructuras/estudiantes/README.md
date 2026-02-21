# Archivos para Estudiantes - Taller 2: Copa Avocandro 2084

Esta carpeta contiene los archivos base que los estudiantes deben completar para el Taller 2.

## 📦 Archivos incluidos

- **ActivationKernel.h**: Declaración de la clase template con las firmas de todos los métodos
- **ActivationKernel.hxx**: Implementación de métodos con TODOs vacíos (¡AQUÍ VAN LAS IMPLEMENTACIONES!)
- **test_copa_avocandro.cxx**: Programa principal que lee archivos y ejecuta operaciones
- **copa_avocandro_00.in**: Archivo de entrada de ejemplo
- **copa_avocandro_00.out**: Salida esperada para el archivo de ejemplo

## 🎯 Tarea de los estudiantes

Los estudiantes deben:

1. **Implementar los 8 TODOs** en `ActivationKernel.hxx`:
   - TODO #1: `operator()` - Evaluación usando Horner
   - TODO #2: `operator+` - Suma de polinomios
   - TODO #3: `operator-` - Resta de polinomios
   - TODO #4: `Derivative()` - Derivada simbólica
   - TODO #5: `Normalize()` - Normalización L2
   - TODO #6: `operator*` - Multiplicación (convolución)
   - TODO #7: `Integrate()` - Integral definida
   - TODO #8: `Compose()` - Composición de polinomios

2. **Compilar y probar** su implementación:
   ```bash
   g++ -std=c++17 -o copa_avocandro test_copa_avocandro.cxx
   ./copa_avocandro copa_avocandro_00.in
   ```

3. **Verificar** que la salida coincide con `copa_avocandro_00.out`:
   ```bash
   ./copa_avocandro copa_avocandro_00.in > mi_salida.txt
   diff mi_salida.txt copa_avocandro_00.out
   ```

## ⚠️ Importante

- NO modificar `ActivationKernel.h` (solo leer las declaraciones)
- SOLO implementar los TODOs en `ActivationKernel.hxx`
- El código debe compilar con `g++ -std=c++17` sin errores ni advertencias
- Consultar el archivo `taller.md` para especificaciones completas de cada TODO

## 📚 Referencias

- Ver `taller.md` para el enunciado completo
- Algoritmos sugeridos están comentados en cada TODO
- Casos de prueba y ejemplos en el enunciado
