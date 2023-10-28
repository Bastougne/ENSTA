package ensta.util;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public enum Orientation {
    SOUTH( 1 ),
    NORTH( -1 ),
    WEST( -1 ),
    EAST( 1 ),
    NULL( 0 );

    private static final List<Orientation> VALUES = Collections.unmodifiableList( Arrays.asList( values() ) );
    private static final int SIZE = VALUES.size();
    private static final Random RANDOM = new Random();
    private int increment;

    private Orientation( int increment ) {
        this.increment = increment;
    }

    public int getIncrement() {
        return increment;
    }

    public static Orientation randomOrientation() {
        return VALUES.get( RANDOM.nextInt( SIZE ) );
    }

    public static Orientation StringToOrientation( String orientationName ) {
        if ( orientationName.equals( "south" ) ) {
            return Orientation.SOUTH;
        } else if ( orientationName.equals( "north" ) ) {
            return Orientation.NORTH;
        } else if ( orientationName.equals( "west" ) ) {
            return Orientation.WEST;
        } else if ( orientationName.equals( "east" ) ) {
            return Orientation.EAST;
        } else {
            return Orientation.NULL;
        }
    }
}
