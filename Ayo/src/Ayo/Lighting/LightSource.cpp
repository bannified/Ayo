#include "ayopch.h"
#include "LightSource.h"

Ayo::LightSource::LightSource(glm::vec3 color, float intensity)
    : p_Color(color), p_Intensity(intensity) { }

Ayo::LightSource::LightSource() 
    : p_Color({1.0f, 1.0f, 1.0f}), p_Intensity(1.0f) { }

Ayo::LightSource::~LightSource()
{

}
