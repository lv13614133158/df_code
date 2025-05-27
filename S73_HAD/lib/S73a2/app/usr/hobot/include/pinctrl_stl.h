/*
 * Horizon Robotics
 *
 *  Copyright (C) 2020 Horizon Robotics Inc.
 *  All rights reserved.
 *  Author: xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __PINCTRL_STL_H_
#define __PINCTRL_STL_H_

#include "diag_lib.h"

int32_t pinctrl_stl_init(struct user_stl_func *stl_info);
int32_t pinctrl_stl_handle(struct user_stl_func *stl_info);
int32_t pinctrl_stl_deinit(struct user_stl_func *stl_info);
int32_t pinctrl_stl_inject(struct user_stl_func *stl_info);
int32_t pinctrl_stl_selfcheck(struct user_stl_func *stl_info);
int32_t pinctrl_stl_clear(struct user_stl_func *stl_info);
#endif
