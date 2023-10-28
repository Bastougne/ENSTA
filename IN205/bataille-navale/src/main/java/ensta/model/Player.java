package ensta.model;

import ensta.model.ship.AbstractShip;
import ensta.util.Orientation;
import ensta.view.InputHelper;
import java.io.Serializable;
import java.util.List;

public class Player implements Serializable {
    /*
     * ** Attributs
     */
    private Board board;
    protected Board opponentBoard;
    private int destroyedCount;
    protected AbstractShip[] ships;
    private boolean lose;

    /*
     * ** Constructeur
     */
    public Player( Board board, Board opponentBoard, List<AbstractShip> ships ) {
        this.setBoard( board );
        this.ships = ships.toArray( new AbstractShip[0] );
        this.opponentBoard = opponentBoard;
    }

    /*
     * ** Méthodes
     */

    /**
     * Read keyboard input to get ships coordinates. Place ships on given
     * coodrinates.
     */
    public void putShips( Boolean[][] hits ) {
        int numberOfShips = ships.length;
        int i = 0;
        AbstractShip ship;
        InputHelper.ShipInput res;
        while ( i < numberOfShips ) {
            ship = ships[i];
            String msg = String.format( "placer %d : %s(%d)", i + 1, ship.getName(), ship.getLength() );
            System.out.println( msg );
            res = InputHelper.readShipInput( this.board.getSize() );
            ship.setOrientation( Orientation.StringToOrientation( res.orientation ) );
            System.out.print( "\033[H\033[2J" ); // clearing the console
            System.out.flush();
            if ( board.putShip( ship, new Coords( res.x, res.y ), true ) )
                i++;
            board.print( hits );
        }
    }

    public Hit sendHit( Coords coords ) {
        boolean done = false;
        Hit hit = null;

        do {
            System.out.println( "Où frapper?" );
            InputHelper.CoordInput hitInput = InputHelper.readCoordInput( board.getSize() );
            hit = opponentBoard.sendHit( hitInput.x, hitInput.y );
            coords.setX( hitInput.x );
            coords.setY( hitInput.y );
            done = ( hit != null );
        } while ( !done );

        return hit;
    }

    public AbstractShip[] getShips() {
        return ships;
    }

    public void setShips( AbstractShip[] ships ) {
        this.ships = ships;
    }

    public Board getBoard() {
        return board;
    }

    public void setBoard( Board board ) {
        this.board = board;
    }

    public int getDestroyedCount() {
        return destroyedCount;
    }

    public void setDestroyedCount( int destroyedCount ) {
        this.destroyedCount = destroyedCount;
    }

    public boolean hasLost() {
        return lose;
    }

    public void setLose( boolean lose ) {
        this.lose = lose;
    }
}
