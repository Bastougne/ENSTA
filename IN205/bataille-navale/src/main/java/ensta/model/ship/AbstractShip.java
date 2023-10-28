package ensta.model.ship;

import ensta.util.Orientation;
import java.io.Serializable;

public class AbstractShip implements Serializable {
    protected Character label;
    protected String name;
    protected int size;
    protected Orientation orientation;
    protected int strikeCount;

    public Character getLabel() { return label; }
    public String getName() { return name; }
    public int getLength() { return size; }
    public Orientation getOrientation() { return orientation; }

    public void setOrientation( Orientation orientation ) {
        this.orientation = orientation;
    }

    public AbstractShip( String name, Character label, int size, Orientation orientation ) {
        this.name = name;
        this.label = label;
        this.size = size;
        this.orientation = orientation;
        this.strikeCount = 0;
    }

    public void addStrike() { strikeCount++; }

    public boolean isSunk() { return strikeCount >= size; }
}
