public class Singleton {

    // Singleton Logic

    protected void finalize() {
        print( "finalize()" );
    }

    public static void print( Object o ) {
        System.out.println( o );
    }

    public static void main( String[] args ) {
        Singleton s1 = new Singleton();
        Singleton s2 = new Singleton();
        Singleton s3 = s1;
        print( s1 == s2 );
        print( s1 == s3 );
        s2 = s3;
        System.gc();
    }
}