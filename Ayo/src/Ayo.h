#pragma once
// This header is intended to only be included by client applications, never within Ayo project.

#include "Ayo/Application.h"
#include "Ayo/Log.h"
#include "Ayo/Input.h"
#include "Ayo/Time.h"

#include "Ayo/Layer.h"
#include "Ayo/ImGui/ImGuiLayer.h"

// Pure macro files
#include "Ayo/Macros/Keycodes.h"
#include "Ayo/Macros/MouseButtonCodes.h"

#include "Ayo/Events/KeyEvent.h"
#include "Ayo/Events/MouseEvent.h"
#include "Ayo/Events/ApplicationEvent.h"

// --- Entry Point ---
#include "Ayo/EntryPoint.h"
// -------------------

// --- Renderer ---

#include "Ayo/Renderer/VertexArray.h"
#include "Ayo/Renderer/Shader.h"
#include "Ayo/Renderer/Texture.h"
#include "Ayo/Renderer/Camera.h"
#include "Ayo/Renderer/Buffer.h"
#include "Ayo/Renderer/RendererAPI.h"

#include "Ayo/Renderer/RenderCommand.h"
#include "Ayo/Renderer/Renderer.h"

#include "Ayo/Renderer/Material.h"
#include "Ayo/Renderer/Materials/StandardMaterial.h"

// ----------------

// --- Math ---

#include "Ayo/Math/Vector3.h"
#include "Ayo/Math/Rotator.h"
#include "Ayo/Math/Quaternion.h"

// ------------

// --- Components and objects ---

#include "Ayo/Components/SceneComponent.h"
#include "Ayo/Lighting/LightSource.h"
#include "Ayo/Lighting/DirectionalLightSource.h"

//

#include "glm/glm.hpp"