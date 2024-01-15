#pragma once

/**
 * @class Constraints
 * @brief Represents constraints with width, height, and length.
 */
class Constraints {
public:
    /**
     * @brief Default constructor for Constraints.
     */
    Constraints();

    /**
     * @brief Constructor to create Constraints with provided width, height, and length.
     * @param width The width constraint.
     * @param height The height constraint.
     * @param length The length constraint.
     */
    Constraints(float width, float height, float length);

    // Member variables
    float width;  ///< Width constraint
    float height; ///< Height constraint
    float length; ///< Length constraint
};
