#include "ActivationKernel.hxx"
#include <fstream>
#include <sstream>
#include <iomanip>

/**
 * Programa principal para el Taller 2: Copa Avocandro 2084
 *
 * Lee NAPs desde un archivo y ejecuta operaciones de fusión, diferenciación,
 * interacción, predicción, derivada, normalización, integración y composición.
 */

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " archivo.in" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << argv[1] << std::endl;
        return 1;
    }

    std::string line;
    std::vector<ActivationKernel<double>> naps;
    std::vector<std::string> napNames;

    std::cout << std::fixed << std::setprecision(1);

    // Leer NAPs del archivo
    while (std::getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        char op;
        iss >> op;

        switch (op) {
        case 'N': { // Nuevo NAP
            size_t index;
            std::string name;
            size_t numCoeffs;

            iss >> index >> name >> numCoeffs;

            ActivationKernel<double> nap(numCoeffs);
            for (size_t i = 0; i < numCoeffs; ++i) {
                double coeff;
                iss >> coeff;
                nap[i] = coeff;
            }

            while (naps.size() <= index) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }
            naps[index] = nap;
            napNames[index] = name;

            std::cout << ">> Cargando NAP[" << index << "] \"" << name << "\": ";
            nap.display("");
            break;
        }
        case 'F': { // Fusión (suma)
            size_t idx1, idx2, resultIdx;
            iss >> idx1 >> idx2 >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idx1] + naps[idx2];
            napNames[resultIdx] = "Fusion_" + napNames[idx1] + "_" + napNames[idx2];

            std::cout << "[F] Fusión " << napNames[idx1] << " ⊕ " << napNames[idx2] << " = ";
            naps[resultIdx].display("");
            break;
        }
        case 'D': { // Diferenciación (resta)
            size_t idx1, idx2, resultIdx;
            iss >> idx1 >> idx2 >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idx1] - naps[idx2];
            napNames[resultIdx] = "Diff_" + napNames[idx1] + "_" + napNames[idx2];

            std::cout << "[D] Diferencia " << napNames[idx1] << " ⊖ " << napNames[idx2] << " = ";
            naps[resultIdx].display("");
            break;
        }
        case 'M': { // Interacción (multiplicación)
            size_t idx1, idx2, resultIdx;
            iss >> idx1 >> idx2 >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idx1] * naps[idx2];
            napNames[resultIdx] = "Interaccion_" + napNames[idx1] + "_" + napNames[idx2];

            std::cout << "[M] Interacción " << napNames[idx1] << " ⊗ " << napNames[idx2] << " = ";
            naps[resultIdx].display("");
            break;
        }
        case 'P': { // Predicción (evaluación)
            size_t idx;
            double x;
            iss >> idx >> x;

            double result = naps[idx](x);
            std::cout << "[P] Predicción " << napNames[idx] << "(" << x << ") = " << result << std::endl;
            break;
        }
        case 'R': { // Derivada
            size_t idx, resultIdx;
            iss >> idx >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idx].Derivative();
            napNames[resultIdx] = "Derivada_" + napNames[idx];

            std::cout << "[R] Derivada " << napNames[idx] << " = ";
            naps[resultIdx].display("");
            break;
        }
        case 'L': { // Normaliza (L2 norm)
            size_t idx, resultIdx;
            iss >> idx >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idx].Normalize();
            napNames[resultIdx] = "Normalizado_" + napNames[idx];

            std::cout << "[L] Normalizado " << napNames[idx] << " = ";
            naps[resultIdx].display("");
            break;
        }
        case 'I': { // Integral
            size_t idx;
            double a, b;
            iss >> idx >> a >> b;

            double result = naps[idx].Integrate(a, b);
            std::cout << "[I] Integral " << napNames[idx] << " [" << a << ", " << b << "] = " << result << std::endl;
            break;
        }
        case 'C': { // Composición
            size_t idxOuter, idxInner, resultIdx;
            iss >> idxOuter >> idxInner >> resultIdx;

            while (naps.size() <= resultIdx) {
                naps.push_back(ActivationKernel<double>());
                napNames.push_back("");
            }

            naps[resultIdx] = naps[idxOuter].Compose(naps[idxInner]);
            napNames[resultIdx] = "Comp_" + napNames[idxOuter] + "_" + napNames[idxInner];

            std::cout << "[C] Composición " << napNames[idxOuter] << " ∘ " << napNames[idxInner] << " = ";
            naps[resultIdx].display("");
            break;
        }
        default:
            std::cerr << "Operación desconocida: " << op << std::endl;
            break;
        }
    }

    inputFile.close();
    return 0;
}
