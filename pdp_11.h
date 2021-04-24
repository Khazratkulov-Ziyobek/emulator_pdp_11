typedef unsigned char byte;
typedef unsigned short int word;
typedef word Address;


#define MEMSIZE (64*1024)
#define pc reg[7]


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS (1 << 1)

typedef struct {
    word val;   //значение аргумента
    word adr;   //адрес аргумента
} Argument;

typedef struct {
    word mask;
    word opcode;
    char *name;
    void (* do_func)(Argument ss, Argument dd);
} Command;


extern byte mem[];
extern word reg[];
extern Command cmd[];



void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file();
void mem_dump(Address adr, word n);
void trace(const char* format, ...);


void do_halt(Argument ss, Argument dd);
void do_mov(Argument ss, Argument dd);
void do_add(Argument ss, Argument dd);
void do_nothing(Argument ss, Argument dd);
void run();
void print_reg();