package ensta.model;

import java.io.Serializable;

import ensta.model.ship.AbstractShip;
import ensta.model.ship.ShipState;
import ensta.util.ColorUtil;
import ensta.util.ColorUtil.Color;
import ensta.util.Orientation;

public class Board implements IBoard, Serializable {

    private static final int DEFAULT_SIZE = 10;

    private String name;
    private int size;
    private ShipState[][] myBoats;
    private Boolean[][] myHits;

    public Boolean[][] getMyHits() { return myHits; }

    public String getName() { return name; }

    public Board( String name, int size ) {
        this.name = name;
        this.size = size;
        myBoats = new ShipState[size][size];
        myHits = new Boolean[size][size];
        for ( int i = 0; i < size; i++ ) {
            for ( int j = 0; j < size; j++ ) {
                myBoats[i][j] = new ShipState();
                myHits[i][j] = null;
            }
        }
    }

    public Board( String name ) {
        this( name, DEFAULT_SIZE );
    }

    public String boolToStr( Boolean bool ) {
        if ( bool == null )
            return ".";
        return ColorUtil.colorize( "X", ( bool ) ? ColorUtil.Color.RED : ColorUtil.Color.WHITE );
    }

    public void print( Boolean[][] hits ) {
        Color labelColor = Color.WHITE;

        System.out.println( "Navires :                Frappes :\n" );
        System.out.print( "  " );
        for ( int i = 0; i < size; i++ ) {
            System.out.print( i );
            System.out.print( ' ' );
        }
        System.out.print( "     " );
        for ( int i = 0; i < size; i++ ) {
            System.out.print( i );
            System.out.print( ' ' );
        }
        System.out.print( '\n' );
        for ( int i = 0; i < size; i++ ) {
            System.out.print( (char)( i + 65 ) );
            System.out.print( ' ' );
            for ( int j = 0; j < size; j++ ) {
                if ( hits[i][j] == null ) {
                    labelColor = Color.WHITE;
                } else if ( hits[i][j] == true ) {
                    labelColor = Color.RED;
                } else if ( hits[i][j] == false ) {
                    labelColor = Color.BLACK;
                }
                System.out.print( ColorUtil.colorize( myBoats[i][j].toString(), labelColor ) );
                System.out.print( ' ' );
            }
            System.out.print( "   " );
            System.out.print( (char)( i + 65 ) );
            System.out.print( ' ' );
            for ( int j = 0; j < size; j++ ) {
                System.out.print( boolToStr( myHits[i][j] ) );
                System.out.print( ' ' );
            }
            System.out.print( '\n' );
        }
        System.out.print( '\n' );
    }

    public boolean canPutShip( AbstractShip ship, Coords coords, boolean display ) {
        Orientation o = ship.getOrientation();
        int dx = 0, dy = 0; // vertical is x ( A, B , ... ) and horizontal is y( 0, 1, ... )
        if ( o == Orientation.EAST ) {
            if ( coords.getY() + ship.getLength() > this.size ) {
                if ( display )
                    System.out.println( "Invalid coordinates" );
                return false;
            }
            dy = 1;
        } else if ( o == Orientation.SOUTH ) {
            if ( coords.getX() + ship.getLength() > this.size ) {
                if ( display )
                    System.out.println( "Invalid coordinates" );
                return false;
            }
            dx = 1;
        } else if ( o == Orientation.NORTH ) {
            if ( coords.getX() + 1 - ship.getLength() < 0 ) {
                if ( display )
                    System.out.println( "Invalid coordinates" );
                return false;
            }
            dx = -1;
        } else if ( o == Orientation.WEST ) {
            if ( coords.getY() + 1 - ship.getLength() < 0 ) {
                if ( display )
                    System.out.println( "Invalid coordinates" );
                return false;
            }
            dy = -1;
        }

        Coords iCoords = new Coords( coords );

        for ( int i = 0; i < ship.getLength(); ++i ) {
            if ( this.hasShip( iCoords ) ) {
                if ( display )
                    System.out.println( "Trying to place ship on existing ship !" );
                return false;
            }
            iCoords.setX( iCoords.getX() + dx );
            iCoords.setY( iCoords.getY() + dy );
        }
        return true;
    }

    public int getSize() { return size; }

    public boolean putShip( AbstractShip ship, Coords coords, boolean display ) {
        if ( !canPutShip( ship, coords, display ) )
            return false;
        Orientation o = ship.getOrientation();
        int dx = 0, dy = 0;
        if ( o == Orientation.EAST ) {
            dy = 1;
        } else if ( o == Orientation.SOUTH ) {
            dx = 1;
        } else if ( o == Orientation.NORTH ) {
            dx = -1;
        } else if ( o == Orientation.WEST ) {
            dy = -1;
        }

        Coords iCoords = new Coords( coords );

        for ( int i = 0; i < ship.getLength(); ++i ) {
            myBoats[iCoords.getX()][iCoords.getY()].setShip( ship );
            iCoords.setX( iCoords.getX() + dx );
            iCoords.setY( iCoords.getY() + dy );
        }

        return true;
    }

    public boolean hasShip( Coords coords ) {
        return myBoats[coords.getX()][coords.getY()].getShip().getLabel() != '0';
    }

    public void setHit( boolean hit, Coords coords ) {
        myHits[coords.getX()][coords.getY()] = hit;
    }

    public Boolean getHit( Coords coords ) { return myHits[coords.getX()][coords.getY()]; }

    public Hit sendHit( int x, int y ) {
        Coords res = new Coords( x, y );
        if ( !hasShip( res ) ) {
            return Hit.MISS;
        } else {
            AbstractShip ship = myBoats[res.getX()][res.getY()].getShip();
            ship.addStrike();
            if ( !ship.isSunk() ) {
                return Hit.STRIKE;
            } else if ( ship.getLabel() == 'D' ) {
                return Hit.DESTROYER;
            } else if ( ship.getLabel() == 'S' ) {
                return Hit.SUBMARINE;
            } else if ( ship.getLabel() == 'B' ) {
                return Hit.BATTLESHIP;
            } else if ( ship.getLabel() == 'C' ) {
                return Hit.CARRIER;
            } else {
                return null;
            }
        }
    }
}
