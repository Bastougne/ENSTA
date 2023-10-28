import java.util.Collections;
import java.util.List;

public class Kruskal {

    public static void main( String[] args ) {

        /* Create a graph which contains nodes a, b, c, d, e, f, g */
        Graph g = new Graph( new String[] { "a", "b", "c", "d", "e", "f", "g" } );

        /* Add the edges */
        g.addEdge( "a", "b", 1.0 );
        g.addEdge( "a", "c", 3.0 );
        g.addEdge( "b", "c", 2.0 );
        g.addEdge( "b", "d", 5.0 );
        g.addEdge( "b", "e", 7.0 );
        g.addEdge( "b", "f", 9.0 );
        g.addEdge( "c", "d", 4.0 );
        g.addEdge( "d", "e", 6.0 );
        g.addEdge( "d", "g", 12.0 );
        g.addEdge( "e", "f", 8.0 );
        g.addEdge( "e", "g", 11.0 );
        g.addEdge( "f", "g", 10.0 );

        System.out.println( g );

        /* Get a minimum spanning tree of the graph */
        Graph tree = kruskal( g, true );

        /* If there is such a tree (i.e., if the graph is connex */
        if ( tree != null )

            /* Display it */
            System.out.println( tree );

        else
            System.out.println( "No spanning tree" );
    }

    /**
     * Apply Kruskal algorithm to find a minimal spanning tree of a graph
     * @return A tree which corresponds a minimal spanning tree of the graph; null if there is none
     */
    public static Graph kruskal( Graph g, boolean computeMin ) {

        /* Create a new graph with the same nodes than g */
        Graph tree = new Graph( g.nodes );

        /* Get all the edges from g */
        List<Edge> edges = g.getEdges();

        /* Sort the edges by increasing weight */
        Collections.sort( edges );

        /* Sort by decreasing weight if looking for maximum spanning tree */
        if ( !computeMin )
        Collections.reverse( edges );

        /* current edge index */
        int j = 0;

        for ( int i = 0; i < tree.nodes.length - 1; i++ ) {
            while ( j < edges.size() && tree.createACycle( edges.get( j ) ) )
                j++;
            if ( j >= edges.size() )
                return null;
            tree.addEdge( edges.get( j ) );
            j++;
        }
        return tree;
    }
}
