#define BUFSIZE 20000000
char buf[BUFSIZE], *pt = buf;
#define scan(tt) do { \
  int &t = tt; \
  t=0; \
  while (!((*pt) >= '0' && (*pt) <= '9')) pt ++; \
  while (((*pt) >= '0' && (*pt) <= '9')) t = t * 10 + (*(pt ++)) - '0'; \
} while (0)
 
int main() {
	fread(buf, 1, BUFSIZE, stdin);
	scan(N); scan(M); // ...
}

