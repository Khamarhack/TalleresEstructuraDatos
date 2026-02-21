# Makefile para Taller 2: Copa Avocandro 2084
# Compilar el programa de prueba para estudiantes

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
TARGET = copa_avocandro
SRC = test_copa_avocandro.cxx
HEADERS = ActivationKernel.h ActivationKernel.hxx
INPUT = copa_avocandro_00.in
EXPECTED_OUTPUT = copa_avocandro_00.out

# Compilar el ejecutable
all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Ejecutar con el archivo de prueba
run: $(TARGET)
	./$(TARGET) $(INPUT)

# Probar y comparar con salida esperada
test: $(TARGET)
	@echo "Ejecutando prueba..."
	./$(TARGET) $(INPUT) > mi_salida.txt
	@echo "Comparando con salida esperada..."
	@if diff -q mi_salida.txt $(EXPECTED_OUTPUT) > /dev/null 2>&1; then \
		echo "✅ ¡PERFECTO! Tu salida coincide exactamente con la esperada."; \
	else \
		echo "❌ Hay diferencias. Ejecuta 'make diff' para ver detalles."; \
	fi

# Ver diferencias entre tu salida y la esperada
diff: mi_salida.txt
	diff -y --width=120 mi_salida.txt $(EXPECTED_OUTPUT) | less

# Limpiar archivos generados
clean:
	rm -f $(TARGET) mi_salida.txt

# Ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make         - Compilar el programa"
	@echo "  make run     - Compilar y ejecutar con el archivo de prueba"
	@echo "  make test    - Compilar, ejecutar y comparar con salida esperada"
	@echo "  make diff    - Ver diferencias detalladas entre tu salida y la esperada"
	@echo "  make clean   - Eliminar archivos generados"
	@echo "  make help    - Mostrar esta ayuda"

.PHONY: all run test diff clean help
