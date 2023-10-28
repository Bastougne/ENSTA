package com.ensta.librarymanager.dao.interfaces;

import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Livre;
import java.sql.SQLException;
import java.util.List;

public interface LivreDao {
    public List<Livre> getList() throws DaoException, SQLException;
    public Livre getById( int id ) throws DaoException, SQLException;
    public int create( String titre, String auteur, String isbn ) throws DaoException, SQLException;
    public void update( Livre livre ) throws DaoException, SQLException;
    public void delete( int id ) throws DaoException, SQLException;
    public int count() throws DaoException, SQLException;
}
