#ifndef __MMC_STL_H_
#define __MMC_STL_H_

#include "diag_lib.h"
#include "diag_lib_id.h"

int32_t mmc_stl_init(struct user_stl_func *stl_info);
int32_t mmc_stl_handle(struct user_stl_func *stl_info);
int32_t mmc_stl_deinit(struct user_stl_func *stl_info);
int32_t mmc_stl_inject(struct user_stl_func *stl_info);
int32_t mmc_stl_selfcheck(struct user_stl_func *stl_info);
int32_t mmc_stl_clear(struct user_stl_func *stl_info);
#endif
