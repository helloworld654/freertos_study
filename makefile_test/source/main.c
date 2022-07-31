#include <stdio.h>
#include "fun0.h"
#include "fun1.h"
#include "fun_lib_a.h"
#include "fun_lib_so.h"

/*
1. cd generic_lib/liba/ , do make
2. cd generic_lib/libso/ , do make
3. copy generic_lib/liba/output/libfun_a.a and generic_lib/libso/output/libfun_so.so to lib/
4. do make
5. ./output/app_1.0.0
*/

int main(void)
{
    #ifdef USE_DEBUG
        printf("Debug Application startup.\r\n");
    #endif
    
        fun0_printf();
        fun1_printf();
        fun_lib_a_printf();
        // fun_lib_so_printf();    //need copy generic_lib/libso/libfun_so.so to /lib or /usr/lib
        return 0;
}

// reference:
// https://mp.weixin.qq.com/s?__biz=MzU5MzcyMjI4MA==&mid=2247505573&idx=1&sn=71e27b7d822db997d1e7590cb51f6d04&chksm=fe0eb862c9793174a769a3e9a237f49ce0959f9dcc0fd4df6a8e27bfdaba40515b70da44aaea&scene=21#wechat_redirect
