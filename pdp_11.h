#define MEMSIZE (64*1024)
#define pc reg[7]


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_R 8


typedef unsigned char byte;
typedef unsigned short int word;
typedef word Address;


typedef struct {
    word val;       //значение аргумента
    word adr;       //адрес аргумента
} Argument;


typedef struct {
    word mask;
    word opcode;
    char *name;
    void (* do_func)(Argument ss, Argument dd, unsigned int nn, unsigned int r);
    char params;
} Command;


extern byte mem[];
extern word reg[];
extern Command cmd[];
extern int word_or_byte;

void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file(const char * filename);
void mem_dump(Address adr, word n);
void trace(const char* format, ...);


void do_halt(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_mov(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_add(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_nothing(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_sob(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_clr(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void do_movb(Argument ss, Argument dd, unsigned int nn, unsigned int r);
void run();
void print_reg();
Argument get_mr(word w);