package com.ensta.librarymanager.dao.implementation;

import com.ensta.librarymanager.dao.interfaces.LivreDao;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Livre;
import com.ensta.librarymanager.persistence.ConnectionManager;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class LivreDaoImpl implements LivreDao {
    private static LivreDaoImpl instance;

    private LivreDaoImpl() {}

    public static LivreDaoImpl getInstance() {
        if ( instance == null )
            instance = new LivreDaoImpl();
        return instance;
    }

    public List<Livre> getList() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "SELECT id, titre, auteur, isbn FROM livre;" );

        ResultSet listResultSet = stnt.executeQuery();
        List<Livre> list = new ArrayList<Livre>();
        while ( listResultSet.next() ) {
            list.add( new Livre( listResultSet.getInt( "id" ),
                                 listResultSet.getString( "titre" ),
                                 listResultSet.getString( "auteur" ),
                                 listResultSet.getString( "ISBN" ) ) );
        }
        conn.close();
        return list;
    }

    public Livre getById( int id ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "SELECT id, titre, auteur, isbn FROM livre WHERE id = ?;" );
        stnt.setInt( 1, id );

        ResultSet livreResultSet = stnt.executeQuery();
        livreResultSet.next();
        Livre livre = new Livre( id,
                                 livreResultSet.getString( "titre" ),
                                 livreResultSet.getString( "auteur" ),
                                 livreResultSet.getString( "ISBN" ) );
        conn.close();
        return livre;
    }

    public int create( String titre, String auteur, String isbn ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "INSERT INTO livre(titre, auteur, isbn) VALUES (?, ?, ?);" );
        stnt.setString( 1, titre );
        stnt.setString( 2, auteur );
        stnt.setString( 3, isbn );

        int created = stnt.executeUpdate();
        conn.close();
        return created;
    }

    public void update( Livre livre ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement(
            "UPDATE livre SET titre = ?, auteur = ?, isbn = ? WHERE id = ?;" );
        stnt.setString( 1, livre.getTitre() );
        stnt.setString( 2, livre.getAuteur() );
        stnt.setString( 3, livre.getIsbn() );
        stnt.setInt( 4, livre.getPrimaryKey() );

        stnt.executeUpdate();
        conn.close();
    }

    public void delete( int id ) throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "DELETE FROM livre WHERE id = ?;" );
        stnt.setInt( 1, id );

        stnt.executeUpdate();
        conn.close();
    }

    public int count() throws DaoException, SQLException {
        Connection conn = ConnectionManager.getConnection();
        PreparedStatement stnt = conn.prepareStatement( "SELECT COUNT(id) AS count FROM livre;" );

        ResultSet countResultSet = stnt.executeQuery();
        countResultSet.next();
        int count = countResultSet.getInt( "count" );
        conn.close();
        return count;
    }
}
