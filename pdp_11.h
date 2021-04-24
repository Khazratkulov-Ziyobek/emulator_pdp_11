typedef unsigned char byte;
typedef unsigned short int word;
typedef word Address;


#define MEMSIZE (64*1024)
#define pc reg[7]


typedef struct {
    word mask;
    word opcode;
    char *name;
    void (* do_func)(void);
} Command;

typedef struct {
    word val;   //значение аргумента
    word adr;   //адрес аргумента
} Argument;


extern byte mem[];
extern word reg[];
extern Command cmd[];
extern Argument ss, dd;


void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file();
void mem_dump(Address adr, word n);
void trace(const char* format, ...);


void do_halt();
void do_mov();
void do_add();
void do_nothing();
void run();
void print_reg();