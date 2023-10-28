package com.ensta.librarymanager.dao.interfaces;

import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.modele.Membre;
import com.ensta.librarymanager.utils.Abonnement;

import java.sql.SQLException;
import java.util.List;

public interface MembreDao {
    public List<Membre> getList() throws DaoException, SQLException;
    public Membre getById( int id ) throws DaoException, SQLException;
    public int create( String nom, String prenom, String adresse, String email, String telephone, Abonnement abonnement ) throws DaoException, SQLException;
    public void update( Membre membre ) throws DaoException, SQLException;
    public void delete( int id ) throws DaoException, SQLException;
    public int count() throws DaoException, SQLException;
}
