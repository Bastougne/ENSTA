package ensta.ai;
import ensta.model.Board;
import ensta.model.Coords;
import ensta.model.Hit;
import ensta.model.Player;
import ensta.model.ship.AbstractShip;
import java.util.List;

public class PlayerAI extends Player {
    /* **
     * Attribut
     */
    private BattleShipsAI ai;

    /* **
     * Constructeur
     */
    public PlayerAI( Board ownBoard, Board opponentBoard, List<AbstractShip> ships ) {
        super( ownBoard, opponentBoard, ships );
        ai = new BattleShipsAI( ownBoard, opponentBoard );
    }

    public void putShips() { ai.putShips( ships ); }

    public void putShips( Boolean[][] hits ) { ai.putShips( ships ); }

    public Hit sendHit( Coords coords ) { return ai.sendHit( coords ); }
}
