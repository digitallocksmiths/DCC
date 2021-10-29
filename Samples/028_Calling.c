
typedef void       (* pxvoid_void)(void);

extern void foo(void);
extern void bar(void);

pxvoid_void RomVmHandlers1[256] = {
    foo,
    bar
};

pxvoid_void fn1;

void main(void) {
    pxvoid_void fn2;
    pxvoid_void RomVmHandlers2[2];
    
    int i;
    
//  foo();
  fn1();
  fn2();
  RomVmHandlers1[1](); 
  RomVmHandlers2[1](); 

    RomVmHandlers1[i](); 
    
}

// #########################


typedef void       (* pxvoid_void)(void);
typedef void       (* pxvoid_int)(int);
typedef void       (* pxvoid_int_ptr)(int, void*);

extern void foo(void);
extern void bar(int);

typedef struct {
    int         iblob;
    pxvoid_void pfn1;
    pxvoid_int  pfn2;
} R_Elf, *TP_Elf;

R_Elf Elf = { 1, foo, bar };

void main(void) {
    TP_Elf pElf = &Elf;
    pxvoid_int pF;
    pxvoid_int_ptr pF2;
   // bar(2);
   // pF(2);
   // pElf->pfn2(2);


    pF2(1, (TP_Elf)((void*)0));
    
}



