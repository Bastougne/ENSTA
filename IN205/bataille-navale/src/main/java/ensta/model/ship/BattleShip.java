package ensta.model.ship;

import ensta.util.Orientation;

public class BattleShip extends AbstractShip {
    public BattleShip( Orientation orientation ) {
        super( "Battle Ship", 'B', 4, orientation );
    }

    public BattleShip() {
        this( Orientation.EAST );
    }
}
