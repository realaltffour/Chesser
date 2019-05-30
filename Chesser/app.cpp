#include "common.h"
// Main Function
#ifdef __ANDROID__
int __main(GLFMDisplay* display);
#else
int __main(int argc, char* argv[]);
#endif

// Cross-Platform Main Function
#if (__OS__ == __OS_WIN64__) || (__OS__ == __OS_WIN32__)
#if !defined(__DEBUG__)
#include <windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT) { return __main(0, nullptr); }
#else
int main(int argc, char* argv[]) { return __main(argc, argv); }
#endif
#elif defined(__ANDROID__)
void glfmMain(GLFMDisplay* display) { __main(display); }
#else
int main(int argc, char* argv[]) { return __main(argc, argv); }
#endif

#include "chsr_api.h"
#include "game/Game.h"
#include "globals.cpp"

#include <engine/text/TextRenderer.h>

void eventHandle(GEngine::Event& evt);

static GEngine::Object* object;
static GEngine::Object* object2;
static GEngine::Shader* shader;
GEngine::Text::TextRenderer* texter;

class App : public GEngine::Window::Window {
   public:
#ifndef __ANDROID__
	App(void) : Window(false, WINDOW_WIDTH, WINDOW_HEIGHT, "Chesser") {
		this->__init();
#else
	App(GLFMDisplay* display)
		: Window(display){
#endif
	};
	~App(void) {}

   public:
	void OnKey(int key, int scancode, int action, int mods) {}
	void OnMouseButton(int button, int action, int mods) {}

	void eventHandler(const GEngine::Event& evt) { Log::info(evt.ToString()); }

   public:
	void tick(void) override {
		object->translate(glm::vec2(1.0f / 128.0f, 0.0f));
	}
	void render(void) override {
		texter->RenderText("MSPF: " + std::to_string(this->getMSPF()) +
							   " UT: " + std::to_string(this->getUT()),
						   "Arial", 1.0f, GEngine::Point(0, 0),
						   glm::vec3(1.0f, 1.0f, 1.0f), this->getMVP());

		shader->bind();
		this->getMVP()->updateModel(object->getModel());
		this->getMVP()->bind(shader->getProgId());
		object->bind();
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}

   private:
	bool inited = false;
#ifndef __ANDROID__
	void __init(void){
#else
	void init(void) override {
#endif
		this->setEventHandler(eventHandle);

	object = new GEngine::Object("assets/awesomeface.png",
								 GEngine::Rect(100, 100, 50, 50));
	object2 = new GEngine::Object("assets/awesomeface.png",
								  GEngine::Rect(200, 250, 100, 100));

	texter = new GEngine::Text::TextRenderer();
	texter->Init();
	texter->LoadFont("Arial", "assets/fonts/arial.ttf");
	texter->LoadCharacters("Arial");

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
	shader = new GEngine::Shader("glsl/vs.glsl", "glsl/fs.glsl");
#elif defined(__EMSCRIPTEN__)
		shader =
			new GEngine::Shader("glsl/vs_es_em.glsl", "glsl/fs_es_em.glsl");
#elif defined(__ANDROID__)
shader = new GEngine::Shader("glsl/vs_es.glsl", "glsl/fs_es.glsl");
#endif
}
}
;

static App* app = nullptr;
void eventHandle(GEngine::Event& evt) { app->eventHandler(evt); }

#ifdef __ANDROID__
int __main(GLFMDisplay* display) {
	initApp(0, nullptr);
#else
int __main(int argc, char* argv[]) {
	initApp(argc, argv);
#endif

#ifdef __ANDROID__
	App* _app = new App(display);
	app = _app;
#else
	App _app;
	app = &_app;
#endif
	app->start();

	return 0;
}
