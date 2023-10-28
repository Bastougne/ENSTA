class Tableau {

    public static void main( String[] args ) {
        /**
         * Les diverses manieres de déclaration d'un tableau. *
         */

        double[] doubleArray;
        double[] doubleArray1;
        double doubleArray2[];
        double doubleArray3[];

        /**
        Une simple déclaration de tableau ne permet pas d'y acceder.
        Décommenter la ligne suivante, voir ce qui se passe à la compilation
        *
        */

        // System.out.println(stringArray[0]);

        /**
        Instanciation du tableau precedemment déclaré.
        Dans l'instruction ecrite ci-dessous, on instancie un tableau de 3 elements
        *
      */

        doubleArray = new double[3];

        /**
        Ecrire ci-dessous une instruction qui permet d'acceder à un element du tableau
        Que remarquez-vous ?
        *
      */

        System.out.println( doubleArray[0] );

        /**
        Changement d'un emplacement du tableau
        *
      */

        doubleArray[0] = 1.0;

        /**
        En Java, il n'est pas possible d'acceder à un emplacement qui depasse n-1 (où n est la taille du tableau)
        Décommenter l'instruction suivante, voir ce qui se passe à l'execution
        *
      */

        // doubleArray[3] = 2.0;

        /**
        Autres manieres d'instanciation
        *
      */

        int[] intArray = new int[] { 42, 55, 99 };

        int[] intArrayAnonymous = { 42, 55, 99, 100 };

        //**************//

        System.out.println( "Taille du tableau intArrayAnonymous : " + intArrayAnonymous.length ); // Avoir la taille du tableau

        /**
        Parcourir un tableau et afficher les elements
        *
      */

        for ( int index = 0; index < intArrayAnonymous.length; index++ ) {
            if ( index == intArrayAnonymous.length - 1 ) {
                System.out.println( intArrayAnonymous[index] );
            } else {
                System.out.print( intArrayAnonymous[index] + ", " );
            }
        }

        /***** Ou encore *****/

        for ( int value : intArrayAnonymous ) {
            System.out.println( value );
        }
    }
}
