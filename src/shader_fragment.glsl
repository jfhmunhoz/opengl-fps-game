#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

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

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

//Id do material do objeto
uniform int material_id;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    vec3 Kd;

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

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = vec3(0.5f,0.5f,0.5f);
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == CEILING )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x * 10.0f;
        V = texcoords.y * 10.0f;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage1, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x * 10.0f;
        V = texcoords.y * 10.0f;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage0, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == METAL_WALL )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        V = texcoords.x * 2.0f;
        U = texcoords.y * 10.0f;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage1, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == BRICK_WALL )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        V = texcoords.x * 2.0f;
        U = texcoords.y * 10.0f;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage2, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == GUN )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage3, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == ROBOT )
    {
        if (material_id == 0) { // Drill
            //Kd 0.110689 0.110689 0.110689
            //Ks 0.408333 0.408333 0.408333
            Kd = vec3(0.110689, 0.110689, 0.110689);
            color.rgb = Kd;

            color.a = 1;

            // Cor final com correção gamma, considerando monitor sRGB.
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
        }
        else if (material_id == 1) { // Eye_Exterior
            //Kd 0.002579 0.002579 0.002579
            //Ks 0.500000 0.500000 0.500000
            Kd = vec3(0.002579, 0.002579, 0.002579);
            color.rgb = Kd;

            color.a = 1;

            // Cor final com correção gamma, considerando monitor sRGB.
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
        }
        else if (material_id == 2) { // Eye_Inside
            //Kd 0.800000 0.000000 0.003908
            //Ks 0.500000 0.500000 0.500000
            Kd = vec3(0.800000, 0.000000, 0.003908);
            color.rgb = Kd;

            color.a = 1;

            // Cor final com correção gamma, considerando monitor sRGB.
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
        }
        else if (material_id == 3) { // Robot_Mat
            //Kd 0.147314 0.147314 0.147314
            //Ks 0.500000 0.500000 0.500000
            Kd = vec3(0.147314, 0.147314, 0.147314);
            color.rgb = Kd;

            color.a = 1;

            // Cor final com correção gamma, considerando monitor sRGB.
            color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
        }
    }
    else if ( object_id == RAT )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage4, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else if ( object_id == ROBOT2 )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        Kd = texture(TextureImage5, vec2(U,V)).rgb;
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    }
    else
    {
        Kd = vec3(1.0f,0.0f,1.0f);
        // Equação de Iluminação
        float lambert = max(0,dot(n,l));


        color.rgb = Kd;

        color.a = 1;

        // Cor final com correção gamma, considerando monitor sRGB.
        color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);

    }
} 

