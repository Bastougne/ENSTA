public class Tp1Exo3 {
    public static int fibonacci( int n ) {
        int f0 = 0, f1 = 1, tempo;
        for ( int i = 0; i < n; i++ ) {
            tempo = f0 + f1;
            f0 = f1;
            f1 = tempo;
        }
        return f0;
    }
    public static void main( String[] args ) {
        System.out.print( fibonacci( 10 ) );
    }
}
