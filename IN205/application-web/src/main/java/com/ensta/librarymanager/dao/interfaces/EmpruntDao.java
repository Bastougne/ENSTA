package com.ensta.librarymanager.dao.interfaces;

import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Emprunt;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;

public interface EmpruntDao {
    public List<Emprunt> getList() throws DaoException, SQLException;
    public List<Emprunt> getListCurrent() throws DaoException, SQLException;
    public List<Emprunt> getListCurrentByMembre( int idMembre ) throws DaoException, SQLException;
    public List<Emprunt> getListCurrentByLivre( int idLivre ) throws DaoException, SQLException;
    public Emprunt getById( int id ) throws DaoException, SQLException;
    public int create( int idMembre, int idLivre, LocalDate dateEmprunt ) throws DaoException, SQLException;
    public void update( Emprunt emprunt ) throws DaoException, SQLException;
    public int count() throws DaoException, SQLException;
}