package ensta.view;

import java.util.Arrays;
import java.util.Scanner;

public final class InputHelper {

    private static Scanner scanner = new Scanner( System.in );

    /*
     * ** Constructeur
     */
    private InputHelper() {
    }

    /*
     * ** Classe ShipInput, interne à InputHelper
     */
    public static class ShipInput {
        public String orientation;
        public int x;
        public int y;
    }

    /*
     * ** Classe CoordInput, interne à InputHelper
     */
    public static class CoordInput {
        public int x;
        public int y;
    }

    /*
     * ** Méthodes de la classe InputHelper
     */
    public static ShipInput readShipInput( int size ) {
        ShipInput res = new ShipInput();
        String[] validOrientations = { "north", "south", "east", "west" }; // North, South, East, West
        boolean done = false;
        do {
            try {
                String[] in = scanner.nextLine().split( " " );
                if ( in.length == 2 ) {
                    String coord = in[0].toUpperCase(); // safety measure, we use upper case here bc of board.print()
                    String orientation = in[1].toLowerCase();
                    if ( Arrays.asList( validOrientations ).contains( orientation ) ) {
                        res.orientation = orientation;
                        res.x = coord.charAt( 0 ) - 'A';
                        res.y = Integer.parseInt( coord.substring( 1, coord.length() ) );
                        if ( res.x >= 0 && res.x < size && res.y >= 0 && res.y < size ) {
                            done = true;
                        } else {
                            System.err.println( "Coordinates are out of range !" );
                        }
                    }
                }
            } catch ( Exception e ) {
            }
            if ( !done ) {
                System.err.println( "Format incorrect! Entrez la position sous forme 'A0 north'" );
            }
        } while ( !done && scanner.hasNextLine() );

        return res;
    }

    public static CoordInput readCoordInput( int size ) {
        CoordInput res = new CoordInput();
        boolean done = false;
        do {
            try {
                String coord = scanner.nextLine().toUpperCase();
                res.x = coord.charAt( 0 ) - 'A';
                res.y = Integer.parseInt( coord.substring( 1, coord.length() ) );
                if ( res.x >= 0 && res.x < size && res.y >= 0 && res.y < size )
                    done = true;
            } catch ( Exception e ) {
                System.err.println( "Format incorrect! Entrez la position sous forme 'A0'" );
            }
        } while ( !done && scanner.hasNextLine() );

        return res;
    }
}
