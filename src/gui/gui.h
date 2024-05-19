#ifndef __GUI_COMMON_H__
#define __GUI_COMMON_H__

#include <GL/gl.h>
#include <stdbool.h>

typedef void Renderer;
typedef void GuiGl;
typedef void Gui;
typedef void AppState;

enum GuiActionTag {
    gui_action_none,
    gui_action_toggle_pause,
    gui_action_close,
    gui_action_seek,
};

struct GuiAction {
    enum GuiActionTag tag;
    float seek_position;
};

struct AppStateSnapshot {
    bool paused;
    float current_position;
    float total_runtime;
};

// GUI interface
Gui* gui_init(AppState* state);
void gui_free(Gui* gui);
void gui_run(Gui* gui, Renderer* renderer);
struct GuiAction gui_next_action(Gui* gui);
void gui_wait_start(Gui* gui);
void gui_notify_update(Gui* gui);
void gui_close(Gui* gui);

// Gui OpenGL wrappers
// GUI owns window creation, and has to draw widgets to the screen. This means
// that it owns the OpenGL context. If we want to render frames in OpenGL, then
// we have to provide the OpenGL interface
GLuint guigl_create_shader(GuiGl* guigl, GLenum shader_type);
void   guigl_delete_shader(GuiGl* guigl, GLuint shader);
void   guigl_shader_source(GuiGl* guigl, GLuint shader, const GLchar* const* source);
void   guigl_compile_shader(GuiGl* guigl, GLuint shader);
GLuint guigl_create_program(GuiGl* guigl);
void   guigl_use_program(GuiGl* guigl, GLuint program);
void   guigl_delete_program(GuiGl* guigl, GLuint program);
void   guigl_attach_shader(GuiGl* guigl, GLuint program, GLuint shader);
void   guigl_link_program(GuiGl* guigl, GLuint program);
GLuint guigl_gen_texture(GuiGl* guigl);
void   guigl_delete_texture(GuiGl* guigl, GLuint texture);
void   guigl_bind_texture(GuiGl* guigl, GLenum target, GLuint texture);
void   guigl_active_texture(GuiGl* guigl, GLuint texture);
void   guigl_tex_parameter_i(GuiGl* guigl, GLenum target, GLenum name, GLint param);
void   guigl_tex_image_2d(GuiGl* guigl, GLenum target, GLint level, GLint internal_format, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum typ, const void * pixels);
void   guigl_uniform_1i(GuiGl* guigl, GLint loc, GLint val);
void   guigl_uniform_1f(GuiGl* guigl, GLint loc, GLfloat val);
GLint  guigl_get_uniform_location(GuiGl* guigl, GLuint program, const GLchar * name);
void   guigl_draw_arrays(GuiGl* guigl, GLenum mode, GLint first, GLsizei count);

// Zig interface
void framerenderer_init_gl(Renderer* renderer, GuiGl* guigl);
void framerenderer_render(Renderer* renderer, float width, float height, GuiGl* guigl);
void framerenderer_deinit_gl(Renderer* renderer, GuiGl* guigl);

struct AppStateSnapshot appstate_snapshot(AppState* app);

#endif // __GUI_H__
