#ifndef INIT_H
# define INIT_H

/*---------------------init/---------------------*/

/**
 * @brief Initializes the MiniLibX context, main window, frame buffer, and wall
 * textures.
 *
 * This function sets up the graphics environment by initializing the MiniLibX
 * instance, creating the main window, generating the rendering frame, and
 * loading all wall textures. It also calculates the field of view (FOV) and
 * projection distance used for rendering.
 *
 * @param cube Pointer to the main cube structure that holds rendering and
 * window data.
 * @return 0 on success, or 1 if any initialization step fails.
 */
int	setup_mlx_context(t_cube *cube);

#endif