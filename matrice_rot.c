/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocarta-l <ocarta-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 13:50:57 by ocarta-l          #+#    #+#             */
/*   Updated: 2016/07/25 14:29:14 by ocarta-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_raystruct.h"

// if ($kwargs['preset'] == self::RX)
// 		{
// 			$this->_matrix = array(array(	'1',				'0', 		'0', 						//'0' ),
// 							  array(		'0', 	cos($kwargs['angle']), -sin($kwargs['angle']), 		//'0' ),
// 							  array(		'0',	sin($kwargs['angle']), cos($kwargs['angle']), 		//'0' ),
// 							  // array(		'0', 				'0', 		'0', 						//'1' ));
// 		}
// 		if ($kwargs['preset'] == self::RY)
// 		{
// 		$this->_matrix = array(array(cos($kwargs['angle']), '0', 			sin($kwargs['angle']), 		//'0' ),
// 							  array('0', 					'1', 				'0', 					//'0' ),
// 							  array(-sin($kwargs['angle']), '0', 			cos($kwargs['angle']), 		//'0' ),
// 							  // array('0', 					'0', 				'0', 					//'1' ));
// 		}
// 		if ($kwargs['preset'] == self::RZ)
// 		{
// 		$this->_matrix = array(array(	cos($kwargs['angle']), 		-sin($kwargs['angle']), 	'0', 	//		'0' ),
// 							  array(	sin($kwargs['angle']), 		cos($kwargs['angle']), 		'0', 	//		'0' ),
// 							  array(			'0', 						'0', 				'1', 	//		'0' ),
// 							  // array(			'0', 						'0', 				'0', 	//		'1' ));

// $tmp = array('x' => 0, 'y' => 0, 'z' => 0, 'w' => 0);
// 		$tmp['x'] = $m->_x * $this->_matrix[0][0] + $m->_y * $this->_matrix[0][1] + $m->_z * $this->_matrix[0][2] //+ $m->_w * $this->_matrix[0][3];
// 		$tmp['y'] = $m->_x * $this->_matrix[1][0] + $m->_y * $this->_matrix[1][1] + $m->_z * $this->_matrix[1][2] //+ $m->_w * $this->_matrix[1][3];
// 		$tmp['z'] = $m->_x * $this->_matrix[2][0] + $m->_y * $this->_matrix[2][1] + $m->_z * $this->_matrix[2][2] //+ $m->_w * $this->_matrix[2][3];
// 		// $tmp['w'] = $m->_x * $this->_matrix[3][0] + $m->_y * $this->_matrix[3][1] + $m->_z * $this->_matrix[3][2] //+ $m->_w * $this->_matrix[3][3];

t_vector MatricerotX(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x ;
	result.y = v.y * cos(angle) + v.z * -sin(angle);
	result.z = v.y * sin(angle) + v.z * cos(angle);
	return (result);
}

t_vector MatricerotY(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(angle) + v.z * sin(angle);
	result.y = v.y ;
	result.z = v.x * -sin(angle) + v.z * cos(angle);
	return (result);
}

t_vector MatricerotZ(t_vector v, double angle)
{
	t_vector result;

	result.x = v.x * cos(angle) + v.y * -sin(angle);
	result.y = v.x * sin(angle) + v.y * cos(angle);
	result.z = v.z;
	return (result);
}