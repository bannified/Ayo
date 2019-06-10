#include "ayopch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "Ayo/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Ayo/Events/ApplicationEvent.h"

#include "Ayo/Application.h"

namespace Ayo {
	
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))         // Size of a static C-style array. Don't use on pointers!

	static GLFWwindow*          g_Window = NULL;    // Main window

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}


	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = (GLFWwindow*)(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	//void ImGuiLayer::OnEvent(Event& e)
	//{
	//	EventDispatcher dispatcher(e);

	//	//AYO_INFO("ImGuiLayer: {0}", e);

	//	/* ------ Mouse -------*/
	//	dispatcher.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();
	//		int button = e.GetButton();

	//		io.MouseDown[button] = true;
	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureMouse;
	//	});

	//	dispatcher.Dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();
	//		int button = e.GetButton();

	//		io.MouseDown[button] = false;
	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureMouse;
	//	});

	//	dispatcher.Dispatch<MouseMovedEvent>([](MouseMovedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		io.MousePos = ImVec2(e.GetMouseX(), e.GetMouseY());

	//		return io.WantCaptureMouse;
	//	});

	//	dispatcher.Dispatch<MouseScrolledEvent>([](MouseScrolledEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		io.MouseWheel += e.GetYOffset();
	//		io.MouseWheelH += e.GetXOffset();

	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureMouse;
	//	});
	//	/* -------------------- */

	//	/* ------ Keys -------*/
	//	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		int keycode = e.GetKeyCode();

	//		io.KeysDown[keycode] = true;

	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureKeyboard;
	//	});

	//	dispatcher.Dispatch<KeyReleasedEvent>([](KeyReleasedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		int keycode = e.GetKeyCode();

	//		io.KeysDown[keycode] = false;

	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureKeyboard;
	//	});

	//	dispatcher.Dispatch<KeyTypedEvent>([](KeyTypedEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		int keycode = e.GetKeyCode();

	//		if (keycode > 0 && keycode < 0x10000) 
	//		{
	//			io.AddInputCharacter((unsigned short)keycode);
	//		}

	//		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	//		return io.WantCaptureKeyboard;
	//	});
	//	/* -------------------- */

	//	/* ------ App -------*/

	//	dispatcher.Dispatch<AppWindowResizeEvent>([](AppWindowResizeEvent& e) -> bool
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		io.DisplaySize = ImVec2(e.Get_XSize(), e.Get_YSize());
	//		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	//		glViewport(0, 0, e.Get_XSize(), e.Get_YSize());

	//		return false;
	//	});

	//	/* -------------------- */
	//}

	void ImGuiLayer::Begin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiDraw()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

}
