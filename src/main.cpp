/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:31:20 by agirona           #+#    #+#             */
/*   Updated: 2023/08/16 13:07:46 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/render.hpp"

int		main(void)
{
	render	test(4, 3, 3, 640, 480, "GLFW BUT IN A CLASS !", "objects/barbara.obj");
	test.loop();
	std::cout << "Program end" << std::endl;
	return (0);
}
