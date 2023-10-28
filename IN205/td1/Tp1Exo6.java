import java.util.Scanner;

public class Tp1Exo6 {
    public static void main(String[] args) {
        int nombre = 1 + (int)( 100 * Math.random() );
        int maxTentatives = 10;
        int essai = 0, tentatives = 0;
        Scanner scanner = new Scanner( System.in );
        System.out.println( maxTentatives + " tentatives" );
        while ( essai != nombre && tentatives < maxTentatives ) {
            essai = scanner.nextInt();
            tentatives++;
            if ( essai > nombre )
                System.out.println( "Trop grand" );
            if ( essai < nombre )
                System.out.println( "Trop petit" );
        }
        scanner.close();
        System.out.print( "Réussi en " + tentatives + " tentatives" );
    }
}
