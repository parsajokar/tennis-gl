#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "stdlib.h"

#include "game.h"
#include "matrix.h"
#include "renderer.h"

struct _Renderer {
    struct {
        float r;
        float g;
        float b;
        float a;
    } clear_color;

    uint32_t program;
    int32_t uniform_projection_location;
    int32_t uniform_transform_location;
    uint32_t vertex_array;
    uint32_t array_buffer;
    uint32_t element_array_buffer;
};

static uint32_t create_shader(uint32_t type, const char* source) {
    uint32_t shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

Renderer* renderer_create() {
    Renderer* self = malloc(sizeof(Renderer));

    gladLoadGL(glfwGetProcAddress);

    self->clear_color.r = 0.0;
    self->clear_color.g = 0.0;
    self->clear_color.b = 0.0;
    self->clear_color.a = 1.0;

    const char* vert_source =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec3 a_Position;\n"
        "\n"
        "uniform mat4 u_Projection;\n"
        "uniform mat4 u_Transform;\n"
        "\n"
        "void main() {\n"
        "    gl_Position = u_Projection * u_Transform * vec4(a_Position, 1.0);\n"
        "}\n";
    const char* frag_source =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 o_Color;\n"
        "\n"
        "void main() {\n"
        "    o_Color = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";

    self->program = glCreateProgram();
    uint32_t vert_shader = create_shader(GL_VERTEX_SHADER, vert_source);
    uint32_t frag_shader = create_shader(GL_FRAGMENT_SHADER, frag_source);

    glAttachShader(self->program, vert_shader);
    glAttachShader(self->program, frag_shader);

    glLinkProgram(self->program);
    glValidateProgram(self->program);

    glDetachShader(self->program, vert_shader);
    glDetachShader(self->program, frag_shader);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    glUseProgram(self->program);
    self->uniform_projection_location = glGetUniformLocation(self->program, "u_Projection");
    self->uniform_transform_location = glGetUniformLocation(self->program, "u_Transform");

    ProjectionSpec projection_spec = {
        .left = 0.0,
        .right = GAME_WIDTH,
        .bottom = 0.0,
        .top = GAME_HEIGHT,
        .near = 0.1,
        .far = 100.0
    };
    Mat4 projection = get_projection(&projection_spec);
    glUniformMatrix4fv(self->uniform_projection_location, 1, GL_FALSE, projection.data);

    float vertices[] = {
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0
    };
    uint32_t indices[] = {0, 2, 1, 0, 2, 3};

    glGenVertexArrays(1, &self->vertex_array);
    glGenBuffers(1, &self->array_buffer);
    glGenBuffers(1, &self->element_array_buffer);

    glBindVertexArray(self->vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, self->array_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->element_array_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    return self;
}

void renderer_destroy(Renderer* self) {
    glDeleteBuffers(1, &self->element_array_buffer);
    glDeleteBuffers(1, &self->array_buffer);
    glDeleteVertexArrays(1, &self->vertex_array);

    glDeleteProgram(self->program);

    free(self);
}

void renderer_clear(const Renderer* self) {
    glClearColor(
        self->clear_color.r,
        self->clear_color.g,
        self->clear_color.b,
        self->clear_color.a
    );
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_draw_rect(const Renderer* self, const Rect* rect) {
    Mat4 transform = get_transform(rect);
    glUniformMatrix4fv(self->uniform_transform_location, 1, GL_FALSE, transform.data);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
