#pragma once

/// Enumeration of the different types of lights.
enum LIB_API LightType {
    /**
     * \brief Directional light.
     */
    DIRECTIONAL,
    /**
    * \brief Omnidirectional light.
    */
    OMNIDIRECTIONAL,
    /**
    * \brief Spot light.
    */
    SPOT
};