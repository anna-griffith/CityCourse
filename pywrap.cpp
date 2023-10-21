////
////  pywrap.cpp
////  BinomialModel
////
////  Created by Anna Griffith on 21/10/2023.
////
//#include "pybind11/include/pybind11/pybind11.h"
////#include "BinomialModel/BinomialModel.h"
////
////namespace py = pybind11;
////constexpr auto byref = py::return_value_policy::reference_internal;
////
////PYBIND11_MODULE(BinomialModel, m) {
////    m.doc() = "optional module docstring";
////
////    py::class_<BinomialModel>(m, "BinomialModel")
////    .def(py::init<double, double, double, double>())
////    .def(py::init<double, double, double, int, double>())
////    .def("calculateRiskNeutralProbability", &MyClass::calculateRiskNeutralProbability)
////    ;
////}
//
////#include <pybind11/pybind11.h>
//
//#define STRINGIFY(x) #x
//#define MACRO_STRINGIFY(x) STRINGIFY(x)
//
//int add(int i, int j) {
//    return i + j;
//}
//
//namespace py = pybind11;
//
//PYBIND11_MODULE(cmake_example, m) {
//    m.doc() = R"pbdoc(
//        Pybind11 example plugin
//        -----------------------
//
//        .. currentmodule:: cmake_example
//
//        .. autosummary::
//           :toctree: _generate
//
//           add
//           subtract
//    )pbdoc";
//
//    m.def("add", &add, R"pbdoc(
//        Add two numbers
//
//        Some other explanation about the add function.
//    )pbdoc");
//
//    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
//        Subtract two numbers
//
//        Some other explanation about the subtract function.
//    )pbdoc");
//
//    m.attr("__version__") = "0.0.1";
//
//}
