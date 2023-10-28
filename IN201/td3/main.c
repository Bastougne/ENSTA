#include <assert.h>
#include <stdio.h>

// question 1 :

#define STACK_SIZE 4096

char stack1[STACK_SIZE];
char stack2[STACK_SIZE];
char stack3[STACK_SIZE];
char stack4[STACK_SIZE];

typedef void *coroutine_t;

// question 2 :

/* Quitte le contexte courant et charge les registres et la pile de CR. */
void enter_coroutine( coroutine_t cr );

// question 3 :

/* Initialise la pile et renvoie une coroutine telle que, lorsqu’on entrera dedans,
elle commencera à s’exécuter à l’adresse initial_pc. */
coroutine_t init_coroutine( void *stack_begin, unsigned int stack_size, void ( *initial_pc )( void ) ) {
    char *stack_end = ( (char *)stack_begin ) + stack_size;
    void **ptr = (void **)stack_end;
    ptr--;
    *ptr = initial_pc; // pc
    ptr--;
    *ptr = NULL; // rbp
    ptr--;
    *ptr = NULL; // rbx
    ptr--;
    *ptr = NULL; // r12
    ptr--;
    *ptr = NULL; // r13
    ptr--;
    *ptr = NULL; // r14
    ptr--;
    *ptr = NULL; // r15

    return ptr;
}

// questions 4 :

void loop() {
    int i = 0;
    while ( 1 ) {
        printf( "loop1 : %d\n", i++ );
    }
}

/* int main() {
    coroutine_t c = init_coroutine( stack1, STACK_SIZE, &loop );
    enter_coroutine( c );
    return 0;
} */

// question 5 :

/* Sauvegarde le contexte courant dans p_from, et entre dans TO. */
void switch_coroutine( coroutine_t *p_from, coroutine_t to );

// question 6 :

coroutine_t c1;
coroutine_t c2;

void loop1() {
    int i = 0;
    while ( 1 ) {
        printf( "loop1 : %d\n", i++ );
        switch_coroutine( &c1, c2 );
    }
}

void loop2() {
    int i = 0;
    while ( 1 ) {
        printf( "loop2 : %d\n", i++ );
        switch_coroutine( &c2, c1 );
    }
}

/* int main() {
    c1 = init_coroutine( stack1, STACK_SIZE, &loop1 );
    c2 = init_coroutine( stack1, STACK_SIZE, &loop2 );

    loop1();
    return 0;
} */

// question 7 :

enum state { blocked,
             ready };

struct thread {
    coroutine_t c;
    enum state state;
};

// question 8 :

#define NUM_THREADS 3

coroutine_t scheduler;

struct thread thread_list[NUM_THREADS];
int current_thread_index = 0;

void scheduling() {
    printf( "hey scheduler\n" );
    current_thread_index = ( current_thread_index + 1 ) % NUM_THREADS;
    while ( thread_list[current_thread_index].state == blocked ) {
        current_thread_index = ( current_thread_index + 1 ) % NUM_THREADS;
    }
    switch_coroutine( &scheduler, thread_list[current_thread_index].c );
}

void yield() {
    printf( "hey yield\n" );
    switch_coroutine( &(thread_list[current_thread_index].c), scheduler );
}

void create_thread( void ( *initial_pc )( void ), char* stack ) {
    assert( current_thread_index < NUM_THREADS );
    thread_list[current_thread_index].c =
        init_coroutine( stack, STACK_SIZE, *initial_pc );
    thread_list[current_thread_index].state = ready;
    current_thread_index = ( current_thread_index + 1 ) % NUM_THREADS;
}

void loop_yield() {
    int i = 0;
    while ( 1 ) {
        printf( "loop%d : %d\n", current_thread_index, i++ );
        yield();
    }
}

int main() {
    scheduler = init_coroutine( stack4, STACK_SIZE, &scheduling );
    create_thread( &loop_yield, stack1 );
    create_thread( &loop_yield, stack2 );
    create_thread( &loop_yield, stack3 );

    loop_yield();
    return 0;
}
