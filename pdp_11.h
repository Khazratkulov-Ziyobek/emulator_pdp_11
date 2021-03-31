typedef unsigned char byte;
typedef unsigned short int word;
typedef word Address;


#define MEMSIZE (64*1024)
void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file();
void debug(const char* format, ...);
void trace(const char* format, ...);