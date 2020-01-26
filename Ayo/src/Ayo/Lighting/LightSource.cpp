#include "ayopch.h"
#include "LightSource.h"

Ayo::LightSource::LightSource(const Vector3 color, const Vector3 diffuse, const Vector3 specular, const float intensity)
    : p_Color(color), p_Diffuse(diffuse), p_Specular(specular), p_Intensity(intensity) { }

Ayo::LightSource::LightSource() 
    : p_Color({ 1.0f, 1.0f, 1.0f }), p_Diffuse({ 1.0f, 1.0f, 1.0f }), p_Specular({ 1.0f, 1.0f, 1.0f }), p_Intensity(1.0f) { }

Ayo::LightSource::~LightSource()
{

}
