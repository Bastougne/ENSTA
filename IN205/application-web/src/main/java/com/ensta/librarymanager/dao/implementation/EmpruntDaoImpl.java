package com.ensta.librarymanager.dao.implementation;

import com.ensta.librarymanager.dao.interfaces.EmpruntDao;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Emprunt;
import com.ensta.librarymanager.persistence.ConnectionManager;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class EmpruntDaoImpl implements EmpruntDao {
    private static EmpruntDaoImpl instance;

    private EmpruntDaoImpl() {}

    public static EmpruntDaoImpl getInstance() {
        if ( instance == null )
            instance = new EmpruntDaoImpl();
        return instance;
    }

    public List<Emprunt> getList() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT e.id AS id, idMembre, nom, prenom, adresse, email, telephone, abonnement, idLivre, titre, auteur,"
            + " isbn, dateEmprunt, dateRetour FROM emprunt AS e INNER JOIN membre ON membre.id = e.idMembre INNER JOIN"
            + " livre ON livre.id = e.idLivre ORDER BY dateRetour DESC;" );

        ResultSet listResultSet = stnt.executeQuery();
        List<Emprunt> list = new ArrayList<Emprunt>();
        while ( listResultSet.next() ) {
            java.sql.Date dateRetour = listResultSet.getDate( "dateRetour" );
            list.add( new Emprunt( listResultSet.getInt( "id" ),
                                   MembreDaoImpl.getInstance().getById( listResultSet.getInt( "idMembre" ) ),
                                   LivreDaoImpl.getInstance().getById( listResultSet.getInt( "idLivre" ) ),
                                   listResultSet.getDate( "dateEmprunt" ).toLocalDate(),
                                   ( dateRetour == null ) ? null : dateRetour.toLocalDate() ) );
        }
        conn.close();
        return list;
    };

    public List<Emprunt> getListCurrent() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT e.id AS id, idMembre, nom, prenom, adresse, email, telephone, abonnement, idLivre, titre, auteur,"
            + " isbn, dateEmprunt, dateRetour FROM emprunt AS e INNER JOIN membre ON membre.id = e.idMembre INNER JOIN"
            + " livre ON livre.id = e.idLivre WHERE dateRetour IS NULL;" );

        ResultSet listResultSet = stnt.executeQuery();
        List<Emprunt> list = new ArrayList<Emprunt>();
        while ( listResultSet.next() ) {
            java.sql.Date dateRetour = listResultSet.getDate( "dateRetour" );
            list.add( new Emprunt( listResultSet.getInt( "id" ),
                                   MembreDaoImpl.getInstance().getById( listResultSet.getInt( "idMembre" ) ),
                                   LivreDaoImpl.getInstance().getById( listResultSet.getInt( "idLivre" ) ),
                                   listResultSet.getDate( "dateEmprunt" ).toLocalDate(),
                                   ( dateRetour == null ) ? null : dateRetour.toLocalDate() ) );
        }
        conn.close();
        return list;
    };

    public List<Emprunt> getListCurrentByMembre( int idMembre ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT e.id AS id, idMembre, nom, prenom, adresse, email, telephone, abonnement, idLivre, titre, auteur,"
            + " isbn, dateEmprunt, dateRetour FROM emprunt AS e INNER JOIN membre ON membre.id = e.idMembre INNER JOIN"
            + " livre ON livre.id = e.idLivre WHERE dateRetour IS NULL AND membre.id = ?;" );
        stnt.setInt( 1, idMembre );

        ResultSet listResultSet = stnt.executeQuery();
        List<Emprunt> list = new ArrayList<Emprunt>();
        while ( listResultSet.next() ) {
            java.sql.Date dateRetour = listResultSet.getDate( "dateRetour" );
            list.add( new Emprunt( listResultSet.getInt( "id" ),
                                   MembreDaoImpl.getInstance().getById( listResultSet.getInt( "idMembre" ) ),
                                   LivreDaoImpl.getInstance().getById( listResultSet.getInt( "idLivre" ) ),
                                   listResultSet.getDate( "dateEmprunt" ).toLocalDate(),
                                   ( dateRetour == null ) ? null : dateRetour.toLocalDate() ) );
        }
        conn.close();
        return list;
    };

    public List<Emprunt> getListCurrentByLivre( int idLivre ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT e.id AS id, idMembre, nom, prenom, adresse, email, telephone, abonnement, idLivre, titre, auteur,"
            + " isbn, dateEmprunt, dateRetour FROM emprunt AS e INNER JOIN membre ON membre.id = e.idMembre INNER JOIN"
            + " livre ON livre.id = e.idLivre WHERE dateRetour IS NULL AND livre.id = ?;" );
            stnt.setInt( 1, idLivre );

        ResultSet listResultSet = stnt.executeQuery();
        List<Emprunt> list = new ArrayList<Emprunt>();
        while ( listResultSet.next() ) {
            java.sql.Date dateRetour = listResultSet.getDate( "dateRetour" );
            list.add( new Emprunt( listResultSet.getInt( "id" ),
                                   MembreDaoImpl.getInstance().getById( listResultSet.getInt( "idMembre" ) ),
                                   LivreDaoImpl.getInstance().getById( listResultSet.getInt( "idLivre" ) ),
                                   listResultSet.getDate( "dateEmprunt" ).toLocalDate(),
                                   ( dateRetour == null ) ? null : dateRetour.toLocalDate() ) );
        }
        conn.close();
        return list;
    };

    public Emprunt getById( int id ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "SELECT e.id AS id, idMembre, nom, prenom, adresse, email, telephone, abonnement, idLivre, titre, auteur,"
            + " isbn, dateEmprunt, dateRetour FROM emprunt AS e INNER JOIN membre ON membre.id = e.idMembre INNER JOIN"
            + " livre ON livre.id = e.idLivre WHERE e.id = ?;" );
        stnt.setInt( 1, id );

        ResultSet empruntResultSet = stnt.executeQuery();
        empruntResultSet.next();
        java.sql.Date dateRetour = empruntResultSet.getDate( "dateRetour" );
        Emprunt emprunt = new Emprunt( id,
                                       MembreDaoImpl.getInstance().getById( empruntResultSet.getInt( "idMembre" ) ),
                                       LivreDaoImpl.getInstance().getById( empruntResultSet.getInt( "idLivre" ) ),
                                       empruntResultSet.getDate( "dateEmprunt" ).toLocalDate(),
                                       ( dateRetour == null ) ? null : dateRetour.toLocalDate() );
        conn.close();
        return emprunt;
    };

    public int create( int idMembre, int idLivre, LocalDate dateEmprunt ) throws DaoException, SQLException{
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "INSERT INTO emprunt(idMembre, idLivre, dateEmprunt, dateRetour) VALUES (?, ?, ?, ?);" );
        stnt.setInt( 1, idMembre );
        stnt.setInt( 2, idLivre );
        stnt.setDate( 3, java.sql.Date.valueOf( dateEmprunt ) );
        stnt.setDate( 4, null );

        int created = stnt.executeUpdate();
        conn.close();
        return created;
    };

    public void update( Emprunt emprunt ) throws DaoException, SQLException{
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "UPDATE emprunt SET idMembre = ?, idLivre = ?, dateEmprunt = ?, dateRetour = ? WHERE id = ?;" );
        stnt.setInt( 1, emprunt.getMembre().getPrimaryKey() );
        stnt.setInt( 2, emprunt.getLivre().getPrimaryKey() );
        stnt.setDate( 3, java.sql.Date.valueOf( emprunt.getDateEmprunt() ) );
        stnt.setDate( 4, java.sql.Date.valueOf( emprunt.getDateRetour() ) );
        stnt.setInt( 5, emprunt.getPrimaryKey() );

        stnt.executeUpdate();
        conn.close();
    };

    public int count() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "SELECT COUNT(id) AS count FROM emprunt;" );

        ResultSet countResultSet = stnt.executeQuery();
        countResultSet.next();
        int count = countResultSet.getInt( "count" );
        conn.close();
        return count;
    };
}
