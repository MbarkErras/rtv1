#include "rtv1.h"

int property_vcounter[7] = {-1, PLANE_VCOUNT, SPHERE_VCOUNT, CYLINDER_VCOUNT, CONE_VCOUNT, CAMERA_VCOUNT, LIGHT_VCOUNT};
int property_scounter[7] = {-1, PLANE_SCOUNT, SPHERE_SCOUNT, CYLINDER_SCOUNT, CONE_SCOUNT, CAMERA_SCOUNT, LIGHT_SCOUNT};

void    print_parsing_results(t_scene scene)
{
    printf("camera:\n\t");
    for (int i = 0; i < CAMERA_VCOUNT; i++)
        printf("(%f, %f, %f) ", scene.camera->vectors[i][0], scene.camera->vectors[i][1], scene.camera->vectors[i][2]);
    for (int i = 0; i < CAMERA_SCOUNT; i++)
        printf("%f ", scene.camera->scalars[i]);
    printf("\n");
    printf("lights:\n");
    t_list *light = scene.lights;
    while (light)
    {
        printf("\t");
        for (int i = 0; i < LIGHT_VCOUNT; i++)
            printf("(%f, %f, %f) ", TLIST(light, t_object)->vectors[i][0], TLIST(light, t_object)->vectors[i][1], TLIST(light, t_object)->vectors[i][2]);
        for (int i = 0; i < LIGHT_SCOUNT; i++)
            printf("%f ", TLIST(light, t_object)->scalars[i]);
        printf("\n");
        light = light->next;
    }
    printf("objects:\n");
    t_list *object = scene.objects;
    while (object)
    {
        printf("\t");
        for (int i = 0; i < property_vcounter[TLIST(object, t_object)->object_type]; i++)
            printf("(%f, %f, %f) ", TLIST(object, t_object)->vectors[i][0], TLIST(object, t_object)->vectors[i][1], TLIST(object, t_object)->vectors[i][2]);
        for (int i = 0; i < property_scounter[TLIST(object, t_object)->object_type]; i++)
            printf("%f ", TLIST(object, t_object)->scalars[i]);
        printf("\n");
        object = object->next;
    }
    (void)scene;
}