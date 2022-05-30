#include <stdlib.h>
#include <pybind11/pybind11.h>
#include "astyle_main.h"

namespace py = pybind11;

// Error handler for the Artistic Style formatter.
void STDCALL ASErrorHandler(int errorNumber, const char* errorMessage) {
    std::cout << "astyle error " << errorNumber << "\n" << errorMessage << std::endl;
}

// Allocate memory for the Artistic Style formatter.
char* STDCALL ASMemoryAlloc(unsigned long memoryNeeded) {
    // error condition is checked after return from AStyleMain
    char* buffer = new char [memoryNeeded];
    return buffer;
}

PYBIND11_MODULE(pyastyle, m) {
    m.doc() = R"pbdoc(Python bingding for Artistic Style.)pbdoc";

    m.def("as_version", &AStyleGetVersion, R"pbdoc(AStyleGetVersion)pbdoc");

    m.def("as_format", [](const char* text_in, const char* options) {
        // call the Artistic Style formatting function
        char* text_out = AStyleMain(text_in, options, ASErrorHandler, ASMemoryAlloc);

        // does not need to terminate on an error
        // an error message has been displayed by the error handler
        if (text_out == NULL) {
            std::cout << "The program has terminated!" << std::endl;
            exit(EXIT_FAILURE);
        }

        return text_out;
    }, R"pbdoc(AStyleMain)pbdoc");

    m.attr("__version__") = AStyleGetVersion();
}
