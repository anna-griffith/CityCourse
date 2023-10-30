//
//  pywrap.cpp
//  BinomialModel
//
//  Created by Anna Griffith on 21/10/2023.
//
#include "src/BinomialModel/BinomialModel.h"
#include "src/Options/OptionPricerBase.h"
#include "src/Options/OptionPricer.h"
#include "src/Options/BarrierOptionPricer.h"
#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(city_course, m) {
    m.doc() = "optional module docstring";

    py::class_<BinomialModel>(m, "BinomialModel")
        .def(py::init<double, double, double, double>())
        .def(py::init<double, double, double, int, double>())
        .def("calculateRiskNeutralProbability", &BinomialModel::calculateRiskNeutralProbability)
        .def("calculateStockPrice", &BinomialModel::calculateStockPrice, py::arg("n"), py::arg("i"))
        .def_property_readonly("m_R", &BinomialModel::getR)
        .def_property_readonly("m_S0", &BinomialModel::getS0)
    ;
    
    py::class_<CallOptionPricer>(m, "CallOptionPricer")
        .def(py::init<int, double, BinomialModel&>())
        .def("calculateNewtonSymbol", &CallOptionPricer::calculateNewtonSymbol, py::arg("i"))
        .def("priceByCRR", &CallOptionPricer::priceByCRR)
        .def("priceAnalytic", &CallOptionPricer::priceAnalytic)
        .def("priceBySnell", &CallOptionPricer::priceBySnell)
        .def("payoff", &CallOptionPricer::payoff)
    ;
    
    py::class_<PutOptionPricer>(m, "PutOptionPricer")
        .def(py::init<int, double, BinomialModel&>())
        .def("priceByCRR", &PutOptionPricer::priceByCRR)
        .def("priceAnalytic", &PutOptionPricer::priceAnalytic)
        .def("priceBySnell", &PutOptionPricer::priceBySnell)
        .def("payoff", &PutOptionPricer::payoff)
    ;
    
    py::class_<DigitalCallOptionPricer>(m, "DigitalCallOptionPricer")
        .def(py::init<int, double, BinomialModel&>())
        .def("priceByCRR", &DigitalCallOptionPricer::priceByCRR)
        .def("priceAnalytic", &DigitalCallOptionPricer::priceAnalytic)
        .def("priceBySnell", &DigitalCallOptionPricer::priceBySnell)
        .def("payoff", &DigitalCallOptionPricer::payoff)
    ;
    
    py::class_<DoubleDigitalOptionPricer>(m, "DoubleDigitalOptionPricer")
        .def(py::init<int, double, double, BinomialModel&>())
        .def("priceByCRR", &DoubleDigitalOptionPricer::priceByCRR)
        .def("priceAnalytic", &DoubleDigitalOptionPricer::priceAnalytic)
        .def("priceBySnell", &DoubleDigitalOptionPricer::priceBySnell)
        .def("payoff", &DoubleDigitalOptionPricer::payoff)
    ;
    
    py::class_<KOBarrierOptionPricer>(m, "KOBarrierOptionPricer")
        .def(py::init<int, double, double, BinomialModel&>())
        .def(py::init<int, double, BinomialModel&>())
        .def("priceByCRR", &KOBarrierOptionPricer::priceByCRR)
        .def("payoff", &KOBarrierOptionPricer::payoff, py::arg("z"))
    ;
    
    py::class_<KIBarrierOptionPricer>(m, "KIBarrierOptionPricer")
        .def(py::init<int, double, double, BinomialModel&>())
        .def(py::init<int, double, BinomialModel&>())
        .def("priceByCRR", &KIBarrierOptionPricer::priceByCRR)
        .def("payoff", &KIBarrierOptionPricer::payoff, py::arg("z"))
    ;
    
    m.attr("__version__") = "0.0.1";
}

