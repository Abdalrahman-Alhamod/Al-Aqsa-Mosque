#include "Constraints.h"

// Default Constructor
Constraints::Constraints() : width(0.0f), height(0.0f), length(0.0f) {
    // Initialize constraints to their default values.
}

// Constructor to create Constraints with provided width, height, and length
Constraints::Constraints(float width, float height, float length) : width(width), height(height), length(length) {
    // No need for separate assignments; use member initializer list.
}
