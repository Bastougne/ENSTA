package com.ensta.librarymanager.modele;

public class Livre {
    private int primaryKey;
    private String titre;
    private String auteur;
    private String isbn;

    public Livre( int primaryKey, String titre, String auteur, String isbn ) {
        this.primaryKey = primaryKey;
        this.titre = titre;
        this.auteur = auteur;
        this.isbn = isbn;
    }

    public Livre() {
        this.primaryKey = 0;
        this.titre = "";
        this.auteur = "";
        this.isbn = "";
    }

    public int getPrimaryKey() { return primaryKey; }
    public String getTitre() { return titre; }
    public String getAuteur() { return auteur; }
    public String getIsbn() { return isbn; }

    public void setPrimaryKey( int primaryKey ) { this.primaryKey = primaryKey; }
    public void setTitre( String titre ) { this.titre = titre; }
    public void setAuteur( String auteur ) { this.auteur = auteur; }
    public void setIsbn( String isbn ) { this.isbn = isbn; }

    public String toString() {
        return "Primary Key : " + primaryKey +
            "\n Titre : " + titre +
            "\n Auteur : " + auteur +
            "\n ISBN : " + isbn;
    }
}
