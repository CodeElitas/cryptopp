#define GNUC_VERSION (__GNUC__*1000 + __GNUC_MAJOR__*10)
#if (GNUC_VERSION >= 4060) || defined(__clang__)
# pragma GCC diagnostic ignored "-Wdeprecated"
#endif

#include <altivec.h>
int main(int argc, char* argv[])
{
#if defined(_ARCH_PWR8)
    __vector unsigned long long x = {1, 2};
    __vector unsigned long long y = vec_xl(0, (__vector unsigned long long*)argv[0]);
    __vector unsigned long long z = vec_add(x, y);
#  if defined(__ibmxl__) || (defined(_AIX) && defined(__xlC__))
    __vector unsigned long long u = __vpmsumd (x, y);
#  elif defined(__clang__)
    __vector unsigned long long u = __builtin_altivec_crypto_vpmsumd (x, y);
#  else
    __vector unsigned long long u = __builtin_crypto_vpmsumd (x, y);
#  endif
#else
    int x[-1];
#endif
    return 0;
}
