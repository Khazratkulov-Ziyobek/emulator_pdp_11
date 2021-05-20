#define MEMSIZE (64*1024)
#define pc reg[7]


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_R 8
#define HAS_XX 16


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
    void (* do_func)(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
    char params;
} Command;


extern byte mem[];
extern word reg[];
extern Command cmd[];
extern int wb;
extern int check;
extern int N, Z, C;

void b_write(Address adr, byte b);
byte b_read(Address adr);
void w_write(Address adr, word w);
word w_read(Address adr);
void load_file(int argc, char  * argv[]);
void mem_dump(Address adr, word n);
void trace(const char* format, ...);
void check_trace(int argc, char  * argv[]);
void usage_print();
void check_bigtrace(int argc, char  * argv[]);

void do_halt(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_mov(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_add(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_nothing(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_sob(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_clr(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_movb(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_br(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_beq(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_ccc(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_cln(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_clz(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_clc(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_scc(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_sec(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_sen(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_sez(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void do_nop(Argument ss, Argument dd, unsigned int nn, unsigned int r, unsigned int xx);
void run();
void print_reg();
Argument get_mr(word w);