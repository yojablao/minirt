/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:34:51 by yojablao          #+#    #+#             */
/*   Updated: 2025/02/26 16:42:28 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

double bump_maping(t_material *m,t_spher *sp,t_comps *comp)
{

    t_tuple    *obj_point ;
    float scaleFactor;
    double theta ;
    double phi ;
    double u ;
    double v ;
    obj_point = normal_at(sp,comp->point);

    theta = atan2(obj_point->z, obj_point->x); // [-π, π]
    phi = acos(obj_point->y / magnitude(*obj_point)); // [0, π]
    u = (theta + M_PI) / (2.0 * M_PI); 
    v = 1.0 - (phi / M_PI); 
    u = fmod(u + 1.0, 1.0);
    v = fmod(v + 1.0, 1.0);
	uint32_t t = (uint32_t)((u) * (m->bump_map->width - 1));
	uint32_t l = (uint32_t)((1.0 - v) * (m->bump_map->height - 1)); 
	uint8_t *bump = &m->bump_map->pixels[(l * m->bump_map->width + t) * m->bump_map->bytes_per_pixel];
	unsigned char  color = bump[0];
    float normal_bump = color / 255.0f;
    scaleFactor = 1.0f + (normal_bump * m->bump_scale);
    return(scaleFactor);
}
// t_color *spher_texter(t_spher *sp,t_material *m,t_comps *comp)
// {

//     t_tuple    *obj_point ;
//     float scaleFactor;
//     double theta ;
//     double phi ;
//     double u ;
//     double v ;
// 	if(m->bump_map)
// 	{
//         obj_point = normal_at(sp,comp->point);
        
//         theta = atan2(obj_point->z, obj_point->x); // [-π, π]
//         phi = acos(obj_point->y / magnitude(*obj_point)); // [0, π]

//             printf("theta: %lf\n",theta);
//         printf("phi: %lf\n",phi);

//         u =  (theta + M_PI) / (2.0 * M_PI); 
//         v = 1.0 - (phi / M_PI); 
//         u = fmod(u + 1.0, 1.0);
//         v = fmod(v + 1.0, 1.0);
// 		uint32_t t = (uint32_t)((u) * (m->bump_map->width - 1));
// 		uint32_t l = (uint32_t)((1.0 - v) * (m->bump_map->height - 1)); 
// 		uint8_t *bump = &m->bump_map->pixels[(l * m->bump_map->width + t) * 4];
// 		unsigned char color = bump[0];
//         float normal_bump = color / 255.0f;
//         scaleFactor = 2.0f + (normal_bump );
// 		printf("Bump Map Color: %f\n", scaleFactor);
      
// 	}
// 	if (m->texter)
// 	{
//         obj_point = normal_at(sp,comp->point);
//         // printf("%f,%f,%f\n",obj_point->x,obj_point->y,obj_point->z);
        
//         theta = atan2(obj_point->z, obj_point->x); // [-π, π]
//         phi = acos(obj_point->y / magnitude(*obj_point)); // [0, π]

 
//         u =  0 +(theta + M_PI) / (2.0 * M_PI); 
//         v = 1 - (phi / M_PI); 
//         u = fmod(u + 1.0, 1.0);
//         v = fmod(v + 1.0, 1.0);
// 		uint32_t x = (uint32_t)(u * (m->texter->width - 1));
// 		uint32_t y = (uint32_t)((1.0 - v) * (m->texter->height - 1)); 


// 		uint8_t *pixel = &m->texter->pixels[(y * m->texter->width + x) * 4];
//     	return new_color(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0); 
// 	}
//     return(&m->color);
// }
t_tuple *compute_tangent(t_tuple N) {
    t_tuple up = {1, 0, 0}; 
    // if (fabs(N.y) > 1) 
    //     up = (t_tuple){1, 0, 0}; 
    return (cross_p(up, N));
}
t_color *cylan_texter(t_cylinder *sp, t_material *m, t_comps *comp)
{
    t_tuple obj_point;
    obj_point = *normal_at_cyl(sp, comp->point);
    
}
t_color *spher_texter(t_spher *sp, t_material *m, t_comps *comp) {
    t_tuple obj_point;
    float scaleFactor;
    double theta, phi, u, v;

    obj_point = *normal_at(sp, comp->point);

    theta = atan2(obj_point.z, obj_point.x); // [-π, π]
    phi = acos(obj_point.y / magnitude(obj_point)); // [0, π]

    u = 0.25 + (theta + M_PI) / (2.0 * M_PI); 
    v = 1.0 - (phi / M_PI);            
    u = fmax(0.0, fmin(1.0, u));
    v = fmax(0.0, fmin(1.0, v));

    if (m->bump_map)
    {
        uint32_t t = (uint32_t)(u * (m->bump_map->width - 1));
        uint32_t l = (uint32_t)((1.0 - v) * (m->bump_map->height - 1));
        uint8_t *bump = &m->bump_map->pixels[(l * m->bump_map->width + t) * 4];
        float higth = (bump[0] / 255.0f ) * 2 -1 ; 
        t_tuple *T = compute_tangent(*comp->normalv);
        normalize(T);
        t_tuple *B = cross_p(*comp->normalv, *T);
        comp->normalv = tpl_o(*comp->normalv,*scalar(*B, higth),add);

        comp->normalv = normal_at(&comp->object.shape, comp->normalv);
    }
    if (m->texter) {
        uint32_t x = (uint32_t)(u * (m->texter->width - 1));
        uint32_t y = (uint32_t)((1.0 - v) * (m->texter->height - 1));

        uint8_t *pixel = &m->texter->pixels[(y * m->texter->width + x) * 4];

        return new_color(pixel[0] / 255.0, pixel[1] / 255.0, pixel[2] / 255.0);
    }
    return &m->color;
}
