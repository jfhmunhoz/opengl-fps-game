#version 330 core

in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;
in vec3 gouraud_shading;

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
#define PENGUIN 9

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

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

//Id do material do objeto
uniform int material_id;
uniform vec4 player_view;
uniform int player_dead;
uniform float time;

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
    

    //define posicao da fonte de luz
    vec4 source_position = vec4(0.0f, 3.1f, 9.9f,1.0f);

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

    bool isGouraud = true;

    if ( object_id == GUN )
    {
        isGouraud = false;
        U = texcoords.x;
        V = texcoords.y;
        Ka = texture(TextureImage3, vec2(U,V)).rgb;
        Kd = 0.8*Ka;
        Ks = 15.5*Ka;
        q = 80.0;
    }
    else if ( object_id == CEILING )
    {
        isGouraud = false;
        U = texcoords.x * 10.0f;
        V = texcoords.y * 10.0f;
        Kd = texture(TextureImage1, vec2(U,V)).rgb;
        Ka = 1.0*Kd;
    }
    else if ( object_id == PLANE )
    {
        isGouraud = false;
        U = texcoords.x * 10.0f;
        V = texcoords.y * 10.0f;
        Kd = texture(TextureImage0, vec2(U,V)).rgb;
        Ka = 1.0*Kd;
    }
    else if ( object_id == METAL_WALL )
    {
        isGouraud = false;
        V = texcoords.x * 2.0f;
        U = texcoords.y * 10.0f;
        Kd = texture(TextureImage1, vec2(U,V)).rgb;
        Ka = 1.0*Kd;
    }
    else if ( object_id == BRICK_WALL )
    {
        isGouraud = false;
        V = texcoords.x * 2.0f;
        U = texcoords.y * 10.0f;
        Kd = texture(TextureImage2, vec2(U,V)).rgb;
        Ka = 1.0*Kd;
    }
    else if ( object_id == PENGUIN )
    {
        isGouraud = false;
        U = texcoords.x;
        V = texcoords.y;
        Ka = texture(TextureImage6, vec2(U,V)).rgb;
        Kd = 0.8*Ka;
        Ks = 1.5*Ka;
        q = 20.0;
    }

    if(isGouraud)
    {
        color.rgb = gouraud_shading;
    }
    else
    {
        vec3 I = 0.5*vec3(0.4,0.4,0.4);
        float intensity = 10.0;
        if(inside_cone)
            I += intensity*(vec3(1.0,0.0,0.0)/length(p - source_position));
        vec3 Ia = 0.005*vec3(1.0,1.0,1.0);
        vec3 lambert_diffuse_term = Kd * I * max(0, dot(n, l));
        vec3 ambient_term = Ka * Ia;
        vec3 phong_specular_term  = Ks * I * pow(max(0,dot(n,h)), q);

        if(q==0.0)
            phong_specular_term = vec3(0.0,0.0,0.0);

        if(object_id == PENGUIN && dot(v,n)<=0)
            color.rgb = vec3(0.0,0.0,0.0);

        color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;
    }

    //deixar o pingu mais cartoonizado
    if(object_id == PENGUIN && dot(v,n)<=0.3)
        color.rgb = vec3(0.0,0.0,0.0);

    //if ( object_id == SPHERE )
    //{
    //    float spin_speed = 2.0;
    //    float pulse_speed = 3.0;
    //    float angle = time * spin_speed;
    //    
    //    vec4 light_to_point = normalize(p - source_position);
    //    
    //    float cos_a = cos(angle);
    //    float sin_a = sin(angle);
    //    
    //    vec3 rotated;
    //    rotated.x = light_to_point.x * cos_a - light_to_point.z * sin_a;
    //    rotated. y = light_to_point.y;
    //    rotated. z = light_to_point.x * sin_a + light_to_point. z * cos_a;
    //    
    //    // Add pulsing brightness
    //    float pulse = 0.5 + 0.5 * sin(time * pulse_speed);
    //    
    //    color.rgb = (rotated * 0.5 + 0.5) * (0.7 + 0.3 * pulse);
    //}


    //if ( object_id == SPHERE )
    //{
    //    //Rainbow
    //    vec4 light_to_point = normalize(p - source_position);
    //    color.rgb = light_to_point. xyz * 0.5 + 0.5;
    //}

    //Cool white effect
    if (player_dead == 1) {
        float NdotL = dot(n, l);
        color. rgb = vec3(NdotL);
    }

    if ( object_id == SPHERE )
    {
        vec3 surface_dir = normalize(n.xyz);
        
        // Multiple overlapping waves for trippy effect
        float t = time * 0.5;
        
        color.r = 0.5 + 0.5 * sin(surface_dir.x * 3.0 + t * 2.0);
        color.g = 0.5 + 0.5 * sin(surface_dir.y * 3.0 + t * 2.5 + 2.094);
        color.b = 0.5 + 0.5 * sin(surface_dir.z * 3.0 + t * 3.0 + 4.188);

        if(dot(v,n)<=0.5)
            color.rgb = color.gbr;
    }

    color.a = 1;
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);



    //Dark
    //float dist = length(p - source_position);
    //color.rgb = vec3(dist / 100.0);

} 

