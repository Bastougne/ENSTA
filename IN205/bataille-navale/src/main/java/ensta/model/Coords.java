package ensta.model;

import java.io.Serializable;
import java.util.Random;

public class Coords implements Serializable {
    private int x;
    private int y;

    public Coords( Coords coords ) {
        this.x = coords.x;
        this.y = coords.y;
    }

    public Coords() {
        x = 0;
        y = 0;
    }

    public Coords( int x, int y ) {
        this.x = x;
        this.y = y;
    }

    public int getX() { return x; }

    public int getY() { return y; }

    public void setX( int x ) { this.x = x; }

    public void setY( int y ) { this.y = y; }

    public void setCoords( Coords res ) {
        this.x = res.x;
        this.y = res.y;
    }

    public boolean isInBoard( int size ) {
        return ( 0 <= x && x < size && 0 <= y && y < size ) ? true : false;
    }

    public static Coords randomCoords( int size ) {
        Random rng = new Random();
        return new Coords( rng.nextInt( size ), rng.nextInt( size ) );
    }
}
