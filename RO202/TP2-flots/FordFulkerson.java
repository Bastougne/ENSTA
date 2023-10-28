import java.util.List;

public class FordFulkerson {

    public static void main( String[] args ) {

        /* The weight in graph g are the capacities of the arcs */
        Graph g = example();

        System.out.println( g );

        /* The weights in graph "flow" are the values of the flow */
        Graph flow = fordFulkerson( g, "s", "t" );

        System.out.println( flow );
    }

    /**
     * Function which creates an example graph on which Ford-Fulkerson will be applied
     */
    public static Graph example() {

        Graph g = new Graph( new String[] { "s", "a", "b", "c", "d", "e", "t" } );

        g.addArc( "s", "a", 8 );
        g.addArc( "s", "c", 4 );
        g.addArc( "s", "e", 6 );
        g.addArc( "a", "b", 10 );
        g.addArc( "a", "d", 4 );
        g.addArc( "b", "t", 8 );
        g.addArc( "c", "b", 2 );
        g.addArc( "c", "d", 1 );
        g.addArc( "d", "t", 6 );
        g.addArc( "e", "b", 4 );
        g.addArc( "e", "t", 2 );

        return g;
    }

    public static boolean marked( int[] mark, int i ) {
        return ( mark[i] != Integer.MAX_VALUE );
    }

    public static Graph fordFulkerson( Graph g, String sName, String tName ) {

        /* Mark of the nodes in the graph
         * - mark[i] is equal to +j if the node of index i can be reached by increasing the flow on arc ji;
         * - mark[i] is equal to -j if the node of index i can be reached by decreasing the flow on arc ij;
         * - mark[i] is equal to Integer.MAX_VALUE if the node is not marked.
         */
        int[] mark = new int[g.n];

        /* Get the index of nodes s and t */
        int s = g.indexOf( sName );
        int t = g.indexOf( tName );

        /* Create a new graph with the same nodes than g, which corresponds to the current flow */
        Graph flow = new Graph( g.nodes );

        /* Get all the arcs of the graph */
        List<Edge> arcs = g.getArcs();
        int i, j;
        double w;

        /* a node has been marked */
        boolean newMarked;

        int pivot;

        /* best flow update */
        // alpha non fonctionnel /!\ On augmente par pas de 1 ... (augmentation importante du temps d'execution)
        // double alpha;

        do {
            for ( i = 0; i < g.n; i++ )
                mark[i] = Integer.MAX_VALUE;
            mark[s] = s;

            do {
                // alpha = Integer.MAX_VALUE;
                newMarked = false;
                for ( Edge arc : arcs ) { // g and flow have the same arcs, but flow may have weight 0 arcs
                    i = arc.id1;
                    j = arc.id2;
                    w = flow.adjacency[i][j]; // can be 0
                    if ( marked( mark, i ) && !marked( mark, j ) && w < arc.weight ) {
                        mark[j] = i;
                        newMarked = true;
                        // if ( alpha > arc.weight - w )
                        //     alpha = w - arc.weight;
                    }
                    if ( !marked( mark, i ) && marked( mark, j ) && w > 0 ) {
                        mark[i] = -j;
                        newMarked = true;
                        // if ( alpha > w )
                        //     alpha = w;
                    }
                }

                // System.out.println( "\n\n" + alpha + "\n\n" );
            } while ( newMarked && ( marked( mark, t ) ) );
            if ( marked( mark, t ) ) {
                pivot = t;
                while ( pivot != s ) {
                    if ( mark[pivot] >= 0 ) {
                        // only works because 0 is source (0 has no sign so we can't know if marked forward or backward)
                        flow.adjacency[mark[pivot]][pivot]++; //= alpha;
                    } else {
                        flow.adjacency[pivot][-mark[pivot]]--; //= alpha;
                    }
                    pivot = mark[pivot];
                    pivot = ( pivot < 0 ) ? -pivot : pivot;
                }
            }
        } while ( marked( mark, t ) );
        return flow;
    }
}
