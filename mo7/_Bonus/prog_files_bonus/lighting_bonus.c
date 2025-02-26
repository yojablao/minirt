/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:35:03 by mthamir           #+#    #+#             */
/*   Updated: 2025/02/26 14:26:05 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt_bonus.h"

t_light	*light_source(t_tuple *position, t_color *color, double brightness)
{
	t_light	*light;

	light = ft_malloc(sizeof(t_light), 0);
	light->position = *position;
	light->color = *color;
	return (light);
}

t_material	*material(void)
{
	t_material	*mate;

	mate = ft_malloc(sizeof(t_material), 0);
	mate->color = *new_color(1.0, 1.0, 1.0);
	mate->ambiant = 0.1;
	mate->diffuse = 0.9;
	mate->specular = 0.9;
	mate->shininess = 200.0;
	mate->checker = 0;
	return (mate);
}

t_color *compute_specular(t_material *m, \
				t_light *light, t_tuple *lightv, t_tuple *normalv, t_tuple *eyev)
{
	double reflect_dot_eye;
	double factor;
	double var;

	opp(lightv);
	reflect_dot_eye =  dot_p(*reflect(*lightv, *normalv), *eyev);
	if (reflect_dot_eye <= 0.0)
		return (NULL);
	factor = pow(reflect_dot_eye, 50);
	var = m->specular * factor;
	return (color_s_mul(&light->color, var));
}

t_color *check_pattern(t_tuple *p, t_material *m)
{
	if ((int )fabs(floor(p->x/m->checker) + floor(p->z/m->checker)) % 2 == 0)
		return (&m->color);
	return (&m->pattern_color);
}

t_color	*shade_hit(t_world *w, t_comps *comp, t_tuple *eyev)
{
	t_material	*m;
	t_color *ambiant;
	t_color *col;
	int i = 0;
	t_color *specular_diffuse = new_color(0,0,0);

	if (!comp)
		return (new_color(0, 0, 0));
	if (comp->object.type == SPHER)
		m = comp->object.shape.material;
	else if (comp->object.type == PLANE)
		m = comp->object.shape_pl.material;
	else if (comp->object.type == CYLINDER)
		m = comp->object.shape_cyl.material;
	col = &m->color;
	if (comp->object.type == PLANE && m->checker)
		col = check_pattern(tup_mat_mul(comp->object.shape_pl.inverse_m,comp->point), m);
	if (comp->object.type == SPHER && (m->texter || m->bump_map))
	{
		col = spher_texter(&comp->object.shape,m,comp);
	}
	ambiant = colors_operation(w->ambiant_color, col, mul);
	while (i < w->light_count){
		if (!in_shadow(w, comp, i))
		{
			specular_diffuse =  colors_operation(specular_diffuse, \
				compute_lightning(m, &w->light[i], comp->point, comp->normalv, eyev, col), add);
		}
		i++;
	}	
	return (colors_operation(ambiant, specular_diffuse, add));
}


t_color	*compute_lightning(t_material *m, \
				t_light *light, t_tuple *pos, t_tuple *normalv, t_tuple *eyev, t_color *col)
{
	t_color	*effective_color;
	t_color	*diffuse;
	t_tuple	*lightv;
	double	light_dot_normal;
	t_color *specular;

	diffuse = NULL;
	specular = NULL;
	effective_color = colors_operation(&light->color, col, mul);
	lightv = tpl_o(light->position, *pos, sub);
	normalize(lightv);
	light_dot_normal = dot_p(*lightv,*normalv);
	if (light_dot_normal >= 0.0)
		diffuse = color_s_mul(effective_color, light_dot_normal);
	if (diffuse)
		specular = compute_specular(m, light, lightv, normalv, eyev);
	return (colors_operation(diffuse, specular, add));
}

t_intersect	*new_intersect(void)
{
	t_intersect	*ret;

	ret = ft_malloc(sizeof(t_intersect), 0);
	ret->next = NULL;
	return (ret);
}


















































// void compute_u_v(t_tuple *pos, uint32_t *u, uint32_t *v, mlx_texture_t *texture)
// {
//     double theta, phi;
//     double uu, vv;

//     // Convert Cartesian coordinates (x, y, z) into spherical coordinates
//     theta = atan2(pos->z, pos->x); // [-π, π]
//     phi = acos(pos->y / magnitude(*pos)); // [0, π]

//     // Convert to UV space (range [0,1])
//     uu = (theta + M_PI) / (2.0 * M_PI); 
//     vv = 1.0 - (phi / M_PI); // Flip V to match texture coordinates

//     // Convert to integer texture coordinates
//     *u = (uint32_t)(uu * (texture->width - 1));
//     *v = (uint32_t)(vv * (texture->height - 1));
// }

// t_tuple *compute_tangent(t_tuple normal)
// {
//     t_tuple reference, *tangent;


//     if (fabs(normal.y) > 0.9) 
//         reference = (t_tuple){1.0, 0.0, 0.0, 0.0};
//     else 
//         reference = (t_tuple){0.0, 1.0, 0.0, 0.0};

//     tangent = cross_p(reference, normal);
// 	normalize(tangent);
//     return (tangent);
    
// }


// t_tuple apply_bump_mapping(t_material *m, t_tuple *normal, t_tuple *pos)
// {
// 	uint32_t u, v;
// 	t_tuple *tangent, *bitangent, *perturbed_normal;
// 	uint8_t *bump_pixel;
// 	double bump_intensity;

// 	// Compute texture coordinates (u, v)
// 	compute_u_v(pos, &u, &v, m->bump_map);

// 	// Get bump map value at (u, v)
// 	bump_pixel = &m->bump_map->pixels[(v * m->bump_map->width + u) * m->bump_map->bytes_per_pixel];
// 	bump_intensity = (bump_pixel[0] / 255.0) * 2.0 - 1.0;  // Convert to [-1, 1] range

// 	// Compute tangent and bitangent vectors for the surface
// 	tangent = compute_tangent(*normal);
// 	bitangent = cross_p(*normal, *tangent);

// 	// Apply bump effect to normal
// 	perturbed_normal = tpl_o(*normal, *scalar(*tangent, bump_intensity * m->bump_scale),add);
// 	perturbed_normal = tpl_o(*perturbed_normal, *scalar(*bitangent, bump_intensity * m->bump_scale),add);

// 	// Normalize the perturbed normal
// 	return *perturbed_normal;
// }

// t_color	*compute_lightning(t_material *m, \
// 				t_light *light, t_tuple *pos, t_tuple *normalv, t_tuple *eyev, t_color *col)
// {
// 	t_color	*effective_color;
// 	t_color	*diffuse;
// 	t_tuple	*lightv;
// 	double	light_dot_normal;
// 	t_color	*specular;
// 	t_tuple	bumped_normal;

// 	diffuse = NULL;
// 	specular = NULL;

// 	// Compute effective color (surface color * light color)
// 	effective_color = colors_operation(&light->color, col, mul);

// 	// Compute light direction (from hit point to light)
// 	lightv = tpl_o(light->position, *pos, sub);
// 	normalize(lightv); 

// 	// If bump mapping is enabled, modify the normal vector
// 	if (m->bump_map)
// 	{
// 		bumped_normal = apply_bump_mapping(m, normalv, pos);
// 		normalize(&bumped_normal);
// 		normalv = &bumped_normal;  // Use modified normal for shading
// 	}

// 	// Compute dot product between light direction and (possibly bumped) normal
// 	light_dot_normal = dot_p(*lightv, *normalv);

// 	// If light is hitting the surface, compute diffuse lighting
// 	if (light_dot_normal >= 0.0)
// 		diffuse = color_s_mul(effective_color, light_dot_normal);

// 	// Compute specular reflection if diffuse lighting exists
// 	if (diffuse)
// 		specular = compute_specular(m, light, &lightv, normalv, eyev);

// 	// Combine diffuse and specular lighting
// 	return (colors_operation(diffuse, specular, add));
// }