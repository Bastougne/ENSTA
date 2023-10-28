package com.ensta.librarymanager.dao.implementation;

import com.ensta.librarymanager.dao.interfaces.MembreDao;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Membre;
import com.ensta.librarymanager.persistence.ConnectionManager;
import com.ensta.librarymanager.utils.Abonnement;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class MembreDaoImpl implements MembreDao {
    private static MembreDaoImpl instance;

    private MembreDaoImpl() {}

    public static MembreDaoImpl getInstance() {
        if ( instance == null )
            instance = new MembreDaoImpl();
        return instance;
    }

    public List<Membre> getList() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT id, nom, prenom, adresse, email, telephone, abonnement FROM membre ORDER BY nom, prenom;" );

        ResultSet listResultSet = stnt.executeQuery();
        List<Membre> list = new ArrayList<Membre>();
        while ( listResultSet.next() ) {
            list.add( new Membre( listResultSet.getInt( "id" ),
                                  listResultSet.getString( "nom" ),
                                  listResultSet.getString( "prenom" ),
                                  listResultSet.getString( "adresse" ),
                                  listResultSet.getString( "email" ),
                                  listResultSet.getString( "telephone" ),
                                  Abonnement.valueOf( listResultSet.getString( "abonnement" ) ) ) );
        }
        conn.close();
        return list;
    }

    public Membre getById( int id ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT id, nom, prenom, adresse, email, telephone, abonnement FROM membre WHERE id = ?;" );
        stnt.setInt( 1, id );
        ResultSet membreResultSet = stnt.executeQuery();
        membreResultSet.next();
        Membre membre = new Membre( membreResultSet.getInt( "id" ),
                                    membreResultSet.getString( "nom" ),
                                    membreResultSet.getString( "prenom" ),
                                    membreResultSet.getString( "adresse" ),
                                    membreResultSet.getString( "email" ),
                                    membreResultSet.getString( "telephone" ),
                                    Abonnement.valueOf( membreResultSet.getString( "abonnement" ) ) );
        conn.close();
        return membre;
    }

    public int create( String nom, String prenom, String adresse, String email, String telephone, Abonnement abonnement )throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "INSERT INTO membre(nom, prenom, adresse, email, telephone, abonnement) VALUES (?, ?, ?, ?, ?, ?);" );
        stnt.setString( 1, nom );
        stnt.setString( 2, prenom );
        stnt.setString( 3, adresse );
        stnt.setString( 4, email );
        stnt.setString( 5, telephone );
        stnt.setString( 6, abonnement.name() );

        int created = stnt.executeUpdate();
        conn.close();
        return created;
    }

    public void update( Membre membre ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "UPDATE membre SET nom = ?, prenom = ?, adresse = ?, email = ?, telephone = ?, abonnement = ? WHERE id = ?;" );
        stnt.setString( 1, membre.getNom() );
        stnt.setString( 2, membre.getPrenom() );
        stnt.setString( 3, membre.getAdresse() );
        stnt.setString( 4, membre.getEmail() );
        stnt.setString( 5, membre.getTelephone() );
        stnt.setString( 6, membre.getAbonnement().name() );

        stnt.executeUpdate();
        conn.close();
    }

    public void delete( int id ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "DELETE FROM membre WHERE id = ?;" );
        stnt.setInt( 1, id );

        stnt.executeUpdate();
        conn.close();
    }

    public int count() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "SELECT COUNT(id) AS count FROM membre;" );

        ResultSet countResultSet = stnt.executeQuery();
        countResultSet.next();
        int count = countResultSet.getInt( "count" );
        conn.close();
        return count;
    }
}
