#version 330 core

// Atributos de vértice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a função BuildTrianglesAndAddToVirtualScene() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Atributos de vértice que serão gerados como saída ("out") pelo Vertex Shader.
// ** Estes serão interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais serão recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec3 gouraud_shading;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE  0
#define GUN 1
#define PLANE  2
#define BRICK_WALL 3
#define METAL_WALL 4
#define CEILING 5
#define ROBOT 6
#define RAT 7
#define ROBOT2 8
#define PENGUIN 9
#define CAMERA 10
// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

uniform int object_id;
// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;
// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;
uniform sampler2D TextureImage4;
uniform sampler2D TextureImage5;
uniform sampler2D TextureImage6;
uniform sampler2D TextureImage7;
//Id do material do objeto
uniform int material_id;
uniform vec4 player_view;

void main()
{
    // A variável gl_Position define a posição final de cada vértice
    // OBRIGATORIAMENTE em "normalized device coordinates" (NDC), onde cada
    // coeficiente estará entre -1 e 1 após divisão por w.
    // Veja {+NDC2+}.
    //
    // O código em "main.cpp" define os vértices dos modelos em coordenadas
    // locais de cada modelo (array model_coefficients). Abaixo, utilizamos
    // operações de modelagem, definição da câmera, e projeção, para computar
    // as coordenadas finais em NDC (variável gl_Position). Após a execução
    // deste Vertex Shader, a placa de vídeo (GPU) fará a divisão por W. Veja
    // slides 41-67 e 69-86 do documento Aula_09_Projecoes.pdf.

    gl_Position = projection * view * model * model_coefficients;

    // Como as variáveis acima  (tipo vec4) são vetores com 4 coeficientes,
    // também é possível acessar e modificar cada coeficiente de maneira
    // independente. Esses são indexados pelos nomes x, y, z, e w (nessa
    // ordem, isto é, 'x' é o primeiro coeficiente, 'y' é o segundo, ...):
    //
    //     gl_Position.x = model_coefficients.x;
    //     gl_Position.y = model_coefficients.y;
    //     gl_Position.z = model_coefficients.z;
    //     gl_Position.w = model_coefficients.w;
    //

    // Agora definimos outros atributos dos vértices que serão interpolados pelo
    // rasterizador para gerar atributos únicos para cada fragmento gerado.

    // Posição do vértice atual no sistema de coordenadas global (World).
    position_world = model * model_coefficients;

    // Posição do vértice atual no sistema de coordenadas local do modelo.
    position_model = model_coefficients;

    // Normal do vértice atual no sistema de coordenadas global (World).
    // Veja slides 123-151 do documento Aula_07_Transformacoes_Geometricas_3D.pdf.
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
    texcoords = texture_coefficients;

    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;

    //define posicao da fonte de luz
    vec4 source_position = vec4(0.0f, 1.9f, 9.9f,1.0f);

    //define direcao da spotilight
    vec4 spotlight_direction = normalize(camera_position-1.0f - source_position);
    //spotlight_direction = vec4(0.0f,-0.2f,-1.0f,1.0f);

    //dfine angulo de abertura da fonte de luz
    float spotilight_angle = radians(30.0)/(1.0+0.1*length(camera_position-1.0f - source_position));

    //test if the point is inside light cone
    float cos_angle = cos(spotilight_angle);
    vec4 incidence = normalize(p - source_position);
    float cos_beta = dot(incidence, spotlight_direction);
    bool inside_cone = cos_beta>cos_angle;

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = - incidence;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    vec4 r = -l + 2 * dot(n, l) * n;

    // Coef de Blinn-Phong
    vec4 h = normalize(l+v);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    vec3 Kd = vec3(0.0f,0.0f,0.0f);
    vec3 Ka = vec3(0.0f,0.0f,0.0f);
    vec3 Ks = vec3(0.0f,0.0f,0.0f);
    float q = 0.0;

    if ( object_id == SPHERE )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        float raio = 1.0;
        vec4 p_linha = bbox_center + raio * normalize(position_model - bbox_center);
        vec4 p_vector = p_linha - bbox_center;

        float theta = atan(p_vector.x, p_vector.z);
        float phi = asin(p_vector.y / raio);

        U = (theta + M_PI) / (2 * M_PI);
        V = (phi + M_PI_2) / M_PI;
        Kd = vec3(0.5f,0.5f,0.5f);
        Ka = 0.5*Kd;
    }
    else if ( object_id == ROBOT )
    {
        if (material_id == 0) { // Drill
            Kd = vec3(0.110689, 0.110689, 0.110689);
            Ka = vec3(0.575000, 0.575000, 0.575000);
            Ks = vec3(0.408333, 0.408333, 0.408333);
            q = 0.0;
        }
        else if (material_id == 1) { // Eye_Exterior
            Kd = vec3(0.002579, 0.002579, 0.002579);
            Ka = vec3(0.466667, 0.466667, 0.466667);
            Ks = vec3(0.500000, 0.500000, 0.500000);
            q = 0.0;
        }
        else if (material_id == 2) { // Eye_Inside
            Kd = vec3(0.800000, 0.000000, 0.003908);
            Ka = vec3(1.000000, 0.000000, 0.000000);
            Ks = vec3(0.500000, 0.000000, 0.000000);
            q = 0.0;
        }
        else if (material_id == 3) { // Robot_Mat
            Kd = vec3(0.147314, 0.147314, 0.147314);
            Ka = vec3(1.000000, 1.000000, 1.000000);
            Ks = vec3(0.500000, 0.500000, 0.500000);
            q = 0.0;
        }
    }
    else if ( object_id == RAT )
    {
        U = texcoords.x;
        V = texcoords.y;
        Kd = texture(TextureImage4, vec2(U,V)).rgb;
        Ka = 0.5*Kd;
    }
    else if ( object_id == ROBOT2 )
    {
        U = texcoords.x;
        V = texcoords.y;
        Kd = texture(TextureImage5, vec2(U,V)).rgb;
        Ka = 0.5*Kd;
    }
    else if ( object_id == CAMERA )
    {
        U = texcoords.x;
        V = texcoords.y;
        Kd = texture(TextureImage7, vec2(U,V)).rgb;
        Ka = 0.5*Kd;
    }
    else
    {
        Kd = vec3(0.0f,0.0f,0.0f);
        Ka = 0.5*Kd;
    }




    vec3 I = vec3(0.4,0.4,0.4);
    float intensity = 5.0;
    if(inside_cone)
        I += intensity*(vec3(1.0,0.0,0.0)/length(p - source_position));
    vec3 Ia = 0*vec3(0.1,0.1,0.1);
    vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
    vec3 ambient_term = Ka * Ia;
    //vec3 phong_specular_term  = Ks * I * pow(max(0,dot(n,h)), q);

    gouraud_shading = lambert_diffuse_term + ambient_term;
}

