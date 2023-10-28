#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

#define BUFFER_SIZE 4096

int main() {
    int father2son[2];
    int son2father[2];
    if ( pipe( father2son ) == -1 ) {
        return 0;
    }
    if ( pipe( son2father ) == -1 ) {
        return 0;
    }
    int pere = fork();

    if ( pere ) {
        // r = sprintf( out, "Papa\n" );
        printf( "Papa" );

    } else {
        // prctl( PR_SET_SECCOMP, SECCOMP_MODE_STRICT );
        // r = sprintf( out, "Fiston\n" );
        printf( "Fiston" );
    }
    return 0;
}

int interpreteur() {

    char in[BUFFER_SIZE], out[BUFFER_SIZE];
    int r = 0;
    int tempo_r;

    while ( ( tempo_r = read( 0, &in[r], BUFFER_SIZE ) ) > 0 ) {
        r += tempo_r;
    }
    char op;
    sscanf( in, "%c", &op );

    if ( op == '+' || op == '-' ) {
        int a, b;
        sscanf( in, "%d, %d", &a, &b );
        int c = a + b;
        r = sprintf( out, "%d\n", c );

    } else if ( op == 'e' ) {
        int c = system( &in[1] );
        r = sprintf( out, "%d\n", c );
    }

    int w = 0;
    do {
        w += write( 1, out, r );
    } while ( w < r );

    syscall( SYS_exit, 0 );
    return 0;
}