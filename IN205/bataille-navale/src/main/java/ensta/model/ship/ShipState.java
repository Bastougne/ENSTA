package ensta.model.ship;

import ensta.util.Orientation;
import java.io.Serializable;

public class ShipState implements Serializable {
    private AbstractShip ship;
    private boolean struck;

    public ShipState() {
        ship = new AbstractShip( "No ship", '0', 0, Orientation.NULL ); // default ship, used in board.hasShip
        struck = false;
    }

    public void addStrike() { ship.addStrike(); }

    public boolean isStruck() { return struck; }

    public String toString() {

        // final String ANSI_RESET = "\u001B[0m";
        // final String ANSI_COLOUR = ( isStruck() ) ? "\u001B[31m" : "\u001B[30m";
        return ship.getLabel().toString();
        // return ANSI_COLOUR + ship.getLabel() + ANSI_RESET;
    }

    public boolean isSunk() { return ship.isSunk(); }

    public AbstractShip getShip() { return ship; }

    public void setShip( AbstractShip ship ) { this.ship = ship; }
}
