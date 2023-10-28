package ensta.controller;

import ensta.ai.PlayerAI;
import ensta.model.Board;
import ensta.model.Coords;
import ensta.model.Hit;
import ensta.model.Player;
import ensta.model.ship.AbstractShip;
import ensta.model.ship.BattleShip;
import ensta.model.ship.Carrier;
import ensta.model.ship.Destroyer;
import ensta.model.ship.Submarine;
import ensta.util.ColorUtil;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Arrays;
import java.util.List;

public class Game {

    /*
     * *** Constante
     */
    public static final File SAVE_FILE = new File( "savegame.dat" );

    /*
     * *** Attributs
     */
    private Player player1;
    private Player player2;

    /*
     * *** Constructeurs
     */
    public Game() {
    }

    public Game init() {
        if ( !loadSave() ) {

            Board board1 = new Board( "Board 1" );
            Board board2 = new Board( "Board 2" );

            player1 = new Player( board1, board2, createDefaultShips() );
            player2 = new PlayerAI( board2, board1, createDefaultShips() );

            player1.getBoard().print( player2.getBoard().getMyHits() );
            player1.putShips( player2.getBoard().getMyHits() );
            player2.putShips( player1.getBoard().getMyHits() );
        } else {
            player1.getBoard().print( player2.getBoard().getMyHits() );
        }
        return this;
    }

    /*
     * *** Méthodes
     */
    public void run() {

        Coords coords = new Coords();
        Board b1 = player1.getBoard();
        Board b2 = player2.getBoard();
        Hit hit;
        boolean strike;

        // main loop
        boolean done;
        do {
            hit = player1.sendHit( coords );
            strike = ( hit != Hit.MISS );
            b1.setHit( strike, coords );

            System.out.print( "\033[H\033[2J" ); // clearing the console
            System.out.flush();
            System.out.println( makeHitMessage( false /* outgoing hit */, coords, hit ) );

            hit = player2.sendHit( coords );
            strike = ( hit != Hit.MISS );
            b2.setHit( strike, coords );

            System.out.println( makeHitMessage( true /* incoming hit */, coords, hit ) );
            System.out.print( '\n' );
            b1.print( b2.getMyHits() );

            done = updateScore();

            save();

        } while ( !done );

        SAVE_FILE.delete();
        System.out.println( String.format( "joueur %d gagne", player1.hasLost() ? 2 : 1 ) );
    }

    private void save() {
        try {
            if ( !SAVE_FILE.exists() ) {
                SAVE_FILE.getAbsoluteFile().getParentFile().mkdirs();
            }
            ObjectOutputStream oos = new ObjectOutputStream( new FileOutputStream( SAVE_FILE ) );
            oos.writeObject( player1 );
            oos.writeObject( player2 );

            oos.close();

        } catch ( IOException e ) {
            e.printStackTrace();
        }
    }

    private boolean loadSave() {
        if ( SAVE_FILE.exists() ) {
            try {
                ObjectInputStream ois = new ObjectInputStream( new FileInputStream( SAVE_FILE ) );
                player1 = (Player)ois.readObject();
                player2 = (Player)ois.readObject();
                ois.close();
                return true;
            } catch ( IOException | ClassNotFoundException e ) {
                ( (Throwable)e ).printStackTrace();
            }
        }
        return false;
    }

    private boolean updateScore() {
        for ( Player player : new Player[] { player1, player2 } ) {
            int destroyed = 0;
            for ( AbstractShip ship : player.getShips() ) {
                if ( ship.isSunk() ) {
                    destroyed++;
                }
            }

            player.setDestroyedCount( destroyed );
            player.setLose( destroyed == player.getShips().length );
            if ( player.hasLost() ) {
                return true;
            }
        }
        return false;
    }

    private String makeHitMessage( boolean incoming, Coords coords, Hit hit ) {
        String msg;
        ColorUtil.Color color = ColorUtil.Color.RESET;
        switch ( hit ) {
        case MISS:
            msg = hit.toString();
            break;
        case STRIKE:
            msg = hit.toString();
            color = ColorUtil.Color.RED;
            break;
        default:
            msg = hit.toString() + " coulé";
            color = ColorUtil.Color.RED;
        }
        msg = String.format( "%s Frappe en %c%d : %s", incoming ? "<=" : "=>", (char)( 'A' + coords.getX() ), coords.getY(), msg );
        return ColorUtil.colorize( msg, color );
    }

    private static List<AbstractShip> createDefaultShips() {
        return Arrays.asList( new AbstractShip[] { new Destroyer(), new Submarine(), new Submarine(), new BattleShip(), new Carrier() } );
    }
}
