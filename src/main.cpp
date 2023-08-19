/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/19 17:22:36 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

int		main(int argc, char **argv)
{
	bool	fullscreen = false;
	if (argc != 2)
	{
		std::cout << "usage: ./scop <obj_path> [-f (fullscreen)]" << std::endl;
		exit(-1);
	}
	render	scop(4, 3, 3, 640, 480, "GLFW BUT IN A CLASS !", argv[1], fullscreen);
	scop.loop();
	std::cout << "Program end" << std::endl;
	return (0);
}
