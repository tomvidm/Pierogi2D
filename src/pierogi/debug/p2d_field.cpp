#include "p2d_field.hpp"

namespace p2d { namespace debug {
    Field::Field(std::string val) 
    : string(val), fieldType(FieldType::STRING) {;}

    Field::Field(int val)
    : intVal(val), fieldType(FieldType::INT) {;}

    Field::Field(float val)
    : floatVal(val), fieldType(FieldType::FLOAT) {;}

    std::string Field::toString() const {
        switch (fieldType) {
            case FieldType::STRING:
                return string;
            case FieldType::INT:
                return std::to_string(intVal);
            case FieldType::FLOAT:
                return std::to_string(floatVal);
            default:
                return "Hahahahaha";
        } // switch
    } // toString
} // namespace debug
} // namespace p2d