// ubicaciones.cpp
#include "locations.hpp"
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::map<std::string, std::vector<std::string>>> locations = {
    {"San José", {
        {"Central", {"Carmen", "Merced", "Hospital", "Catedral", "Zapote", "San Francisco de Dos Ríos", "Uruca", "Mata Redonda", "Hatillo", "Pavas"}},
        {"Escazú", {"Escazú centro", "San Rafael", "San Antonio"}},
        {"Desamparados", {"Desamparados", "San Miguel", "San Juan de Dios"}}
    }},
    {"Alajuela", {
        {"Central", {"Alajuela", "San José", "Carrizal", "San Antonio"}},
        {"Grecia", {"Grecia", "San Roque", "Tacares"}}
    }},
    {"Cartago", {
        {"Central", {"Oriental", "Occidental", "Carmen", "San Nicolás"}},
        {"Paraíso", {"Paraíso", "Santiago", "Orosi"}}
    }},
    {"Heredia", {
        {"Central", {"Heredia", "Mercedes", "San Francisco", "Ulloa"}},
        {"San Rafael", {"San Rafael", "San Josecito", "Santiago"}}
    }},
    {"Guanacaste", {
        {"Liberia", {"Liberia", "Cañas Dulces", "Mayorga"}},
        {"Santa Cruz", {"Santa Cruz", "Bolsón", "Veintisiete de Abril"}}
    }},
    {"Puntarenas", {
        {"Central", {"Puntarenas", "Barranca", "El Roble"}},
        {"Golfito", {"Golfito", "Guaycará", "Pavón"}}
    }},
    {"Limón", {
        {"Limón", {"Limón", "Valle La Estrella", "Río Blanco"}},
        {"Pococí", {"Guápiles", "Jiménez", "La Rita"}}
    }}
};
