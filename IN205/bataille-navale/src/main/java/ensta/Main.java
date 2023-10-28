package ensta;

import ensta.controller.Game;

public class Main {

	public static void main(String args[]) {
        
        System.out.print( "\033[H\033[2J" ); // clearing the console
        System.out.flush();

        new Game().init().run();
    }

}
