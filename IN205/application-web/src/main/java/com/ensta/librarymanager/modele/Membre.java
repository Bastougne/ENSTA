package com.ensta.librarymanager.modele;

import com.ensta.librarymanager.utils.Abonnement;

public class Membre {
    private int primaryKey;
    private String nom;
    private String prenom;
    private String adresse;
    private String email;
    private String telephone;
    private Abonnement abonnement;

    public Membre( int primaryKey, String nom, String prenom, String adresse, String email, String telephone, Abonnement abonnement ) {
        this.primaryKey = primaryKey;
        this.nom = nom;
        this.prenom = prenom;
        this.adresse = adresse;
        this.email = email;
        this.telephone = telephone;
        this.abonnement = abonnement;
    }

    public Membre() {
        this.primaryKey = 0;
        this.nom = "";
        this.prenom = "";
        this.adresse = "";
        this.email = "";
        this.telephone = "";
        this.abonnement = Abonnement.NULL;
    }

    public int getPrimaryKey() { return primaryKey; }
    public String getNom() { return nom; }
    public String getPrenom() { return prenom; }
    public String getAdresse() { return adresse; }
    public String getEmail() { return email; }
    public String getTelephone() { return telephone; }
    public Abonnement getAbonnement() { return abonnement; }

    public void setPrimaryKey( int primaryKey ) { this.primaryKey = primaryKey; }
    public void setNom( String nom ) { this.nom = nom; }
    public void setPrenom( String prenom ) { this.prenom = prenom; }
    public void setAdresse( String adresse ) { this.adresse = adresse; }
    public void setEmail( String email ) { this.email = email; }
    public void setTelephone( String telephone ) { this.telephone = telephone; }
    public void setAbonnement( Abonnement abonnement ) { this.abonnement = abonnement; }

    public String toString() {
        return "Primary Key : " + primaryKey +
            "\n Nom : " + nom +
            "\n Prenom : " + prenom +
            "\n Adresse : " + adresse +
            "\n email : " + email +
            "\n Téléphone : " + telephone +
            "\n Abonnement : " + abonnement;
    }
}
