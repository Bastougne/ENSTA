#include <assert.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct fs_header {
    char _rom1fs_[8];
    char full_size[4];
    char checksum[4];
    char *rest;
};

char *addb0( char *str, int size ) {
    char *strb0 = malloc( ( size + 1 ) * sizeof( char ) );
    for ( int i = 0; i < size; i++ ) {
        strb0[i] = str[i];
    }
    strb0[size] = '\0';
    return ( strb0 );
}

uint32_t read32( char ptr[4] ) {
    uint32_t value = 0;
    int pow = 1;
    for ( int i = 0; i < 4; i++ ) {
        value += ptr[3 - i] * pow;
        pow *= 256;
    }
    return ( value );
}

int padded16( int value ) {
    if ( value % 16 == 0 ) {
        return ( value );
    } else {
        return ( 16 * ( value / 16 + 1 ) );
    }
}

void decode( struct fs_header *p, size_t size ) {
    char *rom1fs = addb0( p->_rom1fs_, 8 );
    uint32_t full_size = read32( p->full_size );
    uint32_t checksum = read32( p->checksum );
    char *volume_name = (char *)&p->rest;
    char *file_headers = volume_name;
    while ( *file_headers != '\0' ) {
        file_headers++;
    }
    file_headers = volume_name + padded16( file_headers - volume_name );
    printf( "_rom1fs_ : %s\nfull_size : %d\nchecksum : %d\nvolume name : %s\nfile headers : %s\n", rom1fs, full_size, checksum, volume_name, file_headers );
    free( rom1fs );
}

int main( int argc, char *argv[] ) {
    int fd = open( "fs.romfs", O_RDONLY );
    assert( fd != -1 );
    int fsize = lseek( fd, 0, SEEK_END );
    printf( "size is %d\n\n", fsize );
    struct fs_header *addr = mmap( addr, fsize, PROT_READ, MAP_SHARED, fd, 0 );
    assert( addr != MAP_FAILED );
    decode( addr, fsize );
    return ( 0 );
}