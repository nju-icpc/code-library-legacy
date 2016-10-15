const int STK_SZ = 2000000; // 堆栈的格数
char STK[STK_SZ * sizeof(void*)];     
void *STK_BAK;

// 32/64位自动检测
#if defined(__i386__)
  define SP "%%esp"
#elif defined(__x86_64__)
  #define SP "%%rsp"
#endif

int main() {
  // 将堆栈指针移动到用户缓存
  asm volatile("mov " SP ",%0; mov %1," SP: "=g"(STK_BAK):"g"(STK+sizeof(STK)):);
  // 这时候就可以愉快地递归了！
  // 将堆栈指针恢复
  asm volatile("mov %0," SP::"g"(STK_BAK));
  return 0;
}
