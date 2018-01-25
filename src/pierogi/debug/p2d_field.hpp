#ifndef P2D_FIELD_HPP
#define P2D_FIELD_HPP

#include <string>

namespace p2d { namespace debug {
    typedef std::string String;
    typedef unsigned int uint;

    enum class FieldType {
        STRING,
        // STRING_PTR,
        INT,
        // INT_PTR,
        FLOAT
        // FLOAT_PTR
    }; // FieldType

    class Field {
    public:
        Field(String val);
        Field(int val);
        Field(float val);
        String toString() const;
    private:
        FieldType fieldType;
        String string;
        union {
            int     intVal;
            float   floatVal;
        }; // union
    }; // Field
} // namespace debug
} // namespace p2d

#endif