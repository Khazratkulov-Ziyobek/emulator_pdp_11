typedef unsigned char byte;
typedef unsigned short int word;
typedef word Address;


#define MEMSIZE (64*1024)
#define pc reg[7]

extern byte mem[];
extern word reg[];


void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file();
void mem_dump(Address adr, word n);
void trace(const char* format, ...);