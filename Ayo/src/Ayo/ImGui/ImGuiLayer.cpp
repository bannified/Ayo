#include "ayopch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Ayo/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Ayo/Events/ApplicationEvent.h"

#include "Ayo/Application.h"

namespace Ayo {
	
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))         // Size of a static C-style array. Don't use on pointers!

	bool show_another_window = true;

	static GLFWwindow*          g_Window = NULL;    // Main window

	static bool                 g_MouseJustPressed[5] = { false, false, false, false, false };

	// Chain GLFW callbacks: our callbacks will call the user's previously installed callbacks, if any.
	static GLFWmousebuttonfun   g_PrevUserCallbackMousebutton = NULL;
	static GLFWscrollfun        g_PrevUserCallbackScroll = NULL;
	static GLFWkeyfun           g_PrevUserCallbackKey = NULL;
	static GLFWcharfun          g_PrevUserCallbackChar = NULL;

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
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		// Temporary. Should be using Ayo's Key codes.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		// Installing callbacks
		Ayo::Window& parentWindow = (Application::Get().GetWindow());
		GLFWwindow* window = ((WindowsWindow&)(parentWindow)).GetGLFWWindow();
		g_Window = window;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void ImGuiLayer::OnUpdate()
	{
		//glfwPollEvents();

		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		// 3. Show another simple window.
		if (show_another_window) {
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		int display_w, display_h;

		glfwGetFramebufferSize(g_Window, &display_w, &display_h);

		glViewport(0, 0, display_w, display_h);
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//glfwSwapBuffers(g_Window);
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		AYO_INFO("ImGuiLayer: {0}", e);

		/* ------ Mouse -------*/
		dispatcher.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();
			int button = e.GetButton();

			io.MouseDown[button] = true;
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureMouse;
		});

		dispatcher.Dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();
			int button = e.GetButton();

			io.MouseDown[button] = false;
			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureMouse;
		});

		dispatcher.Dispatch<MouseMovedEvent>([](MouseMovedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			io.MousePos = ImVec2(e.GetMouseX(), e.GetMouseY());

			return io.WantCaptureMouse;
		});

		dispatcher.Dispatch<MouseScrolledEvent>([](MouseScrolledEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			io.MouseWheel += e.GetYOffset();
			io.MouseWheelH += e.GetXOffset();

			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureMouse;
		});
		/* -------------------- */

		/* ------ Keys -------*/
		dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			int keycode = e.GetKeyCode();

			io.KeysDown[keycode] = true;

			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureKeyboard;
		});

		dispatcher.Dispatch<KeyReleasedEvent>([](KeyReleasedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			int keycode = e.GetKeyCode();

			io.KeysDown[keycode] = false;

			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureKeyboard;
		});

		dispatcher.Dispatch<KeyTypedEvent>([](KeyTypedEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			int keycode = e.GetKeyCode();

			if (keycode > 0 && keycode < 0x10000) 
			{
				io.AddInputCharacter((unsigned short)keycode);
			}

			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return io.WantCaptureKeyboard;
		});
		/* -------------------- */

		/* ------ App -------*/

		dispatcher.Dispatch<AppWindowResizeEvent>([](AppWindowResizeEvent& e) -> bool
		{
			ImGuiIO& io = ImGui::GetIO();

			io.DisplaySize = ImVec2(e.Get_XSize(), e.Get_YSize());
			io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
			glViewport(0, 0, e.Get_XSize(), e.Get_YSize());

			return false;
		});

		/* -------------------- */
	}
}
